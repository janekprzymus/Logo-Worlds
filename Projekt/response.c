#include "response.h"

current *read_response(char *response)
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

fields3 *read_response_explore(char *response)
{
    fields3 *a = NULL;
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
    a = malloc(sizeof(fields3));
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

void free_game_state(current *g){
    free(g->type);
    free(g->direction);
    free(g);
}

void free_game_state_explore(fields3 *g){
    for(int i=0; i<3; i++){
    free(g->type[i]);
    }
    free(g);
}