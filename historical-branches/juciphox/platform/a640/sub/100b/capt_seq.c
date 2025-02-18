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
    long *nrflag = (long*)0x6264;

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



void __attribute__((naked,noinline)) sub_FFD5894C_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFD59310\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "BL      sub_FFC10A3C\n"
                "LDR     R0, =0x122\n"
                "ADD     R1, SP, #0x14-0x10\n"
                "MOV     R2, #4\n"
                "BL      sub_FFC15484\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD5898C\n"
                "LDR     R0, =0xFFD587C8\n"
                "MOV     R1, #0x1D0\n"
                "BL      sub_FFC03CF8\n"
"loc_FFD5898C:\n"
                "LDR     R3, =0x91FA0\n"
                "LDR     R2, =0x92060\n"
                "LDR     R0, [R3,#0x84]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                //"BL      nullsub_47\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD5874C\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6268\n"
                "LDR     R0, [R3]\n"
                "BL      wait_until_remote_button_is_released\n"

		"B       sub_FFD589B0\n"
    );
}

void __attribute__((naked,noinline)) sub_FFD558E0_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0x91FA0\n"
                "LDR     R5, [R0,#0xC]\n"
                "LDR     R1, [R3,#0x28]\n"
                "LDR     R2, [R5,#8]\n"
                "CMP     R1, #0\n"
                "ORR     R2, R2, #1\n"
                "STR     R2, [R5,#8]\n"
                "BNE     loc_FFD55934\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFD5F510\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD55934\n"
                "LDR     R3, [R5,#8]\n"
                "MOV     R0, #1\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R5,#8]\n"
"loc_FFD55924:\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFD54100\n"
"loc_FFD55934:\n"
                "LDR     R4, =0x91FA0\n"
                "BL      sub_FFD56410\n"
                "LDR     R3, [R4,#0x28]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FFD5597C\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD574E8\n"
                "TST     R0, #1\n"
                "BNE     loc_FFD55924\n"
                "BL      sub_FFD96AA4\n"
                "BL      sub_FFC15680\n"
                "STR     R0, [R5,#0x14]\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD58834\n"
                "BL      sub_FFD5919C\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD5894C_my\n"
		"BL      capt_seq_hook_raw_here\n"
                "B       loc_FFD55990\n"
"loc_FFD5597C:\n"
                "LDR     R3, =0x6248\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "MOVNE   R0, #0x1D\n"
                "MOVEQ   R0, #0\n"
"loc_FFD55990:\n"
                "MOV     R1, #1\n"
                "MOV     R2, R5\n"
                "BL      sub_FFD54100\n"
                "BL      sub_FFD58C88\n"
                "CMP     R0, #0\n"
                "LDRNE   R3, [R5,#8]\n"
                "ORRNE   R3, R3, #0x2000\n"
                "STRNE   R3, [R5,#8]\n"
                "LDMFD   SP!, {R4,R5,PC}\n"

    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FFD55F54\n"
"loc_FFD55DC8:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x16\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFD55F28\n"
                ".long loc_FFD55E3C\n"
                ".long loc_FFD55E5C\n"
                ".long loc_FFD55E70\n"
                ".long loc_FFD55E84\n"
                ".long loc_FFD55E7C\n"
                ".long loc_FFD55E8C\n"
                ".long loc_FFD55E94\n"
                ".long loc_FFD55EA0\n"
                ".long loc_FFD55EA8\n"
                ".long loc_FFD55EB4\n"
                ".long loc_FFD55EBC\n"
                ".long loc_FFD55EC4\n"
                ".long loc_FFD55ECC\n"
                ".long loc_FFD55ED4\n"
                ".long loc_FFD55EDC\n"
                ".long loc_FFD55EE8\n"
                ".long loc_FFD55EF0\n"
                ".long loc_FFD55EF8\n"
                ".long loc_FFD55F00\n"
                ".long loc_FFD55F0C\n"
                ".long loc_FFD55F18\n"
                ".long loc_FFD55F20\n"
                ".long loc_FFD55F3C\n"
"loc_FFD55E3C:\n"
                "BL      sub_FFD56438\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFD53B94\n"
                "LDR     R3, =0x91FA0\n"
                "LDR     R2, [R3,#0x28]\n"
                "CMP     R2, #0\n"
                "BEQ     loc_FFD55F38\n"
                "BL      sub_FFD559BC\n"
                "B       loc_FFD55F38\n"
"loc_FFD55E5C:\n"
                "BL      sub_FFD558E0_my\n"
"loc_FFD55E60:\n"
                "LDR     R2, =0x91FA0\n"
                "MOV     R3, #0\n"
                "STR     R3, [R2,#0x28]\n"
                "B       loc_FFD55F38\n"
"loc_FFD55E70:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD5662C\n"
                "B       loc_FFD55F38\n"
"loc_FFD55E7C:\n"
                "BL      sub_FFD5604C\n"
                "B       loc_FFD55E60\n"
"loc_FFD55E84:\n"
                "BL      sub_FFD563F0\n"
                "B       loc_FFD55E60\n"
"loc_FFD55E8C:\n"
                "BL      sub_FFD56400\n"
                "B       loc_FFD55F38\n"
"loc_FFD55E94:\n"
                "BL      sub_FFD56524\n"
                "BL      sub_FFD53B94\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EA0:\n"
                "BL      sub_FFD55A98\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EA8:\n"
                "BL      sub_FFD5658C\n"
                "BL      sub_FFD53B94\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EB4:\n"
                "BL      sub_FFD563F0\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EBC:\n"
                "BL      sub_FFD57C18\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EC4:\n"
                "BL      sub_FFD57DE4\n"
                "B       loc_FFD55F38\n"
"loc_FFD55ECC:\n"
                "BL      sub_FFD57E78\n"
                "B       loc_FFD55F38\n"
"loc_FFD55ED4:\n"
                "BL      sub_FFD57F14\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EDC:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFD58180\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EE8:\n"
                "BL      sub_FFD58338\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EF0:\n"
                "BL      sub_FFD583C8\n"
                "B       loc_FFD55F38\n"
"loc_FFD55EF8:\n"
                "BL      sub_FFD58480\n"
                "B       loc_FFD55F38\n"
"loc_FFD55F00:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD58180\n"
                "B       loc_FFD55F38\n"
"loc_FFD55F0C:\n"
                "BL      sub_FFD5676C\n"
                "BL      sub_FFD55804\n"
                "B       loc_FFD55F38\n"
"loc_FFD55F18:\n"
                "BL      sub_FFD58054\n"
                "B       loc_FFD55F38\n"
"loc_FFD55F20:\n"
                "BL      sub_FFD580AC\n"
                "B       loc_FFD55F38\n"
"loc_FFD55F28:\n"
                "MOV     R1, #0x4E0\n"
                "LDR     R0, =0xFFD55660\n"
                "ADD     R1, R1, #7\n"
                "BL      sub_FFC03CF8\n"
"loc_FFD55F38:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
"loc_FFD55F3C:\n"
                "LDR     R3, =0x67094\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC108A0\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFD556DC\n"
"loc_FFD55F54:\n"
                "LDR     R3, =0x67098\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFC10FB8\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD55DC8\n"
                "MOV     R1, #0x410\n"
                "LDR     R0, =0xFFD55660\n"
                "ADD     R1, R1, #9\n"
                "BL      sub_FFC03CF8\n"
                "BL      sub_FFC12514\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

