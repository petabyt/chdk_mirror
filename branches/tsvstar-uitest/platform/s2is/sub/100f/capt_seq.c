#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define NR_ON (1)
#define NR_OFF (0)

static long *nrflag = (long*)0x5724;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF96F5A8_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R3, =0x571C\n"
                "SUB     SP, SP, #4\n"
                "LDR     R2, [R3]\n"
                "LDR     R4, =0x5720\n"
                "CMP     R2, #0\n"
                "STR     R0, [R4]\n"
                "MOV     R8, #0\n"
                "LDR     R6, =0xFF96F4E0\n"
                "BNE     loc_FF96F5DC\n"
                "LDR     R0, =0xFF96F59C\n"
                "MOV     R1, #0xDB\n"
                "BL      sub_FF813D58\n"
"loc_FF96F5DC:\n"
                "LDR     R3, =0x5D164\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF8208C8\n"
                "BL      sub_FF96F518\n"
         //   "BL      wait_until_remote_button_is_released\n"
	    	"BL      capt_seq_hook_set_nr\n"

		"B       sub_FF96F5F0\n"
    );
}

void __attribute__((naked,noinline)) sub_FF96C034_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R5, [R0,#8]\n"
                "BL      sub_FF97AE20\n"
                "CMP     R0, #0\n"
                "LDR     R0, =0xFF96C010\n"
                "BNE     loc_FF96C054\n"
                "BL      sub_FFAF21BC\n"
                "BL      sub_FF97AE2C\n"
"loc_FF96C054:\n"
                "BL      sub_FF96A094\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "RSB     R3, R5, R3,LSL#3\n"
                "MOV     R6, R3,LSL#2\n"
                "ADD     R0, R6, R0\n"
                "LDR     R3, [R0,#8]\n"
                "CMP     R3, #0\n"
                "BEQ     loc_FF96C078\n"
                "BL      sub_FF953B70\n"
"loc_FF96C078:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96E054\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF96C098\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FF96ADF4\n"
"loc_FF96C098:\n"
                "BL      sub_FF96A094\n"
                "MOV     R4, R0\n"
                "BL      sub_FF825F00\n"
                "ADD     R4, R6, R4\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96FEEC\n"
                "BL      sub_FF96E6B0\n"
                "BL      sub_FF96E61C\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96F5A8_my\n"
                "BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF96ADF4\n"
                "BL      sub_FF96F86C\n"
                "BL      sub_FF96A094\n"
                "ADD     R0, R6, R0\n"
                "LDR     R3, [R0,#8]\n"
                "CMP     R3, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FF953BAC\n"

    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF96CBB0\n"
"loc_FF96CA00:\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "LDR     R3, [R0]\n"
                "CMP     R3, #0x11\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF96CB98\n"
                ".long loc_FF96CA5C\n"
                ".long loc_FF96CA6C\n"
                ".long loc_FF96CA80\n"
                ".long loc_FF96CA90\n"
                ".long loc_FF96CAA0\n"
                ".long loc_FF96CAB0\n"
                ".long loc_FF96CAC4\n"
                ".long loc_FF96CAD4\n"
                ".long loc_FF96CAE8\n"
                ".long loc_FF96CAF8\n"
                ".long loc_FF96CB08\n"
                ".long loc_FF96CB18\n"
                ".long loc_FF96CB28\n"
                ".long loc_FF96CB3C\n"
                ".long loc_FF96CB4C\n"
                ".long loc_FF96CB5C\n"
                ".long loc_FF96CB6C\n"
                ".long loc_FF96CB80\n"
"loc_FF96CA5C:\n"
                "BL      sub_FF96D224\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #8\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CA6C:\n"
                "BL      sub_FF96D9A8\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FF96A964\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x10\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CA80:\n"
                "BL      sub_FF96C034_my\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #2\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CA90:\n"
                "BL      sub_FF96DFB8\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #1\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CAA0:\n"
                "BL      sub_FF96DA58\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x20\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CAB0:\n"
                "BL      sub_FF96DB50\n"
                "BL      sub_FF96A964\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x40\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CAC4:\n"
                "BL      sub_FF96C218\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x80\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CAD4:\n"
                "BL      sub_FF96DCC8\n"
                "BL      sub_FF96A964\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x400\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CAE8:\n"
                "BL      sub_FF96DA58\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x800\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CAF8:\n"
                "BL      sub_FF96E7F4\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x8000\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CB08:\n"
                "BL      sub_FF96EBD0\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x10000\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CB18:\n"
                "BL      sub_FF96EAEC\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x20000\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CB28:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF96EC88\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x40000\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CB3C:\n"
                "BL      sub_FF96EF94\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x80000\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CB4C:\n"
                "BL      sub_FF96F00C\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x100000\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CB5C:\n"
                "BL      sub_FF96F058\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x200000\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CB6C:\n"
                "MOV     R0, #1\n"
                "BL      sub_FF96EC88\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x400000\n"
                "B       loc_FF96CB8C\n"
"loc_FF96CB80:\n"
                "BL      sub_FF96F0C0\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x800000\n"
"loc_FF96CB8C:\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF82072C\n"
                "B       loc_FF96CBA8\n"
"loc_FF96CB98:\n"
                "MOV     R1, #0x374\n"
                "LDR     R0, =0xFF96BCE4\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813D58\n"
"loc_FF96CBA8:\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FF96BD64\n"
"loc_FF96CBB0:\n"
                "LDR     R3, =0x5D100\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820F34\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF96CA00\n"
                "LDR     R0, =0xFF96BCE4\n"
                "MOV     R1, #0x2EC\n"
                "BL      sub_FF813D58\n"
                "BL      sub_FF82275C\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

