#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Binary_Trees.h"

struct NodeID * NewNodeID(int id, char name[size])
{
    struct NodeID* n;
    n=malloc(sizeof(struct NodeID));
    n->ID = id;
    n->NamePtr = malloc(sizeof(struct NodeName));
    n->NamePtr->IDPtr = n;
    strcpy(n->NamePtr->Name, name);
    n->NamePtr->right = NULL;
    n->NamePtr->left = NULL;
    n->left=NULL;
    n->right=NULL;
    return n;
}

void TraversePreorderID(TreeID *t)
{
    if (t)
    {
        printf("%s, %d\n",t->NamePtr->Name, t->ID);
        TraversePreorderID(t->left);
        TraversePreorderID(t->right);
    }
}

void TraversePostorderID(TreeID *t)
{
    if (t)
    {
        TraversePostorderID(t->left);
        TraversePostorderID(t->right);
        printf("%s, %d\n",t->NamePtr->Name, t->ID);
    }
}

void TraverseInorderID(TreeID *t)
{
    if (t)
    {
        TraverseInorderID(t->left);
        printf("%s, %d\n",t->NamePtr->Name, t->ID);
        TraverseInorderID(t->right);
    }
}

void TraversePreorderName(TreeName *t)
{
    if (t)
    {
        printf("%s, %d\n",t->Name, t->IDPtr->ID);
        TraversePreorderName(t->left);
        TraversePreorderName(t->right);
    }
}

void TraversePostorderName(TreeName *t)
{
    if (t)
    {
        TraversePostorderName(t->left);
        TraversePostorderName(t->right);
        printf("%s, %d\n",t->Name, t->IDPtr->ID);
    }
}

void TraverseInorderName(TreeName *t)
{
    if (t)
    {
        TraverseInorderName(t->left);
        printf("%s, %d\n",t->Name, t->IDPtr->ID);
        TraverseInorderName(t->right);
    }
}

int NodesID(TreeID* t)
{
    if (!t)
        return 0;
    return 1+NodesID(t->left)+NodesID(t->right);
}

int NodesName(TreeName* t)
{
    if (!t)
        return 0;
    return 1+NodesName(t->left) + NodesName(t->right);
}

void Insert_BST(TreeID **t, TreeName **n, int val, char name[size])
{
    int flag = 0;
    struct NodeID *root=*t;
    struct NodeID *temp = root;
    if (!root)
    {
        *t = temp = NewNodeID(val, name);
        flag = 1;
    }
    else if (val<root->ID)
    {
        if (!root->left)
        {
            root->left = temp = NewNodeID(val, name);
            flag = 1;
        }
        else
            Insert_BST(&root->left, n, val, name);
        
    }
    else if (val>root->ID)
    {
        if (!root->right)
        {
            root->right = temp = NewNodeID(val, name);
            flag = 1;
        }
        else
            Insert_BST(&root->right, n, val, name);
    }
    else
    {
        printf("Error Same ID Found!\n");
        flag = 0;
        return ;
    }
    if (flag)
        Insert_BST_Name(n, t, val, name, temp->NamePtr);
}

void Insert_BST_Name(TreeName **t, TreeID **n, int val, char name[size], struct NodeName* node)
{
    struct NodeName *root=*t;
    if (!root)
        *t=node;
    else if (strcmp(name, root->Name) < 0)
    {
        if (!root->left)
            root->left = node;
        else Insert_BST_Name(&root->left, n, val, name, node);
    }
    else if (strcmp(name, root->Name) >= 0)
    {
        if (!root->right)
            root->right = node;
        else
            Insert_BST_Name(&root->right, n, val, name, node);
    }
}

struct NodeID* SearchID(TreeID *t, int val)
{
    if (!t)
        return NULL;
    else if (t->ID==val)
        return  t;
    else if (val < t->ID)
        return SearchID(t->left,val);
    else
        return SearchID(t->right,val);
}

void SearchNameNum(TreeName *t, char name[size], int *num)
{
    if (!t)
        return ;
    if (strcmp(name, t->Name) == 0)
    {
        *num = *num+1;
        printf("%d. %s,%d\n", *num, t->Name, t->IDPtr->ID);
    }
    SearchNameNum(t->left, name, num);
    SearchNameNum(t->right, name, num);
}

struct NodeName* SearchNameRep(TreeName *t, char name[size], int num, int flag)
{
    if (!t)
        return NULL;
    if (strcmp(name, t->Name) == 0 && num==flag)
        return  t;
    if (strcmp(name, t->Name) == 0)
        flag++;
    if (strcmp(name, t->Name) < 0)
        return SearchNameRep(t->left, name, num, flag);
    else
        return SearchNameRep(t->right, name, num, flag);
}

void SearchD_ID (TreeID **root, char name[size], int num, struct NodeID **par, struct NodeID **x, int *found)
{
    struct NodeID *q;
    q = *root;
    *found = 0;
    *par = NULL;
    while ( q )
    {
        if ( q->ID == num && strcmp(name, q->NamePtr->Name)==0)
        {
            *found = 1;
            *x = q;
            return;
        }
        *par = q;
        if ( num < q->ID )
            q = q->left;
        else
            q = q->right;
    }
}

void SearchD_Name (TreeName **root, char name[size], int num, struct NodeName **par, struct NodeName **x, int *found)
{
    struct NodeName *q;
    q = *root;
    *found = 0;
    *par = NULL;
    while ( q )
    {
        if (strcmp(name, q->Name) == 0 && q->IDPtr->ID==num)
        {
            *found = 1;
            *x = q;
            return;
        }
        *par = q ;
        if ( strcmp(name, q->Name) < 0 )
            q = q->left;
        else
            q = q->right;
    }
}

void DeleteID(TreeID **root, TreeName **n, char name[size], int num)
{
    int found ;
    struct NodeID *parent, *x, *xsucc;
    if ( *root == NULL )
    {
        printf ( "Tree is empty\n" ) ;
        return ;
    }
    parent = x = NULL ;
    SearchD_ID (root, name, num, &parent, &x, &found);
    if ( found == 0 )
    {
        printf ( "Data to be deleted, not found\n" ) ;
        return ;
    }
    if ( x->left && x->right )
    {
        parent = x ;
        xsucc = x -> right;
        while (xsucc->left)
        {
            parent = xsucc;
            xsucc = xsucc->left;
        }
        x->ID = xsucc->ID;
        x->NamePtr = xsucc->NamePtr;
        xsucc->NamePtr->IDPtr = x;
        x = xsucc;
    }
    if ( !x->left && !x->right )
    {
        if (parent)
        {
            if ( parent->right == x )
                parent->right = NULL ;
            else
                parent->left = NULL ;
        }
        else
            *root = NULL;
        free(x);
        return ;
    }
    if ( !x->left && x->right )
    {
        if (parent)
        {
            if ( parent->left == x )
                parent->left = x->right;
            else
                parent->right= x->right;
        }
        else
            *root = x->right;
        free(x) ;
        return ;
    }
    if ( x->left && !x->right )
    {
        if (parent)
        {
            if ( parent->left== x )
                parent->left = x->left;
            else
                parent->right= x->left;
        }
        else
            *root = x->left;
        free(x);
        return ;
    }
}

void DeleteName(TreeName **root, TreeID **n, char name[size], int num)
{
    int found;
    struct NodeName *parent, *x, *xsucc;
    if ( *root == NULL )
    {
        printf ( "Tree is empty\n" ) ;
        return ;
    }
    parent = x = NULL ;
    SearchD_Name (root, name, num, &parent, &x, &found);
    if ( found == 0 )
    {
        printf ( "Data to be deleted, not found\n" ) ;
        return ;
    }
    if ( x->left && x->right )
    {
        parent = x ;
        xsucc = x -> right;
        while (xsucc->left)
        {
            parent = xsucc;
            xsucc = xsucc->left;
        }
        x->IDPtr = xsucc->IDPtr;
        strcpy(x->Name, xsucc->Name);
        xsucc->IDPtr->NamePtr = x;
        x = xsucc;
    }
    if ( !x->left && !x->right )
    {
        if (parent)
        {
            if ( parent->right == x )
                parent->right = NULL ;
            else
                parent->left = NULL ;
        }
        else
            *root = NULL;
        free(x);
        return ;
    }
    if ( !x->left && x->right )
    {
        if (parent)
        {
            if ( parent->left == x )
                parent->left = x->right;
            else
                parent->right= x->right;
        }
        else
        {
            *root = x->right;
        }
        free(x) ;
        return ;
    }
    if ( x->left && !x->right )
    {
        if (parent)
        {
            if ( parent->left== x )
                parent->left = x->left;
            else
                parent->right= x->left;
        }
        else
            *root = x->left;
        free(x);
        return ;
    }
}

void saveID(TreeID *t, char path[])
{
    if(!t)
        return ;
    else
    {
        FILE * freader;
        freader = fopen(path,"w");
        int ch;
        do {
            ch = 0;
            printf("1.Save InOrder\n2.Save PreOrder\n3.Save PostOrder\n");
            scanf("%d", &ch);
            if (ch == 1)
                saveprintIDIN(freader, t);
            else if (ch == 2)
                saveprintIDPre(freader, t);
            else if (ch==3)
                saveprintIDPost(freader, t);
            else
            {
                getchar();
                printf("Choose Valid Option\n");
            }
        } while (ch !=1 && ch!=2 && ch!=3);
        fclose(freader);
    }
}

void saveName(TreeName *t, char path[])
{
    if(!t)
        return ;
    else
    {
        FILE * freader;
        freader = fopen(path,"w");
        int ch;
        do {
            ch = 0;
            printf("1.Save InOrder\n2.Save PreOrder\n3.Save PostOrder\n");
            scanf("%d", &ch);
            if (ch == 1)
                saveprintNameIN(freader, t);
            else if (ch == 2)
                saveprintNamePre(freader, t);
            else if (ch==3)
                saveprintNamePost(freader, t);
            else
            {
                getchar();
                printf("Choose Valid Option\n");
            }
        } while (ch !=1 && ch!=2 && ch!=3);
        fclose(freader);
    }
}

void saveprintIDIN(FILE *freader, TreeID *t )
{
    if (freader && t)
    {
        saveprintIDIN(freader, t->left);
        fprintf(freader,"%s,%d\n", t->NamePtr->Name, t->ID);
        saveprintIDIN(freader, t->right);
    }
}

void saveprintIDPre(FILE *freader, TreeID *t )
{
    if (freader && t)
    {
        fprintf(freader,"%s,%d\n", t->NamePtr->Name, t->ID);
        saveprintIDPre(freader, t->left);
        saveprintIDPre(freader, t->right);
    }
}

void saveprintIDPost(FILE *freader, TreeID *t )
{
    if (freader && t)
    {
        saveprintIDPost(freader, t->left);
        saveprintIDPost(freader, t->right);
        fprintf(freader,"%s,%d\n", t->NamePtr->Name, t->ID);
    }
}



void saveprintNameIN(FILE *freader, TreeName *t )
{
    if (freader && t)
    {
        saveprintNameIN(freader, t->left);
        fprintf(freader,"%s,%d\n", t->Name, t->IDPtr->ID);
        saveprintNameIN(freader, t->right);
    }
}

void saveprintNamePre(FILE *freader, TreeName *t )
{
    if (freader && t)
    {
        fprintf(freader,"%s,%d\n", t->Name, t->IDPtr->ID);
        saveprintNamePre(freader, t->left);
        saveprintNamePre(freader, t->right);
    }
}

void saveprintNamePost(FILE *freader, TreeName *t )
{
    if (freader && t)
    {
        saveprintNamePost(freader, t->left);
        saveprintNamePost(freader, t->right);
        fprintf(freader,"%s,%d\n", t->Name, t->IDPtr->ID);
    }
}