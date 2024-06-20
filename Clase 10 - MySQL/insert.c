#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define USERS_SIZE 100

struct data_struct {
    int id;
    char first_name[50];
    char last_name[50];
    char email[50];
};

struct data_struct usuarios[USERS_SIZE];

void parseFile(){
    FILE *fp;
    fp = fopen("usuarios.csv", "r");

    char row[1000];
    char *token;

    fgets(row, 1000, fp);

    int n = 0;

    while (feof(fp) != true){

        fgets(row, 1000, fp);

        char *pos;
        if ((pos=strchr(row, '\n')) != NULL) *pos = '\0';
            
        token = strtok(row, ",");
        usuarios[n].id = atoi(token);

        token = strtok(NULL, ",");
        sprintf(usuarios[n].first_name, "%s", token);

        token = strtok(NULL, ",");
        sprintf(usuarios[n].last_name, "%s", token);

        token = strtok(NULL, ",");
        sprintf(usuarios[n].email, "%s", token);

        n++;
    }
}

int main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char* server = "34.41.222.209";
	char* user = "root";
	char* password = "szM0Fl2uaFR~_O|P";
	char* database = "ejemplo";
	
	conn = mysql_init(NULL);	

	
	/* Conexión a la base de datos */
	if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	

    /*Insertar registro de forma individual*/
    if (mysql_query(conn, "INSERT INTO usuarios VALUES('1','Derek', 'Esquivel', 'test@gmail.com')")) {
        mysql_close(conn);
        exit(1);
    }

    /*Insertar registros de forma masiva*/

    parseFile();

    /*Se agrega el incio de la query*/
    char query[2000];
    strcat(query, "INSERT INTO usuarios (ID, FirstName, LastName, Email) values ");
    
    /*Se concatenan a la query los valores*/
    for(int i = 0; i < 5; i++){
        char str_row[200];
        sprintf(str_row, "(%d, '%s', '%s', '%s'),", usuarios[i].id, usuarios[i].first_name, usuarios[i].last_name, usuarios[i].email);
        strcat(query, str_row);
    }

    /*Reemplazamos la ultima ',' por un ';'*/
    size_t length = strlen(query);
    query[length-1] = ';';

    /*Ejecutamos la query*/
    if (mysql_query(conn, query)) {
        mysql_close(conn);
        exit(1);
    }

	mysql_close(conn);
}