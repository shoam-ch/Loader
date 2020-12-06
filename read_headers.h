#ifndef READ_HEADER_H
#define READ_HEADER_H
#include "pch.h"


/**
* create a FileInfo struct with the appropriate values
* @params: the EXE file object
* @return: a pointer to the FileInfo struct
*/
BOOL read_to_file_info_struct(FILE* file, FileInfo* file_info);


/**
* read the DOS_header from the file and cast it into an IMAGE_DOS_HEADER struct
* @params: the EXE file object
* @return: a pointer to an IMAGE_DOS_HEADER struct
*/
BOOL read_DOS_headers(FILE* file, IMAGE_DOS_HEADER* dos_header);


/**
* read the NT_header from the file and cast it into an IMAGE_NT_HEADER struct
* @params: the EXE file object and the address where the NT header start
* @return: a pointer to an IMAGE_NT_HEADER struct
*/
BOOL read_NT_headers(FILE* file, DWORD address, IMAGE_NT_HEADERS* nt_header);


void destroy_headers(IMAGE_DOS_HEADER* dos_header, IMAGE_NT_HEADERS* nt_header);


void destroy_file_info(FileInfo* file_info);


#endif