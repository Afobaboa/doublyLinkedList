#include <stdlib.h>

#include "../headers/doublyLinkedList.h"


//--------------------------------------------------------------------------------------------------


bool DLL_Init(DoublyLinkedList* doublyLinkedList, const size_t valueSize
              _DLL_ON_DEBUG(,const char* name, Place place))
{
    #ifdef _DLL_DEBUG
    if (doublyLinkedList == NULL)
        return false;

    doublyLinkedList->initInfo = {.name  = (char*) name, 
                                  .place = place};
    #endif // _DLL_DEBUG

    if (valueSize == 0)
        return false;

    doublyLinkedList->nodeArray = (DLL_Node*) calloc(MIN_DLL_CAPACITY, sizeof(DLL_Node));
    if (doublyLinkedList->nodeArray == NULL)
        return false;

    doublyLinkedList->valueBuffer.buffer = calloc(MIN_DLL_CAPACITY,valueSize);
    if (doublyLinkedList->valueBuffer.buffer == NULL)
        return false;

    doublyLinkedList->valueBuffer.capacity  = MIN_DLL_CAPACITY;
    doublyLinkedList->valueBuffer.valueSize = valueSize;

    return true;
}


void DLL_Delete(DoublyLinkedList* doublyLinekedList)
{
    free(doublyLinekedList->nodeArray);
    free(doublyLinekedList->valueBuffer.buffer);
    *doublyLinekedList = {};
}
