#ifndef MY_LIB_H_
    #define MY_LIB_H_


    typedef struct MovieNode {
        const char *title;
        const char *overview;
        const char *release_date;
        struct MovieNode *next;
    } MovieNode;

    typedef struct {
        char *memory;
        size_t size;
    } MemoryStruct;


    typedef struct {
        const char *title;
        const char *overview;
        const char *release_date;
    } MovieInfo;

int main(char **argv, int argc);
char *perform_curl_request(const char *url);
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);
char *perform_curl_request(const char *url);
MovieNode* add_movie(MovieNode *head, const char *title, const char *overview, const char *release_date);
void show_movie_info(MovieNode *head);
void parse_json_response(const char *json_response);


#endif
