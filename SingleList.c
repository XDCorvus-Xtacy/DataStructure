#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
    char szData[32];
    struct NODE* next;
} NODE;

NODE *g_pHead = NULL;

//연결리스트 전체 데이터 출력
void PrintList(void)
{
    NODE* pTmp = g_pHead;
    while (pTmp != NULL) {
        printf("[%p] %s, next[%p]\n",
            pTmp, pTmp->szData, pTmp->next);
        pTmp = pTmp->next;
    }
}

int InsertNewNode(char* pszData)
{
    NODE* pNode = (NODE*)(malloc(sizeof(NODE)));
    memset(pNode, 0, sizeof(NODE));

    strcpy(pNode->szData, pszData);

    if (g_pHead == NULL) {
        g_pHead = pNode;
    }
    else {
        pNode->next = g_pHead;
        g_pHead = pNode;
    }

    return 1;
}

int main(void)
{
    //List 테스트
    InsertNewNode("TEST01");
    PrintList();

    InsertNewNode("TEST02");
    PrintList();

    InsertNewNode("TEST03");
    PrintList();

    return 0;
}