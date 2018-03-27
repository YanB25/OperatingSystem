[BITS 16]
extern DBRkernelLoader
global BPB
%include "../include/bridge.inc"
begin:
    jmp code
    times 3 - ($ - $$) db 0

    db 'aaaaaaaa' 
BPB:
    ; 0x7E0B
    BytePerSector dw 512 ; bpb
    SectorPerCluster db 1 ; bpb + 2
    ReservedSector dw 2 ; bpb + 3
    NumberOfFAT db 2 ; bpb + 5
    RootEntries dw 512 ; bpb + 6
    SmallSector dw 2800 ; bpb + 8
    MediaDescriptor db 0xF0 ; bpb + 10
    SectorsPerFAT dw 4 ; bpb + 11
    SectorPerTrack dw 36; bpb + 13
    NumberOfHead dw 2; bpb + 15
    HiddenSector dd 1 ; bpb + 17
    LargeSector dd 0; unused bpb + 21
ExtBPB:
    times 26 db 0
    ;TODO: add extend info
code:
    ; 0x7E3E
    calll DBRkernelLoader
    hlt    

data:
    mydata dw 10

