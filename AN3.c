#include <stdio.h>
#include <stdlib.h>
#include "AN3.h"

int main(){
	ARVORENARIA* an;
	an = NULL;
	int array[31] = {23,95,184,310,32,69,78,82,45,2,7,14,18,9,12,3,5,512,190,201,220,301,231,244,250,98,99,116,180,100,107};
	
	for(int i = 0; i < 31; i++){
		InsertNaria(&an,array[i]);
	}	
	
	ordenado(an);
	printf("\n\n");
	int op = 0;
	int valor;

	do{
		menu(&op);

		switch(op){
			case 1:
				defineValor(&valor);
				InsertNaria(&an,valor);
				break;

			case 2:
				defineValor(&valor);
				DeleteNaria(&an,valor);	
				break;

			case 3:
				ordenado(an);
				printf("\n\n");
				break;
			
			case 4:
				PreOrder(an);
				printf("\n\n");
				break;	

			default:
				op = 0;
				break;	

		}	

	}while(op != 0);	


	return 0;
}	

int DeleteNaria(ARVORENARIA** an,int v){
	ARVORENARIA* aux;

	int p;
	buscaNo(*an,v,&aux,&p);
	
	if(p != -1){
		int Nk = (aux)->NrKeys;
		int k;


		if(aux->ponteiros[p] == NULL){
			if(aux->ponteiros[p+1] == NULL){
				printf("Caso 4\n");
				if(aux->NrKeys == 1){
					if(aux == *an){
						*an = NULL;
						return 1;
					}	
					
					ARVORENARIA* aux2;
					ARVORENARIA* prev;
					prev = NULL;
					aux2 = NULL;
					int x;
					int y;
					


					buscaPrev(*an,v,&aux2,&prev,&x,&y);
					
					printf("prev: %d || aux: %d\n\n",prev->keys[y],aux2->keys[x]);
					
					if(prev != NULL){
						prev->ponteiros[y] = NULL;
					}	
					
					return 1;
				}	
				
				for(k = p; k < Nk; k++){
					aux->keys[k] = aux->keys[k+1];
					aux->ponteiros[k] = aux->ponteiros[k+1];
					aux->ponteiros[k+1] = NULL;
				}	

				aux->NrKeys -= 1;
				
				return 1;		
			}	
		}	

		if(aux->ponteiros[p] == NULL){
			printf("Caso 1\n");
			if(aux == *an){
				if((*an)->NrKeys == 1){
					ARVORENARIA* temp;
					temp = *an;
					*an = (*an)->ponteiros[p+1];
					free(temp);
					return 1;
				}	
				
				for(k = p; k < Nk; k++){
					(*an)->keys[k] = (*an)->keys[k+1];
					(*an)->ponteiros[k] = (*an)->ponteiros[k+1];
					(*an)->ponteiros[k+1] = NULL;
				}	
				(*an)->NrKeys -= 1;
				return 1;

			}
			else{	
				if(aux->NrKeys == 1){
					ARVORENARIA* temp;
					ARVORENARIA* aux2;
					int x;

					aux2 = retornaPonteiro(*an,aux,&x);
					
					temp = aux;
					aux2->ponteiros[x] = aux->ponteiros[p+1];
					free(temp);
					printf("HERE\n");
					return 1;
				}	

				for(k = p; k < Nk; k++){
					aux->keys[k] = aux->keys[k+1];
					aux->ponteiros[k] = aux->ponteiros[k+1];
					aux->ponteiros[k+1] = NULL;
				}	

				aux->NrKeys -= 1;
				return 1;
			}
		}	

		if(aux->ponteiros[p+1] == NULL){
			printf("Caso 2\n");
			if(aux == *an){
				if((*an)->NrKeys == 1){
					ARVORENARIA* temp;
					temp = *an;
					*an = (*an)->ponteiros[p];
					free(temp);
					return 1;
				}	


				for(k = p; k < Nk; k++){
					(*an)->keys[k] = (*an)->keys[k+1];
					(*an)->ponteiros[k+1] = (*an)->ponteiros[k+2];
					(*an)->ponteiros[k+2] = NULL;
				}	
				(*an)->NrKeys -= 1;	
				return 1;

			}
			else{
				if(aux->NrKeys == 1){
					ARVORENARIA* temp;
					ARVORENARIA* aux2;
					temp = aux;
					int x;
					aux2 = retornaPonteiro(*an,aux,&x);
					
					aux2->ponteiros[x] = aux->ponteiros[p];
					free(temp);
					return 1;


				}	

				for(k = p; k < Nk; k++){
					aux->keys[k] = aux->keys[k+1];
					aux->ponteiros[k+1] = aux->ponteiros[k+2];
					aux->ponteiros[k+2] = NULL;
				}	
				aux->NrKeys -= 1;
				return 1;
			}
		}	

		else{
			printf("Caso 3\n");
			int n;

			if(*an == aux){
				n = retornaMaior(&(aux)->ponteiros[p],*an);
				(*an)->keys[p] = n;
				return 1;		
			}
			else{	
				n = retornaMaior(&(aux)->ponteiros[p],*an);
				printf("Valor de n: %d\n",n);
				aux->keys[p] = n;
				return 1;
			}
		}	
	}	
}	

int retornaMaior(ARVORENARIA** an,ARVORENARIA* root){
	if(*an != NULL){
		int Nk = (*an)->NrKeys;
		int n;
		
		if((*an)->ponteiros[Nk] == NULL){
			n = (*an)->keys[Nk-1];
			
			if((*an)->NrKeys == 1){
				*an = NULL;	
				return n;
				
			}	
			
			(*an)->NrKeys -= 1;
			return n;
		}
		else{
			retornaMaior(&(*an)->ponteiros[Nk],root);
		}	


	}	
}	

ARVORENARIA* retornaPonteiro(ARVORENARIA* an,ARVORENARIA* aux,int* p){
	if(an != NULL){
		int Np = an->NrKeys + 1;
		
		for(*p = 0; *p < Np; (*p)++){
			if(an->ponteiros[*p] == aux){
				return an;
			}	
		}	

			
		for(*p = 0; *p < Np; (*p)++){
			retornaPonteiro(an->ponteiros[*p],aux,p);
		}		
			
	}
}	

int buscaPrev(ARVORENARIA* root,int valor,ARVORENARIA** aux,ARVORENARIA** prev,int* j,int* i){
	if(root == NULL){
		return -1;

	}	
	
	else{
		*aux = root;
		int NK = (*aux)->NrKeys;

		for(*j = 0; *j < NK; (*j)++){
			if((*aux)->keys[*j] == valor){
				printf("%d == %d\n",(*aux)->keys[*j],valor);
				return 1;
			}	
			else if((*aux)->keys[*j] > valor){
				break;
		

			}	
			printf("%d != %d\n",(*aux)->keys[*j],valor);
		
		}
		*prev = *aux;
		*i = *j;
		printf("%d != %d\n",(*aux)->keys[*j],valor);
		buscaPrev((*aux)->ponteiros[*j],valor,aux,prev,j,i);	
			
	}

}	

int InsertNaria(ARVORENARIA** root,int valor){
	ARVORENARIA* aux;
	int j;

	if(*root == NULL){
		aux = (ARVORENARIA* ) malloc(sizeof(ARVORENARIA));
		aux->NrKeys = 1;

		for(j = 0; j < TAMANHO; j++){
			aux->keys[j] = -1;
			aux->ponteiros[j] = NULL;
		}	
		aux->ponteiros[j] = NULL;
		aux->keys[0] = valor;

		*root = aux;
		return 1;
	}
	else{
		buscaInsert(*root,valor,&aux,&j);
		if(-1 == j){
			printf("Esse valor %d já existe na árvore N-aria!!!\n\n");
			return -1;
		}
		else{
			int Nk = aux->NrKeys;

			if(Nk == TAMANHO){
				ARVORENARIA* H;
				H =  (ARVORENARIA* ) malloc(sizeof(ARVORENARIA));
				H->NrKeys = 1;
				int i;

				for(i = 0; i < TAMANHO; i++){
					H->keys[i] = -1;
					H->ponteiros[i] = NULL;
				}	
				H->ponteiros[i] = NULL;
				H->keys[0] = valor;

				aux->ponteiros[j] = H;
				return 1;

			}
			else{
				if(Nk == j){	
					aux->ponteiros[j] = NULL;
				}	
				else{
					int k;

					for(k = Nk; k > j; k--){
						aux->keys[k] = aux->keys[k-1];
						aux->ponteiros[k] = aux->ponteiros[k-1];	
					}	
					aux->ponteiros[k] = NULL;
				}
				
				aux->keys[j] = valor;
				aux->NrKeys += 1;	
			}	
		}	
	}	
}	

void menu(int* o){
	printf("[1] Inserir item na árvore N-aria;\n\n");

	printf("[2] Deletar item na árvore N-aria;\n\n");

	printf("[3] Imprime de forma ordenada;\n\n");

	printf("[4] Imprime PreOrder;\n\n");
	
	printf("[0] EXIT.\n\n");

	printf("Escolha uma das opções acima: ");
	fscanf(stdin,"%d",o);
}	

void defineValor(int* valor){
	printf("Digite o valor: ");
	fscanf(stdin,"%d",valor);
}	

int buscaNo(ARVORENARIA* root,int valor,ARVORENARIA** aux,int* j){
	if(root == NULL){
		*aux = NULL;
		*j = -1;
		return -1;
	}	
	
	else{
		*aux = root;
		int Nk;
		Nk = (*aux)->NrKeys;

		for(*j = 0; *j < Nk; (*j)++){
			if(valor == (*aux)->keys[*j]){
				return 1;
			}	
			else if(valor < (*aux)->keys[*j]){
				break;
			}	
		}	
		buscaNo((*aux)->ponteiros[*j],valor,aux,j);
	}
}	

void ordenado(ARVORENARIA* an){
	if(an != NULL){
		int Nk = an->NrKeys;
		int i;
		
		for(i = 0; i < Nk; i++){
			ordenado(an->ponteiros[i]);
			printf("(%d)-",an->keys[i]);
		}	
		printf("\n\n");

		ordenado(an->ponteiros[i]);

	}	
}	

void PreOrder(ARVORENARIA* an){
	if(an != NULL){
		int Nk = an->NrKeys;
		int i;

		for(i = 0; i < Nk; i++){
			printf("(%d)-",an->keys[i]);
		}	
		printf("\n\n");

		
		for(int j = 0; j < Nk+1; j++){
			PreOrder(an->ponteiros[j]);
		}	
	}	
}	

int buscaInsert(ARVORENARIA* root,int valor,ARVORENARIA** aux,int* j){
	if(root != NULL){
		*aux = root;
		int Nk = (*aux)->NrKeys; 	
		
		for(*j = 0; *j < Nk; (*j)++){
			if(valor == (*aux)->keys[*j]){
				*aux = NULL;
				*j = -1;
				return -1;
			}	
			else{
				if(valor < (*aux)->keys[*j]){
					if(Nk < TAMANHO){
						return 1;
					}	
					else{
						break;
					}	

				}	
			}	
		}
		buscaInsert((*aux)->ponteiros[*j],valor,aux,j);
	}	
}	
