#include <stdio.h>

typedef struct NODE{
    int nData;
    struct NODE* next;
} NODE;

int main(void)
{
    NODE List[5];

    List[0].nData = 100;
    List[1].nData = 200;
    List[2].nData = 300;
    List[3].nData = 400;
    List[4].nData = 500;

    List[0].next = &List[1];
    List[1].next = &List[2];
    List[2].next = &List[3];
    List[3].next = &List[4];
    List[4].next = NULL;

    for (int i = 0; i < 5; i++)
        printf("List[%d]: %d\n", i, List[i].nData);

    NODE *pTmp = &List[0];

    while (pTmp != NULL)
    {
        printf("%p: %d\n", pTmp, pTmp->nData);
        pTmp = pTmp->next;
    }
}