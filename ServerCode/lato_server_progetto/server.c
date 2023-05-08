#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include "cJSON.h"

#define PORT 8080
#define MESSAGE_SIZE 256
void trim(char *str);

char *subString(char *string, char *posIniziale, char *posFinale)
{
    int len = (posFinale - posIniziale) - 1;
    char *subString = malloc(len + 1); // +1 per il carattere di terminazione

    strncpy(subString, posIniziale, len);
    subString[len] = '\0'; // aggiungi il carattere di terminazione

	trim(subString);

    return subString;
}

void trim(char *str)
{
    int len = strlen(str);
    int i = 0;
    while (isspace(str[i])) {  // Rimuovi gli spazi iniziali
        i++;
    }
    if (i > 0) {
        memmove(str, str + i, len - i + 1);  // Sposta la stringa
        len -= i;
    }
    i = len - 1;
    while (i >= 0 && isspace(str[i])) {  // Rimuovi gli spazi finali
        str[i] = '\0';
        i--;
    }
}
//creo un thread per la gestione di connessione e query mysql. questo script andrà inserito all'interno della socket del server
void *thread_login(void *arg)
{
	char buffer[1024];
	char sceltaStart[1000];
   	int bytesRecv = 0; // Indicatori di errore di ricezione

	MYSQL *conn; //oggetto per stabilire la connessione
	MYSQL_RES *res; //oggetto per i scorrere i risultati delle query
	//MYSQL_ROW row; oggetto per individuare le righe delle tabelle

	char *server="localhost"; //host a cui connettersi IP_privato
	char *username="root"; //user db
	char *password="fulmine13"; //password db
	char *database="melogiri"; //nomedb
	char query[1000];

	conn=mysql_init(NULL);
	
	if(!mysql_real_connect(conn,server,username,password,database,0,NULL,0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	else 
		printf("Connessione avvenuta al DATABASE \n");

	char *message; //Messaggio che ricevo dal client

	//FORMAT message : 1email||password
	int newSocket = *((int *)arg);
	// Riceve messaggio Scelta login dal client
    bytesRecv = 0;
    do
    {
        bytesRecv = recv(newSocket, (char *)sceltaStart, sizeof(sceltaStart), 0);
        if (bytesRecv == -1)
        {
            printf( "\nConnection Closed.\n");
            break;
        }
        if (bytesRecv < 1) {

            printf("\nRicevuto 0 Chiusura Thread in corso\n");
            /* close connection DB */
            mysql_free_result(res);
            mysql_close(conn);


            /* close connection Socket */
            printf("\nCLIENT DISCONNESSO\n");
            printf("Exit socketThread \n");
            close(newSocket);
            pthread_exit(NULL);

            return 0;
        }
    }
    while(bytesRecv == 0);

	
	if(sceltaStart[0]=='1') //API LOGIN
	{
		//FORMATO RICHIESTA: 1carminefb@live.it&$password
		char email[100];
		char pswd[100];
		char emailFormattata[100]; 
		char passwordFormattata[100];

		printf("EMAIL + PASSWORD : %s \n", sceltaStart);

		//RECUPERO EMAIL da SceltaStart
		char *posEmail = strchr(sceltaStart, '&');
		int len = posEmail - sceltaStart;
		strncpy(email, sceltaStart, len);
		strcpy(emailFormattata, email + 1);

		
		//Pulizia memoria stringhe
		//strcpy(email, "");

		//RECUPERO PASSWORD da SceltaStart
		int lenLogin = strlen(sceltaStart) - 1;
		char *posPassword = strchr(sceltaStart, '$');
	
		int lenPassword = (posPassword - sceltaStart) + 1;
		strcpy(passwordFormattata, posPassword + 1);

		trim(passwordFormattata);
		sprintf(query, "SELECT * FROM utente WHERE email = '%s' && password = '%s';", emailFormattata,passwordFormattata);
		//verifico credenziali di accesso 
		MYSQL_RES *result;
		MYSQL_ROW row;

		if(mysql_query(conn,query))
		{
			fprintf(stderr, "Errore nell'esecuzione della query: %s\n", mysql_error(conn));
			exit(1);
		}
		result = mysql_store_result(conn);
	
		if(mysql_num_rows(result)==0)
		{
			printf("Credenziali di accesso non valide \n");
			mysql_free_result(result);
			mysql_close(conn);
			send(newSocket,"USER_NOTFOUND",13,0);
		}
		else
		{
			printf("Accesso consentito\n");
			
			while((row=mysql_fetch_row(result)) != NULL)
			{
				 // Creazione dell'oggetto JSON
				cJSON *root = cJSON_CreateObject();
				cJSON_AddStringToObject(root, "nome", row[1]);
				cJSON_AddStringToObject(root, "cognome", row[2]);
				cJSON_AddStringToObject(root, "data_di_nascita", row[3]);
				cJSON_AddStringToObject(root, "email", row[4]);
				cJSON_AddStringToObject(root, "password", row[5]);
				char *json_str = cJSON_Print(root);

				send(newSocket, json_str, strlen(json_str), 0);
				// Liberazione della memoria dell'oggetto JSON e della stringa JSON
				cJSON_Delete(root);
				free(json_str);
			}

			mysql_free_result(result);
		}
		
		
	}
	if(sceltaStart[0]=='2') //API REGISTER
	{
		/*
		Il Client manda la sequenza: nome_cognome&data?email!password
		*/
		char *nome;
		char *cognome;
		char *data;
		char *email;
		char *password;
		
		
		//LUNGHEZZA DI TUTTO IL MESSAGGIO INVIATO
		int lenRegister = strlen(sceltaStart) - 1;

		//Recupero Nome
		nome = subString(strchr(sceltaStart, '2') + 1, strchr(sceltaStart, '2') + 1, strchr(sceltaStart, '_') + 1);

		//RECUPERO COGNOME
		cognome = subString(strchr(sceltaStart, '_') + 1, strchr(sceltaStart, '_') + 1, strchr(sceltaStart, '&') + 1);

		//RECUPERO Data
		data = subString(strchr(sceltaStart, '&') + 1, strchr(sceltaStart, '&') + 1, strchr(sceltaStart, '?') + 1);
		
		//RECUPERO Email
		email = subString(strchr(sceltaStart, '?') + 1, strchr(sceltaStart, '?') + 1, strchr(sceltaStart, '!') + 1);
		
		//RECUPERO Password
		password = subString(strchr(sceltaStart, '!') + 1, strchr(sceltaStart, '!') + 1, strchr(sceltaStart, '\0') + 1);;
		

		printf("NOME: %s \n", nome);
		printf("Cognome: %s \n", cognome);
		printf("Data: %s \n", data);
		printf("Email: %s \n", email);
		printf("Password: %s \n", password);

		char query[1000];
    	sprintf(query, "INSERT INTO utente (email, password, nome, cognome, data_nascita) VALUES ('%s', '%s', '%s', '%s', '%s');", email, password, nomeFormattato, cognome, data);

		if (mysql_query(conn, query)) 
		{
			fprintf(stderr, "Errore nell'esecuzione della query: %s\n", mysql_error(conn));
			exit(1);
		}

		free(nome);
		free(cognome);
		free(data);
		free(email);
		free(password);
    	printf("Utente registrato con successo!\n");
		

		send(newSocket,"Registration_Successful",23,0);



	}


	//CHIUDO CONNESSIONE
	mysql_close(conn); 
	//CHIUDO IL THREAD
	pthread_exit(NULL);
	
}

int main()
{
    int server_fd;
	int client_fd;
	int valread;
	struct sockaddr_in address;
	int opt=1;
	int addrlen=sizeof(address);
	char buffer[MESSAGE_SIZE]={0};
	char *hello = "Ciao client Java!";


	//creo il socket file descriptor
	if((server_fd=socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Errore nella creazione del socket");
		exit(EXIT_FAILURE);
	}
	printf("Benvenuto nel SERVER ... provo a connettermi al dabatabase in locale \n");

	//setto opzioni del socket
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("Errore nel settaggio delle opzioni del socket");
		exit(EXIT_FAILURE);
	}

	//setto indirizzo socket
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port= htons(PORT);


	//bisnd del socket
	if(bind(server_fd,(struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("Errore nel binding del socket");
		exit(EXIT_FAILURE);
	}

	
	//metto in ascolto
	if(listen(server_fd, 3) < 0)
	{
		perror("Errore nell ascolto delle connessioni in entrata");
		exit(EXIT_FAILURE);
	}

	pthread_t tid;
	int res;

	while(1)
	{
		//accetto connessione in entrata
		if((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
		{
			perror("Errore nell'accettazione della connessione in entrata");
			exit(EXIT_FAILURE);
		}
		
		
		res=pthread_create(&tid,NULL,thread_login,&client_fd);
		
		if(res)
		{
			printf("Errore creating thread: %d\n", res);
			return 1;
		}

		pthread_join(tid,NULL);
	}
	
 	close(client_fd);
	close(server_fd);
	return 0;
}
