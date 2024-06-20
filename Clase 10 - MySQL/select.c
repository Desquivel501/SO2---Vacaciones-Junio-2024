#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	MYSQL *conn;
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


    /* Enviamos la query a la base de datos */
    if(mysql_query(conn, "SELECT * FROM usuarios")){
        mysql_close(conn);
        exit(1);
    }

    /*Extraemos los resultados de conn*/
    MYSQL_RES *res = mysql_store_result(conn);
    if(res == NULL){
        mysql_close(conn);
        exit(1);
    }

    /*Obtenemos el numero de columnas de la tabla en resultados*/
    int num_fields = mysql_num_fields(res);

    /*Recorremos los registros del resultado y los imprimimos*/
    while(row = mysql_fetch_row(res)){
        for(int i = 0; i < num_fields; i++){
            printf("%s | ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(res);
	mysql_close(conn);
}