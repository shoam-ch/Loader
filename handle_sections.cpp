/**
    read the section table from the file and read the data of every section from the file
    @file handle_sections.cpp
    @author Shoam Kazo Cohen
*/


#include "handle_sections.h"


BOOL get_sections_table_info(FileInfo* file_info, SectionsInfo* section_info)
{
    if (NULL == file_info || NULL == section_info)
        return FALSE;

    section_info->AddressOfSectionTable = file_info->DosHeader->e_lfanew + sizeof(_IMAGE_NT_HEADERS);
    section_info->AddressOfNextSection = section_info->AddressOfSectionTable;
    section_info->NumberOfSections = file_info->NtHeader->FileHeader.NumberOfSections;
    section_info->SectionAlignment = file_info->NtHeader->OptionalHeader.SectionAlignment;

    return TRUE;
}


BOOL read_section_header(FILE* file, SectionsInfo* section_info, IMAGE_SECTION_HEADER* section_header)
{
    BOOL result = FALSE;

    if (NULL == file || NULL == section_info || NULL == section_header)
        goto clean_up;

    if (fseek(file, section_info->AddressOfNextSection, SEEK_SET) != 0) {
        goto clean_up;
    }

    if (fread(section_header, 1, sizeof(IMAGE_SECTION_HEADER), file) != sizeof(IMAGE_SECTION_HEADER)) {
        goto clean_up;
    }

    section_info->AddressOfNextSection += sizeof(IMAGE_SECTION_HEADER);

    result = TRUE;

clean_up:

    return result;
}


BOOL read_section_data(_IMAGE_SECTION_HEADER* section_header, FILE* file, BYTE* data)
{
    BOOL result = FALSE;
    DWORD raw_size = 0;
    DWORD raw_address = 0;

    if (NULL == data || NULL == section_header || NULL == file)
        goto clean_up;

    raw_size = section_header->SizeOfRawData;
    raw_address = section_header->PointerToRawData;


    if (fseek(file, raw_address, SEEK_SET) != 0) {
        goto clean_up;
    }

    if (fread(raw_address, data, 1, file)) {
        goto clean_up;
    }

    result = TRUE;

clean_up:

    return result;
}


void destroy_sections(IMAGE_SECTION_HEADER* sections)
{
    if (sections) {
        free(sections);
    }
}

void destroy_section_info(SectionsInfo* section_info)
{
    if (section_info) {
        free(section_info);
    }
}