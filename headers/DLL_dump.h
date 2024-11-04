#ifndef DLL_DUMP_H
#define DLL_DUMP_H


//--------------------------------------------------------------------------------------------------


#include "doublyLinkedList.h"


struct DLL_Dumper
{
    const char* pngDumpFileName;
    const char* dotDumpFileName;
    FILE* dotDumpFile;
    size_t dumpCounter;
};


bool DumperInit(DLL_Dumper* dumper);

#ifdef _DLL_DEBUG
    #define DUMPER_INIT(dumper) DumperInit(dumper)
#else 
    #define DUMPER_INIT(dumper) 
#endif // _DLL_DUMPER


void DumperDelete(DLL_Dumper* dumper);

#ifdef _DLL_DEBUG
    #define DUMPER_DELETE(dumper) DumperDelete(dumper)
#else 
    #define DUMPER_DELETE(dumper) 
#endif // _DLL_DEBUG


void DLL_Dump(DLL_Dumper* dumper, DoublyLinkedList* doublyLinkedList, Place place);

#ifdef _DLL_DEBUG
    #define DLL_DUMP(dumper, doublyLinkedList) DLL_Dump(dumper, doublyLinkedList, GET_PLACE())
#else 
    #define DLL_DUMP(dumper, doublyLinkedList) 
#endif // _DLL_DEBUG


//--------------------------------------------------------------------------------------------------


#endif // DLL_DUMP_H