#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"
#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

void CreateTask_PhySw();
void CreateTask_spytask();

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_PhySw();
extern void task_FileWrite();

void taskHook(context_t **context) {

    task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

    if(tcb->entry == (void*)task_PhySw)            tcb->entry = (void*)mykbd_task;
    if(tcb->entry == (void*)task_CaptSeq)          tcb->entry = (void*)capt_seq_task; 
    if(tcb->entry == (void*)task_InitFileModules)  tcb->entry = (void*)init_file_modules_task;
    if(tcb->entry == (void*)task_MovieRecord)      tcb->entry = (void*)movie_record_task;
    if(tcb->entry == (void*)task_ExpDrv)           tcb->entry = (void*)exp_drv_task;
    if(tcb->entry == (void*)task_FileWrite)        tcb->entry = (void*)filewritetask;
}

//#define LED_GREEN 		0xC0220120

//** boot  @ 0xFF81000C 

void __attribute__((naked,noinline)) boot() {
asm volatile (
      "LDR     R1, =0xC0410000 \n"
      "MOV     R0, #0 \n"
      "STR     R0, [R1] \n"
      "MOV     R1, #0x78 \n"
      "MCR     p15, 0, R1, c1, c0 \n"
      "MOV     R1, #0 \n"
      "MCR     p15, 0, R1, c7, c10, 4 \n"
      "MCR     p15, 0, R1, c7, c5 \n"
      "MCR     p15, 0, R1, c7, c6 \n"
      "MOV     R0, #0x3D \n"
      "MCR     p15, 0, R0, c6, c0 \n"
      "MOV     R0, #0xC000002F \n"
      "MCR     p15, 0, R0, c6, c1 \n"
      "MOV     R0, #0x33 \n"
      "MCR     p15, 0, R0, c6, c2 \n"
      "MOV     R0, #0x40000033 \n"
      "MCR     p15, 0, R0, c6, c3 \n"
      "MOV     R0, #0x80000017 \n"
      "MCR     p15, 0, R0, c6, c4 \n"
      "LDR     R0, =0xFF80002D \n"
      "MCR     p15, 0, R0, c6, c5 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c2, c0 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c2, c0, 1 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c3, c0 \n"
      "LDR     R0, =0x3333330 \n"
      "MCR     p15, 0, R0, c5, c0, 2 \n"
      "LDR     R0, =0x3333330 \n"
      "MCR     p15, 0, R0, c5, c0, 3 \n"
      "MRC     p15, 0, R0, c1, c0 \n"
      "ORR     R0, R0, #0x1000 \n"
      "ORR     R0, R0, #4 \n"
      "ORR     R0, R0, #1 \n"
      "MCR     p15, 0, R0, c1, c0 \n"
      "MOV     R1, #0x80000006 \n"
      "MCR     p15, 0, R1, c9, c1 \n"
      "MOV     R1, #6 \n"
      "MCR     p15, 0, R1, c9, c1, 1 \n"
      "MRC     p15, 0, R1, c1, c0 \n"
      "ORR     R1, R1, #0x50000 \n"
      "MCR     p15, 0, R1, c1, c0 \n"
      "LDR     R2, =0xC0200000 \n"
      "MOV     R1, #1 \n"
      "STR     R1, [R2, #0x10C] \n"
      "MOV     R1, #0xFF \n"
      "STR     R1, [R2, #0xC] \n"
      "STR     R1, [R2, #0x1C] \n"
      "STR     R1, [R2, #0x2C] \n"
      "STR     R1, [R2, #0x3C] \n"
      "STR     R1, [R2, #0x4C] \n"
      "STR     R1, [R2, #0x5C] \n"
      "STR     R1, [R2, #0x6C] \n"
      "STR     R1, [R2, #0x7C] \n"
      "STR     R1, [R2, #0x8C] \n"
      "STR     R1, [R2, #0x9C] \n"
      "STR     R1, [R2, #0xAC] \n"
      "STR     R1, [R2, #0xBC] \n"
      "STR     R1, [R2, #0xCC] \n"
      "STR     R1, [R2, #0xDC] \n"
      "STR     R1, [R2, #0xEC] \n"
      "STR     R1, [R2, #0xFC] \n"
      "LDR     R1, =0xC0400008 \n"
      "LDR     R2, =0x430005 \n"
      "STR     R2, [R1] \n"
      "MOV     R1, #1 \n"
      "LDR     R2, =0xC0243100 \n"
      "STR     R2, [R1] \n"
      "LDR     R2, =0xC0242010 \n"
      "LDR     R1, [R2] \n"
      "ORR     R1, R1, #1 \n"
      "STR     R1, [R2] \n"
      "LDR     R0, =0xFFC04D54 \n"
      "LDR     R1, =0x3F1000 \n"
      "LDR     R3, =0x4005D4 \n"
"loc_FF81013C:\n"
      "CMP     R1, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FF81013C \n"
      "LDR     R0, =0xFFBF93D8 \n"
      "LDR     R1, =0x1900 \n"
      "LDR     R3, =0xD27C \n"
"loc_FF810158:\n"
      "CMP     R1, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FF810158 \n"
      "LDR     R1, =0x157C84 \n" //MEMISOSTART
      "MOV     R2, #0 \n"
"loc_FF810170:\n"
      "CMP     R3, R1 \n"
      "STRCC   R2, [R3], #4 \n"
      "BCC     loc_FF810170 \n"
//      "B       sub_FF810380 \n" //original
      "B       sub_FF810380_my \n" //patched
	);
}


//** sub_FF810380_my  @ 0xFF810380 

void __attribute__((naked,noinline)) sub_FF810380_my() {

   //http://chdk.setepontos.com/index.php/topic,4194.0.html
   *(int*)0x1934=(int)taskHook;
   *(int*)0x1938=(int)taskHook;

    // Power Button detection (short press = playback mode, long press = record mode) 
	// C0220048  a4000.100c ??
    // C02200F8  a4000.100c sub_ff81a6ac : C0220000 (@ff81a6b4) + 0xF8 (@ff81a6fc)
    // 0x24B0    a4000.100c loc_ff856420
    if ((*(int*) 0xC0220048) & 1)                 // look at power-on switch
            *(int*)(0x24B0+4) = 0x200000;         // start in play mode
    else
            *(int*)(0x24B0+4) = 0x100000;         // start in rec mode    
    
asm volatile (
      "LDR     R0, =0xFF8103F8 \n"
      "MOV     R1, #0 \n"
      "LDR     R3, =0xFF810430 \n"
"loc_FF81038C:\n"
      "CMP     R0, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FF81038C \n"
      "LDR     R0, =0xFF810430 \n"
      "MOV     R1, #0x4B0 \n"
      "LDR     R3, =0xFF810644 \n"
"loc_FF8103A8:\n"
      "CMP     R0, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FF8103A8 \n"
      "MOV     R0, #0xD2 \n"
      "MSR     CPSR_cxsf, R0 \n"
      "MOV     SP, #0x1000 \n"
      "MOV     R0, #0xD3 \n"
      "MSR     CPSR_cxsf, R0 \n"
      "MOV     SP, #0x1000 \n"
      "LDR     R0, =0x6C4 \n"
      "LDR     R2, =0xEEEEEEEE \n"
      "MOV     R3, #0x1000 \n"
"loc_FF8103DC:\n"
      "CMP     R0, R3 \n"
      "STRCC   R2, [R0], #4 \n"
      "BCC     loc_FF8103DC \n"
//      "BL      sub_FF8111D8 \n" //original
      "BL      sub_FF8111D8_my \n" //patched
	);
}


//** sub_FF8111D8_my  @ 0xFF8111D8 

void __attribute__((naked,noinline)) sub_FF8111D8_my() {
asm volatile (
      "STR     LR, [SP, #-4]! \n"
      "SUB     SP, SP, #0x74 \n"
      "MOV     R1, #0x74 \n"
      "MOV     R0, SP \n"
      "BL      sub_003FC448 \n" //RAM
      "MOV     R0, #0x57000 \n"
      "STR     R0, [SP, #4] \n"
#if defined(CHDK_NOT_IN_CANON_HEAP)
      "LDR     R0, =0x157C84 \n" // MEMISOSTART: Use original heap offset since CHDK is loaded in high memory 
#else
      "LDR     R0, =new_sa \n"	    //otherwise use patched value
      "LDR     R0, [R0] \n"
#endif
      "LDR     R2, =0x2ED440 \n"
      "STR     R0, [SP, #8] \n"
      "SUB     R0, R2, R0 \n"
      "STR     R0, [SP, #0xC] \n"
      "MOV     R0, #0x22 \n"
      "STR     R0, [SP, #0x18] \n"
      "MOV     R0, #0x7C \n"
      "STR     R0, [SP, #0x1C] \n"
      "LDR     R1, =0x2F5C00 \n"
      "LDR     R0, =0x1CD \n"
      "STR     R1, [SP] \n"
      "STR     R0, [SP, #0x20] \n"
      "MOV     R0, #0x96 \n"
      "STR     R2, [SP, #0x10] \n"
      "STR     R1, [SP, #0x14] \n"
      "STR     R0, [SP, #0x24] \n"
      "STR     R0, [SP, #0x28] \n"
      "MOV     R0, #0x64 \n"
      "STR     R0, [SP, #0x2C] \n"
      "MOV     R0, #0 \n"
      "STR     R0, [SP, #0x30] \n"
      "STR     R0, [SP, #0x34] \n"
      "MOV     R0, #0x10 \n"
      "STR     R0, [SP, #0x5C] \n"
      "MOV     R0, #0x800 \n"
      "STR     R0, [SP, #0x60] \n"
      "MOV     R0, #0xA0 \n"
      "STR     R0, [SP, #0x64] \n"
      "MOV     R0, #0x280 \n"
      "STR     R0, [SP, #0x68] \n"
//      "LDR     R1, =0xFF814278 \n" //original
      "LDR     R1, =sub_FF814278_my \n" //patched
      "MOV     R2, #0 \n"
      "MOV     R0, SP \n"
      "BL      sub_003F2778 \n"
      "ADD     SP, SP, #0x74 \n"
      "LDR     PC, [SP], #4 \n"
	);
}


//** sub_FF814278_my  @ 0xFF814278 

void __attribute__((naked,noinline)) sub_FF814278_my() {
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "BL      sub_FF810B50 \n"
      "BL      sub_FF815164 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF81438C \n" // "dmSetup"
      "BLLT    _err_init_task \n"
      "BL      sub_FF813EB0 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF814394 \n" // "termDriverInit"
      "BLLT    _err_init_task \n"
      "LDR     R0, =0xFF8143A4 \n" // "/_term"
      "BL      sub_FF813F98 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF8143AC \n" // "termDeviceCreate"
      "BLLT    _err_init_task \n"
      "LDR     R0, =0xFF8143A4 \n" //  "/_term"
      "BL      sub_FF8129B8 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF8143C0 \n" // "stdioSetup"
      "BLLT    _err_init_task \n"
      "BL      sub_FF814B00 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF8143CC \n" // "stdlibSetup"
      "BLLT    _err_init_task \n"
      "BL      sub_FF8116B8 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF8143D8 \n" // "armlib_setup"
      "BLLT    _err_init_task \n"
      "LDMFD   SP!, {R4,LR} \n"
//      "B       sub_FF81A698 \n" //original
      "B       sub_FF81A698_my \n" //patched
	);
}


//** sub_FF81A698_my  @ 0xFF81A698 

void __attribute__((naked,noinline)) sub_FF81A698_my() {
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "BL      sub_FF82EAD8 \n"
//      "BL      loc_FF81A6AC \n" // original taskcreate_Startup
      "BL      taskcreate_Startup_my \n" //patched taskcreate_Startup
      "MOV     R0, #0 \n"
      "LDMFD   SP!, {R4,PC} \n"
	);
}


//** taskcreate_Startup_my  @ 0xFF81A6AC 

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
asm volatile (
      "STMFD   SP!, {R3-R7,LR} \n"
      "BL      sub_FF835B84 \n"
      "LDR     R6, =0xC0220000 \n"
      "MOVS    R4, R0 \n"
      "MOV     R5, #1 \n"
      "BNE     loc_FF81A6FC \n"
      "BL      sub_FF830534 \n"
      "CMP     R0, #0 \n"
      "BEQ     loc_FF81A6FC \n"
      "LDR     R0, [R6, #0xFC] \n"
      "BIC     R1, R5, R0 \n"
      "LDR     R0, [R6, #0xF8] \n"
      "BIC     R0, R5, R0 \n"
      "ORRS    R2, R0, R1 \n"
      "BNE     loc_FF81A70C \n"
      "BL      sub_FF82E1A4 \n"
      "MOV     R0, #0x44 \n"
      "STR     R0, [R6, #0x12C] \n"
      "BL      sub_FF82E2B4 \n"
"loc_FF81A6F8:\n"
      "B       loc_FF81A6F8 \n"
"loc_FF81A6FC:\n"
      "LDR     R0, [R6, #0xF8] \n"
      "LDR     R1, [R6, #0xFC] \n"
      "BIC     R0, R5, R0 \n"
      "BIC     R1, R5, R1 \n"
"loc_FF81A70C:\n"
      "MOV     R3, #0 \n"
      "MOV     R2, R4 \n"
//      "BL      sub_FF82EAE0 \n" // StartUp mode detection. We must remove this for power-on mode handling to work
      "BL      sub_FF82EADC \n"
      "BL      sub_003F77E0 \n"
      "LDR     R1, =0x34E000 \n"
      "MOV     R0, #0 \n"
      "BL      sub_FF8341C0 \n"
      "BL      sub_003F79F8 \n"
      "MOV     R3, #0 \n"
      "STR     R3, [SP] \n"
//      "LDR     R3, =0xFF81A628 \n" //original
      "LDR     R3, =task_Startup_my \n" //patched
      "MOV     R2, #0 \n"
      "MOV     R1, #0x19 \n"
      "LDR     R0, =0xFF81A760 \n"
      "BL      _CreateTask \n"
      "MOV     R0, #0 \n"
      "LDMFD   SP!, {R3-R7,PC} \n"
	);
}


//** task_Startup_my  @ 0xFF81A628

void __attribute__((naked,noinline)) task_Startup_my() {
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "BL      sub_FF8148B8 \n"
      "BL      sub_FF82FC00 \n"
      "BL      sub_FF82DE4C \n"
      "BL      sub_FF835BCC \n"
      "BL      sub_FF835DB8 \n"
      "BL      sub_FF82CC48 \n"
      "BL      sub_FF82D810 \n"
//      "BL      sub_FF835C60 \n" //disable Diskboot.bin
      "BL      sub_FF835F34 \n"
      "BL      sub_FF836100 \n"
      "BL      sub_FF835EF8 \n"
      "BL      sub_FF835DE8 \n"
      "BL      sub_FF8340F4 \n"
      "BL      sub_FF836108 \n"
      "BL     CreateTask_spytask \n"		//added to create the Spytask
//      "BL      sub_FF82E97C \n" //original taskcreate_PhySw()
      "BL     taskcreatePhySw_my \n"		// patched taskcreate_PhySw()
      "BL      sub_FF83235C \n"
      "BL      sub_FF836120 \n"
      "BL      sub_FF82B9C8 \n"
      "BL      sub_FF82C510 \n"
      "BL      sub_FF835940 \n"
      "BL      sub_FF82CB38 \n"
      "BL      sub_FF82C4AC \n"
      "BL      sub_FF835F24 \n"
      "BL      sub_FF836C78 \n" //StartFactoryModeController
      "BL      sub_FF82C470 \n"
      "LDMFD   SP!, {R4,LR} \n"
      "B       sub_FF8149D8 \n"
	);
}


//** taskcreatePhySw_my  @ 0xFF82E97C 

void __attribute__((naked,noinline)) taskcreatePhySw_my() {
asm volatile (
      "STMFD   SP!, {R3-R5,LR} \n"
      "LDR     R4, =0x1C18 \n"
      "LDR     R0, [R4, #4] \n"
      "CMP     R0, #0 \n"
      "BNE     loc_FF82E9B0 \n"
      "MOV     R3, #0 \n"
      "STR     R3, [SP] \n"
//      "LDR     R3, =0xFF82E948 \n" //original
      "LDR     R3, =task_PhySw \n"   //patched  task_PhySw
//      "MOV     R2, #0x800 \n"      // original  
      "MOV     R2, #0x2000 \n" // stack size for new task_PhySw so we don't have to do stack switch
      "MOV     R1, #0x17 \n"
      "LDR     R0, =0xFF82EBD8 \n"
      "BL      sub_003F7A50 \n"
      "STR     R0, [R4, #4] \n"
"loc_FF82E9B0:\n"
      "BL      sub_FF87EE60 \n"
      "BL      sub_FF830484 \n"
      "CMP     R0, #0 \n"
      "BNE     loc_FF82E9CC \n"
      "LDR     R1, =0x3127C \n"
      "MOV     R0, #0 \n"
      "BL      sub_FF87EDD0 \n"
"loc_FF82E9CC:\n"
      "LDMFD   SP!, {R3-R5,PC} \n"
	);
}

void CreateTask_spytask() {

        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);                        
};


//** init_file_modules_task  @ 0xFF88895C 

void __attribute__((naked,noinline)) init_file_modules_task() {
asm volatile (
      "STMFD   SP!, {R4-R6,LR} \n"
      "BL      sub_FF8813CC \n"
      "LDR     R5, =0x5006 \n"
      "MOVS    R4, R0 \n"
      "MOVNE   R1, #0 \n"
      "MOVNE   R0, R5 \n"
      "BLNE    _PostLogicalEventToUI \n"
      "BL      sub_FF8813F8 \n"
      "BL	   core_spytask_can_start \n" //added CHDK: Set "it's-safe-to-start"-Flag for spytask
      "CMP     R4, #0 \n"
      "LDMNEFD SP!, {R4-R6,PC} \n"
      "MOV     R0, R5 \n"
      "LDMFD   SP!, {R4-R6,LR} \n"
      "MOV     R1, #0 \n"
      "B       _PostLogicalEventToUI \n"
	);
}
