#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////////////////////////////////////////////////////////////////
typedef struct NODE 
{

    //관리 대상 자료
    char szData[64];

    //자료구조
    struct NODE* parent;
    struct NODE* left;
    struct NODE* right;

} NODE;

NODE* g_pRoot;
int g_nSize;


///////////////////////////////////////////////////////////////////
int GetSize(void)
{
    return g_nSize;
}

///////////////////////////////////////////////////////////////////
int GetLength(void)
{
    return GetSize();
}

///////////////////////////////////////////////////////////////////
int IsEmpty()
{
    return GetSize();
}

///////////////////////////////////////////////////////////////////
void ReleaseTree(NODE* pParent)
{
    if (pParent == NULL)
        return;

    ReleaseTree(pParent->left);
    ReleaseTree(pParent->right);

    printf("free(): %p, %s\n", pParent, pParent->szData);
    free(pParent);
    g_pRoot = NULL;
}

///////////////////////////////////////////////////////////////////
void PrintTree(NODE* pParent)
{
    if (pParent == NULL)
        return;

    PrintTree(pParent->left);

    printf("[%p] %p, %s [%p]\n", 
        pParent->left, 
        pParent, pParent->szData, 
        pParent->right);

    PrintTree(pParent->right);

    return;
}

///////////////////////////////////////////////////////////////////
int InsertNode(const char *pszData)
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    strcpy(pNewNode->szData, pszData);

    if (g_pRoot == NULL)
    {
        g_pRoot = pNewNode;
        return 1;
    }

    NODE* pTmp = g_pRoot;
    while (pTmp != NULL)
    {
    //비교
        if (strcmp(pTmp->szData, pNewNode->szData) > 0)
        {
            //left
            if (pTmp->left == NULL)
            {
                pTmp->left = pNewNode;
                pNewNode->parent = pTmp;
                break;
            }
            else
            {
                pTmp = pTmp->left;
                continue;
            }
        }
        else
        {
            //right
            if (pTmp->right == NULL)
            {
                pTmp->right = pNewNode;
                pNewNode->parent = pTmp;
                break;
            }
            else
            {
                pTmp = pTmp->right;
                continue;
            }
        }
    }

    return 1;
}

///////////////////////////////////////////////////////////////////
NODE* FindNode(const char* pszData)
{
    NODE* pTmp = g_pRoot;

    while (pTmp != NULL)
    {
        if (strcmp(pTmp->szData, pszData) == 0)
            return pTmp;
        else if (strcmp(pTmp->szData, pszData) > 0)
        {
            //left
            pTmp = pTmp->left;
            continue;
        }
        else
        {
            //right
            pTmp = pTmp->right;
            continue;
        }
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////
int DeleteNode(const char* pszData)
{
    NODE* pDelete = FindNode(pszData);
    if (pDelete == NULL)   
    {
        printf("Not found\n");
        return 1;
    }

    //삭제할 데이터가 g_pRoot인 경우
    

    pDelete->parent = NULL;

    printf("Delete: %s [%p]\n", pszData, pDelete);
    free(pDelete);
    return 0;
}



///////////////////////////////////////////////////////////////////
int main(void)
{
    InsertNode("5번 항목");
    InsertNode("4번 항목");
    InsertNode("7번 항목");
    InsertNode("6번 항목");
    InsertNode("8번 항목");
    InsertNode("1번 항목");
    InsertNode("3번 항목");
    InsertNode("0번 항목");
    InsertNode("2번 항목");
    InsertNode("9번 항목");


    PrintTree(g_pRoot);

    NODE* pNode = FindNode("5번 항목");
    if (pNode == NULL)
        printf("Not found\n");
    else   
        printf("FindNode(): %s [%p]\n", pNode->szData, pNode);

    pNode = FindNode("9번 항목");
    if (pNode == NULL)
        printf("Not found\n");
    else   
        printf("FindNode(): %s [%p]\n", pNode->szData, pNode);

    pNode = FindNode("0번 항목");
    if (pNode == NULL)
        printf("Not found\n");
    else   
        printf("FindNode(): %s [%p]\n", pNode->szData, pNode);

    pNode = FindNode("7번 항목");
    if (pNode == NULL)
        printf("Not found\n");
    else   
        printf("FindNode(): %s [%p]\n", pNode->szData, pNode);

    pNode = FindNode("10번 항목");
    if (pNode == NULL)
        printf("Not found\n");
    else   
        printf("FindNode(): %s [%p]\n", pNode->szData, pNode);


    /*
    DeleteNode("5번 항목");
    DeleteNode("1번 항목");
    DeleteNode("9번 항목");
    DeleteNode("12번 항목");
    DeleteNode("7번 항목");

    PrintTree(g_pRoot);
    */


    ReleaseTree(g_pRoot);
    return 0;
}