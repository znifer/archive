#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

extern const short TreeOk;
extern const short TreeNotMem;
extern const short TreeUnder;
extern short TreeError;
typedef	int BaseType;
typedef struct Node *NodePtr;
typedef struct Node //узел дерева
{
    BaseType Data;  //блок даных узла
    unsigned h;     //высота поддерева с корнев в узле
    NodePtr LSon;   //указатель на левого сына
    NodePtr RSon;   //указатеь на правого сына
} Node;
typedef NodePtr *Root;

void InitTree(Root *T);                     //инициализация дерева
void CreateNode(NodePtr *T);                //создание узла
void WriteDataTree(NodePtr T, BaseType E);  //запись данных
void ReadDataTree(NodePtr T, BaseType *E);  //чтение данных
int  IsLSon(NodePtr T);                     //1 — есть левый сын, 0 — нет
int  IsRSon(NodePtr T);                     //1 — есть правый сын, 0 — нет
void MoveToLSon(NodePtr T, NodePtr *TS);    /*перейти к левому сыну, где T — адрес текущей вершины,
                                                TS — адрес левого поддерева(левого сына)*/
void MoveToRSon(NodePtr T, NodePtr *TS);    //перейти к правому сыну
int  IsEmptyTree(NodePtr T);                //1 — пустое дерево,0 — не пустое
void DelTree(NodePtr T);                    //удаление листа

#endif // TREE_H_INCLUDED
