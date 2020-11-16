#include "Serializacion.h"
#include "Utils.h"
#include "Modulo-Comanda.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

	logger = log_create("Comanda.log", "Comanda", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	int cliente_fd = esperar_cliente(server_fd);

	t_list* lista;
	while(1)
	{
		int cod_op = recibir_operacion(cliente_fd);


		switch(cod_op)
		{
		case GUARDAR_PEDIDO:;
		    pthread_t hilo;
			t_guardar_pedido* pedido;
			pedido = recibir_guardar_pedido(cliente_fd);
			pthread_create(&hilo, NULL, GuardarPedido_Comanda, &pedido);
			pthread_join(hilo, NULL);
			break;
		case OBTENER_PEDIDO:;
		    pthread_t hilo;
			t_obtener_pedido* pedido;
			pedido = recibir_obtener_pedido(cliente_fd);
			pthread_create(&hilo, NULL, ObtenerPedido_Comanda, &pedido);
			pthread_join(hilo, NULL);
			break;
		case CONFIRMAR_PEDIDO:;
		    pthread_t hilo;
			t_confirmar_pedido* pedido;
			pedido = recibir_confirmar_pedido(cliente_fd);
			pthread_create(&hilo, NULL, ConfirmarPedido_Comanda, &pedido);
			pthread_join(hilo, NULL);
			break;
		case FINALIZAR_PEDIDO:;
		    pthread_t hilo;
			t_finalizar_pedido* pedido;
			pedido = recibir_finalizar_pedido(cliente_fd);
			pthread_create(&hilo, NULL, FinalizarPedido_Comanda, &pedido);
			pthread_join(hilo, NULL);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger, "Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;

}


void* GuardarPedido_Comanda(void* pedido) {
    char* NombreDeRes;
	int IdPedido;
	char* estado;

	NombreDeRes = pedido->nombre;
	IdPedido = pedido->id_pedido;

	if (verificaRestaurante(NombreDeRes, IdPedido)) /* Esta función debe verificar o crear la tabla de segmentos del restaurante.
	                                                   Luego también la tabla de páginas asociada  */
		return "Pedido guardado correctamente";

	return "No se pudo guardar el pedido";
}

void* ObtenerPedido_Comanda(void* pedido) {
    char* NombreDeRes;
	int IdPedido;
	char* estado;

	NombreDeRes = pedido->nombre;
	IdPedido = pedido->id_pedido;

	if (existeRestaurante(NombreDeRes)) {

		if (existePedido(NombreDeRes, IdPedido))
			return obtenerDatosPedido(NombreDeRes, IdPedido);

		return "No existe el pedido indicado.";
	}

	return "No existe el restaurante indicado.";
}

void* ConfirmarPedido_Comanda(void* buf) {
    char* NombreDeRes;
	int IdPedido;
	char* estado;

	NombreDeRes = pedido->nombre;
	IdPedido = pedido->id_pedido;

	if (existeRestaurante(NombreDeRes)) {

		if (existePedido(NombreDeRes, IdPedido)) {

			if(obtenerEstadoPedido(NombreDeRes, IdPedido) == "PENDIENTE") {
				estado = actualizarEstadoPedido(NombreDeRes, IdPedido, "CONFIRMADO");

				return estado;
			}

			return "El pedido no se encuentra en estado \'Pendiente\'.";
		}

		return "No existe el pedido indicado.";
	}

	return "No existe el restaurante indicado.";
}

void* FinalizarPedido_Comanda(void* buf) {
    char* NombreDeRes;
	int IdPedido;
	char* estado;

	NombreDeRes = pedido->nombre;
	IdPedido = pedido->id_pedido;

	if (existeRestaurante(NombreDeRes)) {

		if (existePedido(NombreDeRes, IdPedido)) {

			estado = eliminarPlatosyPedido(NombreDeRes, IdPedido);

			return estado;
		}
	    else {
		    return "No existe el pedido indicado";
		}
	}

	return "No existe el restaurante indicado";
}

char* verificaRestaurante(char* NombreDeRes, int IdPedido) {
/*
------FALTA DESARROLLO------
*/
}

char* existeRestaurante(char* NombreDeRes){
/*
------FALTA DESARROLLO------
*/
}

char* existePedido(char* NombreDeRes, int IdPedido){
/*
------FALTA DESARROLLO------
*/
}

char* obtenerDatosPedido(char* NombreDeRes, int IdPedido){
/*
------FALTA DESARROLLO------
*/
}

char* obtenerEstadoPedido(char* NombreDeRes, int IdPedido){
/*
------FALTA DESARROLLO------
*/
}

char* actualizarEstadoPedido(char* NombreDeRes, int IdPedido, char* ESTADO){
/*
------FALTA DESARROLLO------
*/
}

char* eliminarPlatosyPedido(char* NombreDeRes, int IdPedido){
/*
------FALTA DESARROLLO------
*/
}
NEW COMANDA.txt
Mostrando NEW COMANDA.txt.
