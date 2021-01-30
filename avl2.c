#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl2.h"

int main(){
	AVL* avl;
	avl = NULL;
	int valor,op;
	int contador = 1;

	int array[25] = {30,10,20,50,40,100,60,80,70,90,13,31,21,12,43,45,54,56,65,654,67,76,78,87,90};
	int arrayzin[8] = {20,30,10,15,5,22,33,2};	

	for(int i = 0; i < 25; i++)
		InsertAVL(&avl,array[i]);

	do{
		menu(&op);

		switch(op){
			case 1:
				DefineValor(&valor);
				InsertAVL(&avl,valor);
				break;

			case 2:
				DefineValor(&valor);
				DeleteAVL(&avl,&avl,valor);
				break;

			case 3:
				PreOrder(avl,&contador);
				contador = 1;
				break;

			default:
				op = 0;
				break;	
		}	

	}while(op != 0);	

	return 0;
}	

int DeleteAVL(AVL** avl,AVL** root,int valor){

	
	if(*avl == NULL)
		return -1;

	int resp;
	AVL* aux;
	
	if(valor < (*avl)->info){
		if(resp = DeleteAVL(&(*avl)->galhos[0],root,valor) > 0){
			aux = (*avl)->galhos[0];
			
			if(aux->info == valor){
				if(aux->galhos[0] == NULL && aux->galhos[1] == NULL)
					(*avl)->galhos[0] = NULL;

				if(aux->galhos[0] != NULL){
					(*avl)->galhos[0] = aux->galhos[0];
					free(aux);
				}	

				if(aux->galhos[1] != NULL){
					(*avl)->galhos[0] = aux->galhos[1];
					free(aux);
				}	

			}
			altura(*avl);
			BalanceFactor(avl);
			return 1;
		}	
	}	

	if(valor > (*avl)->info){
		if(resp = DeleteAVL(&(*avl)->galhos[1],root,valor) > 0){
			aux = (*avl)->galhos[1];
			
			if(aux->info == valor){
				if(aux->galhos[0] == NULL && aux->galhos[1] == NULL)
					(*avl)->galhos[1] = NULL;

				if(aux->galhos[0] != NULL){
					(*avl)->galhos[1] = aux->galhos[0];
					free(aux);
				}	

				if(aux->galhos[1] != NULL){
					(*avl)->galhos[1] = aux->galhos[1];
					free(aux);
				}	
			}
			altura(*avl);
			BalanceFactor(avl);
			return 1;
		}	
	}	

	if(valor == (*avl)->info){
		if((*avl)->galhos[0] != NULL && (*avl)->galhos[1] != NULL){
			int x = 0;	
		       	retornaMaior(&(*avl)->galhos[0],&x);
			printf("X: %d\n",x);
			(*avl)->info = x;

			if((*avl)->info == (*avl)->galhos[0]->info){
				AVL* temp;
				temp = (*avl)->galhos[0];
				(*avl)->galhos[0] = (*avl)->galhos[0]->galhos[0];
				free(temp);
			}
			altura(*avl);
			BalanceFactor(avl);
			return 1;
		}
		

		else{	
			if(valor == (*root)->info && *avl == *root){	
				AVL* aux;
				if((*avl)->galhos[0] == NULL && (*avl)->galhos[1] == NULL){
					*avl = NULL;
					return 1;	
				}	
				if((*avl)->galhos[0] != NULL){
					aux = *avl;
					(*avl) = (*avl)->galhos[0];
					free(aux);
				}	

				if((*avl)->galhos[1] != NULL){
					aux = *avl; 
					(*avl) = (*avl)->galhos[1];
					free(aux);
				}	
			}	
			printf("ELSE\n\n");
			return 1;
		}	
	}	

}	

int retornaMaior(AVL** aux,int* x){
	if((*aux)->galhos[1] == NULL){
		*x = (*aux)->info;
		return 1;
	}	

	else{
		retornaMaior(&(*aux)->galhos[1],x);

		if(*x == (*aux)->galhos[1]->info){
			AVL* temp;
			temp = (*aux)->galhos[1];
			(*aux)->galhos[1] = (*aux)->galhos[1]->galhos[0];
			free(temp);
		}
		altura(*aux);
		BalanceFactor(aux);
	}	
}	

int buscaDelete(AVL** aux,AVL** ant,int valor){
	while(*aux != NULL){
		if((*aux)->info == valor){
			return 1;
		}
		*ant = *aux;

		if(valor < (*aux)->info){
			*aux = (*aux)->galhos[0];
		}		

		if(valor > (*aux)->info){
			*aux = (*aux)->galhos[1];
		}	

	}	

	*aux = NULL;
	return -1;
}	

int InsertAVL(AVL** avl,int valor){
	if(*avl == NULL){
		AVL* aux;
		aux = (AVL* ) malloc(sizeof(AVL));

		for(int i = 0; i < 2; i++)
			aux->galhos[i] = NULL;

		aux->info = valor;
		aux->bf = 0;

		*avl = aux;
		return 1;
	}
	
	else{
		if(valor < (*avl)->info)
			InsertAVL(&(*avl)->galhos[0],valor);

		if(valor > (*avl)->info)
			InsertAVL(&(*avl)->galhos[1],valor);

		altura(*avl);

		BalanceFactor(avl);
	}	
	
	
}	

int BalanceFactor(AVL** avl){
	if(*avl != NULL){
		if((*avl)->bf > 1){
			printf("BF: %d\n",(*avl)->info);
			if((*avl)->galhos[0]->bf <= -1){
				printf("LR\n\n");
				rotacaoESQ(&(*avl)->galhos[0]);
			}	
			
			printf("RR\n\n");
			rotacaoDIR(avl);
			altura(*avl);
			return 1;
		}
		
		if((*avl)->bf < -1){
			printf("BF: %d\n",(*avl)->info);
			if((*avl)->galhos[1]->bf >= 1){
				printf("RL\n\n");
				rotacaoDIR(&(*avl)->galhos[1]);
			}	
			
			printf("LL\n\n");
			rotacaoESQ(avl);
			altura(*avl);
			return 1;
		}	

	}	
}	

int rotacaoDIR(AVL** avl){
	AVL* aux;
	aux = (*avl)->galhos[0];
	(*avl)->galhos[0] = aux->galhos[1];
	aux->galhos[1] = *avl;
	*avl = aux;
}

int rotacaoESQ(AVL** avl){
	AVL* aux;
	aux = (*avl)->galhos[1];
	(*avl)->galhos[1] = aux->galhos[0];
	aux->galhos[0] = *avl;
	*avl = aux;
}	

int altura(AVL* avl){
	if(avl == NULL)
		return -1;

	else{
		int esq = altura(avl->galhos[0]);
		int dir = altura(avl->galhos[1]);

		avl->bf = esq - dir;

		if(esq > dir)
			return esq+1;

		else{
			return dir+1;
		}	

	}	
}	

void PreOrder(AVL* avl,int* contador){
	if(avl != NULL){
		printf("%do.: Info: %d || BF: %d\n",*contador,avl->info,avl->bf);
		*contador += 1;

		for(int i = 0; i < 2; i++)
			PreOrder(avl->galhos[i],contador);
	}	


}	

void DefineValor(int* v){
	printf("Digite o valor: ");
	fscanf(stdin,"%d",v);
}	

void menu(int* o){
	printf("Selecione um dos itens abaixo: \n\n");

	printf("[1] Insert AVL;\n");
	printf("[2] Delete AVL;\n");
	printf("[3] PreOrder;\n");
	printf("[0] EXIT.\n");

	fscanf(stdin,"%d",o);
}	
