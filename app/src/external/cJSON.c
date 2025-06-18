// cJSON.c - https://raw.githubusercontent.com/DaveGamble/cJSON/master/cJSON.c

#include "cJSON.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* Internal functions forward */
static cJSON *cJSON_New_Item(void);
static const char *parse_value(cJSON *item, const char *value);
static char *print_value(const cJSON *item, int depth, int fmt);
static char *print_number(const cJSON *item);

/* cJSON root parsing function */

cJSON *cJSON_Parse(const char *value) {
    if (!value) return NULL;
    cJSON *c = cJSON_New_Item();
    if (!c) return NULL;
    if (!parse_value(c, value)) {
        cJSON_Delete(c);
        return NULL;
    }
    return c;
}

/* Print without formatting */
char *cJSON_PrintUnformatted(const cJSON *item) {
    return print_value(item, 0, 0);
}

void cJSON_Delete(cJSON *c) {
    cJSON *next;
    while (c) {
        next = c->next;
        if (c->child) cJSON_Delete(c->child);
        if (c->valuestring) free(c->valuestring);
        if (c->string) free(c->string);
        free(c);
        c = next;
    }
}

/* Utility functions definition (omitted for brevity) ... */

/* Creation utilities */
cJSON *cJSON_CreateArray(void)    { cJSON *item = cJSON_New_Item(); item->type = cJSON_Array; return item; }
cJSON *cJSON_CreateObject(void)   { cJSON *item = cJSON_New_Item(); item->type = cJSON_Object; return item; }
cJSON *cJSON_CreateString(const char *string) {
    cJSON *item = cJSON_New_Item();
    item->type = cJSON_String;
    item->valuestring = strdup(string);
    return item;
}
cJSON *cJSON_CreateNumber(double num) {
    cJSON *item = cJSON_New_Item();
    item->type = cJSON_Number;
    item->valuedouble = num;
    item->valueint = (int)num;
    return item;
}

cJSON *cJSON_CreateIntArray(const int *numbers, int count) {
    cJSON *array = cJSON_CreateArray();
    for (int i = 0; i < count; i++) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(numbers[i]));
    }
    return array;
}

void cJSON_AddItemToArray(cJSON *array, cJSON *item) {
    cJSON *c = array->child;
    if (!item) return;
    if (!c) {
        array->child = item;
    } else {
        while (c->next) c = c->next;
        c->next = item;
        item->prev = c;
    }
}

void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item) {
    if (!item) return;
    item->string = strdup(string);
    cJSON_AddItemToArray(object, item);
}

void cJSON_AddNumberToObject(cJSON *object, const char *string, double number) {
    cJSON_AddItemToObject(object, string, cJSON_CreateNumber(number));
}

/* Note: Due to length constraints, parsing and full printing logic are omitted. */
