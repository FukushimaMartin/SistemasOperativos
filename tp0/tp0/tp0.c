/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"
#include "utils.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

//primero creo e inicio el logger, luego mando un log por consola
	logger = iniciar_logger();
	//Loggear "soy un log"
	log_info(logger,"Soy un log");

//segundo creo e inicio el config, luego leo ip y puerto del .config(q tuve q crear y agregar
//la ip y el puerto), luego mando un log por consola con lo que obtuve para chequear
	config = leer_config();
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	log_info(logger,"Lei la ip %s y el puerto %s\n",ip,puerto);

//tercero voy a consola, entro a la carpeta tp0/Servidor, hago "make" y ejecuto "./Server"


	//asignar valor de config a la variable valor

	//Loggear valor de config

	//leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
	conexion = crear_conexion(ip,puerto);
	//enviar mensaje
	enviar_mensaje("Hola como estas", conexion);


	//enviar CLAVE al servirdor

	paquete(conexion);


	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	t_log* logger;

	if((logger = log_create("tp0.log","TP0",1,LOG_LEVEL_INFO)) == NULL){
		printf("no pude crear el logger\n");
		exit(1);
	}
	return logger;
}

t_config* leer_config(void)
{
	t_config* config;

	if((config = config_create("./tp0.config")) == NULL){
		printf("no pude leer la config\n");
		exit(2);
	}
	return config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");


}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete;

	leido = readline(">");
	paquete = crear_paquete();

	while(strncmp(leido, "", 1) != 0) {
			agregar_a_paquete(paquete, leido, strlen(leido) + 1);
			free(leido);
			leido = readline(">");
		}

	free(leido);

	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	if(logger != NULL){
		log_destroy(logger);
	}
	if(config != NULL){
		config_destroy(config);
	}
	liberar_conexion(conexion);

}
