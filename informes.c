/*
 * informes.c
 *
 *  Created on: 20 oct. 2020
 *      Author: pedro_000
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "informes.h"

#define TRUE 1
#define FALSE 0
#define MIN_ID 0
#define MAX_ID 9999
#define CANTIDAD_REINTENTOS 3

/**
 * \brief info_printAdsByClientID: Function to print each ad that a client has (searched by ID).
 * \param Cliente *listUno: Pointer to  array.
 * \param int lenUno: Length of the array
 * \param Publicacion *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \param int id: receive the ID to be search.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int info_printAdsByClientID(Cliente *listUno, int lenUno, Publicacion *listDos, int lenDos, int id)
{
	int retorno=-1;
	int clientIndex;
	int publiIndex;
	char strEstado[8];
	if(listUno!=NULL && lenUno>0 && listDos!=NULL && lenDos>0 && id>0)
	{
		if(cliente_findById(listUno, lenUno,&clientIndex ,id)==0)
		{
			printf("\n  ID cliente: %d - Nombre: %s - Apellido: %s - CUIT: %s", listUno[clientIndex].idCliente, listUno[clientIndex].nombre, listUno[clientIndex].apellido, listUno[clientIndex].cuit);
			if(publicacion_findByIdpcliente(listDos,lenDos,listUno,lenUno,id,&publiIndex)==0)
					//publicacion_findByClientId(adList, adLen, clientList[clientIndex].idCliente)==0)
			{
				for(int i=0;i<lenDos;i++)
				{
					if(listDos[i].idCliente==listUno[clientIndex].idCliente)
					{
						if (listDos[i].isActive == TRUE)
						{
							strncpy(strEstado,"ACTIVA",8);
						}
						else
						{
							strncpy(strEstado,"PAUSADA",8);
						}
						printf("\n   ID publicacion: %d -Estado: %s -Texto: %s  -Rubro: %d",listDos[i].id,strEstado,listDos[i].texto,listDos[i].rubro);
					}
				}
			}
			else
			{
				printf(" NO TIENE ANUNCIOS");
			}
			retorno=0;
		}
		else
		{
			printf("\n  CLIENTE NO ENCONTRADO VERIFIQUE ID");
		}
	}
	return retorno;
}
/**
 * \brief  _removeClientById :Function delete all the data associated to a client searched by ID (put isEmpty field on TRUE).
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array
 * \param Client *listDos: Pointer to array.
 * \param int lenDos: Client array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int info_removeClientById(Cliente* list,int len,Publicacion* listDos,int lenDos)
{
	int retorno = -1;
	int idBaja;
	int option;
	int indexBuscar;

	if(list != NULL && len>0)
	{
		if(!utn_getNumeroString("\n\n  Ingrese ID de cliente a eliminar:","  Error Reingrese ID de cliente a eliminar!",&idBaja,CANTIDAD_REINTENTOS,MIN_ID,MAX_ID) &&
						!info_printAdsByClientID(list,len,listDos,lenDos,idBaja) && cliente_findById(list,len,&indexBuscar,idBaja)==0)
		{
			if(utn_getNumeroString("\n\n  Quiere eliminar este cliente y todas sus publicaciones? (1-SI O 2-NO): ","\n  ERROR Reingrese opcion correcta", &option,CANTIDAD_REINTENTOS, 1, 2)==0 && option == 1)
		    {
				for(int i=0;i<lenDos-1;i++)
				{
					if(listDos[i].isEmpty == FALSE && listDos[i].idCliente==idBaja )
					{
						listDos[i].isEmpty = TRUE;
						listDos[i].isActive = -1;
						retorno = 0;
					}
				}
				if(list[indexBuscar].isEmpty == FALSE)
				{
					//BAJA LOGICA DE ID
					list[indexBuscar].isEmpty = TRUE;
					retorno = 0;
				}
		    }
			else
			{
				printf("\n  OPCION INCORRECTA REINTENTE \n");
			}
		}
		else
		{
			printf("\n  ID NO ENCONTRADO VERIFIQUE \n");
		}
	}
	return retorno;
}

/**
 * \brief _printActive :Function to print clients and how many active ads has.
 * \param Client *listUno: Pointer array.
 * \param int lenUno: Length of the array.
 * \param Advertisement *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int info_printActive(Cliente *listUno, int lenUno, Publicacion *listDos, int lenDos)
{
	int retornar = -1;
	int adCounter;
	if(listUno!=NULL && lenUno>0 && listDos!=NULL && lenDos>0)
	{
		for(int i=0;i<lenUno;i++)
		{
			if(listUno[i].isEmpty == FALSE && publicacion_counterActivePublicationClient(listDos,lenDos,listUno[i].idCliente, &adCounter)==0 && adCounter>0)
			{
				printf("\n  ID Cliente: %d - Nombre: %s - Apellido: %s - CUIT: %s - Cantidad de anuncios activos: %d", listUno[i].idCliente,listUno[i].nombre,listUno[i].apellido,listUno[i].cuit, adCounter);
				retornar=0;
			}
		}
	}
	return retornar;
}
/**
 * \brief Function to report the client with more ads, how many paused ads are and the rubro number with more ads
 * \param Client *listUno: Pointer to array.
 * \param int lenUno: Length of the array.
 * \param Publicacion *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int info_report(Cliente *listUno, int lenUno, Publicacion *listDos, int lenDos)
{
	int retornar = -1;
	int option;
	int adsCounter;
	if(listUno!=NULL && lenUno>0 && listDos!=NULL && lenDos>0  && publicacion_searchForNoEmpty(listDos,lenDos)==0)
	{
		do
		{
			if(utn_getNumeroString("\n\n  1-Cliente con mas avisos\n  2-Cantidad de avisos pausados\n  3-Rubro con mas avisos\n  4-Cliente con mas avisos activos\n  5-Cliente con mas avisos pausados\n  6-Salir \n  Opcion:", "\n  ERROR! Reingrese opcion valida", &option,CANTIDAD_REINTENTOS,1,6)==0)
			{
				switch(option)
				{
					case 1:
						if(informe_imprimirClienteMayorCantidadAvisos(listDos,lenDos,listUno,lenUno)==0)
						{
							retornar=0;
						}
					break;
					case 2:
						if(publicacion_counterPaused(listDos,lenDos,&adsCounter)==0)
						{
							printf("\n  Cantidad de avisos pausados: %d\n",adsCounter);
							retornar=0;
						}
						else
						{
							printf("\n  NO HAY AVISOS PAUSADOS\n");
						}
					break;
					case 3:
						if(publicacion_rubroMax(listDos,lenDos)==0)
						{
							retornar=0;
						}
					break;
				    case 4:
				    	if(informe_imprimirClienteMayorCantidadAvisosActivos(listDos,lenDos,listUno,lenUno)==0)
				    	{
				    		retornar=0;
				    	}
					break;
				    case 5:
				    	if(informe_imprimirClienteMayorCantidadAvisosPausados(listDos,lenDos,listUno,lenUno)==0)
				    	{
				    		retornar=0;
				    	}
					break;
				}
			}
		}while(option != 6);
	}
	return retornar;
}
/**
 * \brief _imprimirClienteMayorCantidadAvisos: Function to find the client with more ads.
 * \param Publicacion* listUno: Pointer to  array.
 * \param int lenUno: Length of the array.
 * \param Cliente *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int informe_imprimirClienteMayorCantidadAvisos(Publicacion* listUno,int lenUno,Cliente* listDos,int lenDos)
{
	int retorno=-1;
	int indice;
	int cantidadAvisos;
	int maximoAvisos;
	int idMaximoAvisos;
	int auxIndiceCliente;

	if(listUno!=NULL && lenUno>0 && listDos!=NULL && lenDos>0)
	{
		for(indice=0;indice<lenDos;indice++)
		{
			if(publicacion_cantidadAvisos(listUno,lenUno,listUno[indice].idCliente,&cantidadAvisos)==0)
			{
				if(indice==0 || cantidadAvisos>maximoAvisos)
				{
					maximoAvisos=cantidadAvisos;
					idMaximoAvisos=listUno[indice].idCliente;
					retorno=0;
				}
			}
		}
		if(retorno==0 && maximoAvisos>0)
		{
			cliente_findById(listDos,lenDos,&auxIndiceCliente,idMaximoAvisos);
			cliente_printById(listDos,lenDos,auxIndiceCliente);
			printf("\n    Es el cliente con mas avisos, la cantidad de avisos publicados es: %d\n",maximoAvisos);
		}
		else
		{
			printf("\n  NO HAY AVISOS CARGADOS\n");
		}
	}
	return retorno;
}
/**
 * \brief _imprimirClienteMayorCantidadAvisosActivos: Function to find the client with more active ads.
 * \param Publicacion* listUno: Pointer to  array.
 * \param int lenUno: Length of the array.
 * \param Cliente *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int informe_imprimirClienteMayorCantidadAvisosActivos(Publicacion* listUno,int lenUno,Cliente* listDos,int lenDos)
{
	int retorno=-1;
	int indice;
	int cantidadAvisos;
	int maximoAvisos;
	int idMaximoAvisos;
	int auxIndiceCliente;

	if(listUno!=NULL && lenUno>0 && listDos!=NULL && lenDos>0)
	{
		for(indice=0;indice<lenDos;indice++)
		{
			if(publicacion_counterActivePublicationClient(listUno,lenUno,listUno[indice].idCliente,&cantidadAvisos)==0)
			{
				if(indice==0 || maximoAvisos<cantidadAvisos)
				{
					maximoAvisos=cantidadAvisos;
					idMaximoAvisos=listUno[indice].idCliente;
					retorno=0;
				}
			}
		}
		if(retorno==0 && maximoAvisos>0)
		{
			cliente_findById(listDos,lenDos,&auxIndiceCliente,idMaximoAvisos);
			cliente_printById(listDos,lenDos,auxIndiceCliente);
			printf("\n    Es el cliente con mas avisos activos, la cantidad de avisos es: %d\n",maximoAvisos);
		}
		else
		{
			printf("\n  NO HAY AVISOS ACTIVOS\n");
		}
	}
	return retorno;
}
/**
 * \brief _imprimirClienteMayorCantidadAvisosPausados: Function to find the client with more paused ads.
 * \param Publicacion* listUno: Pointer to  array.
 * \param int lenUno: Length of the array.
 * \param Cliente *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int informe_imprimirClienteMayorCantidadAvisosPausados(Publicacion* listUno,int lenUno,Cliente* listDos,int lenDos)
{
	int retorno=-1;
	int indice;
	int cantidadAvisos;
	int maximoAvisos;
	int idMaximoAvisos;
	int auxIndiceCliente;

	if(listUno!=NULL && lenUno>0 && listDos!=NULL && lenDos>0)
	{
		for(indice=0;indice<lenDos;indice++)
		{
			if(publicacion_counterPausedPublicationClient(listUno,lenUno,listUno[indice].idCliente,&cantidadAvisos)==0)
			{
				if(indice==0 || maximoAvisos<cantidadAvisos)
				{
					maximoAvisos=cantidadAvisos;
					idMaximoAvisos=listUno[indice].idCliente;
					retorno=0;
				}
			}
		}
		if(retorno==0 && maximoAvisos>0)
		{
		    cliente_findById(listDos,lenDos,&auxIndiceCliente,idMaximoAvisos);
			cliente_printById(listDos,lenDos,auxIndiceCliente);
			printf("\n    Es el cliente con mas avisos pausados, la cantidad de avisos es: %d\n",maximoAvisos);
		}
		else
		{
			printf("\n  NO HAY AVISOS PAUSADOS\n");
		}
	}
	return retorno;
}
