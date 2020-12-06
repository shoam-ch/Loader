#pragma once
#ifndef HANDLE_SECTIONS_H
#define HANDLE_SECTIONS_H
#include "pch.h"


/**
* gets the address where the sections table is locate in the EXE file
* @params: a pointer to the FileInfo struct
* @return: the address of the sections table
*/
BOOL get_sections_table_info(FileInfo* file_info, SectionsInfo* section_info);


/**
* read the section header from the EXE file and cast it into an IMAGE_SECTION_HEADER
* @params: the EXE file object and the address where the data of the section is locate
* @return: a pointer to an IMAGE_SECTION_HEADER struct
*/
BOOL read_section_header(FILE* file, SectionsInfo* section_info, IMAGE_SECTION_HEADER* section_header);


/**
* read the section data from the EXE file
* @params: the section that need to be read from the EXE file and the EXE file object
* @return: a pointer to the section data from the EXE file
*/
BOOL read_section_data(_IMAGE_SECTION_HEADER* section_header, FILE* file, BYTE* data);


void destroy_sections(IMAGE_SECTION_HEADER* sections);


void destroy_section_info(SectionsInfo* section_info);


#endif 
