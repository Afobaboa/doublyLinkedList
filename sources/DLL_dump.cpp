#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DLL_dump.h"


//--------------------------------------------------------------------------------------------------


void PrintHeader(FILE* dotDumpFile);
void PrintNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList);
void PrintEnding(FILE* dotDumpFile);

void DeclareNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList);
void ConnectNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList);

void MakeGraph(const char* dotDumpFileName, const char* pngDumpFileName);


//--------------------------------------------------------------------------------------------------


void DLL_Dump(DoublyLinkedList* doublyLinkedList)
{
    static const char* dotDumpFileName = "DLL_dump.dot";
    static const char* pngDumpFileName = "DLL_dump.png";
    static FILE* dotDumpFile = fopen(dotDumpFileName, "w");

    PrintHeader(dotDumpFile);
    PrintNodes(dotDumpFile, doublyLinkedList);
    PrintEnding(dotDumpFile);

    fclose(dotDumpFile);
    MakeGraph(dotDumpFileName, pngDumpFileName);
}


//--------------------------------------------------------------------------------------------------


void PrintHeader(FILE* dotDumpFile)
{
    fprintf(dotDumpFile, "digraph G\n"
                         "{\n"
                         "\trankdir = LR;\n");
}


void PrintNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList)
{
    DeclareNodes(dotDumpFile, doublyLinkedList);
    ConnectNodes(dotDumpFile, doublyLinkedList);
}


void PrintEnding(FILE* dotDumpFile)
{
    fprintf(dotDumpFile, "}\n");
}


void DeclareNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList)
{
    DLL_Node node = {};
    for (size_t nodeNum = 0; nodeNum <= doublyLinkedList->capacity; nodeNum++)
    {
        node = doublyLinkedList->nodeArray[nodeNum];
        fprintf(dotDumpFile, "\tnode%zu [shape=record,label=\""
                             "{ num     | %zu            } | "
                             "{ value   | %" PRInodeVal "} | "
                             "{ nextNum | %zu            } | "
                             "{ prevNum | %zu            }\"];\n",
                             nodeNum, nodeNum, node.value, node.nextNodeNum, node.prevNodeNum);
    }
}


void ConnectNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList)
{
    DLL_Node node = {};
    for (size_t nodeNum = 0; nodeNum <= doublyLinkedList->capacity; nodeNum++)
    {
        node = doublyLinkedList->nodeArray[nodeNum];
        fprintf(dotDumpFile, "\tnode%zu -> node%zu;\n", nodeNum, node.nextNodeNum);
    }
}


void MakeGraph(const char* dotDumpFileName, const char* pngDumpFileName)
{
    static char commandForDot[100] = {};
    sprintf(commandForDot, "dot -Tpng %s -o %s", dotDumpFileName, pngDumpFileName);
    system(commandForDot);
}
