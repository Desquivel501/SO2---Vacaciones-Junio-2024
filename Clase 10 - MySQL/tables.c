#include <mysql/mysql.h>
#include <stdio.h>

int 	main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char *server = "34.41.222.209";
	char *user = "root";
	char *password = "szM0Fl2uaFR~_O|P";
	char *database = "ejemplo";
	
	conn = mysql_init(NULL);	
	
	/* Conexión a la base de datos */
	if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
	/* Enviamos la query a la base de datos */
	if (mysql_query(conn, "show tables")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
   
	res = mysql_use_result(conn);
	
	/* Imprimimos los resultados */
	printf("Tablas en la base de datos:  %s:\n", database);
   
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s \n", row[0]);
   
	/* Cerramos la conexión */
	mysql_free_result(res);
	mysql_close(conn);
}