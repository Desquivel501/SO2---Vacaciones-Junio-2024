#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>

struct data_struct {
    int id;
    char first_name[50];
    char last_name[50];
    char email[50];
};
struct data_struct usuarios[100];
int usuarios_size = 0;

void print_json_object(char *json_string) {
    cJSON *json = cJSON_Parse(json_string);
    char *formatted_json = cJSON_Print(json);
    printf("%s\n", formatted_json);
    cJSON_Delete(json);
    free(formatted_json);
}

void read_json_file(char* filename){

    // Open the JSON file for reading
    FILE *file = fopen(filename, "r");
    if(!file){
        perror("Open File");
        return;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read the entire file into a buffer
    char *buffer = (char*)malloc(filesize + 1);
    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';

    // Close the file
    fclose(file);

    // Parse the JSON data
    cJSON *json = cJSON_Parse(buffer);
    if(json == NULL){
        perror("Parse JSON");
        return;
    }

    // Check if it's a valid JSON array
    if(!cJSON_IsArray(json)){
        perror("JSON is not Array");
        return;
    }

    // Iterate through the array

    // int array_size = cJSON_GetArraySize(json);
    // for(int i = 0; i< array_size; i++){
    //     cJSON *item = cJSON_GetArrayItem(json, i);
    //     if(cJSON_IsObject(item)){
    //         cJSON *id = cJSON_GetObjectItem(item, "id");
    //         cJSON *firstname = cJSON_GetObjectItem(item, "first_name");
    //         cJSON *lastname = cJSON_GetObjectItem(item, "last_name");
    //         cJSON *email = cJSON_GetObjectItem(item, "email");

    //         if(cJSON_IsNumber(id) && cJSON_IsString(firstname) 
    //             && cJSON_IsString(firstname) && cJSON_IsString(firstname)){

    //                 printf("ID: %d - Name: %s %s - Email: %s\n", id->valueint, 
    //                     firstname->valuestring, lastname->valuestring, email->valuestring);
    //             }

    //     }
    // }

    int n = 0;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, json){
        if(cJSON_IsObject(item)){
            cJSON *id = cJSON_GetObjectItem(item, "id");
            cJSON *firstname = cJSON_GetObjectItem(item, "first_name");
            cJSON *lastname = cJSON_GetObjectItem(item, "last_name");
            cJSON *email = cJSON_GetObjectItem(item, "email");

            if(cJSON_IsNumber(id) && cJSON_IsString(firstname) 
                && cJSON_IsString(lastname) && cJSON_IsString(email)){

                    usuarios[n].id = id -> valueint;
                    sprintf(usuarios[n].first_name , "%s", firstname -> valuestring);
                    sprintf(usuarios[n].last_name , "%s", lastname -> valuestring);
                    sprintf(usuarios[n].email , "%s", email -> valuestring);
                    n++;
            }

        }
    }
    usuarios_size = n;

    // Clean up
    cJSON_Delete(json);
    free(buffer);

}

char* struct_to_json(){

    // Create an empty JSON Array
    cJSON *json_array = cJSON_CreateArray();

    // Iterate through the structs
    for(int i = 0; i < usuarios_size; i++){
        // Create an emty JSON Object
        cJSON *item = cJSON_CreateObject();

        // Add attributes to the object
        cJSON_AddNumberToObject(item, "id", usuarios[i].id);
        cJSON_AddStringToObject(item, "first_name", usuarios[i].first_name);
        cJSON_AddStringToObject(item, "last_name", usuarios[i].last_name);
        cJSON_AddStringToObject(item, "email", usuarios[i].email);

        // Add the opbject to the Array
        cJSON_AddItemToArray(json_array, item);
    }

    // Format the JSON Array 
    char* formatted = cJSON_Print(json_array);
    return formatted;
}

void write_file(char* filename, char* data){
    //Open the file
    FILE *file = fopen(filename, "wb");
    if(file == NULL){
        perror("Open file");
        return;
    }

    // Write the data
    fwrite(data, 1, strlen(data), file);
    fclose(file);
}

int main(){

    char* filename = "MOCK_DATA.json";
    read_json_file(filename);

    for(int i = 0; i < usuarios_size; i++){
        printf("Id: %d   Nombre: %s   Apellido: %s   Email: %s\n", 
            usuarios[i].id, usuarios[i].first_name, usuarios[i].last_name, usuarios[i].email);
    }

    sprintf(usuarios[0].first_name , "Carlos");
    sprintf(usuarios[0].last_name , "Soto");

    char* new_json = struct_to_json();
    write_file("my_json.json", new_json);
}