#include "response.h"

pole *dzejson(char *response)
{
    pole *a;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    cJSON *response_json = cJSON_Parse(response);
    if (response_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }
    payload = cJSON_GetObjectItemCaseSensitive(response_json, "payload");

        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
        cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");

        if (!cJSON_IsNumber(current_x) || !cJSON_IsNumber(current_y))
        {
            goto end;
        }

        a = malloc(sizeof(pole));
        a->x=current_x->valueint;
        a->y=current_y->valueint;
        a->type = (char*) malloc(sizeof(char) * (strlen(field_type->valuestring) + 1));
        strcpy(a->type, field_type->valuestring);

end:
    cJSON_Delete(response_json);
    return a;
}

pole3 *dzejson_explore(char *response)
{
    pole3 *a = NULL;
    int i=0;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    const cJSON *list = NULL;
    const cJSON *field = NULL;
    cJSON *response_json = cJSON_Parse(response);
    if (response_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(response_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(response_json, "payload");
    list = cJSON_GetObjectItemCaseSensitive(payload, "list");
    a = malloc(sizeof(pole3));
    cJSON_ArrayForEach(field, list)
    {
        cJSON *x = cJSON_GetObjectItemCaseSensitive(field, "x");
        cJSON *y = cJSON_GetObjectItemCaseSensitive(field, "y");
        cJSON *type = cJSON_GetObjectItemCaseSensitive(field, "type");

        if (!cJSON_IsNumber(x) || !cJSON_IsNumber(y))
        {
            goto end;
        }

        a->x[i]=x->valueint;
        a->y[i]=y->valueint;
        a->type[i] = (char*) malloc(sizeof(char) * (strlen(type->valuestring) + 1));
        strcpy(a->type[i], type->valuestring);
        i++;
    }

end:
    cJSON_Delete(response_json);
    return a;
}

current *dzejson_current(char *response)
{
    current *a;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    cJSON *response_json = cJSON_Parse(response);
    if (response_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }
    payload = cJSON_GetObjectItemCaseSensitive(response_json, "payload");

        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
        cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
        cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");

        if (!cJSON_IsNumber(current_x) || !cJSON_IsNumber(current_y))
        {
            goto end;
        }

        a = malloc(sizeof(current));
        a->x=current_x->valueint;
        a->y=current_y->valueint;
        a->type = (char*) malloc(sizeof(char) * (strlen(field_type->valuestring) + 1));
        a->direction = (char*) malloc(sizeof(char) * (strlen(direction->valuestring) + 1));
        strcpy(a->type, field_type->valuestring);
        strcpy(a->direction, direction->valuestring);

end:
    cJSON_Delete(response_json);
    return a;
}