#include <nn/assert.h>
#include <nn/font/font_ResFont.h>

/*namespace nn {
namespace font {

ResFont::ResFont(){ }

ResFont::~ResFont(){
    if (!IsManaging(NULL)){
    	RemoveResource();
	}
}

u32 ResFont::GetDrawBufferSize(const void* bfnt){
    const FontTextureGlyph* pGlyph = NULL;
    const detail::BinaryFileHeader* fileHeader =
        reinterpret_cast<const ut::BinaryFileHeader*>(bfnt);

    if (fileHeader->signature == BINFILE_SIG_FONT_RESOLEVED){ }
    else{
        if (!IsValidBinaryFile(fileHeader, BINFILE_SIG_FONT, FONT_FILE_VERSION, 2)){
            return 0;
        }
    }
    
    const ut::BinaryBlockHeader* blockHeader = reinterpret_cast<const ut::BinaryBlockHeader*>(reinterpret_cast<const u8*>(fileHeader) + fileHeader->headerSize);

    int nBlocks = 0;
    while (nBlocks < fileHeader->dataBlocks){
        NN_POINTER_ASSERT( blockHeader );
        if (blockHeader->kind == BINBLOCK_SIG_TGLP){
            pGlyph = reinterpret_cast<const FontTextureGlyph*>(
                reinterpret_cast<const u8*>(blockHeader) + sizeof(*blockHeader)
            );
            break;
        }

        blockHeader = reinterpret_cast<const ut::BinaryBlockHeader*>(reinterpret_cast<const u8*>(blockHeader) + blockHeader->size);
        nBlocks++;
    }

    if (pGlyph == NULL){
        return 0;
    }

    return sizeof(internal::TextureObject) * pGlyph->sheetNum;
}

void* ResFont::SetDrawBuffer(void* buffer){
    void *const prevBuffer = GetTextureObjectsBufferPtr();
    if (prevBuffer == buffer){
        return buffer;
    }

    if (NULL != prevBuffer){
        DeleteTextureNames();
    }

    SetTextureObjectsBufferPtr(buffer);

    if (NULL != buffer){
        GenTextureNames();
    }

    return prevBuffer;
}

}
}*/