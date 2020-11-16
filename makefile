all: Cliente
Cliente: Modulo-Cliente/src/Modulo-Cliente.c Conexion-Serializacion/utils.c Conexion-Serializacion/serializacion.c Modulo-Cliente/src/estructuras_cliente.c
	gcc Modulo-Cliente/src/Modulo-Cliente.c Conexion-Serializacion/utils.c Conexion-Serializacion/serializacion.c Modulo-Cliente/src/estructuras_cliente.c -o Cliente -lcommons -lpthread
