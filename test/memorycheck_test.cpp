#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "memory_check.h"
#include "config.h"

using namespace std;
using namespace bobo;

int main(int argc, char *argv[])
{
    const char* s20 = "this is 20 characte";
    const char* s30 = "this is 30 characters long, o";
    const char* s40 = "this is 40 characters long, okey dokeys";
    const char *filename = "test/memorycheck_test.cpp";
    
    TRACE("char* victim = new char[20]");
    char* victim = new char[20];
    strcpy(victim, s20);
    MemoryCheck::ValidateMemoryAll();

    TagElem *victimInfo = (TagElem *)(victim - sizeof(int) - sizeof(TagElem));
    TRACE("%s", victimInfo->fileName);
    if (strcmp(victimInfo->fileName, filename) != 0)
    {
        assert(false && "victimInfo->fileName != filename");
        abort();
    }

    TRACE("%d", victimInfo->size);
    if (victimInfo->size != 20)
    {
        assert(false && "victimInfo->size != 20");
        abort();
    }
        

    TRACE("char* victim2 = new char[30]");
    char* victim2 = new char[30];
    strcpy(victim2, s30);
    MemoryCheck::ValidateMemoryAll();

    TRACE("char* victim3 = new char[20]");
    char* victim3 = new char[20];
    strcpy(victim3, s20);
    MemoryCheck::ValidateMemoryAll();
    TRACE("char* victim4 = new char[40]");
    char* victim4 = new char[40];
    strcpy(victim4, s40);
    MemoryCheck::ValidateMemoryAll();
    TRACE("char* victim5 = new char[30]");
    char* victim5 = new char[30];
    strcpy(victim5, s30);
    MemoryCheck::ValidateMemoryAll();
    
    TRACE("delete all");
    delete victim3;
    MemoryCheck::ValidateMemoryAll();
    delete victim4;
    MemoryCheck::ValidateMemoryAll();
    delete victim;
    MemoryCheck::ValidateMemoryAll();
    delete victim5;
    MemoryCheck::ValidateMemoryAll();

    // memory leak
    //delete victim2;
    MemoryCheck::ValidateMemoryAll();

    // delete wild pointer
    // delete victim4;
    MemoryCheck::ValidateMemoryAll();

    if (MemoryCheck::ValidateMemoryAll() != 0)
        assert(false && "memory leak");

    return 0;
}