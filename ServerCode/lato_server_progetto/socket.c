#include <stdio.h> //I/O operation
#include <stdlib.h> //base function for allocation memory
#include <string.h> //function for string
#include <stdbool.h> //boolean types and value
#include <time.h> //time manipulation operations
#include <sys/socket.h> //define sockaddr_structure
#include <arpa/inet.h> //for internet operation
#include <netinet/in.h> //definition of internet protocols
#include <fcntl.h> //for open
#include <pthread.h> //function for thread
#include <sys/types.h> //type for pthread
#include <unistd.h> //for close

#define PORT 8080

int main()
{
	int serverSocket; //fileDescriptor for socket
	int newSocket;
	struct sockaddr_in server_address; //STRUCT FOR SERVER ADDRESSES
	struct sockaddr_in client_address; //STRUCT FOR CLIENT ADDRESSES
	socklen_t address_size; //variable for address lenght

	char *response="Messaggio ricervuto dal server C";
	char buffer[1024]={0};

	//create socket
	serverSocket=socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1)
	{
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully created..\n");
	}

	//assign,IP, PORT
	server_address.sin_family=AF_INET; //setting for server address, family=INTERNET
	server_address.sin_port=htons(PORT); //set port number, htons function
	server_address.sin_addr.s_addr=htonl(INADDR_ANY); //set IP address to localhost

	memset(server_address.sin_zero, '\0', sizeof server_address.sin_zero); //set all bits of the padding field to 0

	//binding the address struct to the socket
	bind(serverSocket, (struct sockaddr *) &server_address, sizeof(server_address));

	if(listen(serverSocket,100)==0)
	{
		printf("Server linstening \n");
	}
	else
	{
		printf("Failed \n");
	}

	//Accept the data packet from client and verification
	newSocket=accept(serverSocket, (struct sockaddr *) &client_address, (socklen_t *) &address_size);
	if(newSocket <0)
	{
		printf("Server accept failed...\n");
		exit(0);
	}
	else
	{
		printf("Server accept the client...\n");
		printf("IP ADDRESS is: %s\n", inet_ntoa(client_address.sin_addr));
		printf("Port is: %d\n", (int)ntohs(client_address.sin_port));
	}

	int valread = read (newSocket,buffer,1024);;
	printf("Msg from client: %s\n", buffer);

	send(newSocket, response,strlen(response),0);
	printf("Reply sent to client : %s\n", response);

	//function(serverSocket);

	//after opertaion, close socket
	close(serverSocket);

}
