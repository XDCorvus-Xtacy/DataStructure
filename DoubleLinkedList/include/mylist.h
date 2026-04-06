#pragma once

/////////////////////////////////////////////////////////////////////
typedef struct NODE
{
    //관리 대상 자료
    void* pData;

    //자료구조
    struct NODE* prev;
    struct NODE* next;
} NODE;

typedef struct LIST_INFO
{
    NODE* pHead;
    NODE* pTail;
    int   nSize;
} LIST_INFO;



/////////////////////////////////////////////////////////////////////
void InitList(LIST_INFO* pListData);
void ReleaseList(LIST_INFO* pListData);
int InsertAtHead(LIST_INFO* pListData, void* pParam);
void InsertBefore(LIST_INFO* pListData, NODE* pDstNode, void* pParam);
int InsertAtTail(LIST_INFO* pListData, void* pParam);
NODE* FindeNode(LIST_INFO* pListData, const char* pszKey);
int DeleteNode(LIST_INFO* pListData, const char* pszKey);
int GetSize(LIST_INFO* pListData);
int GetLength(LIST_INFO* pListData);
int IsEmpty(LIST_INFO* pListData);
int InsertAt(LIST_INFO* pListData, int idx, void* pParam);
NODE* GetAt(LIST_INFO* pListData, int idx);

