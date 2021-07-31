// Paulina VF	26/04/18
//PRÁCTICA EXAMEN		CONVOCATORIA AUTORES JÓVENES
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
struct datos
{
	char snom[21];
	int iedad;
	int icla;
	char cate;
};
struct nodo
{
	struct nodo * next;
	struct datos aplicante;
};
int menu ()
{
	int iopc_m;
	printf("\tCONVOCATORIA AUTORES JOVENES\n\n");
	printf("1)  Mandar solicitud\n2)  Mostrar Solicitudes en Proceso\n3)  Procesar Primera Solicitud\n4)  Numero de Solicitudes por Atender\n5)  Procesar Solicitud por Clave\n0)  Salir\n");
	printf("\n\tOPCION:  ");
	scanf("%d",&iopc_m);
	printf("\n");
	return iopc_m;
}//MENU
struct nodo *Solicitud (struct nodo *head_s)
{
	struct datos aplicante;
	struct nodo *temporal;
	int indice;
	//Solicita información
	printf("Ingrese los siguientes datos para procesar su solicitud:\n");
	printf("\n\tNOMBRE:  ");
	fflush(stdin);
	gets(aplicante.snom);
	printf("\tEDAD:  ");
	scanf("%d",&aplicante.iedad);
	printf("\tCATEGORIAS\n\n\t\ta)  CUENTO CORTO\n\t\tb)  POEMA\n\t\tc)  NOVELA JUVENIL\n\n\tCATEGORIA ELEGIDA:  ");
	aplicante.cate=getch();
	printf("%c\n",aplicante.cate);
	printf("\tCLAVE:  ");
	scanf("%d",&aplicante.icla);
	printf("\n");
	//Crea el nodo
	temporal=(struct nodo *) malloc (sizeof(struct nodo));
	//Poner informacion en el nodo
	temporal->aplicante.cate = aplicante.cate;
	temporal->aplicante.icla = aplicante.icla;
	temporal->aplicante.iedad = aplicante.iedad;
	for (indice=0; indice<=strlen(aplicante.snom);indice++)
	{
		temporal->aplicante.snom[indice] = aplicante.snom[indice];
	}//FOR
	temporal->next = NULL;
	//Acomodar el nodo
	if (head_s == NULL)
	{
		head_s = temporal;
	}//IF
	else
	{
		temporal->next=head_s;
		head_s=temporal;
	}//ELSE
	return head_s;
}
struct nodo *Procesamiento (struct nodo *head_p)
{
	struct nodo *temporal;
	temporal=head_p;
	head_p=temporal->next;
	free(temporal);
	printf("Solicitud Procesada\n\n");
	return head_p;
}
struct nodo *ProcesamientoEspecifico (struct nodo *head_p, int iclav, int *iexis)
{
	struct nodo *actual;
	struct nodo *anterior;
	struct datos aplicante;
	actual = head_p;
	anterior = head_p;
	while ((actual->aplicante.icla!=iclav)&&(actual->next!=NULL))
	{
		anterior=actual;
		actual=actual->next;
	}//WHILE
	if((actual->next==NULL)&&(actual->aplicante.icla!=iclav))
	{
		//No esta disponible
		*iexis=0;
	}
	else
	{
		if(actual==head_p)
		{
			head_p=actual->next;
		}
		else
		{
			anterior->next=actual->next;
		}
		free(actual);
		*iexis=1;
	}
	return head_p;
}
int main ()
{
	int iopc, indice, Sol_Pend=0, iexis=-1, iclav;
	struct nodo *head;
	struct nodo *temporal;
	struct datos aplicante;
	head=NULL;
	do
	{
		iopc=menu();
		switch (iopc)
		{
			case 1:
				head=Solicitud(head);
				break;
			case 2:
				temporal=head;
				while (temporal!=NULL)
				{
					printf("%20s %2d %2c %5d\n",temporal->aplicante.snom,temporal->aplicante.iedad,temporal->aplicante.cate,temporal->aplicante.icla );
					temporal=temporal->next;
				}
				printf("\n");
				break;
			case 3:
				if(head==NULL)
				{
					printf("No hay solicitudes pendientes\n\n");
				}
				else
				{
					head=Procesamiento(head);
				}
				break;
			case 4:
				Sol_Pend=0;
				temporal=head;
				while (temporal!=NULL)
				{
					Sol_Pend++;
					temporal=temporal->next;
				}
				printf("El numero de solicitudes por ser atendidas es: %d\n\n", Sol_Pend);
				break;
			case 5:
				if(head!=NULL)
				{
					printf("Ingrese la clave de la solicitud que busca:  ");
					scanf("%d",&iclav);
					head=ProcesamientoEspecifico(head, iclav, &iexis);
					if(iexis==1)
						printf("La solicitud con clave %d fue procesada exitosamente\n\n",iclav);
					else
						printf("No se encontro ninguna solicitud con la clave %d\n\n",iclav);
					}
					else
						printf("No se encontro ninguna solicitud pendiente\n\n");
				break;
			case 0:
				break;
			default:
				printf("Opcion invalida\n\n");
				break;
		}//SWITCH
	}while(iopc!=0);
	return 0;
}//MAIN
