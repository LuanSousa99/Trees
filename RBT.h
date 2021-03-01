#define RED 1
#define BLACK 0


struct redblack{
	int color;
	int data;
	int dir;
	
	struct redblack *parent;
	struct redblack *branch[2];

};	


typedef struct redblack RB;

RB* NewNode(int data);
int insertionRB(RB** root,RB** aux,int data);
int deletionRB(RB** root,RB** aux,int data);
void InOrder(RB* rb);
int balanco(RB* root,RB* rb);
int FixingDeletion(RB** root,RB** Zptr);
int VerificaRegras(RB* root,RB* rb);
void DepthProperty(RB* rb,int caminhos[],int* tot,int b);
