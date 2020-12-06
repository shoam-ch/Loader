#include "handle_reloc.h"


void manage_reloc(FileInfo* file_info, FILE* file)
{
	DWORD* base_address_of_reloc_section = (DWORD*)malloc(sizeof(DWORD));
	DWORD* size_of_reloc_structs = (DWORD*)malloc(sizeof(DWORD));
	DWORD* current_address = (DWORD*)malloc(sizeof(DWORD));

	if (NULL == base_address_of_reloc_section || NULL == size_of_reloc_structs || NULL == current_address)
		goto clean_up;
	if (!get_base_address_and_size(file_info, base_address_of_reloc_section, size_of_reloc_structs))
		goto clean_up;

	*current_address = file_info->BaseAddress + *base_address_of_reloc_section;

	while (*current_address < *base_address_of_reloc_section + *size_of_reloc_structs + file_info->BaseAddress)
	{
		IMAGE_DATA_DIRECTORY* current_reloc_struct = (IMAGE_DATA_DIRECTORY*)*current_address;
		BOOL result = reloc_addresses(current_reloc_struct, file_info, *current_address);
		*current_address += current_reloc_struct->Size;
	}
clean_up:
	return;
}


BOOL get_base_address_and_size(FileInfo* file_info, DWORD* address, DWORD* size)
{
	BOOL result = FALSE;
	if (NULL == file_info || NULL == address || NULL == size)
		goto clean_up;
	*address = file_info->NtHeader->OptionalHeader.DataDirectory[5].VirtualAddress;
	*size = file_info->NtHeader->OptionalHeader.DataDirectory[5].Size;

	result = TRUE;

clean_up:

	return result;
}



BOOL reloc_addresses(IMAGE_DATA_DIRECTORY* current_reloc_struct, FileInfo* file_info, DWORD current_address)
{
	DWORD* address_to_reloc;
	DWORD** change;


	DWORD difference_between_load_addresses = file_info->BaseAddress - file_info->ImageBase;

	DWORD range_of_addresses = current_reloc_struct->VirtualAddress + file_info->BaseAddress;

	WORD* addresses = (WORD*)(current_address + sizeof(IMAGE_DATA_DIRECTORY));



	for (int i = 0; i < (current_reloc_struct->Size - sizeof(IMAGE_DATA_DIRECTORY)) / sizeof(WORD) - 1; i++)
	{
		address_to_reloc = (DWORD*)(range_of_addresses + addresses[i] - 0x3000);
		*address_to_reloc = *address_to_reloc + difference_between_load_addresses;
	}

	return TRUE;
}
