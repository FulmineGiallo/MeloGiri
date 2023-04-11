#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mysql/mysql.h>

//gcc -o conn $(mysql_config --cflags) provaconn.c $(mysql_config --libs)

int main()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server="10.0.0.4"; //localhost
	char *user="gianluca"; //user db
	char *password="Password1234!"; //password db
	char *database="melogiri"; //nome db

	conn=mysql_init(NULL); //inizializzo la connessione

	//Connessione al database
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	//Eseguo la prima query
	if(mysql_query(conn, "SELECT * FROM utente"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}


	res=mysql_use_result(conn);

	printf("Result :\n");

	//Scorro i risultati
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s %s %s %s\n", row[0],row[1],row[2],row[3]);
	}

	//Chiudo il risultato
	mysql_free_result(res);

	//Eseguo la seconda query
	if(mysql_query(conn, "SELECT * FROM bevanda"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res=mysql_use_result(conn);

	//Scorro i risultati
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s %s %s %s %s %s %s\n", row[0],row[1],row[2],row[3],row[4],row[5],row[6]);
	}

	//Chiudo il risultato
	mysql_free_result(res);

	//Chiudo la connessione
	mysql_close(conn);

	return 0;
}
