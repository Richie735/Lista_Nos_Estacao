#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)

#define EMPTY NULL
#define NO_LINK NULL
#define MAX 20


typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum _STATUS { OK, ERROR } STATUS;

typedef struct _LIST_NODE
{
	void* data;
	struct _LIST_NODE* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

typedef struct _ESTACAO
{
	char desig[MAX];
	float custo;
	BOOLEAN ativa,no;
}ESTACAO;



void initList(LIST* list);
void FreeList(LIST* list);		
BOOLEAN emptyList(LIST list);
LIST_NODE* NewNode(void* data);
STATUS RemoveNode(LIST* list, void* data);
STATUS InsertIni(LIST* list, void* data);
STATUS InsertEnd(LIST* list, void* data);

int ListSize(LIST list);
void ShowValues(LIST list);
void ShowStatus(LIST list);

void* FindStationName(LIST list, char* str);

int Menu();

STATUS SaveList(LIST list, const char* filename);
STATUS ReadLine(LIST* list, const char* filename);

/****************************************************************
* Programa principal
****************************************************************/
int main()
{
	LIST line1 = NULL, line2 = NULL, line3 = NULL, line4 = NULL, line5 = NULL;
	ESTACAO* ptr = NULL;
	if (ReadLine(&line1, "Linha1.txt") == OK  &&  ReadLine(&line2, "Linha2.txt") == OK  &&  ReadLine(&line3, "Linha3.txt") == OK  &&  
		ReadLine(&line4, "Linha4.txt") == OK  &&  ReadLine(&line5, "Linha5.txt") == OK) {
		do {
			switch (Menu()) {
			case 1:
				break;

			case 2:
				break;

			case 3:
				break;

			case 4:
				break;

			case 5:
				break;

			case 0:
				return 0;
				break;

			default:
				printf("\n   <Opcao Invalida>   \n\n");
				break;
			}
		} while (true);
	}
	else  printf("     <<ERRO>>\n A ler as linhas\n\n");


	return (0);
}



/****************************************************************
* Funcoes
****************************************************************/

/****************************************************************
* Funcao: Inicializa a lista
*
* Parametros:	list - apontador para lista (duplo apontador para o primeiro no')
* 
* Saida: void
***************************************************************/
void initList(LIST* list)
{
	*list = NULL;
}


/****************************************************************
* Funcao: Da free a lista
*
* Parametros:	list - apontador para lista (duplo apontador para o primeiro no')
*
* Saida: void
***************************************************************/
void FreeList(LIST* list)
{
	LIST_NODE* node;
	
	while (*list != NULL)
	{
		node = (*list)->next;
		free((*list)->data);
		free(*list);
		*list = node;
	}
}


/****************************************************************
* Funcao: verifica se a lista é vazia
*
* Parametros:	list - apontador para lista
* 
* Saida: TRUE se a lista for vazia, ERROR caso contrário
***************************************************************/
BOOLEAN emptyList(LIST list)
{
	return (list == NULL) ? TRUE : FALSE;
}


/****************************************************************
* Funcao: Cria um no'
*
* Parametros:	data - apontador generico para os dados a inserir no no' criado
* 
* Saida: apontador para o no' criado ou NULL em caso de erro
***************************************************************/
LIST_NODE* NewNode(void* data)
{
	LIST_NODE* new_node;
	if ((new_node = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
	{
		DATA(new_node) = data;
		NEXT(new_node) = NULL;
	}
	return(new_node);
}


/****************************************************************
*Funcao: Remove um no'
*
* Parametros:   list - apontador para lista
*				data - apontador generico para os dados a inserir no no' criado
* 
* Saida: OK se o nó foi inserido na LISTA e ERROR caso contrário
***************************************************************/
STATUS RemoveNode(LIST * list, void* data)
{
	LIST_NODE* temp = *list, * ant = *list;

	while (temp != NULL)
	{
		if (temp->data == data) {
			if (temp = *list)   *list = (*list)->next;
			else                ant->next = temp->next;

			free(temp->data);
			free(temp);

			return OK;
		}
		ant = temp;
		temp = temp->next;
	}

	return ERROR;
}


/****************************************************************
* Funcao: Insere um no' no inicio da lista
*
* Parametros:	list - apontador para lista (duplo apontador para o primeiro no')
*				data - apontador generico para os dados a inserir no no' criado
*
* Saida: OK se o nó foi inserido na LISTA e ERROR caso contrário
***************************************************************/
STATUS InsertIni(LIST* list, void* data)
{
	LIST_NODE* new_node;
	if ((new_node = NewNode(data)) != NULL)
	{
		NEXT(new_node) = *list;
		*list = new_node;
		return OK;
	}
	return ERROR;
}


/****************************************************************
* Funcao: Insere um no' no fim da lista
*
* Parametros:	list - apontador para lista (duplo apontador para o primeiro no')
*				data - apontador generico para os dados a inserir no no' criado
* 
* Saida: OK se o nó foi inserido na LISTA e ERROR caso contrário
***************************************************************/
STATUS InsertEnd(LIST* list, void* data)
{
	LIST_NODE* new_node, * temp;
	if ((new_node = NewNode(data)) != NULL)
	{
		if (*list == NULL)
			*list = new_node;
		else
		{
			temp = *list;
			while (NEXT(temp) != NULL)
				temp = NEXT(temp);
			NEXT(temp) = new_node;
		}
		return(OK);
	}
	return(ERROR);
}


/***************************************************************************
* Funcao: calcula quantos elementos contem a lista
*
* Parametros:	list - apontador para uma lista
* 
* Saida: numero de elementos da lista
***************************************************************************/
int ListSize(LIST list)
{
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = NEXT(list);
	}
	return count;
}


/****************************************************************
* Funcao: Escreve no ecra o conteudo da lista
*
* Parametros:	list - apontador para o primeiro no'
* 
* Saida: void
***************************************************************/
void ShowValues(LIST list)
{
	if (emptyList(list) == TRUE)
	{
		printf("\nLista vazia.\n");
		return;
	}

	printf("LISTA ->");
	
	while (list != NULL)
	{
		printf(" %s;%.2f;%d;%d ->", ((ESTACAO*)DATA(list))->desig, ((ESTACAO*)DATA(list))->custo, ((ESTACAO*)DATA(list))->ativa, ((ESTACAO*)DATA(list))->no);
		list = NEXT(list);
	}
	
	printf(" FIM");
}


/****************************************************************
* Funcao: Mostra o tamanho e o conteudo da lista
*
* Parametros:	list - apontador para o primeiro no'
* 
* Saida: void
***************************************************************/
void ShowStatus(LIST list)
{
	printf("\n");
	printf("\nTamanho = %d\n", ListSize(list));
	printf("ESTACOES:\n");
	ShowValues(list);
	printf("\n");

}


/****************************************************************
* Funcao: Procurar por uma estacao numa lista
*
* Parametros:	list - apontador para o primeiro no'
*				str - nome da estacao
*
* Saida: no desejado
***************************************************************/
void* FindStationName(LIST list, char* str)
{
	while (list != NULL)
	{
		if (!strcmp(((ESTACAO*)list->data)->desig, str))	return list->data;
		
		list = list->next;
	}
	return NULL;
}


/****************************************************************
* Funcao: Mostra o menu
*
* Parametros:	void
*
* Saida: Opcao escolhida
***************************************************************/
int Menu()
{
	int op;
	do {
		printf("\n===================================\n");
		printf("\tMENU\t\n");
		printf("===================================\n");
		printf("  1. Ativar/Desativar uma estacao\n");
		printf("  2. Adicionar uma estacao\n");
		printf("  3. Eliminar uma estacao\n");
		printf("  4. Guardar as linhas da rede\n");
		printf("  5. Calcular custo de viagem\n");
		printf("  0. Sair\n");

		printf("\n >> ");
		scanf_s("%d", &op);
	} while (op < 0 && op >5);
	
	return op;
}


/****************************************************************
* Funcao: Guarda uma lista num ficheiro
*
* Parametros:	list - apontador para lista (duplo apontador para o primeiro no')
*				filename - nome do ficheiro onde guardar
* 
* Saida: OK se a lista for guardada com sucesso e ERROR caso o ficheiro nao seja aberto
***************************************************************/
STATUS SaveList(LIST list, const char* filename)
{
	ofstream file;
	file.open(filename);

	if (file.is_open()) {
		while (list != NULL)
		{
			file << ((ESTACAO*)DATA(list))->desig << ';' << ((ESTACAO*)DATA(list))->custo << ';' << ((ESTACAO*)DATA(list))->ativa << ';' << ((ESTACAO*)DATA(list))->no << ';' << endl;
			list = NEXT(list);
		}
	}
	else {
		printf("Erro a Abrir %s", filename);
		return(ERROR);
	}

	file.close();
	return(OK);
}


/****************************************************************
* Funcao: Le uma lista dum ficheiro
*
* Parametros:	list - apontador para lista (duplo apontador para o primeiro no')
*				fname - nome do ficheiro de onde ler
*
* Saida: OK se a lista for guardada com sucesso e ERROR caso o ficheiro nao seja aberto
***************************************************************/
STATUS ReadLine(LIST* list, const char* filename)
{
	ESTACAO* pt = NULL;
	FILE* fp = NULL;
	int ativa, no;

	if ((fp = fopen(filename, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((pt = (ESTACAO*)malloc(sizeof(ESTACAO))) != NULL && (InsertIni(list, pt)) == OK)
			{
				fscanf(fp, "%[^;];%f;%d;%d\n", &pt->desig, &(pt->custo), &ativa, &no);

				pt->ativa = pt->no = FALSE;
				
				if (ativa)	pt->ativa = TRUE;
				if (no)		pt->no = TRUE;
			}
			else
			{
				FreeList(list);
				return ERROR;
			}
		}
		fclose(fp);
		return OK;
	}
	return ERROR;
}
