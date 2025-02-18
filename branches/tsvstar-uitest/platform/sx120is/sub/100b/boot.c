#include "lolevel.h"
#include "platform.h"
#include "core.h"


#define LED_AF     0xC022000C
#define LED_ORANGE 0xC0220010
#define LED_GREEN  0xC0220014

#define DELAY 10000000

void  __attribute__((naked,noinline)) blink()
{
	asm volatile (
	 //---------------start blink---------------
			"B start\n""b10: .long 0\n""b11: .long 0\n""b12: .long 0\n""STR R10, b10\n""STR R11, b11\n""STR R12, b12\n"		
	"start:	LDR R12, =0xC022000C\n"
			"LDR R10, =0xFFFFF\n"
			"MOV R11, #0x46\n"
			"STR R11, [R12]\n"			
	"check:	CMP R10, #0\n"
			"BEQ off\n"
			"SUB R10, R10, #1\n"
			"B check\n"			
	"off:	MOV R11, #0x44\n"
			"STR R11, [R12]\n"	
			"LDR R10, b10\n""LDR R11, b11\n""LDR R12, b12\n"
			"MOV pc,lr\n"
//---------------end blink---------------/
	);
}	
/*	
void debug_my_blink()
{
	volatile long *p = (void*)LED_GREEN;       		// turned off later, so assumed to be power
	volatile long *p2 = (void*)LED_AF;       		// turned off later, so assumed to be power
	int counter;

	// DEBUG: blink led
	//led on
	counter = DELAY; 
	*p = 0x46; 
	while (counter--) { asm("nop\n nop\n"); };
	*p2 = 0x46;
	//led off
	counter = DELAY; 
	*p = 0x44; 
	while (counter--) { asm("nop\n nop\n"); };
	*p2= 0x44;
	
}
*/

const char * const new_sa = &_end;

void JogDial_task_my(void);

void taskCreateHook(int *p) { 
 p-=17;
if (p[0]==0xFFC4F640)  p[0]=(int)capt_seq_task;	
if (p[0]==0xFFC11638)  p[0]=(int)mykbd_task;
if (p[0]==0xFFC696AC)  p[0]=(int)init_file_modules_task;
if (p[0]==0xFFC37070)  p[0]=(int)JogDial_task_my;
if (p[0]==0xFFD144F0)  p[0]=(int)movie_record_task;
if (p[0]==0xFFC86E80)  p[0]=(int)exp_drv_task;
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};


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
                 "MOV     R0, #0x33\n"
                 "MCR     p15, 0, R0,c6,c2\n"
                 "MOV     R0, #0x40000033\n"
                 "MCR     p15, 0, R0,c6,c3\n"
                 "MOV     R0, #0x80000017\n"
                 "MCR     p15, 0, R0,c6,c4\n"
                 "LDR     R0, =0xFFC0002B\n"
                 "MCR     p15, 0, R0,c6,c5\n"
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
                 "LDR     R0, =0xFFF06D78\n"
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0xBCC4\n"

 "loc_FFC0013C:\n"
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC0013C\n"
                 "LDR     R1, =0x10A6AC\n"
                 "MOV     R2, #0\n"

 "loc_FFC00154:\n"
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FFC00154\n"
                 "B       loc_FFC001A0_my\n" //------------------>
    );
};


void __attribute__((naked,noinline)) loc_FFC001A0_my() {
	*(int*)0x1934=(int)taskCreateHook;
	*(int*)0x1938=(int)taskCreateHook;
    *(int*)(0x24BC+0x4) = (*(int*)0xC0220118)&1 ? 0x100000: 0x200000; // replacement of sub_FFC1177C
    //from taskcreate_startup to sub_FFC1177C and there to sub_FFC367AC
	asm volatile (
                 "LDR     R0, =0xFFC00218\n"
                 "MOV     R1, #0\n"
                 "LDR     R3, =0xFFC00250\n"
 "loc_FFC001AC:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC001AC\n"
                 "LDR     R0, =0xFFC00250\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFFC00464\n"
 "loc_FFC001C8:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC001C8\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
 "loc_FFC001FC:\n"
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FFC001FC\n"
                 "BL      sub_FFC00FC4_my\n" //-------------->
	);
}


void __attribute__((naked,noinline)) sub_FFC00FC4_my() {
      asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"
                 "BL      sub_FFE90DB4\n"
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
//                 "LDR     R0, =0x10A6AC\n"	// removed
                 "LDR     R0, =new_sa\n"	// added
                 "LDR     R0, [R0]\n"		// added
                 "LDR     R2, =0x2F9C00\n"
                 "LDR     R1, =0x2F24A8\n"
                 "STR     R0, [SP,#8]\n"
                 "SUB     R0, R1, R0\n"
                 "ADD     R3, SP, #0xC\n"
                 "STR     R2, [SP]\n"
                 "STMIA   R3, {R0-R2}\n"
                 "MOV     R0, #0x22\n"
                 "STR     R0, [SP,#0x18]\n"
                 "MOV     R0, #0x68\n"
                 "STR     R0, [SP,#0x1C]\n"
                 "LDR     R0, =0x19B\n"
                 "LDR     R1, =sub_FFC04B50_my\n"	// changed
                 "STR     R0, [SP,#0x20]\n"
                 "MOV     R0, #0x96\n"
                 "STR     R0, [SP,#0x24]\n"
                 "MOV     R0, #0x78\n"
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
                 "MOV     R0, SP\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FFC02B40\n"
                 "ADD     SP, SP, #0x74\n"
                 "LDR     PC, [SP],#4\n"
	);
}

void __attribute__((naked,noinline)) sub_FFC04B50_my() {
	asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FFC00954\n"
                 "BL      sub_FFC08E64\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04C64\n"    // "dmSetup"
                 "BLLT    sub_FFC04C44\n"
                 "BL      sub_FFC0478C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04C6C\n"    // "termDriverInit"
                 "BLLT    sub_FFC04C44\n"
                 "LDR     R0, =0xFFC04C7C\n"    // "/_term"
                 "BL      sub_FFC04874\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04C84\n"    // "termDeviceCreate"
                 "BLLT    sub_FFC04C44\n"
                 "LDR     R0, =0xFFC04C7C\n"    // "/_term"
                 "BL      sub_FFC0333C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04C98\n"    // "stdioSetup"
                 "BLLT    sub_FFC04C44\n"
                 "BL      sub_FFC08878\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04CA4\n"    // "stdlibSetup"
                 "BLLT    sub_FFC04C44\n"
                 "BL      sub_FFC014A8\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04CB0\n"    // "armlib_setup"
                 "BLLT    sub_FFC04C44\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       taskcreate_Startup_my\n"
        );
};

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
	asm volatile (
                 "STMFD   SP!, {R3,LR}\n"
                 "BL      sub_FFC11774\n"	// j_nullsub_232
                 "BL      sub_FFC188AC\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFC0C060\n"
                 "BL      sub_FFC11770\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFC0C060\n"
                 "BL      sub_FFC10E3C\n"
                 "LDR     R1, =0xC0220000\n"
                 "MOV     R0, #0x44\n"
                 "STR     R0, [R1,#0x84]\n"
                 "STR     R0, [R1,#0x80]\n"
                 "BL      sub_FFC11030\n"
 "loc_FFC0C05C:\n"
                 "B       loc_FFC0C05C\n"
 "loc_FFC0C060:\n"
//                 "BL      sub_FFC1177C\n"	// removed for correct power-on on 'on/off' button
                 "BL      sub_FFC11778\n"	// j_nullsub_233
                 "BL      sub_FFC16B68\n"
                 "LDR     R1, =0x34E000\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FFC16FB0\n"
                 "BL      sub_FFC16D5C\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =task_Startup_my\n"	//----------->
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x19\n"
                 "LDR     R0, =0xFFC0C0A8\n"	// "Startup"
                 "BL      sub_FFC0AD70\n"	// eventproc_export_CreateTask
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R12,PC}\n"
     );
}

void __attribute__((naked,noinline)) task_Startup_my() {
     asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FFC051AC\n"	// taskcreate_ClockSave
                 "BL      sub_FFC12850\n"
                 "BL      sub_FFC10AC8\n"
                 "BL      sub_FFC188EC\n"	// j_nullsub_236
                 "BL      sub_FFC18AD0\n"
//                 BL      sub_FFC18980\n"	// start diskboot.bin
                 "BL      sub_FFC18C6C\n"
                 "BL      sub_FFC0FBB0\n"
                 "BL      sub_FFC18B00\n"
                 "BL      sub_FFC1630C\n"
                 "BL      sub_FFC18C70\n"
		 "BL      CreateTask_spytask\n"    // added
                 "BL      sub_FFC1166C\n"	// taskcreate_PhySw
                 "BL      sub_FFC146C0\n"
                 "BL      sub_FFC18C88\n"
                 "BL      sub_FFC0EEE8\n"	// nullsub_2
                 "BL      sub_FFC104AC\n"
                 "BL      sub_FFC18690\n"	// taskcreate_Bye
                 "BL      sub_FFC10A7C\n"
                 "BL      sub_FFC103D0\n"
                 "BL      sub_FFC0FBE4\n"
                 "BL      sub_FFC196E4\n"
                 "BL      sub_FFC103A8\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FFC052CC\n"
     );
}


void __attribute__((naked,noinline)) init_file_modules_task() {
    asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FFC61560\n"
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    sub_FFC63DA8\n"	// eventproc_export_PostLogicalEventToUI
                 "BL      sub_FFC6158C_my\n"	//--------->
                 "BL      core_spytask_can_start\n"	// CHDK: Set "it's-safe-to-start"-Flag for spytask
                 "CMP     R4, #0\n"
                 "MOVEQ   R0, R5\n"
                 "LDMEQFD SP!, {R4-R6,LR}\n"
                 "MOVEQ   R1, #0\n"
                 "BEQ     sub_FFC63DA8\n"	// eventproc_export_PostLogicalEventToUI
                 "LDMFD   SP!, {R4-R6,PC}\n"
    );
}


void __attribute__((naked,noinline)) sub_FFC6158C_my() {
    asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FFC45524_my\n"	//------------->
                 "BL      sub_FFCF47FC\n"	// nullsub_105
                 "LDR     R4, =0x2E80\n"
                 "LDR     R0, [R4,#4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFC615C4\n"
                 "BL      sub_FFC447E4\n"
                 "BL      sub_FFCEB398\n"
                 "BL      sub_FFC447E4\n"
                 "BL      sub_FFC4105C\n"
                 "BL      sub_FFC446E4\n"
                 "BL      sub_FFCEB458\n"
 "loc_FFC615C4:\n"
                 "MOV     R0, #1\n"
                 "STR     R0, [R4]\n"
                 "LDMFD   SP!, {R4,PC}\n"
    );
}

void __attribute__((naked,noinline)) sub_FFC45524_my() {
    asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R8, R0\n"
                 "BL      sub_FFC4548C\n"
                 "MOV     R6, R0\n"
                 "ADD     R1, R0, R0,LSL#4\n"
                 "LDR     R0, =0x100E0\n"
                 "ADD     R4, R0, R1,LSL#3\n"
                 "LDR     R0, [R4,#0x74]\n"
                 "CMP     R0, #4\n"
                 "LDREQ   R1, =0x804\n"
                 "LDREQ   R0, =0xFFC44FA0\n"	// aMounter_c
                 "BLEQ    sub_FFC0B048\n"	// DebugAssert
                 "MOV     R1, R8\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FFC44CE4\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "BL      sub_FFC45A90\n"
                 "CMP     R0, #0\n"
                 "STREQ   R0, [R4,#0x74]\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FFC44D78\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FFC45108_my\n"	//--------->
                 "MOV     R5, R0\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FFC45324\n"
                 "LDR     R6, [R4,#0x3C]\n"
                 "AND     R7, R5, R0\n"
                 "CMP     R6, #0\n"
                 "LDR     R1, [R4,#0x38]\n"
                 "MOVEQ   R0, #0x80000001\n"
                 "MOV     R5, #0\n"
                 "BEQ     loc_FFC455D8\n"
                 "MOV     R0, R1\n"
                 "BL      sub_FFC4494C\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R5, #4\n"
                 "CMP     R6, #5\n"
                 "ORRNE   R0, R5, #1\n"
                 "BICEQ   R0, R5, #1\n"
                 "CMP     R7, #0\n"
                 "BICEQ   R0, R0, #2\n"
                 "ORREQ   R0, R0, #0x80000000\n"
                 "BICNE   R0, R0, #0x80000000\n"
                 "ORRNE   R0, R0, #2\n"
 "loc_FFC455D8:\n"
                 "CMP     R8, #7\n"
                 "STR     R0, [R4,#0x40]\n"
                 "LDMNEFD SP!, {R4-R8,PC}\n"
                 "MOV     R0, R8\n"
                 "BL      sub_FFC454DC\n"
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R8,LR}\n"
                 "LDREQ   R0, =0xFFC457E0\n"	// aEmemMountError ; "EMEM MOUNT ERROR!!!"
                 "BEQ     sub_FFC015A8\n"	// qPrintf
                 "LDMFD   SP!, {R4-R8,PC}\n"
    );
}

void __attribute__((naked,noinline)) sub_FFC45108_my() {
    asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "MOV     R6, R0\n"
                 "ADD     R5, R0, R0,LSL#4\n"
                 "LDR     R0, =0x100E0\n"
                 "ADD     R4, R0, R5,LSL#3\n"
                 "LDR     R0, [R4,#0x74]\n"
                 "TST     R0, #2\n"
                 "MOVNE   R0, #1\n"
                 "LDMNEFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R6\n"
                 "BL      sub_FFC44E00_my\n"	//------------->
                 "CMP     R0, #0\n"
                 "LDRNE   R0, [R4,#0x38]\n"
                 "MOVNE   R1, R6\n"
                 "BLNE    sub_FFC44FC4\n"
                 "LDR     R1, =0x10168\n"
                 "LDR     R1, [R1,R5,LSL#2]\n"
                 "CMP     R1, #4\n"
                 "BEQ     loc_FFC45168\n"
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FFC449DC\n"
 "loc_FFC45168:\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R1, [R4,#0x74]\n"
                 "ORRNE   R1, R1, #2\n"
                 "STRNE   R1, [R4,#0x74]\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
    );
}

void __attribute__((naked,noinline)) sub_FFC44E00_my() {
    asm volatile(
                 "STMFD   SP!, {R4-R10,LR}\n"
                 "MOV     R9, R0\n"
                 "LDR     R0, =0x100E0\n"
                 "ADD     R1, R1, R1,LSL#4\n"
                 "ADD     R5, R0, R1,LSL#3\n"
                 "LDR     R0, [R5,#0x3C]\n"
                 "MOV     R8, #0\n"
                 "CMP     R0, #7\n"
                 "MOV     R7, #0\n"
                 "MOV     R6, #0\n"
                 "ADDLS   PC, PC, R0,LSL#2\n"
                 "B       loc_FFC44F5C\n"
 "loc_FFC44E30:\n"
                 "B       loc_FFC44E68\n"
 "loc_FFC44E34:\n"
                 "B       loc_FFC44E50\n"
 "loc_FFC44E38:\n"
                 "B       loc_FFC44E50\n"
 "loc_FFC44E3C:\n"
                 "B       loc_FFC44E50\n"
 "loc_FFC44E40:\n"
                 "B       loc_FFC44E50\n"
 "loc_FFC44E44:\n"
                 "B       loc_FFC44F54\n"
 "loc_FFC44E48:\n"
                 "B       loc_FFC44E50\n"
 "loc_FFC44E4C:\n"
                 "B       loc_FFC44E50\n"
 "loc_FFC44E50:\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x200\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC5B6C8\n"
                 "MOVS    R4, R0\n"
                 "BNE     loc_FFC44E70\n"
 "loc_FFC44E68:\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R10,PC}\n"
 "loc_FFC44E70:\n"
                 "LDR     R12, [R5,#0x50]\n"
                 "MOV     R3, R4\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R9\n"
                 "BLX     R12\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FFC44E9C\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC5B814\n"
                 "B       loc_FFC44E68\n"
 "loc_FFC44E9C:\n"
                 "LDR     R1, [R5,#0x6C]\n"
                 "MOV     R0, R9\n"
                 "BLX     R1\n"
          //insertion of new code for FAT32 autodetection
		 "MOV   R1, R4\n"           //  pointer to MBR in R1
		 "BL 	mbr_read_dryos\n"   //  total sectors count in R0 before and after call

          // Start of DataGhost's FAT32 autodetection code
          // Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
          // According to the code below, we can use R1, R2, R3 and R12.
          // LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
          // that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
          "MOV     R12, R4\n"                    // Copy the MBR start address so we have something to work with
          "MOV     LR, R4\n"                     // Save old offset for MBR signature
          "MOV     R1, #1\n"                     // Note the current partition number
          "B       dg_sd_fat32_enter\n"          // We actually need to check the first partition as well, no increments yet!
     "dg_sd_fat32:\n"
          "CMP     R1, #4\n"                     // Did we already see the 4th partition?
          "BEQ     dg_sd_fat32_end\n"            // Yes, break. We didn't find anything, so don't change anything.
          "ADD     R12, R12, #0x10\n"            // Second partition
          "ADD     R1, R1, #1\n"                 // Second partition for the loop
     "dg_sd_fat32_enter:\n"
          "LDRB    R2, [R12, #0x1BE]\n"          // Partition status
          "LDRB    R3, [R12, #0x1C2]\n"          // Partition type (FAT32 = 0xB)
          "CMP     R3, #0xB\n"                   // Is this a FAT32 partition?
          "CMPNE   R3, #0xC\n"                   // Not 0xB, is it 0xC (FAT32 LBA) then?
          "BNE     dg_sd_fat32\n"                // No, it isn't. Loop again.
          "CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
          "CMPNE   R2, #0x80\n"
          "BNE     dg_sd_fat32\n"                // Invalid, go to next partition
                                                 // This partition is valid, it's the first one, bingo!
          "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.

     "dg_sd_fat32_end:\n"
		// End of DataGhost's FAT32 autodetection code
		//end insertion

                 "LDRB    R1, [R4,#0x1C9]\n"
                 "LDRB    R3, [R4,#0x1C8]\n"
                 "LDRB    R12, [R4,#0x1CC]\n"
                 "MOV     R1, R1,LSL#24\n"
                 "ORR     R1, R1, R3,LSL#16\n"
                 "LDRB    R3, [R4,#0x1C7]\n"
                 "LDRB    R2, [R4,#0x1BE]\n"
//                 "LDRB    LR, [R4,#0x1FF]\n"	// removed
                 "ORR     R1, R1, R3,LSL#8\n"
                 "LDRB    R3, [R4,#0x1C6]\n"
                 "CMP     R2, #0\n"
                 "CMPNE   R2, #0x80\n"
                 "ORR     R1, R1, R3\n"
                 "LDRB    R3, [R4,#0x1CD]\n"
                 "MOV     R3, R3,LSL#24\n"
                 "ORR     R3, R3, R12,LSL#16\n"
                 "LDRB    R12, [R4,#0x1CB]\n"
                 "ORR     R3, R3, R12,LSL#8\n"
                 "LDRB    R12, [R4,#0x1CA]\n"
                 "ORR     R3, R3, R12\n"
//                 "LDRB    R12, [R4,#0x1FE]\n"	// removed
                 "LDRB    R12, [LR,#0x1FE]\n"	// added, First MBR signature byte (0x55), LR is original offset.
                 "LDRB    LR, [LR,#0x1FF]\n"	// added, Last MBR signature byte (0xAA), LR is original offset.
                 "BNE     loc_FFC44F28\n"
                 "CMP     R0, R1\n"
                 "BCC     loc_FFC44F28\n"
                 "ADD     R2, R1, R3\n"
                 "CMP     R2, R0\n"
                 "CMPLS   R12, #0x55\n"
                 "CMPEQ   LR, #0xAA\n"
                 "MOVEQ   R7, R1\n"
                 "MOVEQ   R6, R3\n"
                 "MOVEQ   R4, #1\n"
                 "BEQ     loc_FFC44F2C\n"
 "loc_FFC44F28:\n"
                 "MOV     R4, R8\n"
 "loc_FFC44F2C:\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC5B814\n"
                 "CMP     R4, #0\n"
                 "BNE     loc_FFC44F68\n"
                 "LDR     R1, [R5,#0x6C]\n"
                 "MOV     R7, #0\n"
                 "MOV     R0, R9\n"
                 "BLX     R1\n"
                 "MOV     R6, R0\n"
                 "B       loc_FFC44F68\n"
 "loc_FFC44F54:\n"
                 "MOV     R6, #0x40\n"
                 "B       loc_FFC44F68\n"
 "loc_FFC44F5C:\n"
                 "LDR     R1, =0x568\n"
                 "LDR     R0, =0xFFC44FA0\n"	// "Mounter.c"
                 "BL      sub_FFC0B048\n"	// DebugAssert
 "loc_FFC44F68:\n"
                 "STR     R7, [R5,#0x44]!\n"
                 "STMIB   R5, {R6,R8}\n"
                 "MOV     R0, #1\n"
                 "LDMFD   SP!, {R4-R10,PC}\n"
    );
}

void __attribute__((naked,noinline)) JogDial_task_my()
{
	asm volatile(				
		"STMFD   SP!, {R4-R11,LR}\n"
		"SUB     SP, SP, #0x2C\n"
		"BL      sub_FFC37418\n"	// DebugAssert: JogDial.c:14
		"LDR     R1, =0x24CC\n"
		"LDR     R8, =0xFFE9A7E4\n"
		"MOV     R0, #0\n"
		"ADD     R2, SP, #0x14\n"
		"ADD     R3, SP, #0x18\n"
		"ADD     R10, SP, #0xc\n"
		"ADD     R9, SP, #0x10\n"
		"MOV     R7, #0\n"
"loc_FFC3709C:\n"
		"ADD     R3, SP, #0x18\n"
		"ADD     R12, R3, R0,LSL#1\n"
		"ADD     R2, SP, #0x14\n"
		"STRH    R7, [R12]\n"
		"ADD     R12, R2, R0,LSL#1\n"
		"STRH    R7, [R12]\n"
		"STR     R7, [R9,R0,LSL#2]\n"
		"STR     R7, [R10,R0,LSL#2]\n"
		"ADD     R0, R0, #1\n"
		"CMP     R0, #1\n"
		"BLT     loc_FFC3709C\n"

"loc_FFC370C8:\n"
//------------------  added code ---------------------
"loop:\n"
		"LDR     R0, =jogdial_stopped\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0\n"
		"BEQ     endofloop\n"
		"MOV     R0, #40\n"
		"BL      _SleepTask\n"
		"B       loop\n"
"endofloop:\n"
//------------------  original code ------------------	
		"LDR     R0, =0x24CC\n"
		"MOV     R2, #0\n"
		"LDR     R0, [R0,#8]\n"
		"ADD     R1, SP, #0x4\n"
		"BL      sub_FFC1659C\n"	// KerQueue.c
		"TST     R0, #1\n"
		"LDRNE   R1, =0x226\n"
		"LDRNE   R0, =0xFFC3734C\n"
		"BLNE    sub_FFC0B048\n"	// DebugAssert: JogDial.c:550
		"LDR     R0, [SP,#0x4]\n"
		"AND     R4, R0, #0xFF\n"
		"AND     R0, R0, #0xFF00\n"
		"CMP     R0, #0x100\n"
		"BEQ     loc_FFC3714C\n"	//

		"CMP     R0, #0x200\n"
		"BEQ     loc_FFC37184\n"	//
		"CMP     R0, #0x300\n"
		"BEQ     loc_FFC37398\n"
		"CMP     R0, #0x400\n"
		"BNE     loc_FFC370C8\n"	//
		"CMP     R4, #0\n"
		"LDRNE   R1, =0x2CA\n"
		"LDRNE   R0, =0xFFC3734C\n"
		"BLNE    sub_FFC0B048\n"	// DebugAssert: JogDial.c:714
		"LDR     R2, =0xFFE9A7D0\n"
		"ADD     R0, R4, R4,LSL#2\n"
		"LDR     R1, [R2,R0,LSL#2]\n"
		"STR     R7, [R1]\n"
		"MOV     R1, #1\n"
		"ADD     R0, R2, R0,LSL#2\n"

"loc_FFC37140:\n"
		"LDR     R0, [R0,#8]\n"
		"STR     R1, [R0]\n"
		"B       loc_FFC370C8\n"

"loc_FFC3714C:\n"
		"LDR     R5, =0x24DC\n"
		"LDR     R0, [R5,R4,LSL#2]\n"
		"BL      sub_FFC17534\n"
		"LDR     R2, =0xFFC36FFC\n"
		"ADD     R1, R2, #0\n"
		"ORR     R3, R4, #0x200\n"
		"MOV     R0, #0x28\n"
		"BL      sub_FFC17450\n"
		"TST     R0, #1\n"
		"CMPNE   R0, #0x15\n"
		"STR     R0, [R10,R4,LSL#2]\n"
		"BEQ     loc_FFC370C8\n"
		"LDR     R1, =0x23B\n"
		"B       loc_FFC3733C\n"

"loc_FFC37184:\n"
		"LDR     R1, =0xFFE9A7D0\n"
		"ADD     R0, R4, R4,LSL#2\n"
		"STR     R0, [SP,#0x28]\n"
		"ADD     R0, R1, R0,LSL#2\n"
		"STR     R0, [SP,#0x24]\n"
		"LDR     R0, [R0,#4]\n"
		"LDR     R0, [R0]\n"
		"MOV     R2, R0,ASR#16\n"
		"ADD     R0, SP, #0x18\n"
		"ADD     R0, R0, R4,LSL#1\n"
		"STR     R0, [SP,#0x20]\n"
		"STRH    R2, [R0]\n"
		"ADD     R0, SP, #0x14\n"
		"ADD     R0, R0, R4,LSL#1\n"
		"STR     R0, [SP,#0x1c]\n"
		"LDRSH   R3, [R0]\n"
		"SUB     R0, R2, R3\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FFC372F4\n"
		"RSBLT   R0, R0, #0\n"
		"MOVLE   R5, #0\n"
		"MOVGT   R5, #1\n"
		"CMP     R0, #0xFF\n"
		"BLS     loc_FFC37210\n"
		"CMP     R1, #0\n"
		"RSBLE   R0, R3, #0xFF\n"
		"ADDLE   R0, R0, #0x7F00\n"
		"ADDLE   R0, R0, R2\n"
		"RSBGT   R0, R2, #0xFF\n"
		"ADDGT   R0, R0, #0x7F00\n"
		"ADDGT   R0, R0, R3\n"
		"ADD     R0, R0, #0x8000\n"
		"ADD     R0, R0, #1\n"
		"EOR     R5, R5, #1\n"

"loc_FFC37210:\n"
		"STR     R0, [SP,#0x8]\n"
		"LDR     R0, [R9,R4,LSL#2]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FFC37260\n"
		"LDR     R1, =0xFFE9A7C8\n"
		"ADD     R1, R1, R4,LSL#3\n"
		"LDR     R1, [R1,R5,LSL#2]\n"
		"CMP     R1, R0\n"
		"BEQ     loc_FFC3727C\n"
		"ADD     R11, R4, R4,LSL#1\n"
		"ADD     R6, R8, R11,LSL#2\n"
		"LDRB    R0, [R6,#9]\n"
		"CMP     R0, #1\n"
		"LDREQ   R0, [R6,#4]\n"
		"BLEQ    sub_FFC65B38\n"
		"LDRB    R0, [R6,#8]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FFC3727C\n"
		"LDR     R0, [R8,R11,LSL#2]\n"
		"B       loc_FFC37278\n"

"loc_FFC37260:\n"
		"ADD     R0, R4, R4,LSL#1\n"
		"ADD     R1, R8, R0,LSL#2\n"
		"LDRB    R1, [R1,#8]\n"
		"CMP     R1, #1\n"
		"BNE     loc_FFC3727C\n"
		"LDR     R0, [R8,R0,LSL#2]\n"

"loc_FFC37278:\n"
		"BL      sub_FFC65B38\n"

"loc_FFC3727C:\n" // is in loop
		"LDR     R0, =0xFFE9A7C8\n"
		"LDR     R1, [SP,#0x8]\n"
		"ADD     R6, R0, R4,LSL#3\n"
		"LDR     R0, [R6,R5,LSL#2]\n"
		"BL      sub_FFC65A68\n"
		"LDR     R0, [R6,R5,LSL#2]\n"
		"STR     R0, [R9,R4,LSL#2]\n"
		"LDR     R0, [SP,#0x20]\n"
		"LDR     R1, [SP,#0x1c]\n"
		"LDRH    R0, [R0]\n"
		"STRH    R0, [R1]\n"
		"ADD     R0, R4, R4,LSL#1\n"
		"ADD     R0, R8, R0,LSL#2\n"
		"LDRB    R0, [R0,#9]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FFC372F4\n"
		"LDR     R5, =0x24DC\n"
		"LDR     R0, [R5,R4,LSL#2]\n"
		"BL      sub_FFC17534\n"
		"LDR     R2, =0xFFC37008\n"
		"ADD     R1, R2, #0\n"
		"ORR     R3, R4, #0x300\n"
		"MOV     R0, #0x1F4\n"
		"BL      sub_FFC17450\n"
		"TST     R0, #1\n"
		"CMPNE   R0, #0x15\n"
		"STR     R0, [R5,R4,LSL#2]\n"
		"LDRNE   R0, =0xFFC3734C\n"
		"MOVNE   R1, #0x2A4\n"
		"BLNE    sub_FFC0B048\n"	// DebugAssert: JogDial.c:676

"loc_FFC372F4:\n"
		"ADD     R0, R4, R4,LSL#1\n"
		"ADD     R0, R8, R0,LSL#2\n"
		"LDRB    R0, [R0,#0xA]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FFC3737C\n"
		"LDR     R0, =0x23E4\n"
		"LDR     R0, [R0,#0xC]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FFC3737C\n"
		"LDR     R2, =0xFFC36FFC\n"
		"ADD     R1, R2, #0\n"
		"ORR     R3, R4, #0x400\n"
		"BL      sub_FFC17450\n"
		"TST     R0, #1\n"
		"CMPNE   R0, #0x15\n"
		"STR     R0, [R10,R4,LSL#2]\n"
		"BEQ     loc_FFC370C8\n"
		"LDR     R1, =0x2AF\n"

"loc_FFC3733C:\n" // only from 0xFFC37180
		"LDR     R0, =0xFFC3734C\n"
		"BL      sub_FFC0B048\n"	// DebugAssert: JogDial.c: 571
		"B       loc_FFC370C8\n"
		
"loc_FFC3737C:\n"
		"LDR     R1, =0xFFE9A7D0\n"
		"LDR     R0, [SP,#0x28]\n"
		"LDR     R0, [R1,R0,LSL#2]\n"
		"STR     R7, [R0]\n"
		"LDR     R0, [SP,#0x24]\n"
		"MOV     R1, #1\n"
		"B       loc_FFC37140\n"

"loc_FFC37398:\n"
		"LDR     R0, [R9,R4,LSL#2]\n"
		"CMP     R0, #0\n"
		"MOVEQ   R1, #0x2BC\n"
		"lDREQ   R0, =0xFFC3734C\n"
		"BLEQ    sub_FFC0B048\n"	// DebugAssert: JogDial.c:700
		"ADD     R0, R4, R4,LSL#1\n"
		"ADD     R0, R8, R0,LSL#2\n"
		"LDR     R0, [R0,#4]\n"
		"BL      sub_FFC65B38\n"
		"STR     R7, [R9,R4,LSL#2]\n"
		"B       loc_FFC370C8\n"

 );
}

