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
    // DLL_Insert(&DLL, 52,     0);    // 52
    // DLL_Insert(&DLL, 228,    0);    // 228, 52
    // DLL_Insert(&DLL, 323232, 0);    // 323232, 228, 52
    // DLL_Insert(&DLL, 239,    3);    // 323232, 228, 52, 239
    // DLL_Insert(&DLL, 566,    3);    // 323232, 228, 52, 566, 239
    // DLL_Insert(&DLL, 12345,  11);   // ERROR


    // ERASE
    // DLL_Erase(&DLL, 5);     // 323232, 228, 52, 566
    // DLL_Erase(&DLL, 1);     // 228, 52, 566
    // DLL_Erase(&DLL, 6);     // ERROR

    
    // GET VALUE and VALUE SEARCH
    // DLL_Insert(&DLL, 52,  0);
    // DLL_Insert(&DLL, 111, 0);
    // DLL_DUMP(&DLL);

    // size_t nodeNum = (size_t) -1;
    // nodeNum = DLL_ValueSearch(&DLL, 100);
    // ColoredPrintf(YELLOW, "index = %zu\n", nodeNum);
    // nodeNum = DLL_ValueSearch(&DLL, 52);
    // ColoredPrintf(YELLOW, "index = %zu\n", nodeNum);

    // nodeValue_t value = -1;
    // value = DLL_GetNodeValue(&DLL, 5);
    // ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);
    // value = DLL_GetNodeValue(&DLL, 1);
    // ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);
    // value = DLL_GetNodeValue(&DLL, nodeNum);
    // ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);


    DLL_DUMP(&DLL);
    DUMPER_DELETE();
    
    DLL_Delete(&DLL);

    return 0;
}