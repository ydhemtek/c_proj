#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "../include/my_lib.h"

void show_movie_info(MovieNode *head)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *separator;
    char buffer[500];
    int i = 0;

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Informations sur les films");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    MovieNode *current = head;
    while (current != NULL)
    {
        sprintf(buffer, "Title : %s", current->title);
        label = gtk_label_new(buffer);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i * 4, 1, 1);

        sprintf(buffer, "Synopsis : %s", current->overview);
        label = gtk_label_new(buffer);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i * 4 + 1, 1, 1);

        sprintf(buffer, "Date : %s", current->release_date);
        label = gtk_label_new(buffer);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i * 4 + 2, 1, 1);

        separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
        gtk_grid_attach(GTK_GRID(grid), separator, 0, i * 4 + 3, 1, 1);

        current = current->next;
        i++;
    }

    gtk_widget_show_all(window);
    gtk_main();
}

MovieNode *add_movie(MovieNode *head, const char *title, const char *overview, const char *release_date)
{
    MovieNode *new_movie = (MovieNode *)malloc(sizeof(MovieNode));
    new_movie->title = title;
    new_movie->overview = overview;
    new_movie->release_date = release_date;
    new_movie->next = head;
    return new_movie;
}

void parse_json_response(const char *json_response)
{
    cJSON *root = cJSON_Parse(json_response);
    if (root == NULL)
    {
        printf("Erreur de parsing JSON : %s\n", cJSON_GetErrorPtr());
        return;
    }

    cJSON *results = cJSON_GetObjectItem(root, "results");
    if (cJSON_IsArray(results))
    {
        int num_results = cJSON_GetArraySize(results);
        MovieNode *head = NULL;

        for (int i = 0; i < num_results; ++i)
        {
            cJSON *result = cJSON_GetArrayItem(results, i);

            cJSON *title = cJSON_GetObjectItem(result, "title");
            cJSON *overview = cJSON_GetObjectItem(result, "overview");
            cJSON *release_date = cJSON_GetObjectItem(result, "release_date");

            if (cJSON_IsString(title) && cJSON_IsString(overview) && cJSON_IsString(release_date))
            {
                head = add_movie(head, title->valuestring, overview->valuestring, release_date->valuestring);
            }
        }

        show_movie_info(head);

        MovieNode *current = head;
        while (current != NULL)
        {
            MovieNode *temp = current;
            current = current->next;
            free(temp);
        }
    }

    cJSON_Delete(root);
}
