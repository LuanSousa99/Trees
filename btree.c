#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"

int main(){
	BTREE* bt;
	bt = NULL;
	srand(time(NULL));
	int array[12] = {43,24,32,25,18,27,21,20,44,12,40,26};
	int r;	

	for(int i = 0; i < 20; i++){
		r = rand() % 50 + 1;
		InsertBT(&bt,r);
		PreOrder(bt);
		printf("valor: %d\n\n",r);
	}	
	
	int x = altura(bt);
	printf("Valor de x: %d\n",x);	
	InOrder(bt);
	printf("\n\n");
	return 0;
}	

int InsertBT(BTREE** bt,int valor){
	if(*bt == NULL){
		NewNode(bt);
		(*bt)->keys[0] = valor;
		(*bt)->NumK = 1;
		return 1;
	}	

	else{	
		BTREE* aux;
		aux = *bt;

		if((*bt)->NumK == 2*G-1){
			BTREE* new;
			NewNode(&new);
			
			new->ponteiros[0] = aux;
			repartir(&new,0);
			
			*bt = new;
			InsertKey(bt,valor);
				
		}	
		
		else{
			InsertKey(bt,valor);
		}	
	}	
}	

int InsertKey(BTREE** bt,int valor){
	int k = (*bt)->NumK-1;

	if((*bt)->leaf == 1){
		for(k = (*bt)->NumK; k > 0; k--){
			if(valor > (*bt)->keys[k-1])
				break;
			
			(*bt)->keys[k] = (*bt)->keys[k-1];
		}	

		(*bt)->keys[k] = valor;
		(*bt)->NumK += 1;
		
	}	

	else{
		
		for(k = (*bt)->NumK-1; k >= 0; k--){
			if(valor > (*bt)->keys[k])
				break;
		}	

		k++;		

		BTREE* aux;
			
		
		aux = (*bt)->ponteiros[k];

		if(aux->NumK == 2*G-1){
			repartir(bt,k);
			if(valor > (*bt)->keys[k])
				k++;
		}	
		
		aux = (*bt)->ponteiros[k];

		InsertKey(&aux,valor);
		
	}	
}	

int repartir(BTREE** bt,int j){
	BTREE* ant;
	BTREE* new;

	ant = (*bt)->ponteiros[j];
	NewNode(&new);
	
	new->keys[0] = ant->keys[G];
	new->NumK = ant->NumK = 1;

	if(ant->leaf == 0){
		for(int i = 0; i < 2; i++){
			new->ponteiros[i] = ant->ponteiros[i+G];
			ant->ponteiros[i+G] = NULL;
		}
		new->leaf = 0;
	}
	int k = 0;

	for(k = (*bt)->NumK; k > j; k--){
		(*bt)->keys[k] = (*bt)->keys[k-1];
		(*bt)->ponteiros[k+1] = (*bt)->ponteiros[k];
	}	

	(*bt)->keys[k] = ant->keys[G-1];
	(*bt)->ponteiros[k] = ant;
	(*bt)->ponteiros[k+1] = new;
	(*bt)->NumK += 1;
	(*bt)->leaf = 0;
	printf("\n\n");
	InOrder(*bt);
	printf("\n\n");

}	

int NewNode(BTREE** bt){
	*bt = (BTREE* ) malloc(sizeof(BTREE));
	int i;

	for(i = 0; i < 2*G-1; i++){
		(*bt)->keys[i] = -1;
		(*bt)->ponteiros[i] = NULL;
	}	

	(*bt)->ponteiros[i] = NULL;

	(*bt)->leaf = 1;
	(*bt)->NumK = 0;
	return 1;
	
	
}	

void PreOrder(BTREE* bt){
	if(bt != NULL){
		int NK = bt->NumK;

		for(int i = 0; i < NK; i++){
			printf("(%d)-",bt->keys[i]);
		}	

		printf("\n");

		for(int i = 0; i <= NK; i++){
			PreOrder(bt->ponteiros[i]);
		}	

	}	
}	

int InOrder(BTREE* bt){
	if(bt != NULL){
		int NK= bt->NumK;
		int i;
		for(i = 0; i < NK; i++){
			InOrder(bt->ponteiros[i]);
			printf("(%d)-",bt->keys[i]);
		}	

		InOrder(bt->ponteiros[i]);
	}	
}	

int altura(BTREE* bt){
	if(bt == NULL)
		return -1;

	int galhos[2*G];

	for(int i = 0; i < 2*G; i++){
		galhos[i] = altura(bt->ponteiros[i]);
	}	

	return galhos[0]+1;
}	
