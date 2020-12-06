#pragma once
#ifndef HANDLE_MEMORY_H
#define HANDLE_MEMORY_H
#include "pch.h"


/**
* allocating virtual memory and mapping every sections into the virtual memory
* @params: a pointer to the FileInfo struct, the EXE file object and the start address of the
*  section in the EXE file
* @return: if the function succeded or failed
*/
BOOL mapping_sections(FileInfo* file_info, SectionsInfo* section_info);


/**
* copy the section into the virtual memory
* @params: a pointer to the _IMAGE_SECTION_HEADER that contain the section, the start address of the
*  section in the EXE file, and a pointer to the FileInfo struct
* @return: if the function succeded or failed
*/
BOOL copy_section_to_memory(_IMAGE_SECTION_HEADER* section_header, DWORD base_address, FILE* file);


/**
* allocating the virtual memory to the file
* @params: a pointer to the FileInfo struct
* @return: if the function succeded or failed
*/
BOOL allocate_memory(FileInfo* file_info);


/**
* mapping the section into the virtual memory and change the access of the section in the memory
* @params: a pointer to an IMAGE_SECTION_HEADER that contain the section and
*  and the EXE file object
* @return: if the function succeded or failed
*/
//BOOL manage_access(_IMAGE_SECTION_HEADER* section_header, FileInfo* file_info);


#endif 
