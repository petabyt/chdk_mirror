#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)(0x69bc+0x08);         // Found @ ff96b860 & ff96b8ac
#define NR_AUTO (0)                 // have to explictly reset value back to 0 to enable auto
#define PAUSE_FOR_FILE_COUNTER 150          // Enable delay in capt_seq_hook_raw_here to ensure file counter is updated

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) capt_seq_task(  ) {
    // FF877DAC
asm volatile (
      "    STMFD   SP!, {R3-R7,LR} \n"
      "    LDR     R5, =0x39C84 \n"
      "    LDR     R6, =0x2AF0 \n"
"loc_FF877DBC:\n"
      "    MOV     R2, #0 \n"
      "    LDR     R0, [R6, #4] \n"
      "    MOV     R1, SP \n"
      "    BL      sub_FF8397A4 \n"
      "    TST     R0, #1 \n"
      "    BEQ     loc_FF877DE8 \n"
      "    LDR     R1, =0x476 \n"
      "    LDR     R0, =0xFF877950 \n"
      "    BL      sub_FF81EC88 \n"
      "    BL      sub_FF81EC40 \n"
      "    LDMFD   SP!, {R3-R7,PC} \n"
"loc_FF877DE8:\n"
      "    LDR     R0, [SP] \n"
      "    LDR     R1, [R0] \n"
      "    CMP     R1, #0x20 \n"
      "    ADDCC   PC, PC, R1, LSL #2 \n"
      "    B       loc_FF877FEC \n"
      "    B       loc_FF877E7C \n"
      "    B       loc_FF877E84 \n"
      "    B       loc_FF877EB0 \n"
      "    B       loc_FF877EC4 \n"
      "    B       loc_FF877EBC \n"
      "    B       loc_FF877ECC \n"
      "    B       loc_FF877ED4 \n"
      "    B       loc_FF877EE0 \n"
      "    B       loc_FF877EFC \n"
      "    B       loc_FF877EC4 \n"
      "    B       loc_FF877F04 \n"
      "    B       loc_FF877F10 \n"
      "    B       loc_FF877F18 \n"
      "    B       loc_FF877F20 \n"
      "    B       loc_FF877F28 \n"
      "    B       loc_FF877F30 \n"
      "    B       loc_FF877F38 \n"
      "    B       loc_FF877F40 \n"
      "    B       loc_FF877F4C \n"
      "    B       loc_FF877F54 \n"
      "    B       loc_FF877F5C \n"
      "    B       loc_FF877F64 \n"
      "    B       loc_FF877F6C \n"
      "    B       loc_FF877F78 \n"
      "    B       loc_FF877F80 \n"
      "    B       loc_FF877F88 \n"
      "    B       loc_FF877F90 \n"
      "    B       loc_FF877F98 \n"
      "    B       loc_FF877FA0 \n"
      "    B       loc_FF877FA8 \n"
      "    B       loc_FF877FB4 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877E7C:\n"
      "    BL       shooting_expo_iso_override\n"       // +
      "    BL      sub_FF87856C \n"
      "    BL      shooting_expo_param_override\n"      // +
      "    B       loc_FF877ED8 \n"
"loc_FF877E84:\n"
      "    BL      wait_until_remote_button_is_released\n"  // +++ as in a800
      "    BL      capt_seq_hook_set_nr\n"                  // +++ as in a800
      "    LDR     R7, [R0, #0xC] \n"
      "    MOV     R0, R7 \n"
      "    BL      sub_FF969238 \n"
      "    BL      capt_seq_hook_raw_here\n"               // as in a800
      "    MOV     R4, R0 \n"
      "    MOV     R2, R7 \n"
      "    MOV     R1, #1 \n"
      "    BL      sub_FF87611C \n"
      "    TST     R4, #1 \n"
      "    MOVEQ   R0, R7 \n"
      "    BLEQ    sub_FF968D70 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877EB0:\n"
      "    MOV     R0, #1 \n"
      "    BL      sub_FF878800 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877EBC:\n"
      "    BL      sub_FF878208 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877EC4:\n"
      "    BL      sub_FF87854C \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877ECC:\n"
      "    BL      sub_FF878554 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877ED4:\n"
      "    BL      sub_FF878714 \n"
"loc_FF877ED8:\n"
      "    BL      sub_FF875BA8 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877EE0:\n"
      "    LDR     R4, [R0, #0xC] \n"
      "    MOV     R0, R4 \n"
      "    BL      sub_FF9692E0 \n"
      "    MOV     R2, R4 \n"
      "    MOV     R1, #9 \n"
      "    BL      sub_FF87611C \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877EFC:\n"
      "    BL      sub_FF878778 \n"
      "    B       loc_FF877ED8 \n"
"loc_FF877F04:\n"
      "    LDR     R0, [R5, #0x50] \n"
      "    BL      sub_FF878C4C \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F10:\n"
      "    BL      sub_FF878F98 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F18:\n"
      "    BL      sub_FF878FFC \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F20:\n"
      "    BL      sub_FF968178 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F28:\n"
      "    BL      sub_FF968384 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F30:\n"
      "    BL      sub_FF968428 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F38:\n"
      "    BL      sub_FF9684F8 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F40:\n"
      "    MOV     R0, #0 \n"
      "    BL      sub_FF968700 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F4C:\n"
      "    BL      sub_FF968878 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F54:\n"
      "    BL      sub_FF96891C \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F5C:\n"
      "    BL      sub_FF9689FC \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F64:\n"
      "    BL      sub_FF878974 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F6C:\n"
      "    BL      sub_FF8789A0 \n"
      "    BL      sub_FF83780C \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F78:\n"
      "    BL      sub_FF9685BC \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F80:\n"
      "    BL      sub_FF9685FC \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F88:\n"
      "    BL      sub_FF87B25C \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F90:\n"
      "    BL      sub_FF87B2CC \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877F98:\n"
      "    BL      sub_FF968B34 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877FA0:\n"
      "    BL      sub_FF968B98 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877FA8:\n"
      "    BL      sub_FF87B328 \n"
      "    BL      sub_FF87B2E8 \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877FB4:\n"
      "    MOV     R0, #1 \n"
      "    BL      sub_FF969A54 \n"
      "    MOV     R0, #1 \n"
      "    BL      sub_FF969B7C \n"
      "    LDRH    R0, [R5, #0x90] \n"
      "    CMP     R0, #4 \n"
      "    LDRNEH  R0, [R5] \n"
      "    SUBNE   R1, R0, #0x4200 \n"
      "    SUBNES  R1, R1, #0x2A \n"
      "    BNE     loc_FF877FF8 \n"
      "    BL      sub_FF87B2CC \n"
      "    BL      sub_FF87B8CC \n"
      "    BL      sub_FF87B74C \n"
      "    B       loc_FF877FF8 \n"
"loc_FF877FEC:\n"
      "    LDR     R1, =0x5D7 \n"
      "    LDR     R0, =0xFF877950 \n"
      "    BL      sub_FF81EC88 \n"
"loc_FF877FF8:\n"
      "    LDR     R0, [SP] \n"
      "    LDR     R1, [R0, #4] \n"
      "    LDR     R0, [R6] \n"
      "    BL      sub_FF881D64 \n"
      "    LDR     R4, [SP] \n"
      "    LDR     R0, [R4, #8] \n"
      "    CMP     R0, #0 \n"
      "    LDREQ   R0, =0xFF877950 \n"
      "    MOVEQ   R1, #0x118 \n"
      "    BLEQ    sub_FF81EC88 \n"
      "    MOV     R0, #0 \n"
      "    STR     R0, [R4, #8] \n"
      "    B       loc_FF877DBC \n"
    );
}

void __attribute__((naked,noinline)) exp_drv_task(  ) {
    // FF8BB350
asm volatile (
      "    STMFD   SP!, {R4-R9,LR} \n"
      "    SUB     SP, SP, #0x24 \n"
      "    LDR     R6, =0x3E00 \n"
      "    LDR     R7, =0xBB8 \n"
      "    LDR     R4, =0x55174 \n"
      "    MOV     R0, #0 \n"
      "    ADD     R5, SP, #0x14 \n"
      "    STR     R0, [SP, #0x10] \n"
"loc_FF8BB370:\n"
      "    LDR     R0, [R6, #0x20] \n"
      "    MOV     R2, #0 \n"
      "    ADD     R1, SP, #0x20 \n"
      "    BL      sub_FF8397A4 \n"
      "    LDR     R0, [SP, #0x10] \n"
      "    CMP     R0, #1 \n"
      "    BNE     loc_FF8BB3BC \n"
      "    LDR     R0, [SP, #0x20] \n"
      "    LDR     R0, [R0] \n"
      "    CMP     R0, #0x14 \n"
      "    CMPNE   R0, #0x15 \n"
      "    CMPNE   R0, #0x16 \n"
      "    CMPNE   R0, #0x17 \n"
      "    BEQ     loc_FF8BB51C \n"
      "    CMP     R0, #0x29 \n"
      "    BEQ     loc_FF8BB4A4 \n"
      "    ADD     R1, SP, #0x10 \n"
      "    MOV     R0, #0 \n"
      "    BL      sub_FF8BB300 \n"
"loc_FF8BB3BC:\n"
      "    LDR     R0, [SP, #0x20] \n"
      "    LDR     R1, [R0] \n"
      "    CMP     R1, #0x2F \n"
      "    BNE     loc_FF8BB3E8 \n"
      "    BL      sub_FF8BC7FC \n"
      "    LDR     R0, [R6, #0x1C] \n"
      "    MOV     R1, #1 \n"
      "    BL      sub_FF881D64 \n"
      "    BL      sub_FF81EC40 \n"
      "    ADD     SP, SP, #0x24 \n"
      "    LDMFD   SP!, {R4-R9,PC} \n"
"loc_FF8BB3E8:\n"
      "    CMP     R1, #0x2E \n"
      "    BNE     loc_FF8BB404 \n"
      "    LDR     R2, [R0, #0x8C]! \n"
      "    LDR     R1, [R0, #4] \n"
      "    MOV     R0, R1 \n"
      "    BLX     R2 \n"
      "    B       loc_FF8BBA18 \n"
"loc_FF8BB404:\n"
      "    CMP     R1, #0x27 \n"
      "    BNE     loc_FF8BB454 \n"
      "    LDR     R0, [R6, #0x1C] \n"
      "    MOV     R1, #0x80 \n"
      "    BL      sub_FF881D98 \n"
      "    LDR     R0, =0xFF8B6EBC \n"
      "    MOV     R1, #0x80 \n"
      "    BL      sub_FF95F1C8 \n"
      "    LDR     R0, [R6, #0x1C] \n"
      "    MOV     R2, R7 \n"
      "    MOV     R1, #0x80 \n"
      "    BL      sub_FF881CA4 \n"
      "    TST     R0, #1 \n"
      "    LDRNE   R1, =0x1751 \n"
      "    BNE     loc_FF8BB510 \n"
"loc_FF8BB440:\n"
      "    LDR     R1, [SP, #0x20] \n"
      "    LDR     R0, [R1, #0x90] \n"
      "    LDR     R1, [R1, #0x8C] \n"
      "    BLX     R1 \n"
      "    B       loc_FF8BBA18 \n"
"loc_FF8BB454:\n"
      "    CMP     R1, #0x28 \n"
      "    BNE     loc_FF8BB49C \n"
      "    ADD     R1, SP, #0x10 \n"
      "    BL      sub_FF8BB300 \n"
      "    LDR     R0, [R6, #0x1C] \n"
      "    MOV     R1, #0x100 \n"
      "    BL      sub_FF881D98 \n"
      "    LDR     R0, =0xFF8B6ECC \n"
      "    MOV     R1, #0x100 \n"
      "    BL      sub_FF95F458 \n"
      "    LDR     R0, [R6, #0x1C] \n"
      "    MOV     R2, R7 \n"
      "    MOV     R1, #0x100 \n"
      "    BL      sub_FF881CA4 \n"
      "    TST     R0, #1 \n"
      "    BEQ     loc_FF8BB440 \n"
      "    LDR     R1, =0x175B \n"
      "    B       loc_FF8BB510 \n"
"loc_FF8BB49C:\n"
      "    CMP     R1, #0x29 \n"
      "    BNE     loc_FF8BB4B4 \n"
"loc_FF8BB4A4:\n"
      "    LDR     R0, [SP, #0x20] \n"
      "    ADD     R1, SP, #0x10 \n"
      "    BL      sub_FF8BB300 \n"
      "    B       loc_FF8BB440 \n"
"loc_FF8BB4B4:\n"
      "    CMP     R1, #0x2C \n"
      "    BNE     loc_FF8BB4CC \n"
      "    BL      sub_FF8A9138 \n"
      "    BL      sub_FF8A9DA8 \n"
      "    BL      sub_FF8A9920 \n"
      "    B       loc_FF8BB440 \n"
"loc_FF8BB4CC:\n"
      "    CMP     R1, #0x2D \n"
      "    BNE     loc_FF8BB51C \n"
      "    LDR     R0, [R6, #0x1C] \n"
      "    MOV     R1, #4 \n"
      "    BL      sub_FF881D98 \n"
      "    LDR     R1, =0xFF8B6EEC \n"
      "    LDR     R0, =0xFFFFF400 \n"
      "    MOV     R2, #4 \n"
      "    BL      sub_FF8A8BAC \n"
      "    BL      sub_FF8A8E3C \n"
      "    LDR     R0, [R6, #0x1C] \n"
      "    MOV     R2, R7 \n"
      "    MOV     R1, #4 \n"
      "    BL      sub_FF881BC0 \n"
      "    TST     R0, #1 \n"
      "    BEQ     loc_FF8BB440 \n"
      "    LDR     R1, =0x1783 \n"
"loc_FF8BB510:\n"
      "    LDR     R0, =0xFF8B75E0 \n"
      "    BL      sub_FF81EC88 \n"
      "    B       loc_FF8BB440 \n"
"loc_FF8BB51C:\n"
      "    LDR     R0, [SP, #0x20] \n"
      "    MOV     R8, #1 \n"
      "    LDR     R1, [R0] \n"
      "    CMP     R1, #0x12 \n"
      "    CMPNE   R1, #0x13 \n"
      "    BNE     loc_FF8BB5F0 \n"
      "    LDR     R1, [R0, #0x7C] \n"
      "    ADD     R1, R1, R1, LSL #1 \n"
      "    ADD     R1, R0, R1, LSL #2 \n"
      "    SUB     R1, R1, #8 \n"
      "    LDMIA   R1, {R2,R3,R9} \n"
      "    STMIA   R5, {R2,R3,R9} \n"
      "    BL      sub_FF8B9968 \n"
      "    LDR     R0, [SP, #0x20] \n"
      "    LDR     R1, [R0, #0x7C] \n"
      "    LDR     R3, [R0, #0x8C] \n"
      "    LDR     R2, [R0, #0x90] \n"

      "    ADD     R0, R0, #4 \n"
      "    BLX     R3 \n"
      "    LDR     R0, [SP, #0x20] \n"
      "    BL      sub_FF8BCB98 \n"
      "    LDR     R0, [SP, #0x20] \n"
      "    LDR     R1, [R0, #0x7C] \n"
      "    LDR     R2, [R0, #0x98] \n"
      "    LDR     R3, [R0, #0x94] \n"
      "    B       loc_FF8BB904 \n"
"loc_FF8BB5F0:\n"
      "    CMP     R1, #0x14 \n"
      "    CMPNE   R1, #0x15 \n"
      "    CMPNE   R1, #0x16 \n"
      "    CMPNE   R1, #0x17 \n"
      "    BNE     loc_FF8BB6A8 \n"
      "    ADD     R3, SP, #0x10 \n"
      "    ADD     R2, SP, #4 \n"
      "    ADD     R1, SP, #0x14 \n"
      "    BL      sub_FF8B9BD0 \n"
      "    CMP     R0, #1 \n"
      "    MOV     R9, R0 \n"
      "    CMPNE   R9, #5 \n"
      "    BNE     loc_FF8BB644 \n"
      "    LDR     R0, [SP, #0x20] \n"
      "    MOV     R2, R9 \n"
      "    LDR     R1, [R0, #0x7C]! \n"
      "    LDR     R12, [R0, #0x10]! \n"
      "    LDR     R3, [R0, #4] \n"
      "    ADD     R0, SP, #4 \n"
      "    BLX     R12 \n"
      "    B       loc_FF8BB67C \n"
"loc_FF8BB644:\n"
      "    LDR     R0, [SP, #0x20] \n"
      "    CMP     R9, #2 \n"
      "    LDR     R3, [R0, #0x90] \n"
      "    CMPNE   R9, #6 \n"
      "    BNE     loc_FF8BB690 \n"
      "    LDR     R12, [R0, #0x8C] \n"
      "    MOV     R2, R9 \n"
      "    MOV     R1, #1 \n"
      "    ADD     R0, SP, #4 \n"
      "    BLX     R12 \n"
      "    LDR     R0, [SP, #0x20] \n"
      "    ADD     R2, SP, #4 \n"
      "    ADD     R1, SP, #0x14 \n"
      "    BL      sub_FF8BB04C \n"
"loc_FF8BB67C:\n"
      "    LDR     R0, [SP, #0x20] \n"
      "    LDR     R2, [SP, #0x10] \n"
      "    MOV     R1, R9 \n"
      "    BL      sub_FF8BB2A0 \n"
      "    B       loc_FF8BB90C \n"
"loc_FF8BB690:\n"
      "    LDR     R1, [R0, #0x7C] \n"
      "    LDR     R12, [R0, #0x8C] \n"
      "    MOV     R2, R9 \n"
      "    ADD     R0, R0, #4 \n"
      "    BLX     R12 \n"
      "    B       loc_FF8BB90C \n"
"loc_FF8BB6A8:\n"
      "    CMP     R1, #0x23 \n"
      "    CMPNE   R1, #0x24 \n"
      "    BNE     loc_FF8BB6F4 \n"
      "    LDR     R1, [R0, #0x7C] \n"
      "    ADD     R1, R1, R1, LSL #1 \n"
      "    ADD     R1, R0, R1, LSL #2 \n"
      "    SUB     R1, R1, #8 \n"
      "    LDMIA   R1, {R2,R3,R9} \n"
      "    STMIA   R5, {R2,R3,R9} \n"
      "    BL      sub_FF8B89E0 \n"
      "    LDR     R0, [SP, #0x20] \n"
      "    LDR     R1, [R0, #0x7C] \n"
      "    LDR     R3, [R0, #0x8C] \n"
      "    LDR     R2, [R0, #0x90] \n"
      "    ADD     R0, R0, #4 \n"
      "    BLX     R3 \n"
      "    LDR     R0, [SP, #0x20] \n"
      "    BL      sub_FF8B8E1C \n"
      "    B       loc_FF8BB90C \n"
"loc_FF8BB6F4:\n"
      "    ADD     R1, R0, #4 \n"
      "    LDMIA   R1, {R2,R3,R9} \n"
      "    STMIA   R5, {R2,R3,R9} \n"
      "    LDR     R1, [R0] \n"
      "    CMP     R1, #0x27 \n"
      "    ADDCC   PC, PC, R1, LSL #2 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB7AC \n"
      "    B       loc_FF8BB7AC \n"
      "    B       loc_FF8BB7B4 \n"
      "    B       loc_FF8BB7BC \n"
      "    B       loc_FF8BB7BC \n"
      "    B       loc_FF8BB7BC \n"
      "    B       loc_FF8BB7AC \n"
      "    B       loc_FF8BB7B4 \n"
      "    B       loc_FF8BB7BC \n"
      "    B       loc_FF8BB7BC \n"
      "    B       loc_FF8BB7D4 \n"
      "    B       loc_FF8BB7D4 \n"
      "    B       loc_FF8BB8E0 \n"
      "    B       loc_FF8BB8E8 \n"
      "    B       loc_FF8BB8E8 \n"
      "    B       loc_FF8BB8E8 \n"
      "    B       loc_FF8BB8E8 \n"
      "    B       loc_FF8BB8F0 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB7C4 \n"
      "    B       loc_FF8BB7CC \n"
      "    B       loc_FF8BB7CC \n"
      "    B       loc_FF8BB7E0 \n"
      "    B       loc_FF8BB7E0 \n"
      "    B       loc_FF8BB7E8 \n"
      "    B       loc_FF8BB820 \n"
      "    B       loc_FF8BB858 \n"
      "    B       loc_FF8BB890 \n"
      "    B       loc_FF8BB8C8 \n"
      "    B       loc_FF8BB8C8 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB8F4 \n"
      "    B       loc_FF8BB8D0 \n"
      "    B       loc_FF8BB8D8 \n"
"loc_FF8BB7AC:\n"
      "    BL      sub_FF8B7464 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB7B4:\n"
      "    BL      sub_FF8B7704 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB7BC:\n"
      "    BL      sub_FF8B792C \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB7C4:\n"
      "    BL      sub_FF8B7C04 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB7CC:\n"
      "    BL      sub_FF8B7E1C \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB7D4:\n"
      "    BL      sub_FF8B819C_my \n"   //<<<<< patched
      "    MOV     R8, #0 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB7E0:\n"
      "    BL      sub_FF8B82E4 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB7E8:\n"
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
      "    BL      sub_FF8BC890 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB820:\n"
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
      "    BL      sub_FF8BC998 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB858:\n"
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
      "    BL      sub_FF8BCA4C \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB890:\n"
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
      "    BL      sub_FF8BCAF4 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB8C8:\n"
      "    BL      sub_FF8B87D4 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB8D0:\n"
      "    BL      sub_FF8B8F20 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB8D8:\n"
      "    BL      sub_FF8B91C8 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB8E0:\n"
      "    BL      sub_FF8B93A8 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB8E8:\n"
      "    BL      sub_FF8B95F0 \n"
      "    B       loc_FF8BB8F4 \n"
"loc_FF8BB8F0:\n"
      "    BL      sub_FF8B9760 \n"
"loc_FF8BB8F4:\n"
      "    LDR     R0, [SP, #0x20] \n"
      "    LDR     R1, [R0, #0x7C] \n"
      "    LDR     R2, [R0, #0x90] \n"
      "    LDR     R3, [R0, #0x8C] \n"
"loc_FF8BB904:\n"
      "    ADD     R0, R0, #4 \n"
      "    BLX     R3 \n"
"loc_FF8BB90C:\n"
      "    LDR     R1, [SP, #0x20] \n"
      "    LDR     R0, [R1] \n"
      "    CMP     R0, #0x10 \n"
      "    BEQ     loc_FF8BB944 \n"
      "    BGT     loc_FF8BB934 \n"
      "    CMP     R0, #1 \n"
      "    CMPNE   R0, #4 \n"
      "    CMPNE   R0, #0xE \n"
      "    BNE     loc_FF8BB954 \n"
      "    B       loc_FF8BB944 \n"
"loc_FF8BB934:\n"
      "    CMP     R0, #0x13 \n"
      "    CMPNE   R0, #0x17 \n"
      "    CMPNE   R0, #0x1A \n"
      "    BNE     loc_FF8BB954 \n"
"loc_FF8BB944:\n"
      "    LDRH    R0, [R4] \n"
      "    STRH    R0, [SP, #0x14] \n"
      "    LDRH    R0, [R4, #8] \n"
      "    STRH    R0, [SP, #0x1C] \n"
"loc_FF8BB954:\n"
      "    CMP     R8, #1 \n"
      "    BNE     loc_FF8BB9A0 \n"
      "    LDR     R0, [R1, #0x7C] \n"
      "    MOV     R2, #0xC \n"
      "    ADD     R0, R0, R0, LSL #1 \n"
      "    ADD     R0, R1, R0, LSL #2 \n"
      "    SUB     R8, R0, #8 \n"
      "    LDR     R0, =0x55174 \n"
      "    ADD     R1, SP, #0x14 \n"
      "    BL      sub_FFB525C0 \n"     // 1.00b
      "    LDR     R0, =0x55180 \n"
      "    MOV     R2, #0xC \n"
      "    ADD     R1, SP, #0x14 \n"
      "    BL      sub_FFB525C0 \n"     // 1.00b
      "    LDR     R0, =0x5518C \n"
      "    MOV     R2, #0xC \n"
      "    MOV     R1, R8 \n"
      "    BL      sub_FFB525C0 \n"     // 1.00b
      "    B       loc_FF8BBA18 \n"
"loc_FF8BB9A0:\n"
      "    LDR     R0, [R1] \n"
      "    MOV     R3, #1 \n"
      "    CMP     R0, #0xB \n"
      "    BNE     loc_FF8BB9E4 \n"
      "    MOV     R2, #0 \n"
      "    STRD    R2, [SP] \n"
      "    MOV     R2, R3 \n"
      "    MOV     R1, R3 \n"
      "    MOV     R0, #0 \n"
      "    BL      sub_FF8B7244 \n"
      "    MOV     R3, #1 \n"
      "    MOV     R2, #0 \n"
      "    STRD    R2, [SP] \n"
      "    MOV     R2, R3 \n"
      "    MOV     R1, R3 \n"
      "    MOV     R0, #0 \n"
      "    B       loc_FF8BBA14 \n"
"loc_FF8BB9E4:\n"
      "    MOV     R2, #1 \n"
      "    STRD    R2, [SP] \n"
      "    MOV     R3, R2 \n"
      "    MOV     R1, R2 \n"
      "    MOV     R0, R2 \n"
      "    BL      sub_FF8B7244 \n"
      "    MOV     R3, #1 \n"
      "    MOV     R2, R3 \n"
      "    MOV     R1, R3 \n"
      "    MOV     R0, R3 \n"
      "    STR     R3, [SP] \n"
      "    STR     R3, [SP, #4] \n"
"loc_FF8BBA14:\n"
      "    BL      sub_FF8B73B0 \n"
"loc_FF8BBA18:\n"
      "    LDR     R0, [SP, #0x20] \n"
      "    BL      sub_FF8BC7FC \n"
      "    B       loc_FF8BB370 \n"
    );
}

void __attribute__((naked,noinline)) sub_FF8B819C_my(  ) {
   // FF8B819C
asm volatile (
      "    STMFD   SP!, {R4-R8,LR} \n"
      "    LDR     R7, =0x3E00 \n"
      "    MOV     R4, R0 \n"
      "    LDR     R0, [R7, #0x1C] \n"
      "    MOV     R1, #0x3E \n"
      "    BL      sub_FF881D98 \n"
      "    MOV     R2, #0 \n"
      "    LDRSH   R0, [R4, #4] \n"
      "    MOV     R1, R2 \n"
      "    BL      sub_FF8B6F4C \n"
      "    MOV     R5, R0 \n"
      "    LDRSH   R0, [R4, #6] \n"
      "    BL      sub_FF8B709C \n"
      "    LDRSH   R0, [R4, #8] \n"
      "    BL      sub_FF8B70F4 \n"
      "    LDRSH   R0, [R4, #0xA] \n"
      "    BL      sub_FF8B714C \n"
      "    LDRSH   R0, [R4, #0xC] \n"
      "    MOV     R1, #0 \n"
      "    BL      sub_FF8B71A4 \n"
      "    MOV     R6, R0 \n"
      "    LDRSH   R0, [R4, #0xE] \n"
      "    BL      sub_FF8BC82C \n"
      "    LDR     R0, [R4] \n"
      "    LDR     R8, =0x5518C \n"
      "    CMP     R0, #0xB \n"
      "    MOVEQ   R5, #0 \n"
      "    MOVEQ   R6, R5 \n"
      "    BEQ     loc_FF8B8238 \n"
      "    CMP     R5, #1 \n"
      "    BNE     loc_FF8B8238 \n"
      "    LDRSH   R0, [R4, #4] \n"
      "    LDR     R1, =0xFF8B6EAC \n"
      "    MOV     R2, #2 \n"
      "    BL      sub_FF95F31C \n"
      "    STRH    R0, [R4, #4] \n"
      "    MOV     R0, #0 \n"
      "    STR     R0, [R7, #0x28] \n"
      "    B       loc_FF8B8240 \n"
"loc_FF8B8238:\n"
      "    LDRH    R0, [R8] \n"
      "    STRH    R0, [R4, #4] \n"
"loc_FF8B8240:\n"
      "    CMP     R6, #1 \n"
      "    LDRNEH  R0, [R8, #8] \n"
      "    BNE     loc_FF8B825C \n"
      "    LDRSH   R0, [R4, #0xC] \n"
      "    LDR     R1, =0xFF8B6F30 \n"
      "    MOV     R2, #0x20 \n"
      "    BL      sub_FF8BC84C \n"
"loc_FF8B825C:\n"
      "    STRH    R0, [R4, #0xC] \n"
      "    LDRSH   R0, [R4, #6] \n"
      "    BL      sub_FF8A8EA8_my \n"      //<<<<<< patched
      "    B       sub_FF8B8268 \n"         // return to RAM

    );
}

void __attribute__((naked,noinline)) sub_FF8A8EA8_my(  ) {
    // FF8A8EA8
asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n"
      "    LDR     R5, =0x3AC4 \n"
      "    MOV     R4, R0 \n"
      "    LDR     R0, [R5, #4] \n"
      "    CMP     R0, #1 \n"
      "    LDRNE   R1, =0x146 \n"
      "    LDRNE   R0, =0xFF8A8CE0 \n"
      "    BLNE    sub_FF81EC88 \n"
      "    CMN     R4, #0xC00 \n"
      "    LDREQSH R4, [R5, #2] \n"
      "    CMN     R4, #0xC00 \n"
      "    MOVEQ   R1, #0x14C \n"
      "    LDREQ   R0, =0xFF8A8CE0 \n"
      "    STRH    R4, [R5, #2] \n"
      "    BLEQ    sub_FF81EC88 \n"
      "    MOV     R0, R4 \n"
    //"    BL      sub_FFA05DF0 \n"   // deleted
      "    BL      apex2us\n"        // >>>>>>>> patched
      "    B       sub_FF8A8EEC \n"
    );
}
