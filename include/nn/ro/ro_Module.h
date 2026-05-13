#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/ro/ro_Types.h"

namespace nn{
namespace ro{
    class Module{
    public:
        uint8_t  hash0[0x20];           // 0x0000
        uint8_t  hash1[0x20];           // 0x0020
        uint8_t  hash2[0x20];           // 0x0040
        uint8_t  hash3[0x20];           // 0x0060
        uint32_t magic;                 // 0x0080
        uint32_t name_offset;           // 0x0084
        uint32_t next_module;           // 0x0088
        uint32_t prev_module;           // 0x008C
        uint32_t file_size;             // 0x0090
        uint32_t bss_size;              // 0x0094
        uint32_t fixed_size;            // 0x0098
        uint32_t unk_9c;                // 0x009C
        uint32_t ctrl_obj_tag;          // 0x00A0
        uint32_t on_load_tag;           // 0x00A4
        uint32_t on_exit_tag;           // 0x00A8
        uint32_t on_unresolved;         // 0x00AC
        uint32_t code_offset;           // 0x00B0
        uint32_t code_size;             // 0x00B4
        uint32_t data_offset;           // 0x00B8
        uint32_t data_size;             // 0x00BC
        uint32_t mod_name_offset;       // 0x00C0
        uint32_t mod_name_size;         // 0x00C4
        uint32_t seg_table_off;         // 0x00C8
        uint32_t seg_table_cnt;         // 0x00CC
        uint32_t exp_named_off;         // 0x00D0
        uint32_t exp_named_cnt;         // 0x00D4
        uint32_t exp_idx_off;           // 0x00D8
        uint32_t exp_idx_cnt;           // 0x00DC
        uint32_t exp_str_off;           // 0x00E0
        uint32_t exp_str_size;          // 0x00E4
        uint32_t exp_trie_off;          // 0x00E8
        uint32_t exp_trie_cnt;          // 0x00EC
        uint32_t imp_mod_off;           // 0x00F0
        uint32_t imp_mod_cnt;           // 0x00F4
        uint32_t ext_patch_off;         // 0x00F8
        uint32_t ext_patch_cnt;         // 0x00FC
        uint32_t imp_named_off;         // 0x0100
        uint32_t imp_named_cnt;         // 0x0104
        uint32_t imp_idx_off;           // 0x0108
        uint32_t imp_idx_cnt;           // 0x010C
        uint32_t imp_anon_off;          // 0x0110
        uint32_t imp_anon_cnt;          // 0x0114
        uint32_t imp_str_off;           // 0x0118
        uint32_t imp_str_size;          // 0x011C
        uint32_t static_anon_off;       // 0x0120
        uint32_t static_anon_cnt;       // 0x0124
        uint32_t int_patch_off;         // 0x0128
        uint32_t int_patch_cnt;         // 0x012C
        uint32_t static_patch_off;      // 0x0130
        uint32_t static_patch_cnt;      // 0x0134
        class EnumerateCallback{
        public:

            virtual bool operator()(Module* p) = 0;
        };

        ~Module();
        Result Unload();
        Result Link();
        Result Unlink();
        bool IsAllSymbolResolved() const;
        const char* GetName() const;
        void DoInitialize();
        void DoFinalize();
        void GetRegionInfo(nn::ro::RegionInfo* pRegionInfo);
        static void Enumerate(nn::ro::Module::EnumerateCallback* p);
        static Module* Find(const char* pName);
        uptr GetAddress(const char* name) const;
        uptr GetAddress(s32 index) const;
    };
    
}
}