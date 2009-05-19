#include <stdio.h>
#include <vmfile.h>



int main()
{
    VmFile vmfile = vmfile_open(0);
    if(vmfile == NULL) {
        printf("Error: %d\n", vmerrno);
        return vmerrno;
    }

    printf("Header: %s\n", vmfile_header_get(vmfile));
    printf("Version : %d.%d\n", vmfile_version_major_get(vmfile),\
            vmfile_version_minor_get(vmfile));
    printf("Size: %d\n", vmfile_size_get(vmfile));
    printf("Entry: %d\n", vmfile_entry_get(vmfile));

    vmfile_inst_print(vmfile);
    vmfile_close(vmfile);
    
    return 0;
}
