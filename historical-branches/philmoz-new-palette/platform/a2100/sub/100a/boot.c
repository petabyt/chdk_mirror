/*
 * boot.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_FileWrite();

void taskHook(context_t **context)
{
    task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

    // Replace firmware task addresses with ours
    if(tcb->entry == (void*)task_CaptSeq)           tcb->entry = (void*)capt_seq_task;
    if(tcb->entry == (void*)task_InitFileModules)   tcb->entry = (void*)init_file_modules_task;
    if(tcb->entry == (void*)task_MovieRecord)       tcb->entry = (void*)movie_record_task;
    if(tcb->entry == (void*)task_ExpDrv)            tcb->entry = (void*)exp_drv_task;
    if(tcb->entry == (void*)task_FileWrite)         tcb->entry = (void*)filewritetask;
}

/*----------------------------------------------------------------------
    CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask() {
    _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};

/*----------------------------------------------------------------------
    boot()

    Main entry point for the CHDK code
-----------------------------------------------------------------------*/

/*************************************************************/
//** boot @ 0xFFC0000C - 0xFFC00160, length=86
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
"    MOV     R0, #0x33 \n"
"    MCR     p15, 0, R0, c6, c2 \n"
"    MOV     R0, #0x40000033 \n"
"    MCR     p15, 0, R0, c6, c3 \n"
"    MOV     R0, #0x80000017 \n"
"    MCR     p15, 0, R0, c6, c4 \n"
"    LDR     R0, =0xFFC0002B \n"
"    MCR     p15, 0, R0, c6, c5 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c2, c0 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c2, c0, 1 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c3, c0 \n"
"    LDR     R0, =0x3333330 \n"
"    MCR     p15, 0, R0, c5, c0, 2 \n"
"    LDR     R0, =0x3333330 \n"
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
"    LDR     R0, =0xFFED7374 \n"
"    LDR     R1, =0x1900 \n"
"    LDR     R3, =0xB1F8 \n"

"loc_FFC0013C:\n"
"    CMP     R1, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FFC0013C \n"
"    LDR     R1, =0x12EDB4 \n"
"    MOV     R2, #0 \n"

"loc_FFC00154:\n"
"    CMP     R3, R1 \n"
"    STRCC   R2, [R3], #4 \n"
"    BCC     loc_FFC00154 \n"
"    B       sub_FFC001A0_my \n"  // --> Patched. Old value = 0xFFC001A0.
);
}

/*************************************************************/
//** sub_FFC001A0_my @ 0xFFC001A0 - 0xFFC00208, length=27
void __attribute__((naked,noinline)) sub_FFC001A0_my() {

    //http://chdk.setepontos.com/index.php/topic,4194.0.html
    *(int*)0x1930=(int)taskHook;
    *(int*)0x1934=(int)taskHook;

    // replacement of sub_FFC30448 for correct power-on.
    //(short press = playback mode, long press = record mode)
    *(int*)(0x2230+0x4)= (*(int*)0xC0220118) & 1 ? 0x100000 : 0x200000;

asm volatile (
"    LDR     R0, =0xFFC00218 \n"
"    MOV     R1, #0 \n"
"    LDR     R3, =0xFFC00250 \n"

"loc_FFC001AC:\n"
"    CMP     R0, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FFC001AC \n"
"    LDR     R0, =0xFFC00250 \n"
"    MOV     R1, #0x4B0 \n"
"    LDR     R3, =0xFFC00464 \n"

"loc_FFC001C8:\n"
"    CMP     R0, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FFC001C8 \n"
"    MOV     R0, #0xD2 \n"
"    MSR     CPSR_cxsf, R0 \n"
"    MOV     SP, #0x1000 \n"
"    MOV     R0, #0xD3 \n"
"    MSR     CPSR_cxsf, R0 \n"
"    MOV     SP, #0x1000 \n"
"    LDR     R0, =0x6C4 \n"
"    LDR     R2, =0xEEEEEEEE \n"
"    MOV     R3, #0x1000 \n"

"loc_FFC001FC:\n"
"    CMP     R0, R3 \n"
"    STRCC   R2, [R0], #4 \n"
"    BCC     loc_FFC001FC \n"
"    BL      sub_FFC00FC4_my \n"  // --> Patched. Old value = 0xFFC00FC4.
);
}

/*************************************************************/
//** sub_FFC00FC4_my @ 0xFFC00FC4 - 0xFFC01070, length=44
void __attribute__((naked,noinline)) sub_FFC00FC4_my() {
asm volatile (
"    STR     LR, [SP, #-4]! \n"
"    SUB     SP, SP, #0x74 \n"
"    MOV     R0, SP \n"
"    MOV     R1, #0x74 \n"
"    BL      sub_FFE6D060 \n"
"    MOV     R0, #0x53000 \n"
"    STR     R0, [SP, #4] \n"

#if defined(CHDK_NOT_IN_CANON_HEAP) // use original heap offset if CHDK is loaded in high memory
"    LDR     R0, =0x12EDB4 \n"
#else
"    LDR     R0, =new_sa\n"   // otherwise use patched value
"    LDR     R0, [R0]\n"      //
#endif

"    LDR     R2, =0x2F9C00 \n"
"    LDR     R1, =0x2F24A8 \n"
"    STR     R0, [SP, #8] \n"
"    SUB     R0, R1, R0 \n"
"    ADD     R3, SP, #0xC \n"
"    STR     R2, [SP] \n"
"    STMIA   R3, {R0-R2} \n"
"    MOV     R0, #0x22 \n"
"    STR     R0, [SP, #0x18] \n"
"    MOV     R0, #0x68 \n"
"    STR     R0, [SP, #0x1C] \n"
"    LDR     R0, =0x19B \n"
"    LDR     R1, =uHwSetup_my \n"  // --> Patched. Old value = 0xFFC04D38.
"    STR     R0, [SP, #0x20] \n"
"    MOV     R0, #0x96 \n"
"    STR     R0, [SP, #0x24] \n"
"    MOV     R0, #0x78 \n"
"    STR     R0, [SP, #0x28] \n"
"    MOV     R0, #0x64 \n"
"    STR     R0, [SP, #0x2C] \n"
"    MOV     R0, #0 \n"
"    STR     R0, [SP, #0x30] \n"
"    STR     R0, [SP, #0x34] \n"
"    MOV     R0, #0x10 \n"
"    STR     R0, [SP, #0x5C] \n"
"    MOV     R0, #0x800 \n"
"    STR     R0, [SP, #0x60] \n"
"    MOV     R0, #0xA0 \n"
"    STR     R0, [SP, #0x64] \n"
"    MOV     R0, #0x280 \n"
"    STR     R0, [SP, #0x68] \n"
"    MOV     R0, SP \n"
"    MOV     R2, #0 \n"
"    BL      sub_FFC02D68 \n"
"    ADD     SP, SP, #0x74 \n"
"    LDR     PC, [SP], #4 \n"
);
}

/*************************************************************/
//** uHwSetup_my @ 0xFFC04D38 - 0xFFC04DAC, length=30
void __attribute__((naked,noinline)) uHwSetup_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    BL      sub_FFC00954 \n"
"    BL      sub_FFC090B4 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFFC04E4C \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FFC04974 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFFC04E54 \n"
"    BLLT    _err_init_task \n"
"    LDR     R0, =0xFFC04E64 \n"
"    BL      sub_FFC04A5C \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFFC04E6C \n"
"    BLLT    _err_init_task \n"
"    LDR     R0, =0xFFC04E64 \n"
"    BL      sub_FFC03578 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFFC04E80 \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FFC08BCC \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFFC04E8C \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FFC014A8 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFFC04E98 \n"
"    BLLT    _err_init_task \n"
"    LDMFD   SP!, {R4,LR} \n"
"    B       taskcreate_Startup_my \n"  // --> Patched. Old value = 0xFFC0C260.
);
}

/*************************************************************/
//** taskcreate_Startup_my @ 0xFFC0C260 - 0xFFC0C2D8, length=31
void __attribute__((naked,noinline)) taskcreate_Startup_my() {
asm volatile (
"    STMFD   SP!, {R3,LR} \n"
//"  BL      _sub_FFC3043C \n"  // --> Nullsub call removed.
"    BL      sub_FFC186D8 \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FFC0C29C \n"
"    BL      sub_FFC303F4 \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FFC0C29C \n"
"    BL      sub_FFC10E84 \n"
"    LDR     R1, =0xC0220000 \n"
"    MOV     R0, #0x44 \n"
"    STR     R0, [R1, #0x84] \n"
"    STR     R0, [R1, #0x80] \n"
"    BL      sub_FFC11074 \n"

"loc_FFC0C298:\n"
"    B       loc_FFC0C298 \n"

"loc_FFC0C29C:\n"
//"  BL      _sub_FFC30444 \n"  // Removed for correct power-on
//"  BL      _sub_FFC30440 \n"  // --> Nullsub call removed.
"    BL      sub_FFC16994 \n"
"    LDR     R1, =0x34E000 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FFC16DDC \n"
"    BL      sub_FFC16B88 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R3, =task_Startup_my \n"  // --> Patched. Old value = 0xFFC0C1FC.
"    MOV     R2, #0 \n"
"    MOV     R1, #0x19 \n"
"    LDR     R0, =0xFFC0C2E4 \n"
"    BL      _CreateTask \n"
"    MOV     R0, #0 \n"
"    LDMFD   SP!, {R12,PC} \n"
);
}

/*************************************************************/
//** task_Startup_my @ 0xFFC0C1FC - 0xFFC0C25C, length=25
void __attribute__((naked,noinline)) task_Startup_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    BL      sub_FFC05394 \n"
"    BL      sub_FFC128A0 \n"
"    BL      sub_FFC10B28 \n"
//"  BL      _sub_FFC30C00 \n"  // --> Nullsub call removed.
"    BL      sub_FFC188FC \n"
//"  BL      _sub_FFC187AC \n"  // start diskboot.bin
"    BL      sub_FFC5CD74 \n"
"    BL      sub_FFC0FB94 \n"
"    BL      sub_FFC1892C \n"
"    BL      sub_FFC15F94 \n"
"    BL      sub_FFC18A9C \n"
"    BL      CreateTask_spytask\n"  // added
"    BL      taskcreatePhySw_my \n"  // --> Patched. Old value = 0xFFC116B0.

#if defined(OPT_RUN_WITH_BATT_COVER_OPEN)
"    LDR     R0, =0xE0000\n"    // Pause for startup with battery door open
"batt_delay:\n"
"    NOP\n"
"    SUBS    R0,R0,#1\n"
"    BNE     batt_delay\n"
#endif

"    BL      sub_FFC146C0 \n"
"    BL      sub_FFC18AB4 \n"
//"  BL      _sub_FFC0EFB4 \n"  // --> Nullsub call removed.
"    BL      sub_FFC104B0 \n"
"    BL      sub_FFC184BC \n"
"    BL      sub_FFC10AD8 \n"
"    BL      sub_FFC103D4 \n"
"    BL      sub_FFC0FBC8 \n"
"    BL      sub_FFC194FC \n"
"    BL      sub_FFC103AC \n"
"    LDMFD   SP!, {R4,LR} \n"
"    B       sub_FFC054B4 \n"
);
}

/*************************************************************/
//** taskcreatePhySw_my @ 0xFFC116B0 - 0xFFC116D0, length=9
void __attribute__((naked,noinline)) taskcreatePhySw_my() {
asm volatile (
"    STMFD   SP!, {R3-R5,LR} \n"
"    LDR     R4, =0x1C18 \n"
"    LDR     R0, [R4, #0x10] \n"
"    CMP     R0, #0 \n"
"    BNE     sub_FFC116E4 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R3, =mykbd_task \n"  // --> Patched. Old value = 0xFFC1167C.
"    MOV     R2, #0x2000 \n"  // --> Patched. Old value = 0x800. stack size for new task_PhySw
"    LDR     PC, =0xFFC116D4 \n"  // Continue in firmware
);
}

/*************************************************************/
//** init_file_modules_task @ 0xFFC6036C - 0xFFC603A0, length=14
void __attribute__((naked,noinline)) init_file_modules_task() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    BL      sub_FFC59AF0 \n"
"    LDR     R5, =0x5006 \n"
"    MOVS    R4, R0 \n"
"    MOVNE   R1, #0 \n"
"    MOVNE   R0, R5 \n"
"    BLNE    _PostLogicalEventToUI \n"
"    BL      sub_FFC59B1C_my \n"  // --> Patched. Old value = 0xFFC59B1C.
"    BL      core_spytask_can_start\n"  // CHDK: Set "it's-safe-to-start" flag for spytask
"    CMP     R4, #0 \n"
"    MOVEQ   R0, R5 \n"
"    LDMEQFD SP!, {R4-R6,LR} \n"
"    MOVEQ   R1, #0 \n"
"    BEQ     _PostLogicalEventToUI \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
);
}

/*************************************************************/
//** sub_FFC59B1C_my @ 0xFFC59B1C - 0xFFC59B24, length=3
void __attribute__((naked,noinline)) sub_FFC59B1C_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    MOV     R0, #3 \n"
"    BL      sub_FFC3E874_my \n"  // --> Patched. Old value = 0xFFC3E874.
"    LDR     PC, =0xFFC59B28 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFC3E874_my @ 0xFFC3E874 - 0xFFC3E8C8, length=22
void __attribute__((naked,noinline)) sub_FFC3E874_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R6, R0 \n"
"    BL      sub_FFC3E7DC \n"
"    LDR     R1, =0xE618 \n"
"    MOV     R5, R0 \n"
"    ADD     R4, R1, R0, LSL#7 \n"
"    LDR     R0, [R4, #0x70] \n"
"    CMP     R0, #4 \n"
"    LDREQ   R1, =0x6D8 \n"
"    LDREQ   R0, =0xFFC3E300 \n"
"    BLEQ    _DebugAssert \n"
"    MOV     R1, R6 \n"
"    MOV     R0, R5 \n"
"    BL      sub_FFC3E248 \n"
"    LDR     R0, [R4, #0x38] \n"
"    BL      sub_FFC3EDA0 \n"
"    CMP     R0, #0 \n"
"    STREQ   R0, [R4, #0x70] \n"
"    MOV     R0, R5 \n"
"    BL      sub_FFC3E320 \n"
"    MOV     R0, R5 \n"
"    BL      sub_FFC3E614_my \n"  // --> Patched. Old value = 0xFFC3E614.
"    LDR     PC, =0xFFC3E8CC \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFC3E614_my @ 0xFFC3E614 - 0xFFC3E63C, length=11
void __attribute__((naked,noinline)) sub_FFC3E614_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    MOV     R5, R0 \n"
"    LDR     R0, =0xE618 \n"
"    ADD     R4, R0, R5, LSL#7 \n"
"    LDR     R0, [R4, #0x70] \n"
"    TST     R0, #2 \n"
"    MOVNE   R0, #1 \n"
"    LDMNEFD SP!, {R4-R6,PC} \n"
"    LDR     R0, [R4, #0x38] \n"
"    MOV     R1, R5 \n"
"    BL      sub_FFC3E3A4_my \n"  // --> Patched. Old value = 0xFFC3E3A4.
"    LDR     PC, =0xFFC3E640 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFC3E3A4_my @ 0xFFC3E3A4 - 0xFFC3E50C, length=91
void __attribute__((naked,noinline)) sub_FFC3E3A4_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R8, R0 \n"
"    LDR     R0, =0xE618 \n"
"    MOV     R7, #0 \n"
"    ADD     R5, R0, R1, LSL#7 \n"
"    LDR     R0, [R5, #0x3C] \n"
"    MOV     R6, #0 \n"
"    CMP     R0, #7 \n"
"    ADDLS   PC, PC, R0, LSL#2 \n"
"    B       loc_FFC3E4F4 \n"
"    B       loc_FFC3E404 \n"
"    B       loc_FFC3E3EC \n"
"    B       loc_FFC3E3EC \n"
"    B       loc_FFC3E3EC \n"
"    B       loc_FFC3E3EC \n"
"    B       loc_FFC3E4EC \n"
"    B       loc_FFC3E3EC \n"
"    B       loc_FFC3E3EC \n"

"loc_FFC3E3EC:\n"
"    MOV     R2, #0 \n"
"    MOV     R1, #0x200 \n"
"    MOV     R0, #2 \n"
"    BL      sub_FFC53C30 \n"
"    MOVS    R4, R0 \n"
"    BNE     loc_FFC3E40C \n"

"loc_FFC3E404:\n"
"    MOV     R0, #0 \n"
"    LDMFD   SP!, {R4-R8,PC} \n"

"loc_FFC3E40C:\n"
"    LDR     R12, [R5, #0x4C] \n"
"    MOV     R3, R4 \n"
"    MOV     R2, #1 \n"
"    MOV     R1, #0 \n"
"    MOV     R0, R8 \n"
"    BLX     R12 \n"
"    CMP     R0, #1 \n"
"    BNE     loc_FFC3E438 \n"
"    MOV     R0, #2 \n"
"    BL      sub_FFC53D7C \n"
"    B       loc_FFC3E404 \n"

"loc_FFC3E438:\n"
"    LDR     R1, [R5, #0x68] \n"
"    MOV     R0, R8 \n"
"    BLX     R1 \n"

"    MOV     R1, R4\n"              //  pointer to MBR in R1
"    BL      mbr_read_dryos\n"      //  total sectors count in R0 before and after call

// Start of DataGhost's FAT32 autodetection code
// Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
// According to the code below, we can use R1, R2, R3 and R12.
// LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
// that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
"    MOV     R12, R4\n"             // Copy the MBR start address so we have something to work with
"    MOV     LR, R4\n"              // Save old offset for MBR signature
"    MOV     R1, #1\n"              // Note the current partition number
"    B       dg_sd_fat32_enter\n"   // We actually need to check the first partition as well, no increments yet!
"dg_sd_fat32:\n"
"    CMP     R1, #4\n"              // Did we already see the 4th partition?
"    BEQ     dg_sd_fat32_end\n"     // Yes, break. We didn't find anything, so don't change anything.
"    ADD     R12, R12, #0x10\n"     // Second partition
"    ADD     R1, R1, #1\n"          // Second partition for the loop
"dg_sd_fat32_enter:\n"
"    LDRB    R2, [R12, #0x1BE]\n"   // Partition status
"    LDRB    R3, [R12, #0x1C2]\n"   // Partition type (FAT32 = 0xB)
"    CMP     R3, #0xB\n"            // Is this a FAT32 partition?
"    CMPNE   R3, #0xC\n"            // Not 0xB, is it 0xC (FAT32 LBA) then?
"    CMPNE   R3, #0x7\n"            // exFat?
"    BNE     dg_sd_fat32\n"         // No, it isn't. Loop again.
"    CMP     R2, #0x00\n"           // It is, check the validity of the partition type
"    CMPNE   R2, #0x80\n"
"    BNE     dg_sd_fat32\n"         // Invalid, go to next partition
                                    // This partition is valid, it's the first one, bingo!
"    MOV     R4, R12\n"             // Move the new MBR offset for the partition detection.

"dg_sd_fat32_end:\n"
// End of DataGhost's FAT32 autodetection code

"    LDRB    R1, [R4, #0x1C9] \n"
"    LDRB    R3, [R4, #0x1C8] \n"
"    LDRB    R12, [R4, #0x1CC] \n"
"    MOV     R1, R1, LSL#24 \n"
"    ORR     R1, R1, R3, LSL#16 \n"
"    LDRB    R3, [R4, #0x1C7] \n"
"    LDRB    R2, [R4, #0x1BE] \n"
//"  LDRB    LR, [R4, #0x1FF] \n"  // replaced below
"    ORR     R1, R1, R3, LSL#8 \n"
"    LDRB    R3, [R4, #0x1C6] \n"
"    CMP     R2, #0 \n"
"    CMPNE   R2, #0x80 \n"
"    ORR     R1, R1, R3 \n"
"    LDRB    R3, [R4, #0x1CD] \n"
"    MOV     R3, R3, LSL#24 \n"
"    ORR     R3, R3, R12, LSL#16 \n"
"    LDRB    R12, [R4, #0x1CB] \n"
"    ORR     R3, R3, R12, LSL#8 \n"
"    LDRB    R12, [R4, #0x1CA] \n"
"    ORR     R3, R3, R12 \n"
//"  LDRB    R12, [R4, #0x1FE] \n"  // replaced below
//mod start
"    LDRB    R12, [LR,#0x1FE]\n"    // replace instructions above - First MBR signature byte (0x55), LR is original offset.
"    LDRB    LR, [LR,#0x1FF]\n"     // replace instructions above - Last MBR signature byte (0xAA), LR is original offset.
//mod end
"    MOV     R4, #0 \n"
"    BNE     loc_FFC3E4C4 \n"
"    CMP     R0, R1 \n"
"    BCC     loc_FFC3E4C4 \n"
"    ADD     R2, R1, R3 \n"
"    CMP     R2, R0 \n"
"    CMPLS   R12, #0x55 \n"
"    CMPEQ   LR, #0xAA \n"
"    MOVEQ   R7, R1 \n"
"    MOVEQ   R6, R3 \n"
"    MOVEQ   R4, #1 \n"

"loc_FFC3E4C4:\n"
"    MOV     R0, #2 \n"
"    BL      sub_FFC53D7C \n"
"    CMP     R4, #0 \n"
"    BNE     loc_FFC3E500 \n"
"    LDR     R1, [R5, #0x68] \n"
"    MOV     R7, #0 \n"
"    MOV     R0, R8 \n"
"    BLX     R1 \n"
"    MOV     R6, R0 \n"
"    B       loc_FFC3E500 \n"

"loc_FFC3E4EC:\n"
"    MOV     R6, #0x40 \n"
"    B       loc_FFC3E500 \n"

"loc_FFC3E4F4:\n"
"    LDR     R1, =0x5C9 \n"
"    LDR     R0, =0xFFC3E300 \n"
"    BL      _DebugAssert \n"

"loc_FFC3E500:\n"
"    STR     R7, [R5, #0x44]! \n"
"    MOV     R0, #1 \n"
"    STR     R6, [R5, #4] \n"
"    LDMFD   SP!, {R4-R8,PC} \n"
);
}
