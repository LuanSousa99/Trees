struct tree{
	int data;

	struct tree *esq;
	struct tree *dir;

};

typedef struct tree TREE;

void menu(int* o);
int RetornaValor();
int InsertNode(TREE** a,int v);
int PreOrder(TREE* a);
int InOrder(TREE* a);
int PosOrder(TREE* a);
int DeleteNode(TREE** a,int v);
int RetornaMaior(TREE** a);
