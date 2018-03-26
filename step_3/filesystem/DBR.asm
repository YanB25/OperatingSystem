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
    SmallSector dw 3660 
    MediaDescriptor db 0xF0 
    SectorsPerFAT dw 9
    SectorPerTrark dw 0;TODO: fixme
    NumberOfHead dw 0;TODO:fixme
    HiddenSector dd 1;
    LargeSector dd 0; unused
ExtBPB:
    times 26 db 0
    ;TODO: add extend info
code:
    