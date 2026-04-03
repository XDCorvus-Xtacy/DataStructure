#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct USERDATA {
    
    char szName[64];    //Key
    char szPhone[64];
} USERDATA;


///////////////////////////////////////////////////////////////////
typedef struct NODE {

    //관리 대상 자료
    USERDATA* pData;

    //자료구조
    struct NODE* prev;
    struct NODE* next;

} NODE;


NODE* g_pHead; 
NODE* g_pTail;
int g_nSize;

///////////////////////////////////////////////////////////////////
void InsertBefore(NODE* pDstNode, USERDATA* pParam);

///////////////////////////////////////////////////////////////////
USERDATA* CreateNewData(const char* pszName, const char* pszPhone)
{
    USERDATA* pNewData = (USERDATA*)malloc(sizeof(USERDATA));
    memset(pNewData, 0, sizeof(USERDATA));
    strcpy(pNewData->szName, pszName);
    strcpy(pNewData->szPhone, pszPhone);

    return pNewData;
}

///////////////////////////////////////////////////////////////////
void InitList(void)
{
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));
    g_nSize = 0;

    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    g_pHead->next = g_pTail;
    g_pTail->prev = g_pHead;
}

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
void ReleaseList()
{
    printf("\nReleasList()\n");
    NODE* pTmp = g_pHead;
    while (pTmp != NULL) 
    {
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;

        printf("Delete: [%p] %s\n", pDelete, pDelete->pData->szName);

        free(pDelete->pData);
        free(pDelete);
    }

    g_pHead = NULL;
    g_pTail = NULL;
    g_nSize = 0;
}

///////////////////////////////////////////////////////////////////
void PrintList(void)
{
    int i = 0;
    printf("\nPrintList(): g_nSize: %d, g_pHead [%p], g_pTail [%p]\n", 
            g_nSize, g_pHead, g_pTail);
    NODE* pTmp = g_pHead;
    while (pTmp != NULL) 
    {
        if (pTmp == g_pHead || pTmp == g_pTail)
            printf("[DUMMY]\n");
        else 
        {
            printf("Index:%d %s %s\n", 
                    i, pTmp->pData->szName, pTmp->pData->szPhone);
            ++i;
        } 
        pTmp = pTmp->next;
    }

    putchar('\n');
}

///////////////////////////////////////////////////////////////////
//pParam: 호출자가 메모리를 동적 할당 + 값 설정까지 해서 전달
int InsertAtHead(USERDATA* pParam)
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->pData = pParam;

    pNewNode->prev = g_pHead;
    pNewNode->next = g_pHead->next;

    g_pHead->next->prev = pNewNode;
    g_pHead->next = pNewNode;

    g_nSize++;

    return g_nSize;
}

///////////////////////////////////////////////////////////////////
int InsertAtTail(USERDATA* pParam)
{
    InsertBefore(g_pTail, pParam);

    return g_nSize;
}

///////////////////////////////////////////////////////////////////
NODE* FindNode(const char* pszName)
{
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail) {
        if (strcmp(pTmp->pData->szName, pszName) == 0)
            return pTmp;
        
        pTmp = pTmp->next;
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////
int DeleteNode(const char* pszName)
{
    NODE* pNode = FindNode(pszName);
    if (pNode == NULL)
        return 0;

    printf("DeleteNode(): %s (%p)\n", pszName, pNode);

    pNode->prev->next = pNode->next;
    pNode->next->prev = pNode->prev;

    free(pNode->pData);
    free(pNode);

    g_nSize--;
    return 0;
}


///////////////////////////////////////////////////////////////////
NODE* GetAt(int idx)
{
    int i = 0;
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail)
    {
        if (i == idx)
            return pTmp;

        pTmp = pTmp->next;
        ++i;
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////
void InsertBefore(NODE* pDstNode, USERDATA* pParam)
{
    NODE* pPrev = pDstNode->prev;

    NODE* pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->pData = pParam;
    
    pNewNode->prev = pPrev;
    pNewNode->next = pDstNode;

    pDstNode->prev = pNewNode;
    pPrev->next = pNewNode;

    g_nSize++;
}

///////////////////////////////////////////////////////////////////
int InsertAt(int idx, USERDATA* pParam)
{
    int i = 0;
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail)
    {
        if (i == idx)
        {
            InsertBefore(pTmp, pParam);
            return i;
        }

        pTmp = pTmp->next;
        ++i;
    }

    InsertAtTail(pParam);
    return i;
}



///////////////////////////////////////////////////////////////////
int main(void)
{
    InitList();

    USERDATA* pNewData = CreateNewData("Ho-sung", "010-1234-5678");
    InsertAtTail(pNewData);


    PrintList();
    ReleaseList();
    return 0;
}