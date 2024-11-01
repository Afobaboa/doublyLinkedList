#include <stdlib.h>

#include "doublyLinkedList.h"


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DoublyLinkedList* doublyLinkedList, const size_t startNodeNum);


//--------------------------------------------------------------------------------------------------


bool DLL_Init(DoublyLinkedList* doublyLinkedList
              _DLL_ON_DEBUG(,const char* name, Place place))
{
    #ifdef _DLL_DEBUG
    if (doublyLinkedList == NULL)
        return false;

    doublyLinkedList->initInfo = {.name  = (char*) name, 
                                  .place = place};
    #endif // _DLL_DEBUG

    doublyLinkedList->capacity  = MIN_DLL_CAPACITY;
    doublyLinkedList->free      = 1;
    doublyLinkedList->nodeArray = (DLL_Node*) calloc(MIN_DLL_CAPACITY + 1, sizeof(DLL_Node));
    if (doublyLinkedList->nodeArray == NULL)
        return false;

    NodeArrayInit(doublyLinkedList, 1);

    return true;
}


void DLL_Delete(DoublyLinkedList* doublyLinekedList)
{
    free(doublyLinekedList->nodeArray);
    *doublyLinekedList = {};
}


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DoublyLinkedList* doublyLinkedList, const size_t startNodeNum)
{
    DLL_Node* node = NULL;
    for (size_t nodeNum = startNodeNum; nodeNum < doublyLinkedList->capacity; nodeNum++)
    {
        node = doublyLinkedList->nodeArray + nodeNum;
        node->value       = 0;
        node->nextNodeNum = nodeNum + 1;
        node->prevNodeNum = nodeNum - 1;
    }

    node = doublyLinkedList->nodeArray + doublyLinkedList->capacity;
    node->value       = 0;
    node->nextNodeNum = 0;
    node->prevNodeNum = doublyLinkedList->capacity;
}
