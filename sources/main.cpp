#include <stdio.h>
#include <unistd.h>

#include "doublyLinkedList.h"
#include "DLL_dump.h"


int main() 
{   
    DoublyLinkedList DLL = {};
    DLL_INIT(&DLL, 8);

    // #ifdef _DLL_SUPER_DUMP
    // printf("debug is switched on\n");
    // #else
    // printf("debug is switched off\n");
    // #endif

    DUMPER_INIT();

    DLL_DUMP(&DLL);
    DLL_Insert(&DLL, 52, 0);
    DLL_Insert(&DLL, 228, 0);
    DLL_Insert(&DLL, 323232, 0);
    DLL_Insert(&DLL, 239, 3);
    DLL_Insert(&DLL, 566, 3);
    DLL_DUMP(&DLL);

    DUMPER_DELETE();
    
    DLL_Delete(&DLL);

    return 0;
}