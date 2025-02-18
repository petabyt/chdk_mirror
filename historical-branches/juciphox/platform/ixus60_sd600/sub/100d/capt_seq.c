#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (2)
#define NR_OFF (1)

static long raw_save_stage;

void capt_seq_hook_raw_here()
{
    raw_save_stage = RAWDATA_AVAILABLE;
    core_rawdata_available();
    while (raw_save_stage != RAWDATA_SAVED){
	_SleepTask(10);
    }
}

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}


void capt_seq_hook_set_nr()
{
    long *nrflag = (long*)0x61B8;   // found at 0xFF962C18

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = 1;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = 2;
	break;
    };
}

void __attribute__((naked,noinline)) sub_FF962C30_my(long p)
{
#if 1
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R3, =0x6F204\n"
                "LDR     R5, =0x61B4\n"
                "SUB     SP, SP, #4\n"
                "MVN     R1, #0\n"          // MOVL    R1, 0xFFFFFFFF
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FE80\n"    // ClearEventFlag
                "LDR     R3, =0x99CC0\n"
                "LDR     R0, [R3,#0x7C]\n"
                "BL      sub_FF89E17C\n"    // IsEmptyWriteCache_42
                "BL      sub_FF962B84\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x61BC\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF89E63C\n"

		"B	 sub_FF962C6C\n"    // ---> finish original function
    );
#endif
}

void __attribute__((naked,noinline)) sub_FF95F788_my(long p)
{
    asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "LDR     R4, [R0,#0xC]\n"
                 "BL      sub_FF967F2C\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF95F7A0\n"
                 "BL      sub_FF967F38\n"   
 "loc_FF95F7A0:\n"
                 "LDR     R3, =0x99CC0\n"
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BNE     loc_FF95F7D4\n"
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF967F4C\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF95F7D4\n"
                 "MOV     R0, #1\n"         
 "loc_FF95F7C4:\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF95DE70\n"   
 "loc_FF95F7D4:\n"
                 "LDR     R3, =0x99CC0\n"
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BNE     loc_FF95F824\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF9619E8\n"
                 "TST     R0, #1\n"
                 "BNE     loc_FF95F7C4\n"
                 "BL      sub_FF9A0B80\n"
                 "BL      sub_FF824A78\n"
                 "LDR     R2, =0x99C04\n"
                 "ADD     R3, R4, R4,LSL#1\n"
                 "STR     R0, [R2,R3,LSL#5]\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF96339C\n"
                 "BL      sub_FF961EEC\n"
                 "BL      sub_FF961E88\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF962C30_my\n"  //------------->

                 "BL      capt_seq_hook_raw_here\n"

                 "B       loc_FF95F838\n"       
 "loc_FF95F824:\n"
                 "LDR     R3, =0x61A4\n"
                 "LDR     R2, [R3]\n"
                 "CMP     R2, #0\n"
                 "MOVNE   R0, #0x1D\n"
                 "MOVEQ   R0, #0\n"
 "loc_FF95F838:\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF95DE70\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF962E28\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()    // task_CaptSeqTask
{
 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "SUB     SP, SP, #4\n"
                 "MOV     R4, SP\n"
                 "B       loc_FF95FD74\n"   
 "loc_FF95FC0C:\n"
                 "LDR     R2, [SP]\n"       
                 "LDR     R3, [R2]\n"
                 "MOV     R0, R2\n"
                 "CMP     R3, #0x14\n"
                 "LDRLS   PC, [PC,R3,LSL#2]\n"
                 "B       loc_FF95FD48\n"   
                 ".long loc_FF95FC78\n"
                 ".long loc_FF95FC98\n"
                 ".long loc_FF95FCAC\n"
                 ".long loc_FF95FCBC\n"
                 ".long loc_FF95FCB4\n"
                 ".long loc_FF95FCC4\n"
                 ".long loc_FF95FCCC\n"
                 ".long loc_FF95FCD8\n"
                 ".long loc_FF95FCE0\n"
                 ".long loc_FF95FCEC\n"
                 ".long loc_FF95FCF4\n"
                 ".long loc_FF95FCFC\n"
                 ".long loc_FF95FD04\n"
                 ".long loc_FF95FD0C\n"
                 ".long loc_FF95FD14\n"
                 ".long loc_FF95FD20\n"
                 ".long loc_FF95FD28\n"
                 ".long loc_FF95FD30\n"
                 ".long loc_FF95FD38\n"
                 ".long loc_FF95FD40\n"
                 ".long loc_FF95FD5C\n"     
 "loc_FF95FC78:\n"
                 "BL      sub_FF961648\n"
                 "BL      shooting_expo_param_override\n"   // +
                 "BL      sub_FF95D990\n"   
                 "LDR     R3, =0x99CC0\n"        
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BEQ     loc_FF95FD58\n"
                 "BL      sub_FF95F858\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FC98:\n"
                 "BL      sub_FF95F788_my\n" //------------->
 "loc_FF95FC9C:\n"
                 "LDR     R2, =0x99CC0\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [R2,#0x24]\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FCAC:\n"
                 "BL      sub_FF9619D8\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FCB4:\n"
                 "BL      sub_FF960848\n"
                 "B       loc_FF95FC9C\n"   
 "loc_FF95FCBC:\n"
                 "BL      sub_FF960BE4\n"   //BackLightDrv_LcdBackLightOff_3
                 "B       loc_FF95FC9C\n"   
 "loc_FF95FCC4:\n"
                 "BL      sub_FF960BF4\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FCCC:\n"
                 "BL      sub_FF96172C\n"
                 "BL      sub_FF95D990\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FCD8:\n"
                 "BL      sub_FF95F92C\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FCE0:\n"
                 "BL      sub_FF961794\n"
                 "BL      sub_FF95D990\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FCEC:\n"
                 "BL      sub_FF960BE4\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FCF4:\n"
                 "BL      sub_FF961F2C\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FCFC:\n"
                 "BL      sub_FF962278\n"   
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD04:\n"
                 "BL      sub_FF9622FC\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD0C:\n"
                 "BL      sub_FF9623E8\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD14:\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF9624B0\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD20:\n"
                 "BL      sub_FF96261C\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD28:\n"
                 "BL      sub_FF9626B0\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD30:\n"
                 "BL      sub_FF96276C\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD38:\n"
                 "BL      sub_FF962858\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD40:\n"
                 "BL      sub_FF9628AC\n"
                 "B       loc_FF95FD58\n"   
 "loc_FF95FD48:\n"
                 "MOV     R1, #0x36C\n"
                 "LDR     R0, =0xFF95F514\n"
                 "ADD     R1, R1, #1\n"
                 "BL      sub_FF813AFC\n"   // DebugAssert
 "loc_FF95FD58:\n"
                 "LDR     R2, [SP]\n"
 "loc_FF95FD5C:\n"
                 "LDR     R3, =0x6F18C\n"
                 "LDR     R1, [R2,#4]\n"
                 "LDR     R0, [R3]\n"
                 "BL      sub_FF81FCE4\n"   // SetEventFlag
                 "LDR     R0, [SP]\n"
                 "BL      sub_FF95F590\n"
 "loc_FF95FD74:\n"
                 "LDR     R3, =0x6F190\n"
                 "MOV     R1, R4\n"
                 "LDR     R0, [R3]\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF8203FC\n"   // ReceiveMessageQueue
                 "TST     R0, #1\n"
                 "BEQ     loc_FF95FC0C\n"
                 "MOV     R1, #0x2A4\n"
                 "LDR     R0, =0xFF95F514\n"
                 "ADD     R1, R1, #3\n"
                 "BL      sub_FF813AFC\n"   // DebugAssert
                 "BL      sub_FF821958\n"   // ExitTask
                 "ADD     SP, SP, #4\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}





