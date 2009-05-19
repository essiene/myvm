#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <myvm.h>

enum VmErrno vmerrno = VM_EOK;

struct _VmFile {
    unsigned char header[4];

    union {
        struct {
            unsigned int minor:4;
            unsigned int major:4;
        } detail;

        unsigned char val;
    } version;

    unsigned int size;
    unsigned int entry;

    unsigned char unused[4];

    VmInst *code;
};



VmFile vmfile_open(int fd)
{
    VmFile vmfile = calloc(sizeof(*vmfile), 1);
    if(vmfile == NULL) {
        vmerrno = VM_ENOMEM;
        return NULL;
    }

    ssize_t bytes = read(fd, vmfile->header, 3);
    if(bytes != 3) {
        vmerrno = VM_ENOHEADER;
        return NULL;
    }
    vmfile->header[3] = 0;

    bytes = read(fd, &vmfile->version, 1);
    if(bytes != 1) {
        vmerrno = VM_ENOVERSION;
        return NULL;
    }

    bytes = read(fd, &vmfile->size, 4);
    if(bytes != 4) {
        vmerrno = VM_ENOSIZE;
        return NULL;
    }

    bytes = read(fd, &vmfile->entry, 4);
    if(bytes != 4) {
        vmerrno = VM_ENOENTRY;
        return NULL;
    }

    bytes = read(fd, &vmfile->unused, 4);
    if(bytes != 4) {
        vmerrno = VM_ENOUNUSED;
        return NULL;
    }

    vmfile->code = calloc(sizeof(*(vmfile->code)), vmfile->size);

    unsigned int entry = vmfile->entry;

    for(int i = 0; i < vmfile->size; i++) {
        vmfile->code[i] = vminst_new(fd, vmfile->entry);
        if(vmfile->code[i] == NULL) {
            return NULL;
        }

        entry = entry + sizeof(*(vmfile->code));
    }

    return vmfile;
}

unsigned char* vmfile_header_get(VmFile vmfile)
{
    return vmfile->header;
}

unsigned int vmfile_version_major_get(VmFile vmfile)
{
    return vmfile->version.detail.major;
}

unsigned int vmfile_version_minor_get(VmFile vmfile)
{
    return vmfile->version.detail.minor;
}

unsigned int vmfile_size_get(VmFile vmfile)
{
    return vmfile->size;
}

unsigned int vmfile_entry_get(VmFile vmfile)
{
    return vmfile->entry;
}

void vmfile_inst_print(VmFile vmfile)
{
    for(int i = 0; i < vmfile->size; i++) {
        vminst_print(vmfile->code[i]);
    }
}

void vmfile_close(VmFile vmfile)
{
    for(int i = 0; i< vmfile->size; i++) {
        vminst_del(vmfile->code[i]);
    }
    free(vmfile);
}
