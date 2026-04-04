#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct USERDATA {

    //멤버 함수 포인터
    const char* (*GetKey)(void*);
    
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

    //자료구조
    struct NODE* prev;
    struct NODE* next;

} NODE;


NODE* g_pHead; 
NODE* g_pTail;
int g_nSize;

///////////////////////////////////////////////////////////////////
void InsertBefore(NODE* pDstNode, void* pParam);
int InsertAtHead(void* pParam);
int InsertAtTail(void* pParam);

///////////////////////////////////////////////////////////////////
USERDATA* CreateUserData(const char* pszName, const char* pszPhone)
{
    USERDATA* pNewData = (USERDATA*)malloc(sizeof(USERDATA));
    memset(pNewData, 0, sizeof(USERDATA));

    strcpy(pNewData->szName, pszName);
    strcpy(pNewData->szPhone, pszPhone);

    //구조체 멤버 함수 초기화
    pNewData->GetKey = GetKeyFromUserData;

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
            USERDATA* pUser = pTmp->pData;  //형 불일치 문제 해결
            printf("Index:%d %s\n", 
                    i, pUser->GetKey(pUser));
            ++i;
        } 
        pTmp = pTmp->next;
    }

    putchar('\n');
}

///////////////////////////////////////////////////////////////////
//pParam: 호출자가 메모리를 동적 할당 + 값 설정까지 해서 전달
int InsertAtHead(void* pParam)
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    //관리 대상 자료에 관한 초기화
    pNewNode->pData = pParam;

    //연결 리스트에 관한 초기화
    pNewNode->prev = g_pHead;
    pNewNode->next = g_pHead->next;

    g_pHead->next->prev = pNewNode;
    g_pHead->next = pNewNode;

    g_nSize++;

    return g_nSize;
}

///////////////////////////////////////////////////////////////////
int InsertAtTail(void* pParam)
{
    InsertBefore(g_pTail, pParam);

    return g_nSize;
}

///////////////////////////////////////////////////////////////////
NODE* FindNode(const char* pszKey)
{
    NODE* pTmp = g_pHead->next;
    const char* (*pfGetKey)(void*) = NULL;
    while (pTmp != g_pTail) 
    {
        //관리 대상 데이터 구조체 첫 번째 멤버가 함수 포인터임을 가정
        pfGetKey = pTmp->pData;
        if (strcmp(pfGetKey(pTmp->pData), pszKey) == 0)
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
void InsertBefore(NODE* pDstNode, void* pParam)
{
    NODE* pPrev = pDstNode->prev;

    NODE* pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->pData = pParam;
    
    pNewNode->prev = pPrev;
    pNewNode->next = pDstNode;

    pPrev->next = pNewNode;
    pDstNode->prev = pNewNode;

    g_nSize++;
}

///////////////////////////////////////////////////////////////////
int InsertAt(int idx, void* pParam)
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

    USERDATA* pNewData = NULL;
    pNewData = CreateUserData("Ho-sung", "010-1234-5678");
    InsertAtTail(pNewData);
    pNewData = CreateUserData("TEST", "010-1111-2222");
    InsertAtTail(pNewData);

    PrintList();
    ReleaseList();
    return 0;
}