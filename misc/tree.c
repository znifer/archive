#include "nice_tree.h"
#include <stdio.h>
#include <stdlib.h>

const short TreeOk = 0;
const short TreeNotMem = 1;
const short TreeUnder = 2;
short TreeError;

void CreateNode(NodePtr *T){
    if (TreeError != TreeOk) return;
    NodePtr newel;
    newel = malloc(sizeof(Node));
    if (newel == NULL)
    {
        TreeError = TreeNotMem;
        return;
    }
    newel->h = 0;
    newel->LSon = NULL;
    newel->RSon = NULL;
    *T = newel;
    TreeError = TreeOk;
}

void InitTree(Root *T)
{
    if (TreeError != TreeOk) return;
    *T = malloc(sizeof(NodePtr));
    CreateNode(*T);
}

void WriteDataTree(NodePtr T, BaseType E)
{
    if (TreeError != TreeOk) return;
    T->Data = E;
}

void ReadDataTree(NodePtr T, BaseType *E)
{
    if (TreeError != TreeOk) return;
    *E = T->Data;
}

int IsLSon(NodePtr T)
{
    if (TreeError != TreeOk) return -1;
    return T->LSon != NULL;
}

int IsRSon(NodePtr T)
{
    if (TreeError != TreeOk) return -1;
    return T->RSon != NULL;
}

void MoveToLSon(NodePtr T, NodePtr *TS)
{
    if (TreeError != TreeOk) return;
    if (!IsLSon(T))
    {
        TreeError = TreeUnder;
        return;
    }
    *TS = T->LSon;
}

void MoveToRSon(NodePtr T, NodePtr *TS)
{
    if (TreeError != TreeOk) return;
    if (!IsRSon(T))
    {
        TreeError = TreeUnder;
        return;
    }
    *TS = T->RSon;
}

int IsEmptyTree(NodePtr T)
{
    if (TreeError != TreeOk) return -1;
    return T->LSon == NULL && T->RSon == NULL;
}

void DelTree(NodePtr T)
{
    free(T);
}
