#define TAMANHO 4
#define GRAU 5

struct arvorenaria{
	int NrKeys;

	int keys[TAMANHO];
	struct arvorenaria* ponteiros[GRAU];

};	

typedef struct arvorenaria ARVORENARIA;

int buscaInsert(ARVORENARIA* root,int valor,ARVORENARIA** aux,int* j);
int InsertNaria(ARVORENARIA** root,int valor);
void ordenado(ARVORENARIA* an);
int buscaNo(ARVORENARIA* root,int valor,ARVORENARIA** aux,int* j);
void menu(int* o);
void defineValor(int* valor);
int DeleteNaria(ARVORENARIA** an,int v);
void PreOrder(ARVORENARIA* an);
ARVORENARIA* retornaPonteiro(ARVORENARIA* an,ARVORENARIA* aux,int* p);
int retornaMaior(ARVORENARIA** an,ARVORENARIA* root);
int buscaPrev(ARVORENARIA* root,int valor,ARVORENARIA** aux,ARVORENARIA** prev,int* j,int* i);
