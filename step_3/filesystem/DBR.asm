[BITS 16]
extern DBRkernelLoader
global mydata
%include "../include/bridge.inc"
begin:
    jmp code
    times 3 - ($ - $$) db 0

    db 'aaaaaaaa' 
BPB:
    BytePerSector dw 512 
    SectorPerCluster db 1 
    ReservedSector dw 1 
    NumberOfFAT db 2 
    RootEntries dw 512
    SmallSector dw 2800 
    MediaDescriptor db 0xF0 
    SectorsPerFAT dw 9
    SectorPerTrack dw 36
    NumberOfHead dw 2
    HiddenSector dd 1
    LargeSector dd 0; unused
ExtBPB:
    times 26 db 0
    ;TODO: add extend info
code:
    ; 0x7E3E
    calll DBRkernelLoader
    hlt    

data:
    mydata dw 10


; 磁道 面 扇区
;  0～79     0~1    1~18