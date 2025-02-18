#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6E50;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF9A2B40_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FF9A35AC\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "BL      sub_FF820E7C\n"
                "LDR     R0, =0x122\n"
                "ADD     R1, SP, #0x14-0x10\n"
                "MOV     R2, #4\n"
                "BL      sub_FF8258D4\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF9A2B80\n"
                "LDR     R0, =0xFF9A29BC\n"
                "MOV     R1, #0x1DC\n"
                "BL      sub_FF813D70\n"
"loc_FF9A2B80:\n"
                "LDR     R3, =0xA4840\n"
                "LDR     R2, =0xA4900\n"
                "LDR     R0, [R3,#0x84]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                //"BL      nullsub_47\n"
                "MOV     R0, R4\n"
                "BL      sub_FF9A2940\n"
                "BL      wait_until_remote_button_is_released\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6E54\n"
                "LDR     R0, [R3]\n"

		"B       sub_FF9A2BA4\n"
    );
}

void __attribute__((naked,noinline)) sub_FF99ED38_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0xA4840\n"
                "LDR     R4, [R0,#0xC]\n"
                "LDR     R1, [R3,#0x28]\n"
                "LDR     R2, [R4,#8]\n"
                "CMP     R1, #0\n"
                "ORR     R2, R2, #1\n"
                "STR     R2, [R4,#8]\n"
                "BNE     loc_FF99ED8C\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FF9AA0F8\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF99ED8C\n"
                "LDR     R3, [R4,#8]\n"
                "MOV     R0, #1\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R4,#8]\n"
"loc_FF99ED7C:\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF99D200\n"
"loc_FF99ED8C:\n"
		"LDR     R1, =0xA4840\n"
                "MOV     R3, #0x8200\n"
                "LDRH    R2, [R1]\n"
                "ADD     R3, R3, #0xA\n"
                "CMP     R2, R3\n"
                "BEQ     loc_FF99EDD8\n"
                "LDRH    R3, [R1,#0x90]\n"
                "CMP     R3, #3\n"
                "BEQ     loc_FF99EDD8\n"
                "LDR     R3, [R4,#0xC]\n"
                "CMP     R3, #1\n"
                "BLS     loc_FF99EDD8\n"
                "LDRH    R3, [R1,#0x8E]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF99EDD8\n"
                "LDRH    R3, [R1,#0x8A]\n"
                "CMP     R3, #2\n"
                "BNE     loc_FF99EDD8\n"
                "BL      sub_FF99FFF4\n"
"loc_FF99EDD8:\n"
                "LDR     R1, =0xA4840\n"
                "MOV     R3, #0x8200\n"
                "LDRH    R2, [R1]\n"
                "ADD     R3, R3, #0xA\n"
                "CMP     R2, R3\n"
                "BEQ     loc_FF99EE20\n"
                "LDRH    R3, [R1,#0x90]\n"
                "CMP     R3, #3\n"
                "BEQ     loc_FF99EE20\n"
                "LDR     R3, [R4,#0xC]\n"
                "CMP     R3, #1\n"
                "BLS     loc_FF99EE20\n"
                "LDRH    R3, [R1,#0x8E]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF99EE20\n"
                "LDRH    R3, [R1,#0x8A]\n"
                "CMP     R3, #2\n"
                "BEQ     loc_FF99EE88\n"
"loc_FF99EE20:\n"
                "LDR     R2, =0xA4840\n"
                "LDRH    R3, [R2,#0x90]\n"
                "CMP     R3, #3\n"
                "BEQ     loc_FF99EEA0\n"
                "LDRH    R3, [R2,#0x8E]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF99EEA0\n"
                "LDRH    R1, [R2,#0x8A]\n"
                "CMP     R1, #1\n"
                "BNE     loc_FF99EEA0\n"
                "LDRH    R2, [R2]\n"
                "MOV     R3, #0x8200\n"
		"ADD     R3, R3, #0xA\n"
                "CMP     R2, R3\n"
                "BEQ     loc_FF99EEA0\n"
                "LDR     R3, [R4,#0xC]\n"
                "CMP     R3, #1\n"
                "BLS     loc_FF99EEA0\n"
                "ADD     R3, R1, #0xFF00\n"
                "ADD     R3, R3, #0xFF\n"
                "MOV     R3, R3,LSL#16\n"
                "CMP     R3, #0x10000\n"
                "BHI     loc_FF99EEA0\n"
                "LDR     R3, [R4,#0x10]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FF99EEA0\n"
"loc_FF99EE88:\n"
                "LDR     R3, =0x77BB4\n"
                "MOV     R2, #0xEA00\n"
                "LDR     R0, [R3]\n"
                "MOV     R1, #0x8000000\n"
                "ADD     R2, R2, #0x60\n"
                "BL      sub_FF9AA57C\n"
"loc_FF99EEA0:\n"
                "LDR     R5, =0xA4840\n"
                "BL      sub_FF99EC18\n"
                "LDR     R3, [R5,#0x28]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF99EEBC\n"
                "MOV     R0, #2\n"
                "BL      sub_FFB41B1C\n"
"loc_FF99EEBC:\n"
                "BL      sub_FF99FAC0\n"
                "LDR     R3, [R5,#0x28]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF99EF08\n"
                "MOV     R0, R4\n"
                "BL      sub_FF9A2578\n"
                "MOV     R0, R4\n"
                "BL      sub_FF9A0E20\n"
                "TST     R0, #1\n"
                "BNE     loc_FF99ED7C\n"
                "BL      sub_FF9E6FCC\n"
                "BL      sub_FF825AD0\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FF9A2A28\n"
                "BL      sub_FF9A3424\n"
                "MOV     R0, R4\n"
                "BL      sub_FF9A2B40_my\n"          //---------->
                "BL      capt_seq_hook_raw_here\n"   // +
                "B       loc_FF99EF1C\n"
"loc_FF99EF08:\n"
                "LDR     R3, =0x6E20\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "MOVNE   R0, #0x1D\n"
                "MOVEQ   R0, #0\n"
"loc_FF99EF1C:\n"
                "MOV     R1, #1\n"
                "MOV     R2, R4\n"
                "BL      sub_FF99D200\n"
                "BL      sub_FF9A2F14\n"
                "CMP     R0, #0\n"
                "LDRNE   R3, [R4,#8]\n"
                "ORRNE   R3, R3, #0x2000\n"
                "STRNE   R3, [R4,#8]\n"
                "LDR     R2, =0xA4840\n"
                "LDRH    R3, [R2,#0x90]\n"
                "CMP     R3, #3\n"
                "LDMEQFD SP!, {R4,R5,PC}\n"
                "LDRH    R3, [R2,#0x8E]\n"
                "CMP     R3, #0\n"
                "LDMNEFD SP!, {R4,R5,PC}\n"
                "LDRH    R3, [R2,#0x8A]\n"
                "CMP     R3, #2\n"
                "LDMNEFD SP!, {R4,R5,PC}\n"
                "MOV     R0, R4\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF9A004C\n"
    );
}

void __attribute__((naked,noinline)) sub_FF99EF7C_my(){
 asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FF99E724\n"
                "LDR     R3, =0xA4840\n"
                "LDR     R2, [R3,#0x28]\n"
                "CMP     R2, #0\n"
                "MOV     R4, R0\n"
                "MOV     R0, #0xC\n"
                "BEQ     loc_FF99EFC4\n"
                "BL      sub_FF9AA0F8\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF99EFC4\n"
                "LDR     R3, [R4,#8]\n"
                "LDR     R2, =0x6E20\n"
                "ORR     R3, R3, #0x40000000\n"
                "MOV     R1, #1\n"
                "STR     R1, [R2]\n"
                "STR     R3, [R4,#8]\n"
                "LDMFD   SP!, {R4,PC}\n"
"loc_FF99EFC4:\n"
                "MOV     R0, R4\n"
                "BL      sub_FF9A2578\n"
                "BL      sub_FF9E6FCC\n"
                "BL      sub_FF825AD0\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FF9A2B40_my\n" //------->
                "BL      capt_seq_hook_raw_here\n" // +
                "TST     R0, #1\n"
                "LDRNE   R3, =0x6E20\n"
                "MOVNE   R2, #1\n"
                "STRNE   R2, [R3]\n"
                "LDMFD   SP!, {R4,PC}\n"
 );
}
 
void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R5, SP\n"
                "B       loc_FF99F5A8\n"
"loc_FF99F3C0:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x19\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF99F57C\n"
                ".long loc_FF99F440\n"
                ".long loc_FF99F460\n"
                ".long loc_FF99F474\n"
                ".long loc_FF99F488\n"
                ".long loc_FF99F480\n"
                ".long loc_FF99F490\n"
                ".long loc_FF99F498\n"
                ".long loc_FF99F4A4\n"
                ".long loc_FF99F4AC\n"
                ".long loc_FF99F4B8\n"
                ".long loc_FF99F4C0\n"
                ".long loc_FF99F4C8\n"
                ".long loc_FF99F4D0\n"
                ".long loc_FF99F4D8\n"
                ".long loc_FF99F4E0\n"
                ".long loc_FF99F4EC\n"
                ".long loc_FF99F4F4\n"
                ".long loc_FF99F4FC\n"
                ".long loc_FF99F504\n"
                ".long loc_FF99F510\n"
                ".long loc_FF99F51C\n"
                ".long loc_FF99F524\n"
                ".long loc_FF99F564\n"
                ".long loc_FF99F56C\n"
                ".long loc_FF99F574\n"
                ".long loc_FF99F590\n"
"loc_FF99F440:\n"
                "BL      sub_FF99FAE8\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FF99CC60\n"
                "LDR     R3, =0xA4840\n"
                "LDR     R2, [R3,#0x28]\n"
                "CMP     R2, #0\n"
                "BEQ     loc_FF99F58C\n"
                "BL      sub_FF99EF7C_my\n"  //-------->
                "B       loc_FF99F58C\n"
"loc_FF99F460:\n"
                "BL      sub_FF99ED38_my\n" //--------->
"loc_FF99F464:\n"
                "LDR     R2, =0xA4840\n"
                "MOV     R3, #0\n"
                "STR     R3, [R2,#0x28]\n"
                "B       loc_FF99F58C\n"
"loc_FF99F474:\n"
                "MOV     R0, #1\n"
                "BL      sub_FF99FDA8\n"
                "B       loc_FF99F58C\n"
"loc_FF99F480:\n"
                "BL      sub_FF99F6A4\n"
                "B       loc_FF99F464\n"
"loc_FF99F488:\n"
                "BL      sub_FF99FAA0\n"
                "B       loc_FF99F464\n"
"loc_FF99F490:\n"
                "BL      sub_FF99FAB0\n"
                "B       loc_FF99F58C\n"
"loc_FF99F498:\n"
                "BL      sub_FF99FC48\n"
                "BL      sub_FF99CC60\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4A4:\n"
                "BL      sub_FF99F060\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4AC:\n"
                "BL      sub_FF99FCFC\n"
                "BL      sub_FF99CC60\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4B8:\n"
                "BL      sub_FF99FAA0\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4C0:\n"
                "BL      sub_FF9A16F4\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4C8:\n"
                "BL      sub_FF9A1938\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4D0:\n"
                "BL      sub_FF9A19F0\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4D8:\n"
                "BL      sub_FF9A1A8C\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4E0:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF9A1F14\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4EC:\n"
                "BL      sub_FF9A2120\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4F4:\n"
                "BL      sub_FF9A21B8\n"
                "B       loc_FF99F58C\n"
"loc_FF99F4FC:\n"
                "BL      sub_FF9A2278\n"
                "B       loc_FF99F58C\n"
"loc_FF99F504:\n"
                "MOV     R0, #1\n"
                "BL      sub_FF9A1F14\n"
                "B       loc_FF99F58C\n"
"loc_FF99F510:\n"
                "BL      sub_FF99FF7C\n"
                "BL      sub_FF99EAF8\n"
                "B       loc_FF99F58C\n"
"loc_FF99F51C:\n"
                "BL      sub_FF9A1D9C\n"
                "B       loc_FF99F58C\n"
"loc_FF99F524:\n"
		"LDR     R4, =0xA48A0\n"
		"MOV     R0, #0x11\n"
		"MOV     R1, R4\n"
		"MOV     R2, #2\n"
		"BL      sub_FF8258D4\n"
		"TST     R0, #1\n"
		"BEQ     loc_FF99F550\n"
		"MOV     R1, #0x4C0\n"
		"LDR     R0, =0xFF99E838\n"
		"ADD     R1, R1, #6\n"
		"BL      sub_FF813D70\n"
"loc_FF99F550:\n"                         
		"LDRH    R3, [R4]\n"
		"CMP     R3, #1\n"
		"BNE     loc_FF99F58C\n"
		"BL      sub_FF9A1D88\n"
		"B       loc_FF99F58C\n"
"loc_FF99F564:\n"
		"BL      sub_FF9A1E34\n"
		"B       loc_FF99F58C\n"
"loc_FF99F56C:\n"
		"BL      sub_FF99EC18\n"
		"B       loc_FF99F58C\n"
"loc_FF99F574:\n"
		"BL      sub_FF99BA04\n"
		"B       loc_FF99F58C\n"
"loc_FF99F57C:\n"
		"MOV     R1, #0x4E0\n"
		"LDR     R0, =0xFF99E838\n"
		"ADD     R1, R1, #7\n"
		"BL      sub_FF813D70\n"
"loc_FF99F58C:\n"
		"LDR     R2, [SP]\n"
"loc_FF99F590:\n"
		"LDR     R3, =0x77BB4\n"
		"LDR     R1, [R2,#4]\n"
		"LDR     R0, [R3]\n"
		"BL      sub_FF820CE0\n"
		"LDR     R0, [SP]\n"
		"BL      sub_FF99E928\n"
"loc_FF99F5A8:\n"
		"LDR     R3, =0x77BB8\n"
		"MOV     R1, R5\n"
		"LDR     R0, [R3]\n"
		"MOV     R2, #0\n"
		"BL      sub_FF8213F8\n"
		"TST     R0, #1\n"
		"BEQ     loc_FF99F3C0\n"
		"MOV     R1, #0x410\n"
		"LDR     R0, =0xFF99E838\n"
		"ADD     R1, R1, #9\n"
		"BL      sub_FF813D70\n"
		"BL      sub_FF822954\n"
		"ADD     SP, SP, #4\n"
		"LDMFD   SP!, {R4,R5,PC}\n"
	);
}

