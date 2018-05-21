void trap_init() {
    int i;
    set_trap_gate(0, &divide_error);
    // TODO: lots of functions

    for (int i =  17; i < 48; ++i) {
        set_trap_gate(i, &reserverd);
    }
}