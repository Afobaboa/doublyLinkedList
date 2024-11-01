#include <stdio.h>

#include "doublyLinkedList.h"
#include "DLL_dump.h"


int main() 
{   
    DoublyLinkedList DLL = {};
    DLL_INIT(&DLL, 8);

    DLL_Dump(&DLL);

    DLL_Delete(&DLL);

    return 0;
}