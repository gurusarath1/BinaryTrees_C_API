#include <stdio.h>
#include <stdlib.h>
#define NO_VAL 0
#define NO_NODE_HEIGHT -1
#define ACTIVATED 1
#define DEACTIVATED 0
#define __DebugMode__ if(DebugModeState)

typedef int DataType;
typedef struct NODE NODE;
struct NODE {
    int Height;
    int Depth;
    int TotalNumberOfNodes;
    NODE* Left;
    NODE* Right;
    NODE* Parent;
    DataType Value;

};

typedef enum DIRECTION
{
    LEFT = 0,
    RIGHT,
    UP,
    DOWM,
}DIRECTION;

NODE Create_BT(DataType rootNodeValue);
int CompareNodes(NODE* a, NODE* b);
NODE Create_Node(DataType NodeValue, NODE* Left, NODE* Right, NODE* Parent, int Height);
int BST_insert(NODE* Parent, DataType ValueToInsert);
int setNodeHeight(NODE* NODEX);
void updateHeightsOfAllNodesAbove(NODE* LeafNodeX);
void InOrderTraversal(NODE* root, DataType* aryX);
void PreOrderTraversal(NODE* root, DataType* aryX);
void PostOrderTraversal(NODE* root, DataType* aryX);
DataType* createArrayForTraversal(NODE* root);
void insertInGlobalArray(DataType* aryX, DataType val, int resetIndex);

void L_rotate(NODE* nodeX, DIRECTION aboutNodeOn);

static NODE NO_NODE;
static int DebugModeState = ACTIVATED;

int main()
{
    NODE BT = Create_BT(5);


    BST_insert(&BT, 6);
    BST_insert(&BT, 3);
    BST_insert(&BT, 7);
    BST_insert(&BT, 10);
    BST_insert(&BT, 1);
    BST_insert(&BT, 2);
    BST_insert(&BT, 24);
    BST_insert(&BT, 9);
    BST_insert(&BT, 9);
    BST_insert(&BT, 15);

    DataType* aryX = createArrayForTraversal(&BT);
    insertInGlobalArray(0,0,1);
    InOrderTraversal(&BT, aryX);

    for(int i=0; i<11; i++)
    {
        printf("%d   ", aryX[i]);
    }


    return 0;
}

int CompareNodes(NODE* a, NODE* b)
{
    if(a->Value > b->Value)
        return 1;
    else if(a->Value < b->Value)
        return -1;
    else
        return 0;
}

int CompareValues(DataType* a, DataType* b)
{
    if( *a > *b )
        return 1;
    else if( *a < *b )
        return -1;
    else
        return 0;
}


int setNodeHeight(NODE* NodeX)
{
    int H = 0;
    int H_left = NodeX->Left->Height;
    int H_right = NodeX->Right->Height;

    if(H_right >= H_left)
    {
        H = H_right + 1;
    } else {
        H = H_left + 1;
    }

    NodeX->Height = H;
    return H;
}




NODE Create_BT(DataType rootNodeValue)
{
    NODE x;

    NO_NODE.Height = NO_NODE_HEIGHT;

    x.Left = &NO_NODE;
    x.Right = &NO_NODE;
    x.Parent = &NO_NODE;
    x.Value = rootNodeValue;
    x.TotalNumberOfNodes = 0;
    setNodeHeight(&x);
    x.Depth = 0;

    return x;
}




NODE Create_Node(DataType NodeValue, NODE* Left, NODE* Right, NODE* Parent, int Height)
{
    NODE x;
    x.Left = Left;
    x.Right = Right;
    x.Parent = Parent;
    x.Value = NodeValue;
    setNodeHeight(&x);

    return x;
}




int BST_insert(NODE* Parent, DataType ValueToInsert)
{
    Parent->TotalNumberOfNodes += 1;
    int DepthNext = Parent->Depth + 1;

    if( CompareValues(&(Parent->Value), &ValueToInsert) > 0 )
    {
        if(Parent->Left == &NO_NODE)
        {
            NODE* NewLeftNodeToInsert = (NODE*) malloc(sizeof(NODE));;
            NewLeftNodeToInsert->Value = ValueToInsert;
            NewLeftNodeToInsert->Parent = Parent;
            NewLeftNodeToInsert->Left = &NO_NODE;
            NewLeftNodeToInsert->Right = &NO_NODE;
            NewLeftNodeToInsert->Depth = DepthNext;
            setNodeHeight(NewLeftNodeToInsert);
            Parent->Left = NewLeftNodeToInsert;
            updateHeightsOfAllNodesAbove(Parent->Left);

            __DebugMode__
            printf("Left%d\n", ValueToInsert);
        } else {

            __DebugMode__
            printf("Left -- ");
            BST_insert(Parent->Left, ValueToInsert);

        }
    }
    else
    {
        if(Parent->Right == &NO_NODE)
        {
            NODE* NewRightNodeToInsert = (NODE*) malloc(sizeof(NODE));
            NewRightNodeToInsert->Value = ValueToInsert;
            NewRightNodeToInsert->Parent = Parent;
            NewRightNodeToInsert->Left = &NO_NODE;
            NewRightNodeToInsert->Right = &NO_NODE;
            NewRightNodeToInsert->Depth = DepthNext;
            setNodeHeight(NewRightNodeToInsert);
            Parent->Right = NewRightNodeToInsert;
            updateHeightsOfAllNodesAbove(Parent->Right);

            __DebugMode__
            printf("Right%d\n", ValueToInsert);
        } else {
            __DebugMode__
            printf("Right -- ");
            BST_insert(Parent->Right, ValueToInsert);

        }
    }
}

void updateHeightsOfAllNodesAbove(NODE* LeafNodeX)
{
    if(LeafNodeX->Parent->Height != NO_NODE_HEIGHT)
    {
        setNodeHeight(LeafNodeX->Parent);
        updateHeightsOfAllNodesAbove(LeafNodeX->Parent);
    }
}

void InOrderTraversal(NODE* root, DataType* aryX)
{
    if(root->Left->Height != NO_NODE_HEIGHT)
    {
        InOrderTraversal(root->Left, aryX);
    }

    if(root->Height != NO_NODE_HEIGHT)
    {
        __DebugMode__
        printf("%d  Height: %d  Depth: %d  NumNodes: %d\n", root->Value, root->Height, root->Depth, root->TotalNumberOfNodes);
        insertInGlobalArray(aryX, root->Value, 0);
    }

    if(root->Right->Height != NO_NODE_HEIGHT)
    {
        InOrderTraversal(root->Right, aryX);
    }

}

void PreOrderTraversal(NODE* root, DataType* aryX)
{

    if(root->Height != NO_NODE_HEIGHT)
    {
        __DebugMode__
        printf("%d  Height: %d  Depth: %d  NumNodes: %d\n", root->Value, root->Height, root->Depth, root->TotalNumberOfNodes);
        insertInGlobalArray(aryX, root->Value, 0);
    }

    if(root->Left->Height != NO_NODE_HEIGHT)
    {
        PreOrderTraversal(root->Left, aryX);
    }

    if(root->Right->Height != NO_NODE_HEIGHT)
    {
        PreOrderTraversal(root->Right, aryX);
    }
}

void PostOrderTraversal(NODE* root, DataType* aryX)
{
    if(root->Left->Height != NO_NODE_HEIGHT)
    {
        PostOrderTraversal(root->Left, aryX);
    }

    if(root->Right->Height != NO_NODE_HEIGHT)
    {
        PostOrderTraversal(root->Right, aryX);
    }

    if(root->Height != NO_NODE_HEIGHT)
    {
        __DebugMode__
        printf("%d  Height: %d  Depth: %d  NumNodes: %d\n", root->Value, root->Height, root->Depth, root->TotalNumberOfNodes);
        insertInGlobalArray(aryX, root->Value, 0);
    }
}

DataType* createArrayForTraversal(NODE* root)
{
    __DebugMode__
    printf("array size created = %d \n", root->TotalNumberOfNodes);
    return (DataType*)malloc(root->TotalNumberOfNodes * sizeof(DataType));
}

void insertInGlobalArray(DataType* aryX, DataType val, int resetIndex)
{
    static int index = 0;

    if(resetIndex)
    {
        index = 0;

    } else {

        aryX[index] = val;
        index += 1;

    }

}

// AVL -------------------


void Left_rotate(NODE* nodeX)
{
    nodeX->Parent->Right = nodeX->Right;
    nodeX->Right->Left = nodeX;
    nodeX->Right->Parent = nodeX->Parent;
    nodeX->Parent = nodeX->Right;
    nodeX->Right = &NO_NODE;
}

void Right_rotate(NODE* nodeX)
{
    nodeX->Parent->Left = nodeX->Left;
    nodeX->Left->Right = nodeX;
    nodeX->Left->Parent = nodeX->Parent;
    nodeX->Parent = nodeX->Left;
    nodeX->Left = &NO_NODE;
}

void RL_rotate(NODE* nodeX)
{
    Right_rotate(nodeX->Right);
    Left_rotate(nodeX);
}

void LR_rotate(NODE* nodeX)
{
    Left_rotate(nodeX->Left);
    Right_rotate(nodeX);
}

int BalanceFactor(NODE* nodeX)
{
    return (nodeX->Left->Height - nodeX->Right->Height);
}




