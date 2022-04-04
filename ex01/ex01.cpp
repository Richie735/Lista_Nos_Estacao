#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum _STATUS { OK, ERROR } STATUS;

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)

#define EMPTY NULL
#define NO_LINK NULL
#define MAX 50

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
	BOOLEAN ativa, no;
}ESTACAO;

void initList(LIST* list);
void FreeList(LIST* list);
BOOLEAN emptyList(LIST list);
LIST_NODE* NewNode(void* data);
STATUS RemoveNode(LIST* list, void* data);
STATUS InsertIni(LIST* list, void* data);
STATUS InsertEnd(LIST* list, void* data);

int ListSize(LIST list);
LIST ChooseList(LIST line1, LIST line2, LIST line3, LIST line4, LIST line5);
void ShowValues(LIST list);
void ShowStatus(LIST list);

void AddEstacao(LIST* list);
void RemoveEstacao(LIST* list);
ESTACAO* FindStationName(LIST list, char* str);

int Menu();

STATUS ReadLine(LIST* list, const char* filename);
STATUS SaveLine(LIST list, const char* filename);


int main()
{
	LIST linha1 = NULL, linha2 = NULL, linha3 = NULL, linha4 = NULL, linha5 = NULL, linha = NULL;
	ESTACAO* ptr = NULL;

	char str[20];
	void* pt = NULL;

	if ((ReadLine(&linha1, "Linha1.txt") == OK)
		&& (ReadLine(&linha2, "Linha2.txt") == OK)
		&& (ReadLine(&linha3, "Linha3.txt") == OK)
		&& (ReadLine(&linha4, "Linha4.txt") == OK)
		&& (ReadLine(&linha5, "Linha5.txt") == OK))
	{
		do {
			switch (Menu()) {
			case 1: // Ativar/Desativar uma estacao
			{
				printf("\n\n-----------------------------------\n");
				printf("\tAtivar / Desativar\t\n");
				printf("-----------------------------------\n");

				linha = ChooseList(linha1, linha2, linha3, linha4, linha5);

				printf(" >Insere o nome da estacao :  ");
				while ((getchar()) != '\n');
				gets_s(str);

				if ((ptr = FindStationName(linha, str)) != NULL)
				{

					if ((ptr->ativa) == FALSE)
					{
						ptr->ativa = TRUE;
						printf(" -Estacao ativada\n");
					}
					else
					{
						ptr->ativa = FALSE;
						printf(" -Estacao desativada\n");
					}
				}
				printf("\n\n");
				break;
			}

			case 2: // Adicionar uma estacao
			{
				linha = ChooseList(linha1, linha2, linha3, linha4, linha5);
				AddEstacao(&linha);
				ShowValues(linha);
				break;
			}

			case 3: // Eliminar uma estacao
			{
				linha = ChooseList(linha1, linha2, linha3, linha4, linha5);
				RemoveEstacao(&linha);
				break;
			}

			case 4: // Guardar as linhas da rede
			{
				break;
			}

			case 5: // Calcular custo de viagem
			{
				break;
			}

			case 0: // Sair
			{
				return 0;
				break;
			}

			default:
			{
				printf("Opção inválida");
				break;
			}
			}
		} while (true);
	}
	else printf("<<ERROR - leitura de linhas>>\n");

	return 0;
}



/****************************************************************
* Funcoes
****************************************************************/

/****************************************************************
* Funcao: Inicializa a lista
*
* Parametros: list - apontador para lista (duplo apontador para o primeiro no')
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
* Parametros: list - apontador para lista
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
* Parametros: data - apontador generico para os dados a inserir no no' criado
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
STATUS RemoveNode(LIST* list, void* data)
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
* Parametros: list - apontador para lista (duplo apontador para o primeiro no')
*			  data - apontador generico para os dados a inserir no no' criado
* 
Saida: OK se o nó foi inserido na LISTA e ERROR caso contrário
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
* Parametros: list - apontador para lista (duplo apontador para o primeiro no')
*			  data - apontador generico para os dados a inserir no no' criado
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
* Parametros: list - apontador para uma lista
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


/***************************************************************************
* Funcao: calcula quantos elementos contem a lista
*
* Parametros: line+ - apontador para uma lista
* 
* Saida: numero de elementos da lista
***************************************************************************/
LIST ChooseList(LIST line1, LIST line2, LIST line3, LIST line4, LIST line5)
{
	int op;

	printf(" >Numero da linha : ");
	scanf("%d", &op);

	switch (op) {
		case 1: 
			return line1;
			break;
		
		case 2:
			return line2;
			break;

		case 3: 
			return line3;
			break;

		case 4:
			return line4;
			break;
		
		case 5:
			return line5;
			break;
		
		default:
			printf("Linha nao existe \n");
			break;
	}
}

/****************************************************************
* Funcao: Escreve no ecra o conteudo da lista
*
* Parametros: list - apontador para o primeiro no'
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
	printf("INICIO LISTA:\n");
	while (list != NULL)
	{
		printf(" %s;%.1f;%d;%d;\n", ((ESTACAO*)DATA(list))->desig, ((ESTACAO*)DATA(list))->custo, ((ESTACAO*)DATA(list))->ativa, ((ESTACAO*)DATA(list))->no);
		list = NEXT(list);
	}
	printf("--FIM--\n");
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
	printf("\n---Tamanho = %d---\n", ListSize(list));
	ShowValues(list);
	printf("\n");

}


/***************************************************************************
* Funcao: Insere uma estacao no fim de uma lista
*
* Parametros: list - apontador para o primeiro no'
* 
* Saida: void
***************************************************************************/
void AddEstacao(LIST* list)
{
	ESTACAO* ptr;
	int ativa, no;

	if (((ptr = (ESTACAO*)malloc(sizeof(ESTACAO))) != NULL) && (InsertEnd(list, ptr) == OK))
	{
		printf(" Designação: ");
		scanf("%s", &ptr->desig);

		printf(" Custo: ");
		scanf("%f", &ptr->custo);
		
		printf(" Ativo (0/1): ");
		scanf("%d", &ativa);
		if (ativa) ptr->ativa = TRUE;
		else ptr->ativa = FALSE;

		printf(" No (0/1): ");
		scanf("%d", &no);
		if (no) ptr->no = TRUE;
		else ptr->no = FALSE;
	}
}


/***************************************************************************
* Funcao: Remove uma estacao de uma lista
*
* Parametros: list - apontador para lista (duplo apontador para o primeiro no')
*
* Saida: void
***************************************************************************/
void RemoveEstacao(LIST* list)
{
	char str[30];
	ESTACAO* ptr;

	printf("\n\n\n");
	printf("Designação da estação: ");
	while ((getchar()) != '\n');
	gets_s(str);

	if ((ptr = FindStationName(*list, str)) != NULL) RemoveNode(list, ptr);
	else printf("Estação inexistente\n");

}


/****************************************************************
* Funcao: Procurar por uma estacao numa lista
*
* Parametros:	list - apontador para o primeiro no'
*				str - nome da estacao
*
* Saida: no desejado
***************************************************************/
ESTACAO* FindStationName(LIST list, char* str)
{
	while (list != NULL)
	{
		if (!strcmp(((ESTACAO*)list->data)->desig, str))
		{
			printf(" -Estacao encontrada\n");
			return (ESTACAO*)DATA(list);
		}
		list = NEXT(list);
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
		printf("\t\tMENU\t\n");
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
STATUS SaveLine(LIST list, const char* filename)
{
	FILE* fp = NULL;
	ESTACAO* pt = NULL;
	int ativa = 0, no = 0;

	if ((fp = fopen(filename, "w")) != NULL)
	{
		while (list != NULL)
		{
			pt = (ESTACAO*)DATA(list);
			if (pt->ativa) ativa = 1;
			if (pt->no) no = 1;
			fprintf(fp, "%c;%.1f;%d;%d;\n", pt->desig, pt->custo, ativa, no);
			list = NEXT(list);
		}
		fclose(fp);
		printf("Linha salva com sucesso\n");
		return OK;
	}
	else {
		fclose(fp);
		printf("ERRO\n");
		return ERROR;
	}
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
	FILE* fp = NULL;
	ESTACAO* pt = NULL;
	int ativa = 0, no = 0;

	if (((fp = fopen(filename, "r")) != NULL))
	{
		while (!feof(fp))
		{
			if (((pt = (ESTACAO*)malloc(sizeof(ESTACAO))) != NULL) && (InsertEnd(list, pt) == OK))
			{
				fscanf(fp, "%[^;];%f;%d;%d;\n", pt->desig, &(pt->custo), &ativa, &no);
				pt->ativa = pt->no = FALSE;
				if (ativa)
					pt->ativa = TRUE;
				if (no)
					pt->no = TRUE;
				//InsertIni(list, pt);
			}
			else
			{
				FreeList(list);
				return (ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	return(ERROR);
}