#include <stdio.h>
#include <fcntl.h>
#include <myvm.h>



int main(int argc, char** argv)
{
    int fp = open(argv[1], O_RDONLY);
    if(fp < 0) {
        perror("Error opening file");
        return 1;
    }

    VmFile vmfile = vmfile_open(fp);
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
