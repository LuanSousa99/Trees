#define G 2

struct btree{
	int NumK;
	
	int keys[(2*G)-1];

	struct btree* ponteiros[2*G];
	int leaf;	

};	

typedef struct btree BTREE;

int InsertBT(BTREE** bt,int valor);
int InsertKey(BTREE** bt,int valor);
int repartir(BTREE** bt,int j);
int NewNode(BTREE** bt);
void PreOrder(BTREE* bt);
int altura(BTREE* bt);
int InOrder(BTREE* bt);
