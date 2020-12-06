/**
    create virtual memory and mapping the sections to memory
    @file handle_memory.cpp
    @author Shoam Kazo Cohen
*/


#include "handle_memory.h"
#include "handle_sections.h"


BOOL mapping_sections(FileInfo* file_info, SectionsInfo* section_info)
{
    BOOL result = FALSE;
    IMAGE_SECTION_HEADER* section_header = (IMAGE_SECTION_HEADER*)malloc(sizeof(IMAGE_SECTION_HEADER));

    if (NULL == file_info || NULL == section_info)
        goto clean_up;

    section_info->AddressOfNextSection = section_info->AddressOfSectionTable;

    for (DWORD i = 1; i <= section_info->NumberOfSections; i++)
    {

        result = read_section_header(file_info->File, section_info, section_header);

        if (!result)
            goto clean_up;

        if (!copy_section_to_memory(section_header, file_info->BaseAddress, file_info->File))
            goto clean_up;

    }
    section_info->AddressOfNextSection = section_info->AddressOfSectionTable;

    result = TRUE;

clean_up:
    return result;
}


BOOL allocate_memory(FileInfo* file_info)
{
    BOOL result = FALSE;
    LPVOID base_address = 0;

    if (NULL == file_info)
        goto clean_up;

    base_address = VirtualAlloc(LPVOID(file_info->ImageBase), file_info->SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (NULL == base_address)
        base_address = VirtualAlloc(NULL, file_info->SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (0 == base_address)
        goto clean_up;

    file_info->BaseAddress = (DWORD)base_address;

    result = TRUE;

clean_up:

    return result;
}


BOOL copy_section_to_memory(_IMAGE_SECTION_HEADER* section_header, DWORD base_address, FILE* file)
{
    BOOL result = FALSE;

    BYTE* data = NULL;

    if (NULL == section_header || NULL == base_address || NULL == file) {
        goto clean_up;
    }

    data = (BYTE*)malloc(sizeof(section_header->SizeOfRawData));

    if (NULL == data)
        goto clean_up;

    if (!read_section_data(section_header, file, data)) {
        goto clean_up;
    }

    memcpy(LPVOID(base_address + section_header->VirtualAddress), data, section_header->SizeOfRawData);

    result = TRUE;

clean_up:
    return result;
}


BOOL manage_access(_IMAGE_SECTION_HEADER* section_header, FileInfo* file_info)
{
    DWORD Characteristics;
    LPVOID start_section_address;
    DWORD* last_access = (DWORD*)malloc(sizeof(DWORD));

    if (NULL == last_access || NULL == section_header || NULL == file_info)
        goto clean_up;

    Characteristics = section_header->Characteristics;

    start_section_address = LPVOID(file_info->BaseAddress + section_header->VirtualAddress);

    if (Characteristics > 0xE0000000)
    {
        if (!VirtualProtect(start_section_address, section_header->Misc.VirtualSize, PAGE_EXECUTE_READWRITE, last_access))
            printf("failed to change the access");
    }
    else if (Characteristics > 0xC0000000)
    {
        if (!VirtualProtect(start_section_address, section_header->Misc.VirtualSize, PAGE_READWRITE, last_access))
            printf("failed to change the access");
    }
    else if (Characteristics > 0x60000000)
    {
        if (!VirtualProtect(start_section_address, section_header->Misc.VirtualSize, PAGE_EXECUTE_READ, last_access))
            printf("failed to change the access");
    }
    else if (Characteristics > 0x40000000)
    {
        if (!VirtualProtect(start_section_address, section_header->Misc.VirtualSize, PAGE_READONLY, last_access))
            printf("failed to change the access");
    }
    else if (Characteristics > 0x20000000)
    {
        if (!VirtualProtect(start_section_address, section_header->Misc.VirtualSize, PAGE_EXECUTE, last_access))
            printf("failed to change the access");
    }
    else
    {
        if (!VirtualProtect(start_section_address, section_header->Misc.VirtualSize, PAGE_NOACCESS, last_access))
            printf("failed to change the access");
    }

    return TRUE;

clean_up:
    free(last_access);
    return FALSE;
}
