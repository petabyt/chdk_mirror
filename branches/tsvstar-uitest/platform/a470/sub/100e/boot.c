#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

void boot();

void taskCreateHook(int *p) { //function taken from the ixus80 port, adapted of course
 p-=16;
 if (p[0]==0xffc900b8)  p[0]=(int)exp_drv_task; //100e ok
} 

void boot() { //#fs
    long *canon_data_src = (void*)0xFFEAB38C; //found with "romdata start" string
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xEBA8 - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xEBA8; // just after data 
    long canon_bss_len = 0xA5718 - 0xEBA8; // found using heapstart 

    long i;

    // Code taken from VxWorks CHDK. Changes CPU speed?
    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
	canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
	canon_bss_start[i]=0;

    *(int*)0x1930=(int)taskCreateHook; //from ixus80 port
    *(int*)0x1934=(int)taskCreateHook; //from ixus80 port (was taskCreateHook2...)

/*    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"BIC     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");
*/

    // jump to init-sequence that follows the data-copy-routine 
    asm volatile ("B      sub_FFC001a4_my\n");
}; //#fe


// init
void __attribute__((naked,noinline)) sub_FFC001a4_my() { //#fs 
        asm volatile (
                "LDR     R0, =0xFFC0021C\n"
                "MOV     R1, #0\n"
                "LDR     R3, =0xFFC00254\n"
        "loc_FFC001B0:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FFC001B0\n"
                "LDR     R0, =0xFFC00254\n"
                "MOV     R1, #0x4B0\n"
                "LDR     R3, =0xFFC00468\n"
        "loc_FFC001CC:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FFC001CC\n"
                "MOV     R0, #0xD2\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "MOV     R0, #0xD3\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"			
                "LDR     R0, =0xFFC00210\n"
                "LDR     R2, =0xEEEEEEEE\n"
                "MOV     R3, #0x1000\n"
        "loc_FFC00200:\n"
                "CMP     R0, R3\n"
                "STRCC   R2, [R0],#4\n"
                "BCC     loc_FFC00200\n"
                //"BL      sub_FFC00FA0\n"
                "BL      sub_FFC00FA0_my\n"
        );
} //#fe

void __attribute__((naked,noinline)) sub_FFC00FA0_my() { //#fs 
        asm volatile (
              //"STR     LR, [SP,#0xFFFFFFFC]!\n"
              "STR     LR, [SP,#-4]!\n"         // inspired by original CHDK-code
              "SUB     SP, SP, #0x74\n"
              "MOV     R0, SP\n"
              "MOV     R1, #0x74\n"
              "BL      sub_FFE4E264\n"
              "MOV     R0, #0x53000\n"
              "STR     R0, [SP,#0x74-0x70]\n"
        );
//              "LDR     R0, =0xA5718\n"    
        asm volatile (
              "LDR     R0, =new_sa\n"
              "LDR     R0, [R0]\n"
        );
        asm volatile (
              "LDR     R2, =0x279C00\n"
              "LDR     R1, =0x272968\n"
              "STR     R0, [SP,#0x74-0x6C]\n"
              "SUB     R0, R1, R0\n"
              "ADD     R3, SP, #0x74-0x68\n"
              "STR     R2, [SP,#0x74-0x74]\n"
              "STMIA   R3, {R0-R2}\n"
              "MOV     R0, #0x22\n"
              "STR     R0, [SP,#0x74-0x5C]\n"
              "MOV     R0, #0x68\n"
              "STR     R0, [SP,#0x74-0x58]\n"
              "LDR     R0, =0x19B\n"
              "MOV     R1, #0x64\n"
              //"STRD     R0, [SP,#0x74-0x54]\n"        // "strd not supported by cpu" claims gcc
              "STR      R0, [SP,#0x74-0x54]\n"          // split in two single-word STRs
              "STR      R1, [SP,#0x74-0x50]\n"
              "MOV     R0, #0x78\n"
              //"STRD     R0, [SP,#0x74-0x4C]\n"        // "strd not supported by cpu" claims gcc
              "STR      R0, [SP,#0x74-0x4C]\n"          // split in two single-word STRs
              "STR      R1, [SP,#0x74-0x48]\n"
              "MOV     R0, #0\n"
              "STR     R0, [SP,#0x74-0x44]\n"
              "STR     R0, [SP,#0x74-0x40]\n"
              "MOV     R0, #0x10\n"
              "STR     R0, [SP,#0x74-0x18]\n"
              "MOV     R0, #0x800\n"
              "STR     R0, [SP,#0x74-0x14]\n"
              "MOV     R0, #0xA0\n"
              "STR     R0, [SP,#0x74-0x10]\n"
              "MOV     R0, #0x280\n"
              "STR     R0, [SP,#0x74-0x0C]\n"
              //"LDR     R1, =0xFFC04DA4\n"         // uHwSetup 
              "LDR     R1, =uHwSetup_my\n"         // followup to own function
              "MOV     R0, SP\n"
              "MOV     R2, #0\n"
              "BL      sub_FFC02D58\n"
              "ADD     SP, SP, #0x74\n"
              "LDR     PC, [SP],#4\n"
        );
}; //#fe

void __attribute__((naked,noinline)) uHwSetup_my() { //#fs 
        asm volatile (
              "STMFD   SP!, {R4,LR}\n"
              "BL      sub_FFC0094C\n"
              "BL      sub_FFC0972C\n"          // _dmSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EB8\n"       // aDmsetup
              "BLLT    sub_FFC04E98\n"          // _err_init_task
              "BL      sub_FFC049C8\n"          // _termDriverInit
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EC0\n"       // aTermdriverinit
              "BLLT    sub_FFC04E98\n"          // _err_init_task
              "LDR     R0, =0xFFC04ED0\n"       // a_term
              "BL      sub_FFC04AB4\n"          // _termDeviceCreate
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04ED8\n"       // aTermdevicecrea
              "BLLT    sub_FFC04E98\n"          // _err_init_task
              "LDR     R0, =0xFFC04ED0\n"       // a_term
              "BL      sub_FFC03564\n"          // _stdioSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EEC\n"       // aStdiosetup
              "BLLT    sub_FFC04E98\n"          // _err_init_task
              "BL      sub_FFC092B4\n"          // _stdlibSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EF8\n"       // aStdlibsetup
              "BLLT    sub_FFC04E98\n"          // _err_init_task
              "BL      sub_FFC014B8\n"          // _armlib_setup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04F04\n"       // aArmlib_setup
              "BLLT    sub_FFC04E98\n"          // _err_init_task
              "LDMFD   SP!, {R4,LR}\n"
              //"B       _CreateTaskStartup\n"   // FFC0CD84
              "B       CreateTask_Startup_my\n"
        );
}; //#fe

void __attribute__((naked,noinline)) CreateTask_Startup_my() { //#fs 
        asm volatile (
                "STMFD   SP!, {R3,LR}\n"
                //"BL      nullsub_201\n"
                "BL      sub_FFC1978C\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC0CDB4\n"
				"BL      sub_FFC119C0\n"
				"CMP     R0, #0\n"
                "BNE     loc_FFC0CDB4\n"
				"LDR     R1, =0xC0220000\n"
                "MOV     R0, #0x44\n"
                "STR     R0, [R0,#0xA0]\n"
        "loc_FFC0CDB0:\n"
                "B       loc_FFC0CDB0\n"
        "loc_FFC0CDB4:\n"
                //"BL      nullsub_203\n"
                //"BL      nullsub_202\n"
                "BL      sub_FFC17B14\n"
                "LDR     R1, =0x2CE000\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC17D5C\n"
                "BL      sub_FFC17D08\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP,#8-8]\n"
                //"LDR     R3, =0xFFC0CD28\n"    // Startup
                "LDR     R3, =task_Startup_my\n"      // followup to own function
                "MOV     R2, #0\n"
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFFC0CDFC\n"      // aStartup
                "BL      sub_FFC0B8E0\n"         // CreateTask
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) task_Startup_my() { //#fs 
                asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC051BC\n"  // uRegClockSave
                "BL      sub_FFC12B1C\n"
                "BL      sub_FFC0FDFC\n"
                "BL      sub_FFC197CC\n"
                "BL      sub_FFC19994\n"
                //"BL      sub_FFC19854\n"  // StartDiskboot
        );

        CreateTask_spytask();

        asm volatile (
                "BL      sub_FFC19B48\n"
                "BL      sub_FFC199E4\n"        
			
                "BL      sub_FFC17054\n"
                "BL      sub_FFC19B4C\n"
        );

        CreateTask_PhySw();

        asm volatile (
                //"BL      sub_FFC118D8\n"        // CreateTask_PhySw - checks buttons and acts accordingly
                "BL      sub_FFC14A18_my\n"        // divert to intercept task_ShootSeqTask
                "BL      sub_FFC19B64\n"
                //"BL      nullsub_2\n"
                "BL      sub_FFC10DAC\n"
                "BL      sub_FFC19554\n"		// taskCreate_bye
                "BL      sub_FFC11408\n"
                "BL      sub_FFC10CAC\n"
                //"BL      sub_FFC1A4CC\n"
                "BL      sub_FFC1A4CC_my\n"     // divert for SDHC-bootdisk-support
                "BL      sub_FFC10C68\n"

                // modification: BL instead of B to last function to control action after its return
                "BL       sub_FFC05070\n"
                "LDMFD   SP!, {R4,PC}\n"        // restore stack to PC instead of LR to return to caller
        );
}; //#fe

void CreateTask_spytask() { //#fs 
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; //#fe

void CreateTask_PhySw() { //#fs 
        _CreateTask("PhySw", 0x18, 0x800, mykbd_task, 0);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC14A18_my() { //#fs 
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x1C04\n"
                "MOV     R0, #0\n"
                "MOV     R1, #4\n"
                "STR     R0, [R4,#0xC]\n"
                "BL      sub_FFC0BC10\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #1\n"
                "BL      sub_FFC0BC34\n"
                "STR     R0, [R4,#8]\n"
                "BL      sub_FFC4B714\n"
				"BL		 sub_FFC4C8E8\n"
                "BL      sub_FFC4A828\n"
				//"BL		 sub_FFC47814\n"
                "BL      sub_FFC47814_my\n"     // divert this for ShootSeqTask
                "BL      sub_FFC4B9D4\n"
                "LDR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,LR}\n"
                "MOV     R1, #0x1000\n"
                "B       sub_FFC173B8\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC47814_my() { //#fs 
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x5298\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC47880\n"
                //"BL      nullsub_5\n"
                "MOV     R1, #1\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BC34\n"
                "STR     R0, [R4,#0xC]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC0BC10\n"
                "STR     R0, [R4,#0x10]\n"
                "BL      sub_FFC47B10\n"
                "BL      sub_FFC48060\n"   // continue here for task_ShootSeqTask (this is nonsense. We just need CaptSeqTask)
                "MOV     R0, #0\n"			
                "STR     R0, [R4,#0x8]\n"
                "ADD     R0, R4, #0x14\n"
                "MOV     R1, #0\n"
                "STR     R1, [R0],#4\n"
                "STR     R1, [R0]\n"
                "BL      sub_FFC48200\n"
                "BL      sub_FFC4BB80\n"
                "BL      sub_FFC4A1F8\n"
				//"BL      sub_FFC48B2C\n"
                "BL      sub_FFC48B2C_my\n"     // continue here for task_CaptSeqTask
                "BL      sub_FFC49D40\n"
        "loc_FFC47880:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC48B2C_my() { //#fs  // CreateTask_CaptSeqTask
        asm volatile (
                "STMFD   SP!, {R3-R5,LR}\n"
                "LDR     R2, =0x1961C\n"
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
        "loc_FFC48B3C:\n"
                "ADD     R3, R2, R0,LSL#4\n"
                "ADD     R0, R0, #1\n"
                "CMP     R0, #5\n"
                "STR     R1, [R3,#8]\n"
                "BCC     loc_FFC48B3C\n"			
                "BL      sub_FFD0B9C0\n"
                "BL      sub_FFD0D598\n"				
                "MOV     R1, #5\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BBEC\n"
                "LDR     R4, =0x52D0\n"
                "LDR     R1, =0x1001FF\n"
                "STR     R0, [R4,#8]\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BC10\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #1\n"
				"BL      sub_FFC0BC34\n"
				"STR     R0, [R4,#0xC]\n"
                "MOV     R3, #0\n"
                //"STR     R3, [SP,#0x10+var_10]\n"
                "STR     R3, [SP]\n"
                //"LDR     R3, =0xFFC488A4\n"           // task_CaptSeqTask
                "LDR     R3, =task_CaptSeqTask_my\n"            // task_CaptSeqTask
                "LDR     R0, =0xFFC48C60\n"             // aCaptseqtask ; "CaptSeqTask"
                "MOV     R2, #0x1000\n"
                "MOV     R1, #0x17\n"
                "BL      sub_FFC0BBB8\n"                // uKernelMiscCreateTask o. CreateTaskStrict
                "LDMFD   SP!, {R3-R5,PC}\n"
        ".ltorg\n"
        );
}; //#fe

// -----------------
// SDHC-Boot-Support
// -----------------
// Required subs:
//   Startup -> FFC1A4CC -> FFC1A080 -> FFC5DFE0 -> uAC_Boot -> CreateTask_InitFileModules -> task_InitFileModules -> FFC577C0 -> FFC3CA60 -> FFC3C380 -> FFC3C62C
//                           \->FFC5E924 -> FFC5F410 ->/|
//                   -> StartFactoryModeController =>||
//
// uAC_Boot:                   FFC5D48C
// CreateTask_InitFileModules: FFC5EC48 
// task_InitFileModules:       FFC5F754 


void __attribute__((naked,noinline)) sub_FFC1A4CC_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC5BFB4\n"
                "BL      sub_FFC33B48\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC1A4EC\n"
                "BL      sub_FFC5ED54\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFC33BB8\n"
"loc_FFC1A4EC:\n"
                "BL      sub_FFC5DD9C\n"
                "LDR     R4, =0x1D18\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "LDMNEFD SP!, {R4,PC}\n"
                "MOV     R1, #0\n"
                "LDR     R0, =sub_FFC1A080_my\n" //------->
                "BL      sub_FFC5A41C\n"
                "STR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC1A080_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R3-R11,LR}\n"
                "LDR     R6, =0x1D18\n"
                "MOV     R5, R1\n"
                "LDR     R0, [R6,#0x14]\n"
                "MOV     R4, R3\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC1A0A4\n"
                "BL      sub_FFC5C7D8\n"
                "B       loc_FFC1A13C\n"
"loc_FFC1A0A4:\n"
                "LDR     R11, =0x1167\n"
                "MOV     R7, #0\n"
                "SUB     R12, R11, #5\n"
                "CMP     R5, R12\n"
                "MOV     R9, #1\n"
                "BEQ     loc_FFC1A3D8\n"
                "BGT     loc_FFC1A1D4\n"
                "LDR     R3, =0x1063\n"
                "CMP     R5, R3\n"
                "SUB     LR, R3, #0xD\n"
                "SUB     R1, R3, #8\n"
                "SUB     R8, R3, #5\n"
                "SUB     R2, R3, #2\n"
                "SUB     R0, R3, #1\n"
                "BEQ     loc_FFC1A470\n"
                "BGT     loc_FFC1A15C\n"
                "CMP     R5, LR\n"
                "BEQ     loc_FFC1A470\n"
                "BGT     loc_FFC1A144\n"
                "SUB     R12, R5, #0x800\n"
                "SUBS    R12, R12, #3\n"
                "BEQ     loc_FFC1A2F4\n"
                "SUB     R12, R5, #0x800\n"
                "SUBS    R12, R12, #0x144\n"
                "BEQ     loc_FFC1A4A8\n"
                "SUB     R12, R5, #0x900\n"
                "SUBS    R12, R12, #0xA3\n"
                "SUBNE   R12, R5, #0x900\n"
                "SUBNES  R12, R12, #0xA5\n"
                "BNE     loc_FFC1A4C4\n"
                "LDR     R0, [R6,#0xC]\n"
                "SUB     R12, R0, #0x8000\n"
                "SUBS    R12, R12, #2\n"
                "BEQ     loc_FFC1A13C\n"
                "LDR     R0, =0x10A5\n"
                "BL      sub_FFC5B294\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC1A4C4\n"
"loc_FFC1A13C:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
"loc_FFC1A144:\n"
                "CMP     R5, R1\n"
                "CMPNE   R5, R8\n"
                "CMPNE   R5, R2\n"
                "CMPNE   R5, R0\n"
                "BNE     loc_FFC1A4C4\n"
                "B       loc_FFC1A470\n"
"loc_FFC1A15C:\n"
                "LDR     R12, =0x10AE\n"
                "CMP     R5, R12\n"
                "BEQ     loc_FFC1A40C\n"
                "BGT     loc_FFC1A1A4\n"
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0x65\n"
                "BEQ     loc_FFC1A470\n"
                "SUB     R12, R5, #0x1000\n"
                "LDR     R0, =0x10A3\n"
                "SUBS    R12, R12, #0xA9\n"
                "BEQ     loc_FFC1A3E8\n"
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0xAA\n"
                "BEQ     loc_FFC1A400\n"
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0xAD\n"
                "BNE     loc_FFC1A4C4\n"
                "B       loc_FFC1A3F4\n"
"loc_FFC1A1A4:\n"
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0xAF\n"
                "BEQ     loc_FFC1A3F4\n"
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0xB0\n"
                "BEQ     loc_FFC1A40C\n"
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0xB2\n"
                "BNE     loc_FFC1A4C4\n"
                "LDR     R0, =0x1008\n"
                "MOV     R1, R4\n"
                "B       loc_FFC1A3D0\n"
"loc_FFC1A1D4:\n"
                "LDR     R10, =0x201B\n"
                "LDR     R0, =0x1D18\n"
                "CMP     R5, R10\n"
                "LDR     R2, [R0,#0x10]!\n"
                "LDR     R1, [R0,#0x10]\n"
                "SUB     R8, R10, #0x17\n"
                "BEQ     loc_FFC1A3AC\n"
                "BGT     loc_FFC1A290\n"
                "LDR     R10, =0x116A\n"
                "CMP     R5, R10\n"
                "BEQ     loc_FFC1A398\n"
                "BGT     loc_FFC1A24C\n"
                "SUB     R12, R5, #0x1100\n"
                "SUBS    R12, R12, #0x63\n"
                "MOVEQ   R1, #0\n"
                "MOVEQ   R0, #0x82\n"
                "BEQ     loc_FFC1A3C4\n"
                "SUB     R12, R5, #0x1100\n"
                "SUBS    R12, R12, #0x65\n"
                "BEQ     loc_FFC1A3BC\n"
                "LDR     R4, =0x1168\n"
                "CMP     R5, R11\n"
                "CMPNE   R5, R4\n"
                "BNE     loc_FFC1A4C4\n"
                "STR     R9, [R6,#0x10]\n"
                "LDR     R6, =0x4508\n"
                "CMP     R1, #0\n"
                "BEQ     loc_FFC1A380\n"
                "BL      sub_FFC5C80C\n"
                "B       loc_FFC1A38C\n"
"loc_FFC1A24C:\n"
                "SUB     R12, R5, #0x2000\n"
                "SUBS    R12, R12, #2\n"
                "BEQ     loc_FFC1A43C\n"
                "CMP     R5, R8\n"
                "MOV     R0, R8\n"
                "BEQ     loc_FFC1A448\n"
                "SUB     R12, R5, #0x2000\n"
                "SUBS    R12, R12, #5\n"
                "BEQ     loc_FFC1A43C\n"
                "SUB     R12, R5, #0x2000\n"
                "SUBS    R12, R12, #0x19\n"
                "BNE     loc_FFC1A4C4\n"
                "CMP     R1, #0\n"
                "BEQ     loc_FFC1A13C\n"
                "CMP     R2, #0\n"
                "BNE     loc_FFC1A13C\n"
                "B       loc_FFC1A4A0\n"
"loc_FFC1A290:\n"
                "LDR     R12, =0x3111\n"
                "CMP     R5, R12\n"
                "BEQ     loc_FFC1A410\n"
                "BGT     loc_FFC1A2D0\n"
                "SUB     R12, R5, #0x2000\n"
                "SUBS    R12, R12, #0x1D\n"
                "BEQ     loc_FFC1A43C\n"
                "LDR     R0, =0x2027\n"
                "CMP     R5, R0\n"
                "BEQ     loc_FFC1A418\n"
                "SUB     R12, R5, #0x3000\n"
                "SUBS    R12, R12, #6\n"
                "SUBNE   R12, R5, #0x3000\n"
                "SUBNES  R12, R12, #0x110\n"
                "BNE     loc_FFC1A4C4\n"
                "B       loc_FFC1A410\n"
"loc_FFC1A2D0:\n"
                "CMP     R5, #0x3140\n"
                "BEQ     loc_FFC1A464\n"
                "SUB     R12, R5, #0x3200\n"
                "SUBS    R12, R12, #1\n"
                "BEQ     loc_FFC1A4C4\n"
                "SUB     R12, R5, #0x3200\n"
                "SUBS    R12, R12, #2\n"
                "BNE     loc_FFC1A4C4\n"
                "B       loc_FFC1A410\n"
"loc_FFC1A2F4:\n"
                "MOV     R4, #1\n"
                "MOV     R0, #2\n"
                "BL      sub_FFC5C048\n"
                "CMP     R0, #1\n"
                "MOVEQ   R4, #2\n"
                "MOV     R0, R4\n"
                "BL      sub_FFC11030\n"
                "CMP     R0, #0\n"
                "STRNE   R9, [R6,#0x14]\n"
                "BNE     loc_FFC1A34C\n"
                "BL      sub_FFC61810\n"
                "BL      sub_FFC5F6AC\n"
                "BL      sub_FFC601B0\n"
                "BL      sub_FFC5EFFC\n"
                "BL      sub_FFC60808\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC1A354\n"
                "BL      sub_FFC19DA4\n"
                "BL      sub_FFC6076C\n"
                "MOV     R1, R0\n"
                "MOV     R0, R11\n"
                "BL      sub_FFC5AC24\n"
"loc_FFC1A34C:\n"
                "MOV     R0, R7\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
"loc_FFC1A354:\n"
                "BL      sub_FFC1507C\n"
                "CMP     R0, #1\n"
                "LDRNE   R0, =0x310B\n"
                "LDREQ   R0, =0x310C\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC5AC24\n"
                "BL      sub_FFC5E924_my\n"  // Continue here (possibility 1) for SDHC-boot
                "B       loc_FFC1A34C\n"
"loc_FFC1A374:\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC46100\n"
                "B       loc_FFC1A13C\n"
"loc_FFC1A380:\n"
                "BL      sub_FFC5F924\n"
                "BL      sub_FFC5F888\n"
                "BL      sub_FFC14D5C\n"
"loc_FFC1A38C:\n"
                "CMP     R5, R4\n"
                "BNE     loc_FFC1A13C\n"
                "B       loc_FFC1A374\n"
"loc_FFC1A398:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFC5C938\n"
                "LDR     R0, =0x1005\n"
                "MOV     R1, R10\n"
                "B       loc_FFC1A3D0\n"
"loc_FFC1A3AC:\n"
                "CMP     R2, #1\n"
                "BNE     loc_FFC1A410\n"
                "BL      sub_FFC5C80C\n"
                "B       loc_FFC1A13C\n"
"loc_FFC1A3BC:\n"
                "MOV     R1, #0\n"
                "MOV     R0, #0x83\n"
"loc_FFC1A3C4:\n"
                "BL      sub_FFC60288\n"
                "B       loc_FFC1A13C\n"
"loc_FFC1A3CC:\n"
                "MOV     R0, R5\n"
"loc_FFC1A3D0:\n"
                "BL      sub_FFC5DAC4_my\n"  // Continue here (possibility 2) for SDHC-boot
                "LDMFD   SP!, {R3-R11,PC}\n"
"loc_FFC1A3D8:\n"
                "BL      sub_FFC637A8\n"
                "CMP     R0, #0\n"
                "BLNE    sub_FFC626DC\n"
                "B       loc_FFC1A410\n"
"loc_FFC1A3E8:\n"
                "BL      sub_FFC5B294\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC1A13C\n"
"loc_FFC1A3F4:\n"
                "MOV     R0, R5\n"
                "BL      sub_FFC19E70\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
"loc_FFC1A400:\n"
                "BL      sub_FFC5B294\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC1A13C\n"
"loc_FFC1A40C:\n"
                "BL      sub_FFC1A8CC\n"
"loc_FFC1A410:\n"
                "MOV     R1, R4\n"
                "B       loc_FFC1A3CC\n"
"loc_FFC1A418:\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC5DAC4_my\n"  // Continue here (possibility 2) for SDHC-boot
                "MOV     R1, #0\n"
                "MOV     R0, R10\n"
                "BL      sub_FFC5DAC4_my\n"  // Continue here (possibility 2) for SDHC-boot
                "MOV     R1, #0\n"
                "MOV     R0, R8\n"
"loc_FFC1A434:\n"
                "BL      sub_FFC5DAC4_my\n"  // Continue here (possibility 2) for SDHC-boot
                "B       loc_FFC1A13C\n"
"loc_FFC1A43C:\n"
                "STR     R7, [R6,#0x20]\n"
                "BL      sub_FFC1A690\n"
                "B       loc_FFC1A410\n"
"loc_FFC1A448:\n"
                "STR     R7, [R6,#0x20]\n"
                "BL      sub_FFC1A690\n"
                "LDR     R0, [R6,#0x10]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC1A410\n"
                "BL      sub_FFC5C850\n"
                "B       loc_FFC1A13C\n"
"loc_FFC1A464:\n"
                "CMP     R1, #0\n"
                "BLEQ    sub_FFC1A690\n"
                "B       loc_FFC1A13C\n"
"loc_FFC1A470:\n"
                "CMP     R5, R2\n"
                "MOVEQ   R0, R2\n"
                "BEQ     loc_FFC1A4A0\n"
                "BGT     loc_FFC1A490\n"
                "CMP     R5, LR\n"
                "CMPNE   R5, R8\n"
                "BEQ     loc_FFC1A4A0\n"
                "B       loc_FFC1A49C\n"
"loc_FFC1A490:\n"
                "CMP     R5, R0\n"
                "CMPNE   R5, R3\n"
                "BEQ     loc_FFC1A4A0\n"
"loc_FFC1A49C:\n"
                "MOV     R0, R1\n"
"loc_FFC1A4A0:\n"
                "MOV     R1, #0\n"
                "B       loc_FFC1A434\n"
"loc_FFC1A4A8:\n"
                "TST     R4, #0x80000000\n"
                "MOVNE   R0, #1\n"
                "LDMNEFD SP!, {R3-R11,PC}\n"
                "BL      sub_FFC64C74\n"
                "CMP     R0, #0\n"
                "BLEQ    sub_FFC16F6C\n"
                "B       loc_FFC1A13C\n"
"loc_FFC1A4C4:\n"
                "MOV     R1, #0\n"
                "B       loc_FFC1A3CC\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5E924_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC1A644\n"
                "CMP     R0, #0\n"
                "LDRNE   R0, =0x1061\n"
                "BNE     loc_FFC5E94C\n"
                "BL      sub_FFC1A62C\n"
                "CMP     R0, #0\n"
                "LDRNE   R0, =0x105B\n"
                "BNE     loc_FFC5E94C\n"
                "BL      sub_FFC1A65C\n"
"loc_FFC5E94C:\n"
                "MOV     R4, R0\n"
                "BL      sub_FFC5EAAC\n"
                "MOV     R0, R4\n"
                "BL      sub_FFC5EB4C\n"
                "LDR     R0, =0x581C\n"
                "LDR     R0, [R0]\n"
                "TST     R0, #1\n"
                "TSTEQ   R0, #0x10\n"
                "BEQ     loc_FFC5E97C\n"
"loc_FFC5E970:\n"
                "MOV     R1, R4\n"
                "MOV     R0, #2\n"
                "B       loc_FFC5E9C0\n"
"loc_FFC5E97C:\n"
                "TST     R0, #0x40\n"
                "BEQ     loc_FFC5E990\n"
"loc_FFC5E984:\n"
                "MOV     R1, R4\n"
                "MOV     R0, #1\n"
                "B       loc_FFC5E9C0\n"
"loc_FFC5E990:\n"
                "TST     R0, #0x20\n"
                "BEQ     loc_FFC5E9AC\n"
                "TST     R0, #0x4000\n"
                "BNE     loc_FFC5E9AC\n"
"loc_FFC5E9A0:\n"
                "MOV     R1, R4\n"
                "MOV     R0, #0\n"
                "B       loc_FFC5E9C0\n"
"loc_FFC5E9AC:\n"
                "LDR     R1, =0x102\n"
                "BICS    R1, R1, R0\n"
                "BNE     loc_FFC5E9C8\n"
                "MOV     R1, R4\n"
                "MOV     R0, #6\n"
"loc_FFC5E9C0:\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFC5E8C0_my\n"  // cont. for SDHC-boot
"loc_FFC5E9C8:\n"
                "TST     R0, #0x100\n"
                "BNE     loc_FFC5E970\n"
                "TST     R0, #0x400\n"
                "BNE     loc_FFC5E984\n"
                "TST     R0, #0x200\n"
                "TSTEQ   R0, #2\n"
                "BNE     loc_FFC5E9A0\n"
                "TST     R0, #0x40000\n"
                "BEQ     loc_FFC5E970\n"
                "TST     R0, #0x200000\n"
                "MOVEQ   R1, R4\n"
                "MOVEQ   R0, #1\n"
                "BLEQ    sub_FFC5E8C0_my\n"  // cont. for SDHC-boot
                "B       loc_FFC5E970\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5E8C0_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOVS    R4, R0\n"
                "MOV     R0, #1\n"
                "MOV     R5, R1\n"
                "BNE     loc_FFC5E900\n"
                "MOV     R1, #0\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC5BFD8\n"
                "BL      sub_FFC1A65C\n"
                "SUB     R12, R0, #0x1000\n"
                "SUBS    R12, R12, #0x5B\n"
                "BNE     loc_FFC5E8F8\n"
"loc_FFC5E8F0:\n"
                "BL      sub_FFC5E7F4\n"
                "B       loc_FFC5E908\n"
"loc_FFC5E8F8:\n"
                "BL      sub_FFC5E854\n"
                "B       loc_FFC5E908\n"
"loc_FFC5E900:\n"
                "CMP     R4, #5\n"
                "BEQ     loc_FFC5E8F0\n"
"loc_FFC5E908:\n"
                "CMP     R0, #0\n"
                "LDREQ   R5, =0x1162\n"
                "MOVEQ   R4, #2\n"
                "MOV     R0, R4\n"
                "MOV     R1, R5\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FFC5DAC4_my\n" //------>
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5DAC4_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "MOV     R7, R1\n"
                "MOV     R6, R0\n"
                "BL      sub_FFC60808\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5DD94\n"
                "MOV     R1, R7\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC5CB08\n"
                "LDR     R4, =0x5760\n"
                "MOV     R5, #0\n"
                "LDR     R0, [R4,#0x10]\n"
                "CMP     R0, #0x16\n"
                "ADDLS   PC, PC, R0,LSL#2\n"
                "B       loc_FFC5DD94\n"
"loc_FFC5DB00:\n"
                "B       loc_FFC5DB5C\n"
"loc_FFC5DB04:\n"
                "B       loc_FFC5DB78\n"
"loc_FFC5DB08:\n"
                "B       loc_FFC5DBAC\n"
"loc_FFC5DB0C:\n"
                "B       loc_FFC5DC5C\n"
"loc_FFC5DB10:\n"
                "B       loc_FFC5DC6C\n"
"loc_FFC5DB14:\n"
                "B       loc_FFC5DD94\n"
"loc_FFC5DB18:\n"
                "B       loc_FFC5DD94\n"
"loc_FFC5DB1C:\n"
                "B       loc_FFC5DCF0\n"
"loc_FFC5DB20:\n"
                "B       loc_FFC5DB6C\n"
"loc_FFC5DB24:\n"
                "B       loc_FFC5DD94\n"
"loc_FFC5DB28:\n"
                "B       loc_FFC5DCF0\n"
"loc_FFC5DB2C:\n"
                "B       loc_FFC5DBA0\n"
"loc_FFC5DB30:\n"
                "B       loc_FFC5DD94\n"
"loc_FFC5DB34:\n"
                "B       loc_FFC5DD94\n"
"loc_FFC5DB38:\n"
                "B       loc_FFC5DBB8\n"
"loc_FFC5DB3C:\n"
                "B       loc_FFC5DBC4\n"
"loc_FFC5DB40:\n"
                "B       loc_FFC5DC34\n"
"loc_FFC5DB44:\n"
                "B       loc_FFC5DB84\n"
"loc_FFC5DB48:\n"
                "B       loc_FFC5DD7C\n"
"loc_FFC5DB4C:\n"
                "B       loc_FFC5DCFC\n"
"loc_FFC5DB50:\n"
                "B       loc_FFC5DD2C\n"
"loc_FFC5DB54:\n"
                "B       loc_FFC5DD2C\n"
"loc_FFC5DB58:\n"
                "B       loc_FFC5DC78\n"
"loc_FFC5DB5C:\n"
                "MOV     R1, R7\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5D48C_my\n"  // uAC_Boot // divert for SDHC-boot
"loc_FFC5DB6C:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5E4C0\n"
"loc_FFC5DB78:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5D12C\n"
"loc_FFC5DB84:\n"
                "SUB     R12, R6, #0x3000\n"
                "SUBS    R12, R12, #6\n"
                "BNE     loc_FFC5DD94\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC19C3C\n"
                "BL      sub_FFC5E3BC\n"
                "B       loc_FFC5DD8C\n"
"loc_FFC5DBA0:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5E3F4\n"
"loc_FFC5DBAC:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5D2BC\n"
"loc_FFC5DBB8:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5D864\n"
"loc_FFC5DBC4:\n"
                "SUB     R12, R6, #0x3200\n"
                "SUBS    R12, R12, #2\n"
                "BNE     loc_FFC5DD94\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC5CA14\n"
                "MOV     R0, #8\n"
                "BL      sub_FFC19B9C\n"
                "MOV     R1, #0\n"
                "MOV     R0, #0x19\n"
                "BL      sub_FFC2795C\n"
                "BL      sub_FFC5F924\n"
                "BL      sub_FFC5FBBC\n"
                "BL      sub_FFC5F06C\n"
                "B       loc_FFC5DD8C\n"
"loc_FFC5DC34:\n"
                "SUB     R12, R6, #0x3300\n"
                "SUBS    R12, R12, #1\n"
                "BNE     loc_FFC5DD94\n"
                "LDR     R0, =0x4010\n"
                "BL      sub_FFC19B9C\n"
                "BL      sub_FFD5A3CC\n"
                "BL      sub_FFC5F06C\n"
                "MOV     R0, #4\n"
                "BL      sub_FFC5CA14\n"
                "B       loc_FFC5DD8C\n"
"loc_FFC5DC5C:\n"
                "MOV     R1, R7\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5D9C0\n"
"loc_FFC5DC6C:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5E604\n"
"loc_FFC5DC78:\n"
                "LDR     R7, =0x1182\n"
                "MOV     R0, R6\n"
                "CMP     R0, R7\n"
                "MOV     R6, #1\n"
                "STREQ   R6, [R4,#0xA8]\n"
                "BEQ     loc_FFC5DD8C\n"
                "SUB     R12, R0, #0x1000\n"
                "SUBS    R12, R12, #0x1AC\n"
                "BEQ     loc_FFC5DCD8\n"
                "SUB     R12, R0, #0x3000\n"
                "SUBS    R12, R12, #0x224\n"
                "BNE     loc_FFC5DD94\n"
                "MOV     R0, #8\n"
                "BL      sub_FFC19B9C\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC5CA14\n"
                "STR     R5, [R4,#0xAC]\n"
                "LDR     R0, [R4,#0xA8]\n"
                "CMP     R0, #0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R7\n"
                "STRNE   R5, [R4,#0xA8]\n"
                "BLNE    sub_FFC5D9C0\n"
                "B       loc_FFC5DD8C\n"
"loc_FFC5DCD8:\n"
                "LDR     R0, [R4,#0xAC]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5DD8C\n"
                "BL      sub_FFD582F4\n"
                "STR     R6, [R4,#0xAC]\n"
                "B       loc_FFC5DD8C\n"
"loc_FFC5DCF0:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5D784_my\n"  //----------> movie_rec.c
"loc_FFC5DCFC:\n"
                "LDR     R12, =0x10B0\n"
                "CMP     R6, R12\n"
                "BEQ     loc_FFC5DD28\n"
                "BGT     loc_FFC5DD34\n"
                "CMP     R6, #4\n"
                "BEQ     loc_FFC5DD5C\n"
                "SUB     R12, R6, #0x1000\n"
                "SUBS    R12, R12, #0xAA\n"
                "SUBNE   R12, R6, #0x1000\n"
                "SUBNES  R12, R12, #0xAE\n"
                "BNE     loc_FFC5DD94\n"
"loc_FFC5DD28:\n"
                "BL      sub_FFC5C6F4\n"
"loc_FFC5DD2C:\n"
                "MOV     R0, R5\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC5DD34:\n"
                "SUB     R12, R6, #0x2000\n"
                "SUBS    R12, R12, #4\n"
                "BEQ     loc_FFC5DD74\n"
                "SUB     R12, R6, #0x5000\n"
                "SUBS    R12, R12, #1\n"
                "SUBNE   R12, R6, #0x5000\n"
                "SUBNES  R12, R12, #6\n"
                "BNE     loc_FFC5DD94\n"
                "BL      sub_FFC5D098\n"
                "B       loc_FFC5DD8C\n"
"loc_FFC5DD5C:\n"
                "LDR     R0, [R4,#0x2C]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5DD74\n"
                "BL      sub_FFC5DF50\n"
                "BL      sub_FFC14BF8\n"
                "B       loc_FFC5DD8C\n"
"loc_FFC5DD74:\n"
                "BL      sub_FFC5C730\n"
                "B       loc_FFC5DD8C\n"
"loc_FFC5DD7C:\n"
                "SUB     R12, R6, #0x3000\n"
                "SUBS    R12, R12, #0x130\n"
                "BNE     loc_FFC5DD94\n"
                "BL      sub_FFC5C7D8\n"
"loc_FFC5DD8C:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC5DD94:\n"
                "MOV     R0, #1\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5D48C_my() { //#fs  uAC_Boot
        asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R7, =0x8002\n"
                "LDR     R4, =0x5760\n"
                "CMP     R0, #2\n"
                "MOV     R6, R1\n"
                "MOV     R5, #1\n"
                "BEQ     loc_FFC5D518\n"
                "BGT     loc_FFC5D500\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC5D544\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC5D5DC\n"
                "MOV     R0, #8\n"
                "BL      sub_FFC5CA14\n"
                "BL      sub_FFC5EC84\n"
                "BL      sub_FFC5F78C\n"
                "LDR     R1, =0xFFC5D73C\n"
                "MOV     R0, #0x20\n"
                "BL      sub_FFC542D8\n"
                "BL      sub_FFC5EC48_my\n" //------>
                "BL      sub_FFC5ED54\n"
                "BL      sub_FFC1A5BC\n"
                "LDR     R0, =0x4004\n"
                "BL      sub_FFC19B9C\n"
                "LDR     R0, [R4,#0x68]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5D5BC\n"
                "BL      sub_FFC19D80\n"
                "B       loc_FFC5D5C0\n"
"loc_FFC5D500:\n"
                "CMP     R0, #6\n"
                "STREQ   R5, [R4,#0x28]\n"
                "BEQ     loc_FFC5D5D0\n"
                "SUB     R12, R0, #0x2000\n"
                "SUBS    R12, R12, #4\n"
                "BNE     loc_FFC5D5DC\n"
"loc_FFC5D518:\n"
                "SUB     R12, R6, #0x1100\n"
                "SUBS    R12, R12, #0x62\n"
                "BNE     loc_FFC5D534\n"
                "MOV     R1, R7\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC60288\n"
                "STR     R5, [R4,#0x60]\n"
"loc_FFC5D534:\n"
                "BL      sub_FFC5F924\n"
                "BL      sub_FFC5FBBC\n"
                "BL      sub_FFC5D038\n"
                "B       loc_FFC5D5D4\n"
"loc_FFC5D544:\n"
                "MOV     R0, #7\n"
                "BL      sub_FFC5CA14\n"
                "MOV     R0, R7\n"
                "BL      sub_FFC19B9C\n"
                "BL      sub_FFC5EC84\n"
                "BL      sub_FFC5F78C\n"
                "LDR     R1, =0xFFC5D74C\n"
                "MOV     R0, #0x20\n"
                "STR     R6, [R4,#0x18]\n"
                "BL      sub_FFC542D8\n"
                "LDR     R1, =0xFFC5D758\n"
                "MOV     R0, #0x20\n"
                "BL      sub_FFC542D8\n"
                "STR     R5, [R4,#0x28]\n"
                "BL      sub_FFC19D10\n"
                "BL      sub_FFC19C64\n"
                "LDR     R0, [R4,#0x1C]\n"
                "LDR     R1, [R4,#0x20]\n"
                "ORRS    R0, R0, R1\n"
                "BLNE    sub_FFC5DF2C\n"
                "LDR     R0, [R4,#0x68]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5D5A8\n"
                "BL      sub_FFC19D80\n"
                "B       loc_FFC5D5B0\n"
"loc_FFC5D5A8:\n"
                "BL      sub_FFC14A7C\n"
                "BL      sub_FFC1A5F4\n"
"loc_FFC5D5B0:\n"
                "BL      sub_FFC5EC48_my\n" //------>
                "BL      sub_FFC5ECC0\n"
                "B       loc_FFC5D5D4\n"
"loc_FFC5D5BC:\n"
                "BL      sub_FFC14A7C\n"
"loc_FFC5D5C0:\n"
                "BL      sub_FFC5ECF0\n"
                "LDR     R0, [R4,#0x30]\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC5D5D4\n"
"loc_FFC5D5D0:\n"
                "BL      sub_FFC5DF74\n"
"loc_FFC5D5D4:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC5D5DC:\n"
                "MOV     R0, #1\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5EC48_my() { //#fs  CreateTask_InitFileModules
        asm volatile (
                "LDR     R0, =0x5828\n"
                "STMFD   SP!, {R3,LR}\n"
                "LDR     R1, [R0,#4]\n"
                "CMP     R1, #0\n"
                "BNE     locret_FFC5EC80\n"
                "MOV     R1, #1\n"
                "STR     R1, [R0,#4]\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP,#8-0x8]\n"
                "LDR     R3, =task_InitFileModules_my\n"  // continue for SDHC-boot (orig: FFC5EBF8)
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFFC5EDAC\n"
                "MOV     R2, #0x1000\n"
                "BL      sub_FFC0B8E0\n"
"locret_FFC5EC80:\n"
                "LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "BL      sub_FFC57794\n"
                "LDR     R5, =0x5006\n"
                "MOVS    R4, R0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R5\n"
                "BLNE    sub_FFC5AC24\n"
                "BL      sub_FFC577C0_my\n"  // continue to SDHC-hook here!
				"BL      core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask
                "CMP     R4, #0\n"
                "MOVEQ   R0, R5\n"
                "LDMEQFD SP!, {R4-R6,LR}\n"
                "MOVEQ   R1, #0\n"
                "BEQ     sub_FFC5AC24\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC577C0_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC3C544_my\n"  // continue to SDHC-hook here!
                "LDR     R4, =0x55A8\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC577F0\n"
                "BL      sub_FFC65B88\n"
                "BL      sub_FFCDC234\n"
                "BL      sub_FFC65B88\n"
                "BL      sub_FFC39F34\n"
                "BL      sub_FFC65B98\n"
                "BL      sub_FFCDC300\n"
"loc_FFC577F0:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3C544_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOV     R6, #0\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3C004\n"
                "LDR     R4, =0x11168\n"
                "MOV     R5, #0\n"
                "LDR     R0, [R4,#0x38]\n"
                "BL      sub_FFC3CA38\n"
                "CMP     R0, #0\n"
                "LDREQ   R0, =0x2858\n"
                "STREQ   R5, [R0,#0x10]\n"
                "STREQ   R5, [R0,#0x14]\n"
                "STREQ   R5, [R0,#0x18]\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3C044\n"
                "MOV     R0, R6\n"
				"BL      sub_FFC3C380_my\n"  // continue to SDHC-hook here!
                "MOV     R5, R0\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3C3EC\n"
                "LDR     R1, [R4,#0x3C]\n"
                "AND     R2, R5, R0\n"
                "CMP     R1, #0\n"
                "MOV     R0, #0\n"
                "MOVEQ   R0, #0x80000001\n"
                "BEQ     loc_FFC3C5D8\n"
                "LDR     R3, [R4,#0x2C]\n"
                "CMP     R3, #2\n"
                "MOVEQ   R0, #4\n"
                "CMP     R1, #5\n"
                "ORRNE   R0, R0, #1\n"
                "BICEQ   R0, R0, #1\n"
                "CMP     R2, #0\n"
                "BICEQ   R0, R0, #2\n"
                "ORREQ   R0, R0, #0x80000000\n"
                "BICNE   R0, R0, #0x80000000\n"
                "ORRNE   R0, R0, #2\n"
"loc_FFC3C5D8:\n"
                "STR     R0, [R4,#0x40]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe


void __attribute__((naked,noinline)) sub_FFC3C380_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R5, =0x2858\n"
                "MOV     R6, R0\n"
                "LDR     R0, [R5,#0x14]\n"
                "CMP     R0, #0\n"
                "MOVNE   R0, #1\n"
                "LDMNEFD SP!, {R4-R6,PC}\n"
                "MOV     R0, #0x17\n"
                "MUL     R1, R0, R6\n"
                "LDR     R0, =0x11168\n"
                "ADD     R4, R0, R1,LSL#2\n"
                "LDR     R0, [R4,#0x38]\n"
                "MOV     R1, R6\n"
                "BL      sub_FFC3C110_my\n"  // continue to SDHC-hook here!
                "CMP     R0, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "LDR     R0, [R4,#0x38]\n"
                "MOV     R1, R6\n"
                "BL      sub_FFC3C278\n"
                "CMP     R0, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3BC0C\n"
                "CMP     R0, #0\n"
                "MOVNE   R1, #1\n"
                "STRNE   R1, [R5,#0x14]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3C110_my() { //#fs  ; Partition table parse takes place here. => SDHC-boot
        asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "MOV     R8, R0\n"
                "MOV     R0, #0x17\n"
                "MUL     R1, R0, R1\n"
                "LDR     R0, =0x11168\n"
                "MOV     R6, #0\n"
                "ADD     R7, R0, R1,LSL#2\n"
                "LDR     R0, [R7,#0x3C]\n"
                "MOV     R5, #0\n"
                "CMP     R0, #6\n"
                "ADDLS   PC, PC, R0,LSL#2\n"
                "B       loc_FFC3C25C\n"
"loc_FFC3C140:\n"
                "B       loc_FFC3C174\n"
"loc_FFC3C144:\n"
                "B       loc_FFC3C15C\n"
"loc_FFC3C148:\n"
                "B       loc_FFC3C15C\n"
"loc_FFC3C14C:\n"
                "B       loc_FFC3C15C\n"
"loc_FFC3C150:\n"
                "B       loc_FFC3C15C\n"
"loc_FFC3C154:\n"
                "B       loc_FFC3C254\n"
"loc_FFC3C158:\n"
                "B       loc_FFC3C15C\n"
"loc_FFC3C15C:\n"
                "MOV     R2, #0\n"
                "MOV     R1, #0x200\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC51940\n"
                "MOVS    R4, R0\n"
                "BNE     loc_FFC3C17C\n"
"loc_FFC3C174:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC3C17C:\n"
                "LDR     R12, [R7,#0x4C]\n"
                "MOV     R3, R4\n"
                "MOV     R2, #1\n"
                "MOV     R1, #0\n"
                "MOV     R0, R8\n"
                //"BLX     R12\n"       // !! Workaround !!
                "MOV     LR, PC\n"      // gcc won't compile "BLX R12" nor "BL R12".
                "MOV     PC, R12\n"     // workaround: make your own "BL" and hope we don't need the change to thumb-mode
				
                "CMP     R0, #1\n"
                "BNE     loc_FFC3C1A8\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC51A80\n"
                "B       loc_FFC3C174\n"
"loc_FFC3C1A8:\n"
                "MOV     R0, R8\n"
                "BL      sub_FFCF8D9C\n" // Add FAT32 autodetect-code after this line\n"

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
                "BNE     dg_sd_fat32\n"                // No, it isn't.
                "CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
                "CMPNE   R2, #0x80\n"
                "BNE     dg_sd_fat32\n"                // Invalid, go to next partition
                                                       // This partition is valid, it's the first one, bingo!
                "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.
                
           "dg_sd_fat32_end:\n"
                // End of DataGhost's FAT32 autodetection code
				// Continue with firmware
                "LDRB    R1, [R4,#0x1C9]\n"
                "LDRB    R3, [R4,#0x1C8]\n"
                "LDRB    R12, [R4,#0x1CC]\n"
                "MOV     R1, R1,LSL#24\n"
                "ORR     R1, R1, R3,LSL#16\n"
                "LDRB    R3, [R4,#0x1C7]\n"
                "LDRB    R2, [R4,#0x1BE]\n"
                "LDRB    LR, [R4,#0x1FF]\n"  // replaced, see below
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
                "LDRB    R12, [R4,#0x1FE]\n"  // replaced, see below
                //"LDRB    R12, [LR,#0x1FE]\n"            // New! First MBR signature byte (0x55)
                //"LDRB    LR, [LR,#0x1FF]\n"             //      Last MBR signature byte (0xAA)
                "MOV     R4, #0\n"
                "BNE     loc_FFC3C230\n"
                "CMP     R0, R1\n"
                "BCC     loc_FFC3C230\n"
                "ADD     R2, R1, R3\n"
                "CMP     R2, R0\n"
                "CMPLS   R12, #0x55\n"
                "CMPEQ   LR, #0xAA\n"
                "MOVEQ   R6, R1\n"
                "MOVEQ   R5, R3\n"
                "MOVEQ   R4, #1\n"
"loc_FFC3C230:\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC51A80\n"
                "CMP     R4, #0\n"
                "BNE     loc_FFC3C268\n"
                "MOV     R6, #0\n"
                "MOV     R0, R8\n"
                "BL      sub_FFCF8D9C\n"
                "MOV     R5, R0\n"
                "B       loc_FFC3C268\n"
"loc_FFC3C254:\n"
                "MOV     R5, #0x40\n"
                "B       loc_FFC3C268\n"
"loc_FFC3C25C:\n"
                "MOV     R1, #0x374\n"
                "LDR     R0, =0xFFC3C104\n"
                "BL      sub_FFC0BDB8\n"
"loc_FFC3C268:\n"
                "STR     R6, [R7,#0x44]!\n"
                "MOV     R0, #1\n"
                "STR     R5, [R7,#4]\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        );
}; //#fe


