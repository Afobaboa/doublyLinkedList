#include <stdlib.h>

#include "doublyLinkedList.h"
#include "DLL_dump.h"


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DLL_NodeArray* nodeArray);


bool DLL_Verify(const DoublyLinkedList* doublyLinkedList, const size_t nodeLogicIndex);


void DLL_AddNode(DoublyLinkedList* doublyLinkedList, 
                 const size_t nextnodeLogicIndex, const size_t prevnodeLogicIndex, const nodeValue_t value);

                
size_t DLL_GetNodeRealIndex(DoublyLinkedList* doublyLinkedList, const size_t nodeLogicIndex);


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

    DLL_NodeArray* nodeArray = &doublyLinkedList->nodeArray;
    nodeArray->capacity = DLL_CAPACITY;
    nodeArray->firstFreenodeLogicIndex     = 1;
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
    
    for (size_t nodeLogicIndex = 0, nodeRealIndex = 0; nodeLogicIndex <= doublyLinkedList->nodeArray.nodeCount; 
                                                                                    nodeLogicIndex++)
    {
        DLL_Node* node = &doublyLinkedList->nodeArray.buffer[nodeRealIndex];
        ColoredPrintf(WHITE, "nodeRealIndex = %zu, value = %" PRInodeVal ", index = %zu\n", 
                      nodeRealIndex, node->value, nodeLogicIndex);
        if (node->value == value)
            return nodeLogicIndex;

        nodeRealIndex = node->nextnodeLogicIndex;
    }

    return 0;
}


nodeValue_t DLL_GetNodeValue(const DoublyLinkedList* doublyLinkedList, const size_t nodeLogicIndex)
{
    if (!DLL_Verify(doublyLinkedList, nodeLogicIndex))
        return 0;

    DLL_Node* nodeBuffer = doublyLinkedList->nodeArray.buffer;
    DLL_Node* node       = &nodeBuffer[0];
    for (size_t iterator = 0; iterator < nodeLogicIndex; iterator++)
        node = &doublyLinkedList->nodeArray.buffer[node->nextnodeLogicIndex];

    return node->value;
}


bool DLL_Insert(DoublyLinkedList* doublyLinkedList, nodeValue_t value, const size_t nodeLogicIndex)
{
    doublyLinkedList->nodeArray.nodeCount += 1;

    if (!DLL_Verify(doublyLinkedList, nodeLogicIndex))
    {
        doublyLinkedList->nodeArray.nodeCount--;
        return false;
    }

    DLL_Node* nodeBuffer = doublyLinkedList->nodeArray.buffer;

    const size_t nodeRealIndex     = DLL_GetNodeRealIndex(doublyLinkedList, nodeLogicIndex);
    DLL_Node*    currentNode = &nodeBuffer[nodeRealIndex];

    const size_t prevnodeLogicIndex      = nodeLogicIndex;
    const size_t nextnodeLogicIndex      = currentNode->nextnodeLogicIndex;
    const size_t firstFreenodeLogicIndex = doublyLinkedList->nodeArray.firstFreenodeLogicIndex;

    currentNode->nextnodeLogicIndex              = firstFreenodeLogicIndex;
    nodeBuffer[nextnodeLogicIndex].prevnodeLogicIndex = firstFreenodeLogicIndex;

    DLL_AddNode(doublyLinkedList, nextnodeLogicIndex, prevnodeLogicIndex, value);

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


bool DLL_Erase(DoublyLinkedList* doublyLinkedList, const size_t nodeLogicIndex)
{   
    if (nodeLogicIndex == 0)
        return false;

    if (!DLL_Verify(doublyLinkedList, nodeLogicIndex))
        return false;

    const size_t nodeRealIndex = DLL_GetNodeRealIndex(doublyLinkedList, nodeLogicIndex);
    DLL_Node* nodeBuffer = doublyLinkedList->nodeArray.buffer;

    DLL_Node* currentNode = &nodeBuffer[nodeRealIndex];
    DLL_Node* prevNode    = &nodeBuffer[currentNode->prevnodeLogicIndex];
    DLL_Node* nextNode    = &nodeBuffer[currentNode->nextnodeLogicIndex];

    prevNode->nextnodeLogicIndex = currentNode->nextnodeLogicIndex;
    nextNode->prevnodeLogicIndex = currentNode->prevnodeLogicIndex;
    
    size_t*   firstFreenodeLogicIndexPtr = &doublyLinkedList->nodeArray.firstFreenodeLogicIndex;
    DLL_Node* firstFreeNode         = &nodeBuffer[*firstFreenodeLogicIndexPtr];

    firstFreeNode->prevnodeLogicIndex = nodeLogicIndex;
    currentNode->nextnodeLogicIndex   = *firstFreenodeLogicIndexPtr;
    *firstFreenodeLogicIndexPtr = nodeLogicIndex;

    doublyLinkedList->nodeArray.nodeCount--;
    return true;
}


bool DLL_PopBack(DoublyLinkedList* doublyLinkedList)
{
    return DLL_Erase(doublyLinkedList, 1);
}


bool DLL_PopFront(DoublyLinkedList* doublyLinkedList)
{
    return DLL_Erase(doublyLinkedList, doublyLinkedList->nodeArray.nodeCount);
}


//--------------------------------------------------------------------------------------------------


void NodeArrayInit(DLL_NodeArray* nodeArray)
{
    DLL_Node* node = NULL;
    node = &nodeArray->buffer[0];
    node->value       = 0;
    node->nextnodeLogicIndex = 1;
    node->prevnodeLogicIndex = nodeArray->capacity + 1;

    for (size_t nodeRealIndex = 1; nodeRealIndex < nodeArray->capacity; nodeRealIndex++)
    {
        node = nodeArray->buffer + nodeRealIndex;
        node->value       = 0;
        node->nextnodeLogicIndex = nodeRealIndex + 1;
        node->prevnodeLogicIndex = nodeRealIndex - 1;
    }

    node = nodeArray->buffer + nodeArray->capacity;
    node->value       = 0;
    node->nextnodeLogicIndex = 0;
    node->prevnodeLogicIndex = nodeArray->capacity;
}


void DLL_AddNode(DoublyLinkedList* doublyLinkedList, 
                 const size_t nextnodeLogicIndex, const size_t prevnodeLogicIndex, const nodeValue_t value)
{
    // DLL_DUMP(doublyLinkedList);
    const size_t firstFreenodeLogicIndex = doublyLinkedList->nodeArray.firstFreenodeLogicIndex;
    doublyLinkedList->nodeArray.firstFreenodeLogicIndex = doublyLinkedList->nodeArray.buffer[firstFreenodeLogicIndex].nextnodeLogicIndex;

    DLL_Node* newNode = &doublyLinkedList->nodeArray.buffer[firstFreenodeLogicIndex];
    *newNode = {.value       = value,
                .nextnodeLogicIndex = nextnodeLogicIndex,
                .prevnodeLogicIndex = prevnodeLogicIndex};

    // DLL_DUMP(doublyLinkedList);
}


#ifndef _DLL_QUIET_VERIFY
    #define QUIET(...) __VA_ARGS__
#else 
    #define QUIET(...) 
#endif // _DLL_QUIET_VERIFY

bool DLL_Verify(const DoublyLinkedList* doublyLinkedList, const size_t nodeLogicIndex)
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

    if (nodeLogicIndex > doublyLinkedList->nodeArray.nodeCount)
    {
        QUIET(ColoredPrintf(RED, "nodeRealIndex = %zu > nodeCount\n", nodeLogicIndex));
        return false;
    }

    if (doublyLinkedList->nodeArray.nodeCount > doublyLinkedList->nodeArray.capacity)
    {
        QUIET(ColoredPrintf(RED, "nodeArray > capacity\n"));
        return false;
    }

    #ifdef _DLL_DEBUG
    if (doublyLinkedList->nodeArray.firstFreenodeLogicIndex > doublyLinkedList->nodeArray.capacity)
    {
        QUIET(ColoredPrintf(RED, "firstFreenodeLogicIndex > capacity\n"));
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


size_t DLL_GetNodeRealIndex(DoublyLinkedList* doublyLinkedList, const size_t nodeLogicIndex)
{
    size_t    nodeRealIndex = 0;
    DLL_Node* node    = &doublyLinkedList->nodeArray.buffer[0];

    for (size_t iterator = 0; iterator < nodeLogicIndex; iterator++) 
    {
        nodeRealIndex = node->nextnodeLogicIndex;
        node    = &doublyLinkedList->nodeArray.buffer[nodeRealIndex];
    }

    return nodeRealIndex;
}
