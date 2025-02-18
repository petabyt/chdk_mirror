/*
 * capt_seq.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define USE_STUBS_NRFLAG 1          // see stubs_entry.S
#define NR_AUTO (0)                 // have to explictly reset value back to 0 to enable auto
#define PAUSE_FOR_FILE_COUNTER 150  // Enable delay in capt_seq_hook_raw_here to ensure file counter is updated

#include "../../../generic/capt_seq.c"

/*************************************************************/
//** capt_seq_task @ 0xFF07B330 - 0xFF07B630, length=193
void __attribute__((naked,noinline)) capt_seq_task() {
asm volatile (
"    STMFD   SP!, {R3-R7,LR} \n"
"    LDR     R4, =0x409E0 \n"
"    LDR     R7, =0x4068 \n"
"    MOV     R6, #0 \n"

"loc_FF07B340:\n"
"    LDR     R0, [R7, #4] \n"
"    MOV     R2, #0 \n"
"    MOV     R1, SP \n"
"    BL      sub_FF029EA8 /*_ReceiveMessageQueue*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF07B36C \n"
"    LDR     R1, =0x491 \n"
"    LDR     R0, =0xFF07AC7C /*'SsShootTask.c'*/ \n"
"    BL      _DebugAssert \n"
"    BL      _ExitTask \n"
"    LDMFD   SP!, {R3-R7,PC} \n"

"loc_FF07B36C:\n"
"    LDR     R0, [SP] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x28 \n"
"    ADDCC   PC, PC, R1, LSL#2 \n"
"    B       loc_FF07B5F8 \n"
"    B       loc_FF07B420 \n"
"    B       loc_FF07B438 \n"
"    B       loc_FF07B444 \n"
"    B       loc_FF07B458 \n"
"    B       loc_FF07B450 \n"
"    B       loc_FF07B464 \n"
"    B       loc_FF07B46C \n"
"    B       loc_FF07B474 \n"
"    B       loc_FF07B490 \n"
"    B       loc_FF07B4D0 \n"
"    B       loc_FF07B49C \n"
"    B       loc_FF07B4A8 \n"
"    B       loc_FF07B4B0 \n"
"    B       loc_FF07B4B8 \n"
"    B       loc_FF07B4C0 \n"
"    B       loc_FF07B4C8 \n"
"    B       loc_FF07B4D8 \n"
"    B       loc_FF07B4E0 \n"
"    B       loc_FF07B4E8 \n"
"    B       loc_FF07B4F0 \n"
"    B       loc_FF07B4F8 \n"
"    B       loc_FF07B500 \n"
"    B       loc_FF07B508 \n"
"    B       loc_FF07B510 \n"
"    B       loc_FF07B518 \n"
"    B       loc_FF07B520 \n"
"    B       loc_FF07B52C \n"
"    B       loc_FF07B534 \n"
"    B       loc_FF07B540 \n"
"    B       loc_FF07B548 \n"
"    B       loc_FF07B578 \n"
"    B       loc_FF07B580 \n"
"    B       loc_FF07B588 \n"
"    B       loc_FF07B590 \n"
"    B       loc_FF07B598 \n"
"    B       loc_FF07B5A0 \n"
"    B       loc_FF07B5AC \n"
"    B       loc_FF07B5B4 \n"
"    B       loc_FF07B5C0 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B420:\n"
"    BL      shooting_expo_iso_override\n"      // added
"    BL      sub_FF07BC40 \n"
"    BL      shooting_expo_param_override\n"    // added
"    BL      sub_FF078618 \n"
"    MOV     R0, #0\n"                          // added
"    STR     R0, [R4,#0x2C]\n"                  // added, fixes overrides  behavior at short shutter press (from S95)
//"  LDR     R0, [R4, #0x2C] \n"  // above patch makes these three lines redundant
//"  CMP     R0, #0 \n"
//"  BLNE    _sub_FF1D1654 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B438:\n"
"    BL      wait_until_remote_button_is_released\n"    // added
"    BL      capt_seq_hook_set_nr\n"                    // added
"    LDR     R0, [R0, #0x10] \n"
"    BL      sub_FF07B74C_my \n"  // --> Patched. Old value = 0xFF07B74C.
"    B       loc_FF07B604 \n"

"loc_FF07B444:\n"
"    MOV     R0, #1 \n"
"    BL      sub_FF07BFBC \n"
"    B       loc_FF07B604 \n"

"loc_FF07B450:\n"
"    BL      sub_FF07B8AC \n"
"    B       loc_FF07B45C \n"

"loc_FF07B458:\n"
"    BL      sub_FF07BC20 \n"

"loc_FF07B45C:\n"
"    STR     R6, [R4, #0x2C] \n"
"    B       loc_FF07B604 \n"

"loc_FF07B464:\n"
"    BL      sub_FF07BC28 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B46C:\n"
"    BL      sub_FF07BE64 \n"
"    B       loc_FF07B494 \n"

"loc_FF07B474:\n"
"    LDR     R5, [R0, #0x10] \n"
"    MOV     R0, R5 \n"
"    BL      sub_FF1D16E4 \n"
"    MOV     R2, R5 \n"
"    MOV     R1, #9 \n"
"    BL      sub_FF0790B4 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B490:\n"
"    BL      sub_FF07BF20 \n"

"loc_FF07B494:\n"
"    BL      sub_FF078618 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B49C:\n"
"    LDR     R0, [R4, #0x5C] \n"
"    BL      sub_FF07C8DC \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4A8:\n"
"    BL      sub_FF07CB9C \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4B0:\n"
"    BL      sub_FF07CC00 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4B8:\n"
"    BL      sub_FF07CDD0 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4C0:\n"
"    BL      sub_FF07D220 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4C8:\n"
"    BL      sub_FF07D2D0 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4D0:\n"
"    BL      sub_FF07BC20 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4D8:\n"
"    BL      sub_FF1CF1D4 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4E0:\n"
"    BL      sub_FF1CF4C0 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4E8:\n"
"    BL      sub_FF1CF574 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4F0:\n"
"    BL      sub_FF1CF65C \n"
"    B       loc_FF07B604 \n"

"loc_FF07B4F8:\n"
"    BL      sub_FF1CF758 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B500:\n"
"    MOV     R0, #0 \n"
"    B       loc_FF07B524 \n"

"loc_FF07B508:\n"
"    BL      sub_FF1CFD74 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B510:\n"
"    BL      sub_FF1CFE08 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B518:\n"
"    BL      sub_FF1CFEC4 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B520:\n"
"    MOV     R0, #1 \n"

"loc_FF07B524:\n"
"    BL      sub_FF1CFC04 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B52C:\n"
"    BL      sub_FF07C22C \n"
"    B       loc_FF07B604 \n"

"loc_FF07B534:\n"
"    BL      sub_FF07C2C0 \n"
"    BL      sub_FF1D29F0 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B540:\n"
"    BL      sub_FF1CFA44 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B548:\n"
"    MOV     R2, #2 \n"
"    ADD     R1, R4, #0x68 \n"
"    MOV     R0, #0x6F \n"
"    BL      _GetPropertyCase \n"
"    TST     R0, #1 \n"
"    LDRNE   R1, =0x592 \n"
"    LDRNE   R0, =0xFF07AC7C /*'SsShootTask.c'*/ \n"
"    BLNE    _DebugAssert \n"
"    LDRH    R0, [R4, #0x68] \n"
"    CMP     R0, #1 \n"
"    BLEQ    sub_FF1CFA38 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B578:\n"
"    BL      sub_FF1CFB64 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B580:\n"
"    BL      sub_FF1D2ABC \n"
"    B       loc_FF07B604 \n"

"loc_FF07B588:\n"
"    BL      sub_FF0272CC \n"
"    B       loc_FF07B604 \n"

"loc_FF07B590:\n"
"    BL      sub_FF07FC60 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B598:\n"
"    BL      sub_FF07FCE8 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B5A0:\n"
"    LDR     R0, [R0, #0xC] \n"
"    BL      sub_FF1CFFEC \n"
"    B       loc_FF07B604 \n"

"loc_FF07B5AC:\n"
"    BL      sub_FF1D005C \n"
"    B       loc_FF07B604 \n"

"loc_FF07B5B4:\n"
"    BL      sub_FF07FD50 \n"
"    BL      sub_FF07FD08 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B5C0:\n"
"    MOV     R0, #1 \n"
"    BL      sub_FF1D1DF4 \n"
"    MOV     R0, #1 \n"
"    BL      sub_FF1D1F28 \n"
"    LDRH    R0, [R4, #0xA4] \n"
"    CMP     R0, #4 \n"
"    LDRNEH  R0, [R4] \n"
"    SUBNE   R1, R0, #0x4200 \n"
"    SUBNES  R1, R1, #0x2B \n"
"    BNE     loc_FF07B604 \n"
"    BL      sub_FF07FCE8 \n"
"    BL      sub_FF080464 \n"
"    BL      sub_FF080178 \n"
"    B       loc_FF07B604 \n"

"loc_FF07B5F8:\n"
"    LDR     R1, =0x5F2 \n"
"    LDR     R0, =0xFF07AC7C /*'SsShootTask.c'*/ \n"
"    BL      _DebugAssert \n"

"loc_FF07B604:\n"
"    LDR     R0, [SP] \n"
"    LDR     R1, [R0, #4] \n"
"    LDR     R0, [R7] \n"
"    BL      sub_FF087530 /*_SetEventFlag*/ \n"
"    LDR     R5, [SP] \n"
"    LDR     R0, [R5, #8] \n"
"    CMP     R0, #0 \n"
"    LDREQ   R1, =0x117 \n"
"    LDREQ   R0, =0xFF07AC7C /*'SsShootTask.c'*/ \n"
"    BLEQ    _DebugAssert \n"
"    STR     R6, [R5, #8] \n"
"    B       loc_FF07B340 \n"
);
}

/*************************************************************/
//** sub_FF07B74C_my @ 0xFF07B74C - 0xFF07B7F4, length=43
void __attribute__((naked,noinline)) sub_FF07B74C_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R5, =0x409E0 \n"
"    MOV     R6, R0 \n"
"    LDR     R0, [R5, #0x2C] \n"
"    LDR     R4, =0x222F \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF07B7A8 \n"
"    LDRH    R0, [R5] \n"
"    CMP     R0, R4 \n"
"    SUBNE   R1, R0, #0x4200 \n"
"    SUBNES  R1, R1, #0x2E \n"
"    BLEQ    sub_FF07DDC4 \n"
"    BL      sub_FF07DA60 \n"
"    MOV     R1, R6 \n"
"    BL      sub_FF07DAB8 \n"
"    LDR     R0, =0x10F \n"
"    MOV     R2, #4 \n"
"    ADD     R1, R6, #0x58 \n"
"    BL      _SetPropertyCase \n"
"    MOV     R2, #4 \n"
"    ADD     R1, R6, #0x5C \n"
"    MOV     R0, #0x2C \n"
"    BL      _SetPropertyCase \n"

"loc_FF07B7A8:\n"
"    LDRH    R0, [R5] \n"
"    CMP     R0, R4 \n"
"    MOV     R0, R6 \n"
"    BNE     loc_FF07B7C0 \n"
"    BL      sub_FF1D2418 \n"
"    B       loc_FF07B7C4 \n"

"loc_FF07B7C0:\n"
"    BL      sub_FF1D140C \n"

"loc_FF07B7C4:\n"
"    BL      capt_seq_hook_raw_here\n"      // +++  (8/4/2013 - moved here to fix RAW Develop)
"    MOV     R4, R0 \n"
"    MOV     R2, R6 \n"
"    MOV     R1, #1 \n"
"    BL      sub_FF0790B4 \n"
"    TST     R4, #1 \n"
"    MOVEQ   R0, R6 \n"
"    BLEQ    sub_FF1D05D0 \n"
"    LDR     R0, [R5, #0xC8] \n"
"    CMP     R0, #2 \n"
"    LDMNEFD SP!, {R4-R6,PC} \n"
"    MOV     R0, R6 \n"
"    LDMFD   SP!, {R4-R6,LR} \n"
"    B       sub_FF079288 \n"
);
}

/*************************************************************/
//** exp_drv_task @ 0xFF0CD9F0 - 0xFF0CE064, length=414
void __attribute__((naked,noinline)) exp_drv_task() {
asm volatile (
"    STMFD   SP!, {R4-R9,LR} \n"
"    SUB     SP, SP, #0x24 \n"
"    LDR     R6, =0x5BE4 \n"
"    LDR     R7, =0xBB8 \n"
"    LDR     R4, =0x5EDD0 \n"
"    MOV     R0, #0 \n"
"    ADD     R5, SP, #0x14 \n"
"    STR     R0, [SP, #0x10] \n"

"loc_FF0CDA10:\n"
"    LDR     R0, [R6, #0x20] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #0x20 \n"
"    BL      sub_FF029EA8 /*_ReceiveMessageQueue*/ \n"
"    LDR     R0, [SP, #0x10] \n"
"    CMP     R0, #1 \n"
"    BNE     loc_FF0CDA60 \n"
"    LDR     R0, [SP, #0x20] \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #0x14 \n"
"    CMPNE   R0, #0x15 \n"
"    CMPNE   R0, #0x16 \n"
"    CMPNE   R0, #0x17 \n"
"    CMPNE   R0, #0x18 \n"
"    BEQ     loc_FF0CDBC0 \n"
"    CMP     R0, #0x2B \n"
"    BEQ     loc_FF0CDB48 \n"
"    ADD     R1, SP, #0x10 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF0CD9A0 \n"

"loc_FF0CDA60:\n"
"    LDR     R0, [SP, #0x20] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x31 \n"
"    BNE     loc_FF0CDA8C \n"
"    BL      sub_FF0CEEA8 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R1, #1 \n"
"    BL      sub_FF087530 /*_SetEventFlag*/ \n"
"    BL      _ExitTask \n"
"    ADD     SP, SP, #0x24 \n"
"    LDMFD   SP!, {R4-R9,PC} \n"

"loc_FF0CDA8C:\n"
"    CMP     R1, #0x30 \n"
"    BNE     loc_FF0CDAA8 \n"
"    LDR     R2, [R0, #0x8C]! \n"
"    LDR     R1, [R0, #4] \n"
"    MOV     R0, R1 \n"
"    BLX     R2 \n"
"    B       loc_FF0CE05C \n"

"loc_FF0CDAA8:\n"
"    CMP     R1, #0x29 \n"
"    BNE     loc_FF0CDAF8 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_FF087564 /*_ClearEventFlag*/ \n"
"    LDR     R0, =0xFF0C9044 \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_FF1BEEB4 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R2, R7 \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_FF087470 /*_WaitForAllEventFlag*/ \n"
"    TST     R0, #1 \n"
"    LDRNE   R1, =0x1572 \n"
"    BNE     loc_FF0CDBB4 \n"

"loc_FF0CDAE4:\n"
"    LDR     R1, [SP, #0x20] \n"
"    LDR     R0, [R1, #0x90] \n"
"    LDR     R1, [R1, #0x8C] \n"
"    BLX     R1 \n"
"    B       loc_FF0CE05C \n"

"loc_FF0CDAF8:\n"
"    CMP     R1, #0x2A \n"
"    BNE     loc_FF0CDB40 \n"
"    ADD     R1, SP, #0x10 \n"
"    BL      sub_FF0CD9A0 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_FF087564 /*_ClearEventFlag*/ \n"
"    LDR     R0, =0xFF0C9054 \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_FF1BFC84 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R2, R7 \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_FF087470 /*_WaitForAllEventFlag*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF0CDAE4 \n"
"    LDR     R1, =0x157C \n"
"    B       loc_FF0CDBB4 \n"

"loc_FF0CDB40:\n"
"    CMP     R1, #0x2B \n"
"    BNE     loc_FF0CDB58 \n"

"loc_FF0CDB48:\n"
"    LDR     R0, [SP, #0x20] \n"
"    ADD     R1, SP, #0x10 \n"
"    BL      sub_FF0CD9A0 \n"
"    B       loc_FF0CDAE4 \n"

"loc_FF0CDB58:\n"
"    CMP     R1, #0x2E \n"
"    BNE     loc_FF0CDB70 \n"
"    BL      sub_FF0B8F5C \n"
"    BL      sub_FF0B9C58 \n"
"    BL      sub_FF0B97AC \n"
"    B       loc_FF0CDAE4 \n"

"loc_FF0CDB70:\n"
"    CMP     R1, #0x2F \n"
"    BNE     loc_FF0CDBC0 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R1, #4 \n"
"    BL      sub_FF087564 /*_ClearEventFlag*/ \n"
"    LDR     R1, =0xFF0C9074 \n"
"    LDR     R0, =0xFFFFF400 \n"
"    MOV     R2, #4 \n"
"    BL      sub_FF0B89AC \n"
"    BL      sub_FF0B8C3C \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R2, R7 \n"
"    MOV     R1, #4 \n"
"    BL      sub_FF08738C /*_WaitForAnyEventFlag*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF0CDAE4 \n"
"    LDR     R1, =0x15A4 \n"

"loc_FF0CDBB4:\n"
"    LDR     R0, =0xFF0C97BC /*'ExpDrv.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FF0CDAE4 \n"

"loc_FF0CDBC0:\n"
"    LDR     R0, [SP, #0x20] \n"
"    MOV     R8, #1 \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x12 \n"
"    CMPNE   R1, #0x13 \n"
"    BNE     loc_FF0CDC28 \n"
"    LDR     R1, [R0, #0x7C] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R1, R0, R1, LSL#2 \n"
"    SUB     R1, R1, #8 \n"
"    LDMIA   R1, {R2,R3,R9} \n"
"    STMIA   R5, {R2,R3,R9} \n"
"    BL      sub_FF0CBDB4 \n"
"    LDR     R0, [SP, #0x20] \n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R3, [R0, #0x8C] \n"
"    LDR     R2, [R0, #0x90] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"
"    LDR     R0, [SP, #0x20] \n"
"    BL      sub_FF0CF2C0 \n"
"    LDR     R0, [SP, #0x20] \n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R2, [R0, #0x98] \n"
"    LDR     R3, [R0, #0x94] \n"
"    B       loc_FF0CDF48 \n"

"loc_FF0CDC28:\n"
"    CMP     R1, #0x14 \n"
"    CMPNE   R1, #0x15 \n"
"    CMPNE   R1, #0x16 \n"
"    CMPNE   R1, #0x17 \n"
"    CMPNE   R1, #0x18 \n"
"    BNE     loc_FF0CDCE4 \n"
"    ADD     R3, SP, #0x10 \n"
"    ADD     R2, SP, #4 \n"
"    ADD     R1, SP, #0x14 \n"
"    BL      sub_FF0CC020 \n"
"    CMP     R0, #1 \n"
"    MOV     R9, R0 \n"
"    CMPNE   R9, #5 \n"
"    BNE     loc_FF0CDC80 \n"
"    LDR     R0, [SP, #0x20] \n"
"    MOV     R2, R9 \n"
"    LDR     R1, [R0, #0x7C]! \n"
"    LDR     R12, [R0, #0x10]! \n"
"    LDR     R3, [R0, #4] \n"
"    ADD     R0, SP, #4 \n"
"    BLX     R12 \n"
"    B       loc_FF0CDCB8 \n"

"loc_FF0CDC80:\n"
"    LDR     R0, [SP, #0x20] \n"
"    CMP     R9, #2 \n"
"    LDR     R3, [R0, #0x90] \n"
"    CMPNE   R9, #6 \n"
"    BNE     loc_FF0CDCCC \n"
"    LDR     R12, [R0, #0x8C] \n"
"    MOV     R2, R9 \n"
"    MOV     R1, #1 \n"
"    ADD     R0, SP, #4 \n"
"    BLX     R12 \n"
"    LDR     R0, [SP, #0x20] \n"
"    ADD     R2, SP, #4 \n"
"    ADD     R1, SP, #0x14 \n"
"    BL      sub_FF0CD6EC \n"

"loc_FF0CDCB8:\n"
"    LDR     R0, [SP, #0x20] \n"
"    LDR     R2, [SP, #0x10] \n"
"    MOV     R1, R9 \n"
"    BL      sub_FF0CD940 \n"
"    B       loc_FF0CDF50 \n"

"loc_FF0CDCCC:\n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R12, [R0, #0x8C] \n"
"    MOV     R2, R9 \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R12 \n"
"    B       loc_FF0CDF50 \n"

"loc_FF0CDCE4:\n"
"    CMP     R1, #0x25 \n"
"    CMPNE   R1, #0x26 \n"
"    BNE     loc_FF0CDD30 \n"
"    LDR     R1, [R0, #0x7C] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R1, R0, R1, LSL#2 \n"
"    SUB     R1, R1, #8 \n"
"    LDMIA   R1, {R2,R3,R9} \n"
"    STMIA   R5, {R2,R3,R9} \n"
"    BL      sub_FF0CAD80 \n"
"    LDR     R0, [SP, #0x20] \n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R3, [R0, #0x8C] \n"
"    LDR     R2, [R0, #0x90] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"
"    LDR     R0, [SP, #0x20] \n"
"    BL      sub_FF0CB1DC \n"
"    B       loc_FF0CDF50 \n"

"loc_FF0CDD30:\n"
"    ADD     R1, R0, #4 \n"
"    LDMIA   R1, {R2,R3,R9} \n"
"    STMIA   R5, {R2,R3,R9} \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x29 \n"
"    ADDCC   PC, PC, R1, LSL#2 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDDF0 \n"
"    B       loc_FF0CDDF0 \n"
"    B       loc_FF0CDDF8 \n"
"    B       loc_FF0CDE00 \n"
"    B       loc_FF0CDE00 \n"
"    B       loc_FF0CDE00 \n"
"    B       loc_FF0CDDF0 \n"
"    B       loc_FF0CDDF8 \n"
"    B       loc_FF0CDE00 \n"
"    B       loc_FF0CDE00 \n"
"    B       loc_FF0CDE18 \n"
"    B       loc_FF0CDE18 \n"
"    B       loc_FF0CDF24 \n"
"    B       loc_FF0CDF2C \n"
"    B       loc_FF0CDF2C \n"
"    B       loc_FF0CDF2C \n"
"    B       loc_FF0CDF2C \n"
"    B       loc_FF0CDF34 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDE08 \n"
"    B       loc_FF0CDE10 \n"
"    B       loc_FF0CDE10 \n"
"    B       loc_FF0CDE10 \n"
"    B       loc_FF0CDE24 \n"
"    B       loc_FF0CDE24 \n"
"    B       loc_FF0CDE2C \n"
"    B       loc_FF0CDE64 \n"
"    B       loc_FF0CDE9C \n"
"    B       loc_FF0CDED4 \n"
"    B       loc_FF0CDF0C \n"
"    B       loc_FF0CDF0C \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDF38 \n"
"    B       loc_FF0CDF14 \n"
"    B       loc_FF0CDF1C \n"

"loc_FF0CDDF0:\n"
"    BL      sub_FF0C95F8 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDDF8:\n"
"    BL      sub_FF0C98EC \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDE00:\n"
"    BL      sub_FF0C9B58 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDE08:\n"
"    BL      sub_FF0C9E50 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDE10:\n"
"    BL      sub_FF0CA06C \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDE18:\n"
"    BL      sub_FF0CA444_my \n"  // --> Patched. Old value = 0xFF0CA444.
"    MOV     R8, #0 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDE24:\n"
"    BL      sub_FF0CA58C \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDE2C:\n"
"    LDRH    R1, [R0, #4] \n"
"    STRH    R1, [SP, #0x14] \n"
"    LDRH    R1, [R4, #2] \n"
"    STRH    R1, [SP, #0x16] \n"
"    LDRH    R1, [R4, #4] \n"
"    STRH    R1, [SP, #0x18] \n"
"    LDRH    R1, [R4, #6] \n"
"    STRH    R1, [SP, #0x1A] \n"
"    LDRH    R1, [R0, #0xC] \n"
"    STRH    R1, [SP, #0x1C] \n"
"    LDRH    R1, [R4, #0xA] \n"
"    STRH    R1, [SP, #0x1E] \n"
"    BL      sub_FF0CEF3C \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDE64:\n"
"    LDRH    R1, [R0, #4] \n"
"    STRH    R1, [SP, #0x14] \n"
"    LDRH    R1, [R4, #2] \n"
"    STRH    R1, [SP, #0x16] \n"
"    LDRH    R1, [R4, #4] \n"
"    STRH    R1, [SP, #0x18] \n"
"    LDRH    R1, [R4, #6] \n"
"    STRH    R1, [SP, #0x1A] \n"
"    LDRH    R1, [R4, #8] \n"
"    STRH    R1, [SP, #0x1C] \n"
"    LDRH    R1, [R4, #0xA] \n"
"    STRH    R1, [SP, #0x1E] \n"
"    BL      sub_FF0CF0C0 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDE9C:\n"
"    LDRH    R1, [R4] \n"
"    STRH    R1, [SP, #0x14] \n"
"    LDRH    R1, [R0, #6] \n"
"    STRH    R1, [SP, #0x16] \n"
"    LDRH    R1, [R4, #4] \n"
"    STRH    R1, [SP, #0x18] \n"
"    LDRH    R1, [R4, #6] \n"
"    STRH    R1, [SP, #0x1A] \n"
"    LDRH    R1, [R4, #8] \n"
"    STRH    R1, [SP, #0x1C] \n"
"    LDRH    R1, [R4, #0xA] \n"
"    STRH    R1, [SP, #0x1E] \n"
"    BL      sub_FF0CF174 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDED4:\n"
"    LDRH    R1, [R4] \n"
"    STRH    R1, [SP, #0x14] \n"
"    LDRH    R1, [R4, #2] \n"
"    STRH    R1, [SP, #0x16] \n"
"    LDRH    R1, [R4, #4] \n"
"    STRH    R1, [SP, #0x18] \n"
"    LDRH    R1, [R4, #6] \n"
"    STRH    R1, [SP, #0x1A] \n"
"    LDRH    R1, [R0, #0xC] \n"
"    STRH    R1, [SP, #0x1C] \n"
"    LDRH    R1, [R4, #0xA] \n"
"    STRH    R1, [SP, #0x1E] \n"
"    BL      sub_FF0CF21C \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDF0C:\n"
"    BL      sub_FF0CAB14 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDF14:\n"
"    BL      sub_FF0CB2E0 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDF1C:\n"
"    BL      sub_FF0CB650 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDF24:\n"
"    BL      sub_FF0CB878 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDF2C:\n"
"    BL      sub_FF0CBA38 \n"
"    B       loc_FF0CDF38 \n"

"loc_FF0CDF34:\n"
"    BL      sub_FF0CBBA8 \n"

"loc_FF0CDF38:\n"
"    LDR     R0, [SP, #0x20] \n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R2, [R0, #0x90] \n"
"    LDR     R3, [R0, #0x8C] \n"

"loc_FF0CDF48:\n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"

"loc_FF0CDF50:\n"
"    LDR     R1, [SP, #0x20] \n"
"    LDR     R0, [R1] \n"
"    CMP     R0, #0x10 \n"
"    BEQ     loc_FF0CDF88 \n"
"    BGT     loc_FF0CDF78 \n"
"    CMP     R0, #1 \n"
"    CMPNE   R0, #4 \n"
"    CMPNE   R0, #0xE \n"
"    BNE     loc_FF0CDF98 \n"
"    B       loc_FF0CDF88 \n"

"loc_FF0CDF78:\n"
"    CMP     R0, #0x13 \n"
"    CMPNE   R0, #0x18 \n"
"    CMPNE   R0, #0x1B \n"
"    BNE     loc_FF0CDF98 \n"

"loc_FF0CDF88:\n"
"    LDRH    R0, [R4] \n"
"    STRH    R0, [SP, #0x14] \n"
"    LDRH    R0, [R4, #8] \n"
"    STRH    R0, [SP, #0x1C] \n"

"loc_FF0CDF98:\n"
"    CMP     R8, #1 \n"
"    BNE     loc_FF0CDFE4 \n"
"    LDR     R0, [R1, #0x7C] \n"
"    MOV     R2, #0xC \n"
"    ADD     R0, R0, R0, LSL#1 \n"
"    ADD     R0, R1, R0, LSL#2 \n"
"    SUB     R8, R0, #8 \n"
"    LDR     R0, =0x5EDD0 \n"
"    ADD     R1, SP, #0x14 \n"
"    BL      sub_FF45F020 \n"
"    LDR     R0, =0x5EDDC \n"
"    MOV     R2, #0xC \n"
"    ADD     R1, SP, #0x14 \n"
"    BL      sub_FF45F020 \n"
"    LDR     R0, =0x5EDE8 \n"
"    MOV     R2, #0xC \n"
"    MOV     R1, R8 \n"
"    BL      sub_FF45F020 \n"
"    B       loc_FF0CE05C \n"

"loc_FF0CDFE4:\n"
"    LDR     R0, [R1] \n"
"    MOV     R3, #1 \n"
"    CMP     R0, #0xB \n"
"    BNE     loc_FF0CE028 \n"
"    MOV     R2, #0 \n"
"    STRD    R2, [SP] \n"
"    MOV     R2, R3 \n"
"    MOV     R1, R3 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF0C93CC \n"
"    MOV     R3, #1 \n"
"    MOV     R2, #0 \n"
"    STRD    R2, [SP] \n"
"    MOV     R2, R3 \n"
"    MOV     R1, R3 \n"
"    MOV     R0, #0 \n"
"    B       loc_FF0CE058 \n"

"loc_FF0CE028:\n"
"    MOV     R2, #1 \n"
"    STRD    R2, [SP] \n"
"    MOV     R3, R2 \n"
"    MOV     R1, R2 \n"
"    MOV     R0, R2 \n"
"    BL      sub_FF0C93CC \n"
"    MOV     R3, #1 \n"
"    MOV     R2, R3 \n"
"    MOV     R1, R3 \n"
"    MOV     R0, R3 \n"
"    STR     R3, [SP] \n"
"    STR     R3, [SP, #4] \n"

"loc_FF0CE058:\n"
"    BL      sub_FF0C9544 \n"

"loc_FF0CE05C:\n"
"    LDR     R0, [SP, #0x20] \n"
"    BL      sub_FF0CEEA8 \n"
"    B       loc_FF0CDA10 \n"
);
}

/*************************************************************/
//** sub_FF0CA444_my @ 0xFF0CA444 - 0xFF0CA50C, length=51
void __attribute__((naked,noinline)) sub_FF0CA444_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    LDR     R7, =0x5BE4 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R1, #0x3E \n"
"    BL      sub_FF087564 /*_ClearEventFlag*/ \n"
"    MOV     R2, #0 \n"
"    LDRSH   R0, [R4, #4] \n"
"    MOV     R1, R2 \n"
"    BL      sub_FF0C90D4 \n"
"    MOV     R5, R0 \n"
"    LDRSH   R0, [R4, #6] \n"
"    BL      sub_FF0C9224 \n"
"    LDRSH   R0, [R4, #8] \n"
"    BL      sub_FF0C927C \n"
"    LDRSH   R0, [R4, #0xA] \n"
"    BL      sub_FF0C92D4 \n"
"    LDRSH   R0, [R4, #0xC] \n"
"    MOV     R1, #0 \n"
"    BL      sub_FF0C932C \n"
"    MOV     R6, R0 \n"
"    LDRSH   R0, [R4, #0xE] \n"
"    BL      sub_FF0CEED8 \n"
"    LDR     R0, [R4] \n"
"    LDR     R8, =0x5EDE8 \n"
"    CMP     R0, #0xB \n"
"    MOVEQ   R5, #0 \n"
"    MOVEQ   R6, R5 \n"
"    BEQ     loc_FF0CA4E0 \n"
"    CMP     R5, #1 \n"
"    BNE     loc_FF0CA4E0 \n"
"    LDRSH   R0, [R4, #4] \n"
"    LDR     R1, =0xFF0C9034 \n"
"    MOV     R2, #2 \n"
"    BL      sub_FF1BF1D8 \n"
"    STRH    R0, [R4, #4] \n"
"    MOV     R0, #0 \n"
"    STR     R0, [R7, #0x28] \n"
"    B       loc_FF0CA4E8 \n"

"loc_FF0CA4E0:\n"
"    LDRH    R0, [R8] \n"
"    STRH    R0, [R4, #4] \n"

"loc_FF0CA4E8:\n"
"    CMP     R6, #1 \n"
"    LDRNEH  R0, [R8, #8] \n"
"    BNE     loc_FF0CA504 \n"
"    LDRSH   R0, [R4, #0xC] \n"
"    LDR     R1, =0xFF0C90B8 \n"
"    MOV     R2, #0x20 \n"
"    BL      sub_FF0CEEF8 \n"

"loc_FF0CA504:\n"
"    STRH    R0, [R4, #0xC] \n"
"    LDRSH   R0, [R4, #6] \n"
"    BL      sub_FF0B8CA8_my \n"  // --> Patched. Old value = 0xFF0B8CA8.
"    LDR     PC, =0xFF0CA510 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FF0B8CA8_my @ 0xFF0B8CA8 - 0xFF0B8CE8, length=17
void __attribute__((naked,noinline)) sub_FF0B8CA8_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R5, =0x587C \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5, #4] \n"
"    CMP     R0, #1 \n"
"    LDRNE   R1, =0x14D \n"
"    LDRNE   R0, =0xFF0B8AE0 /*'Shutter.c'*/ \n"
"    BLNE    _DebugAssert \n"
"    CMN     R4, #0xC00 \n"
"    LDREQSH R4, [R5, #2] \n"
"    CMN     R4, #0xC00 \n"
"    LDREQ   R1, =0x153 \n"
"    LDREQ   R0, =0xFF0B8AE0 /*'Shutter.c'*/ \n"
"    STRH    R4, [R5, #2] \n"
"    BLEQ    _DebugAssert \n"
"    MOV     R0, R4 \n"
"    BL      apex2us \n"  // --> Patched. Old value = _apex2us.
"    LDR     PC, =0xFF0B8CEC \n"  // Continue in firmware
);
}
