#ifndef DLL_DUMP_H
#define DLL_DUMP_H


//--------------------------------------------------------------------------------------------------


#include "doublyLinkedList.h"


void DLL_Dump(DoublyLinkedList* doublyLinkedList, Place place);

#define DLL_DUMP(doublyLinkedList) \
    DLL_Dump(doublyLinkedList, GET_PLACE())


//--------------------------------------------------------------------------------------------------


#endif // DLL_DUMP_H