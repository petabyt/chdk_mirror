#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

//void __attribute__((naked,noinline)) my_blinker(int n) {
//	asm volatile (
//"                STMFD   SP!, {R0-R5,LR}\n"
//);
//	volatile long *p=(void*)0xC022C30C;
//	int i, j;
//	for (j=0; j<n; j++)
//	{
//		*p = (*p & 0xFFFFFFCF) | 0x20; // Turn on LED
//		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }
//
//		*p = (*p & 0xFFFFFFCF);		 // Turn on LED
//		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }
//	}
//	for (i=0; i<0x900000; i++) { asm volatile ( "nop\n" ); }
//	asm volatile (
//"                LDMFD   SP!, {R0-R5,PC}\n"
//	);
//}

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_RotaryEncoder();
extern void task_MovieRecord();
extern void task_ExpDrv();

void __attribute__((naked,noinline)) taskHook(context_t **context)
{ 
    asm volatile("STMFD   SP!, {R0-R12,LR}\n");     // G1X crashes without this
    
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task; 
	if(tcb->entry == (void*)task_InitFileModules)	tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_RotaryEncoder)		tcb->entry = (void*)JogDial_task_my;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
    
    asm volatile("LDMFD   SP!, {R0-R12,PC}\n");     // G1X crashes without this
}

/*----------------------------------------------------------------------
	boot()

	Main entry point for the CHDK code
-----------------------------------------------------------------------*/

void __attribute__((naked,noinline)) boot() {

    asm volatile (
                 "LDR     R1, =0xC0410000\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R1]\n"
                 "MOV     R1, #0x78\n"
                 "MCR     p15, 0, R1,c1,c0\n"
                 "MOV     R1, #0\n"
                 "MCR     p15, 0, R1,c7,c10, 4\n"
                 "MCR     p15, 0, R1,c7,c5\n"
                 "MCR     p15, 0, R1,c7,c6\n"
                 "MOV     R0, #0x3D\n"
                 "MCR     p15, 0, R0,c6,c0\n"
                 "MOV     R0, #0xC000002F\n"
                 "MCR     p15, 0, R0,c6,c1\n"
                 "MOV     R0, #0x37\n"
                 "MCR     p15, 0, R0,c6,c2\n"
                 "MOV     R0, #0x40000037\n"
                 "MCR     p15, 0, R0,c6,c3\n"
                 "MOV     R0, #0x80000017\n"
                 "MCR     p15, 0, R0,c6,c4\n"
                 "LDR     R0, =0xFF00002F\n"
                 "MCR     p15, 0, R0,c6,c5\n"
				 "LDR     R0, =0xD000002B\n"
				 "MCR     p15, 0, R0,c6,c7\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c2,c0\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c2,c0, 1\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c3,c0\n"
                 "LDR     R0, =0x3333330\n"
                 "MCR     p15, 0, R0,c5,c0, 2\n"
                 "LDR     R0, =0x3333330\n"
                 "MCR     p15, 0, R0,c5,c0, 3\n"
                 "MRC     p15, 0, R0,c1,c0\n"
                 "ORR     R0, R0, #0x1000\n"
                 "ORR     R0, R0, #4\n"
                 "ORR     R0, R0, #1\n"
                 "MCR     p15, 0, R0,c1,c0\n"
                 "MOV     R1, #0x80000006\n"
                 "MCR     p15, 0, R1,c9,c1\n"
                 "MOV     R1, #6\n"
                 "MCR     p15, 0, R1,c9,c1, 1\n"
                 "MRC     p15, 0, R1,c1,c0\n"
                 "ORR     R1, R1, #0x50000\n"
                 "MCR     p15, 0, R1,c1,c0\n"
                 "LDR     R2, =0xC0200000\n"
                 "MOV     R1, #1\n"
                 "STR     R1, [R2,#0x10C]\n"
                 "MOV     R1, #0xFF\n"
                 "STR     R1, [R2,#0xC]\n"
                 "STR     R1, [R2,#0x1C]\n"
                 "STR     R1, [R2,#0x2C]\n"
                 "STR     R1, [R2,#0x3C]\n"
                 "STR     R1, [R2,#0x4C]\n"
                 "STR     R1, [R2,#0x5C]\n"
                 "STR     R1, [R2,#0x6C]\n"
                 "STR     R1, [R2,#0x7C]\n"
                 "STR     R1, [R2,#0x8C]\n"
                 "STR     R1, [R2,#0x9C]\n"
                 "STR     R1, [R2,#0xAC]\n"
                 "STR     R1, [R2,#0xBC]\n"
                 "STR     R1, [R2,#0xCC]\n"
                 "STR     R1, [R2,#0xDC]\n"
                 "STR     R1, [R2,#0xEC]\n"
                 "STR     R1, [R2,#0xFC]\n"
                 "LDR     R1, =0xC0400008\n"
                 "LDR     R2, =0x430005\n"
                 "STR     R2, [R1]\n"
                 "MOV     R1, #1\n"
                 "LDR     R2, =0xC0243100\n"
                 "STR     R2, [R1]\n"
                 "LDR     R2, =0xC0242010\n"
                 "LDR     R1, [R2]\n"
                 "ORR     R1, R1, #1\n"
                 "STR     R1, [R2]\n"

                 "LDR     R0, =0xFF662CEC\n"
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0x14E54\n"
 "loc_FF000144:\n"
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF000144\n"
                 "LDR     R1, =0x18C774\n"
                 "MOV     R2, #0\n"
 "loc_FF00015C:\n"
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FF00015C\n"

//                 "B       sub_FF000364\n"
                 "B       sub_FF000364_my\n" // -->
    );
}

void __attribute__((naked,noinline)) sub_FF000364_my() {

	//http://chdk.setepontos.com/index.php/topic,4194.0.html
	*(int*)0x1938=(int)taskHook;
	*(int*)0x193C=(int)taskHook;	// need this for startup in Playback mode (otherwise init_file_modules_task doesn't hook properly)
    
	// replacement of sub_FF056804 for correct power-on.
	*(int*)(0x26C8) = (*(int*)0xC022F48C)&0x800000 ? 0x200000 : 0x100000; 
    
	asm volatile (
                 "LDR     R0, =0xFF0003DC\n"
                 "MOV     R1, #0\n"
                 "LDR     R3, =0xFF000414\n"
 "loc_FF000370:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF000370\n"
                 "LDR     R0, =0xFF000414\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFF000628\n"
 "loc_FF00038C:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF00038C\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
 "loc_FF0003C0:\n"
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FF0003C0\n"
//                 "BL      sub_FF0011BC\n"
                 "BL      sub_FF0011BC_my\n" // -->
     );
}

void __attribute__((naked,noinline)) sub_FF0011BC_my() {

     asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R1, #0x74\n"
                 "MOV     R0, SP\n"
                 "BL      sub_FF45ED58\n"
                 "MOV     R0, #0x67000\n"
                 "STR     R0, [SP,#4]\n"

#if defined(OPT_CHDK_IN_EXMEM)
               "LDR     R0, =0x18C774\n" // use original heap offset since CHDK is loaded in high memory
#else
               "LDR     R0, =new_sa\n"   // otherwise use patched value
               "LDR     R0, [R0]\n"      // 
#endif
                 "LDR     R2, =0x55D788\n"
                 "STR     R0, [SP,#0x08]\n"
                 "SUB     R0, R2, R0\n"
                 "STR     R0, [SP,#0x0C]\n"
                 "MOV     R0, #0x22\n"
                 "STR     R0, [SP,#0x18]\n"
                 "MOV     R0, #0x72\n"
                 "STR     R0, [SP,#0x1C]\n"
                 "LDR     R1, =0x565C00\n"
                 "LDR     R0, =0x1CD\n"
                 "STR     R1, [SP]\n"
                 "STR     R0, [SP,#0x20]\n"
                 "MOV     R0, #0x96\n"
                 "STR     R2, [SP,#0x10]\n"
                 "STR     R1, [SP,#0x14]\n"
                 "STR     R0, [SP,#0x24]\n"
                 "STR     R0, [SP,#0x28]\n"
                 "MOV     R0, #0x64\n"
                 "STR     R0, [SP,#0x2C]\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [SP,#0x30]\n"
                 "STR     R0, [SP,#0x34]\n"
                 "MOV     R0, #0x10\n"
                 "STR     R0, [SP,#0x5C]\n"
                 "MOV     R0, #0x800\n"
                 "STR     R0, [SP,#0x60]\n"
                 "MOV     R0, #0xA0\n"
                 "STR     R0, [SP,#0x64]\n"
                 "MOV     R0, #0x280\n"
                 "STR     R0, [SP,#0x68]\n"

//"		LDR	R1, =0xFF005F38 \n"
"		LDR	R1, =sub_FF005F38_my \n"		// patched

"		B		sub_FF001258 \n"		// Continue in firmware
     );
}

void __attribute__((naked,noinline)) sub_FF005F38_my() {

	asm volatile (
"		STMFD	SP!, {R4,LR} \n"
"		BL	sub_FF000B34 \n"
"		BL	sub_FF00A390 \n"				// dmSetup
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aDmsetup \n"			// "dmSetup"
"		LDRLT	r0, =0xFF00604C \n"

"		BLLT	_err_init_task \n"
"		BL	sub_FF005B70 \n"
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aTermdriverinit \n"		// "termDriverInit"
"		LDRLT	R0, =0xFF006054 \n"

"		BLLT	_err_init_task \n"

//"		ADR	R0, a_term \n"					// "/_term"
"		LDR	R0, =0xFF006064 \n"

"		BL	sub_FF005C58 \n"				// termDeviceCreate
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aTermdevicecrea \n"		// "termDeviceCreate"
"		LDRLT	R0, =0xFF00606C \n"

"		BLLT	_err_init_task \n"

//"		ADR	R0, a_term \n"					// "/_term"
"		LDR	R0, =0xFF006064 \n"

"		BL	sub_FF003CB4 \n"
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aStdiosetup \n"			// "stdioSetup"
"		LDRLT	R0, =0xFF006080 \n"

"		BLLT	_err_init_task \n"
"		BL	sub_FF009CF8 \n"
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aStdlibsetup \n"		// "stdlibSetup"
"		LDRLT	R0, =0xFF00608C \n"

"		BLLT	_err_init_task \n"
"		BL	sub_FF00169C \n"
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aArmlib_setup \n"		// "armlib_setup"
"		LDRLT	R0, =0xFF006098 \n"

"		BLLT	_err_init_task \n"

"		LDMFD	SP!, {R4,LR} \n"

//"		B	sub_FF00FD90 \n"				// taskcreate_Startup
"		B	taskcreate_Startup_my \n"		// patched
        );
};

void __attribute__((naked,noinline)) taskcreate_Startup_my() {

	asm volatile (
		"STMFD   SP!, {R4,LR}\n"
//		"BL      j_nullsub_199\n"
//		"BL      sub_FF00FDA4\n"
		"BL      sub_FF00FDA4_my\n"
		"MOV     R0, #0\n"
		"LDMFD   SP!, {R4,PC}\n"
        );
};

void __attribute__((naked,noinline)) sub_FF00FDA4_my() {

	asm volatile (
		"STMFD   SP!, {R3-R7,LR}\n"
		"MOV     R6, #0\n"
		"BL      sub_FF02C534\n"
		"MOVS    R7, R0\n"
		"BNE     loc_FF00FE10\n"
		"BL      sub_FF025358\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF00FE10\n"
		"MOV     R0, #0x4F\n"
		"BL      sub_FF02AAF0\n"
		"RSBS    R5, R0, #1\n"
		"MOVCC   R5, #0\n"
		"MOV     R0, #0x4B\n"
		"BL      sub_FF02AAF0\n"
		"RSBS    R4, R0, #1\n"
		"MOVCC   R4, #0\n"
		"BL      sub_FF022B70\n"
		"CMP     R0, #1\n"
		"MOVEQ   R6, #1\n"
		"ORR     R0, R4, R5\n"
		"ORRS    R0, R0, R6\n"
		"BNE     loc_FF00FE30\n"
		"BL      sub_FF022D08\n"
		"LDR     R4, =0x83DC00\n"
		"MOV     R0, #0x54\n"
		"BL      sub_FF02AAE0\n"
"loc_FF00FE0C:\n"
		"B       loc_FF00FE0C\n"
"loc_FF00FE10:\n"
		"MOV     R0, #0x4B\n"
		"BL      sub_FF02AAF0\n"
		"RSBS    R4, R0, #1\n"
		"MOVCC   R4, #0\n"
		"MOV     R0, #0x4F\n"
		"BL      sub_FF02AAF0\n"
		"RSBS    R5, R0, #1\n"
		"MOVCC   R5, #0\n"
"loc_FF00FE30:\n"
		"MOV     R3, R6\n"
		"MOV     R2, R7\n"
		"MOV     R1, R5\n"
		"MOV     R0, R4\n"
//		"BL      sub_FF02398C\n"         // see begin of sub_FF000364_my()
//		"BL      j_nullsub_200\n"
		"BL      sub_FF02A470\n"
		"LDR     R1, =0x5CE000\n"
		"MOV     R0, #0\n"
		"BL      sub_FF02A8E0\n"
		"BL      sub_FF02A688\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP]\n"

//		"LDR     R3, =0xFF00FD34\n"
		"LDR	 R3, =task_Startup_my\n"	// patched

		"B		 sub_FF00FE68\n"	// Continue in firmware
     );
}

/*----------------------------------------------------------------------
	spytask
-----------------------------------------------------------------------*/
void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}

/*----------------------------------------------------------------------
	CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask()
{
	_CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);
}

void __attribute__((naked,noinline)) task_Startup_my() {

	asm volatile (
		"STMFD	SP!, {R4,LR}\n"
		"BL		sub_FF0065E8\n"	// taskcreate_ClockSave\n"
		"BL		sub_FF024A9C\n"
		"BL		sub_FF022B80\n"
//		"BL	j_nullsub_201\n"
		"BL		sub_FF02C768\n"
//		"BL		sub_FF02C610\n" // start diskboot.bin
		"BL		sub_FF02C920\n"
		"BL		sub_FF02C798\n"
		"BL		sub_FF029C14\n"
		"BL		sub_FF02C924\n"

		"BL		CreateTask_spytask\n" // added

//		"BL		sub_FF02380C\n"	//taskcreate_PhySw\n"
		"BL		taskcreatePhySw_my\n"  // we do this here rather than hook so we don't waste the original stack

        "B		sub_FF00FD64\n"		// Continue in firmware
     );
}

void __attribute__((naked,noinline)) taskcreatePhySw_my() {
	asm volatile (
        "STMFD   SP!, {R3-R5,LR}\n"
        "LDR     R4, =0x1BF4\n"
        "LDR     R0, [R4,#0x4]\n"
        "CMP     R0, #0\n"
        "BNE     sub_FF023840\n"
        "MOV     R3, #0\n"
        "STR     R3, [SP]\n"
        "LDR     R3, =mykbd_task\n" // task_PhySw
      //"MOV     R2, #0x800\n"
        "MOV     R2, #0x2000\n"     // stack size for new task_PhySw so we don't have to do stack switch
        "B	     sub_FF023830 \n" // continue in firmware
	);
}

///*----------------------------------------------------------------------
// @ 0xff09a978
void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FF0902A4\n"
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    _PostLogicalEventToUI\n"
				 "BL      sub_FF0902D0\n"

                 "BL      core_spytask_can_start\n"      // CHDK: Set "it's-safe-to-start" flag for spytask

				 "B	      sub_FF09A998\n"	// Continue in firmware
 );
}

///*----------------------------------------------------------------------
// Pointer to stack location where jogdial task records previous and current
// jogdial positions
short *jog_position;

// Firmware version @ FF0575CC
void __attribute__((naked,noinline)) JogDial_task_my() {
 asm volatile(
"                STMFD   SP!, {R4-R11,LR} \n"
"                SUB     SP, SP, #0x24 \n"
"                BL      sub_FF057960 \n"
"                LDR     R12, =0x26E8 \n"
"                LDR     R6, =0xFF464914 \n"
"                MOV     R0, #0 \n"

// Save pointer for kbd.c routine
" ADD R10, SP, #0x18 \n"
" LDR R9, =jog_position \n"
" STR R10, [R9] \n"

"                ADD     R10, SP, #0x08 \n"
"                ADD     R9, SP, #0x10 \n"

"loc_FF0575EC: \n"
"                ADD     R2, SP, #0x1C \n"
"                MOV     R1, #0 \n"
"                ADD     R4, R2, R0,LSL#1 \n"
"                ADD     R3, SP, #0x18 \n"
"                STRH    R1, [R4] \n"
"                ADD     R4, R3, R0,LSL#1 \n"
"                STRH    R1, [R4] \n"
"                STR     R2, [R9,R0,LSL#2] \n"
"                STR     R2, [R10,R0,LSL#2] \n"
"                ADD     R0, R0, #1 \n"
"                CMP     R0, #2 \n"
"                BLT     loc_FF0575EC \n"

"loc_FF05761C: \n"
"                LDR     R0, =0x26E8 \n"
"                MOV     R2, #0 \n"
"                LDR     R0, [R0,#8] \n"
"                MOV     R1, SP \n"
"                BL      sub_FF029EA8 \n"
"                CMP     R0, #0 \n"
"                LDRNE   R1, =0x256 \n"
"				 LDRNE   R0,=0xFF05787C \n" //aRotaryencoder_ ; "RotaryEncoder.c" \n"
"                BLNE    _DebugAssert \n"
"                LDR     R0, [SP] \n"
"                AND     R4, R0, #0xFF \n"
"                AND     R0, R0, #0xFF00 \n"
"                CMP     R0, #0x100 \n"
"                BEQ     loc_FF05768C \n"
"                CMP     R0, #0x200 \n"
"                BEQ     loc_FF0576C4 \n"
"                CMP     R0, #0x300 \n"
"                BEQ     loc_FF0578C4 \n"
"                CMP     R0, #0x400 \n"
"                BNE     loc_FF05761C \n"
"                CMP     R4, #0 \n"
"                LDRNE   R1, =0x2E1 \n"
"				 LDRNE   R0,=0xFF05787C \n" //aRotaryencoder_ ; "RotaryEncoder.c" \n"
"                BLNE    _DebugAssert \n"
"                RSB     R0, R4, R4,LSL#3 \n"
"                LDR     R0, [R6,R0,LSL#2] \n"

"loc_FF057684: \n"
"                BL      sub_FF057944 \n"
"                B       loc_FF05761C \n"

"loc_FF05768C: \n"
//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n" //sleep
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------
"                LDR     R0, =0x26F8 \n"
"                LDR     R0, [R0,R4,LSL#2] \n"
"                BL      sub_FF02B0E4 \n"

//"                ADR     R2, sub_FF057518 \n"
"                LDR     R2, =0xFF057518 \n"

"                ORR     R3, R4, #0x200 \n"
"                MOV     R1, R2 \n"
"                MOV     R0, #0x28 \n"
"                BL      sub_FF02B000 \n"
"                TST     R0, #1 \n"
"                CMPNE   R0, #0x15 \n"
"                STR     R0, [R10,R4,LSL#2] \n"
"                BEQ     loc_FF05761C \n"
"                MOV     R1, #0x268 \n"
"                B       loc_FF057868 \n"

"loc_FF0576C4: \n"
"                RSB     R5, R4, R4,LSL#3 \n"
"                LDR     R0, [R6,R5,LSL#2] \n"
"                LDR     R1, =0xC0240000 \n"
"                ADD     R0, R1, R0,LSL#8 \n"
"				 LDR	 R0, [R0,#0x104] \n"
"                MOV     R1, R0,ASR#16 \n"
"                ADD     R0, SP, #0x1C \n"
"                ADD     R11, R0, R4,LSL#1 \n"
"                ADD     R0, SP, #0x18 \n"
"				 ADD	 R0, R0, R4,LSL#1 \n"
"                STRH    R1, [R11] \n"
"                STR     R0, [SP,#0x20] \n"
"                LDRSH   R3, [R0] \n"
"                SUB     R2, R1, R3 \n"
"                CMP     R2, #0 \n"
"                BNE     loc_FF057748 \n"
"                LDR     R0, [R9,R4,LSL#2] \n"
"                CMP     R0, #0 \n"
"                BEQ     loc_FF057824 \n"
"                LDR     R7, =0x26F8 \n"
"                LDR     R0, [R7,R4,LSL#2] \n"
"                BL      sub_FF02B0E4 \n"

//"                ADR     R2, sub_FF057524 \n"
"                LDR     R2, =0xFF057524 \n"

"                ORR     R3, R4, #0x300 \n"
"                MOV     R1, R2 \n"
"                MOV     R0, #0x1F4 \n"
"                BL      sub_FF02B000 \n"
"                TST     R0, #1 \n"
"                CMPNE   R0, #0x15 \n"
"                STR     R0, [R7,R4,LSL#2] \n"
"                BEQ     loc_FF057824 \n"
"                LDR     R1, =0x281 \n"
"                B       loc_FF05781C \n"

"loc_FF057748: \n"
"                MOV     R0, R2 \n"
"                RSBLT   R0, R0, #0 \n"
"                MOVLE   R7, #0 \n"
"                MOVGT   R7, #1 \n"
"                CMP     R0, #0xFF \n"
"                BLS     loc_FF057784 \n"
"				 LDR	 R0, =0x7FFF \n"
"                CMP     R2, #0 \n"
"                SUBLE   R0, R0, R3 \n"
"                ADDLE   R0, R0, R1 \n"
"                SUBGT   R0, R0, R1 \n"
"                ADDGT   R0, R0, R3 \n"
"                MOV     R1, #0xFFFF7FFF \n"
"                SUB     R0, R0, R1 \n"
"                EOR     R7, R7, #1 \n"

"loc_FF057784: \n"
"                STR     R0, [SP,#0x04] \n"
"                LDR     R0, [R9,R4,LSL#2] \n"
"                CMP     R0, #0 \n"
"                ADDEQ   R0, R6, R5,LSL#2 \n"
"                LDREQ   R0, [R0,#8] \n"
"                BEQ     loc_FF0577BC \n"
"                ADD     R8, R6, R5,LSL#2 \n"
"                ADD     R1, R8, R7,LSL#2 \n"
"                LDR     R1, [R1,#0x10] \n"
"                CMP     R1, R0 \n"
"                BEQ     loc_FF0577C0 \n"
"                LDR     R0, [R8,#0xC] \n"
"                BL      sub_FF023864 \n"
"                LDR     R0, [R8,#8] \n"

"loc_FF0577BC: \n"
"                BL      sub_FF023864 \n"

"loc_FF0577C0: \n"
"                ADD     R0, R6, R5,LSL#2 \n"
"                ADD     R7, R0, R7,LSL#2 \n"
"                LDR     R0, [R7,#0x10] \n"
"                LDR     R1, [SP,#0x04] \n"
"                BL      sub_FF023874 \n"
"                LDR     R0, [R7,#0x10] \n"
"                LDR     R7, =0x26F8 \n"
"                STR     R0, [R9,R4,LSL#2] \n"
"                LDRH    R1, [R11] \n"
"                LDR     R0, [SP,#0x20] \n"
"                STRH    R1, [R0] \n"
"                LDR     R0, [R7,R4,LSL#2] \n"
"                BL      sub_FF02B0E4 \n"

//"                ADR     R2, sub_FF057524 \n"
"                LDR     R2, =0xFF057524 \n"

"                ORR     R3, R4, #0x300 \n"
"                MOV     R1, R2 \n"
"                MOV     R0, #0x1F4 \n"
"                BL      sub_FF02B000 \n"
"                TST     R0, #1 \n"
"                CMPNE   R0, #0x15 \n"
"                STR     R0, [R7,R4,LSL#2] \n"
"                BEQ     loc_FF057824 \n"
"                LDR     R1, =0x2C3 \n"

"loc_FF05781C: \n"
"				 LDR     R0,=0xFF05787C \n" //aRotaryencoder_ ; "RotaryEncoder.c" \n"
"                BL      _DebugAssert \n"

"loc_FF057824: \n"
"                ADD     R0, R6, R5,LSL#2 \n"
"                LDR     R0, [R0,#0x18] \n"
"                CMP     R0, #1 \n"
"                BNE     loc_FF0578BC \n"
"                LDR     R0, =0x26E8 \n"
"                LDR     R0, [R0,#0xC] \n"
"                CMP     R0, #0 \n"
"                BEQ     loc_FF0578BC \n"

//"                ADR     R2, sub_FF057518 \n"
"                LDR     R2, =0xFF057518 \n"

"                ORR     R3, R4, #0x400 \n"
"                MOV     R1, R2 \n"
"                BL      sub_FF02B000 \n"
"                TST     R0, #1 \n"
"                CMPNE   R0, #0x15 \n"
"                STR     R0, [R10,R4,LSL#2] \n"
"                BEQ     loc_FF05761C \n"
"                LDR     R1, =0x2CA \n"

"loc_FF057868: \n"
"				 LDR     R0,=0xFF05787C \n" //aRotaryencoder_ ; "RotaryEncoder.c" \n"
"                BL      _DebugAssert \n"
"                B       loc_FF05761C \n"

"loc_FF0578BC: \n"
"                LDR     R0, [R6,R5,LSL#2] \n"
"                B       loc_FF057684 \n"

"loc_FF0578C4: \n"
"                LDR     R0, [R9,R4,LSL#2] \n"
"                CMP     R0, #0 \n"
"                MOVEQ   R1, #0x2D4 \n"
"				 LDREQ   R0,=0xFF05787C \n" //aRotaryencoder_ ; "RotaryEncoder.c" \n"
"                BLEQ    _DebugAssert \n"
"                RSB     R0, R4, R4,LSL#3 \n"
"                ADD     R0, R6, R0,LSL#2 \n"
"                LDR     R0, [R0,#0xC] \n"
"                BL      sub_FF023864 \n"
"                MOV     R0, #0 \n"
"                STR     R0, [R9,R4,LSL#2] \n"
"                B       loc_FF05761C \n"
);
}
