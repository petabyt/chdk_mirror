#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x9B44;  // FF23C248
#define NR_AUTO (0)		    // have to explictly reset value back to 0 to enable auto
#define PAUSE_FOR_FILE_COUNTER 100 // Enable delay in capt_seq_hook_raw_here to ensure file counter is updated

#include "../../../generic/capt_seq.c"

/*----------------------------------------------------------------------
	capt_seq_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) capt_seq_task() {
// FF0769F8
    asm volatile (
        "    STMFD   SP!, {R3-R9,LR} \n" 
        "    LDR     R4, =0x3B3CC \n" 
        "    LDR     R7, =0x2E98 \n" 
        "    MOV     R6, #0 \n" 
        "loc_FF076A08:\n"
        "    LDR     R0, [R7, #4] \n" 
        "    MOV     R2, #0 \n" 
        "    MOV     R1, SP \n" 
        "    BL      sub_FF02B314 \n" 
        "    TST     R0, #1 \n" 
        "    BEQ     loc_FF076A34 \n" 
        "    LDR     R1, =0x491 \n" 
        "    LDR     R0, =0xFF0764B4 \n" // **"SsShootTask.c" 
        //"    BL      sub_FF00EDBC \n" // original 
        "    BL      _DebugAssert \n"
        //"    BL      sub_FF00ED74 \n" // original
        "    BL      _ExitTask \n "
        "    LDMFD   SP!, {R3-R9,PC} \n" 
        "loc_FF076A34:\n"
        "    LDR     R0, [SP] \n" 
        "    LDR     R1, [R0] \n" 
        "    CMP     R1, #0x23 \n" 
        "    ADDCC   PC, PC, R1, LSL #2 \n" 
        "    B       loc_FF076CCC \n" 
        "    B       loc_FF076AD4 \n" 
        "    B       loc_FF076AEC \n" 
        "    B       loc_FF076B68 \n" 
        "    B       loc_FF076B7C \n" 
        "    B       loc_FF076B74 \n" 
        "    B       loc_FF076B88 \n" 
        "    B       loc_FF076B90 \n" 
        "    B       loc_FF076B98 \n" 
        "    B       loc_FF076BB4 \n" 
        "    B       loc_FF076BF4 \n" 
        "    B       loc_FF076BC0 \n" 
        "    B       loc_FF076BCC \n" 
        "    B       loc_FF076BD4 \n" 
        "    B       loc_FF076BDC \n" 
        "    B       loc_FF076BE4 \n" 
        "    B       loc_FF076BEC \n" 
        "    B       loc_FF076BFC \n" 
        "    B       loc_FF076C04 \n" 
        "    B       loc_FF076C0C \n" 
        "    B       loc_FF076C14 \n" 
        "    B       loc_FF076C1C \n" 
        "    B       loc_FF076C28 \n" 
        "    B       loc_FF076C30 \n" 
        "    B       loc_FF076C38 \n" 
        "    B       loc_FF076C40 \n" 
        "    B       loc_FF076C48 \n" 
        "    B       loc_FF076C54 \n" 
        "    B       loc_FF076C5C \n" 
        "    B       loc_FF076C64 \n" 
        "    B       loc_FF076C6C \n" 
        "    B       loc_FF076C74 \n" 
        "    B       loc_FF076C80 \n" 
        "    B       loc_FF076C88 \n" 
        "    B       loc_FF076C94 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076AD4:\n" // jump table entry 0
        "    BL      shooting_expo_iso_override \n" // added
        "    BL      sub_FF0772A4 \n"
        "    BL      shooting_expo_param_override \n" // added
        "    BL      sub_FF07416C \n" 
        //"    LDR     R0, [R4, #0x28] \n" 
        //"    CMP     R0, #0 \n" 
        //"    BLNE    sub_FF18C580 \n" // above 3 lines removed - redundant with added lines below
        "    MOV     R0, #0 \n" // added
        "    STR     R0, [R5,#0x28] \n" //added, fixes overrides behavior at short shutter press (S95)
        "    B       loc_FF076CD8 \n" 
        "loc_FF076AEC:\n" // jump table entry 1
        "    LDR     R5, [R0, #0x10] \n" 
        "    LDR     R0, [R4, #0x28] \n" 
        "    CMP     R0, #0 \n" 
        "    BNE     loc_FF076B40 \n" 
        "    LDRH    R0, [R4] \n" 
        "    SUB     R1, R0, #0x8200 \n" 
        "    SUBS    R1, R1, #0x2F \n" 
        "    SUBNE   R1, R0, #0x8200 \n" 
        "    SUBNES  R1, R1, #0x2E \n" 
        "    BLEQ    sub_FF0790F0 \n" 
        "    BL      sub_FF078D90 \n" 
        "    MOV     R1, R5 \n" 
        "    BL      sub_FF078DE8 \n" 
        "    LDR     R0, =0x10F \n" 
        "    MOV     R2, #4 \n" 
        "    ADD     R1, R5, #0x24 \n" 
        "    BL      sub_FF08A1D4 \n" 
        "    MOV     R2, #4 \n" 
        "    ADD     R1, R5, #0x28 \n" 
        "    MOV     R0, #0x2C \n" 
        "    BL      sub_FF08A1D4 \n" 
        "loc_FF076B40:\n"
        "    MOV     R0, R5 \n" 
        "    BL      sub_FF18C3EC \n" // original
        //"    BL      sub_FF18C3EC_my \n" // patched
        "    BL      capt_seq_hook_raw_here \n" // added
        "    MOV     R8, R0 \n" 
        "    MOV     R2, R5 \n" 
        "    MOV     R1, #1 \n" 
        "    BL      sub_FF074B24 \n" 
        "    TST     R8, #1 \n" 
        "    MOVEQ   R0, R5 \n" 
        "    BLEQ    sub_FF18BD5C \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076B68:\n" // jump table entry 2
        "    MOV     R0, #1 \n" 
        "    BL      sub_FF0775A0 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076B74:\n" // jump table entry 4
        "    BL      sub_FF076EA8 \n" 
        "    B       loc_FF076B80 \n" 
        "loc_FF076B7C:\n" // jump table entry 3
        "    BL      sub_FF077284 \n" 
        "loc_FF076B80:\n"
        "    STR     R6, [R4, #0x28] \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076B88:\n" // jump table entry 5
        "    BL      sub_FF07728C \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076B90:\n" // jump table entry 6
        "    BL      sub_FF077478 \n" 
        "    B       loc_FF076BB8 \n" 
        "loc_FF076B98:\n" // jump table entry 7
        "    LDR     R5, [R0, #0x10] \n" 
        "    MOV     R0, R5 \n" 
        "    BL      sub_FF18C608 \n" 
        "    MOV     R2, R5 \n" 
        "    MOV     R1, #9 \n" 
        "    BL      sub_FF074B24 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BB4:\n"  // jump table entry 8
        "    BL      sub_FF077508 \n" 
        "loc_FF076BB8:\n"
        "    BL      sub_FF07416C \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BC0:\n"  // jump table entry 10
        "    LDR     R0, [R4, #0x58] \n" 
        "    BL      sub_FF077C2C \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BCC:\n"  // jump table entry 11
        "    BL      sub_FF077F10 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BD4:\n"  // jump table entry 12
        "    BL      sub_FF077F74 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BDC:\n"  // jump table entry 13
        "    BL      sub_FF078168 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BE4:\n"  // jump table entry 14
        "    BL      sub_FF0785B8 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BEC:\n"  // jump table entry 15
        "    BL      sub_FF078668 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BF4:\n"  // jump table entry 9
        "    BL      sub_FF077284 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076BFC:\n"  // jump table entry 16
        "    BL      sub_FF18AFD0 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C04:\n"  // jump table entry 17
        "    BL      sub_FF18B23C \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C0C:\n"  // jump table entry 18
        "    BL      sub_FF18B2F8 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C14:\n"  // jump table entry 19
        "    BL      sub_FF18B3CC \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C1C:\n"  // jump table entry 20
        "    MOV     R0, #0 \n" 
        "    BL      sub_FF18B680 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C28:\n"  // jump table entry 21
        "    BL      sub_FF18B7F0 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C30:\n"  // jump table entry 22
        "    BL      sub_FF18B884 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C38:\n"  // jump table entry 23
        "    BL      sub_FF18B940 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C40:\n"  // jump table entry 24
        "    BL      sub_FF077758 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C48:\n"  // jump table entry 25
        "    BL      sub_FF0777EC \n" 
        "    BL      sub_FF028E3C \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C54:\n"  // jump table entry 26
        "    BL      sub_FF18B49C \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C5C:\n"  // jump table entry 27
        "    BL      sub_FF18B504 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C64:\n"  // jump table entry 28
        "    BL      sub_FF07ACBC \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C6C:\n"  // jump table entry 29
        "    BL      sub_FF07AD44 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C74:\n"  // jump table entry 30
        "    LDR     R0, [R0, #0xC] \n" 
        "    BL      sub_FF18BA68 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C80:\n"  // jump table entry 31
        "    BL      sub_FF18BAD8 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C88:\n"  // jump table entry 32
        "    BL      sub_FF07ADAC \n" 
        "    BL      sub_FF07AD64 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076C94:\n"  // jump table entry 33
        "    MOV     R0, #1 \n" 
        "    BL      sub_FF18CD70 \n" 
        "    MOV     R0, #1 \n" 
        "    BL      sub_FF18CEA4 \n" 
        "    LDRH    R0, [R4, #0x98] \n" 
        "    CMP     R0, #4 \n" 
        "    LDRNEH  R0, [R4] \n" 
        "    SUBNE   R1, R0, #0x8200 \n" 
        "    SUBNES  R1, R1, #0x2B \n" 
        "    BNE     loc_FF076CD8 \n" 
        "    BL      sub_FF07AD44 \n" 
        "    BL      sub_FF07B378 \n" 
        "    BL      sub_FF07B1D4 \n" 
        "    B       loc_FF076CD8 \n" 
        "loc_FF076CCC:\n" // jump table default entry
        "    LDR     R1, =0x5F2 \n" 
        "    LDR     R0, =0xFF0764B4 \n"  // *"SsShootTask.c"
        //"    BL      sub_FF00EDBC \n" // original 
        "    BL      _DebugAssert \n"
        "loc_FF076CD8:\n" // jump table entry 34
        "    LDR     R0, [SP] \n" 
        "    LDR     R1, [R0, #4] \n" 
        "    LDR     R0, [R7] \n" 
        "    BL      sub_FF081D00 \n" 
        "    LDR     R5, [SP] \n" 
        "    LDR     R0, [R5, #8] \n" 
        "    CMP     R0, #0 \n" 
        "    LDREQ   R1, =0x117 \n" 
        "    LDREQ   R0, =0xFF0764B4 \n" 
        //"    BLEQ  sub_FF00EDBC \n" // original 
        "    BLEQ    _DebugAssert \n"
        "    STR     R6, [R5, #8] \n" 
        "    B       loc_FF076A08 \n" 
    );
}

/*----------------------------------------------------------------------
	sub_FF18C3EC_my()
-----------------------------------------------------------------------*/
/* void __attribute__((naked,noinline)) sub_FF18C3EC_my() {
// FF18C3EC
    asm volatile (
        "    STMFD   SP!, {R3-R7,LR} \n" 
        "    LDR     R5, =0x3B3CC \n" 
        "    MOV     R4, R0 \n" 
        "    LDR     R0, [R5, #0x28] \n" 
        "    LDR     R6, =0x820D \n" 
        "    CMP     R0, #0 \n" 
        "    MOV     R7, #0 \n" 
        "    BNE     loc_FF18C47C \n" 
        "    LDR     R0, [R5, #0xBC] \n" 
        "    CMP     R0, #0 \n" 
        "    BNE     loc_FF18C42C \n" 
        "    MOV     R0, #0xC \n" 
        "    BL      sub_FF07CA70 \n" 
        "    TST     R0, #1 \n" 
        "    BEQ     loc_FF18C47C \n" 
        "    B       loc_FF18C474 \n" 
        "loc_FF18C42C:\n"
        "    LDRH    R0, [R5] \n" 
        "    CMP     R0, R6 \n" 
        "    LDRNEH  R0, [R5, #0x96] \n" 
        "    CMPNE   R0, #3 \n" 
        "    LDRNE   R0, [R4, #8] \n" 
        "    CMPNE   R0, #1 \n" 
        "    BLS     loc_FF18C45C \n" 
        "    BL      sub_FF022E64 \n" 
        "    TST     R0, #1 \n" 
        "    BEQ     loc_FF18C47C \n" 
        "    BL      sub_FF07CAD8 \n" 
        "    B       loc_FF18C474 \n" 
        "loc_FF18C45C:\n"
        "    MOV     R0, #0xC \n" 
        "    BL      sub_FF07CA70 \n" 
        "    TST     R0, #1 \n" 
        "    BEQ     loc_FF18C47C \n" 
        "    BL      sub_FF18CBE8 \n" 
        "    BL      sub_FF074820 \n" 
        "loc_FF18C474:\n"
        "    MOV     R0, #1 \n" 
        "    LDMFD   SP!, {R3-R7,PC} \n" 
        "loc_FF18C47C:\n"
        "    BL      sub_FF077294 \n" 
        "    LDR     R0, [R5, #0x28] \n" 
        "    CMP     R0, #0 \n" 
        "    BNE     sub_FF18C568 \n" 
        "    MOV     R0, R4 \n" 
        "    BL      sub_FF18BC50 \n" 
        "    TST     R0, #1 \n" 
        "    LDMNEFD SP!, {R3-R7,PC} \n" 
        "    LDR     R0, [R5, #0xBC] \n" 
        "    CMP     R0, #0 \n" 
        "    LDRNEH  R0, [R5] \n" 
        "    CMPNE   R0, R6 \n" 
        "    LDRNEH  R0, [R5, #0x96] \n" 
        "    CMPNE   R0, #3 \n" 
        "    LDRNE   R0, [R4, #8] \n" 
        "    CMPNE   R0, #1 \n" 
        "    BHI     loc_FF18C4D8 \n" 
        "    MOV     R0, R4 \n" 
        "    BL      sub_FF18C020 \n" 
        "    BL      sub_FF18CB2C \n" 
        "    LDR     R0, [R5, #0xBC] \n" 
        "    CMP     R0, #0 \n" 
        "    BEQ     loc_FF18C4F4 \n" 
        "loc_FF18C4D8:\n"
        "    LDRH    R0, [R5] \n" 
        "    CMP     R0, R6 \n" 
        "    LDRNEH  R0, [R5, #0x96] \n" 
        "    CMPNE   R0, #3 \n" 
        "    LDRNE   R0, [R4, #8] \n" 
        "    CMPNE   R0, #1 \n" 
        "    BHI     loc_FF18C4FC \n" 
        "loc_FF18C4F4:\n"
        "    MOV     R0, #2 \n" 
        "    BL      sub_FF07E118 \n" 
        "loc_FF18C4FC:\n"
        "    LDRH    R0, [R5] \n" 
        "    SUB     R1, R0, #0x8200 \n" 
        "    SUBS    R1, R1, #0x2E \n" 
        "    BNE     sub_FF18C558 \n" 
        "    MOV     R5, #1 \n" 
        "    MOV     R2, #2 \n" 
        "    MOV     R1, SP \n" 
        "    ADD     R0, R2, #0x15C \n" 
        "    STR     R5, [SP] \n" 
        "    BL      sub_FF08A35C \n" 
        "    TST     R0, #1 \n" 
        "    MOVNE   R1, #0xC5 \n" 
        "    LDRNE   R0, =0xFF18C6EC \n" 
        "    BLNE    sub_FF00EDBC \n" 
        "    LDRH    R0, [SP] \n" 
        "    CMP     R0, #1 \n" 
        "    BLS     sub_FF18C550 \n" 
        "    MOV     R0, R4 \n" 
        "    STR     R5, [R4, #0xD8] \n" 
        "    BL      sub_FF2EE7DC \n" 
        "    BL      capt_seq_hook_raw_here \n" // added
        "    B       sub_FF18C560 \n" 
    );
}*/

/*----------------------------------------------------------------------
	exp_drv_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) exp_drv_task(){
// FF0C0E24
    asm volatile (
        "    STMFD   SP!, {R4-R9,LR} \n" 
        "    SUB     SP, SP, #0x24 \n" 
        "    LDR     R6, =0x42D0 \n" 
        "    LDR     R7, =0xBB8 \n" 
        "    LDR     R4, =0x58390 \n" 
        "    MOV     R0, #0 \n" 
        "    ADD     R5, SP, #0x14 \n" 
        "    STR     R0, [SP, #0x10] \n" 
        "loc_FF0C0E44:\n"
        "    LDR     R0, [R6, #0x20] \n" 
        "    MOV     R2, #0 \n" 
        "    ADD     R1, SP, #0x20 \n" 
        "    BL      sub_FF02B314 \n" 
        "    LDR     R0, [SP, #0x10] \n" 
        "    CMP     R0, #1 \n" 
        "    BNE     loc_FF0C0E90 \n" 
        "    LDR     R0, [SP, #0x20] \n" 
        "    LDR     R0, [R0] \n" 
        "    CMP     R0, #0x14 \n" 
        "    CMPNE   R0, #0x15 \n" 
        "    CMPNE   R0, #0x16 \n" 
        "    CMPNE   R0, #0x17 \n" 
        "    BEQ     loc_FF0C0FF0 \n" 
        "    CMP     R0, #0x29 \n" 
        "    BEQ     loc_FF0C0F78 \n" 
        "    ADD     R1, SP, #0x10 \n" 
        "    MOV     R0, #0 \n" 
        "    BL      sub_FF0C0DD4 \n" 
        "loc_FF0C0E90:\n"
        "    LDR     R0, [SP, #0x20] \n" 
        "    LDR     R1, [R0] \n" 
        "    CMP     R1, #0x2F \n" 
        "    BNE     loc_FF0C0EBC \n" 
        "    BL      sub_FF0C2254 \n" 
        "    LDR     R0, [R6, #0x1C] \n" 
        "    MOV     R1, #1 \n" 
        "    BL      sub_FF081D00 \n" 
        "    BL      sub_FF00ED74 \n" 
        "    ADD     SP, SP, #0x24 \n" 
        "    LDMFD   SP!, {R4-R9,PC} \n" 
        "loc_FF0C0EBC:\n"
        "    CMP     R1, #0x2E \n" 
        "    BNE     loc_FF0C0ED8 \n" 
        "    LDR     R2, [R0, #0x8C]! \n" 
        "    LDR     R1, [R0, #4] \n" 
        "    MOV     R0, R1 \n" 
        "    BLX     R2 \n" 
        "    B       loc_FF0C1480 \n" 
        "loc_FF0C0ED8:\n"
        "    CMP     R1, #0x27 \n" 
        "    BNE     loc_FF0C0F28 \n" 
        "    LDR     R0, [R6, #0x1C] \n" 
        "    MOV     R1, #0x80 \n" 
        "    BL      sub_FF081D34 \n" 
        "    LDR     R0, =0xFF0BBDD8 \n" 
        "    MOV     R1, #0x80 \n" 
        "    BL      sub_FF17C4A8 \n" 
        "    LDR     R0, [R6, #0x1C] \n" 
        "    MOV     R2, R7 \n" 
        "    MOV     R1, #0x80 \n" 
        "    BL      sub_FF081C40 \n" 
        "    TST     R0, #1 \n" 
        "    LDRNE   R1, =0x151F \n" 
        "    BNE     loc_FF0C0FE4 \n" 
        "loc_FF0C0F14:\n"
        "    LDR     R1, [SP, #0x20] \n" 
        "    LDR     R0, [R1, #0x90] \n" 
        "    LDR     R1, [R1, #0x8C] \n" 
        "    BLX     R1 \n" 
        "    B       loc_FF0C1480 \n" 
        "loc_FF0C0F28:\n"
        "    CMP     R1, #0x28 \n" 
        "    BNE     loc_FF0C0F70 \n" 
        "    ADD     R1, SP, #0x10 \n" 
        "    BL      sub_FF0C0DD4 \n" 
        "    LDR     R0, [R6, #0x1C] \n" 
        "    MOV     R1, #0x100 \n" 
        "    BL      sub_FF081D34 \n" 
        "    LDR     R0, =0xFF0BBDE8 \n" 
        "    MOV     R1, #0x100 \n" 
        "    BL      sub_FF17C860 \n" 
        "    LDR     R0, [R6, #0x1C] \n" 
        "    MOV     R2, R7 \n" 
        "    MOV     R1, #0x100 \n" 
        "    BL      sub_FF081C40 \n" 
        "    TST     R0, #1 \n" 
        "    BEQ     loc_FF0C0F14 \n" 
        "    LDR     R1, =0x1529 \n" 
        "    B       loc_FF0C0FE4 \n" 
        "loc_FF0C0F70:\n"
        "    CMP     R1, #0x29 \n" 
        "    BNE     loc_FF0C0F88 \n" 
        "loc_FF0C0F78:\n"
        "    LDR     R0, [SP, #0x20] \n" 
        "    ADD     R1, SP, #0x10 \n" 
        "    BL      sub_FF0C0DD4 \n" 
        "    B       loc_FF0C0F14 \n" 
        "loc_FF0C0F88:\n"
        "    CMP     R1, #0x2C \n" 
        "    BNE     loc_FF0C0FA0 \n" 
        "    BL      sub_FF0ACB90 \n" 
        "    BL      sub_FF0AD864 \n" 
        "    BL      sub_FF0AD3C8 \n" 
        "    B       loc_FF0C0F14 \n" 
        "loc_FF0C0FA0:\n"
        "    CMP     R1, #0x2D \n" 
        "    BNE     loc_FF0C0FF0 \n" 
        "    LDR     R0, [R6, #0x1C] \n" 
        "    MOV     R1, #4 \n" 
        "    BL      sub_FF081D34 \n" 
        "    LDR     R1, =0xFF0BBE08 \n" 
        "    LDR     R0, =0xFFFFF400 \n" 
        "    MOV     R2, #4 \n" 
        "    BL      sub_FF0AC5E0 \n" 
        "    BL      sub_FF0AC870 \n" 
        "    LDR     R0, [R6, #0x1C] \n" 
        "    MOV     R2, R7 \n" 
        "    MOV     R1, #4 \n" 
        "    BL      sub_FF081B5C \n" 
        "    TST     R0, #1 \n" 
        "    BEQ     loc_FF0C0F14 \n" 
        "    LDR     R1, =0x1551 \n" 
        "loc_FF0C0FE4:\n"
        "    LDR     R0, =0xFF0BC598 \n" // **"ExpDrv.c"
        //"    BL      sub_FF00EDBC \n" // original 
        "    BL      _DebugAssert \n"
        "    B       loc_FF0C0F14 \n" 
        "loc_FF0C0FF0:\n"
        "    LDR     R0, [SP, #0x20] \n" 
        "    MOV     R8, #1 \n" 
        "    LDR     R1, [R0] \n" 
        "    CMP     R1, #0x12 \n" 
        "    CMPNE   R1, #0x13 \n" 
        "    BNE     loc_FF0C1058 \n" 
        "    LDR     R1, [R0, #0x7C] \n" 
        "    ADD     R1, R1, R1, LSL #1 \n" 
        "    ADD     R1, R0, R1, LSL #2 \n" 
        "    SUB     R1, R1, #8 \n" 
        "    LDMIA   R1, {R2,R3,R9} \n" 
        "    STMIA   R5, {R2,R3,R9} \n" 
        "    BL      sub_FF0BEFE8 \n" 
        "    LDR     R0, [SP, #0x20] \n" 
        "    LDR     R1, [R0, #0x7C] \n" 
        "    LDR     R3, [R0, #0x8C] \n" 
        "    LDR     R2, [R0, #0x90] \n" 
        "    ADD     R0, R0, #4 \n" 
        "    BLX     R3 \n" 
        "    LDR     R0, [SP, #0x20] \n" 
        "    BL      sub_FF0C2664 \n" 
        "    LDR     R0, [SP, #0x20] \n" 
        "    LDR     R1, [R0, #0x7C] \n" 
        "    LDR     R2, [R0, #0x98] \n" 
        "    LDR     R3, [R0, #0x94] \n" 
        "    B       loc_FF0C136C \n" 
        "loc_FF0C1058:\n"
        "    CMP     R1, #0x14 \n" 
        "    CMPNE   R1, #0x15 \n" 
        "    CMPNE   R1, #0x16 \n" 
        "    CMPNE   R1, #0x17 \n" 
        "    BNE     loc_FF0C1110 \n" 
        "    ADD     R3, SP, #0x10 \n" 
        "    ADD     R2, SP, #4 \n" 
        "    ADD     R1, SP, #0x14 \n" 
        "    BL      sub_FF0BF250 \n" 
        "    CMP     R0, #1 \n" 
        "    MOV     R9, R0 \n" 
        "    CMPNE   R9, #5 \n" 
        "    BNE     loc_FF0C10AC \n" 
        "    LDR     R0, [SP, #0x20] \n" 
        "    MOV     R2, R9 \n" 
        "    LDR     R1, [R0, #0x7C]! \n" 
        "    LDR     R12, [R0, #0x10]! \n" 
        "    LDR     R3, [R0, #4] \n" 
        "    ADD     R0, SP, #4 \n" 
        "    BLX     R12 \n" 
        "    B       loc_FF0C10E4 \n" 
        "loc_FF0C10AC:\n"
        "    LDR     R0, [SP, #0x20] \n" 
        "    CMP     R9, #2 \n" 
        "    LDR     R3, [R0, #0x90] \n" 
        "    CMPNE   R9, #6 \n" 
        "    BNE     loc_FF0C10F8 \n" 
        "    LDR     R12, [R0, #0x8C] \n" 
        "    MOV     R2, R9 \n" 
        "    MOV     R1, #1 \n" 
        "    ADD     R0, SP, #4 \n" 
        "    BLX     R12 \n" 
        "    LDR     R0, [SP, #0x20] \n" 
        "    ADD     R2, SP, #4 \n" 
        "    ADD     R1, SP, #0x14 \n" 
        "    BL      sub_FF0C0AC4 \n" 
        "loc_FF0C10E4:\n"
        "    LDR     R0, [SP, #0x20] \n" 
        "    LDR     R2, [SP, #0x10] \n" 
        "    MOV     R1, R9 \n" 
        "    BL      sub_FF0C0D74 \n" 
        "    B       loc_FF0C1374 \n" 
        "loc_FF0C10F8:\n"
        "    LDR     R1, [R0, #0x7C] \n" 
        "    LDR     R12, [R0, #0x8C] \n" 
        "    MOV     R2, R9 \n" 
        "    ADD     R0, R0, #4 \n" 
        "    BLX     R12 \n" 
        "    B       loc_FF0C1374 \n" 
        "loc_FF0C1110:\n"
        "    CMP     R1, #0x23 \n" 
        "    CMPNE   R1, #0x24 \n" 
        "    BNE     loc_FF0C115C \n" 
        "    LDR     R1, [R0, #0x7C] \n" 
        "    ADD     R1, R1, R1, LSL #1 \n" 
        "    ADD     R1, R0, R1, LSL #2 \n" 
        "    SUB     R1, R1, #8 \n" 
        "    LDMIA   R1, {R2,R3,R9} \n" 
        "    STMIA   R5, {R2,R3,R9} \n" 
        "    BL      sub_FF0BDD58 \n" 
        "    LDR     R0, [SP, #0x20] \n" 
        "    LDR     R1, [R0, #0x7C] \n" 
        "    LDR     R3, [R0, #0x8C] \n" 
        "    LDR     R2, [R0, #0x90] \n" 
        "    ADD     R0, R0, #4 \n" 
        "    BLX     R3 \n" 
        "    LDR     R0, [SP, #0x20] \n" 
        "    BL      sub_FF0BE22C \n" 
        "    B       loc_FF0C1374 \n" 
        "loc_FF0C115C:\n"
        "    ADD     R1, R0, #4 \n" 
        "    LDMIA   R1, {R2,R3,R9} \n" 
        "    STMIA   R5, {R2,R3,R9} \n" 
        "    LDR     R1, [R0] \n" 
        "    CMP     R1, #0x27 \n" 
        "    ADDCC   PC, PC, R1, LSL #2 \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C1214 \n" 
        "    B       loc_FF0C1214 \n" 
        "    B       loc_FF0C121C \n" 
        "    B       loc_FF0C1224 \n" 
        "    B       loc_FF0C1224 \n" 
        "    B       loc_FF0C1224 \n" 
        "    B       loc_FF0C1214 \n" 
        "    B       loc_FF0C121C \n" 
        "    B       loc_FF0C1224 \n" 
        "    B       loc_FF0C1224 \n" 
        "    B       loc_FF0C123C \n" 
        "    B       loc_FF0C123C \n" 
        "    B       loc_FF0C1348 \n" 
        "    B       loc_FF0C1350 \n" 
        "    B       loc_FF0C1350 \n" 
        "    B       loc_FF0C1350 \n" 
        "    B       loc_FF0C1350 \n" 
        "    B       loc_FF0C1358 \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C122C \n" 
        "    B       loc_FF0C1234 \n" 
        "    B       loc_FF0C1234 \n" 
        "    B       loc_FF0C1248 \n" 
        "    B       loc_FF0C1248 \n" 
        "    B       loc_FF0C1250 \n" 
        "    B       loc_FF0C1288 \n" 
        "    B       loc_FF0C12C0 \n" 
        "    B       loc_FF0C12F8 \n" 
        "    B       loc_FF0C1330 \n" 
        "    B       loc_FF0C1330 \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C135C \n" 
        "    B       loc_FF0C1338 \n" 
        "    B       loc_FF0C1340 \n" 
        "loc_FF0C1214:\n" // jump table entries 0,1,6
        "    BL      sub_FF0BC3CC \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C121C:\n"  // jump table entries 2,7
        "    BL      sub_FF0BC6C4 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1224:\n"  // jump table entries 3-5,8,9
        "    BL      sub_FF0BC92C \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C122C:\n" // jump table entries 24
        "    BL      sub_FF0BCC20 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1234:\n" // jump table entries 25,26
        "    BL      sub_FF0BCE38 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C123C:\n"  // jump table entries 10,11
        //"    BL      sub_FF0BD2F4 \n" // original
        "    BL      sub_FF0BD2F4_my \n" // patched
        "    MOV     R8, #0 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1248:\n" // jump table entries 27,28
        "    BL      sub_FF0BD4CC \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1250:\n" // jump table entries 29
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
        "    BL      sub_FF0C22E8 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1288:\n" // jump table entries 30
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
        "    BL      sub_FF0C2464 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C12C0:\n" // jump table entries 31
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
        "    BL      sub_FF0C2518 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C12F8:\n" // jump table entries 32
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
        "    BL      sub_FF0C25C0 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1330:\n" // jump table entries 33,34
        "    BL      sub_FF0BDB0C \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1338:\n" // jump table entries 37
        "    BL      sub_FF0BE330 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1340:\n" // jump table entries 38
        "    BL      sub_FF0BE890 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1348:\n"  // jump table entries 12
        "    BL      sub_FF0BEAB4 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1350:\n" // jump table entries 13-16
        "    BL      sub_FF0BEC70 \n" 
        "    B       loc_FF0C135C \n" 
        "loc_FF0C1358:\n" // jump table entries 17
        "    BL      sub_FF0BEDE0 \n" 
        "loc_FF0C135C:\n" // jump table default entry
        "    LDR     R0, [SP, #0x20] \n" 
        "    LDR     R1, [R0, #0x7C] \n" 
        "    LDR     R2, [R0, #0x90] \n" 
        "    LDR     R3, [R0, #0x8C] \n" 
        "loc_FF0C136C:\n"
        "    ADD     R0, R0, #4 \n" 
        "    BLX     R3 \n" 
        "loc_FF0C1374:\n"
        "    LDR     R1, [SP, #0x20] \n" 
        "    LDR     R0, [R1] \n" 
        "    CMP     R0, #0x10 \n" 
        "    BEQ     loc_FF0C13AC \n" 
        "    BGT     loc_FF0C139C \n" 
        "    CMP     R0, #1 \n" 
        "    CMPNE   R0, #4 \n" 
        "    CMPNE   R0, #0xE \n" 
        "    BNE     loc_FF0C13BC \n" 
        "    B       loc_FF0C13AC \n" 
        "loc_FF0C139C:\n"
        "    CMP     R0, #0x13 \n" 
        "    CMPNE   R0, #0x17 \n" 
        "    CMPNE   R0, #0x1A \n" 
        "    BNE     loc_FF0C13BC \n" 
        "loc_FF0C13AC:\n"
        "    LDRH    R0, [R4] \n" 
        "    STRH    R0, [SP, #0x14] \n" 
        "    LDRH    R0, [R4, #8] \n" 
        "    STRH    R0, [SP, #0x1C] \n" 
        "loc_FF0C13BC:\n"
        "    CMP     R8, #1 \n" 
        "    BNE     loc_FF0C1408 \n" 
        "    LDR     R0, [R1, #0x7C] \n" 
        "    MOV     R2, #0xC \n" 
        "    ADD     R0, R0, R0, LSL #1 \n" 
        "    ADD     R0, R1, R0, LSL #2 \n" 
        "    SUB     R8, R0, #8 \n" 
        "    LDR     R0, =0x58390 \n" 
        "    ADD     R1, SP, #0x14 \n" 
        "    BL      sub_FF3A2A8C \n" 
        "    LDR     R0, =0x5839C \n" 
        "    MOV     R2, #0xC \n" 
        "    ADD     R1, SP, #0x14 \n" 
        "    BL      sub_FF3A2A8C \n" 
        "    LDR     R0, =0x583A8 \n" 
        "    MOV     R2, #0xC \n" 
        "    MOV     R1, R8 \n" 
        "    BL      sub_FF3A2A8C \n" 
        "    B       loc_FF0C1480 \n" 
        "loc_FF0C1408:\n"
        "    LDR     R0, [R1] \n" 
        "    MOV     R3, #1 \n" 
        "    CMP     R0, #0xB \n" 
        "    BNE     loc_FF0C144C \n" 
        "    MOV     R2, #0 \n" 
        "    STRD    R2, [SP] \n" 
        "    MOV     R2, R3 \n" 
        "    MOV     R1, R3 \n" 
        "    MOV     R0, #0 \n" 
        "    BL      sub_FF0BC1A0 \n" 
        "    MOV     R3, #1 \n" 
        "    MOV     R2, #0 \n" 
        "    STRD    R2, [SP] \n" 
        "    MOV     R2, R3 \n" 
        "    MOV     R1, R3 \n" 
        "    MOV     R0, #0 \n" 
        "    B       loc_FF0C147C \n" 
        "loc_FF0C144C:\n"
        "    MOV     R2, #1 \n" 
        "    STRD    R2, [SP] \n" 
        "    MOV     R3, R2 \n" 
        "    MOV     R1, R2 \n" 
        "    MOV     R0, R2 \n" 
        "    BL      sub_FF0BC1A0 \n" 
        "    MOV     R3, #1 \n" 
        "    MOV     R2, R3 \n" 
        "    MOV     R1, R3 \n" 
        "    MOV     R0, R3 \n" 
        "    STR     R3, [SP] \n" 
        "    STR     R3, [SP, #4] \n" 
        "loc_FF0C147C:\n"
        "    BL      sub_FF0BC318 \n" 
        "loc_FF0C1480:\n"
        "    LDR     R0, [SP, #0x20] \n" 
        "    BL      sub_FF0C2254 \n" 
        "    B       loc_FF0C0E44 \n" 
    );
}

/*----------------------------------------------------------------------
	sub_FF0BD2F4_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF0BD2F4_my() {
// FF0BD2F4
    asm volatile (
        "    STMFD   SP!, {R4-R8,LR} \n" 
        "    LDR     R7, =0x42D0 \n" 
        "    MOV     R4, R0 \n" 
        "    LDR     R0, [R7, #0x1C] \n" 
        "    MOV     R1, #0x3E \n" 
        "    BL      sub_FF081D34 \n" 
        "    MOV     R2, #0 \n" 
        "    LDRSH   R0, [R4, #4] \n" 
        "    MOV     R1, R2 \n" 
        "    BL      sub_FF0BBE68 \n" 
        "    MOV     R5, R0 \n" 
        "    LDRSH   R0, [R4, #6] \n" 
        "    BL      sub_FF0BBFB8 \n" 
        "    LDRSH   R0, [R4, #8] \n" 
        "    BL      sub_FF0BC010 \n" 
        "    LDRSH   R0, [R4, #0xA] \n" 
        "    BL      sub_FF0BC068 \n" 
        "    LDRSH   R0, [R4, #0xC] \n" 
        "    MOV     R1, #0 \n" 
        "    BL      sub_FF0BC0C0 \n" 
        "    MOV     R6, R0 \n" 
        "    LDRSH   R0, [R4, #0xE] \n" 
        "    BL      sub_FF0C2284 \n" 
        "    LDR     R0, [R4] \n" 
        "    LDR     R8, =0x583A8 \n" 
        "    CMP     R0, #0xB \n" 
        "    MOVEQ   R5, #0 \n" 
        "    MOVEQ   R6, R5 \n" 
        "    BEQ     loc_FF0BD390 \n" 
        "    CMP     R5, #1 \n" 
        "    BNE     loc_FF0BD390 \n" 
        "    LDRSH   R0, [R4, #4] \n" 
        "    LDR     R1, =0xFF0BBDC8 \n" 
        "    MOV     R2, #2 \n" 
        "    BL      sub_FF17C5FC \n" 
        "    STRH    R0, [R4, #4] \n" 
        "    MOV     R0, #0 \n" 
        "    STR     R0, [R7, #0x28] \n" 
        "    B       loc_FF0BD398 \n" 
        "loc_FF0BD390:\n"
        "    LDRH    R0, [R8] \n" 
        "    STRH    R0, [R4, #4] \n" 
        "loc_FF0BD398:\n"
        "    CMP     R6, #1 \n" 
        "    LDRNEH  R0, [R8, #8] \n" 
        "    BNE     loc_FF0BD3B4 \n" 
        "    LDRSH   R0, [R4, #0xC] \n" 
        "    LDR     R1, =0xFF0BBE4C \n" 
        "    MOV     R2, #0x20 \n" 
        "    BL      sub_FF0C22A4 \n" 
        "loc_FF0BD3B4:\n"
        "    STRH    R0, [R4, #0xC] \n" 
        "    LDRSH   R0, [R4, #6] \n" 
        //"    BL      sub_FF0AC8DC \n" // original
        "    BL      sub_FF0AC8DC_my \n" // patched
        "    B       sub_FF0BD3C0 \n" // continue in firmware
    );
}

/*----------------------------------------------------------------------
	sub_FF0AC8DC_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF0AC8DC_my() {
// FF0AC8DC
    asm volatile (
        "    STMFD   SP!, {R4-R6,LR} \n" 
        "    LDR     R5, =0x3F6C \n" 
        "    MOV     R4, R0 \n" 
        "    LDR     R0, [R5, #4] \n" 
        "    CMP     R0, #1 \n" 
        "    LDRNE   R1, =0x14D \n" 
        "    LDRNE   R0, =0xFF0AC714 \n" 
        //"    BLNE    sub_FF00EDBC \n" // original
        "    BLNE    _DebugAssert \n"
        "    CMN     R4, #0xC00 \n" 
        "    LDREQSH R4, [R5, #2] \n" 
        "    CMN     R4, #0xC00 \n" 
        "    LDREQ   R1, =0x153 \n" 
        "    LDREQ   R0, =0xFF0AC714 \n" 
        "    STRH    R4, [R5, #2] \n" 
        //"    BLEQ    sub_FF00EDBC \n" // original
        "    BLEQ    _DebugAssert \n"
        "    MOV     R0, R4 \n" 
        //"    BL      sub_FF236100\n" // original
        "    BL      apex2us \n" // patched
        "    B       sub_FF0AC920 \n" // continue in firmware
    );
}
