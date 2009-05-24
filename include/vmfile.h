#ifndef _VM_FILE_H
#define _VM_FILE_H

typedef struct _VmFile* VmFile;

VmFile vmfile_open(int);
VmInst vmfile_inst_fetch(VmFile, unsigned int);
unsigned char* vmfile_header_get(VmFile);
unsigned int vmfile_version_major_get(VmFile);
unsigned int vmfile_version_minor_get(VmFile);
unsigned int vmfile_size_get(VmFile);
unsigned int vmfile_entry_get(VmFile);
void vmfile_inst_print(VmFile);
void vmfile_close(VmFile);



#endif
