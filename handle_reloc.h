#ifndef HANDLE_RELOC_H
#define HANDLE_RELOC_H
#include "pch.h"


void manage_reloc(FileInfo* file_info, FILE* file);


BOOL get_base_address_and_size(FileInfo* file_info, DWORD* address, DWORD* size);


BOOL reloc_addresses(IMAGE_DATA_DIRECTORY* current_reloc_struct, FileInfo* file_info, DWORD base_address);


#endif 

