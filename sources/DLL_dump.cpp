#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DLL_dump.h"


//--------------------------------------------------------------------------------------------------


struct DLL_Dumper
{
    const char* pngDumpFileName;
    const char* dotDumpFileName;
    FILE* dotDumpFile;
    size_t dumpCounter;
};

static DLL_Dumper dumper = {};


//--------------------------------------------------------------------------------------------------


void PrintDigraphEnvironment();

void PrintHeader();
void PrintNodes(DoublyLinkedList* doublyLinkedList, Place* dumpPlace);
void PrintEnding();

void DeclareNodes(DoublyLinkedList* doublyLinkedList, Place* dumpPlace);
void ConnectNodes(DoublyLinkedList* doublyLinkedList);

void MakeGraph();


//--------------------------------------------------------------------------------------------------


bool DumperInit()
{
    static bool dumperIsInit = false;
    if (dumperIsInit)
        return false;

    dumper.dotDumpFileName = "DLL_dump.dot";
    dumper.pngDumpFileName = "DLL_dump.png";
    dumper.dumpCounter     = 0;

    dumper.dotDumpFile = fopen(dumper.dotDumpFileName, "w");
    if (dumper.dotDumpFile == NULL)
        return false;

    PrintDigraphEnvironment();
    
    dumperIsInit = true;
    return false;
}


void DumperDelete()
{
    fclose(dumper.dotDumpFile);

    dumper.dotDumpFile     = NULL;
    dumper.dotDumpFileName = "";
    dumper.pngDumpFileName = "";
    dumper.dumpCounter     = 0;
}


void DLL_Dump(DoublyLinkedList* doublyLinkedList, Place place)
{
    // printf("counter = %zu\n", dumper->dumpCounter);

    PrintHeader();
    PrintNodes(doublyLinkedList, &place);
    PrintEnding();
    fflush(dumper.dotDumpFile);

    MakeGraph();

    getchar(); // for pause
    dumper.dumpCounter++;
}


//--------------------------------------------------------------------------------------------------


void PrintDigraphEnvironment()
{
    fprintf(dumper.dotDumpFile, "digraph dumpGraph\n"
                                "{\n"
                                "\trankdir = LR; \n");
}


void PrintHeader()
{
    fseek(dumper.dotDumpFile, -2, SEEK_END);
        
    fprintf(dumper.dotDumpFile, "\nsubgraph dump%zu\n"
                                "{\n"
                                "\trankdir = LR;\n",
                                dumper.dumpCounter);
}


void PrintNodes(DoublyLinkedList* doublyLinkedList, Place* dumpPlace)
{
    DeclareNodes(doublyLinkedList, dumpPlace);
    ConnectNodes(doublyLinkedList);
}


void PrintEnding()
{
    fprintf(dumper.dotDumpFile, "}\n"
                                "}");
}


void DeclareNodes(DoublyLinkedList* doublyLinkedList, Place* dumpPlace)
{
    DLL_NodeArray* nodeArray = &doublyLinkedList->nodeArray;
    #ifdef _DLL_DEBUG
    DLL_InitInfo* initInfo = &doublyLinkedList->initInfo;
    #endif

    static DLL_Node node = {};
    for (size_t nodeRealIndex = 0; nodeRealIndex <= nodeArray->capacity; nodeRealIndex++)
    {
        node = nodeArray->buffer[nodeRealIndex];
        fprintf(dumper.dotDumpFile, "\tnode%zu_%zu [shape=record,label=\""
                                    "{ num     | %zu            } | "
                                    "{ value   | %" PRInodeVal "} | "
                                    "{ nextNum | %zu            } | "
                                    "{ prevNum | %zu            }\"];\n",
                                    dumper.dumpCounter, nodeRealIndex, 
                                    nodeRealIndex, 
                                    node.value, 
                                    node.nextnodeLogicIndex, 
                                    node.prevnodeLogicIndex);
    }
    fprintf(dumper.dotDumpFile, "\n");

    for (size_t nodeRealIndex = 0; nodeRealIndex < nodeArray->capacity; nodeRealIndex++)
    {
        fprintf(dumper.dotDumpFile, "\tnode%zu_%zu -> node%zu_%zu[weight = 1000, color = white]\n",
                dumper.dumpCounter, nodeRealIndex, dumper.dumpCounter, nodeRealIndex + 1);
    }
    fprintf(dumper.dotDumpFile, "\n");

    fprintf(dumper.dotDumpFile, "\tDLL%zu [shape = record, label = \""
                                "{ dumpNum     | %zu   } | "
                                "{ dumpPlace   | %s:%d } | "
                                "{ nodeCount   | %zu   } | "
                                "{ capacity    | %zu   } | "
                                "{ firstFreenodeLogicIndex        | %zu   }"
                                #ifdef _DLL_DEBUG
                                " | { listName  | %s    } | "
                                "   { initPlace | %s:%d }"
                                #endif // _DLL_DEBUG
                                "\"];\n\n",
                                dumper.dumpCounter,
                                dumper.dumpCounter,
                                dumpPlace->function, dumpPlace->line,
                                nodeArray->nodeCount,
                                nodeArray->capacity,
                                nodeArray->firstFreenodeLogicIndex
        
                                #ifdef _DLL_DEBUG
                                , initInfo->name
                                , initInfo->place.file
                                , initInfo->place.line
                                #endif // _DLL_DEBUG
                                );
}


void ConnectNodes(DoublyLinkedList* doublyLinkedList)
{
    DLL_NodeArray* nodeArray = &doublyLinkedList->nodeArray;
    fprintf(dumper.dotDumpFile, "\tDLL%zu -> node%zu_%zu;\n\n", 
            dumper.dumpCounter, dumper.dumpCounter, nodeArray->firstFreenodeLogicIndex);

    static DLL_Node node = {};
    for (size_t nodeRealIndex = 0; nodeRealIndex <= nodeArray->capacity; nodeRealIndex++)
    {
        node = nodeArray->buffer[nodeRealIndex];
        fprintf(dumper.dotDumpFile, "\tnode%zu_%zu -> node%zu_%zu;\n", 
                dumper.dumpCounter, nodeRealIndex, dumper.dumpCounter, node.nextnodeLogicIndex);
    }
    fprintf(dumper.dotDumpFile, "\n");
}


void MakeGraph()
{
    const size_t MAX_COMMAND_LENGTH = 100;
    char commandForDot[MAX_COMMAND_LENGTH] = {};
    sprintf(commandForDot, "dot -Tpng %s -o %s", dumper.dotDumpFileName, dumper.pngDumpFileName);
    system(commandForDot);
}
