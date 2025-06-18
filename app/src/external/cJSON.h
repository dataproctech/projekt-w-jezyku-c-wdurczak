// cJSON.h - https://raw.githubusercontent.com/DaveGamble/cJSON/master/cJSON.h

#ifndef CJSON__H
#define CJSON__H

#ifdef __cplusplus
extern "C" {
#endif

/* cJSON Types: */
#define cJSON_Invalid (0)
#define cJSON_False   (1 << 0)
#define cJSON_True    (1 << 1)
#define cJSON_NULL    (1 << 2)
#define cJSON_Number  (1 << 3)
#define cJSON_String  (1 << 4)
#define cJSON_Array   (1 << 5)
#define cJSON_Object  (1 << 6)

/* The cJSON structure: */
typedef struct cJSON {
    struct cJSON *next;
    struct cJSON *prev;
    struct cJSON *child;

    int type;

    char *valuestring;
    int valueint;
    double valuedouble;

    char *string;
} cJSON;

/* Parse JSON text to a cJSON object. Returns NULL on error. */
cJSON *cJSON_Parse(const char *value);

/* Render a cJSON entity to text. */
char *cJSON_PrintUnformatted(const cJSON *item);

/* Delete a cJSON entity and all subentities. */
void cJSON_Delete(cJSON *c);

/* Returns the array size, or 0 if not an array. */
int cJSON_GetArraySize(const cJSON *array);

/* Retrieve item number "item" from array "array". Returns NULL if unsuccessful. */
cJSON *cJSON_GetArrayItem(const cJSON *array, int item);

/* Get item "string" from object. Case insensitive. */
cJSON *cJSON_GetObjectItem(const cJSON *object, const char *string);

/* Returns true if the item is type number. */
int cJSON_IsNumber(const cJSON *item);

/* Returns true if the item is type string. */
int cJSON_IsString(const cJSON *item);

/* Utility for creating arrays and objects. */
cJSON *cJSON_CreateArray(void);
cJSON *cJSON_CreateObject(void);
/* Utilities for creating basic types. */
cJSON *cJSON_CreateString(const char *string);
cJSON *cJSON_CreateNumber(double num);
cJSON *cJSON_CreateIntArray(const int *numbers, int count);

/* Add item to array/object. */
void cJSON_AddItemToArray(cJSON *array, cJSON *item);
void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
void cJSON_AddNumberToObject(cJSON *object, const char *string, double number);

#ifdef __cplusplus
}
#endif

#endif // CJSON__H