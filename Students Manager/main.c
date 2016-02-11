//  main.c
//  Data Structure Project
//  Created by Ahmed Barakat on 140 / 20 / 14.
//  Copyright (c) 2014 Ahmed Barakat. All rights reserved.

// Ahmed Emad Barakat  ID: 2807

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Binary_Trees.h"

int main()
{
    // /Volumes/BOOTCAMP/students.txt
    TreeID *treeId1;
    TreeName *treeName1;
    int ch=-1;
    char path[100];
    do {
        int id;
        char name[size];
        ch = -1;
        printf("\nChoose Option:\n");
        printf("[1] Insert from File\n");
        printf("[2] Insert\n");
        printf("[3] Search by ID\n");
        printf("[4] Search by Name\n");
        printf("[5] Delete by ID\n");
        printf("[6] Delete by Name\n");
        printf("[7] Show InOrder\n");
        printf("[8] Show PreOrder\n");
        printf("[9] Show PostOrder\n");
        printf("[10] Size ?\n");
        printf("[11] Save ?\n");
        printf("[12] Exit\n");
        scanf("%d",&ch);
        //printf("Choice: %d\n", ch);
        if(ch==1)
        {
            int i, id, studentcounter=0;
            char temp[size];
            printf("Enter The Path of the File: ");
            scanf("%s", path);
            FILE *freader;
            freader = fopen(path,"r");
            if (freader != NULL){
                printf("\nFile exist !\n");
                while(!(feof(freader))){
                    fscanf(freader,"%[^,],%d]", temp, &id);
                    studentcounter++;
                    fscanf(freader, "\n");
                    i=0;
                    while (temp[i])
                    {
                        temp[i] = toupper(temp[i]);
                        i++;
                    }
                    Insert_BST(&treeId1, &treeName1, id, temp);
                }
                printf("Successfully loaded %d Student!\n", studentcounter);
            }
            else
                printf("Error reading file\n");
            fclose(freader);
        }
        else if(ch==2)
        {
            printf("Enter Name: ");
            getchar();
            gets(name);
            int i = 0, flag = 1;
            while (name[i])
            {
                if (!((name[i]>='A' && name[i]<='Z') || (name[i]>='a' && name[i]<='z') || name[i]==' '))
                    flag = 0;
                else
                    name[i] = toupper(name[i]);
                i++;
            }
            char idtemp[20];
            printf("Enter ID: ");
            scanf("%s", idtemp);
            for (int i = 0; i < strlen(idtemp); ++i)
            {
                if (!isdigit(idtemp[i]))
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                id = atoi(idtemp);
                Insert_BST(&treeId1, &treeName1, id, name);
            }
            else
                printf("UNValid Input\n");
        }
        else if(ch==3)
        {
            int flag=1;
            char idtemp[20];
            printf("Enter ID: ");
            scanf("%s", idtemp);
            for (int i = 0; i < strlen(idtemp); ++i)
            {
                if (!isdigit(idtemp[i]))
                {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                id = atoi(idtemp);
                struct NodeID *temp = SearchID(treeId1, id);
                if (temp)
                    printf("Found\nName: %s, ID: %d\n", temp->NamePtr->Name, temp->ID);
                else
                    printf("Not Found\n");
            }
            else
                printf("UNValid Input\n");
        }
        else if(ch==4)
        {
            printf("Enter Name: ");
            getchar();
            gets(name);
            int i = 0, flag = 1, num=0;
            while (name[i])
            {
                if (!((name[i]>='A' && name[i]<='Z') || (name[i]>='a' && name[i]<='z') || name[i]==' '))
                    flag = 0;
                else
                    name[i] = toupper(name[i]);
                i++;
            }
            if (flag)
            {
                SearchNameNum(treeName1, name, &num);
                if (!num)
                    printf("Not Found!\n");
            }
            else
                printf("UNValid Input\n");
        }
        else if(ch==5)
        {
            int flag=1;
            char idtemp[20];
            printf("Enter ID: ");
            scanf("%s", idtemp);
            for (int i = 0; i < strlen(idtemp); ++i)
            {
                if (!isdigit(idtemp[i]))
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                id = atoi(idtemp);
                struct NodeID *temp = SearchID(treeId1, id);
                if (temp)
                {
                    printf("Deleted Succesfully : %s, %d\n", temp->NamePtr->Name, temp->ID);
                    DeleteName(&treeName1, &treeId1, temp->NamePtr->Name, id);
                    DeleteID(&treeId1, &treeName1, temp->NamePtr->Name, id);
                }
                else
                    printf("Data Not Found!\n");
            }
            else
                printf("UNValid Input\n");
        }
        else if(ch==6)
        {
            printf("Enter Name: ");
            getchar();
            gets(name);
            int i = 0, flag = 1, num=0, ch2=0;;
            while (name[i])
            {
                if (!((name[i]>='A' && name[i]<='Z') || (name[i]>='a' && name[i]<='z') || name[i]==' '))
                    flag = 0;
                else
                    name[i] = toupper(name[i]);
                i++;
            }
            if (flag)
            {
                SearchNameNum(treeName1, name, &num);
                if (num == 0)
                    printf("Data Not Found!\n");
                else
                {
                    printf("Choose to delete:\n");
                    do {
                        scanf("%d", &ch2);
                    } while (ch2 <0 || ch2>num);
                }
                struct NodeName *temp = SearchNameRep(treeName1, name, ch2, flag);
                //struct NodeName *temp = SearchName(treeName1, name);
                if (temp)
                {
                    printf("Deleted Succesfully : %s, %d\n", temp->Name, temp->IDPtr->ID);
                    DeleteID(&treeId1, &treeName1, name, temp->IDPtr->ID);
                    DeleteName(&treeName1, &treeId1, name, temp->IDPtr->ID);
                }
            }
            else
                printf("UNValid Input\n");
        }
        else if(ch==7)
        {
            int ch2;
            do {
                ch2 = 0;
                printf("1.Show InOrder by Name\n2.Show InOrder by ID\n");
                scanf("%d", &ch2);
                if (ch2 == 1)
                    TraverseInorderName(treeName1);
                else if (ch2 == 2)
                    TraverseInorderID(treeId1);
                else
                {
                    getchar();
                    printf("Choose Valid Option\n");
                }
            } while (ch2 !=1 && ch2!=2);
        }
        else if(ch==8)
        {
            int ch2;
            do {
                ch2 = 0;
                printf("1.Show PreOrder by Name\n2.Show PreOrder by ID\n");
                scanf("%d", &ch2);
                if (ch2 == 1)
                    TraversePreorderName(treeName1);
                else if (ch2 == 2)
                    TraversePreorderID(treeId1);
                else
                {
                    getchar();
                    printf("Choose Valid Option\n");
                }
            } while (ch2 !=1 && ch2!=2);

        }
        else if(ch==9)
        {
            int ch2;
            do {
                ch2 = 0;
                printf("1.Show PostOrder by Name\n2.Show PostOrder by ID\n");
                scanf("%d", &ch2);
                if (ch2 == 1)
                    TraversePostorderName(treeName1);
                else if (ch2 == 2)
                    TraversePostorderID(treeId1);
                else
                {
                    getchar();
                    printf("Choose Valid Option\n");
                }
            } while (ch2 !=1 && ch2!=2);

        }
        else if(ch==10)
        {
            if (NodesID(treeId1) == NodesName(treeName1))
                printf("No. of Students are %d\n", NodesID(treeId1));
            else
                printf("Error!");
        }
        else if(ch==11)
        {
            int ch=0;
            do {
            printf("1.Save by Name\n2.Save by ID\n");
            scanf("%d", &ch);
            if (ch == 1)
                saveName(treeName1, path);
            else if (ch == 2)
                saveID(treeId1, path);
            else
            {
                getchar();
                printf("Choose Valid Option\n");
            }
            } while (ch !=1 && ch!=2);
            printf("Saved Successfully %d Students\n", NodesID(treeId1));
        }
        else if(ch==12)
        {
            break;
        }
        else
        {
            getchar();
            printf("\nChoose Valid Option!\n");
        }
    } while (ch != 12);
    return 0;
}