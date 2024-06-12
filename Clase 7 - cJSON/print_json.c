#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

void parse_json_object(char* json_string){

    cJSON *json = cJSON_Parse(json_string);
    if(json == NULL){
        perror("Error Parse JSON");
    }

    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON *lastname = cJSON_GetObjectItemCaseSensitive(json, "lastname");

    // printf("%s", name->type);

    printf("%s %s \n", name->valuestring, lastname->valuestring);

    cJSON_Delete(json);
}   

int main(){

    char *my_json = "{\"name\":\"Derek\", \"lastname\":\"Esquivel\"}";
    parse_json_object(my_json);

}