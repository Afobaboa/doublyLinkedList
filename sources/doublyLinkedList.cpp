#include <stdlib.h>

#include "doublyLinkedList.h"
#include "DLL_dump.h"


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DLL_NodeArray* nodeArray);


bool DLL_Verify(const DoublyLinkedList* doublyLinkedList, const size_t nodeNum);


void DLL_AddNode(DoublyLinkedList* doublyLinkedList, 
                 const size_t nextNum, const size_t prevNum, const nodeValue_t value);


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

    NodeArrayInit(&doublyLinkedList->nodeArray);

    return true;
}


void DLL_Delete(DoublyLinkedList* doublyLinekedList)
{
    free(doublyLinekedList->nodeArray.buffer);
    *doublyLinekedList = {};
}


size_t DLL_ValueSearch(const DoublyLinkedList* doublyLinkedList, nodeValue_t value)
{
    if (!DLL_Verify(doublyLinkedList, 0))
        return 0;
    
    for (size_t nodeIndex = 0, nodeNum = 0; nodeIndex <= doublyLinkedList->nodeArray.nodeCount; 
                                                                                    nodeIndex++)
    {
        DLL_Node* node = &doublyLinkedList->nodeArray.buffer[nodeNum];
        ColoredPrintf(WHITE, "nodeNum = %zu, value = %" PRInodeVal ", index = %zu\n", 
                      nodeNum, node->value, nodeIndex);
        if (node->value == value)
            return nodeIndex;

        nodeNum = node->nextNodeNum;
    }

    return 0;
}


nodeValue_t DLL_GetNodeValue(const DoublyLinkedList* doublyLinkedList, size_t nodeNum)
{
    if (!DLL_Verify(doublyLinkedList, nodeNum))
        return 0;

    DLL_Node* node = &doublyLinkedList->nodeArray.buffer[0];
    for (size_t nodeIndex = 0; nodeIndex < nodeNum; nodeIndex++)
        node = &doublyLinkedList->nodeArray.buffer[node->nextNodeNum];

    return node->value;
}


bool DLL_Insert(DoublyLinkedList* doublyLinkedList, nodeValue_t value, size_t nodeNum)
{
    doublyLinkedList->nodeArray.nodeCount += 1;

    if (!DLL_Verify(doublyLinkedList, nodeNum))
        return false;

    DLL_Node* node = &doublyLinkedList->nodeArray.buffer[0];
    size_t nodeIndex = 0;
    for (size_t nodeIterator = 1; nodeIterator <= nodeNum; nodeIterator++)
    {
        nodeIndex = node->nextNodeNum;
        node = doublyLinkedList->nodeArray.buffer + nodeIndex;
    }

    size_t free    = doublyLinkedList->nodeArray.free;
    size_t prevNum = nodeIndex;
    size_t nextNum = node->nextNodeNum;
    if (nextNum == free)
        nextNum = doublyLinkedList->nodeArray.buffer[free].nextNodeNum;

    node->nextNodeNum = free;
    node = &doublyLinkedList->nodeArray.buffer[nextNum];
    node->prevNodeNum = free;

    DLL_AddNode(doublyLinkedList, nextNum, prevNum, value);

    return true;
}


bool DLL_PushBack(DoublyLinkedList* doublyLinkedList, nodeValue_t value)
{
    return DLL_Insert(doublyLinkedList, value, doublyLinkedList->nodeArray.nodeCount);
}


bool DLL_PushFront(DoublyLinkedList* doublyLinkedList, nodeValue_t value)
{
    return DLL_Insert(doublyLinkedList, value, 0);
}


bool DLL_PopBack(DoublyLinkedList* doublyLinkedList)
{
    if (!DLL_Verify(doublyLinkedList, 0))
        return false;

    return true;
}


bool DLL_PopFront(DoublyLinkedList* doublyLinkedList)
{
    if (!DLL_Verify(doublyLinkedList, 0))
        return false;

    return true;
}


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DLL_NodeArray* nodeArray)
{
    DLL_Node* node = NULL;
    node = &nodeArray->buffer[0];
    node->value       = 0;
    node->nextNodeNum = 1;
    node->prevNodeNum = nodeArray->capacity + 1;

    for (size_t nodeNum = 1; nodeNum < nodeArray->capacity; nodeNum++)
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


void DLL_AddNode(DoublyLinkedList* doublyLinkedList, 
                 const size_t nextNum, const size_t prevNum, const nodeValue_t value)
{
    // DLL_DUMP(doublyLinkedList);
    const size_t free = doublyLinkedList->nodeArray.free;
    doublyLinkedList->nodeArray.free = doublyLinkedList->nodeArray.buffer[free].nextNodeNum;

    DLL_Node* newNode = &doublyLinkedList->nodeArray.buffer[free];
    *newNode = {.value       = value,
                .nextNodeNum = nextNum,
                .prevNodeNum = prevNum};

    // DLL_DUMP(doublyLinkedList);
}


#ifndef _DLL_QUIET_VERIFY
    #define QUIET(...) __VA_ARGS__
#else 
    #define QUIET(...) 
#endif // _DLL_QUIET_VERIFY

bool DLL_Verify(const DoublyLinkedList* doublyLinkedList, const size_t nodeNum)
{
    #ifdef _DLL_SUPER_DUMP
    DLL_DUMP(doublyLinkedList);
    #endif // _DLL_SUPER_DUMP

    #ifdef _DLL_DEBUG
    if (doublyLinkedList == NULL)
    {
        QUIET(ColoredPrintf(RED, "doublyLinkedList == NULL\n"));
        return false;
    }
    #endif // _DLL_DEBUG

    if (nodeNum > doublyLinkedList->nodeArray.nodeCount)
    {
        QUIET(ColoredPrintf(RED, "nodeNum = %zu > nodeCount\n", nodeNum));
        return false;
    }

    if (doublyLinkedList->nodeArray.nodeCount > doublyLinkedList->nodeArray.capacity)
    {
        QUIET(ColoredPrintf(RED, "nodeArray > capacity\n"));
        return false;
    }

    #ifdef _DLL_DEBUG
    if (doublyLinkedList->nodeArray.free > doublyLinkedList->nodeArray.capacity)
    {
        QUIET(ColoredPrintf(RED, "free > capacity\n"));
        return false;
    }

    if (doublyLinkedList->nodeArray.buffer == NULL)
    {
        QUIET(ColoredPrintf(RED, "buffer == NULL\n"));
        return false;
    }
    #endif // _DLL_DEBUG

    return true;
}
#undef QUIET
