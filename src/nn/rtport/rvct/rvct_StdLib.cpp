#include <nn/types.h>
#include <nn/assert.h>
#include <nn/os/os_ThreadLocal.h>
#include <nn/dbg/dbg_Break.h>

#include <rt_sys.h>
#include <rt_misc.h>
#include <time.h>
#include <stdio.h>
#include <typeinfo>
#include <cstring>

#define NN_UNUSED_VAR(x) ((void)(x))

typedef int FILEHANDLE;

extern "C"{
    FILEHANDLE _sys_open(const char * name, int openmode) { NN_UNUSED_VAR(name); NN_UNUSED_VAR(openmode); return -1; }
    int _sys_close(FILEHANDLE fh) { NN_UNUSED_VAR(fh); return -1; }
    int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode) { NN_UNUSED_VAR(fh); NN_UNUSED_VAR(buf); NN_UNUSED_VAR(len); NN_UNUSED_VAR(mode); return -1; }
    int _sys_read(FILEHANDLE fh, unsigned char * buf, unsigned len, int mode) { NN_UNUSED_VAR(fh); NN_UNUSED_VAR(buf); NN_UNUSED_VAR(len); NN_UNUSED_VAR(mode); return len; }
    void _ttywrch(int ch) { NN_UNUSED_VAR(ch); }
    int _sys_istty(FILEHANDLE fh) { NN_UNUSED_VAR(fh); return -1; }
    int _sys_seek(FILEHANDLE fh, long pos) { NN_UNUSED_VAR(fh); NN_UNUSED_VAR(pos); return -1; }
    int _sys_ensure(FILEHANDLE fh) { NN_UNUSED_VAR(fh); return -1; }
    long _sys_flen(FILEHANDLE fh) { NN_UNUSED_VAR(fh); return -1; }
    int _sys_tmpnam(char *name, int fileno, unsigned maxlength) { NN_UNUSED_VAR(name); NN_UNUSED_VAR(fileno); NN_UNUSED_VAR(maxlength); return -1; }
    void _sys_exit(int return_code) { NN_UNUSED_VAR(return_code); }
    char* _sys_command_string (char* cmd, int len) { NN_UNUSED_VAR(cmd); NN_UNUSED_VAR(len); return NULL; }
    void abort() { nndbgPanic(); }

    void __aeabi_atexit() {}
    void __cxa_finalize() {}
    void __rt_SIGTMEM() {}
    void __rt_SIGABRT() {}
    void __rt_div0() {}


}

namespace std{
    bool type_info::operator==(const type_info& rhs) const{
        return std::strcmp(this->name(), rhs.name()) == 0;
    }
    bool type_info::operator!=(const type_info& rhs) const{
        return std::strcmp(this->name(), rhs.name()) != 0;
    }
    bool type_info::before(const type_info& rhs) const{
        return std::strcmp(this->name(), rhs.name()) < 0;
    }
}