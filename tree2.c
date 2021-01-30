#include <stdio.h>
#include <stdlib.h>
#include "tree2.h"

int main(){
	TREE* arvore;
	arvore = NULL;
	int opcao = 0;
	int valor = 0;

	do{
		menu(&opcao);
		switch(opcao){
			case 1:
				valor = RetornaValor();
				InsertNode(&arvore,valor);
				break;

			case 2:
				valor = RetornaValor();
				DeleteNode(&arvore,valor);
				break;

			case 3:
				PreOrder(arvore);
				printf("\n\n");
				break;

			case 4:
				InOrder(arvore);
				printf("\n\n");
				break;

			case 5:
				PosOrder(arvore);
				printf("\n\n");
				break;

			default:
				opcao = 0;
				break;	

		}	

	}while(opcao != 0);	

	return 0;
}	

int DeleteNode(TREE** a,int v){
	if(*a == NULL)
		return -1;
	
	if(v == (*a)->data){
		TREE* aux;

		if((*a)->esq == NULL){
			aux = *a;
			*a = (*a)->dir;
			free(aux);
			return 1;
		}	
		
		if((*a)->dir == NULL){
			aux = *a;
			*a = (*a)->esq;
			free(aux);
			return 1;
		}
		
		else{
			(*a)->data = RetornaMaior(&(*a)->esq);
			return 1;
		}
	}	
	else{
		if(v < (*a)->data){
			DeleteNode(&(*a)->esq,v);
		}	
		if(v > (*a)->data){
			DeleteNode(&(*a)->dir,v);
		}
	}	

}	

int RetornaMaior(TREE** a){
	if((*a)->dir != NULL){
		RetornaMaior(&(*a)->dir);
	}	
	
	else{
		int v = (*a)->data;
		TREE* aux;
	
		aux = *a;
	
		*a = (*a)->esq;

		free(aux);

		return v;
	}

}	

int InsertNode(TREE** a,int v){
	TREE* aux;
	
	if(*a == NULL){
		aux = (TREE* ) malloc(sizeof(TREE));
		aux->data = v;
		aux->esq = NULL;
		aux->dir = NULL;
		*a = aux;
		return 1;
	}	

	else{
		if(v < (*a)->data){
			InsertNode(&(*a)->esq,v);
		}	
		if(v > (*a)->data){
			InsertNode(&(*a)->dir,v);
		}
		
		if(v == (*a)->data){
			printf("O número %d já está presente na árvore!\n\n",v);
			return -1;
		}	
	}	

}	

int PreOrder(TREE* a){
	if(a == NULL)
		return -1;

	printf("%d-",a->data);
	PreOrder(a->esq);
	PreOrder(a->dir);

}	

int InOrder(TREE* a){
	if(a == NULL)
		return -1;
	
	InOrder(a->esq);
	printf("%d-",a->data);
	InOrder(a->dir);

}	

int PosOrder(TREE* a){
	if(a == NULL)
		return -1;

	PosOrder(a->esq);
	PosOrder(a->dir);
	printf("%d-",a->data);
}	

int RetornaValor(){
	int v;
	printf("Digite o valor a ser retornado: ");
	fscanf(stdin,"%d",&v);

	return v;

}	

void menu(int* o){
	printf("Selecione uma das opções abaixo: \n\n\n");

	printf("[1]->Insere nó \n\n");

	printf("[2]->Deleta nó \n\n");

	printf("[3]->Imprime PreOrder \n\n");

	printf("[4]->Imprime InOrder \n\n");

	printf("[5]->Imprime PosOrder \n\n");

	printf("[0]->EXIT\n\n");

	fscanf(stdin,"%d",o);
}	
