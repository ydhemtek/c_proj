#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "../include/my_lib.h"

char *perform_curl_request(const char *url)
{
    CURL *curl;
    CURLcode res;
    MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "Erreur lors de la requête : %s\n", curl_easy_strerror(res));
            free(chunk.memory);
            curl_easy_cleanup(curl);
            return NULL;
        }

        curl_easy_cleanup(curl);

        return chunk.memory;
    }
    else
    {
        fprintf(stderr, "Erreur lors de l'initialisation de libcurl.\n");
        return NULL;
    }
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userdata;

    char *ptr_reallocated = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr_reallocated == NULL)
    {
        fprintf(stderr, "Erreur de réallocation de mémoire.\n");
        return 0;
    }

    mem->memory = ptr_reallocated;
    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}
