struct avl{
	int info;
	int bf;

	struct avl *galhos[2];
};

typedef struct avl AVL;

int InsertAVL(AVL** avl,int valor);
int altura(AVL* avl);
void PreOrder(AVL* avl,int* contador);
int BalanceFactor(AVL** avl);
int rotacaoDIR(AVL** avl);
int rotacaoESQ(AVL** avl);
void DefineValor(int* v);
void menu(int* o);
int DeleteAVL(AVL** avl,AVL** root,int valor);
int buscaDelete(AVL** aux,AVL** ant,int valor);
int retornaMaior(AVL** aux,int* x);


