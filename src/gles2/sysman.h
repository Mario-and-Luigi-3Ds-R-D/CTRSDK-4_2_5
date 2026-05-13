#include "GLES2/gl2.h"

typedef struct _DB_LIST_T {
    GLuint      id;         // 0x0
    void*       address;    // 0x4
    GLenum      format;     // 0x8
    GLsizei     width;      // 0xc
    GLsizei     height;     // 0x10
    GLenum      area;       // 0x14
    _DB_LIST_T* next;       // 0x18
} DB_LIST_T;

typedef struct _CL_CMDREQ_T {
    unsigned char       id;                 // 0x0
    GLboolean   callback_enabled;   // 0x1
    GLboolean   stop_enabled;       // 0x2
    char        padding1;           // 0x3
    cl_cmdreq_param_t param;        // 0x4
} CL_CMDREQ_T;

typedef struct _CL_LIST_T {
    GLuint      id;                     // 0x0
    unsigned int*       command_buffer;         // 0x4
    GLsizei     max_bufsize;            // 0x8
    GLsizei     used_bufsize;           // 0xc
    GLsizei     run_bufsize;            // 0x10
    GLsizei     last_split_offset;      // 0x14
    CL_CMDREQ_T* command_request;       // 0x18
    GLsizei     max_reqcount;           // 0x1c
    GLsizei     used_reqcount;          // 0x20
    GLsizei     issued_reqcount;        // 0x24
    GLsizei     run_reqcount;           // 0x28
    GLenum      run_mode;               // 0x2c
    GLsizei     subr_bufsize;           // 0x30
    unsigned int*       subr_addr;              // 0x34
    void        (*callbackfunc)(GLint); // 0x38
    GLboolean   last_callback_enabled;  // 0x3c
    GLboolean   gas_accumulation;       // 0x3d
    char        padding2[2];            // 0x3e
    _CL_LIST_T* next;                   // 0x40
} CL_LIST_T;

typedef struct _SYS_MANAGER_T {
    GLsizei     display_width[2];       // 0x0
    GLsizei     display_height[2];      // 0x8
    GLboolean   initialized;            // 0x10
    GLboolean   is_running;             // 0x11
    GLboolean   start_run;              // 0x12
    GLboolean   saving_cmdlist;         // 0x13
    int         num_speculative;        // 0x14
    GLboolean   stop_speculative;       // 0x18
    char        padding3[3];            // 0x19
    CL_LIST_T*  cl_list_table[32];      // 0x1c
    CL_LIST_T*  bound_cmdlist;          // 0x9c
    CL_LIST_T*  run_cmdlist;            // 0xa0
    DB_LIST_T*  db_list_table[32];      // 0xa4
    int         active_display;         // 0x124
    DB_LIST_T*  current_buffer[3];      // 0x128
    GLint       display_xoffset[3];     // 0x134
    GLint       display_yoffset[3];     // 0x140
    int         next_bank[2];           // 0x14c
    GLint       v_counter[2];           // 0x154
    void        (*v0callback)(GLenum);  // 0x15c
    void        (*v1callback)(GLenum);  // 0x160
    GLenum      extension_mode;         // 0x164
    unsigned int        save_cmdbuf_offset;     // 0x168
    GLuint      save_cmdreq_id;         // 0x16c
    void        (*tocallback)(void);    // 0x170
    char        padding4[4];            // 0x174
    signed long long         timeout;                // 0x178
} SYS_MANAGER_T;