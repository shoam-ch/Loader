#pragma once
#ifndef PCH_H
#define PCH_H


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <winnt.h>

/**
* declare a struct that contain the headers of the PE format and some useful fields
*/
typedef struct FileInfo{
    _IMAGE_DOS_HEADER* DosHeader;
    _IMAGE_NT_HEADERS* NtHeader;
    FILE* File;
    DWORD ImageBase;
    DWORD SizeOfImage;
    DWORD BaseAddress;
}FileInfo;

typedef struct SectionsInfo {
    DWORD AddressOfSectionTable;
    DWORD NumberOfSections;
    DWORD SectionAlignment;
}SectionsInfo;

#endif // !PCH_H
BOOL result = FALSE;
if (true) {
    goto clean_up;
}

result = TRUE;

clean_up:
return result;