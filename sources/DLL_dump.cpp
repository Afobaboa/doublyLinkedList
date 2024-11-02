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
    DLL_NodeArray* nodeArray = &doublyLinkedList->nodeArray;
    #ifdef _DLL_DEBUG
    DLL_InitInfo* initInfo = &doublyLinkedList->initInfo;
    #endif

    static DLL_Node node = {};
    for (size_t nodeNum = 0; nodeNum <= nodeArray->capacity; nodeNum++)
    {
        node = nodeArray->buffer[nodeNum];
        fprintf(dotDumpFile, "\tnode%zu [shape=record,label=\""
                             "{ num     | %zu            } | "
                             "{ value   | %" PRInodeVal "} | "
                             "{ nextNum | %zu            } | "
                             "{ prevNum | %zu            }\"];\n",
                             nodeNum, nodeNum, node.value, node.nextNodeNum, node.prevNodeNum);
    }
    fprintf(dotDumpFile, "\n");

    for (size_t nodeNum = 0; nodeNum < nodeArray->capacity; nodeNum++)
    {
        fprintf(dotDumpFile, "\tnode%zu -> node%zu[weight = 1000, color = white]\n",
                nodeNum, nodeNum + 1);
    }
    fprintf(dotDumpFile, "\n");

    fprintf(dotDumpFile, "\tDLL [shape = record, label = \""
                         "{ nodeCount | %zu   } | "
                         "{ capacity  | %zu   } | "
                         "{ free      | %zu   }"
                         #ifdef _DLL_DEBUG
                         "| { name     | %s    } | "
                         "  { place    | %s:%d }"
                         #endif // _DLL_DEBUG
                         "\"];\n\n",
                         nodeArray->nodeCount,
                         nodeArray->capacity,
                         nodeArray->free

                         #ifdef _DLL_DEBUG
                         , initInfo->name
                         , initInfo->place.file
                         , initInfo->place.line
                         #endif // _DLL_DEBUG
                         );
}


void ConnectNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList)
{
    DLL_NodeArray* nodeArray = &doublyLinkedList->nodeArray;
    fprintf(dotDumpFile, "DLL -> node%zu;\n\n", nodeArray->free);

    static DLL_Node node = {};
    for (size_t nodeNum = 0; nodeNum <= nodeArray->capacity; nodeNum++)
    {
        node = nodeArray->buffer[nodeNum];
        fprintf(dotDumpFile, "\tnode%zu -> node%zu;\n", nodeNum, node.nextNodeNum);
    }
    fprintf(dotDumpFile, "\n");
}


void MakeGraph(const char* dotDumpFileName, const char* pngDumpFileName)
{
    static char commandForDot[100] = {};
    sprintf(commandForDot, "dot -Tpng %s -o %s", dotDumpFileName, pngDumpFileName);
    system(commandForDot);
}
