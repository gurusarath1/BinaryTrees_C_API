#include <stdio.h>
#include <stdlib.h>
#define NO_VAL 0
#define NO_NODE_HEIGHT -1

typedef int DataType;
typedef struct NODE NODE;
typedef struct NODE {
    int Height;
    int Depth;
    NODE* Left;
    NODE* Right;
    NODE* Parent;
    DataType Value;

}NODE;

NODE Create_BT(DataType rootNodeValue);
int CompareNodes(NODE* a, NODE* b);
NODE Create_Node(DataType NodeValue, NODE* Left, NODE* Right, NODE* Parent, int Height);
int BST_insert(NODE* Parent, DataType ValueToInsert, int DepthNext);
int setNodeHeight(NODE* NODEX);
void updateHeightsOfAllNodesAbove(NODE* LeafNodeX);
void InOrderTraversal(NODE* root);
void PreOrderTraversal(NODE* root);
void PostOrderTraversal(NODE* root);

static NODE NO_NODE;

int main()
{
    NODE BT = Create_BT(5);
    NO_NODE.Height = NO_NODE_HEIGHT;

    printf("%d\n", BT.Value);

    BST_insert(&BT, 6, BT.Depth + 1);
    BST_insert(&BT, 3, BT.Depth + 1);
    BST_insert(&BT, 7, BT.Depth + 1);
    BST_insert(&BT, 10, BT.Depth + 1);
    BST_insert(&BT, 1, BT.Depth + 1);
    BST_insert(&BT, 2, BT.Depth + 1);
    BST_insert(&BT, 4, BT.Depth + 1);
    BST_insert(&BT, 9, BT.Depth + 1);

    printf("\n\n%d\n",BT.Height);

PreOrderTraversal(&BT);


    return 0;
}

int CompareNodes(NODE* a, NODE* b)
{
    if(a->Value > b->Value)
    {
        return 1;
    }
    else if(a->Value < b->Value)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int CompareValues(DataType* a, DataType* b)
{
    if( *a > *b )
    {
        return 1;
    }
    else if( *a < *b )
    {
        return -1;
    }
    else
    {
        return 0;
    }
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
    x.Left = &NO_NODE;
    x.Right = &NO_NODE;
    x.Parent = &NO_NODE;
    x.Value = rootNodeValue;
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




int BST_insert(NODE* Parent, DataType ValueToInsert, int DepthNext)
{
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
            printf("Left%d\n", ValueToInsert);
        } else {

            printf("Left -- ");
            BST_insert(Parent->Left, ValueToInsert, DepthNext+1);

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
            printf("Right%d\n", ValueToInsert);
        } else {
            printf("Right -- ");
            BST_insert(Parent->Right, ValueToInsert, DepthNext+1);

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

void InOrderTraversal(NODE* root)
{
    if(root->Left->Height != NO_NODE_HEIGHT)
    {
        InOrderTraversal(root->Left);
    }

    if(root->Height != NO_NODE_HEIGHT)
    {
        printf("%d", root->Value);
    }

    if(root->Right->Height != NO_NODE_HEIGHT)
    {
        InOrderTraversal(root->Right);
    }

}

void PreOrderTraversal(NODE* root)
{

    if(root->Height != NO_NODE_HEIGHT)
    {
        printf("%d", root->Value);
    }

    if(root->Left->Height != NO_NODE_HEIGHT)
    {
        InOrderTraversal(root->Left);
    }

    if(root->Right->Height != NO_NODE_HEIGHT)
    {
        InOrderTraversal(root->Right);
    }
}

void PostOrderTraversal(NODE* root)
{
    if(root->Left->Height != NO_NODE_HEIGHT)
    {
        InOrderTraversal(root->Left);
    }

    if(root->Right->Height != NO_NODE_HEIGHT)
    {
        InOrderTraversal(root->Right);
    }

    if(root->Height != NO_NODE_HEIGHT)
    {
        printf("%d", root->Value);
    }
}
