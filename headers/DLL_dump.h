#ifndef DLL_DUMP_H
#define DLL_DUMP_H


//--------------------------------------------------------------------------------------------------


#include "doublyLinkedList.h"


bool DumperInit();

#ifdef _DLL_DEBUG
    #define DUMPER_INIT() DumperInit()
#else 
    #define DUMPER_INIT() 
#endif // _DLL_DUMPER


void DumperDelete();

#ifdef _DLL_DEBUG
    #define DUMPER_DELETE() DumperDelete()
#else 
    #define DUMPER_DELETE() 
#endif // _DLL_DEBUG


void DLL_Dump(DoublyLinkedList* doublyLinkedList, Place place);

#ifdef _DLL_DEBUG
    #define DLL_DUMP(doublyLinkedList) DLL_Dump(doublyLinkedList, GET_PLACE())
#else 
    #define DLL_DUMP(doublyLinkedList) 
#endif // _DLL_DEBUG


//--------------------------------------------------------------------------------------------------


#endif // DLL_DUMP_H