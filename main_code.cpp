/**
    assembale all the headers into one file that load file into memory and run it
    @file main_code.cpp
    @author Shoam Kazo Cohen
*/

#include "read_headers.h"
#include "handle_sections.h"
#include "handle_memory.h"
#include "handle_reloc.h"
#define  PATH_TO_FILE "C:\\Projects\\reversingEX\\reex2\\Debug\\reex2.exe"


int main()
{
    DWORD address_of_section = 0;
    BOOL result = FALSE;
    FILE* file = fopen(PATH_TO_FILE, "rb");
    SectionsInfo* section_info = NULL;
    FileInfo* file_info = NULL;
    file_info = (FileInfo*)malloc(sizeof(file_info));

    if (NULL == file_info || !read_to_file_info_struct(file, file_info)){
        printf("something didn't go well");
        goto clean_up;
    }
    section_info = (SectionsInfo*)malloc(sizeof(SectionsInfo));

    if (!get_sections_table_info(file_info, section_info)) {
        goto clean_up;
    }

    result = manage_memory(file_info, file, address_of_section);

    manage_reloc(file_info, file);

    printf("//\n");

clean_up:
    destroy_file_info(file_info);
    printf("end of program\n");
    fclose(file);
    printf("end of program\n");
}






