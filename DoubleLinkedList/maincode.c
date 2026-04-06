#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mylist.h"

////////////////////////////////////////////////////////////////////////
typedef struct USERDATA
{
    //멤버 함수 포인터
    const char* (*GetKey)(void*);

    char szName[64];        //Key
    char szPhone[64];
} USERDATA;

const char* GetKeyFromUserData(void* pUser)
{
    USERDATA* p = (USERDATA*)pUser;
    return p->szName;
}

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

////////////////////////////////////////////////////////////////////////
void PrintList(LIST_INFO* pListData)
{
    int i = 0;
    printf("\nPrintList(): nSize: %d, pHead [%p], pTail [%p]\n", 
            pListData->nSize, pListData->pHead, pListData->pTail);
    NODE* pTmp = pListData->pHead;
    while (pTmp != NULL) 
    {
        if (pTmp == pListData->pHead || pTmp == pListData->pTail)
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



////////////////////////////////////////////////////////////////////////
int main(void)
{
    LIST_INFO userList01 = {0};
    InitList(&userList01);

    USERDATA* pNewData = CreateUserData("CHS01", "010-1234-5678");
    InsertAtTail(&userList01, pNewData);
    pNewData = CreateUserData("CHS02", "010-1234-5678");
    InsertAtTail(&userList01, pNewData);
    pNewData = CreateUserData("CHS03", "010-1234-5678");
    InsertAtTail(&userList01, pNewData);


    LIST_INFO userList02 = {0};
    InitList(&userList02);

    pNewData = CreateUserData("TESTER01", "010-1234-5678");
    InsertAtTail(&userList02, pNewData);
    pNewData = CreateUserData("TESTER02", "010-1234-5678");
    InsertAtTail(&userList02, pNewData);
    pNewData = CreateUserData("TESTER03", "010-1234-5678");
    InsertAtTail(&userList02, pNewData);


    LIST_INFO userList03 = {0};
    InitList(&userList03);

    pNewData = CreateUserData("ABCD01", "010-1234-5678");
    InsertAtTail(&userList03, pNewData);
    pNewData = CreateUserData("ABCD02", "010-1234-5678");
    InsertAtTail(&userList03, pNewData);
    pNewData = CreateUserData("ABCD03", "010-1234-5678");
    InsertAtTail(&userList03, pNewData);


    PrintList(&userList01);
    PrintList(&userList02);
    PrintList(&userList03);


    ReleaseList(&userList01);
    ReleaseList(&userList02);
    ReleaseList(&userList03);
    return 0;
}