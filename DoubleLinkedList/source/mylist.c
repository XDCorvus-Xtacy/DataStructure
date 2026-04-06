#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mylist.h"


////////////////////////////////////////////////////////////////////////
void InitList(LIST_INFO* pListData)
{
    pListData->pHead = (NODE*)malloc(sizeof(NODE));
    pListData->pTail = (NODE*)malloc(sizeof(NODE));
    memset(pListData->pHead, 0, sizeof(NODE));
    memset(pListData->pTail, 0, sizeof(NODE));

    pListData->pHead->next = pListData->pTail;
    pListData->pTail->prev = pListData->pHead;

    pListData->nSize = 0;
}

/////////////////////////////////////////////////////////////////////
void ReleaseList(LIST_INFO* pListData)
{
    printf("\nReleaseList\n");
    NODE* pTmp = pListData->pHead;

    while (pTmp != NULL)
    {
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;
        
        printf("Delete: %p\n", pDelete);

        free(pDelete->pData);
        free(pDelete);
    }
}

/////////////////////////////////////////////////////////////////////
int InsertAtHead(LIST_INFO* pListData, void* pParam)
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->pData = pParam;

    pNewNode->prev = pListData->pHead;
    pNewNode->next = pListData->pHead->next;

    pListData->pHead->next = pNewNode;
    pNewNode->next->prev = pNewNode;

    pListData->nSize++;

    return pListData->nSize;
}

/////////////////////////////////////////////////////////////////////
void InsertBefore(LIST_INFO* pListData, NODE* pDstNode, void* pParam)
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    pNewNode->pData = pParam;

    pNewNode->prev = pDstNode->prev;
    pNewNode->next = pDstNode;

    pDstNode->prev->next = pNewNode;
    pDstNode->prev = pNewNode;

    pListData->nSize++;
}

/////////////////////////////////////////////////////////////////////
int InsertAtTail(LIST_INFO* pListData, void* pParam)
{
    InsertBefore(pListData, pListData->pTail, pParam);

    return pListData->nSize;
}

/////////////////////////////////////////////////////////////////////
NODE* FindNode(LIST_INFO* pListData, const char* pszKey)
{
    NODE* pTmp = pListData->pHead->next;
    const char* (*pfGetKey)(void*) = NULL;
    while (pTmp != pListData->pTail)
    {
        //관리 대상 데이터 구조체 첫 번째 멤버가 함수 포인터임을 가정
        pfGetKey = pTmp->pData;
        if (strcmp(pfGetKey(pTmp->pData), pszKey) == 0)
            return pTmp;

        pTmp = pTmp->next;
    }

    return NULL;
}

/////////////////////////////////////////////////////////////////////
int DeleteNode(LIST_INFO* pListData, const char* pszKey)
{
    NODE* pNode = FindNode(pListData, pszKey);
    if (pNode == NULL)  
        return 0;

    printf("DeleteNode(): %s (%p)\n", pszKey, pNode);

    pNode->prev->next = pNode->next;
    pNode->next->prev = pNode->prev;

    free(pNode->pData);
    free(pNode);

    pListData->nSize--;
    return 0;
}

/////////////////////////////////////////////////////////////////////
int GetSize(LIST_INFO* pListData)
{
    return pListData->nSize;
}

/////////////////////////////////////////////////////////////////////
int GetLength(LIST_INFO* pListData)
{
    return GetSize(pListData);
}

/////////////////////////////////////////////////////////////////////
int IsEmpty(LIST_INFO* pListData)
{
    return GetSize(pListData);
}

/////////////////////////////////////////////////////////////////////
int InsertAt(LIST_INFO* pListData, int idx, void* pParam)
{
    int i = 0;
    NODE* pTmp = pListData->pHead->next;
    while (pTmp != pListData->pTail)
    {
        if (i == idx)
        {
            InsertBefore(pListData, pTmp, pParam);
            return i;
        }

        pTmp = pTmp->next;
        i++;
    }

    InsertAtTail(pListData, pParam);
    return i;
}

/////////////////////////////////////////////////////////////////////
NODE* GetAt(LIST_INFO* pListData, int idx)
{
    int i = 0;
    NODE* pTmp = pListData->pHead->next;
    while (pTmp != pListData->pTail)
    {
        if (i == idx)
            return pTmp;

        pTmp = pTmp->next;
        i++;
    }

    return NULL;
}
