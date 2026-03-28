#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char szData[64];

    struct NODE* prev;
    struct NODE* next;
} NODE;


NODE* g_pHead; 
NODE* g_pTail;
int g_nSize;

///////////////////////////////////////////////////////////////////
void InsertBefore(NODE* pDstNode, const char* pszData);
///////////////////////////////////////////////////////////////////
void InitList(void)
{
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));
    g_nSize = 0;

    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    strcpy(g_pHead->szData, "DUMMY HEAD");
    strcpy(g_pTail->szData, "DUMMY TAIL");

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
    while (pTmp != NULL) {
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;

        printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
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
            printf("[%p] %s (%p), [%p]\n",
                pTmp->prev, pTmp->szData, pTmp, pTmp->next);
        else 
        {
            printf("Index:%d [%p] %p, %s [%p]\n",
                i, pTmp->prev, pTmp, pTmp->szData, pTmp->next);
            ++i;
        }
        pTmp = pTmp->next;
    }

    putchar('\n');
}

///////////////////////////////////////////////////////////////////
NODE* FindNode(const char* pszData)
{
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail) {
        if (strcmp(pTmp->szData, pszData) == 0)
            return pTmp;
        
        pTmp = pTmp->next;
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////
int DeleteNode(const char* pszData)
{
    NODE* pNode = FindNode(pszData);
    if (pNode == NULL)
        return 0;

    printf("DeleteNode(): %s (%p)\n", pszData, pNode);

    pNode->prev->next = pNode->next;
    pNode->next->prev = pNode->prev;

    free(pNode);

    g_nSize--;
    return 0;
}

///////////////////////////////////////////////////////////////////
int InsertAtHead(const char* pszData)
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    strcpy(pNewNode->szData, pszData);

    pNewNode->prev = g_pHead;
    pNewNode->next = g_pHead->next;

    g_pHead->next->prev = pNewNode;
    g_pHead->next = pNewNode;

    g_nSize++;

    return g_nSize;
}

///////////////////////////////////////////////////////////////////
int InsertAtTail(const char* pszData)
{
    InsertBefore(g_pTail, pszData);

    return g_nSize;
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
void InsertBefore(NODE* pDstNode, const char* pszData)
{
    NODE* pPrev = pDstNode->prev;

    NODE* pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    strcpy(pNewNode->szData, pszData);

    pNewNode->prev = pPrev;
    pNewNode->next = pDstNode;

    pDstNode->prev = pNewNode;
    pPrev->next = pNewNode;

    g_nSize++;
}

///////////////////////////////////////////////////////////////////
int InsertAt(int idx, const char* pszData)
{
    int i = 0;
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail)
    {
        if (i == idx)
        {
            InsertBefore(pTmp, pszData);
            return i;
        }

        pTmp = pTmp->next;
        ++i;
    }

    InsertAtTail(pszData);
    return i;
}



///////////////////////////////////////////////////////////////////
int main(void)
{
    InitList();

    InsertAtTail("TEST01");
    InsertAtTail("TEST02");
    InsertAtTail("TEST03");

    InsertAt(0, "TEST AT 00");
    PrintList();

    InsertAt(2, "TEST AT 02");
    PrintList();

    InsertAt(4, "TEST AT 04");
    PrintList();

    InsertAt(10, "TEST AT 10");
    PrintList();

    NODE* pNode = GetAt(0);
    if (pNode)
        printf("GetAt(%d): %s\n", 0, pNode->szData);
    else
        printf("GetAt(%d): %s\n", 0, "Not Found");

    pNode = GetAt(3);
    if (pNode)
        printf("GetAt(%d): %s\n", 3, pNode->szData);
    else
        printf("GetAt(%d): %s\n", 3, "Not Found");

    pNode = GetAt(6);
    if (pNode)
        printf("GetAt(%d): %s\n", 6, pNode->szData);
    else
        printf("GetAt(%d): %s\n", 6, "Not Found");

    pNode = GetAt(7);
    if (pNode)
        printf("GetAt(%d): %s\n", 7, pNode->szData);
    else
        printf("GetAt(%d): %s\n", 7, "Not Found");

    DeleteNode("TEST01");
    DeleteNode("TEST02");
    DeleteNode("TEST03");


    PrintList();
    ReleaseList();
    return 0;
}