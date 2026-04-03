#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct USERDATA {
    
    char szName[64];    //Key
    char szPhone[64];
} USERDATA;

const char* GetKeyFromUserData(void* pUser)
{
    USERDATA* p = (USERDATA*)pUser;
    return p->szName;
}


///////////////////////////////////////////////////////////////////
typedef struct NODE {

    //관리 대상 자료
    void* pData;

    //멤버 함수 포인터
    const char* (*GetKey)(void*);

    //자료구조
    struct NODE* prev;
    struct NODE* next;

} NODE;


NODE* g_pHead; 
NODE* g_pTail;
int g_nSize;

///////////////////////////////////////////////////////////////////
void InsertBefore(NODE* pDstNode, void* pParam, const char* (*pfParam)(void*));
int InsertAtHead(void* pParam, const char* (*pfParam)(void*));
int InsertAtTail(void* pParam, const char* (*pfParam)(void*));

///////////////////////////////////////////////////////////////////
void CreateUserData(const char* pszName, const char* pszPhone)
{
    USERDATA* pNewData = (USERDATA*)malloc(sizeof(USERDATA));
    memset(pNewData, 0, sizeof(USERDATA));

    strcpy(pNewData->szName, pszName);
    strcpy(pNewData->szPhone, pszPhone);

    InsertAtTail(pNewData, GetKeyFromUserData);
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

        printf("Delete: %p\n", 
            pDelete);

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
            printf("Index:%d %s\n", 
                    i, pTmp->GetKey(pTmp->pData));
            ++i;
        } 
        pTmp = pTmp->next;
    }

    putchar('\n');
}

///////////////////////////////////////////////////////////////////
//pParam: 호출자가 메모리를 동적 할당 + 값 설정까지 해서 전달
int InsertAtHead(void* pParam, const char* (*pfParam)(void*))
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    //관리 대상 자료에 관한 초기화
    pNewNode->pData = pParam;
    pNewNode->GetKey = pfParam;

    //연결 리스트에 관한 초기화
    pNewNode->prev = g_pHead;
    pNewNode->next = g_pHead->next;

    g_pHead->next->prev = pNewNode;
    g_pHead->next = pNewNode;

    g_nSize++;

    return g_nSize;
}

///////////////////////////////////////////////////////////////////
int InsertAtTail(void* pParam, const char* (*pfParam)(void*))
{
    InsertBefore(g_pTail, pParam, pfParam);

    return g_nSize;
}

///////////////////////////////////////////////////////////////////
NODE* FindNode(const char* pszKey)
{
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail) {
        if (strcmp(pTmp->GetKey(pTmp->pData), pszKey) == 0)
            return pTmp;
        
        pTmp = pTmp->next;
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////
int DeleteNode(const char* pszKey)
{
    NODE* pNode = FindNode(pszKey);
    if (pNode == NULL)
        return 0;

    printf("DeleteNode(): %s (%p)\n", pszKey, pNode);

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
void InsertBefore(NODE* pDstNode, void* pParam, const char* (*pfParam)(void*))
{
    NODE* pPrev = pDstNode->prev;

    NODE* pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->pData = pParam;
    pNewNode->GetKey = pfParam;
    
    pNewNode->prev = pPrev;
    pNewNode->next = pDstNode;

    pPrev->next = pNewNode;
    pDstNode->prev = pNewNode;

    g_nSize++;
}

///////////////////////////////////////////////////////////////////
int InsertAt(int idx, void* pParam, const char* (*pfParam)(void*))
{
    int i = 0;
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail)
    {
        if (i == idx)
        {
            InsertBefore(pTmp, pParam, pfParam);
            return i;
        }

        pTmp = pTmp->next;
        ++i;
    }

    InsertAtTail(pParam, pfParam);
    return i;
}



///////////////////////////////////////////////////////////////////
int main(void)
{
    InitList();

    CreateUserData("Ho-sung", "010-1234-5678");
    CreateUserData("TEST", "010-1111-2222");

    PrintList();
    ReleaseList();
    return 0;
}