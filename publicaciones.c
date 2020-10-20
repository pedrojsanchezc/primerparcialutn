/*
 * publicaciones.c
 *
 *  Created on: 20 oct. 2020
 *      Author: pedro_000
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#include "publicaciones.h"
#include "cliente.h"
#include "informes.h"
#include "utn.h"

#define TRUE 1
#define FALSE 0
#define MIN_RUBRO 1
#define MAX_RUBRO 10
#define MIN_ID 0
#define MAX_ID 9999
#define CANTIDAD_REINTENTOS 3

static int newIdGenerate(void);

/**
 * \brief _init: To indicate that all position in the array are empty,
*                this function put the flag (isEmpty) in TRUE in all
*                position of the array.
* \param (Publicacion)* list: Pointer to the array.
* \param int len:  Length of the array.
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int publicacion_init(Publicacion* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = TRUE;
			list[i].isActive=-1;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief _searchEmpty: Search in the array for the first index with TRUE in isEmpty.
 * \param (Publicacion)* list: Pointer to the array.
 * \param int len: Length of the array.
 * \param int *pIndex: Pointer to position of first empty index.
 * \return (-1) Error / (0) Ok
 */
int publicacion_searchEmpty(Publicacion* list, int len, int *pIndex)
{
	int retornar = -1;
	if(list != NULL && pIndex != NULL && len>0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}
/* \brief newIdGenerate: Create a new id when the user load data (different id).
 *  \return id.
 */
static int newIdGenerate(void)
{
	static int id=0; // es global para solo la fn puede usarla

	//guarda el ultimo que asigne (ultimo que devolvi)
	//para devolver 1+
	id = id+1;
	return id;
}
/**
 * \brief _findById: find position in the array  by Id.
 * \param (Publicacion)* list: Pointer to the array.
 * \param int len: Length of the array.
 * \param int *pIndex: Pointer to the memory  where write the value.
 * \param int id: Assigned id.
 * \return (-1) Error / (0) Ok
 */
int publicacion_findById(Publicacion* list, int len, int* pIndex, int id)
{
    int retorno = -1;
    //*pIndex = -1;
    if (list != NULL && len > 0)
    {
        for (int i = 0; i < len; i++)
        {
            if(list[i].isEmpty == FALSE && (list[i].isActive==TRUE || list[i].isActive==FALSE))
            {
                if(list[i].id == id)
                {
                   *pIndex = i;
                   retorno = 0;
                    break;
                }
            }
        }
    }
    return retorno;
}
/**
 * \brief _createNewProfile: Create a new profile asking data to the user.
 * \param (Publicacion) * listUno: Pointer to the array.
 * \param int lenUno: Length of the array.
 * \param (Cliente) * lisDos: Pointer to the array.
 * \param int lenDos: Length of the array.
 * \return (-1) Error / (0) Ok
 */
int publicacion_createNewProfile(Publicacion * listUno, int lenUno,Cliente* listDos,int lenDos)
{
	int retorno = -1;
	int indice;
	Publicacion buffer;
	int clientIndex;
	if (listUno != NULL && lenUno >0 && listDos !=NULL && lenDos>0)
	{
		if (publicacion_searchEmpty(listUno,lenUno,&indice) == 0 && indice>=0 && cliente_printAll(listDos,lenDos)==0)
		{
			if (utn_getNumeroString("\n  Id de cliente: ","\n  Error no es un numero valido",&buffer.idCliente,CANTIDAD_REINTENTOS,MIN_ID,MAX_ID)==0 &&
			    cliente_findById(listDos,lenDos,&clientIndex,buffer.idCliente)==0 &&
				utn_getNumeroString("\n  Ingrese el numero de rubro: ", "\nERROR! Ingrese un numero de rubro valido: ",&buffer.rubro, CANTIDAD_REINTENTOS, MIN_RUBRO, MAX_RUBRO)==0 &&
			    utn_getAlfanumerico("\n  Ingrese el texto del aviso: ", "\nERROR! Ingrese caracteres validos: ",buffer.texto,CANTIDAD_REINTENTOS, SIZE_TEXT)==0)
			{
					buffer.id= newIdGenerate();
					buffer.isActive = TRUE;
					listUno[indice].isEmpty = FALSE;
					listUno[indice] = buffer;
					printf("\n  ID para el nuevo aviso: %d", listUno[indice].id);
					retorno=0;
			}
			else
			{
					printf("\n  ID DE CLIENTE NO ENCONTRADO");
			}
		}
		else
		{
			printf("\n  NO QUEDAN ESPACIOS LIBRES");
		}
	}
	return retorno ;
}
/**
 * \brief  _pause :Function pause a publication searched by ID (put isActive field on FALSE)
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array.
 * \param Cliente *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int publicacion_pause(Publicacion* list,int len,Cliente* listDos,int lenDos)
{
	int retorno = -1;
	int idPausa;
	int index;
	int option;

	if(list != NULL && len>0 && listDos != NULL && lenDos>0 && publicacion_printActive(list, len)==0)
	{
		if(!utn_getNumeroString("\n\n  Ingrese id de publicacion a pausar:","  Error Reingrese id publicacion!",&idPausa,CANTIDAD_REINTENTOS, MIN_ID,MAX_ID) &&
						!publicacion_findById(list,len,&index,idPausa) && list[index].isActive==TRUE && !publicacion_printClientById(list,len,listDos,lenDos,idPausa))
		{
			if(utn_getNumeroString("\n\n  Quiere pausar esta publicidad? (1-SI O 2-NO): " ,"\n  ERROR ", &option,CANTIDAD_REINTENTOS, 1, 2)==0 && option == 1)
		    {
					if(list[index].isActive == TRUE)
					{
						//BAJA LOGICA DE ID
						list[index].isActive = FALSE;
						retorno = 0;
					}
			}
			else
			{
				printf("\n  PUBLICIDAD NO PAUSADA \n");
			}

		}
		else
		{
			printf("\n  ID NO ENCONTRADO VERIFIQUE \n");
		}
	}
	else
	{
		printf("\n  NO EXISTE PUBLICACIONES ACTIVAS \n");
	}
	return retorno;
}
/**
 * \brief  _pause :Function reanude a publication searched by ID (put isActive field on TRUE)
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array
 * \param Cliente *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int publicacion_reanude(Publicacion* list,int len,Cliente* listDos,int lenDos)
{
	int retorno = -1;
	int idPausa;
	int index;
	int option;

	if(list != NULL && len>0 && listDos != NULL && lenDos>0 && publicacion_printPause(list, len)==0)
	{
		if(!utn_getNumeroString("\n\n  Ingrese id de publicacion a reanudar:","  Error Reingrese id publicacion!",&idPausa,CANTIDAD_REINTENTOS, MIN_ID,MAX_ID) &&
		   !publicacion_findById(list,len,&index,idPausa)&& list[index].isActive==FALSE && !publicacion_printClientById(list,len,listDos,lenDos,idPausa))
		{
			if(utn_getNumeroString("\n\n  Quiere reanudar esta publicidad? (1-SI O 2-NO): ","\n  ERROR\n ", &option,CANTIDAD_REINTENTOS,1,2)==0 && option == 1 )
		    {
					if(list[index].isActive == FALSE)
					{
						list[index].isActive = TRUE;
						retorno = 0;
					}
			}
			else
			{
				printf("\n  PUBLICIDAD NO REANUDADA \n");
			}
		}
		else
		{
			printf("\n  ID NO ENCONTRADO VERIFIQUE \n");
		}
	}
	else
	{
		printf("\n  NO EXISTE PUBLICACIONES PAUSADAS \n");
	}
	return retorno;
}
/**
 * \brief _printClientById: Function to print info searched by ID.
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array
 * \param Cliente *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \param int id: receive the ID to be search.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int publicacion_printClientById(Publicacion *list, int len, Cliente *listDos, int lenDos, int id)
{
	int retorno=-1;
	int index;
	int auxIdCliente;
	if(list!=NULL && len>0 && listDos!=NULL && lenDos>0 && id>0 &&
		publicacion_findByIdpcliente(list,len,listDos,lenDos,id,&auxIdCliente)==0 &&
		cliente_findById(listDos, len,&index,auxIdCliente)==0)
	{
		printf("\n  Cliente:\n  -IDC: %d  -Nombre: %s - Apellido: %s - Cuit: %s"
			   ,listDos[index].idCliente,listDos[index].nombre,listDos[index].apellido,listDos[index].cuit);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief _findByIdpcliente: find idCliente position in the array  by Id.
 * \param (Publicacion)* list: Pointer to the array.
 * \param int len: Length of the array.
 * \param Cliente *listDos: Pointer to array.
 * \param int lenDos: Length of the array.
 * \param int id: Assigned id.
 * \param int *pIdCliente: Pointer to the memory  where write the value.
 * \return (-1) Error / (0) Ok
 */
int publicacion_findByIdpcliente(Publicacion* list, int len, Cliente *listDos, int lenDos, int id, int* pIdCliente)
{
	int retorno = -1;
	int i;
	if(list!=NULL && len>0 && listDos!=NULL && lenDos>0 && id>0 && pIdCliente !=NULL)
	{
		for(i=0;i<len; i++)
		{
			if(list[i].isEmpty==FALSE && list[i].id == id && (list[i].isActive==TRUE || list[i].isActive==FALSE))
			{
				*pIdCliente = list[i].idCliente;
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief _printAll :Function to print the array.
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int publicacion_printAll(Publicacion *list, int len)
{
	int retorno = -1;
	char strEstado[8];
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && (list[i].isActive==TRUE || list[i].isActive==FALSE))
			{
				if (list[i].isActive == TRUE)
				{
					strncpy(strEstado,"ACTIVA",8);
				}
				else
				{
					strncpy(strEstado,"PAUSADA",8);
				}
				printf("\n  -IDP: %d -Estado: %s -Texto: %s -Rubro: %d -IDC: %d",list[i].id,strEstado,list[i].texto,list[i].rubro,list[i].idCliente);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief _printActive: Function to print Active in the array.
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK
**/
int publicacion_printActive(Publicacion *list, int len)
{
	int retorno = -1;
	char strEstado[8];
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].isActive==TRUE )
			{
				if (list[i].isActive == TRUE)
				{
					strncpy(strEstado,"ACTIVA",8);
				}
				printf("\n  -IDP: %d -Estado: %s -Texto: %s -Rubro: %d -IDC: %d",list[i].id,strEstado,list[i].texto,list[i].rubro,list[i].idCliente);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief _printPause: Function to print Paused in the array.
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array.
 * \return (-1) if something went wrong, (0) if everything is OK
 **/
int publicacion_printPause(Publicacion *list, int len)
{
	int retorno = -1;
	char strEstado[8];
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].isActive==FALSE )
			{
				if (list[i].isActive == FALSE)
				{
					strncpy(strEstado,"PAUSADA",8);
				}
				printf("\n  -IDP: %d -Estado: %s -Texto: %s -Rubro: %d -IDC: %d",list[i].id,strEstado,list[i].texto,list[i].rubro,list[i].idCliente);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief _cantidadAvisos: Function to count how many ads has a client searched by ID
 * \param Publicacion *list: Pointer to an array.
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \param int *pResultado: Pointer to the memory  where write the value.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int publicacion_cantidadAvisos(Publicacion* list,int len,int id,int *pResultado)
{
	int retorno=-1;
	int indice;
	int contadorAvisos=0;

	if(list!=NULL && len>0 && id>0 && pResultado!=NULL)
	{
		for(indice=0;indice<len;indice++)
		{
			if(list[indice].isEmpty==FALSE && list[indice].idCliente==id && (list[indice].isActive==TRUE || list[indice].isActive==FALSE))
			{
				contadorAvisos++;
				retorno=0;
			}
		}
	}
	*pResultado=contadorAvisos;
	return retorno;
}
/**
 * \brief _counterActivePublicationClient: Function to count how many active ads has a client searched by ID
 * \param Publicacion *list: Pointer to the array.
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \param int *pCounter: Pointer to the memory  where write the value.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int publicacion_counterActivePublicationClient(Publicacion *list, int len, int id, int *pCounter)
{
	int retorno=-1;
	int counter=0;
	if(list!=NULL && len>0 && id>0 && pCounter!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].idCliente == id && list[i].isActive == TRUE && list[i].isEmpty==FALSE )
			{
				counter++;
			}
		}
		*pCounter = counter;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief _counterPausedPublicationClient: Function to count how many paused ads has a client searched by ID
 * \param Publicacion *list: Pointer to the array.
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \param int *pCounter: Pointer to the memory  where write the value.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int publicacion_counterPausedPublicationClient(Publicacion *list, int len, int id, int *pCounter)
{
	int retorno=-1;
	int counter=0;
	if(list!=NULL && len>0 && id>0 && pCounter!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].idCliente == id && list[i].isActive == FALSE && list[i].isEmpty==FALSE )
			{
				counter++;
			}
		}
		*pCounter = counter;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief _counterPaused: Function to count how many paused ads have the array.
 * \param Publicacion *list: Pointer to  array.
 * \param int len: Length of the array
 * \param int *pCounter: Pointer to the memory  where write the value.
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int publicacion_counterPaused(Publicacion *list, int len, int *pCounter)
{
	int retorno=-1;
	int counter=0;
	if(list!=NULL && len>0 && pCounter!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isActive == FALSE && list[i].isEmpty==FALSE)
			{
				counter++;
				retorno=0;
			}
		}
		*pCounter = counter;
	}
	return retorno;
}
/**
 * \brief _searchForNoEmpty: Function to search in the publicacion array for no empty field.
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int publicacion_searchForNoEmpty(Publicacion *list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief _searchForActive: Function to search in the publicacion array if there's any active
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array
 * \return (1) is there any active field TRUE or (0) if not
 */
int publicacion_searchForActive(Publicacion *list, int len)
{
	int retorno = 0;
	if(list != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isActive == TRUE)
			{
				retorno = 1;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief _findByClientId: Function to find an Publicacion index receiving a client ID.
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array.
 * \param int id: receive the id to be searched.
 * \return the index or (-1) if something went wrong.
 */
int publicacion_findByClientId(Publicacion *list, int len, int id)
{
	int retorno = -1;
	if(list != NULL && len > 0 && id > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].idCliente==id && list[i].isEmpty==FALSE && (list[i].isActive==TRUE || list[i].isActive==FALSE))
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief _rubroMax: Function to compare rubro counter and find the max.
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array
 * \return the index or (-1) if something went wrong
 */
int publicacion_rubroMax(Publicacion *list, int len)
{
	int retorno=-1;
	int currentCounter;
	int maxCounter;
	Publicacion bufferAux;
	if(list!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && publicacion_equalRubro(list,len,list[i].rubro, &currentCounter)==0)
			{
				if(i==0 || currentCounter>maxCounter)
				{
					maxCounter = currentCounter;
					bufferAux = list[i];
					retorno=0;
				}
			}
		}
		printf("\n  El rubro con mas avisos es el: %d y tiene %d avisos.\n",bufferAux.rubro,maxCounter);
	}
	return retorno;
}
/**
 * \brief _equalRubro: Function to count how many times a sector is repeated in the array.
 * \param Publicacion *list: Pointer to array.
 * \param int len: Length of the array
 * \param int sector: receive the sector to be searched
 * \param int *pCounter: Pointer to the memory  where write the value.
 * \return the index or (-1) if something went wrong
 */
int publicacion_equalRubro(Publicacion *list, int len, int rubro, int *pCounter)
{
	int retorno=-1;
	int counter=0;
	if(list!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].rubro == rubro && (list[i].isActive==TRUE || list[i].isActive==FALSE))
			{
				counter++;
				retorno=0;
			}
		}
		*pCounter = counter;
	}
	return retorno;
}
/**
 * \brief_altaForzada: Automatically creates a new profile .
 * \param Publicacion * list: Pointer to the array.
 * \param int len: Array length.
 * \param int idCliente: Id assigned.
 * \param char* texto: text of the publication.
 * \param int rubro: Rubro of the publication.
 * \return (-1) Error / (0) Ok
 */
int publicacion_altaForzada(Publicacion* list, int len,int idCliente,char* texto,int rubro)
{
	int retorno = -1;
	int indice;
	Publicacion buffer;
	if (list != NULL && len >0)
	{
		if(publicacion_searchEmpty(list,len,&indice) == 0)
		{
			buffer.id= newIdGenerate();
			buffer.idCliente= idCliente;
			strncpy(buffer.texto,texto,SIZE_TEXT);
			buffer.rubro= rubro;
			list[indice] = buffer;
			list[indice].isEmpty = FALSE;
			list[indice].isActive =TRUE ;
			retorno=0;
	    }
	}
	return retorno ;
}
