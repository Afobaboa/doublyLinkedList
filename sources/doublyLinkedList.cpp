#include <stdlib.h>

#include "doublyLinkedList.h"


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DLL_NodeArray* nodeArray, const size_t startNodeNum);


bool DLL_Verify(DoublyLinkedList* doublyLinkedList);


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


size_t DLL_ValueSearch(DoublyLinkedList* doublyLinkedList, nodeValue_t value)
{
    if (DLL_Verify(doublyLinkedList))
        return 0;

    return 0;
}


bool DLL_Insert(DoublyLinkedList* doublyLinkedList, nodeValue_t value, size_t nodeNum)
{
    if (DLL_Verify(doublyLinkedList))
        return false;

    return true;
}


bool DLL_PushBack(DoublyLinkedList* doublyLinkedList, nodeValue_t value)
{
    if (DLL_Verify(doublyLinkedList))
        return false;

    return true;
}


bool DLL_PushFront(DoublyLinkedList* doublyLinkedList, nodeValue_t value)
{
    if (DLL_Verify(doublyLinkedList))
        return false;

    return true;
}


bool DLL_Erase(DoublyLinkedList* doublyLinkedList, size_t nodeNum)
{
    if (DLL_Verify(doublyLinkedList))
        return false;

    return true;
}


bool DLL_PopBack(DoublyLinkedList* doublyLinkedList)
{
    if (DLL_Verify(doublyLinkedList))
        return false;

    return true;
}


bool DLL_PopFront(DoublyLinkedList* doublyLinkedList)
{
    if (DLL_Verify(doublyLinkedList))
        return false;

    return true;
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


#ifndef _DLL_QUIET_VERIFY
    #define QUIET(...) __VA_ARGS__
#else 
    #define QUIET(...) 
#endif // _DLL_QUIET_VERIFY

bool DLL_Verify(DoublyLinkedList* doublyLinkedList)
{
    #ifdef _SUPER_DUMP
    DLL_DUMP(doublyLinkedList);
    #endif // _SUPER_DUMP


    return true;
}
#undef QUIET
