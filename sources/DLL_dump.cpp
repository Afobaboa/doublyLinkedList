#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DLL_dump.h"


//--------------------------------------------------------------------------------------------------


void PrintDigraphEnvironment(FILE* dotDumpFile);

void PrintHeader(FILE* dotDumpFile, const size_t dumpCounter);
void PrintNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList, Place* dumpPlace);
void PrintEnding(FILE* dotDumpFile);

void DeclareNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList, Place* dumpPlace);
void ConnectNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList);

void MakeGraph(const char* dotDumpFileName, const char* pngDumpFileName);


//--------------------------------------------------------------------------------------------------


void DLL_Dump(DoublyLinkedList* doublyLinkedList, Place place)
{
    static const char* dotDumpFileName = "DLL_dump.dot";
    static const char* pngDumpFileName = "DLL_dump.png";
    static size_t dumpCounter = 0;
    printf("counter = %zu\n", dumpCounter);

    FILE* dotDumpFile = NULL;
    if (dumpCounter > 0)
        dotDumpFile = fopen(dotDumpFileName, "a+");
    else 
    {
        dotDumpFile = fopen(dotDumpFileName, "w");
        PrintDigraphEnvironment(dotDumpFile);
    }

    PrintHeader(dotDumpFile, dumpCounter);
    PrintNodes(dotDumpFile, doublyLinkedList, &place);
    PrintEnding(dotDumpFile);

    fclose(dotDumpFile);
    MakeGraph(dotDumpFileName, pngDumpFileName);

    getchar(); //for pause
    dumpCounter++;
}


//--------------------------------------------------------------------------------------------------


void PrintDigraphEnvironment(FILE* dotDumpFile)
{
    fprintf(dotDumpFile, "digraph dumpGraph\n"
                         "{ \n");
}


void PrintHeader(FILE* dotDumpFile, const size_t dumpCounter)
{
    if (dumpCounter == 0)
        fseek(dotDumpFile, -2, SEEK_END);
    else 
        fseek(dotDumpFile, -2, SEEK_SET);
        
    fprintf(dotDumpFile, "\nsubgraph dump%zu\n"
                         "{\n"
                         "\trankdir = LR;\n",
                         dumpCounter);
}


void PrintNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList, Place* dumpPlace)
{
    DeclareNodes(dotDumpFile, doublyLinkedList, dumpPlace);
    ConnectNodes(dotDumpFile, doublyLinkedList);
}


void PrintEnding(FILE* dotDumpFile)
{
    fprintf(dotDumpFile, "}\n"
                         "}");
}


void DeclareNodes(FILE* dotDumpFile, DoublyLinkedList* doublyLinkedList, Place* dumpPlace)
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
                         "{ dumpPlace   | %s:%d } | "
                         "{ nodeCount   | %zu   } | "
                         "{ capacity    | %zu   } | "
                         "{ free        | %zu   }"
                         #ifdef _DLL_DEBUG
                         "| { listname  | %s    } | "
                         "  { initplace | %s:%d }"
                         #endif // _DLL_DEBUG
                         "\"];\n\n",
                         dumpPlace->function, dumpPlace->line,
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
    fprintf(dotDumpFile, "\tDLL -> node%zu;\n\n", nodeArray->free);

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
