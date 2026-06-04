#include "./sysman.h"
#include "gles2/gl2.h"

void glActiveTexture (GLenum texture){
    if((texture < 0x84c0) || (0x84c2 < texture)){
        __err_
    }
}
