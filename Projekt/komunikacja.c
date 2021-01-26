#include "komunikacja.h"

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    Memory *mem = (Memory *) userp;
    char *ptr = NULL;

    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; 

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

char *make_request(char *url){
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK){
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("%s", chunk.response);
        }

        curl_easy_cleanup(curl);

    }
    return chunk.response;
}

char *info(char *token){
    char url[255]="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
    char *response;
    strncat(url,token,10);
    printf("%s\n",url);
    printf("Wyświetlam informacje o położeniu dla świata %s:\n\n",token);
    response=make_request(url);
    return response;
}

char *move(char *token){
    char url[255]="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
    char *response;
    strncat(url,token,10);
    printf("%s\n",url);
    printf("Wykonuję ruch.\n\n");
    response=make_request(url);
    return response;
}

char *rotate(char *token, char *direction){
    char url[255]="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    char *response;
    strncat(url,token,10);
    strncat(url, "/", 2);
    strncat(url,direction,10);
    printf("%s\n",url);
    if(strcmp(direction, "left")==0)
        printf("Obracam w lewo.\n\n");
    if(strcmp(direction, "right")==0)
        printf("Obracam w prawo.\n\n");
    response=make_request(url);
    return response;
}

char *explore(char *token){
    char url[255]="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
    char *response;
    strncat(url,token,10);
    printf("%s\n",url);
    printf("Eksploruję.\n\n");
    response=make_request(url);
    return response;
}

char *reset(char *token){
    char url[255]="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/";
    char *response;
    strncat(url,token,10);
    printf("%s\n",url);
    printf("Resetuję świat: %s\n\n",token);
    response=make_request(url);
    return response;
}
