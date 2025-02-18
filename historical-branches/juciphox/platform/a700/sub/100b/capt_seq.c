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
    long *nrflag = (long*)0x6104;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = NR_OFF;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = NR_ON;
	break;
    };
}


void __attribute__((naked,noinline)) sub_FFD48B28_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R3, =0x6EAC4\n"
                "LDR     R5, =0x6100\n"
                "SUB     SP, SP, #4\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC0FB44\n"
                "LDR     R3, =0x99240\n"
                "LDR     R0, [R3,#0x74]\n"
                "BL      sub_FFC8B8B8\n"
                "BL      sub_FFD48A7C\n"
             "BL      wait_until_remote_button_is_released\n"
	    	"BL      capt_seq_hook_set_nr\n"

		"B       sub_FFD48B58\n"
    );
}

void __attribute__((naked,noinline)) sub_FFD457CC_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, [R0,#0xC]\n"
                "BL      sub_FFD4DECC\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFD457E4\n"
                "BL      sub_FFD4DED8\n"
"loc_FFD457E4:\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFD4DEEC\n"
                "TST     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R0, R4\n"
                "BEQ     loc_FFD4580C\n"
                "MOV     R0, #1\n"
                "MOV     R1, R0\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFD43CFC\n"
"loc_FFD4580C:\n"
                "BL      sub_FFD478E4\n"
                "TST     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FFD45828\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFD43CFC\n"
"loc_FFD45828:\n"
                "BL      sub_FFD87078\n"
                "BL      sub_FFC146EC\n"
                "LDR     R2, =0x99184\n"
                "ADD     R3, R4, R4,LSL#1\n"
                "STR     R0, [R2,R3,LSL#5]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD49294\n"
                "BL      sub_FFD47DE8\n"
                "BL      sub_FFD47D84\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD48B28_my\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BL      sub_FFD43CFC\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFD48D20\n"

    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FFD45D40\n"
"loc_FFD45BE8:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFD45D14\n"
                ".long loc_FFD45C58\n"
                ".long loc_FFD45C64\n"
                ".long loc_FFD45C6C\n"
                ".long loc_FFD45C7C\n"
                ".long loc_FFD45C74\n"
                ".long loc_FFD45C84\n"
                ".long loc_FFD45C8C\n"
                ".long loc_FFD45C98\n"
                ".long loc_FFD45CA0\n"
                ".long loc_FFD45CAC\n"
                ".long loc_FFD45CB4\n"
                ".long loc_FFD45CBC\n"
                ".long loc_FFD45CC4\n"
                ".long loc_FFD45CCC\n"
                ".long loc_FFD45CD4\n"
                ".long loc_FFD45CE0\n"
                ".long loc_FFD45CE8\n"
                ".long loc_FFD45CF0\n"
                ".long loc_FFD45CF8\n"
                ".long loc_FFD45D04\n"
                ".long loc_FFD45D0C\n"
                ".long loc_FFD45D28\n"
"loc_FFD45C58:\n"
                "BL      sub_FFD4753C\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFD438A0\n"
                "B       loc_FFD45D24\n"
"loc_FFD45C64:\n"
                "BL      sub_FFD457CC_my\n"
                "B       loc_FFD45D24\n"
"loc_FFD45C6C:\n"
                "BL      sub_FFD478D4\n"
                "B       loc_FFD45D24\n"
"loc_FFD45C74:\n"
                "BL      sub_FFD467A0\n"
                "B       loc_FFD45D24\n"
"loc_FFD45C7C:\n"
                "BL      sub_FFD46BD8\n"
                "B       loc_FFD45D24\n"
"loc_FFD45C84:\n"
                "BL      sub_FFD46BE8\n"
                "B       loc_FFD45D24\n"
"loc_FFD45C8C:\n"
                "BL      sub_FFD47620\n"
                "BL      sub_FFD438A0\n"
                "B       loc_FFD45D24\n"
"loc_FFD45C98:\n"
                "BL      sub_FFD458D8\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CA0:\n"
                "BL      sub_FFD47688\n"
                "BL      sub_FFD438A0\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CAC:\n"
                "BL      sub_FFD46BD8\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CB4:\n"
                "BL      sub_FFD47E28\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CBC:\n"
                "BL      sub_FFD4816C\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CC4:\n"
                "BL      sub_FFD481F0\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CCC:\n"
                "BL      sub_FFD482E0\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CD4:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFD483A8\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CE0:\n"
                "BL      sub_FFD48514\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CE8:\n"
                "BL      sub_FFD485A8\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CF0:\n"
                "BL      sub_FFD48664\n"
                "B       loc_FFD45D24\n"
"loc_FFD45CF8:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD483A8\n"
                "B       loc_FFD45D24\n"
"loc_FFD45D04:\n"
                "BL      sub_FFD48750\n"
                "B       loc_FFD45D24\n"
"loc_FFD45D0C:\n"
                "BL      sub_FFD487A4\n"
                "B       loc_FFD45D24\n"
"loc_FFD45D14:\n"
                "MOV     R1, #0x36C\n"
                "LDR     R0, =0xFFD45558\n"
                "ADD     R1, R1, #1\n"
                "BL      sub_FFC03AE8\n"
"loc_FFD45D24:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
"loc_FFD45D28:\n"
                "LDR     R3, =0x6EA4C\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC0F9A8\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFD455D4\n"
"loc_FFD45D40:\n"
                "LDR     R3, =0x6EA50\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFC100C0\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD45BE8\n"
                "MOV     R1, #0x2A4\n"
                "LDR     R0, =0xFFD45558\n"
                "ADD     R1, R1, #3\n"
                "BL      sub_FFC03AE8\n"
                "BL      sub_FFC1161C\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

