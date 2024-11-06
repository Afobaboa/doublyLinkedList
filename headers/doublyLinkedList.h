#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


//--------------------------------------------------------------------------------------------------


#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

#include "logPrinter.h"


// #define _DLL_DEBUG

#ifdef _DLL_DEBUG
    #define _DLL_ON_DEBUG(...) __VA_ARGS__
#else 
    #define _DLL_ON_DEBUG(...) 
#endif // _DLL_DEBUG


//--------------------------------------------------------------------------------------------------


#ifdef _DLL_DEBUG
struct DLL_InitInfo
{
    char* name;
    Place place;
};
#endif // _DLL_DEBUG
// printf("My value = %" PRIu64, value);

typedef int64_t nodeValue_t; 
#define PRInodeVal PRId64

struct DLL_Node
{
    nodeValue_t value;
    size_t nextNodeNum;
    size_t prevNodeNum;
};


struct DLL_NodeArray 
{
    DLL_Node* buffer;
    size_t nodeCount;
    size_t capacity;
    size_t free;
};


struct DoublyLinkedList
{
    DLL_NodeArray nodeArray;

    #ifdef _DLL_DEBUG
    DLL_InitInfo initInfo;
    #endif // _DLL_DEBUG
};

const size_t DLL_CAPACITY = 10;


//--------------------------------------------------------------------------------------------------


bool DLL_Init(DoublyLinkedList* doublyLinkedList
              _DLL_ON_DEBUG(,const char* name, Place place));

#define DLL_INIT(doublyLinkedList, valueSize) \
    DLL_Init(doublyLinkedList _DLL_ON_DEBUG(,GET_NAME(doublyLinkedList), GET_PLACE()))


void DLL_Delete(DoublyLinkedList* doublyLinekedList);


size_t DLL_ValueSearch(const DoublyLinkedList* doublyLinkedList, nodeValue_t value);
nodeValue_t DLL_GetNodeValue(const DoublyLinkedList* doublyLinkedList, const size_t nodeNum);

bool DLL_Insert(DoublyLinkedList* doublyLinkedList, nodeValue_t value, const size_t nodeNum);
bool DLL_PushBack(DoublyLinkedList* doublyLinkedList, nodeValue_t value);
bool DLL_PushFront(DoublyLinkedList* doublyLinkedList, nodeValue_t value);

bool DLL_Erase(DoublyLinkedList* doublyLinkedList, const size_t nodeNum);
bool DLL_PopBack(DoublyLinkedList* doublyLinkedList);
bool DLL_PopFront(DoublyLinkedList* doublyLinkedList);


//--------------------------------------------------------------------------------------------------


#endif // DOUBLY_LINKED_LIST_H