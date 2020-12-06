/**
    read the headers from the file and create new struct that contain both
    @file read_headers.cpp
    @author Shoam Kazo Cohen
*/


#include "read_headers.h"


BOOL read_to_file_info_struct(FILE* file, FileInfo* file_info)
{
    BOOL result = FALSE;
    DWORD address_of_nt_header = 0;

    _IMAGE_DOS_HEADER* dos_header = NULL;
    _IMAGE_NT_HEADERS*  nt_header = NULL;

    if (NULL == file) {
        goto clean_up;
    }

    dos_header = (_IMAGE_DOS_HEADER*)malloc(sizeof(IMAGE_DOS_HEADER));
    nt_header = (_IMAGE_NT_HEADERS*)malloc(sizeof(IMAGE_NT_HEADERS));

    if (NULL == dos_header || NULL == nt_header) {
        goto clean_up;
    }

     result = read_DOS_headers(file, dos_header);

     if (!result) {
         goto clean_up;
     }

    address_of_nt_header = dos_header->e_lfanew;

    result = read_NT_headers(file, address_of_nt_header, nt_header);

    if (!result) {
        goto clean_up;
    }

    file_info->DosHeader = dos_header;
    file_info->NtHeader = nt_header;
    file_info->ImageBase = nt_header->OptionalHeader.ImageBase;
    file_info->SizeOfImage = nt_header->OptionalHeader.SizeOfImage;

    //nt_header = NULL;
    //dos_header = NULL;

    result = TRUE;

clean_up:

    if (NULL != nt_header || NULL != dos_header) {
        destroy_headers(dos_header, nt_header);
    }

    return result;
}


BOOL read_DOS_headers(FILE* file, IMAGE_DOS_HEADER* dos_header)
{
    BOOL result = FALSE;

    if (NULL == file || NULL == dos_header) {
        goto clean_up;
    }

    if (fread(dos_header, 1, sizeof(*dos_header), file) != sizeof(*dos_header)) {
        goto clean_up;
    }

    result = TRUE;

clean_up:

    return result;
}


BOOL read_NT_headers(FILE* file, DWORD address, IMAGE_NT_HEADERS* nt_header)
{
    BOOL result = FALSE;

    if (NULL == file || NULL == nt_header) {
        goto clean_up;
    }

    if (fseek(file, address, SEEK_SET) != 0) {
        goto clean_up;
    }

    if (fread(nt_header, 1, sizeof(*nt_header), file) != sizeof(*nt_header)) {
        goto clean_up;
    }

    result = TRUE;

clean_up:

    return result;
}



void destroy_headers(IMAGE_DOS_HEADER* dos_header, IMAGE_NT_HEADERS* nt_header)
{
    if (dos_header) {
        free(dos_header);
    }

    if (nt_header) {
        free(nt_header);
    }
}


void destroy_file_info(FileInfo* file_info)
{
    destroy_headers(file_info->DosHeader, file_info->NtHeader);
    if (file_info) {
        free(file_info);
    }
}


