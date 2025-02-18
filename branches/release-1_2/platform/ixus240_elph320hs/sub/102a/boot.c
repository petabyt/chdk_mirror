/*
 * boot.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
void task_TouchPanel_my(void);

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_TouchPanel();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_FileWrite();

void taskHook(context_t **context)
{
    task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

    // Replace firmware task addresses with ours
    if(tcb->entry == (void*)task_CaptSeq)          tcb->entry = (void*)capt_seq_task;
    if(tcb->entry == (void*)task_InitFileModules)  tcb->entry = (void*)init_file_modules_task;
    if(tcb->entry == (void*)task_TouchPanel)       tcb->entry = (void*)task_TouchPanel_my;
    if(tcb->entry == (void*)task_MovieRecord)      tcb->entry = (void*)movie_record_task;
    if(tcb->entry == (void*)task_ExpDrv)           tcb->entry = (void*)exp_drv_task;
    if(tcb->entry == (void*)task_FileWrite)        tcb->entry = (void*)filewritetask;
}

/*----------------------------------------------------------------------
    CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask() {
    _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

/*----------------------------------------------------------------------
    boot()

    Main entry point for the CHDK code
-----------------------------------------------------------------------*/

/*************************************************************/
//** boot @ 0xFF00000C - 0xFF000184, length=95
void __attribute__((naked,noinline)) boot() {
asm volatile (
"    LDR     R1, =0xC0410000 \n"
"    MOV     R0, #0 \n"
"    STR     R0, [R1] \n"
"    MOV     R1, #0x78 \n"
"    MCR     p15, 0, R1, c1, c0 \n"
"    MOV     R1, #0 \n"
"    MCR     p15, 0, R1, c7, c10, 4 \n"
"    MCR     p15, 0, R1, c7, c5 \n"
"    MCR     p15, 0, R1, c7, c6 \n"
"    MOV     R0, #0x3D \n"
"    MCR     p15, 0, R0, c6, c0 \n"
"    MOV     R0, #0xC000002F \n"
"    MCR     p15, 0, R0, c6, c1 \n"
"    MOV     R0, #0x37 \n"
"    MCR     p15, 0, R0, c6, c2 \n"
"    MOV     R0, #0x40000037 \n"
"    MCR     p15, 0, R0, c6, c3 \n"
"    MOV     R0, #0x80000017 \n"
"    MCR     p15, 0, R0, c6, c4 \n"
"    LDR     R0, =0xFF00002F \n"
"    MCR     p15, 0, R0, c6, c5 \n"
"    LDR     R0, =0xD000002B \n"
"    MCR     p15, 0, R0, c6, c7 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c2, c0 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c2, c0, 1 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c3, c0 \n"
"    LDR     R0, =0x33333330 \n"
"    MCR     p15, 0, R0, c5, c0, 2 \n"
"    LDR     R0, =0x33333330 \n"
"    MCR     p15, 0, R0, c5, c0, 3 \n"
"    MRC     p15, 0, R0, c1, c0 \n"
"    ORR     R0, R0, #0x1000 \n"
"    ORR     R0, R0, #4 \n"
"    ORR     R0, R0, #1 \n"
"    MCR     p15, 0, R0, c1, c0 \n"
"    MOV     R1, #0x80000006 \n"
"    MCR     p15, 0, R1, c9, c1 \n"
"    MOV     R1, #6 \n"
"    MCR     p15, 0, R1, c9, c1, 1 \n"
"    MRC     p15, 0, R1, c1, c0 \n"
"    ORR     R1, R1, #0x50000 \n"
"    MCR     p15, 0, R1, c1, c0 \n"
"    LDR     R2, =0xC0200000 \n"
"    MOV     R1, #1 \n"
"    STR     R1, [R2, #0x10C] \n"
"    MOV     R1, #0xFF \n"
"    STR     R1, [R2, #0xC] \n"
"    STR     R1, [R2, #0x1C] \n"
"    STR     R1, [R2, #0x2C] \n"
"    STR     R1, [R2, #0x3C] \n"
"    STR     R1, [R2, #0x4C] \n"
"    STR     R1, [R2, #0x5C] \n"
"    STR     R1, [R2, #0x6C] \n"
"    STR     R1, [R2, #0x7C] \n"
"    STR     R1, [R2, #0x8C] \n"
"    STR     R1, [R2, #0x9C] \n"
"    STR     R1, [R2, #0xAC] \n"
"    STR     R1, [R2, #0xBC] \n"
"    STR     R1, [R2, #0xCC] \n"
"    STR     R1, [R2, #0xDC] \n"
"    STR     R1, [R2, #0xEC] \n"
"    STR     R1, [R2, #0xFC] \n"
"    LDR     R1, =0xC0400008 \n"
"    LDR     R2, =0x430005 \n"
"    STR     R2, [R1] \n"
"    MOV     R1, #1 \n"
"    LDR     R2, =0xC0243100 \n"
"    STR     R2, [R1] \n"
"    LDR     R2, =0xC0242010 \n"
"    LDR     R1, [R2] \n"
"    ORR     R1, R1, #1 \n"
"    STR     R1, [R2] \n"
"    LDR     R0, =0xFF887998 \n"
"    LDR     R1, =0x685000 \n"
"    LDR     R3, =0x6B309C \n"

"loc_FF000144:\n"
"    CMP     R1, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF000144 \n"
"    LDR     R0, =0xFF86FBDC \n"
"    LDR     R1, =0x1900 \n"
"    LDR     R3, =0x196BC \n"

"loc_FF000160:\n"
"    CMP     R1, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF000160 \n"
"    LDR     R1, =0x281D28 \n"
"    MOV     R2, #0 \n"

"loc_FF000178:\n"
"    CMP     R3, R1 \n"
"    STRCC   R2, [R3], #4 \n"
"    BCC     loc_FF000178 \n"
"    B       sub_FF00038C_my \n"  // --> Patched. Old value = 0xFF00038C.
);
}

/*************************************************************/
//** sub_FF00038C_my @ 0xFF00038C - 0xFF0003F4, length=27
void __attribute__((naked,noinline)) sub_FF00038C_my() {

    //http://chdk.setepontos.com/index.php/topic,4194.0.html
    *(int*)0x1938=(int)taskHook;
    *(int*)0x193C=(int)taskHook;

    // Replacement of sub_FF0257D4 (sub_FF065650) for correct power-on.
    // (short press = playback mode, long press = record mode)
    // look at power-on switch @ 0xFF00D08C
    *(int*)(0x28D4) = (*(int*)0xC022C30C)&1 ? 0x200000 : 0x100000;

asm volatile (
"    LDR     R0, =0xFF000404 \n"
"    MOV     R1, #0 \n"
"    LDR     R3, =0xFF00043C \n"

"loc_FF000398:\n"
"    CMP     R0, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF000398 \n"
"    LDR     R0, =0xFF00043C \n"
"    MOV     R1, #0x4B0 \n"
"    LDR     R3, =0xFF000650 \n"

"loc_FF0003B4:\n"
"    CMP     R0, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF0003B4 \n"
"    MOV     R0, #0xD2 \n"
"    MSR     CPSR_cxsf, R0 \n"
"    MOV     SP, #0x1000 \n"
"    MOV     R0, #0xD3 \n"
"    MSR     CPSR_cxsf, R0 \n"
"    MOV     SP, #0x1000 \n"
"    LDR     R0, =0x6C4 \n"
"    LDR     R2, =0xEEEEEEEE \n"
"    MOV     R3, #0x1000 \n"

"loc_FF0003E8:\n"
"    CMP     R0, R3 \n"
"    STRCC   R2, [R0], #4 \n"
"    BCC     loc_FF0003E8 \n"
"    BL      sub_FF0011E4_my \n"  // --> Patched. Old value = 0xFF0011E4.
);
}

/*************************************************************/
//** sub_FF0011E4_my @ 0xFF0011E4 - 0xFF001284, length=41
void __attribute__((naked,noinline)) sub_FF0011E4_my() {
asm volatile (
"    STR     LR, [SP, #-4]! \n"
"    SUB     SP, SP, #0x74 \n"
"    MOV     R1, #0x74 \n"
"    MOV     R0, SP \n"
"    BL      sub_006AB8C8 \n"
"    MOV     R0, #0x83000 \n"
"    STR     R0, [SP, #4] \n"

#if defined(CHDK_NOT_IN_CANON_HEAP) // use original heap offset if CHDK is loaded in high memory
"    LDR     R0, =0x281D28 \n"
#else
"    LDR     R0, =new_sa\n"   // otherwise use patched value
"    LDR     R0, [R0]\n"      //
#endif

"    LDR     R2, =0x53F15C \n"
"    STR     R0, [SP, #8] \n"
"    SUB     R0, R2, R0 \n"
"    STR     R0, [SP, #0xC] \n"
"    MOV     R0, #0x22 \n"
"    STR     R0, [SP, #0x18] \n"
"    MOV     R0, #0x98 \n"
"    STR     R0, [SP, #0x1C] \n"
"    LDR     R0, =0x1E2 \n"
"    LDR     R1, =0x549C00 \n"
"    STR     R2, [SP, #0x10] \n"
"    STR     R0, [SP, #0x20] \n"
"    MOV     R0, #0xF6 \n"
"    STR     R1, [SP] \n"
"    STR     R1, [SP, #0x14] \n"
"    STR     R0, [SP, #0x24] \n"
"    MOV     R0, #0xB6 \n"
"    STR     R0, [SP, #0x28] \n"
"    MOV     R0, #0x85 \n"
"    STR     R0, [SP, #0x2C] \n"
"    MOV     R0, #0x40 \n"
"    STR     R0, [SP, #0x30] \n"
"    MOV     R0, #4 \n"
"    STR     R0, [SP, #0x34] \n"
"    MOV     R0, #0x10 \n"
"    STR     R0, [SP, #0x5C] \n"
"    MOV     R0, #0x800 \n"
"    STR     R0, [SP, #0x60] \n"
"    MOV     R0, #0xA0 \n"
"    STR     R0, [SP, #0x64] \n"
"    MOV     R0, #0x280 \n"
"    STR     R0, [SP, #0x68] \n"
"    LDR     R1, =sub_FF0042DC_my \n"  // --> Patched. Old value = 0xFF0042DC.
"    LDR     PC, =0xFF001288 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FF0042DC_my @ 0xFF0042DC - 0xFF004380, length=42
void __attribute__((naked,noinline)) sub_FF0042DC_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    BL      sub_FF000B5C \n"
"    BL      sub_FF0054B0 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF00444C \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF003F14 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF004454 \n"
"    BLLT    _err_init_task \n"
"    LDR     R0, =0xFF004464 \n"
"    BL      sub_FF003FFC \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF00446C \n"
"    BLLT    _err_init_task \n"
"    LDR     R0, =0xFF004464 \n"
"    BL      sub_FF002A1C \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF004480 \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF004E4C \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF00448C \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF0079F0 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF004498 \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF007AB0 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF0044A4 \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF006920 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF0044B4 \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF0016DC \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF0044C0 \n"
"    BLLT    _err_init_task \n"
"    LDMFD   SP!, {R4,LR} \n"
"    B       sub_FF00D03C_my \n"  // --> Patched. Old value = 0xFF00D03C.
);
}

/*************************************************************/
//** sub_FF00D03C_my @ 0xFF00D03C - 0xFF00D04C, length=5
void __attribute__((naked,noinline)) sub_FF00D03C_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
//"  BL      _sub_FF065648 \n"  // --> Nullsub call removed.
"    BL      taskcreate_Startup_my \n"  // --> Patched. Old value = 0xFF00D050.
"    MOV     R0, #0 \n"
"    LDMFD   SP!, {R4,PC} \n"
);
}

/*************************************************************/
//** taskcreate_Startup_my @ 0xFF00D050 - 0xFF00D120, length=53
void __attribute__((naked,noinline)) taskcreate_Startup_my() {
asm volatile (
"    STMFD   SP!, {R3-R7,LR} \n"
"    BL      sub_FF03CBF0 \n"
"    MOVS    R6, R0 \n"
"    BNE     loc_FF00D0B4 \n"
"    BL      sub_FF0272C0 /*_IsNormalCameraMode_FW*/ \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FF00D0B4 \n"
"    MOV     R0, #0x38 \n"
"    BL      sub_FF03B1B8 \n"
"    RSBS    R5, R0, #1 \n"
"    MOVCC   R5, #0 \n"
"    MOV     R0, #0x37 \n"
"    BL      sub_FF03B1B8 \n"
"    RSBS    R4, R0, #1 \n"
"    MOVCC   R4, #0 \n"
"    ORRS    R0, R4, R5 \n"
"    BNE     loc_FF00D0D4 \n"
"    BL      sub_FF024BCC \n"
"    BL      sub_0068A7F8 /*_GetSRAndDisableInterrupt*/ \n"
"    LDR     R2, =0xC022C000 \n"
"    LDR     R1, [R2, #0x30C] \n"
"    BIC     R1, R1, #0x300 \n"
"    STR     R1, [R2, #0x30C] \n"
"    BL      sub_0068A7FC /*_SetSR*/ \n"

"loc_FF00D0B0:\n"
"    B       loc_FF00D0B0 \n"

"loc_FF00D0B4:\n"
"    MOV     R0, #0x37 \n"
"    BL      sub_FF03B1B8 \n"
"    RSBS    R4, R0, #1 \n"
"    MOVCC   R4, #0 \n"
"    MOV     R0, #0x38 \n"
"    BL      sub_FF03B1B8 \n"
"    RSBS    R5, R0, #1 \n"
"    MOVCC   R5, #0 \n"

"loc_FF00D0D4:\n"
"    MOV     R3, #0 \n"
"    MOV     R2, R6 \n"
"    MOV     R1, R5 \n"
"    MOV     R0, R4 \n"
//"  BL      _sub_FF065650 \n"  // See begin of sub_FF00038C_my
//"  BL      _sub_FF06564C \n"  // --> Nullsub call removed.
"    BL      sub_0068F4A0 \n"
"    LDR     R1, =0x5CE000 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF03AFA4 \n"
"    BL      sub_0068F6B8 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R3, =task_Startup_my \n"  // --> Patched. Old value = 0xFF00CFD4.
"    MOV     R2, #0 \n"
"    MOV     R1, #0x19 \n"
"    LDR     R0, =0xFF00D130 \n"
"    BL      _CreateTask \n"
"    MOV     R0, #0 \n"
"    LDMFD   SP!, {R3-R7,PC} \n"
);
}

/*************************************************************/
//** task_Startup_my @ 0xFF00CFD4 - 0xFF00D02C, length=23
void __attribute__((naked,noinline)) task_Startup_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    BL      sub_FF0049CC \n"
"    BL      sub_FF02698C \n"
"    BL      sub_FF024A40 \n"
//"  BL      _sub_FF065E60 \n"  // --> Nullsub call removed.
"    BL      sub_FF03CE24 \n"
//"  BL      _sub_FF03CCCC \n"  // start diskboot.bin
"    BL      sub_FF03CF9C \n"
"    BL      sub_FF03D168 \n"
//"  BL      _sub_FF03CF90 \n"  // --> Nullsub call removed.
"    BL      sub_FF03CE54 \n"
"    BL      sub_FF03AED8 \n"
"    BL      sub_FF03D170 \n"

"    BL      CreateTask_spytask\n"  // added

"    BL      taskcreatePhySw_my \n"  // --> Patched. Old value = 0xFF025678.
"    LDR     PC, =0xFF00D00C \n"  // Continue in firmware
);
}

/*************************************************************/
//** taskcreatePhySw_my @ 0xFF025678 - 0xFF025698, length=9
void __attribute__((naked,noinline)) taskcreatePhySw_my() {
asm volatile (
"    STMFD   SP!, {R3-R5,LR} \n"
"    LDR     R4, =0x1D34 \n"
"    LDR     R0, [R4, #4] \n"
"    CMP     R0, #0 \n"
"    BNE     sub_FF0256AC \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R3, =mykbd_task \n"  // --> Patched. Old value = 0xFF025644.
"    MOV     R2, #0x2000 \n"  // --> Patched. Old value = 0x800. stack size for new task_PhySw
"    LDR     PC, =0xFF02569C \n"  // Continue in firmware
);
}

/*************************************************************/
//** init_file_modules_task @ 0xFF0BF930 - 0xFF0BF94C, length=8
void __attribute__((naked,noinline)) init_file_modules_task() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    BL      sub_FF0B6F74 \n"
"    LDR     R5, =0x5006 \n"
"    MOVS    R4, R0 \n"
"    MOVNE   R1, #0 \n"
"    MOVNE   R0, R5 \n"
"    BLNE    _PostLogicalEventToUI \n"
"    BL      sub_FF0B6FA0 \n"
"    BL      core_spytask_can_start\n"  // CHDK: Set "it's-safe-to-start" flag for spytask
"    LDR     PC, =0xFF0BF950 \n"  // Continue in firmware
);
}

/*************************************************************/
//** task_TouchPanel_my @ 0xFF069FF8 - 0xFF06A178, length=97
void __attribute__((naked,noinline)) task_TouchPanel_my() {
asm volatile (
"    STMFD   SP!, {R3-R7,LR} \n"
"    MOV     R0, #0 \n"
"    LDR     R1, =0xC0221000 \n"
"    MOV     R4, R0 \n"
"    STR     R0, [SP] \n"
"    MOV     R0, #4 \n"
"    STR     R0, [R1, #0x314] \n"
"    MOV     R0, #0x1C \n"
"    SUB     R1, R1, #0x1E000 \n"
"    STR     R0, [R1, #0x40] \n"
"    MOV     R3, #0 \n"
"    LDR     R2, =0xFF069CF8 \n"
"    MOV     R1, #0x55 \n"
"    MOV     R0, R3 \n"
"    BL      sub_0068A7BC /*_RegisterInterruptHandler*/ \n"
"    BL      sub_FF06A440 \n"
"    LDR     R5, =0x2B60 \n"
"    MOV     R1, #0x10 \n"
"    LDR     R0, [R5, #0x30] \n"
"    BL      sub_0068ED10 /*_ClearEventFlag*/ \n"
"    MOV     R6, #7 \n"

"loc_FF06A04C:\n"
"    LDR     R0, [R5, #0x30] \n"
"    MOV     R2, #0 \n"
"    MOV     R1, #0x17 \n"
"    BL      sub_0068EB38 /*_WaitForAnyEventFlag*/ \n"
"    CMP     R0, #0 \n"
"    LDRNE   R1, =0x2B3 \n"
"    LDRNE   R0, =0xFF069CD0 \n"
"    BLNE    _DebugAssert \n"
"    LDR     R0, [R5, #0x30] \n"
"    MOV     R1, SP \n"
"    BL      sub_0068ED48 /*_GetEventFlagValue*/ \n"
"    CMP     R0, #0 \n"
"    MOVNE   R1, #0x2B4 \n"
"    LDRNE   R0, =0xFF069CD0 \n"
"    BLNE    _DebugAssert \n"
"    LDR     R0, [SP] \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF06A0CC \n"
"    LDR     R0, [R5, #0x10] \n"
"    CMP     R0, #7 \n"
"    BEQ     loc_FF06A0A8 \n"
"    BL      sub_FF0B1DA4 /*_CancelHPTimer*/ \n"
"    STR     R6, [R5, #0x10] \n"

"loc_FF06A0A8:\n"
"    LDR     R0, [R5, #0x30] \n"
"    MOV     R1, #5 \n"
"    BL      sub_0068ED10 /*_ClearEventFlag*/ \n"
"    BL      sub_FF069D08 \n"
"    MOV     R4, #0 \n"
"    BL      sub_FF06A440 \n"
"    LDR     R0, [R5, #0x30] \n"
"    MOV     R1, #0x80000000 \n"
"    BL      sub_0068ECDC /*_SetEventFlag*/ \n"

"loc_FF06A0CC:\n"
"    LDR     R0, [SP] \n"
"    TST     R0, #2 \n"
"    BEQ     loc_FF06A0FC \n"
"    LDR     R0, [R5, #0x30] \n"
"    MOV     R1, #2 \n"
"    BL      sub_0068ED10 /*_ClearEventFlag*/ \n"
"    CMP     R4, #0 \n"
"    BNE     loc_FF06A04C \n"
"    LDR     R0, =0xBB8 \n"
"    BL      sub_FF069A64 \n"
"    MOV     R4, #1 \n"
"    BL      sub_FF06A42C \n"

"loc_FF06A0FC:\n"
"    LDR     R0, [SP] \n"
"    TST     R0, #0x10 \n"
"    BEQ     loc_FF06A144 \n"
"    LDR     R0, [R5, #0x10] \n"
"    CMP     R0, #7 \n"
"    BEQ     loc_FF06A11C \n"
"    BL      sub_FF0B1DA4 /*_CancelHPTimer*/ \n"
"    STR     R6, [R5, #0x10] \n"

"loc_FF06A11C:\n"
"    BL      sub_FF06A440 \n"
"    LDR     R0, [R5, #0x30] \n"
"    MOV     R1, #0x14 \n"
"    BL      sub_0068ED10 /*_ClearEventFlag*/ \n"
"    CMP     R4, #0 \n"
"    BEQ     loc_FF06A04C \n"
"    BL      sub_FF069F28_my \n"  // --> Patched. Old value = 0xFF069F28.
"    LDR     R0, [R5, #0x18] \n"
"    CMP     R0, #0 \n"
"    BLNE    sub_FF06A408 \n"

"loc_FF06A144:\n"
"    LDR     R0, [SP] \n"
"    TST     R0, #4 \n"
"    BEQ     loc_FF06A04C \n"
"    STR     R6, [R5, #0x10] \n"
"    LDR     R0, [R5, #0x30] \n"
"    MOV     R1, #4 \n"
"    BL      sub_0068ED10 /*_ClearEventFlag*/ \n"
"    CMP     R4, #0 \n"
"    BEQ     loc_FF06A04C \n"
"    BL      sub_FF069F28_my \n"  // --> Patched. Old value = 0xFF069F28.
"    LDR     R0, [R5, #0x18] \n"
"    CMP     R0, #0 \n"
"    BLNE    sub_FF06A408 \n"
"    B       loc_FF06A04C \n"
);
}

/*************************************************************/
//** sub_FF069F28_my @ 0xFF069F28 - 0xFF069FD4, length=44
void __attribute__((naked,noinline)) sub_FF069F28_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R4, =0x2B60 \n"
"    LDR     R0, [R4, #0x18] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FF069F60 \n"
"    CMP     R0, #1 \n"
"    BEQ     loc_FF069F80 \n"
"    CMP     R0, #2 \n"
"    LDMEQFD SP!, {R4-R6,LR} \n"
"    BEQ     sub_FF069E08_my \n"  // --> Patched. Old value = 0xFF069E08.
"    LDMNEFD SP!, {R4-R6,LR} \n"
"    LDRNE   R1, =0x29E \n"
"    LDRNE   R0, =0xFF069CD0 \n"
"    BNE     _DebugAssert \n"

"loc_FF069F60:\n"
"    MOV     R0, #4 \n"
"    BL      sub_FF03B1B8 \n"
"    CMP     R0, #0 \n"
"    LDMNEFD SP!, {R4-R6,LR} \n"
"    BNE     sub_FF06A42C \n"
"    MOV     R0, #1 \n"
"    STR     R0, [R4, #0x18] \n"
"    LDMFD   SP!, {R4-R6,PC} \n"

"loc_FF069F80:\n"
"    MOV     R0, #4 \n"
"    BL      sub_FF03B1B8 \n"
"    CMP     R0, #0 \n"
"    LDMNEFD SP!, {R4-R6,LR} \n"
"    BNE     sub_FF069D08 \n"
"    LDR     R1, =0x2B9C \n"
"    MOV     R2, #2 \n"
"    MOV     R0, #8 \n"
"    BL      sub_FF069B0C \n"
"    LDR     R5, =0x2B9C \n"
"    MOV     R2, #2 \n"
"    ADD     R1, R5, #4 \n"
"    MOV     R0, #0xA \n"
"    BL      sub_FF069B0C \n"
"    BL      process_TouchCoords_my \n"  // --> Patched. Old value = 0xFF069D58.
"    MOV     R0, #3 \n"
"    STR     R0, [R4, #0x1C] \n"
"    MOV     R0, #2 \n"
"    STR     R0, [R4, #0x18] \n"
"    MVN     R0, #0x8000 \n"
"    STRH    R0, [R5] \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
);
}

/*************************************************************/
//** sub_FF069E08_my @ 0xFF069E08 - 0xFF069F24, length=72
void __attribute__((naked,noinline)) sub_FF069E08_my() {
asm volatile (
"    STMFD   SP!, {R3-R7,LR} \n"
"    MOV     R0, #4 \n"
"    BL      sub_FF03B1B8 \n"
"    LDR     R6, =0x2B60 \n"
"    CMP     R0, #0 \n"
"    LDR     R7, =0x1388 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    BEQ     loc_FF069E3C \n"
"    SUBS    R0, R0, #1 \n"
"    STR     R0, [R6, #0x1C] \n"
"    LDMEQFD SP!, {R3-R7,LR} \n"
"    BEQ     sub_FF069D08 \n"
"    B       loc_FF069E64 \n"

"loc_FF069E3C:\n"
"    SUB     R1, R0, #1 \n"
"    LDR     R4, =0x2B9C \n"
"    LDR     R5, =0x7FFF \n"
"    MOV     R0, #3 \n"
"    CMP     R1, #2 \n"
"    STR     R0, [R6, #0x1C] \n"
"    BCS     loc_FF069E70 \n"
"    LDRH    R0, [R4] \n"
"    CMP     R0, R5 \n"
"    BNE     loc_FF069F1C \n"

"loc_FF069E64:\n"
"    MOV     R0, R7 \n"
"    LDMFD   SP!, {R3-R7,LR} \n"
"    B       sub_FF069A64 \n"

"loc_FF069E70:\n"
"    LDR     R1, =0x2B9C \n"
"    MOV     R2, #2 \n"
"    MOV     R0, #8 \n"
"    BL      sub_FF069B0C \n"
"    MOV     R2, #2 \n"
"    ADD     R1, R4, #4 \n"
"    MOV     R0, #0xA \n"
"    BL      sub_FF069B0C \n"
"    MOV     R0, R7 \n"
"    BL      sub_FF069A64 \n"
"    MOV     R0, #4 \n"
"    BL      sub_FF03B1B8 \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FF069F1C \n"
"    LDRH    R1, [R4] \n"
"    LDRSH   R3, [R6, #6] \n"
"    LDRH    R2, [R4, #2] \n"
"    SUB     R0, R3, R1 \n"
"    MUL     R7, R0, R0 \n"
"    LDRSH   R0, [R6, #8] \n"
"    CMP     R3, R5 \n"
"    SUB     R12, R0, R2 \n"
"    MUL     R0, R12, R12 \n"
"    BEQ     loc_FF069EEC \n"
"    SUB     R3, R7, #0x19000 \n"
"    CMP     R3, #0xE7000 \n"
"    BHI     loc_FF069EEC \n"
"    CMP     R0, #0x19000 \n"
"    BCC     loc_FF069EEC \n"
"    CMP     R0, #0x100000 \n"
"    BLS     loc_FF069F1C \n"

"loc_FF069EEC:\n"
"    LDR     R0, =0x3FF \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R12, [R6, #0x24] \n"
"    EOR     R2, R0, R2, LSR#2 \n"
"    EOR     R1, R0, R1, LSR#2 \n"
"    MOV     R0, R3 \n"
"    BLX     R12 \n"
"    LDR     R0, [R6, #0x1C] \n"
"    SUB     R0, R0, #1 \n"
"    STR     R0, [R6, #0x1C] \n"
"    LDMFD   SP!, {R3-R7,PC} \n"

"loc_FF069F1C:\n"
"    BL      process_TouchCoords_my \n"  // --> Patched. Old value = 0xFF069D58.
"    STRH    R5, [R4] \n"
"    LDMFD   SP!, {R3-R7,PC} \n"
);
}

/*************************************************************/
//** process_TouchCoords_my @ 0xFF069D58 - 0xFF069D58, length=1
void __attribute__((naked,noinline)) process_TouchCoords_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    BL      chdk_process_touch \n"
"    LDMFD   SP!, {R4,R5,LR} \n"
"    CMP     R0, #0 \n"
"    BXNE    LR \n"
"    LDR     PC, =0xFF069D58 \n"  // Continue in firmware
);
}
