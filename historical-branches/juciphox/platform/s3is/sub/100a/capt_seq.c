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
    long *nrflag = (long*)0x6688;

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


void __attribute__((naked,noinline)) sub_FF97DD78_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R3, =0x6193C\n"
                "LDR     R5, =0x6684\n"
                "SUB     SP, SP, #4\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FF40\n"
                "LDR     R3, =0x92DE0\n"
                "LDR     R0, [R3,#0x74]\n"
                //"BL      nullsub_31\n"
                "BL      sub_FF97DCCC\n"
         //   "BL      wait_until_remote_button_is_released\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x668C\n"
                "LDR     R0, [R3]\n"

		"B       sub_FF97DDB0\n"
    );
}

void __attribute__((naked,noinline)) sub_FF97A124_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R7,LR}\n"
                "LDR     R4, [R0,#0xC]\n"
                "BL      sub_FF983D84\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF97A13C\n"
                "BL      sub_FF983D90\n"
"loc_FF97A13C:\n"
                "LDR     R1, =0x92DE0\n"
                "MOV     R3, #0x8000\n"
                "LDRH    R2, [R1]\n"
                "ADD     R3, R3, #7\n"
                "CMP     R2, R3\n"
                "BNE     loc_FF97A198\n"
                "LDRH    R3, [R1,#0x80]\n"
                "CMP     R3, #3\n"
                "BEQ     loc_FF97A198\n"
                "LDRH    R3, [R1,#0x7E]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A198\n"
                "LDRH    R3, [R1,#0x7A]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FF97A198\n"
                "LDR     R2, =0x92E80\n"
                "LDR     R3, [R2,#0x1C]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A198\n"
                "LDR     R3, [R2,#0x18]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A198\n"
                "BL      sub_FF97D9C4\n"
"loc_FF97A198:\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FF983DA4\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF97A1BC\n"
                "MOV     R0, #1\n"
"loc_FF97A1AC:\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4-R7,LR}\n"
                "B       sub_FF9783E4\n"
"loc_FF97A1BC:\n"
                "MOV     R0, #2\n"
                "LDR     R6, =0x92D20\n"
                "BL      sub_FFB01384\n"
                "ADD     R3, R4, R4,LSL#1\n"
                "MOV     R5, R3,LSL#5\n"
                "ADD     R7, R6, #8\n"
                "LDR     R3, [R7,R5]\n"
                "CMP     R3, #0\n"
                "BEQ     loc_FF97A1E4\n"
                "BL      sub_FF962E94\n"
"loc_FF97A1E4:\n"
                "MOV     R0, R4\n"
                "BL      sub_FF97C7B8\n"
                "MOV     R0, R4\n"
                "BL      sub_FF97C7F4\n"
                "TST     R0, #1\n"
                "BNE     loc_FF97A1AC\n"
                "BL      sub_FF9C0724\n"
                "BL      sub_FF824B88\n"
                "ADD     R3, R6, #4\n"
                "STR     R0, [R3,R5]\n"
                "MOV     R0, R4\n"
                "BL      sub_FF97E4FC\n"
                "BL      sub_FF97CD9C\n"
                "BL      sub_FF97CD38\n"
                "MOV     R0, R4\n"
                "BL      sub_FF97DD78_my\n"
                "BL      capt_seq_hook_raw_here\n"
                "MOV     R1, #1\n"
                "MOV     R2, R4\n"
                "BL      sub_FF9783E4\n"
                "BL      sub_FF97DF88\n"
                "LDR     R3, [R7,R5]\n"
                "CMP     R3, #0\n"
                "BEQ     loc_FF97A244\n"
                "BL      sub_FF962EB4\n"
"loc_FF97A244:\n"
                "LDR     R1, =0x92DE0\n"
                "MOV     R3, #0x8000\n"
                "LDRH    R2, [R1]\n"
                "ADD     R3, R3, #7\n"
                "CMP     R2, R3\n"
                "LDMNEFD SP!, {R4-R7,PC}\n"
                "LDRH    R3, [R1,#0x80]\n"
                "CMP     R3, #3\n"
                "LDMEQFD SP!, {R4-R7,PC}\n"
                "LDRH    R3, [R1,#0x7E]\n"
                "CMP     R3, #0\n"
                "LDMNEFD SP!, {R4-R7,PC}\n"
                "LDRH    R3, [R1,#0x7A]\n"
                "CMP     R3, #1\n"
                "LDMNEFD SP!, {R4-R7,PC}\n"
                "LDR     R2, =0x92E80\n"
                "LDR     R3, [R2,#0x1C]\n"
                "CMP     R3, #0\n"
                "LDMNEFD SP!, {R4-R7,PC}\n"
                "LDR     R3, [R2,#0x18]\n"
                "CMP     R3, #0\n"
                "LDMNEFD SP!, {R4-R7,PC}\n"
                "MOV     R0, R4\n"
                "LDMFD   SP!, {R4-R7,LR}\n"
                "B       sub_FF97D970\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF97A8F8\n"
"loc_FF97A630:\n"
                "LDR     R1, [SP,#0xC-0xC]\n"
                "LDR     R3, [R1]\n"
                "MOV     R0, R1\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF97A8D0\n"
                ".long loc_FF97A6A0\n"
                ".long loc_FF97A6AC\n"
                ".long loc_FF97A6B4\n"
                ".long loc_FF97A720\n"
                ".long loc_FF97A718\n"
                ".long loc_FF97A784\n"
                ".long loc_FF97A7E8\n"
                ".long loc_FF97A7F4\n"
                ".long loc_FF97A7FC\n"
                ".long loc_FF97A808\n"
                ".long loc_FF97A810\n"
                ".long loc_FF97A818\n"
                ".long loc_FF97A820\n"
                ".long loc_FF97A828\n"
                ".long loc_FF97A830\n"
                ".long loc_FF97A83C\n"
                ".long loc_FF97A844\n"
                ".long loc_FF97A84C\n"
                ".long loc_FF97A854\n"
                ".long loc_FF97A860\n"
                ".long loc_FF97A868\n"
                ".long loc_FF97A870\n"
"loc_FF97A6A0:\n"
                "BL      sub_FF97C09C\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FF977E9C\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A6AC:\n"
                "BL      sub_FF97A124_my\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A6B4:\n"
                "LDR     R1, =0x92DE0\n"
                "MOV     R3, #0x8000\n"
                "LDRH    R2, [R1]\n"
                "ADD     R3, R3, #7\n"
                "CMP     R2, R3\n"
                "BNE     loc_FF97A710\n"
                "LDRH    R3, [R1,#0x80]\n"
                "CMP     R3, #3\n"
                "BEQ     loc_FF97A710\n"
                "LDRH    R3, [R1,#0x7E]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A710\n"
                "LDRH    R3, [R1,#0x7A]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FF97A710\n"
                "LDR     R2, =0x92E80\n"
                "LDR     R3, [R2,#0x1C]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A710\n"
                "LDR     R3, [R2,#0x18]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A710\n"
                "BL      sub_FF97D9C4\n"
"loc_FF97A710:\n"
                "BL      sub_FF97C7A8\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A718:\n"
                "BL      sub_FF97B384\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A720:\n"
                "LDR     R1, =0x92DE0\n"
                "MOV     R3, #0x8000\n"
                "LDRH    R2, [R1]\n"
                "ADD     R3, R3, #7\n"
                "CMP     R2, R3\n"
                "BNE     loc_FF97A77C\n"
                "LDRH    R3, [R1,#0x80]\n"
                "CMP     R3, #3\n"
                "BEQ     loc_FF97A77C\n"
                "LDRH    R3, [R1,#0x7E]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A77C\n"
                "LDRH    R3, [R1,#0x7A]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FF97A77C\n"
                "LDR     R2, =0x92E80\n"
                "LDR     R3, [R2,#0x1C]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A77C\n"
                "LDR     R3, [R2,#0x18]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A77C\n"
                "BL      sub_FF97D9C4\n"
"loc_FF97A77C:\n"
                "BL      sub_FF97B724\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A784:\n"
                "LDR     R1, =0x92DE0\n"
                "MOV     R3, #0x8000\n"
                "LDRH    R2, [R1]\n"
                "ADD     R3, R3, #7\n"
                "CMP     R2, R3\n"
                "BNE     loc_FF97A7E0\n"
                "LDRH    R3, [R1,#0x80]\n"
                "CMP     R3, #3\n"
                "BEQ     loc_FF97A7E0\n"
                "LDRH    R3, [R1,#0x7E]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A7E0\n"
                "LDRH    R3, [R1,#0x7A]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FF97A7E0\n"
                "LDR     R2, =0x92E80\n"
                "LDR     R3, [R2,#0x1C]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A7E0\n"
                "LDR     R3, [R2,#0x18]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A7E0\n"
                "BL      sub_FF97D9C4\n"
"loc_FF97A7E0:\n"
                "BL      sub_FF97B734\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A7E8:\n"
                "BL      sub_FF97C180\n"
                "BL      sub_FF977E9C\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A7F4:\n"
                "BL      sub_FF97A320\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A7FC:\n"
                "BL      sub_FF97C1E8\n"
                "BL      sub_FF977E9C\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A808:\n"
                "BL      sub_FF97B724\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A810:\n"
                "BL      sub_FF97CDDC\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A818:\n"
                "BL      sub_FF97D120\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A820:\n"
                "BL      sub_FF97D1A4\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A828:\n"
                "BL      sub_FF97D2A0\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A830:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF97D368\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A83C:\n"
                "BL      sub_FF97D504\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A844:\n"
                "BL      sub_FF97D598\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A84C:\n"
                "BL      sub_FF97D654\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A854:\n"
                "MOV     R0, #1\n"
                "BL      sub_FF97D368\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A860:\n"
                "BL      sub_FF97D740\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A868:\n"
                "BL      sub_FF97D810\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A870:\n"
                "LDR     R0, =0x92DE0\n"
                "MOV     R3, #0x8000\n"
                "LDRH    R2, [R0]\n"
                "ADD     R3, R3, #7\n"
                "CMP     R2, R3\n"
                "BNE     loc_FF97A8E0\n"
                "LDRH    R3, [R0,#0x80]\n"
                "CMP     R3, #3\n"
                "BEQ     loc_FF97A8E0\n"
                "LDRH    R3, [R0,#0x7E]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A8E0\n"
                "LDRH    R3, [R0,#0x7A]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FF97A8E0\n"
                "LDR     R2, =0x92E80\n"
                "LDR     R3, [R2,#0x1C]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A8E0\n"
                "LDR     R3, [R2,#0x18]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF97A8E0\n"
                "BL      sub_FF97D9C4\n"
                "B       loc_FF97A8DC\n"
"loc_FF97A8D0:\n"
                "MOV     R1, #0x36C\n"
                "LDR     R0, =0xFF979EB0\n"
                "BL      sub_FF813B80\n"
"loc_FF97A8DC:\n"
                "LDR     R1, [SP,#0xC-0xC]\n"
"loc_FF97A8E0:\n"
                "LDR     R3, =0x618C4\n"
                "LDR     R1, [R1,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FDA4\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FF979F2C\n"
"loc_FF97A8F8:\n"
                "LDR     R3, =0x618C8\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF8204BC\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF97A630\n"
                "MOV     R1, #0x2A4\n"
                "LDR     R0, =0xFF979EB0\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813B80\n"
                "BL      sub_FF821A18\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

