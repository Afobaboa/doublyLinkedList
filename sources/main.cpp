#include <stdio.h>
#include <unistd.h>

#include "doublyLinkedList.h"
#include "DLL_dump.h"


static void DLL_InsertTest(DoublyLinkedList* doublyLinkedList);
static void DLL_EraseTest(DoublyLinkedList* doublyLinkedList);
static void DLL_SearchTest(DoublyLinkedList* doublyLinkedList);


int main() 
{   
    DoublyLinkedList DLL = {};
    DLL_INIT(&DLL);
    DUMPER_INIT();
    DLL_DUMP(&DLL);

    // INSERT
    DLL_InsertTest(&DLL);

    // ERASE
    // DLL_EraseTest(&DLL);

    // GET VALUE and VALUE SEARCH
    // DLL_SearchTest(&DLL);

    DLL_DUMP(&DLL);
    DUMPER_DELETE();
    DLL_Delete(&DLL);

    return 0;
}


static void DLL_InsertTest(DoublyLinkedList* doublyLinkedList)
{
    DLL_Insert(doublyLinkedList, 52,     0);    // 52
    DLL_Insert(doublyLinkedList, 228,    0);    // 228, 52
    DLL_Insert(doublyLinkedList, 323232, 0);    // 323232, 228, 52
    DLL_Insert(doublyLinkedList, 239,    3);    // 323232, 228, 52, 239
    DLL_Insert(doublyLinkedList, 566,    3);    // 323232, 228, 52, 566, 239
    DLL_Insert(doublyLinkedList, 12345,  11);   // ERROR

    DLL_DUMP(doublyLinkedList);
}


static void DLL_EraseTest(DoublyLinkedList* doublyLinkedList)
{
    DLL_InsertTest(doublyLinkedList);

    DLL_Erase(doublyLinkedList, 5);     // 323232, 228, 52, 566
    DLL_Erase(doublyLinkedList, 1);     // 228, 52, 566
    DLL_Erase(doublyLinkedList, 6);     // ERROR

    DLL_DUMP(doublyLinkedList);
}


static void DLL_SearchTest(DoublyLinkedList* doublyLinkedList)
{
    DLL_Insert(doublyLinkedList, 52,  0);
    DLL_Insert(doublyLinkedList, 111, 0);
    DLL_DUMP(doublyLinkedList);

    size_t nodeRealIndex = (size_t) -1;
    nodeRealIndex = DLL_ValueSearch(doublyLinkedList, 100);
    ColoredPrintf(YELLOW, "index = %zu\n", nodeRealIndex);
    nodeRealIndex = DLL_ValueSearch(doublyLinkedList, 52);
    ColoredPrintf(YELLOW, "index = %zu\n", nodeRealIndex);

    nodeValue_t value = -1;
    value = DLL_GetNodeValue(doublyLinkedList, 5);
    ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);
    value = DLL_GetNodeValue(doublyLinkedList, 1);
    ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);
    value = DLL_GetNodeValue(doublyLinkedList, nodeRealIndex);
    ColoredPrintf(YELLOW, "value = %" PRInodeVal "\n", value);
}
