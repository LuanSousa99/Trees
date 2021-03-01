#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RBT.h"

int main(){
	RB* root = NULL;
	RB* stack[100];
	srand(time(NULL));

	for(int i = 0; i < 100; i++){
		insertionRB(&root,&root,i+1);

		InOrder(root);
		printf("root: %d || balanco: %d\n\n",root->data,balanco(root,root));
	}
	
	VerificaRegras(root,root);

	for(int i = 100; i > 1; i--){
		deletionRB(&root,&root,i);
		InOrder(root);
		int x = VerificaRegras(root,root);
		
		if(x == -1)
			break;

		if(root != NULL)
			printf("root: %d || balanco: %d\n\n",root->data,balanco(root,root));
	}
	return 0;
}	

int VerificaRegras(RB* root,RB* rb){
	if(rb != NULL){
		int x = 0;
		int l,r;
		if(root->color == RED){
			printf("Regra da raiz violada!\n\n");
			return -1;
		}	

		if(rb->color == RED){
			if(((rb->branch[0]) && (rb->branch[0]->color == RED)) ||((rb->branch[1]) && (rb->branch[1]->color == RED))){
				printf("Regra dos nós vermelhos violada!\n");
				return -1;	
			}	
		}	

		l = VerificaRegras(root,rb->branch[0]);
		r = VerificaRegras(root,rb->branch[1]);
		
		if(l == -1)
			x = l;

		if(r == -1)
			x = r;	


		if(rb == root){
			int tot = 0;
			int caminhos[150];
			int y;

			DepthProperty(root,caminhos,&tot,0);
			
			y = caminhos[0];
			for(int i = 0; i < tot; i++){
				printf("%d:  %d || y: %d\n",i,caminhos[i],y);
				if(y != caminhos[i]){
					printf("Propriedade de profundidade violada!\n\n");
					return -1;
				}	
			}		
		}	

		return x;
	}	
}	

void DepthProperty(RB* rb,int caminhos[],int* tot,int b){
	if(rb != NULL){
		if((rb->branch[0] != NULL) && (rb->branch[1] != NULL)){
			int x = *tot;
	
			caminhos[x] = b;
			(*tot)++;
			return;
		}
	}	
	
	if(rb != NULL){
		if(rb->color == BLACK){
			DepthProperty(rb->branch[0],caminhos,tot,b+1);
			DepthProperty(rb->branch[1],caminhos,tot,b+1);
		}

		else{
			DepthProperty(rb->branch[0],caminhos,tot,b);
			DepthProperty(rb->branch[1],caminhos,tot,b);
		}	

	}	
}

int deletionRB(RB** root,RB** aux,int data){
	if(*root == NULL){
		printf("Árvore vazia!!!\n\n");
		return -1;
	}	

	else{
		if(*aux == NULL){
			printf("Número %d não encontrado!\n\n",data);
			return -1;
		}	

		if((*aux)->data == data){
			if(*root != NULL)

			RB* deleted, *replacement, *Xptr, *Yptr, *Zptr;

			deleted = *aux;


			if((*aux)->branch[0] == NULL && (*aux)->branch[1] == NULL){
				if(*aux == *root){
					free(*aux);
					*root = NULL;
					return 1;
				}	
				else{
					printf("Sem nó child\n");
					if((*aux)->parent == *root){
						(*root)->branch[(*root)->dir] = NULL;
						Zptr = *root;
					}	
				
					else{
						printf("aux->parent data: %d || dir: %d\n",(*aux)->parent->data,(*aux)->parent->dir);
						Zptr = (*aux)->parent;
						(*aux)->parent->branch[(*aux)->parent->dir] = NULL;
					}
					replacement = NULL;
					
					if(deleted == NULL)
						printf("Deleted == NULL\n");
				}
				Xptr = NULL;
			}

			else{
				if((*aux)->branch[0] != NULL && (*aux)->branch[1] != NULL){
					Xptr = (*aux)->branch[1];
					Xptr->parent = *aux;
					int z;		

					if(Xptr->branch[0] == NULL){
						Yptr = Xptr;
						Zptr = Yptr->parent;
						z = 1;
						
					}	
					
					else{
						while(1){
							Yptr = Xptr->branch[0];
							Yptr->parent = Xptr;

							if(Yptr->branch[0] == NULL)
								break;
							
							Xptr = Yptr;
						}	
						Zptr = Xptr;
						z = 0;
					}

					
					Xptr = Yptr->branch[1];
					Zptr->branch[z] = Xptr;
					
					replacement = Yptr;
					replacement->branch[0] = (*aux)->branch[0];
					replacement->branch[1] = (*aux)->branch[1];
					
					if(*aux == *root){
						replacement->parent = NULL;
						*root = replacement;
					}	
					
					else{
						replacement->parent = (*aux)->parent;	
						(*aux)->parent->branch[(*aux)->parent->dir] = replacement;
					}

					
				}

				else{
					if((*aux)->branch[0] == NULL){
						replacement = (*aux)->branch[1];
						
						if(*aux == *root){
							replacement->parent = NULL;
							*root = replacement;
							return 1;
						}	
						
						else{
							replacement->parent = (*aux)->parent;
							(*aux)->parent->branch[(*aux)->parent->dir] = replacement;
							Zptr = (*aux)->parent;
						}
					}
						
					else{
						
						replacement = (*aux)->branch[0];
						
						if(*aux == *root){
							replacement->parent = NULL;
							*root = replacement;
							return 1;
						}	
						
						else{
							replacement->parent = (*aux)->parent;
							(*aux)->parent->branch[(*aux)->parent->dir] = replacement;
							Zptr = (*aux)->parent;
						}	
					}	
				}	
			}
			printf("Teste deleted->color = %d\n",deleted->color);
			if(deleted->color == RED){
				printf("deleted %d == RED\n",deleted->data);

				if(replacement == NULL || replacement->color == RED)
					return 0;

				else{
					printf("Replacement %d = RED\n",replacement->data);
					replacement->color = RED;
					FixingDeletion(root,&Zptr);
							
				}	
			}	

			else{
				printf("deleted %d == BLACK\n",deleted->data);
				if(replacement == NULL || replacement->color == BLACK){
					printf("Fixing\n");
					FixingDeletion(root,&Zptr);
				}

				else{
					printf("4\n");
					printf("Replacement %d = BLACK\n",replacement->data);
					replacement->color = BLACK;
				}	
			}	
			
			(*root)->color = BLACK;
			return 1;
		}
		
		else{
			int index;
			
			if(data > (*aux)->data)
				index = 1;

			else{
				index = 0;
			}	
				
			(*aux)->dir = index;

			if((*aux)->branch[index] != NULL)
				(*aux)->branch[index]->parent = (*aux);

			int x = deletionRB(root,&(*aux)->branch[index],data);

			if(*aux == *root){
				(*root)->parent = NULL;
				(*root)->color = BLACK;
			}	

			return x;
		}	
	}	
}	

int FixingDeletion(RB** root, RB** Zptr){
	printf("Fixing Deletion\n");
	RB* Xptr, *Wptr;

	
	printf("Z: %d \n",(*Zptr)->data); 
	
	Xptr = (*Zptr)->branch[(*Zptr)->dir];

	while(1){
		int x = VerificaRegras(*root,*root);

		
		if(Xptr != NULL && Xptr->color == RED){
			printf("Case 0\n");
			Xptr->color = BLACK;
			break;
		}

		else{
			printf("Zptr: %d\n",(*Zptr)->data);
			
			if((*Zptr)->dir == 0){ 
				printf("Zptr->dir == 0\n");
				Xptr = (*Zptr)->branch[0];
				Wptr = (*Zptr)->branch[1];
				
				if(Xptr != NULL)
					printf("X left: %d Color: %d\n",Xptr->data,Xptr->color);

				if(Wptr != NULL)
					printf("W right: %d\n",Wptr->data);	
				
				
				
				if(Wptr == NULL){
					
					break;
				}	

				if(Wptr != NULL && Wptr->color == RED){
					Wptr->color = BLACK;
					(*Zptr)->color = RED;

					(*Zptr)->branch[1] = Wptr->branch[0];
					Wptr->branch[0] = *Zptr;

					if(*Zptr == *root){
						Wptr->parent = NULL;
						*root = Wptr;
						(*Zptr)->parent = Wptr;

						*Zptr = *root;

					}

					else{
						Wptr->parent = (*Zptr)->parent;
						(*Zptr)->parent->branch[(*Zptr)->parent->dir] = Wptr;
						(*Zptr)->parent = Wptr;	

						*Zptr = Wptr->parent;
					}	
					
					(*Zptr)->dir = 0;
						
					Xptr = (*Zptr)->branch[0];
					Wptr = (*Zptr)->branch[1]; 
					printf("Case 1 Zptr = %d\n",(*Zptr)->data);

					if(Wptr == NULL) 
						break;

				}	

				
				if(Wptr->branch[0] == NULL)
					printf("0 NULL\n");

				if(Wptr->branch[1] == NULL)
					printf("1 NULL \n");	

				if(((!Wptr->branch[0]) || (Wptr->branch[0]->color == BLACK)) && ((!Wptr->branch[1]) || (Wptr->branch[1]->color == BLACK))){ 
					printf("Case 2\n");
					Wptr->color = RED;

					if(*Zptr == *root) 
						break;
					(*Zptr)->parent->dir = 0;


					(*Zptr) = (*Zptr)->parent;
					Xptr = (*Zptr)->branch[0];
					Wptr = (*Zptr)->branch[1]; 
				}	
				else{
					printf("case 3 // 4\n");

					if(Wptr->branch[0] != NULL && Wptr->branch[0]->color == RED){
						printf("Case 3\n");
						RB* LeftChild = Wptr->branch[0];

						LeftChild->color = BLACK;
						Wptr->color = RED;

						printf("Wptr: %d || LeftChild: %d\n",Wptr->data,LeftChild->data);	

						Wptr->branch[0] = LeftChild->branch[1];
						LeftChild->branch[1] = Wptr;

						Wptr->parent = LeftChild;

						(*Zptr)->branch[1] = LeftChild;

						LeftChild->parent = (*Zptr);

						if(*Zptr == *root){ 
							*Zptr = *root;

						}
						else{
							*Zptr = (*Zptr)->parent;
							(*Zptr)->dir = 0;
						}

						Xptr = (*Zptr)->branch[0];
						Wptr = (*Zptr)->branch[1];

					}

					printf("Case 4\n");		
					Wptr->color = (*Zptr)->color;
					(*Zptr)->color = BLACK;
					Wptr->branch[1]->color = BLACK;

					if(Wptr->branch[0] != NULL)
						Wptr->branch[0]->parent = *Zptr;

					(*Zptr)->branch[1] = Wptr->branch[0];
					Wptr->branch[0] = *Zptr;	

					if((*Zptr) == *root){
						Wptr->parent = NULL;
						*root = Wptr;
						(*Zptr)->parent = Wptr;
					}	

					else{
						Wptr->parent = (*Zptr)->parent;
						(*Zptr)->parent->branch[(*Zptr)->parent->dir] = Wptr;
						(*Zptr)->parent = Wptr;
					}

					break;	
				}	

			}

			else{
				printf("Zptr->dir == 1\n");
					
					Xptr = (*Zptr)->branch[1];
				Wptr = (*Zptr)->branch[0];

				if(Xptr != NULL)
					printf("X right: %d\n",Xptr->data);

				if(Wptr != NULL)
					printf("W left: %d\n",Wptr->data);	

				if(Wptr == NULL) 
					break;

				if(Wptr != NULL && Wptr->color == RED){
					Wptr->color = BLACK;
					(*Zptr)->color = RED;

					(*Zptr)->branch[0] = Wptr->branch[1];
					Wptr->branch[1] = *Zptr;

					if(*Zptr == *root){
						Wptr->parent = NULL;
						*root = Wptr;
						(*Zptr)->parent = Wptr;

						*Zptr = *root;

					}

					else{
						Wptr->parent = (*Zptr)->parent;
						(*Zptr)->parent->branch[(*Zptr)->parent->dir] = Wptr;
						(*Zptr)->parent = Wptr;	

						*Zptr = Wptr->parent;
					}	
					
					(*Zptr)->dir = 1;
						
					Xptr = (*Zptr)->branch[1];
					Wptr = (*Zptr)->branch[0]; 
					printf("Case 1 Zptr = %d\n",(*Zptr)->data);

					if(Wptr == NULL) 
						break;

				}	

				
				if(Wptr->branch[0] == NULL)
					printf("0 NULL\n");

				if(Wptr->branch[1] == NULL)
					printf("1 NULL \n");	

				if(((!Wptr->branch[0]) || (Wptr->branch[0]->color == BLACK)) && ((!Wptr->branch[1]) || (Wptr->branch[1]->color == BLACK))){ //
					printf("Case 2\n");
					Wptr->color = RED;

					if(*Zptr == *root) 
						break;
					(*Zptr)->parent->dir = 1;
												

					(*Zptr) = (*Zptr)->parent;
					Xptr = (*Zptr)->branch[1];
					Wptr = (*Zptr)->branch[0];
				}	

				else{
					printf("case 3 // 4\n");
					
					if(Wptr->branch[1] != NULL && Wptr->branch[1]->color == RED){
						printf("Case 3\n");
						RB* RightChild = Wptr->branch[1];

						RightChild->color = BLACK;
						Wptr->color = RED;
						
						printf("Wptr: %d || RightChild: %d\n",Wptr->data,RightChild->data);	

						Wptr->branch[1] = RightChild->branch[0];
						RightChild->branch[0] = Wptr;

						Wptr->parent = RightChild;
							
						(*Zptr)->branch[0] = RightChild;
							
						RightChild->parent = (*Zptr);
						
						if(*Zptr == *root){ 
							*Zptr = *root;
							
						}
						else{
							*Zptr = (*Zptr)->parent;
							(*Zptr)->dir = 1;
						}

						Xptr = (*Zptr)->branch[1];
						Wptr = (*Zptr)->branch[0];

					}

					printf("Case 4\n");		
					Wptr->color = (*Zptr)->color;
					(*Zptr)->color = BLACK;
					Wptr->branch[0]->color = BLACK;

					if(Wptr->branch[1] != NULL)
						Wptr->branch[0]->parent = *Zptr;

					(*Zptr)->branch[0] = Wptr->branch[1];
					Wptr->branch[1] = *Zptr;	

					if((*Zptr) == *root){
						Wptr->parent = NULL;
						*root = Wptr;
						(*Zptr)->parent = Wptr;
					}	

					else{
						Wptr->parent = (*Zptr)->parent;
						(*Zptr)->parent->branch[(*Zptr)->parent->dir] = Wptr;
						(*Zptr)->parent = Wptr;
					}
						
					break;	

			}
		}

		}	
		
	}	

	return 1;
}	

int insertionRB(RB** root,RB** aux,int data){
	if(*root == NULL){
		*root = NewNode(data);
		(*root)->color = BLACK;
		return 1;
	}	

	else{
		if(*aux == NULL){
			return 1;
		}
		

		if(data == (*aux)->data){
			printf("Valor %d já existente na árvore!!!\n\n",data);
			return -1;
		}	
		
		int x,index;

		if(data > (*aux)->data)
			index = 1;

		else{
			index = 0;
		}	
		
		(*aux)->dir = index;
		
		if((*aux)->branch[index] != NULL){
			(*aux)->branch[index]->parent = *aux;
		}	

		x = insertionRB(root,&(*aux)->branch[index],data);
	
		if(x == 1){
			printf("data: %d || aux: %d \n",data,(*aux)->data);	
			(*aux)->branch[index] = NewNode(data);
			(*aux)->branch[index]->parent = *aux;

			RB* Avo, *Pai,*Tio ,*Xptr, *Yptr,*temp;
			Avo = (*aux)->parent;

			if((*aux)->color == BLACK)
				return 0;	
			
			while(Avo != NULL){
				printf("Avo: %d\n",Avo->data);
				Pai = Avo->branch[0];
				Tio = Avo->branch[1];
				
				if(Pai == NULL || Pai->color == BLACK)
					break;

				if(Tio == NULL || Tio->color == BLACK)
					break;

				if(Pai != NULL && Pai->color == RED){
					if(Tio != NULL && Tio->color == RED){	
						printf("Tio OK\n");
						Avo->color = RED;
						Tio->color = Pai->color = BLACK;

						if(Avo == *root){
							Avo->color = BLACK;
							return 0;
						}	

						else{
							printf("Pai: %d\n",Avo->parent->data);
							
							if(Avo->parent->parent == NULL)
								return 0;

							Avo = Avo->parent->parent;
						}	

					}	
				}	
			}

				if(Avo->dir == 0){
					printf("Avo: %d->dir == 0\n",Avo->data);
					
					temp = Avo->branch[0];

					if(temp->dir == 0)
						Yptr = temp;

					else{
						Xptr = temp;
						Yptr = Xptr->branch[1];
						Xptr->branch[1] = Yptr->branch[0];
						Yptr->branch[0] = Xptr;
						
						Xptr->parent = Yptr;

						Avo->branch[0] = Yptr;
					}	
					
					Avo->color = RED;
					Yptr->color = BLACK;

					Avo->branch[0] = Yptr->branch[1];
					Yptr->branch[1] = Avo;
					

					if(Avo == *root)
						*root = Yptr;

					else{
						temp = Avo->parent;
						temp->branch[temp->dir] = Yptr;
						Yptr->parent = temp;
					}	
					Avo->parent = Yptr;

				}

				else{
					printf("Avo: %d->dir == 1\n",Avo->data);

					temp = Avo->branch[1];
					

					if(temp->dir == 1)
						Yptr = temp;

					else{
						Xptr = temp;
						Yptr = Xptr->branch[0];
						Xptr->branch[0] = Yptr->branch[1];
						Yptr->branch[1] = Xptr;
						
						Xptr->parent = Yptr;

						Avo->branch[1] = Yptr;
						printf("Right 2.0\n");
					}	
					
					printf("Left 2.0\n");
					Avo->color = RED;
					Yptr->color = BLACK;

					Avo->branch[1] = Yptr->branch[0];
					Yptr->branch[0] = Avo;

					if(Avo == *root)
						*root = Yptr;

					else{
						temp = Avo->parent;
						temp->branch[temp->dir] = Yptr;
						Yptr->parent = temp;
					}
					Avo->parent = Yptr;

				}	
			}	
	
			


		
		(*root)->parent = NULL;
		(*root)->color = BLACK;



		return 0;	
	}	
}	

int balanco(RB* root,RB* rb){
	if(rb == NULL)
		return -1;

	int esq = balanco(root,rb->branch[0]);
	int dir = balanco(root,rb->branch[1]);

	if(rb == root){
		int diff = esq - dir;
	       return diff;	
	}	

	if(esq > dir)
		return esq+1;

	else{
		return dir+1;
	}	
}	

void InOrder(RB* rb){
	if(rb != NULL){
		InOrder(rb->branch[0]);
		printf("->%d(%c)",rb->data,rb->color == RED ? 'R' : 'B');
		InOrder(rb->branch[1]);
	}	
}	



RB* NewNode(int data){
	RB* new = (RB* ) calloc(1,sizeof(RB));
	new->color = RED;
	new->data = data;
	new->dir = 0;
	int i;
	new->parent = NULL;

	for(i = 0; i < 2; i++)
		new->branch[i] = NULL;


	return new;
}	
