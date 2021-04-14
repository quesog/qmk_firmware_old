#include "quantum.h"

#if defined(BLINKER_ISR)
OSAL_IRQ_HANDLER(INT_TMR) {
    OSAL_IRQ_PROLOGUE();

    RISCV_MTIMECMP = (72000 * 3) - 1;
    RISCV_MTIME    = 0;
    palToggleLine(LED1);

    OSAL_IRQ_EPILOGUE();
}
#endif

#if defined(__riscv)
uintptr_t handle_nmi(void) {
    //  write(1, "nmi\n", 5);
    //_exit(1);
    return 0;
}

uint64_t SEGGER_SYSVIEW_X_GetTimestamp() {
    return __get_rv_cycle();
}

uint32_t SEGGER_SYSVIEW_X_GetInterruptId() {
    uint32_t cause = __RV_CSR_READ(mcause);
    // EXCCODE bits hold the current interrupt id
    return cause & 0xFFF;
}

uintptr_t handle_trap(uintptr_t mcause, uintptr_t sp, uintptr_t mdcause, uintptr_t msubm) {
    if (mcause == 0xFFF) {
        handle_nmi();
    }

  /*  uint32_t m_epc = read_csr(mepc);
    uint32_t m_bad = read_csr(mbadaddr);

    uint32_t exccode = mcause & (0xFFF);
    uint32_t mpp     = (mcause & (0b11 << 28)) >> 28;
    uint32_t mpie    = (mcause & (1 << 27)) >> 27;
    uint32_t mpil    = (mcause & (0xFF << 16)) >> 16;
*/
#if defined(SEGGER_RTT)
    //SEGGER_SYSVIEW_PrintfHost("TRAP! mepc: %x, exccode: %d, mpp: %d, mpie: %d, mpil: %d\n", m_epc, exccode, mpp, mpie, mpil);
#endif

    while (1) {
    };

    return 0;
}

#endif