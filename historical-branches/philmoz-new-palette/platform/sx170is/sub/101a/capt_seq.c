/*
 * capt_seq.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"
#include "core.h"

//#define NR_AUTO (0)                 // have to explictly reset value back to 0 to enable auto
static long *nrflag = (long*)(0xA8F8+0xC); // sx170is 100a Found @ 0xffa2feb4 (0xA8F8) & 0xffa2feb8 (+0xC)
#define PAUSE_FOR_FILE_COUNTER 350  // Enable delay in capt_seq_hook_raw_here to ensure file counter is updated

#include "../../../generic/capt_seq.c"

/*************************************************************/
//** capt_seq_task @ 0xFF87A64C - 0xFF87A94C, length=193
void __attribute__((naked,noinline)) capt_seq_task() {
asm volatile (
"    STMFD   SP!, {R3-R7,LR} \n"
"    LDR     R5, =0x1D758 \n"
"    LDR     R7, =0x35A0 \n"
"    MOV     R6, #0 \n"

"loc_FF87A65C:\n"
"    LDR     R0, [R7, #4] \n"
"    MOV     R2, #0 \n"
"    MOV     R1, SP \n"
"    BL      sub_003F84B8 \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF87A68C \n"
"    LDR     R2, =0x4D4 \n"
"    LDR     R1, =0xFF879E90 /*'SsShootTask.c'*/ \n"
"    MOV     R0, #0 \n"
"    BL      _DebugAssert \n"
"    BL      _ExitTask \n"
"    LDMFD   SP!, {R3-R7,PC} \n"

"loc_FF87A68C:\n"
"    LDR     R0, [SP] \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #1 \n"
"    BLNE    sub_FF995700 \n"
"    LDR     R0, [SP] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x29 \n"
"    ADDCC   PC, PC, R1, LSL#2 \n"
"    B       loc_FF87A910 \n"
"    B       loc_FF87A754 \n"
"    B       loc_FF87A76C \n"
"    B       loc_FF87A778 \n"
"    B       loc_FF87A78C \n"
"    B       loc_FF87A784 \n"
"    B       loc_FF87A798 \n"
"    B       loc_FF87A7A0 \n"
"    B       loc_FF87A7A8 \n"
"    B       loc_FF87A7B4 \n"
"    B       loc_FF87A7E0 \n"
"    B       loc_FF87A7C0 \n"
"    B       loc_FF87A7CC \n"
"    B       loc_FF87A7D4 \n"
"    B       loc_FF87A7E8 \n"
"    B       loc_FF87A7F0 \n"
"    B       loc_FF87A7F8 \n"
"    B       loc_FF87A800 \n"
"    B       loc_FF87A808 \n"
"    B       loc_FF87A810 \n"
"    B       loc_FF87A818 \n"
"    B       loc_FF87A820 \n"
"    B       loc_FF87A828 \n"
"    B       loc_FF87A830 \n"
"    B       loc_FF87A838 \n"
"    B       loc_FF87A840 \n"
"    B       loc_FF87A84C \n"
"    B       loc_FF87A854 \n"
"    B       loc_FF87A85C \n"
"    B       loc_FF87A868 \n"
"    B       loc_FF87A870 \n"
"    B       loc_FF87A878 \n"
"    B       loc_FF87A880 \n"
"    B       loc_FF87A888 \n"
"    B       loc_FF87A890 \n"
"    B       loc_FF87A898 \n"
"    B       loc_FF87A8A4 \n"
"    B       loc_FF87A8AC \n"
"    B       loc_FF87A8B8 \n"
"    B       loc_FF87A8F0 \n"
"    B       loc_FF87A8FC \n"
"    B       loc_FF87A920 \n"

"loc_FF87A754:\n"
//"    BL      shooting_expo_iso_override\n"      // extra ISO override call doesn't appear to be needed on elph130
"    BL      sub_FF87AE34 \n"
"    BL      shooting_expo_param_override\n"    // added
"    BL      sub_FF877CE4 \n"
// try avoid intermittetant override failues on quick press, not needed?
//"    MOV     R0, #0\n"                          // added
//"    STR     R0, [R5,#0x28]\n"                  // added
"    LDR     R0, [R5, #0x28] \n"
"    CMP     R0, #0 \n"
"    BLNE    sub_FF994004_my \n"  // --> Patched. Old value = 0xFF994004.
"    B       loc_FF87A920 \n"

"loc_FF87A76C:\n"
"    LDR     R0, [R0, #0x10] \n"
"    BL      sub_FF993EFC_my \n"  // --> Patched. Old value = 0xFF993EFC.
"    B       loc_FF87A920 \n"

"loc_FF87A778:\n"
"    MOV     R0, #1 \n"
"    BL      sub_FF87B19C \n"
"    B       loc_FF87A920 \n"

"loc_FF87A784:\n"
"    BL      sub_FF87AB10 \n"
"    B       loc_FF87A790 \n"

"loc_FF87A78C:\n"
"    BL      sub_FF87AE10 \n"

"loc_FF87A790:\n"
"    STR     R6, [R5, #0x28] \n"
"    B       loc_FF87A920 \n"

"loc_FF87A798:\n"
"    BL      sub_FF87AE18 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7A0:\n"
"    BL      sub_FF87B058 \n"
"    B       loc_FF87A7B8 \n"

"loc_FF87A7A8:\n"
"    LDR     R0, [R0, #0x10] \n"
"    BL      sub_FF994094 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7B4:\n"
"    BL      sub_FF87B0F0 \n"

"loc_FF87A7B8:\n"
"    BL      sub_FF877CE4 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7C0:\n"
"    LDR     R0, [R5, #0x58] \n"
"    BL      sub_FF87B844 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7CC:\n"
"    BL      sub_FF87BC94 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7D4:\n"
"    LDR     R0, [R0, #0xC] \n"
"    BL      sub_FF87BCFC \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7E0:\n"
"    BL      sub_FF87AE10 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7E8:\n"
"    BL      sub_FF993300 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7F0:\n"
"    BL      sub_FF99353C \n"
"    B       loc_FF87A920 \n"

"loc_FF87A7F8:\n"
"    BL      sub_FF9935F8 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A800:\n"
"    BL      sub_FF993698 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A808:\n"
"    BL      sub_FF993770 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A810:\n"
"    MOV     R0, #0 \n"
"    B       loc_FF87A844 \n"

"loc_FF87A818:\n"
"    BL      sub_FF993B90 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A820:\n"
"    BL      sub_FF881A30 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A828:\n"
"    BL      sub_FF881A3C \n"
"    B       loc_FF87A920 \n"

"loc_FF87A830:\n"
"    BL      sub_FF993C2C \n"
"    B       loc_FF87A920 \n"

"loc_FF87A838:\n"
"    BL      sub_FF993CD8 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A840:\n"
"    MOV     R0, #1 \n"

"loc_FF87A844:\n"
"    BL      sub_FF993A2C \n"
"    B       loc_FF87A920 \n"

"loc_FF87A84C:\n"
"    BL      sub_FF87B31C \n"
"    B       loc_FF87A920 \n"

"loc_FF87A854:\n"
"    MOV     R0, #0 \n"
"    B       loc_FF87A860 \n"

"loc_FF87A85C:\n"
"    LDR     R0, [R0, #0xC] \n"

"loc_FF87A860:\n"
"    BL      sub_FF87B3A8 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A868:\n"
"    BL      sub_FF993900 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A870:\n"
"    BL      sub_FF993998 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A878:\n"
"    BL      sub_FF994DF0 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A880:\n"
//"  BL      _sub_FF8785E8 \n"  // --> Nullsub call removed.
"    B       loc_FF87A920 \n"

"loc_FF87A888:\n"
"    BL      sub_FF87E30C \n"
"    B       loc_FF87A920 \n"

"loc_FF87A890:\n"
"    BL      sub_FF87E428 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A898:\n"
"    LDR     R0, [R0, #0xC] \n"
"    BL      sub_FF993DE8 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A8A4:\n"
"    BL      sub_FF993E70 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A8AC:\n"
"    BL      sub_FF87E598 \n"
"    BL      sub_FF87E484 \n"
"    B       loc_FF87A920 \n"

"loc_FF87A8B8:\n"
"    MOV     R0, #1 \n"
"    BL      sub_FF99481C \n"
"    MOV     R0, #1 \n"
"    BL      sub_FF994948 \n"
"    LDR     R0, =0x1D858 \n"
"    LDRH    R0, [R0, #0xB0] \n"
"    CMP     R0, #4 \n"
"    LDRNEH  R0, [R5] \n"
"    SUBNE   R1, R0, #0x8000 \n"
"    SUBNES  R1, R1, #0x230 \n"
"    BNE     loc_FF87A920 \n"
"    BL      sub_FF87E428 \n"
"    BL      sub_FF87E93C \n"
"    B       loc_FF87A920 \n"

"loc_FF87A8F0:\n"
"    MOV     R2, #0 \n"
"    MOV     R1, #0x10 \n"
"    B       loc_FF87A904 \n"

"loc_FF87A8FC:\n"
"    MOV     R2, #0 \n"
"    MOV     R1, #0xF \n"

"loc_FF87A904:\n"
"    MOV     R0, #0 \n"
"    BL      sub_FF8787AC \n"
"    B       loc_FF87A920 \n"

"loc_FF87A910:\n"
"    LDR     R2, =0x65A \n"
"    LDR     R1, =0xFF879E90 /*'SsShootTask.c'*/ \n"
"    MOV     R0, #0 \n"
"    BL      _DebugAssert \n"

"loc_FF87A920:\n"
"    LDR     R0, [SP] \n"
"    LDR     R1, [R0, #4] \n"
"    LDR     R0, [R7] \n"
"    BL      sub_003F82C8 /*_SetEventFlag*/ \n"
"    LDR     R4, [SP] \n"
"    LDR     R0, [R4, #8] \n"
"    CMP     R0, #0 \n"
"    LDREQ   R2, =0x126 \n"
"    LDREQ   R1, =0xFF879E90 /*'SsShootTask.c'*/ \n"
"    BLEQ    _DebugAssert \n"
"    STR     R6, [R4, #8] \n"
"    B       loc_FF87A65C \n"
);
}

/*************************************************************/
//** sub_FF994004_my @ 0xFF994004 - 0xFF994090, length=36
void __attribute__((naked,noinline)) sub_FF994004_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    BL      sub_FF879A6C \n"
"    MOV     R4, R0 \n"
"    MOV     R0, #0xC \n"
"    BL      sub_FF8801D8 \n"
"    LDR     R6, =0x7944 \n"
"    TST     R0, #1 \n"
"    MOV     R5, #1 \n"
"    BNE     loc_FF99408C \n"
"    BL      sub_FF87AE20 \n"
"    BL      sub_FF87C038 \n"
"    MOV     R1, R4 \n"
"    BL      sub_FF87C094 \n"
"    LDR     R0, =0x10E \n"
"    MOV     R2, #4 \n"
"    ADD     R1, R4, #0x30 \n"
"    BL      _SetPropertyCase \n"
"    MOV     R2, #4 \n"
"    ADD     R1, R4, #0x34 \n"
"    MOV     R0, #0x2C \n"
"    BL      _SetPropertyCase \n"
"    MOV     R2, #4 \n"
"    ADD     R1, R4, #8 \n"
"    MOV     R0, #0x3F \n"
"    BL      _SetPropertyCase \n"
"    BL      sub_FF994B08 \n"
"    MVN     R1, #0x1000 \n"
"    BL      sub_003F82FC /*_ClearEventFlag*/ \n"
"    MOV     R0, R4 \n"
"    BL      sub_FFAD9E68 \n"
"    MOV     R0, R4 \n"
"    BL      sub_FFADA20C_my \n"  // --> Patched. Old value = 0xFFADA20C.
"    BL      capt_seq_hook_raw_here \n"         // added
"    TST     R0, #1 \n"
"    LDMEQFD SP!, {R4-R6,PC} \n"

"loc_FF99408C:\n"
"    STR     R5, [R6] \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
);
}

/*************************************************************/
//** sub_FF993EFC_my @ 0xFF993EFC - 0xFF994000, length=66
void __attribute__((naked,noinline)) sub_FF993EFC_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R6, =0x1D758 \n"
"    MOV     R5, R0 \n"
"    LDR     R0, [R6, #0x28] \n"
"    MOV     R4, #0 \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FF993F48 \n"
"    LDR     R0, =0x7944 \n"
"    MOV     R2, R5 \n"
"    LDR     R0, [R0] \n"
"    MOV     R1, #1 \n"
"    CMP     R0, #0 \n"
"    MOVNE   R4, #0x1D \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF8787AC \n"
"    MOV     R1, R4 \n"
"    MOV     R0, R5 \n"
"    BL      sub_FF995488 \n"
"    B       loc_FF993FF8 \n"

"loc_FF993F48:\n"
"    BL      sub_FF87C038 \n"
"    MOV     R1, R5 \n"
"    BL      sub_FF87C094 \n"
"    LDR     R0, =0x10E \n"
"    MOV     R2, #4 \n"
"    ADD     R1, R5, #0x30 \n"
"    BL      _SetPropertyCase \n"
"    MOV     R2, #4 \n"
"    ADD     R1, R5, #0x34 \n"
"    MOV     R0, #0x2C \n"
"    BL      _SetPropertyCase \n"
"    MOV     R0, #0xC \n"
"    BL      sub_FF8801D8 \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF993F8C \n"
"    BL      sub_FF8785D8 \n"
"    MOV     R4, #1 \n"

"loc_FF993F8C:\n"
"    TST     R4, #1 \n"
"    BNE     loc_FF993FDC \n"
"    MOV     R0, R5 \n"
"    BL      sub_FF994E64 \n"
"    BL      sub_FF994B08 \n"
"    MVN     R1, #0x1000 \n"
"    BL      sub_003F82FC /*_ClearEventFlag*/ \n"
"    MOV     R0, R5 \n"
"    BL      sub_FFAD9538 \n"
"    TST     R0, #1 \n"
"    MOV     R4, R0 \n"
"    BNE     loc_FF993FDC \n"
"    BL      sub_FF87AE20 \n"
"    MOV     R0, R5 \n"
"    BL      sub_FFAD9E68 \n"
"    MOV     R0, #2 \n"
"    BL      sub_FF881BA8 \n"
"    MOV     R0, R5 \n"
"    BL      sub_FFADA20C_my \n"  // --> Patched. Old value = 0xFFADA20C.
"    BL      capt_seq_hook_raw_here \n"         // added
"    B       loc_FF993FF8 \n"

"loc_FF993FDC:\n"
"    MOV     R2, R5 \n"
"    MOV     R1, #1 \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF8787AC \n"
"    MOV     R1, R4 \n"
"    MOV     R0, R5 \n"
"    BL      sub_FF99569C \n"

"loc_FF993FF8:\n"
"    MOV     R0, #0 \n"
"    STR     R0, [R6, #0x28] \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
);
}

/*************************************************************/
//** sub_FFADA20C_my @ 0xFFADA20C - 0xFFADA290, length=34
void __attribute__((naked,noinline)) sub_FFADA20C_my() {
asm volatile (
"    STMFD   SP!, {R2-R10,LR} \n"
"    MOV     R4, R0 \n"
"    BL      sub_FFAD9DE0 \n"
"    BL      sub_FF9945E0 \n"
"    LDR     R8, =0x1D758 \n"
"    LDR     R0, [R8, #0x1A4] \n"
"    CMP     R0, #2 \n"
"    BNE     loc_FFADA248 \n"
"    ADD     R0, R8, #0x100 \n"
"    LDRH    R0, [R0, #0xAE] \n"
"    CMP     R0, #3 \n"
"    LDRNE   R0, [R4, #8] \n"
"    CMPNE   R0, #1 \n"
"    MOVLS   R0, #4 \n"
"    BLLS    sub_FF90DD78 \n"

"loc_FFADA248:\n"
"    LDR     R0, =0x12F \n"
"    MOV     R2, #4 \n"
"    ADD     R1, SP, #4 \n"
"    BL      _GetPropertyCase \n"
"    TST     R0, #1 \n"
"    LDRNE   R2, =0x17B \n"
"    LDRNE   R1, =0xFFADA474 /*'SsStandardCaptureSeq.c'*/ \n"
"    MOVNE   R0, #0 \n"
"    BLNE    _DebugAssert \n"
"    LDR     R0, [SP, #4] \n"
"    AND     R0, R0, #0xFF00 \n"
"    CMP     R0, #0x600 \n"
"    LDRNE   R0, =0xFFAD9A68 \n"
"    LDREQ   R0, =0xFFADA1D4 \n"
"    MOVNE   R1, R4 \n"
"    MOVEQ   R1, #0 \n"
"    BL      sub_FF8BDC88 \n"
"    MOV     R0, R4 \n"
"    BL      sub_FFAD9EF0_my \n"  // --> Patched. Old value = 0xFFAD9EF0.
"    LDR     PC, =0xFFADA294 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFAD9EF0_my @ 0xFFAD9EF0 - 0xFFAD9F9C, length=44
void __attribute__((naked,noinline)) sub_FFAD9EF0_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R6, =0x1D758 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R6, #0xFC] \n"
"    LDR     R5, =0xD700 \n"
"    CMP     R0, #0 \n"
"    ADDNE   R0, R6, #0x100 \n"
"    LDRNEH  R0, [R0, #0xAE] \n"
"    CMPNE   R0, #3 \n"
"    LDRNE   R0, [R4, #8] \n"
"    CMPNE   R0, #1 \n"
"    BHI     loc_FFAD9F40 \n"
"    BL      _GetCCDTemperature \n"
"    MOV     R1, R0 \n"
"    STRH    R0, [R4, #0xB0] \n"
"    LDR     R0, =0x1D950 \n"
"    LDRSH   R2, [R0, #0xC] \n"
"    LDRH    R0, [R6, #0x5E] \n"
"    BL      sub_FFA2FE14 \n"
"    STR     R0, [R5] \n"

"loc_FFAD9F40:\n"
"    BL      wait_until_remote_button_is_released\n" // added
"    BL      capt_seq_hook_set_nr\n"                 // added
"    LDR     R0, [R4, #0x20] \n"
"    MOV     R1, #0 \n"
"    CMP     R0, #0 \n"
"    STRNE   R1, [R5] \n"
"    LDR     R0, [R5] \n"
"    CMP     R0, #0 \n"
"    STREQH  R1, [R4, #0x18] \n"
"    BEQ     loc_FFAD9F7C \n"
"    CMP     R0, #1 \n"
"    STREQH  R0, [R4, #0x18] \n"
"    BEQ     loc_FFAD9F7C \n"
"    LDR     R2, =0x343 \n"
"    LDR     R1, =0xFFAD9AE0 /*'SsCaptureCommon.c'*/ \n"
"    MOV     R0, #0 \n"
"    BL      _DebugAssert \n"

"loc_FFAD9F7C:\n"
"    LDR     R0, [R4, #0x1C] \n"
"    MOV     R3, #2 \n"
"    ADD     R2, R4, #0x18 \n"
"    MOV     R1, #0x33 \n"
"    BL      sub_FF88B388 \n"
"    LDR     R0, [R5] \n"
"    MOV     R0, R0, LSL#16 \n"
"    MOV     R0, R0, LSR#16 \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
);
}

/*************************************************************/
//** exp_drv_task @ 0xFF8CB99C - 0xFF8CC020, length=418
void __attribute__((naked,noinline)) exp_drv_task() {
asm volatile (
"    STMFD   SP!, {R4-R9,LR} \n"
"    SUB     SP, SP, #0x2C \n"
"    LDR     R6, =0x4834 \n"
"    LDR     R7, =0xBB8 \n"
"    LDR     R4, =0x5A344 \n"
"    MOV     R0, #0 \n"
"    ADD     R5, SP, #0x1C \n"
"    STR     R0, [SP, #0xC] \n"

"loc_FF8CB9BC:\n"
"    LDR     R0, [R6, #0x20] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #0x28 \n"
"    BL      sub_003F84B8 \n"
"    LDR     R0, [SP, #0xC] \n"
"    CMP     R0, #1 \n"
"    BNE     loc_FF8CBA08 \n"
"    LDR     R0, [SP, #0x28] \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #0x14 \n"
"    CMPNE   R0, #0x15 \n"
"    CMPNE   R0, #0x16 \n"
"    CMPNE   R0, #0x17 \n"
"    BEQ     loc_FF8CBB6C \n"
"    CMP     R0, #0x2A \n"
"    BEQ     loc_FF8CBAF0 \n"
"    ADD     R1, SP, #0xC \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF8CB948 \n"

"loc_FF8CBA08:\n"
"    LDR     R0, [SP, #0x28] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x30 \n"
"    BNE     loc_FF8CBA34 \n"
"    BL      sub_FF8CCFE4 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R1, #1 \n"
"    BL      sub_003F82C8 /*_SetEventFlag*/ \n"
"    BL      _ExitTask \n"
"    ADD     SP, SP, #0x2C \n"
"    LDMFD   SP!, {R4-R9,PC} \n"

"loc_FF8CBA34:\n"
"    CMP     R1, #0x2F \n"
"    BNE     loc_FF8CBA50 \n"
"    LDR     R2, [R0, #0xA8]! \n"
"    LDR     R1, [R0, #4] \n"
"    MOV     R0, R1 \n"
"    BLX     R2 \n"
"    B       loc_FF8CC018 \n"

"loc_FF8CBA50:\n"
"    CMP     R1, #0x28 \n"
"    BNE     loc_FF8CBAA0 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_003F82FC /*_ClearEventFlag*/ \n"
"    LDR     R0, =0xFF8C6EE4 \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_FF871FE0 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R2, R7 \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_003F81FC /*_WaitForAllEventFlag*/ \n"
"    TST     R0, #1 \n"
"    LDRNE   R2, =0x16EF \n"
"    BNE     loc_FF8CBB5C \n"

"loc_FF8CBA8C:\n"
"    LDR     R1, [SP, #0x28] \n"
"    LDR     R0, [R1, #0xAC] \n"
"    LDR     R1, [R1, #0xA8] \n"
"    BLX     R1 \n"
"    B       loc_FF8CC018 \n"

"loc_FF8CBAA0:\n"
"    CMP     R1, #0x29 \n"
"    BNE     loc_FF8CBAE8 \n"
"    ADD     R1, SP, #0xC \n"
"    BL      sub_FF8CB948 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_003F82FC /*_ClearEventFlag*/ \n"
"    LDR     R0, =0xFF8C6EF4 \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_FF872DB4 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R2, R7 \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_003F81FC /*_WaitForAllEventFlag*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF8CBA8C \n"
"    LDR     R2, =0x16F9 \n"
"    B       loc_FF8CBB5C \n"

"loc_FF8CBAE8:\n"
"    CMP     R1, #0x2A \n"
"    BNE     loc_FF8CBB00 \n"

"loc_FF8CBAF0:\n"
"    LDR     R0, [SP, #0x28] \n"
"    ADD     R1, SP, #0xC \n"
"    BL      sub_FF8CB948 \n"
"    B       loc_FF8CBA8C \n"

"loc_FF8CBB00:\n"
"    CMP     R1, #0x2D \n"
"    BNE     loc_FF8CBB18 \n"
"    BL      sub_FF8B57D4 \n"
"    BL      sub_FF8B663C \n"
"    BL      sub_FF8B611C \n"
"    B       loc_FF8CBA8C \n"

"loc_FF8CBB18:\n"
"    CMP     R1, #0x2E \n"
"    BNE     loc_FF8CBB6C \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R1, #4 \n"
"    BL      sub_003F82FC /*_ClearEventFlag*/ \n"
"    LDR     R1, =0xFF8C6F14 \n"
"    LDR     R0, =0xFFFFF400 \n"
"    MOV     R2, #4 \n"
"    BL      sub_FF8B51B8 \n"
"    BL      sub_FF8B5468 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    MOV     R2, R7 \n"
"    MOV     R1, #4 \n"
"    BL      sub_003F8110 /*_WaitForAnyEventFlag*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF8CBA8C \n"
"    LDR     R2, =0x1721 \n"

"loc_FF8CBB5C:\n"
"    LDR     R1, =0xFF8C7644 /*'ExpDrv.c'*/ \n"
"    MOV     R0, #0 \n"
"    BL      _DebugAssert \n"
"    B       loc_FF8CBA8C \n"

"loc_FF8CBB6C:\n"
"    LDR     R0, [SP, #0x28] \n"
"    MOV     R8, #1 \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x12 \n"
"    CMPNE   R1, #0x13 \n"
"    BNE     loc_FF8CBBD4 \n"
"    LDR     R1, [R0, #0x94] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R1, R0, R1, LSL#2 \n"
"    SUB     R1, R1, #8 \n"
"    LDMIA   R1, {R2,R3,R9} \n"
"    STMIA   R5, {R2,R3,R9} \n"
"    BL      sub_FF8C9DF8 \n"
"    LDR     R0, [SP, #0x28] \n"
"    LDR     R1, [R0, #0x94] \n"
"    LDR     R3, [R0, #0xA8] \n"
"    LDR     R2, [R0, #0xAC] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"
"    LDR     R0, [SP, #0x28] \n"
"    BL      sub_FF8CD31C \n"
"    LDR     R0, [SP, #0x28] \n"
"    LDR     R1, [R0, #0x94] \n"
"    LDR     R2, [R0, #0xB4] \n"
"    LDR     R3, [R0, #0xB0] \n"
"    B       loc_FF8CBEDC \n"

"loc_FF8CBBD4:\n"
"    CMP     R1, #0x14 \n"
"    CMPNE   R1, #0x15 \n"
"    CMPNE   R1, #0x16 \n"
"    CMPNE   R1, #0x17 \n"
"    BNE     loc_FF8CBC7C \n"
"    ADD     R3, SP, #0xC \n"
"    MOV     R2, SP \n"
"    ADD     R1, SP, #0x1C \n"
"    BL      sub_FF8CA068 \n"
"    CMP     R0, #1 \n"
"    MOV     R9, R0 \n"
"    CMPNE   R9, #5 \n"
"    BNE     loc_FF8CBC28 \n"
"    LDR     R0, [SP, #0x28] \n"
"    MOV     R2, R9 \n"
"    LDR     R1, [R0, #0x94] \n"
"    LDR     R12, [R0, #0xA8] \n"
"    LDR     R3, [R0, #0xAC] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R12 \n"
"    B       loc_FF8CBC60 \n"

"loc_FF8CBC28:\n"
"    LDR     R0, [SP, #0x28] \n"
"    CMP     R9, #2 \n"
"    LDR     R1, [R0, #0x94] \n"
"    LDR     R12, [R0, #0xA8] \n"
"    LDR     R3, [R0, #0xAC] \n"
"    CMPNE   R9, #6 \n"
"    MOV     R2, R9 \n"
"    ADD     R0, R0, #4 \n"
"    BNE     loc_FF8CBC74 \n"
"    BLX     R12 \n"
"    LDR     R0, [SP, #0x28] \n"
"    MOV     R2, SP \n"
"    ADD     R1, SP, #0x1C \n"
"    BL      sub_FF8CB68C \n"

"loc_FF8CBC60:\n"
"    LDR     R0, [SP, #0x28] \n"
"    LDR     R2, [SP, #0xC] \n"
"    MOV     R1, R9 \n"
"    BL      sub_FF8CB8E0 \n"
"    B       loc_FF8CBEE4 \n"

"loc_FF8CBC74:\n"
"    BLX     R12 \n"
"    B       loc_FF8CBEE4 \n"

"loc_FF8CBC7C:\n"
"    CMP     R1, #0x24 \n"
"    CMPNE   R1, #0x25 \n"
"    BNE     loc_FF8CBCC8 \n"
"    LDR     R1, [R0, #0x94] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R1, R0, R1, LSL#2 \n"
"    SUB     R1, R1, #8 \n"
"    LDMIA   R1, {R2,R3,R9} \n"
"    STMIA   R5, {R2,R3,R9} \n"
"    BL      sub_FF8C8D10 \n"
"    LDR     R0, [SP, #0x28] \n"
"    LDR     R1, [R0, #0x94] \n"
"    LDR     R3, [R0, #0xA8] \n"
"    LDR     R2, [R0, #0xAC] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"
"    LDR     R0, [SP, #0x28] \n"
"    BL      sub_FF8C916C \n"
"    B       loc_FF8CBEE4 \n"

"loc_FF8CBCC8:\n"
"    ADD     R1, R0, #4 \n"
"    LDMIA   R1, {R2,R3,R9} \n"
"    STMIA   R5, {R2,R3,R9} \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x28 \n"
"    ADDCC   PC, PC, R1, LSL#2 \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBD84 \n"
"    B       loc_FF8CBD84 \n"
"    B       loc_FF8CBD8C \n"
"    B       loc_FF8CBD94 \n"
"    B       loc_FF8CBD94 \n"
"    B       loc_FF8CBD94 \n"
"    B       loc_FF8CBD84 \n"
"    B       loc_FF8CBD8C \n"
"    B       loc_FF8CBD94 \n"
"    B       loc_FF8CBD94 \n"
"    B       loc_FF8CBDAC \n"
"    B       loc_FF8CBDAC \n"
"    B       loc_FF8CBEB8 \n"
"    B       loc_FF8CBEC0 \n"
"    B       loc_FF8CBEC0 \n"
"    B       loc_FF8CBEC0 \n"
"    B       loc_FF8CBEC0 \n"
"    B       loc_FF8CBEC8 \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBD9C \n"
"    B       loc_FF8CBDA4 \n"
"    B       loc_FF8CBDA4 \n"
"    B       loc_FF8CBDA4 \n"
"    B       loc_FF8CBDB8 \n"
"    B       loc_FF8CBDB8 \n"
"    B       loc_FF8CBDC0 \n"
"    B       loc_FF8CBDF8 \n"
"    B       loc_FF8CBE30 \n"
"    B       loc_FF8CBE68 \n"
"    B       loc_FF8CBEA0 \n"
"    B       loc_FF8CBEA0 \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBECC \n"
"    B       loc_FF8CBEA8 \n"
"    B       loc_FF8CBEB0 \n"

"loc_FF8CBD84:\n"
"    BL      sub_FF8C74C4 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBD8C:\n"
"    BL      sub_FF8C7794 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBD94:\n"
"    BL      sub_FF8C79D4 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBD9C:\n"
"    BL      sub_FF8C7D1C \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBDA4:\n"
"    BL      sub_FF8C7F4C \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBDAC:\n"
"    BL      sub_FF8C8330_my \n"  // --> Patched. Old value = 0xFF8C8330.
"    MOV     R8, #0 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBDB8:\n"
"    BL      sub_FF8C8500 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBDC0:\n"
"    LDRH    R1, [R0, #4] \n"
"    STRH    R1, [SP, #0x1C] \n"
"    LDRH    R1, [R4, #2] \n"
"    STRH    R1, [SP, #0x1E] \n"
"    LDRH    R1, [R4, #4] \n"
"    STRH    R1, [SP, #0x20] \n"
"    LDRH    R1, [R4, #6] \n"
"    STRH    R1, [SP, #0x22] \n"
"    LDRH    R1, [R0, #0xC] \n"
"    STRH    R1, [SP, #0x24] \n"
"    LDRH    R1, [R4, #0xA] \n"
"    STRH    R1, [SP, #0x26] \n"
"    BL      sub_FF8C897C \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBDF8:\n"
"    LDRH    R1, [R0, #4] \n"
"    STRH    R1, [SP, #0x1C] \n"
"    LDRH    R1, [R4, #2] \n"
"    STRH    R1, [SP, #0x1E] \n"
"    LDRH    R1, [R4, #4] \n"
"    STRH    R1, [SP, #0x20] \n"
"    LDRH    R1, [R4, #6] \n"
"    STRH    R1, [SP, #0x22] \n"
"    LDRH    R1, [R4, #8] \n"
"    STRH    R1, [SP, #0x24] \n"
"    LDRH    R1, [R4, #0xA] \n"
"    STRH    R1, [SP, #0x26] \n"
"    BL      sub_FF8CD08C \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBE30:\n"
"    LDRH    R1, [R4] \n"
"    STRH    R1, [SP, #0x1C] \n"
"    LDRH    R1, [R0, #6] \n"
"    STRH    R1, [SP, #0x1E] \n"
"    LDRH    R1, [R4, #4] \n"
"    STRH    R1, [SP, #0x20] \n"
"    LDRH    R1, [R4, #6] \n"
"    STRH    R1, [SP, #0x22] \n"
"    LDRH    R1, [R4, #8] \n"
"    STRH    R1, [SP, #0x24] \n"
"    LDRH    R1, [R4, #0xA] \n"
"    STRH    R1, [SP, #0x26] \n"
"    BL      sub_FF8CD1C8 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBE68:\n"
"    LDRH    R1, [R4] \n"
"    STRH    R1, [SP, #0x1C] \n"
"    LDRH    R1, [R4, #2] \n"
"    STRH    R1, [SP, #0x1E] \n"
"    LDRH    R1, [R4, #4] \n"
"    STRH    R1, [SP, #0x20] \n"
"    LDRH    R1, [R4, #6] \n"
"    STRH    R1, [SP, #0x22] \n"
"    LDRH    R1, [R0, #0xC] \n"
"    STRH    R1, [SP, #0x24] \n"
"    LDRH    R1, [R4, #0xA] \n"
"    STRH    R1, [SP, #0x26] \n"
"    BL      sub_FF8CD274 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBEA0:\n"
"    BL      sub_FF8C8A90 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBEA8:\n"
"    BL      sub_FF8C9284 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBEB0:\n"
"    BL      sub_FF8C9624 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBEB8:\n"
"    BL      sub_FF8C9894 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBEC0:\n"
"    BL      sub_FF8C9A60 \n"
"    B       loc_FF8CBECC \n"

"loc_FF8CBEC8:\n"
"    BL      sub_FF8C9BD8 \n"

"loc_FF8CBECC:\n"
"    LDR     R0, [SP, #0x28] \n"
"    LDR     R1, [R0, #0x94] \n"
"    LDR     R2, [R0, #0xAC] \n"
"    LDR     R3, [R0, #0xA8] \n"

"loc_FF8CBEDC:\n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"

"loc_FF8CBEE4:\n"
"    LDR     R0, [SP, #0x28] \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #0x10 \n"
"    BEQ     loc_FF8CBF1C \n"
"    BGT     loc_FF8CBF0C \n"
"    CMP     R0, #1 \n"
"    CMPNE   R0, #4 \n"
"    CMPNE   R0, #0xE \n"
"    BNE     loc_FF8CBF50 \n"
"    B       loc_FF8CBF1C \n"

"loc_FF8CBF0C:\n"
"    CMP     R0, #0x13 \n"
"    CMPNE   R0, #0x17 \n"
"    CMPNE   R0, #0x1A \n"
"    BNE     loc_FF8CBF50 \n"

"loc_FF8CBF1C:\n"
"    LDRSH   R0, [R4] \n"
"    CMN     R0, #0xC00 \n"
"    LDRNESH R1, [R4, #8] \n"
"    CMNNE   R1, #0xC00 \n"
"    STRNEH  R0, [SP, #0x1C] \n"
"    STRNEH  R1, [SP, #0x24] \n"
"    BNE     loc_FF8CBF50 \n"
"    ADD     R0, SP, #0x10 \n"
"    BL      sub_FF8CD534 \n"
"    LDRH    R0, [SP, #0x10] \n"
"    STRH    R0, [SP, #0x1C] \n"
"    LDRH    R0, [SP, #0x18] \n"
"    STRH    R0, [SP, #0x24] \n"

"loc_FF8CBF50:\n"
"    LDR     R0, [SP, #0x28] \n"
"    CMP     R8, #1 \n"
"    BNE     loc_FF8CBFA0 \n"
"    LDR     R1, [R0, #0x94] \n"
"    MOV     R2, #0xC \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R0, R0, R1, LSL#2 \n"
"    SUB     R8, R0, #8 \n"
"    LDR     R0, =0x5A344 \n"
"    ADD     R1, SP, #0x1C \n"
"    BL      sub_003FC064 \n"
"    LDR     R0, =0x5A350 \n"
"    MOV     R2, #0xC \n"
"    ADD     R1, SP, #0x1C \n"
"    BL      sub_003FC064 \n"
"    LDR     R0, =0x5A35C \n"
"    MOV     R2, #0xC \n"
"    MOV     R1, R8 \n"
"    BL      sub_003FC064 \n"
"    B       loc_FF8CC018 \n"

"loc_FF8CBFA0:\n"
"    LDR     R0, [R0] \n"
"    MOV     R3, #1 \n"
"    CMP     R0, #0xB \n"
"    BNE     loc_FF8CBFE4 \n"
"    MOV     R2, #0 \n"
"    STRD    R2, [SP] \n"
"    MOV     R2, R3 \n"
"    MOV     R1, R3 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF8C7284 \n"
"    MOV     R3, #1 \n"
"    MOV     R2, #0 \n"
"    STRD    R2, [SP] \n"
"    MOV     R2, R3 \n"
"    MOV     R1, R3 \n"
"    MOV     R0, #0 \n"
"    B       loc_FF8CC014 \n"

"loc_FF8CBFE4:\n"
"    MOV     R2, #1 \n"
"    STRD    R2, [SP] \n"
"    MOV     R3, R2 \n"
"    MOV     R1, R2 \n"
"    MOV     R0, R2 \n"
"    BL      sub_FF8C7284 \n"
"    MOV     R3, #1 \n"
"    MOV     R2, R3 \n"
"    MOV     R1, R3 \n"
"    MOV     R0, R3 \n"
"    STR     R3, [SP] \n"
"    STR     R3, [SP, #4] \n"

"loc_FF8CC014:\n"
"    BL      sub_FF8C740C \n"

"loc_FF8CC018:\n"
"    LDR     R0, [SP, #0x28] \n"
"    BL      sub_FF8CCFE4 \n"
"    B       loc_FF8CB9BC \n"
);
}

/*************************************************************/
//** sub_FF8C8330_my @ 0xFF8C8330 - 0xFF8C83F4, length=50
void __attribute__((naked,noinline)) sub_FF8C8330_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    LDR     R7, =0x4834 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R1, #0x3E \n"
"    BL      sub_003F82FC /*_ClearEventFlag*/ \n"
"    MOV     R2, #0 \n"
"    LDRSH   R0, [R4, #4] \n"
"    MOV     R3, #1 \n"
"    MOV     R1, R2 \n"
"    BL      sub_FF8C6F7C \n"
"    MOV     R6, R0 \n"
"    LDRSH   R0, [R4, #6] \n"
"    BL      sub_FF8C70E4 \n"
"    LDRSH   R0, [R4, #8] \n"
"    BL      sub_FF8C713C \n"
"    LDRSH   R0, [R4, #0xA] \n"
"    BL      sub_FF8C7194 \n"
"    LDRSH   R0, [R4, #0xC] \n"
"    MOV     R1, #0 \n"
"    BL      sub_FF8C71EC \n"
"    MOV     R5, R0 \n"
"    LDR     R0, [R4] \n"
"    LDR     R8, =0x5A35C \n"
"    CMP     R0, #0xB \n"
"    MOVEQ   R6, #0 \n"
"    MOVEQ   R5, R6 \n"
"    BEQ     loc_FF8C83C8 \n"
"    CMP     R6, #1 \n"
"    BNE     loc_FF8C83C8 \n"
"    LDRSH   R0, [R4, #4] \n"
"    LDR     R1, =0xFF8C6ED4 \n"
"    MOV     R2, #2 \n"
"    BL      sub_FF87230C \n"
"    STRH    R0, [R4, #4] \n"
"    MOV     R0, #0 \n"
"    STR     R0, [R7, #0x28] \n"
"    B       loc_FF8C83D0 \n"

"loc_FF8C83C8:\n"
"    LDRH    R0, [R8] \n"
"    STRH    R0, [R4, #4] \n"

"loc_FF8C83D0:\n"
"    CMP     R5, #1 \n"
"    LDRNEH  R0, [R8, #8] \n"
"    BNE     loc_FF8C83EC \n"
"    LDRSH   R0, [R4, #0xC] \n"
"    LDR     R1, =0xFF8C6F58 \n"
"    MOV     R2, #0x20 \n"
"    BL      sub_FF8CD048 \n"

"loc_FF8C83EC:\n"
"    STRH    R0, [R4, #0xC] \n"
"    LDRSH   R0, [R4, #6] \n"
"    BL      sub_FF8B54E0_my \n"  // --> Patched. Old value = 0xFF8B54E0.
"    LDR     PC, =0xFF8C83F8 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FF8B54E0_my @ 0xFF8B54E0 - 0xFF8B5528, length=19
void __attribute__((naked,noinline)) sub_FF8B54E0_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R5, =0x44A8 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5, #4] \n"
"    CMP     R0, #1 \n"
"    MOVNE   R2, #0x154 \n"
"    LDRNE   R1, =0xFF8B52A8 /*'Shutter.c'*/ \n"
"    MOVNE   R0, #0 \n"
"    BLNE    _DebugAssert \n"
"    CMN     R4, #0xC00 \n"
"    LDREQSH R4, [R5, #2] \n"
"    CMN     R4, #0xC00 \n"
"    LDREQ   R2, =0x15A \n"
"    LDREQ   R1, =0xFF8B52A8 /*'Shutter.c'*/ \n"
"    MOVEQ   R0, #0 \n"
"    STRH    R4, [R5, #2] \n"
"    BLEQ    _DebugAssert \n"
"    MOV     R0, R4 \n"
"    BL      apex2us \n"  // --> Patched. Old value = _apex2us.
"    LDR     PC, =0xFF8B552C \n"  // Continue in firmware
);
}
