#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "../include/my_lib.h"

int main(char **argv, int argc)
{
    const char *url = "https://api.themoviedb.org/3/movie/now_playing?api_key=0c0e2f25660076cecabb64bac1c723fc";
    char *response = perform_curl_request(url);

    if (response != NULL)
    {
        parse_json_response(response);
        free(response);
    }

    return 0;
}
