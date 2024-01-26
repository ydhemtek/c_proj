#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "../include/my_lib.h"


void parse_config_line(Config *config, const char *line)
{
    char key[50];
    char value[200];

    if (sscanf(line, "%49s = %199s", key, value) == 2) {
        if (strcmp(key, "api_key") == 0) {
            strcpy(config->api_key, value);
        } else if (strcmp(key, "api_url") == 0) {
            strcpy(config->api_url, value);
        }
    }
}

Config read_config(const char *filename)
{
    Config config;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de la lecture du fichier de configuration");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        parse_config_line(&config, line);
    }

    fclose(file);

    return config;
}

int main(char **argv, int argc)
{
    Config config = read_config("config.txt");
     const char *url = config.api_url;
    const char *api_key = config.api_key;
    char *response = perform_curl_request(url);
    if (response != NULL)
    {
        parse_json_response(response);
        free(response);
    }

    return 0;
}
