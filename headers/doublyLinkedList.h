#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


//--------------------------------------------------------------------------------------------------


#include <stddef.h>

#include "../logPrinter/logPrinter.h"


#define _DLL_DEBUG

#ifdef _DLL_DEBUG
    #define _DLL_ON_DEBUG(...) __VA_ARGS__
#else 
    #define _DLL_ON_DEGUG(...) 
#endif // _DLL_DEBUG


//--------------------------------------------------------------------------------------------------


#ifdef _DLL_DEBUG
struct DLL_InitInfo
{
    char* name;
    Place place;
};
#endif // _DLL_DEBUG


struct DLL_Node
{
    size_t nextNodeNum;
    size_t prevNodeNum;
};


struct DLL_ValueBuffer 
{
    void*  buffer;
    size_t valueSize;
    size_t capacity;
};


struct DoublyLinkedList
{
    DLL_Node* nodeArray;
    DLL_ValueBuffer valueBuffer;

    #ifdef _DLL_DEBUG
    DLL_InitInfo initInfo;
    #endif // _DLL_DEBUG
};

const size_t MIN_DLL_CAPACITY = 10;


//--------------------------------------------------------------------------------------------------


bool DLL_Init(DoublyLinkedList* doublyLinkedList, const size_t valueSize
              _DLL_ON_DEBUG(,const char* name, Place place));

#define DLL_INIT(doublyLinkedList, valueSize) \
    DLL_Init(doublyLinkedList, valueSize _DLL_ON_DEBUG(,GET_NAME(doublyLinkedList), GET_PLACE()))


void DLL_Delete(DoublyLinkedList* doublyLinekedList);


//--------------------------------------------------------------------------------------------------


#endif // DOUBLY_LINKED_LIST_H