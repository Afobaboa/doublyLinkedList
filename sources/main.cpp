#include <stdio.h>
#include <unistd.h>

#include "doublyLinkedList.h"
#include "DLL_dump.h"


int main() 
{   
    DoublyLinkedList DLL = {};
    DLL_INIT(&DLL, 8);

    // #ifdef _DLL_DEBUG
    // printf("debug is switched on\n");
    // #else
    // printf("debug is switched off\n");
    // #endif

    DLL_Dumper dumper = {};
    DUMPER_INIT(&dumper);

    DLL_DUMP(&dumper, &DLL);
    DLL_DUMP(&dumper, &DLL);
    DLL_DUMP(&dumper, &DLL);
    DLL_DUMP(&dumper, &DLL);
    DLL_DUMP(&dumper, &DLL);

    DUMPER_DELETE(&dumper);
    
    DLL_Delete(&DLL);

    return 0;
}