/*
 ============================================================================
 Name        : primerExamen.c
 Author      : Pedro Sánchez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"
#include "utn.h"
#include "publicaciones.h"
#include "informes.h"

#define QTY_CLIENTES 100
#define QTY_PUBLICACIONES 10000
#define CANTIDAD_REINTENTOS 3
#define TRUE 1
#define FALSE 0

int main(void)
{
	setbuf(stdout,NULL);
	int opcion;

    Cliente arrayClientes[QTY_CLIENTES];
    Publicacion arrayPublicacion[QTY_PUBLICACIONES];

	if(cliente_init(arrayClientes,QTY_CLIENTES)==0 && publicacion_init(arrayPublicacion,QTY_PUBLICACIONES)==0)
	{
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"20-94728818-1","ANDRES","TORRES");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"20-78567890-2","FELIPE","CAICEDO");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"30-33567897-7","VIVIANA","HERRERA");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"20-94888818-1","GUSTAVO","ROJAS");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"30-21345654-6","JULIANA","PORTELA");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"20-94728818-1","CARLOS","FLORES");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"20-78567890-2","TOMAS","GIL");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"30-23908765-7","CAMILA","VASQUEZ");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"20-96786518-1","HERNAN","PRIETO");
		cliente_altaForzada(arrayClientes,QTY_CLIENTES,"30-21376454-6","DONOFRIO","VARGAS");

		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,4,"venta de lote",5);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,2,"venta de casa",2);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,5,"venta de bote",3);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,3,"venta de ropa",4);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,4,"venta de lote",5);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,4,"venta de auto",6);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,5,"venta de ropa",6);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,7,"venta de moto",3);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,4,"venta de ropa",6);
		publicacion_altaForzada(arrayPublicacion,QTY_PUBLICACIONES,2,"venta de zapatillas",2);

		do
		{
			if(utn_getNumeroString("\n\n  1-Alta Cliente\n  2-Modificar Cliente\n  3-Baja Cliente "
				                   "\n  4-Alta Publicacion\n  5-Pausar publicacion\n  6-Reanudar Publicacion\n  "
				             "7-Imprimir Clientes\n  8-Informar\n  9-Salir  \n  Ingrese opción:   ",
							 "ERROR Reingrese opcion valida",&opcion,CANTIDAD_REINTENTOS,1,9)==0)
			{
				switch(opcion)
				{
					case 1://Alta Cliente
						   if(cliente_createNew(arrayClientes,QTY_CLIENTES)==0)
						   {
							   printf("\n  ALTA EXITOSA\n");
						   }
						   else
						   {
							   printf("\n  NO SE REALIZO ALTA \n");
						   }
						break;
					case 2://Modificar Cliente
						if(cliente_modifify(arrayClientes,QTY_CLIENTES)==0)
						{
							printf("\n  MODIFICACION EXITOSA\n");
						}
						else
						{
							printf("\n  MODIFICACION INCORECTA\n");
						}
					break;
					case 3://Baja Cliente
					    if(info_removeClientById(arrayClientes,QTY_CLIENTES,arrayPublicacion,QTY_PUBLICACIONES)==0)
					    {
							 printf("\n  BAJA EXITOSA\n");
						}
						else
						{
							printf("\n  BAJA INCORECTA\n");
						}
					break;
					case 4://Alta Publicacion
						if(publicacion_createNewProfile(arrayPublicacion,QTY_PUBLICACIONES,arrayClientes,QTY_CLIENTES)==0)
						{
							   printf("\n  ALTA EXITOSA\n");
						}
					    else
						{
				        	   printf("\n  NO SE REALIZO ALTA \n");
					    }
					break;
					case 5://Pausar publicacion
						if(publicacion_pause(arrayPublicacion,QTY_PUBLICACIONES,arrayClientes,QTY_CLIENTES)==0)
						{
							printf("\n  PUBLICACION PAUSADA\n");
						}
						else
						{
							printf("\n  PUBLICACION NO PAUSADA, ERROR\n");
						}
					break;
					case 6://Reanudar Publicacion
						if(publicacion_reanude(arrayPublicacion,QTY_PUBLICACIONES,arrayClientes,QTY_CLIENTES)==0)
						{
							 printf("\n  PUBLICACION ACTIVA\n");
						}
						else
						{
							printf("\n  PUBLICACION NO ACTIVA, ERROR \n");
						}
					break;
					case 7://Imprimir clientes con todos sus datos
						if(info_printActive(arrayClientes,QTY_CLIENTES,arrayPublicacion,QTY_PUBLICACIONES)==0)
						{
							printf("\n  FIN DE IMFORME\n");
						}
						else
						{
							printf("\n NO HAY CLIENTES CARGADOS\n");
						}
					break;
					case 8://Informar
						if(info_report(arrayClientes,QTY_CLIENTES,arrayPublicacion,QTY_PUBLICACIONES)==0)
						{
							printf("\n  FIN DEL INFORME\n");
						}
						else
						{
							printf("\n  NO HAY DATOS CARGADOS\n");
						}
					break;
				}
			}
		}while(opcion!=9);
	}
	return EXIT_SUCCESS;
}
