#include <stdio.h>

#include "../headers/doublyLinkedList.h"


int main() 
{   
    DoublyLinkedList DLL = {};
    DLL_INIT(&DLL, 8);
    DLL_Delete(&DLL);

    return 0;
}