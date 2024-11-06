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

    // INSERT
    // DLL_Insert(&DLL, 52,     0);
    // DLL_Insert(&DLL, 228,    0);
    // DLL_Insert(&DLL, 323232, 0);
    // DLL_Insert(&DLL, 239,    3);
    // DLL_Insert(&DLL, 566,    3);

    
    // GET VALUE and VALUE SEARCH
    DLL_Insert(&DLL, 52,  0);
    DLL_Insert(&DLL, 111, 0);
    DLL_DUMP(&DLL);

    size_t nodeNum = (size_t) -1;
    nodeNum = DLL_ValueSearch(&DLL, 100);
    ColoredPrintf(YELLOW, "index = %zu\n", nodeNum);
    nodeNum = DLL_ValueSearch(&DLL, 52);
    ColoredPrintf(YELLOW, "index = %zu\n", nodeNum);

    nodeValue_t value = -1;
    value = DLL_GetNodeValue(&DLL, 5);
    ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);
    value = DLL_GetNodeValue(&DLL, 1);
    ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);
    value = DLL_GetNodeValue(&DLL, nodeNum);
    ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);



    DLL_DUMP(&DLL);
    DUMPER_DELETE();
    
    DLL_Delete(&DLL);

    return 0;
}