#include "api_client.h"
#include <curl/curl.h>
#include <cjson/CJSON.h>
#include <stdlib.h>
#include <string.h>

struct {
    char *ptr;
    size_t len;
} static resp = { .ptr = NULL, .len = 0 };

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t new_len = resp.len + size*nmemb;
    resp.ptr = realloc(resp.ptr, new_len+1);
    memcpy(resp.ptr + resp.len, data, size*nmemb);
    resp.ptr[new_len] = '\\0';
    resp.len = new_len;
    return size*nmemb;
}

bool get_best_move_api(int player, int board[3][3], int *row, int *col) {
    CURL *curl = curl_easy_init();
    if (!curl) return false;

    cJSON *root = cJSON_CreateObject();
    cJSON *b    = cJSON_CreateArray();
    for (int r = 0; r < 3; ++r) {
        cJSON *rowArr = cJSON_CreateIntArray(board[r], 3);
        cJSON_AddItemToArray(b, rowArr);
    }
    cJSON_AddItemToObject(root, "board", b);
    cJSON_AddNumberToObject(root, "player", player);
    char *body = cJSON_PrintUnformatted(root);

    curl_easy_setopt(curl, CURLOPT_URL,    "http://127.0.0.1:8000/move");
    curl_easy_setopt(curl, CURLOPT_POST,   1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    struct curl_slist *hdr = NULL;
    hdr = curl_slist_append(hdr, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hdr);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    free(resp.ptr); resp.ptr = NULL; resp.len = 0;

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(hdr);
    curl_easy_cleanup(curl);
    cJSON_Delete(root);
    free(body);

    if (res != CURLE_OK || !resp.ptr) return false;


    cJSON *json = cJSON_Parse(resp.ptr);
    if (!json) return false;
    cJSON *jr = cJSON_GetObjectItem(json, "row");
    cJSON *jc = cJSON_GetObjectItem(json, "col");
    if (!cJSON_IsNumber(jr) || !cJSON_IsNumber(jc)) {
        cJSON_Delete(json);
        return false;
    }
    *row = jr->valueint;
    *col = jc->valueint;
    cJSON_Delete(json);
    return true;
}