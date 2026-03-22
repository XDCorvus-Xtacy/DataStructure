#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char szData[64];
    struct NODE* next;
} NODE;

NODE g_head = {0};
NODE* g_pTail = 0;


int HeadIsEmpty()
{
    if (g_head.next == NULL)
        return 1;

    return 0;
}

void PrintList(void)
{
    NODE* pTmp = g_head.next;
    while (pTmp != NULL) {
        printf("[%p] %s, next[%p]\n",
            pTmp, pTmp->szData, pTmp->next);
        pTmp = pTmp->next;
    }

    putchar('\n');
}


int InsertAtHead(char* pszData)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode->szData, pszData);

    if (HeadIsEmpty()) {
        //리스트에 추가된 첫 번째 데이터 처리
        g_head.next = pNode;
        g_pTail = pNode;
    }
    else {
        pNode->next = g_head.next;
        g_head.next = pNode;
    }

    return 1;
}

int InsertAtTail(char* pszData)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0 , sizeof(NODE));
    strcpy(pNode->szData, pszData);

    pTmp->next = pNode;

    if (HeadIsEmpty())
        //리스트에 추가된 첫 번째 데이터 처리
        g_head.next = pNode;
    else
        g_pTail->next = pNode;

    g_pTail = pNode;

    return 1;
}

void ReleasList(void)
{
    printf("\nReleasList()\n");
    NODE* pTmp = g_head.next;
    while (pTmp != NULL) {
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;

        printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
        free(pDelete);
    }

    g_head.next = NULL;
    g_pTail = 0;
}

NODE* FindData(char* pszData)
{
    NODE* pCur = g_head.next;
    NODE* pPrev = &g_head;
    while (pCur != NULL) {
        if (strcmp(pCur->szData, pszData) == 0)
            return pPrev;
        pCur = pCur->next;
        pPrev = pPrev->next;
    }

    return 0;
}

int DeleteData(char* pszData)
{
    NODE* pPrev = FindData(pszData);
    if (pPrev != 0)
    {
        NODE* pDelete = pPrev->next;
        pPrev->next = pDelete->next;

        printf("DeleteData(): %s\n", pDelete->szData);

        if (pDelete == g_pTail)
            g_pTail = pPrev->next;

        free(pDelete);
        return 1;
    }

    return 0;
}


int main(void)
{
    //List 테스트를 위한 코드
    puts("*** InsertAtHead() ***");
    InsertAtHead("TEST01");
    InsertAtHead("TEST02");
    InsertAtHead("TEST03");
    PrintList();

    if (FindData("TEST01") == 1)
        printf("FindData(): TEST01 found\n");
    if (FindData("TEST02") == 1)
        printf("FindData(): TEST02 found\n");
    if (FindData("TEST03") == 1)
        printf("FindData(): TEST03 found\n");
    putchar('\n');

    DeleteData("TEST01");
    PrintList();
    DeleteData("TEST02");
    PrintList();
    DeleteData("TEST03");
    PrintList();

    puts("*** InsertAtTail() ***");
    InsertAtTail("TEST01");
    InsertAtTail("TEST02");
    InsertAtTail("TEST03");
    PrintList();

    if (FindData("TEST01") == 1)
        printf("FindData(): TEST01 found\n");
    if (FindData("TEST02") == 1)
        printf("FindData(): TEST02 found\n");
    if (FindData("TEST03") == 1)
        printf("FindData(): TEST03 found\n");
    putchar('\n');

    DeleteData("TEST01");
    PrintList();
    DeleteData("TEST02");
    PrintList();
    DeleteData("TEST03");
    PrintList();

    ReleasList();
    return 0;
}