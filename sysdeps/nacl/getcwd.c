#include <unistd.h>
#include <errno.h>
#include <irt_syscalls.h>

char* __getcwd(char* buf, size_t size) {
    if(buf == NULL){ //buf is NULL.
        __set_errno (EINVAL);
        return NULL;
    }
    int error = __nacl_irt_getcwd(buf, size);
    if(error==0){
        return buf;
    } 
    else { 
        __set_errno (error);
        return NULL;
    }
}

weak_alias (__getcwd, getcwd)
