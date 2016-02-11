#ifndef Binary_Trees_Binary_Trees_h
#define Binary_Trees_Binary_Trees_h

#define size 50

struct NodeID
{
    int ID;
    struct NodeName *NamePtr;
    struct NodeID *left,*right;
};

struct NodeName
{
    char Name[size];
    struct NodeID *IDPtr;
    struct NodeName *left,*right;
};

typedef  struct NodeID TreeID;
typedef  struct NodeName TreeName;


struct NodeID * NewNodeID(int id, char name[size]);

void TraverseInorderID(TreeID *);

void TraversePostorderID(TreeID *);

void TraversePreorderID(TreeID *);

void TraverseInorderName(TreeName *);

void TraversePostorderName(TreeName *);

void TraversePreorderName(TreeName *);

int NodesID( TreeID* );

int NodesName( TreeName* );

void Insert_BST(TreeID **t, TreeName **n, int val, char name[size]);

void Insert_BST_Name(TreeName **t, TreeID **n, int val, char name[size], struct NodeName* node);

struct NodeID* SearchID(TreeID *, int);

void SearchNameNum(TreeName *t, char name[size], int *num);

struct NodeName* SearchNameRep(TreeName *t, char name[size], int num, int flag);

void SearchD_ID (TreeID **root, char name[size], int num, struct NodeID **par, struct NodeID **x, int *found);

void SearchD_Name (TreeName **root, char name[size], int num, struct NodeName **par, struct NodeName **x, int *found);

void DeleteID(TreeID **root, TreeName **n, char name[size], int num);

void DeleteName(TreeName **root, TreeID **n, char name[size], int num);

void saveID(TreeID *t, char path[]);

void saveName(TreeName *t, char path[]);

void saveprintIDIN(FILE *freader, TreeID *t );

void saveprintIDPre(FILE *freader, TreeID *t );

void saveprintIDPost(FILE *freader, TreeID *t );

void saveprintNameIN(FILE *freader, TreeName *t );

void saveprintNamePre(FILE *freader, TreeName *t );

void saveprintNamePost(FILE *freader, TreeName *t );



#endif