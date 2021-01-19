#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

#define MAX 49

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

char *make_request(char *url){
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;
    //char *response = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK){
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("%s", chunk.response);
        }

        //response = (char*) malloc(sizeof(char) * strlen((chunk.response) + 1));
        //strcpy(response, chunk.response);
        //free(chunk.response);
        curl_easy_cleanup(curl);

    }
    return chunk.response;
}

char *info(char *token) {
    char url[255]="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
    char *response;
    strncat(url,token,10);
    printf("%s\n",url);
    printf("Wyświetlam informacje o świecie %s:\n\n",token);
    response=make_request(url);
    return response;
}

char *move(char *token) {
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

typedef struct _pole
{
    int x;
    int y;
    char *type;
} pole;

typedef struct _pole3
{
    int x[3];
    int y[3];
    char *type[3];
}   pole3;

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
        a->type = (char*) malloc(sizeof(char) * strlen((field_type->valuestring) + 1));
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
        a->type[i] = (char*) malloc(sizeof(char) * strlen((type->valuestring) + 1));
        strcpy(a->type[i], type->valuestring);
        i++;
    }

end:
    cJSON_Delete(response_json);
    return a;
}

void wypisz(char plansza[50][50]){
    int i, j;

    for(i=0;i<50;i++){
        for(j=0;j<50;j++){
            printf("%2c",plansza[i][j]);
        }
        printf("\n");
    }

}

void zapisz(char plansza[50][50]){
    FILE *fout = fopen("plansza.txt", "w");
    int i, j;

    for(i=0;i<50;i++){
        for(j=0;j<50;j++){
            fprintf(fout, "%c", plansza[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}

int wczytaj(char plansza[50][50]){
    FILE *fin = fopen("plansza.txt", "r");
    if(fin != NULL){
        int i, j;
        char bufor[51];
        for(i=0;i<50;i++){
            fgets(bufor, 52, fin);
            for(j=0;j<50;j++){
                plansza[i][j]=bufor[j];
            }
        }
        fclose(fin);
        return 1;
    }
    else
    {
        fclose(fin);
        return 0;
    }
    
    
}

int main(int argc, char **argv)
{
    /* Program obługuje się poprzez podanie tokena świata jako pierwszy argument linii komend.
    Następnie jeśli nie ma kolejnych argumentow - program wyświetla informacje o świecie.
    Jeśli następne argumenty występują, w zaleznosci od nich program wykonuje dane polecenia:
    ("M" - ruch, "Rleft" - obrot w lewo, "Rright" - obrot w prawo, "E" - eksploracja) */ 
    char *url;
    char *token;
    char *s1="M";
    char *s21="Rleft";
    char *s22="Rright";
    char *s3="E";
    char *s4="reset";
    token=argv[1];
    char plansza[50][50];
    int i, j;
    
    if(wczytaj(plansza)==0)
    {
        for(i=0;i<50;i++){
            for(j=0;j<50;j++){
                plansza[i][j]='.';
            }
        }
    }
    

    if(argc<3){
        char *response;
        response=info(token);
        free(response);
        wypisz(plansza);
    }
    else
    {
        int i;
        for(i=2;i<argc;i++){
            char *response;
            if(strcmp(argv[i],s1)==0){
                response=move(token);
                pole *field = dzejson(response);
                free(response);
                printf("x: %d\n",field->x);
                printf("y: %d\n",field->y);
                printf("Typ pola: %s\n",field->type);
                if(strcmp(field->type, "grass")==0)
                    plansza[MAX-field->y][field->x]='G';
                if(strcmp(field->type, "sand")==0)
                    plansza[MAX-field->y][field->x]='S';
                if(strcmp(field->type, "wall")==0)
                    plansza[MAX-field->y][field->x]='W';

                free(field->type);
                free(field);
            }
            else if(strcmp(argv[i],s21)==0){
                response=rotate(token,"left");
                free(response);
            }
            else if(strcmp(argv[i],s22)==0){
                response=rotate(token,"right");
                free(response);
            }
            else if(strcmp(argv[i],s3)==0){
                response=explore(token);
                pole3 *polee = dzejson_explore(response);
                free(response);
                printf("x_0: %d\n",polee->x[0]);
                printf("y_0: %d\n",polee->y[0]);
                printf("Typ pola 0: %s\n",polee->type[0]);
                printf("x_1: %d\n",polee->x[1]);
                printf("y_1: %d\n",polee->y[1]);
                printf("Typ pola 1: %s\n",polee->type[1]);
                printf("x_2: %d\n",polee->x[2]);
                printf("y_2: %d\n",polee->y[2]);
                printf("Typ pola 2: %s\n",polee->type[2]);
                if(strcmp(polee->type[0], "grass")==0)
                    plansza[MAX-polee->y[0]][polee->x[0]]='G';
                if(strcmp(polee->type[1], "grass")==0)
                    plansza[MAX-polee->y[1]][polee->x[1]]='G';
                if(strcmp(polee->type[2], "grass")==0)
                    plansza[MAX-polee->y[2]][polee->x[2]]='G';
                if(strcmp(polee->type[0], "sand")==0)
                    plansza[MAX-polee->y[0]][polee->x[0]]='S';
                if(strcmp(polee->type[1], "sand")==0)
                    plansza[MAX-polee->y[1]][polee->x[1]]='S';
                if(strcmp(polee->type[2], "sand")==0)
                    plansza[MAX-polee->y[2]][polee->x[2]]='S';
                if(strcmp(polee->type[0], "wall")==0)
                    plansza[MAX-polee->y[0]][polee->x[0]]='W';
                if(strcmp(polee->type[1], "wall")==0)
                    plansza[MAX-polee->y[1]][polee->x[1]]='W';
                if(strcmp(polee->type[2], "wall")==0)
                    plansza[MAX-polee->y[2]][polee->x[2]]='W';

                for(int i=0;i<3;i++){
                free(polee->type[i]);
                }
                free(polee);
            }
            else if(strcmp(argv[i],s4)==0){
                for(i=0;i<50;i++){
                    for(j=0;j<50;j++){
                        plansza[i][j]='.';
                    }
                }
                response=reset(token);
                pole *field = dzejson(response);
                free(response);
                printf("x: %d\n",field->x);
                printf("y: %d\n",field->y);
                printf("Typ pola: %s\n",field->type);
                if(strcmp(field->type, "grass")==0)
                    plansza[MAX-field->y][field->x]='G';
                if(strcmp(field->type, "sand")==0)
                    plansza[MAX-field->y][field->x]='S';
                if(strcmp(field->type, "wall")==0)
                    plansza[MAX-field->y][field->x]='W';

                free(field->type);
                free(field);
            }
            else
            {
                printf("\nBłąd: nieznana komenda!\n");
                exit(-1);
            }
            wypisz(plansza);
        }
    }
    
    zapisz(plansza);
    return 0;
}