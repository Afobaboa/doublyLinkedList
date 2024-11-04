#include <stdlib.h>

#include "doublyLinkedList.h"


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DLL_NodeArray* nodeArray, const size_t startNodeNum);


//--------------------------------------------------------------------------------------------------


bool DLL_Init(DoublyLinkedList* doublyLinkedList
              _DLL_ON_DEBUG(,const char* name, Place place))
{
    #ifdef _DLL_DEBUG
    if (doublyLinkedList == NULL)
        return false;

    doublyLinkedList->initInfo = {.name  = (char*) name + 1, 
                                  .place = place};
    #endif // _DLL_DEBUG

    DLL_NodeArray* nodeArray = &doublyLinkedList->nodeArray;
    nodeArray->capacity = DLL_CAPACITY;
    nodeArray->free     = 1;
    nodeArray->buffer   = (DLL_Node*) calloc(DLL_CAPACITY + 1, sizeof(DLL_Node));
    if (nodeArray->buffer == NULL)
        return false;

    NodeArrayInit(&doublyLinkedList->nodeArray, 1);

    return true;
}


void DLL_Delete(DoublyLinkedList* doublyLinekedList)
{
    free(doublyLinekedList->nodeArray.buffer);
    *doublyLinekedList = {};
}


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DLL_NodeArray* nodeArray, const size_t startNodeNum)
{
    DLL_Node* node = NULL;
    for (size_t nodeNum = startNodeNum; nodeNum < nodeArray->capacity; nodeNum++)
    {
        node = nodeArray->buffer + nodeNum;
        node->value       = 0;
        node->nextNodeNum = nodeNum + 1;
        node->prevNodeNum = nodeNum - 1;
    }

    node = nodeArray->buffer + nodeArray->capacity;
    node->value       = 0;
    node->nextNodeNum = 0;
    node->prevNodeNum = nodeArray->capacity;
}
