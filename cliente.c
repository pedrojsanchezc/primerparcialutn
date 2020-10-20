/*
 * cliente.c
 *
 *  Created on: 20 oct. 2020
 *      Author: pedro_000
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "cliente.h"

#define TRUE 1
#define FALSE 0
#define CANTIDAD_REINTENTOS 3
#define MIN_ID 0
#define MAX_ID 9999

static int newIdGenerate(void);

/**
 * \brief _init: To indicate that all position in the array are empty,
*                this function put the flag (isEmpty) in TRUE in all
*                position of the array.
* \param (Cliente)* list: Pointer to the array.
* \param int len:  Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int cliente_init(Cliente* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief _searchEmpty: Search in the array for the first index with TRUE in isEmpty.
 * \param (Cliente)* list: Pointer to the array.
 * \param int len: Array length.
 * \param int *pIndex: Pointer to position of first empty index.
 * \return (-1) Error / (0) Ok
 */
int cliente_searchEmpty(Cliente* list, int len, int *pIndex)
{
	int retorno = -1;
	if(list != NULL && pIndex != NULL && len>0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/* \brief newIdGenerate: Create a new id when the user load data (different id).
 *  \return id.
 */
static int newIdGenerate(void)
{
	static int idCliente=0; // es global para solo la fn puede usarla
	//guarda el ultimo que asigne (ultimo que devolvi)
	//para devolver 1+
	idCliente = idCliente+1;
	return idCliente;
}
/**
 * \brief _createNew: Create a new profile asking data to the user.
 *                    Use _searchEmpty, to locate data in an empty index.
 * \param (Cliente) * list: Pointer to the array.
 * \param int len: Array length.
 * \return (-1) Error / (0) Ok
 */
int cliente_createNew(Cliente * list, int len)
{
	int retorno = -1;
	int indice;
	int auxIndice;
	Cliente buffer;
	if (list != NULL && len >0)
	{
		if (cliente_searchEmpty(list,len,&indice) == 0)
		{
			if(utn_getCuit("\n  Ingrese Cuit?","\n  Error no es un cuit valido",buffer.cuit,CANTIDAD_REINTENTOS,SIZE_CUIT) == 0 && buffer.isEmpty==FALSE &&
					cliente_findByCuit(list,len,&auxIndice,buffer.cuit)==-1)
		    {
					if (//utn_getCuit("\n  Ingrese Cuit?","\n  Error no es un cuit valido",buffer.cuit,CANTIDAD_REINTENTOS,SIZE_CUIT) == 0 &&
						utn_getNombre("\n  Ingrese Nombre?","\n  Error no es un nombre valido",buffer.nombre,CANTIDAD_REINTENTOS,SIZE_NAME) == 0 &&
						utn_getNombre("\n  Ingrese Apellido?","\n  Error no es un apellido valido",buffer.apellido,CANTIDAD_REINTENTOS,SIZE_NAME) == 0)
					{
						buffer.idCliente= newIdGenerate();
						list[indice].isEmpty = FALSE;
						list[indice] = buffer;
						retorno=0;
					}
					else
					{
						printf("  ERROR NO INGRESASTE DATOS VALIDOS");
					}
			}
			else
			{
				printf("  CUIT EXISTENTE EN SISTEMA");
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
 * \brief _findByCuit: find position in the array by Cuit.
 * \param (Cliente)* list: Pointer to the array.
 * \param int len: Array length.
 * \param int *pIndex: Pointer to the memory  where write the value.
 * \param char* cuitCliente: Assigned cuit.
 * \return (-1) Error / (0) Ok
 */
int cliente_findByCuit(Cliente* list, int len, int* pIndex, char* cuitCliente)
{
    int retorno = -1;

    if (list != NULL && pIndex!= NULL && len > 0 && cuitCliente>0)
    {
        for (int i = 0; i < len; i++)
        {
            if(list[i].isEmpty == FALSE )
            {
                if(strncmp(list[i].cuit,cuitCliente,SIZE_CUIT)==0)
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
 * \brief _findIdByCuit: find idCliente position in the array  by cuit.
 * \param (Cliente)* list: Pointer to the array.
 * \param int len: Array length.
 * \param char* cuit: Cuit typed by the user.
 * \param int *pIdCliente: Pointer to the memory  where write the search value.
 * \param int id: Assigned id.
 * \return (-1) Error / (0) Ok
 */
int cliente_findIdByCuit(Cliente* list, int len,char* cuitCliente, int* pIdCliente)
{
	int retorno = -1;
	int i;

	if (list != NULL && pIdCliente!= NULL && len > 0 && cuitCliente>0)
	{
		for(i=0;i<len; i++)
		{
			if(list[i].isEmpty==FALSE &&  strncmp(list[i].cuit,cuitCliente,SIZE_CUIT)==0)
			{
				*pIdCliente = list[i].idCliente;
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief _findById: find the position in the array searched by Id.
 * \param (Cliente)* list: Pointer to the array.
 * \param int len: Array length.
 * \param int *pIndex: Pointer to the memory  where write the value.
 * \param int id: Id received to search position.
 * \return (-1) Error / (0) Ok
 */
int cliente_findById(Cliente* list, int len, int* pIndex, int idCliente)
{
    int retorno = -1;

    if (list != NULL && len > 0 && pIndex != NULL && idCliente>0)
    {
        for (int i = 0; i < len; i++)
        {
            if(list[i].isEmpty == FALSE )
            {
                if(list[i].idCliente == idCliente)
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
 * \brief _printById: Print data by ID.
 * \param (Cliente)* list: Pointer to the array.
 * \param int len: Array length.
 * \param int index: Is the data position in the array.
 * \return (-1) Error / (0) Ok
 */
int cliente_printById(Cliente* list, int len, int index)
{
	int retorno = -1;
	if(list!= NULL && len > 0 && index < len)
	{
		if(list[index].isEmpty == FALSE)
		{
			printf("\n  -IDC: %d -Cuit de cliente: %s -Nombre: %s -Apellido: %s",
					list[index].idCliente,list[index].cuit,list[index].nombre, list[index].apellido);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief _printAll: Print all the uploaded data.
 * \param (Cliente)* list: Pointer to the array.
 * \param int len: Array length..
 * \return (-1) Error / (0) Ok
 */
int cliente_printAll(Cliente* list, int len)
{
	int retorno = -1;

	if(list!= NULL && len > 0 )
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				printf("\n  -IDC: %d -Cuit de cliente: %s -Nombre: %s -Apellido: %s",
						list[i].idCliente,list[i].cuit,list[i].nombre, list[i].apellido);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief _modifify: Modify the data only if the index corresponds to a NO Empty
 * \param (Cliente)* list: Pointer to the array.
 * \param int len: Array length.
 * \return (-1) Error / (0) Ok
 */
int cliente_modifify(Cliente* list,int len)
{
	int retorno = -1;
	int idModificar;
	int index;
	Cliente buffer;
	if(list != NULL && len>0)
	{
		cliente_printAll(list,len);
		if(utn_getNumeroString("\n\n  Ingrese el ID a modificar:","  Error Reingrese el ID a modificar!"
									,&idModificar,CANTIDAD_REINTENTOS,1,1000)==0)
		{
		   if(cliente_findById(list,len,&index,idModificar)==0)
		   {
				if(utn_getCuit("\n  Ingrese Cuit?","\n  Error no es un cuit valido",buffer.cuit,CANTIDAD_REINTENTOS,SIZE_CUIT) == 0 &&
					utn_getNombre("\n  Ingrese Nombre?","\n  Error no es un nombre valido",buffer.nombre,CANTIDAD_REINTENTOS,SIZE_NAME) == 0 &&
					utn_getNombre("\n  Ingrese Apellido?","\n  Error no es un apellido valido",buffer.apellido,CANTIDAD_REINTENTOS,SIZE_NAME) == 0)
				{
					//bufferAlumno.isEmpty = FALSE;
					buffer.idCliente= list[index].idCliente; //generarIdNuevo(); // NOOOOOOOOO
					list[index] = buffer;
					list[index].isEmpty = FALSE;
					retorno = 0;
				}
	       }
		   else
		   {
				printf("\n  ID NO ENCONTRADO VERIFIQUE ID\n");
		   }
		}
	}
	return retorno;
}
/**
 * \brief _remove: Remove data by Id (put isEmpty Flag in 1)
 * \param  (Cliente)* list: Pointer to the array.
 * \param int len: Length of the array
 * \param int index: is the position from which the data is deleted.
 * \return int Return (-1) if Error [Invalid length or NULL pointer o] - (0) if Ok
 */
int cliente_remove(Cliente* list,int len )
{
	int retorno = -1;
	int idBaja;
	int index;

	if(list != NULL && len>0)
	{
		cliente_printAll(list,len);
		if(utn_getNumeroString("\n\n  Ingrese el ID a dar de baja:","  Error Reingrese el ID a dar de baja!"
								 ,&idBaja,CANTIDAD_REINTENTOS,1,1000)==0)
		{
			if(cliente_findById(list,len,&index,idBaja)==0)
			{
				if(list[index].isEmpty == FALSE)
				{
					//BAJA LOGICA DE ID
					list[index].isEmpty = TRUE;
					retorno = 0;
				}
			}
		}
		else
		{
			printf("\nID NO ENCONTRADO VERIFIQUE ID\n");
		}
	}
	return retorno;
}
/**
 * \brief _countId: Count the data you have registered.
 * \param (Cliente)* list: Pointer to the array.
 * \param int len: Array length.
 * \paramfloat* quantityId:Pointer to the memory space where the result of the function will be left.
 * \return (-1) Error / (0) Ok
 */
int cliente_countId(Cliente* list,int len,int* quantityId)
{
	int retorno=-1;
	int counterId=0;
	int i;

	if(list!=NULL && len>0 && quantityId!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty==FALSE && list[i].idCliente>0)
			{
				counterId++;
				retorno=0;
			}
		}
	}
	*quantityId = counterId;
	return retorno;
}
/**
 * \brief_altaForzada: Automatically creates a new profile .
 * \param Cliente * list: Pointer to the array.
 * \param int len: Array length.
 * \param char* cuit: Cuit assigned.
 * \param char* nombre: Name of the client.
 * \param char* apellido: Last name of the client..
 * \return (-1) Error / (0) Ok
 */
int cliente_altaForzada(Cliente * list, int len,char*cuit, char* nombre,char* apellido)
{
	int retorno = -1;
	int indice;
	Cliente buffer;
	if (list != NULL && len >0 && cuit!=NULL && nombre!=NULL && apellido!=NULL)
	{
		if(cliente_searchEmpty(list,len,&indice) == 0)
		{
			    strncpy(buffer.cuit,cuit,SIZE_CUIT);
				strncpy(buffer.nombre,nombre,SIZE_NAME);
				strncpy(buffer.apellido,apellido,SIZE_NAME);
				buffer.idCliente= newIdGenerate();
				list[indice] = buffer;
				list[indice].isEmpty = FALSE;
				retorno=0;
	    }
	}
	return retorno ;
}
