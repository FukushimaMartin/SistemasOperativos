/*
 ============================================================================
 Name        : socket-uno.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : 1- abre conexión
 	 	 	 2- acepta conexión, reutiliza conexión, envio msj
 	 	 	 3- recibir mensaje
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
	struct sockaddr_in direcciónServidor;
	direcciónServidor.sin_family = AF_INET;
	direcciónServidor.sin_addr.s_addr = INADDR_ANY;
	direcciónServidor.sin_port = htons(8080);
	
	int servidor = socket(AF_INET,SOCK_STREAM,0);
	
	//segunda parte del tuto sockets
	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado,sizeof(activado));
/*esto permite que si cerras abruptamente el socket (ej con ctrl+c)
no cuelgue y te permita reabrirlo y reutilizarlo
con "close" lo cerras correctamente*/
	//segunda parte del tuto sockets - fin

	if(bind(servidor, (void*) &direcciónServidor, sizeof(direcciónServidor)) != 0){
		perror("Fallo el bind");
		return 1;
	}
	printf("Estoy escuchando\n");
	listen(servidor, 100);

	//segunda parte del tuto sockets
	struct sockaddr_in direcciónCliente;
	unsigned int tamañoDirección;
	int cliente = accept(servidor,  (void*) &direcciónCliente, tamañoDirección);

	printf("Recibi una conexión en &d!!\n",cliente);

	send(cliente, "hola, gato",11,0);//11 es el tamaño del mensaje +1
	send(cliente, ":)",3,0);
	//segunda parte del tuto sockets - fin

	//tercera parte del tuto sockets
	char* buffer = malloc(5);
	int bytesRecibidos = recv(cliente, buffer,4,0);//4 bytes max
	if (bytesRecibidos < 0){
		perror("El chabon se desconecto o bla.");
		return 1;
	}
	buffer[bytesRecibidos] = '\0';
	printf("Me llegaron %d bytes con %s", bytesRecibidos, buffer);

	free(buffer);
/*el ultimo campo en recv o send (0) corresponde al flag,
yo puedo poner MSG_WAITALL, que espera a recibir los bytes
que le estoy pidiendo, o sea 4. (1 caracter y enter, son 2 bytes)
la forma de saber el tamaño q recibimos es:

uint32_t tamañoPaquete;
recv(cliente,&tamañoPaquete,4,0);
char* buffer = malloc(tamañoPaquete);
recv(cliente,buffer,tamañoPaquete,MSG_WAITALL);
*/
	//tercera parte del tuto sockets - fin

	for(;;);
	return 0;
}
