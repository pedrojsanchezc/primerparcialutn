/*
 * publicaciones.h
 *
 *  Created on: 20 oct. 2020
 *      Author: pedro_000
 */

#ifndef PUBLICACIONES_H_
#define PUBLICACIONES_H_

#include "cliente.h"
#define SIZE_TEXT 64


typedef struct
{
	int id;
	int isEmpty;
	int idCliente;
	char texto[SIZE_TEXT];
	int rubro;
	int isActive;
}Publicacion;

int publicacion_init(Publicacion* list, int len);
int publicacion_searchEmpty(Publicacion* list, int len, int *pIndex);
int publicacion_findById(Publicacion* list, int len, int* pIndex, int id);
int publicacion_createNewProfile(Publicacion * listUno, int lenUno,Cliente* listDos,int lenDos);
int publicacion_pause(Publicacion* list,int len,Cliente* listDos,int lenDos);
int publicacion_reanude(Publicacion* list,int len,Cliente* listDos,int lenDos);
int publicacion_printClientById(Publicacion *list, int len, Cliente *listDos, int lenDos, int id);
int publicacion_findByIdpcliente(Publicacion* list, int len, Cliente *listDos, int lenDos, int id, int* pIdCliente);
int publicacion_printAll(Publicacion *list, int len);
int publicacion_printActive(Publicacion *list, int len);
int publicacion_printPause(Publicacion *list, int len);
int publicacion_cantidadAvisos(Publicacion* list,int len,int id,int *pResultado);
int publicacion_counterActivePublicationClient(Publicacion *list, int len, int id, int *pCounter);
int publicacion_counterPaused(Publicacion *list, int len, int *pCounter);
int publicacion_searchForNoEmpty(Publicacion *list, int len);
int publicacion_searchForActive(Publicacion *list, int len);
int publicacion_findByClientId(Publicacion *list, int len, int id);
int publicacion_rubroMax(Publicacion *list, int len);
int publicacion_equalRubro(Publicacion *list, int len, int rubro, int *pCounter);
int publicacion_altaForzada(Publicacion* list, int len,int idCliente,char* texto,int rubro);
int publicacion_counterPausedPublicationClient(Publicacion *list, int len, int id, int *pCounter);

#endif /* PUBLICACIONES_H_ */
