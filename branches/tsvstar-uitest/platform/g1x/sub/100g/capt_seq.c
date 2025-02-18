#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)(0xCEB4+0x4);  // in sub_FF2A76E0 @ FF2A7814 & FF2A791C
#define NR_AUTO (0)							// have to explictly reset value back to 0 to enable auto
#define PAUSE_FOR_FILE_COUNTER 150          // Enable delay in capt_seq_hook_raw_here to ensure file counter is updated

#include "../../../generic/capt_seq.c"

// @ 0xff07b364 in firmware
void __attribute__((naked,noinline)) capt_seq_task() {

asm volatile (
	"STMFD SP!, {R3-R7,LR}\n"
	"LDR	R4, =0x40A00\n"
	"LDR	R7, =0x4070\n"
	"MOV	R6, #0\n"

"loc_FF07B374:\n"
	"LDR	R0, [R7,#4]\n"
	"MOV	R2, #0\n"
	"MOV	R1, SP\n"
	"BL		sub_FF029EA8\n"
	"TST	R0, #1\n"
	"BEQ	loc_FF07B3A0\n"
	"LDR	R1, =0x491\n"
	"LDR	R0, =0xFF07ACB0\n"  //aSsshoottask_c
	"BL		_DebugAssert\n"
	"BL		_ExitTask\n"
	"LDMFD SP!, {R3-R7,PC}\n"

"loc_FF07B3A0:\n"
	"LDR	R0, [SP]\n"
	"LDR	R1, [R0]\n"
	"CMP	R1, #0x28\n"
	"ADDCC	PC, PC, R1,LSL#2\n"
"                B       loc_FF07B62C\n"
"                B       loc_FF07B454\n"
"                B       loc_FF07B46C\n"
"                B       loc_FF07B478\n"
"                B       loc_FF07B48C\n"
"                B       loc_FF07B484\n"
"                B       loc_FF07B498\n"
"                B       loc_FF07B4A0\n"
"                B       loc_FF07B4A8\n"
"                B       loc_FF07B4C4\n"
"                B       loc_FF07B504\n"
"                B       loc_FF07B4D0\n"
"                B       loc_FF07B4DC\n"
"                B       loc_FF07B4E4\n"
"                B       loc_FF07B4EC\n"
"                B       loc_FF07B4F4\n"
"                B       loc_FF07B4FC\n"
"                B       loc_FF07B50C\n"
"                B       loc_FF07B514\n"
"                B       loc_FF07B51C\n"
"                B       loc_FF07B524\n"
"                B       loc_FF07B52C\n"
"                B       loc_FF07B534\n"
"                B       loc_FF07B53C\n"
"                B       loc_FF07B544\n"
"                B       loc_FF07B54C\n"
"                B       loc_FF07B554\n"
"                B       loc_FF07B560\n"
"                B       loc_FF07B568\n"
"                B       loc_FF07B574\n"
"                B       loc_FF07B57C\n"
"                B       loc_FF07B5AC\n"
"                B       loc_FF07B5B4\n"
"                B       loc_FF07B5BC\n"
"                B       loc_FF07B5C4\n"
"                B       loc_FF07B5CC\n"
"                B       loc_FF07B5D4\n"
"                B       loc_FF07B5E0\n"
"                B       loc_FF07B5E8\n"
"                B       loc_FF07B5F4\n"
"                B       loc_FF07B638\n"

// jump table entry 0
"loc_FF07B454:\n"

"		BL	shooting_expo_iso_override\n"  		    // added

"		BL	sub_FF07BC74 \n"

"		BL	shooting_expo_param_override\n"  		// added

"		BL	sub_FF07864C \n"

"		MOV     R0, #0\n"							// added
"		STR     R0, [R4,#0x2C]\n"					// added, fixes overrides behavior at short shutter press (from S95)

//"		LDR	R0, [R4,#0x2C] \n"						// above two lines make this code redundant
//"		CMP	R0, #0 \n"								// above two lines make this code redundant

//"		BLNE	sub_FF1D168C \n"					// above two lines make this code redundant
//"		BLNE	sub_FF1D168C_my \n"					// patched (above two lines make this patch redundant)

"		B	loc_FF07B638 \n"

// jump table entry 1
"loc_FF07B46C: \n"

"       BL      wait_until_remote_button_is_released\n"	// +++
"       BL      capt_seq_hook_set_nr\n"           		// +++

"		LDR     R0, [R0,#0x10]\n"
"       BL      sub_FF07B780\n"

"       BL      capt_seq_hook_raw_here\n"           	// +++

"		B	loc_FF07B638 \n"

// jump table entry 2
"loc_FF07B478: \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF07BFF0 \n"
"		B	loc_FF07B638 \n"

// jump table entry 4
"loc_FF07B484: \n"
"		BL	sub_FF07B8E0 \n"
"		B	loc_FF07B490 \n"

// jump table entry 3
"loc_FF07B48C: \n"
"		BL	sub_FF07BC54 \n"
"loc_FF07B490: \n"
"		STR	R6, [R4,#0x2C] \n"
"		B	loc_FF07B638 \n"

// jump table entry 5
"loc_FF07B498: \n"
"		BL	sub_FF07BC5C \n"
"		B	loc_FF07B638 \n"

// jump table entry 6
"loc_FF07B4A0: \n"
"		BL	sub_FF07BE98 \n"
"		B	loc_FF07B4C8 \n"

// jump table entry 7
"loc_FF07B4A8: \n"
"		LDR	R5, [R0,#0x10] \n"
"       MOV R0, R5 \n"
"		BL	sub_FF1D171C \n"
"       MOV R2, R5 \n"
"       MOV R1, #9 \n"
"		BL	sub_FF0790E8 \n"
"		B	loc_FF07B638 \n"

// jump table entry 8
"loc_FF07B4C4: \n"
"		BL	sub_FF07BF54 \n"
"loc_FF07B4C8: \n"
"		BL	sub_FF07864C \n"
"		B	loc_FF07B638 \n"

// jump table entry 10
"loc_FF07B4D0: \n"
"		LDR	R0, [R4,#0x5C] \n"
"		BL	sub_FF07C910 \n"
"		B	loc_FF07B638 \n"

// jump table entry 11
"loc_FF07B4DC: \n"
"		BL	sub_FF07CBD0 \n"
"		B	loc_FF07B638 \n"

// jump table entry 12
"loc_FF07B4E4: \n"
"		BL	sub_FF07CC34 \n"
"		B	loc_FF07B638 \n"

// jump table entry 13
"loc_FF07B4EC: \n"
"		BL	sub_FF07CE04 \n"
"		B	loc_FF07B638 \n"

// jump table entry 14
"loc_FF07B4F4: \n"
"		BL	sub_FF07D254 \n"
"		B	loc_FF07B638 \n"

// jump table entry 15
"loc_FF07B4FC: \n"
"		BL	sub_FF07D304 \n"
"		B	loc_FF07B638 \n"

// jump table entry 9
"loc_FF07B504: \n"
"		BL	sub_FF07BC54 \n"
"		B	loc_FF07B638 \n"

// jump table entry 16
"loc_FF07B50C: \n"
"		BL	sub_FF1CF20C \n"
"		B	loc_FF07B638 \n"

// jump table entry 17
"loc_FF07B514: \n"
"		BL	sub_FF1CF4F8 \n"
"		B	loc_FF07B638 \n"

// jump table entry 18
"loc_FF07B51C: \n"
"		BL	sub_FF1CF5AC \n"
"		B	loc_FF07B638 \n"

// jump table entry 19
"loc_FF07B524: \n"
"		BL	sub_FF1CF694 \n"
"		B	loc_FF07B638 \n"

// jump table entry 20
"loc_FF07B52C: \n"
"		BL	sub_FF1CF790 \n"
"		B	loc_FF07B638 \n"

// jump table entry 21
"loc_FF07B534: \n"
"		MOV	R0, #0 \n"
"		B	loc_FF07B558 \n"

// jump table entry 22
"loc_FF07B53C: \n"
"		BL	sub_FF1CFDAC \n"
"		B	loc_FF07B638 \n"

// jump table entry 23
"loc_FF07B544: \n"
"		BL	sub_FF1CFE40 \n"
"		B	loc_FF07B638 \n"

// jump table entry 24
"loc_FF07B54C: \n"
"		BL	sub_FF1CFEFC \n"
"		B	loc_FF07B638 \n"

// jump table entry 25
"loc_FF07B554: \n"
"		MOV	R0, #1 \n"
"loc_FF07B558: \n"
"		BL	sub_FF1CFC3C \n"
"		B	loc_FF07B638 \n"

// jump table entry 26
"loc_FF07B560: \n"
"		BL	sub_FF07C260 \n"
"		B	loc_FF07B638 \n"

// jump table entry 27
"loc_FF07B568: \n"
"		BL	sub_FF07C2F4 \n"
"		BL	sub_FF1D2A28 \n"
"		B	loc_FF07B638 \n"

// jump table entry 28
"loc_FF07B574: \n"
"		BL	sub_FF1CFA7C \n"
"		B	loc_FF07B638 \n"

// jump table entry 29
"loc_FF07B57C: \n"
"		MOV     R2, #2 \n"
"		ADD     R1, R4, #0x68 \n"
"		MOV     R0, #0x6F \n"
"		BL      _GetPropertyCase \n"
"		TST     R0, #1 \n"
"		LDRNE   R1, =0x592 \n"
"		LDRNE   R0, =0xFF07ACB0 \n"	//=aSsshoottask_c
"		BLNE    _DebugAssert \n"
"		LDRH    R0, [R4,#0x68] \n"
"		CMP     R0, #1 \n"
"		BLEQ    sub_FF1CFA70 \n"
"		B	loc_FF07B638 \n"

// jump table entry 30
"loc_FF07B5AC: \n"
"		BL	sub_FF1CFB9C \n"
"		B	loc_FF07B638 \n"

// jump table entry 31
"loc_FF07B5B4: \n"
"		BL	sub_FF1D2AF4 \n"
"		B	loc_FF07B638 \n"

// jump table entry 32
"loc_FF07B5BC: \n"
"		BL	sub_FF0272CC \n"
"		B	loc_FF07B638 \n"

// jump table entry 33
"loc_FF07B5C4: \n"
"		BL	sub_FF07FC94 \n"
"		B	loc_FF07B638 \n"

// jump table entry 34
"loc_FF07B5CC: \n"
"		BL	sub_FF07FD1C \n"
"		B	loc_FF07B638 \n"

// jump table entry 35
"loc_FF07B5D4: \n"
"       LDR R0, [R0,#0xC] \n"
"		BL	sub_FF1D0024 \n"
"		B	loc_FF07B638 \n"

// jump table entry 36
"loc_FF07B5E0: \n"
"		BL	sub_FF1D0094 \n"
"		B	loc_FF07B638 \n"

// jump table entry 37
"loc_FF07B5E8: \n"
"		BL	sub_FF07FD84 \n"
"		BL	sub_FF07FD3C \n"
"		B	loc_FF07B638 \n"

// jump table entry 38
"loc_FF07B5F4: \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF1D1E2C \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF1D1F60 \n"
"		LDRH	R0, [R4,#0xA4] \n"
"		CMP	R0, #4 \n"
"		LDRNEH	R0, [R4] \n"
"		SUBNE	R1, R0, #0x4200 \n"
"		SUBNES	R1, R1, #0x2B \n"
"		BNE	loc_FF07B638 \n"
"		BL	sub_FF07FD1C \n"
"		BL	sub_FF080498 \n"
"		BL	sub_FF0801AC \n"
"		B	loc_FF07B638 \n"

// jump table default entry
"loc_FF07B62C: \n"
"		LDR	R1, =0x5F2 \n"
"		LDR	R0, =0xFF07ACB0 \n"				// "SsShootTask.c"
"		BL	_DebugAssert \n"

// jump table entry 39
"loc_FF07B638: \n"
"		LDR	R0, [SP] \n"
"		LDR	R1, [R0,#4] \n"
"		LDR	R0, [R7] \n"
"		BL	 sub_FF087564 \n"
"		LDR	R5, [SP] \n"
"		LDR	R0, [R5,#8] \n"
"		CMP	R0, #0 \n"
"		LDREQ	R1, =0x117 \n"
"		LDREQ	R0, =0xFF07ACB0 \n"			// "SsShootTask.c"
"		BLEQ	_DebugAssert \n"
"		STR	R6, [R5,#8] \n"
"		B	loc_FF07B374 \n"
	);
}

///*----------------------------------------------------------------------
// @ 0xff0cda24
void __attribute__((naked,noinline)) exp_drv_task()
{
 asm volatile(
"                STMFD   SP!, {R4-R9,LR} \n"
"                SUB     SP, SP, #0x24 \n"
"                LDR     R6, =0x5BEC \n"
"                LDR     R7, =0xBB8 \n"
"                LDR     R4, =0x5EDF0 \n"
"                MOV     R0, #0 \n"
"                ADD     R5, SP, #0x14 \n"
"                STR     R0, [SP,#0x10] \n"

"loc_FF0CDA44: \n"
"                LDR     R0, [R6,#0x20] \n"
"                MOV     R2, #0 \n"
"                ADD     R1, SP, #0x20 \n"
"                BL      sub_FF029EA8 \n"
"                LDR     R0, [SP,#0x10] \n"
"                CMP     R0, #1 \n"
"                BNE     loc_FF0CDA94 \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R0, [R0] \n"
"                CMP     R0, #0x14 \n"
"                CMPNE   R0, #0x15 \n"
"                CMPNE   R0, #0x16 \n"
"                CMPNE   R0, #0x17 \n"
"                CMPNE   R0, #0x18 \n"
"                BEQ     loc_FF0CDBF4 \n"
"                CMP     R0, #0x2B \n"
"                BEQ     loc_FF0CDB7C \n"
"                ADD     R1, SP, #0x10 \n"
"                MOV     R0, #0 \n"
"                BL      sub_FF0CD9D4 \n"

"loc_FF0CDA94: \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0] \n"
"                CMP     R1, #0x31 \n"
"                BNE     loc_FF0CDAC0 \n"
"                BL      sub_FF0CEEDC \n"
"                LDR     R0, [R6,#0x1C] \n"
"                MOV     R1, #1 \n"
"                BL      sub_FF087564 \n"
"                BL      _ExitTask \n"
"                ADD     SP, SP, #0x24 \n"
"                LDMFD   SP!, {R4-R9,PC} \n"

"loc_FF0CDAC0: \n"
"                CMP     R1, #0x30 \n"
"                BNE     loc_FF0CDADC \n"
"                LDR     R2, [R0,#0x8C]! \n"
"                LDR     R1, [R0,#4] \n"
"                MOV     R0, R1 \n"
"                BLX     R2 \n"
"                B       loc_FF0CE090 \n"

"loc_FF0CDADC: \n"
"                CMP     R1, #0x29 \n"
"                BNE     loc_FF0CDB2C \n"
"                LDR     R0, [R6,#0x1C] \n"
"                MOV     R1, #0x80 \n"
"                BL      sub_FF087598 \n"
"                LDR     R0, =0xFF0C9078 \n"
"                MOV     R1, #0x80 \n"
"                BL      sub_FF1BEEEC \n"
"                LDR     R0, [R6,#0x1C] \n"
"                MOV     R2, R7 \n"
"                MOV     R1, #0x80 \n"
"                BL      sub_FF0874A4 \n"
"                TST     R0, #1 \n"
"                LDRNE   R1, =0x1572 \n"
"                BNE     loc_FF0CDBE8 \n"

"loc_FF0CDB18: \n"
"                LDR     R1, [SP,#0x20] \n"
"                LDR     R0, [R1,#0x90] \n"
"                LDR     R1, [R1,#0x8C] \n"
"                BLX     R1 \n"
"                B       loc_FF0CE090 \n"

"loc_FF0CDB2C: \n"
"                CMP     R1, #0x2A \n"
"                BNE     loc_FF0CDB74 \n"
"                ADD     R1, SP, #0x10 \n"
"                BL      sub_FF0CD9D4 \n"
"                LDR     R0, [R6,#0x1C] \n"
"                MOV     R1, #0x100 \n"
"                BL      sub_FF087598 \n"
"                LDR     R0, =0xFF0C9088 \n"
"                MOV     R1, #0x100 \n"
"                BL      sub_FF1BFCBC \n"
"                LDR     R0, [R6,#0x1C] \n"
"                MOV     R2, R7 \n"
"                MOV     R1, #0x100 \n"
"                BL      sub_FF0874A4 \n"
"                TST     R0, #1 \n"
"                BEQ     loc_FF0CDB18 \n"
"                LDR     R1, =0x157C \n"
"                B       loc_FF0CDBE8 \n"

"loc_FF0CDB74: \n"
"                CMP     R1, #0x2B \n"
"                BNE     loc_FF0CDB8C \n"

"loc_FF0CDB7C: \n"
"                LDR     R0, [SP,#0x20] \n"
"                ADD     R1, SP, #0x10 \n"
"                BL      sub_FF0CD9D4 \n"
"                B       loc_FF0CDB18 \n"

"loc_FF0CDB8C: \n"
"                CMP     R1, #0x2E \n"
"                BNE     loc_FF0CDBA4 \n"
"                BL      sub_FF0B8F90 \n"
"                BL      sub_FF0B9C8C \n"
"                BL      sub_FF0B97E0 \n"
"                B       loc_FF0CDB18 \n"

" loc_FF0CDBA4: \n"
"                CMP     R1, #0x2F \n"
"                BNE     loc_FF0CDBF4 \n"
"                LDR     R0, [R6,#0x1C] \n"
"                MOV     R1, #4 \n"
"                BL      sub_FF087598 \n"
"                LDR     R1, =0xFF0C90A8 \n"
"                LDR     R0, =0xFFFFF400 \n"
"                MOV     R2, #4 \n"
"                BL      sub_FF0B89E0 \n"
"                BL      sub_FF0B8C70 \n"
"                LDR     R0, [R6,#0x1C] \n"
"                MOV     R2, R7 \n"
"                MOV     R1, #4 \n"
"                BL      sub_FF0873C0 \n"
"                TST     R0, #1 \n"
"                BEQ     loc_FF0CDB18 \n"
"                LDR     R1, =0x15A4 \n"

"loc_FF0CDBE8: \n"
"                LDR     R0, =0xFF0C97F0 \n"    //aExpdrv_c  ; "ExpDrv.c"
"                BL      _DebugAssert \n"
"                B       loc_FF0CDB18 \n"

"loc_FF0CDBF4: \n"
"                LDR     R0, [SP,#0x20] \n"
"                MOV     R8, #1 \n"
"                LDR     R1, [R0] \n"
"                CMP     R1, #0x12 \n"
"                CMPNE   R1, #0x13 \n"
"                BNE     loc_FF0CDC5C \n"
"                LDR     R1, [R0,#0x7C] \n"
"                ADD     R1, R1, R1,LSL#1 \n"
"                ADD     R1, R0, R1,LSL#2 \n"
"                SUB     R1, R1, #8 \n"
"                LDMIA   R1, {R2,R3,R9} \n"
"                STMIA   R5, {R2,R3,R9} \n"
"                BL      sub_FF0CBDE8 \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R3, [R0,#0x8C] \n"
"                LDR     R2, [R0,#0x90] \n"
"                ADD     R0, R0, #4 \n"
"                BLX     R3 \n"
"                LDR     R0, [SP,#0x20] \n"
"                BL      sub_FF0CF2F4 \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R2, [R0,#0x98] \n"
"                LDR     R3, [R0,#0x94] \n"
"                B       loc_FF0CDF7C \n"

"loc_FF0CDC5C: \n"
"                CMP     R1, #0x14 \n"
"                CMPNE   R1, #0x15 \n"
"                CMPNE   R1, #0x16 \n"
"                CMPNE   R1, #0x17 \n"
"                CMPNE   R1, #0x18 \n"
"                BNE     loc_FF0CDD18 \n"
"                ADD     R3, SP, #0x10 \n"
"                ADD     R2, SP, #0x04 \n"
"                ADD     R1, SP, #0x14 \n"
"                BL      sub_FF0CC054 \n"
"                CMP     R0, #1 \n"
"                MOV     R9, R0 \n"
"                CMPNE   R9, #5 \n"
"                BNE     loc_FF0CDCB4 \n"
"                LDR     R0, [SP,#0x20] \n"
"                MOV     R2, R9 \n"
"                LDR     R1, [R0,#0x7C]! \n"
"                LDR     R12, [R0,#0x10]! \n"
"                LDR     R3, [R0,#4] \n"
"                ADD     R0, SP, #0x04 \n"
"                BLX     R12 \n"
"                B       loc_FF0CDCEC \n"

"loc_FF0CDCB4: \n"
"                LDR     R0, [SP,#0x20] \n"
"                CMP     R9, #2 \n"
"                LDR     R3, [R0,#0x90] \n"
"                CMPNE   R9, #6 \n"
"                BNE     loc_FF0CDD00 \n"
"                LDR     R12, [R0,#0x8C] \n"
"                MOV     R2, R9 \n"
"                MOV     R1, #1 \n"
"                ADD     R0, SP, #0x04 \n"
"                BLX     R12 \n"
"                LDR     R0, [SP,#0x20] \n"
"                ADD     R2, SP, #0x04 \n"
"                ADD     R1, SP, #0x14 \n"
"                BL      sub_FF0CD720 \n"

"loc_FF0CDCEC: \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R2, [SP,#0x10] \n"
"                MOV     R1, R9 \n"
"                BL      sub_FF0CD974 \n"
"                B       loc_FF0CDF84 \n"

"loc_FF0CDD00: \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R12, [R0,#0x8C] \n"
"                MOV     R2, R9 \n"
"                ADD     R0, R0, #4 \n"
"                BLX     R12 \n"
"                B       loc_FF0CDF84 \n"

"loc_FF0CDD18: \n"
"                CMP     R1, #0x25 \n"
"                CMPNE   R1, #0x26 \n"
"                BNE     loc_FF0CDD64 \n"
"                LDR     R1, [R0,#0x7C] \n"
"                ADD     R1, R1, R1,LSL#1 \n"
"                ADD     R1, R0, R1,LSL#2 \n"
"                SUB     R1, R1, #8 \n"
"                LDMIA   R1, {R2,R3,R9} \n"
"                STMIA   R5, {R2,R3,R9} \n"
"                BL      sub_FF0CADB4 \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R3, [R0,#0x8C] \n"
"                LDR     R2, [R0,#0x90] \n"
"                ADD     R0, R0, #4 \n"
"                BLX     R3 \n"
"                LDR     R0, [SP,#0x20] \n"
"                BL      sub_FF0CB210 \n"
"                B       loc_FF0CDF84 \n"

"loc_FF0CDD64: \n"
"                ADD     R1, R0, #4 \n"
"                LDMIA   R1, {R2,R3,R9} \n"
"                STMIA   R5, {R2,R3,R9} \n"
"                LDR     R1, [R0] \n"
"                CMP     R1, #0x29 \n"
"                ADDCC   PC, PC, R1,LSL#2 \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDE24 \n"
"                B       loc_FF0CDE24 \n"
"                B       loc_FF0CDE2C \n"
"                B       loc_FF0CDE34 \n"
"                B       loc_FF0CDE34 \n"
"                B       loc_FF0CDE34 \n"
"                B       loc_FF0CDE24 \n"
"                B       loc_FF0CDE2C \n"
"                B       loc_FF0CDE34 \n"
"                B       loc_FF0CDE34 \n"
"                B       loc_FF0CDE4C \n"
"                B       loc_FF0CDE4C \n"
"                B       loc_FF0CDF58 \n"
"                B       loc_FF0CDF60 \n"
"                B       loc_FF0CDF60 \n"
"                B       loc_FF0CDF60 \n"
"                B       loc_FF0CDF60 \n"
"                B       loc_FF0CDF68 \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDE3C \n"
"                B       loc_FF0CDE44 \n"
"                B       loc_FF0CDE44 \n"
"                B       loc_FF0CDE44 \n"
"                B       loc_FF0CDE58 \n"
"                B       loc_FF0CDE58 \n"
"                B       loc_FF0CDE60 \n"
"                B       loc_FF0CDE98 \n"
"                B       loc_FF0CDED0 \n"
"                B       loc_FF0CDF08 \n"
"                B       loc_FF0CDF40 \n"
"                B       loc_FF0CDF40 \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDF6C \n"
"                B       loc_FF0CDF48 \n"
"                B       loc_FF0CDF50 \n"

"loc_FF0CDE24: \n"
//"; jumptable FF0CC77C entries 0,1,6
"                BL      sub_FF0C962C \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDE2C: \n"
//"; jumptable FF0CC77C entries 2,7
"                BL      sub_FF0C9920 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDE34: \n"
//"; jumptable FF0CC77C entries 3-5,8,9
"                BL      sub_FF0C9B8C \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDE3C: \n"
//"; jumptable FF0CC77C entry 25
"                BL      sub_FF0C9E84 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDE44: \n"
//"; jumptable FF0CC77C entries 26-28
"                BL      sub_FF0CA0A0 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDE4C: \n"
//"; jumptable FF0CC77C entries 10,11
//"                BL      sub_FF0CA478 \n"
"                BL      sub_FF0CA478_my \n"  // patched
"                MOV     R8, #0 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDE58: \n"
//"; jumptable FF0CC77C entries 29,30
"                BL      sub_FF0CA5C0 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDE60: \n"
//"; jumptable FF0CC77C entry 31
"                LDRH    R1, [R0,#4] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R4,#2] \n"
"                STRH    R1, [SP,#0x16] \n"
"                LDRH    R1, [R4,#4] \n"
"                STRH    R1, [SP,#0x18] \n"
"                LDRH    R1, [R4,#6] \n"
"                STRH    R1, [SP,#0x1A] \n"
"                LDRH    R1, [R0,#0xC] \n"
"                STRH    R1, [SP,#0x1C] \n"
"                LDRH    R1, [R4,#0xA] \n"
"                STRH    R1, [SP,#0x1E] \n"
"                BL      sub_FF0CEF70 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDE98: \n"
//"; jumptable FF0CC77C entry 32
"                LDRH    R1, [R0,#4] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R4,#2] \n"
"                STRH    R1, [SP,#0x16] \n"
"                LDRH    R1, [R4,#4] \n"
"                STRH    R1, [SP,#0x18] \n"
"                LDRH    R1, [R4,#6] \n"
"                STRH    R1, [SP,#0x1A] \n"
"                LDRH    R1, [R4,#8] \n"
"                STRH    R1, [SP,#0x1C] \n"
"                LDRH    R1, [R4,#0xA] \n"
"                STRH    R1, [SP,#0x1E] \n"
"                BL      sub_FF0CF0F4 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDED0: \n"
//"; jumptable FF0CC77C entry 33
"                LDRH    R1, [R4] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R0,#6] \n"
"                STRH    R1, [SP,#0x16] \n"
"                LDRH    R1, [R4,#4] \n"
"                STRH    R1, [SP,#0x18] \n"
"                LDRH    R1, [R4,#6] \n"
"                STRH    R1, [SP,#0x1A] \n"
"                LDRH    R1, [R4,#8] \n"
"                STRH    R1, [SP,#0x1C] \n"
"                LDRH    R1, [R4,#0xA] \n"
"                STRH    R1, [SP,#0x1E] \n"
"                BL      sub_FF0CF1A8 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDF08: \n"
//"; jumptable FF0CC77C entry 34
"                LDRH    R1, [R4] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R4,#2] \n"
"                STRH    R1, [SP,#0x16] \n"
"                LDRH    R1, [R4,#4] \n"
"                STRH    R1, [SP,#0x18] \n"
"                LDRH    R1, [R4,#6] \n"
"                STRH    R1, [SP,#0x1A] \n"
"                LDRH    R1, [R0,#0xC] \n"
"                STRH    R1, [SP,#0x1C] \n"
"                LDRH    R1, [R4,#0xA] \n"
"                STRH    R1, [SP,#0x1E] \n"
"                BL      sub_FF0CF250 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDF40: \n"
//"; jumptable FF0CC77C entries 35,36
"                BL      sub_FF0CAB48 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDF48: \n"
//"; jumptable FF0CC77C entry 39
"                BL      sub_FF0CB314 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDF50: \n"
//"; jumptable FF0CC77C entry 40
"                BL      sub_FF0CB684 \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDF58: \n"
//"; jumptable FF0CC77C entry 12
"                BL      sub_FF0CB8AC \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDF60: \n"
//"; jumptable FF0CC77C entries 13-16
"                BL      sub_FF0CBA6C \n"
"                B       loc_FF0CDF6C \n"

"loc_FF0CDF68: \n"
//"; jumptable FF0CC77C entry 17
"                BL      sub_FF0CBBDC \n"

"loc_FF0CDF6C: \n"
//"; jumptable FF0CC77C default entry
//"; jumptable FF0CC77C entries 18-24,37,38
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R2, [R0,#0x90] \n"
"                LDR     R3, [R0,#0x8C] \n"

"loc_FF0CDF7C: \n"
"                ADD     R0, R0, #4 \n"
"                BLX     R3 \n"

"loc_FF0CDF84: \n"
"                LDR     R1, [SP,#0x20] \n"
"                LDR     R0, [R1] \n"
"                CMP     R0, #0x10 \n"
"                BEQ     loc_FF0CDFBC \n"
"                BGT     loc_FF0CDFAC \n"
"                CMP     R0, #1 \n"
"                CMPNE   R0, #4 \n"
"                CMPNE   R0, #0xE \n"
"                BNE     loc_FF0CDFCC \n"
"                B       loc_FF0CDFBC \n"

"loc_FF0CDFAC: \n"
"                CMP     R0, #0x13 \n"
"                CMPNE   R0, #0x18 \n"
"                CMPNE   R0, #0x1B \n"
"                BNE     loc_FF0CDFCC \n"

"loc_FF0CDFBC: \n"
"                LDRH    R0, [R4] \n"
"                STRH    R0, [SP,#0x14] \n"
"                LDRH    R0, [R4,#8] \n"
"                STRH    R0, [SP,#0x1C] \n"

"loc_FF0CDFCC: \n"
"                CMP     R8, #1 \n"
"                BNE     loc_FF0CE018 \n"
"                LDR     R0, [R1,#0x7C] \n"
"                MOV     R2, #0xC \n"
"                ADD     R0, R0, R0,LSL#1 \n"
"                ADD     R0, R1, R0,LSL#2 \n"
"                SUB     R8, R0, #8 \n"
"                LDR     R0, =0x5EDF0 \n"
"                ADD     R1, SP, #0x14 \n"
"                BL      sub_FF45F614 \n"
"                LDR     R0, =0x5EDFC \n"
"                MOV     R2, #0xC \n"
"                ADD     R1, SP, #0x14 \n"
"                BL      sub_FF45F614 \n"
"                LDR     R0, =0x5EE08 \n"
"                MOV     R2, #0xC \n"
"                MOV     R1, R8 \n"
"                BL      sub_FF45F614 \n"
"                B       loc_FF0CE090 \n"

"loc_FF0CE018: \n"
"                LDR     R0, [R1] \n"
"                MOV     R3, #1 \n"
"                CMP     R0, #0xB \n"
"                BNE     loc_FF0CE05C \n"
"                MOV     R2, #0 \n"
"                STRD    R2, [SP] \n"
"                MOV     R2, R3 \n"
"                MOV     R1, R3 \n"
"                MOV     R0, #0 \n"
"                BL      sub_FF0C9400 \n"
"                MOV     R3, #1 \n"
"                MOV     R2, #0 \n"
"                STRD    R2, [SP] \n"
"                MOV     R2, R3 \n"
"                MOV     R1, R3 \n"
"                MOV     R0, #0 \n"
"                B       loc_FF0CE08C \n"

"loc_FF0CE05C: \n"
"                MOV     R2, #1 \n"
"                STRD    R2, [SP] \n"
"                MOV     R3, R2 \n"
"                MOV     R1, R2 \n"
"                MOV     R0, R2 \n"
"                BL      sub_FF0C9400 \n"
"                MOV     R3, #1 \n"
"                MOV     R2, R3 \n"
"                MOV     R1, R3 \n"
"                MOV     R0, R3 \n"
"                STR     R3, [SP] \n"
"                STR     R3, [SP,#0x04] \n"

"loc_FF0CE08C: \n"
"                BL      sub_FF0C9578 \n"

"loc_FF0CE090: \n"
"                LDR     R0, [SP,#0x20] \n"
"                BL      sub_FF0CEEDC \n"
"                B       loc_FF0CDA44 \n"
 );
}

void __attribute__((naked,noinline)) sub_FF0CA478_my() {
	asm volatile (
"                STMFD   SP!, {R4-R8,LR} \n"
"                LDR     R7, =0x5BEC \n"
"                MOV     R4, R0 \n"
"                LDR     R0, [R7,#0x1C] \n"
"                MOV     R1, #0x3E \n"
"                BL      sub_FF087598 \n"
"                MOV     R2, #0 \n"
"                LDRSH   R0, [R4,#4] \n"
"                MOV     R1, R2 \n"
"                BL      sub_FF0C9108 \n"
"                MOV     R5, R0 \n"
"                LDRSH   R0, [R4,#6] \n"
"                BL      sub_FF0C9258 \n"
"                LDRSH   R0, [R4,#8] \n"
"                BL      sub_FF0C92B0 \n"
"                LDRSH   R0, [R4,#0xA] \n"
"                BL      sub_FF0C9308 \n"
"                LDRSH   R0, [R4,#0xC] \n"
"                MOV     R1, #0 \n"
"                BL      sub_FF0C9360 \n"
"                MOV     R6, R0 \n"
"                LDRSH   R0, [R4,#0xE] \n"
"                BL      sub_FF0CEF0C \n"
"                LDR     R0, [R4] \n"
"                LDR     R8, =0x5EE08 \n"
"                CMP     R0, #0xB \n"
"                MOVEQ   R5, #0 \n"
"                MOVEQ   R6, R5 \n"
"                BEQ     loc_FF0CA514 \n"
"                CMP     R5, #1 \n"
"                BNE     loc_FF0CA514 \n"
"                LDRSH   R0, [R4,#4] \n"
"                LDR     R1, =0xFF0C9068 \n"
"                MOV     R2, #2 \n"
"                BL      sub_FF1BF210 \n"
"                STRH    R0, [R4,#4] \n"
"                MOV     R0, #0 \n"
"                STR     R0, [R7,#0x28] \n"
"                B       loc_FF0CA51C \n"

"loc_FF0CA514: \n"
"                LDRH    R0, [R8] \n"
"                STRH    R0, [R4,#4] \n"

"loc_FF0CA51C: \n"
"                CMP     R6, #1 \n"
"                LDRNEH  R0, [R8,#8] \n"
"                BNE     loc_FF0CA538 \n"
"                LDRSH   R0, [R4,#0xC] \n"
"                LDR     R1, =0xFF0C90EC \n"
"                MOV     R2, #0x20 \n"
"                BL      sub_FF0CEF2C \n"

"loc_FF0CA538: \n"
"                STRH    R0, [R4,#0xC] \n"
"                LDRSH   R0, [R4,#6] \n"
//"                BL      sub_FF0B8CDC \n"
"                BL      sub_FF0B8CDC_my \n" // patched
"				 B	     sub_FF0CA544 \n"	 // continue in firmware
	);
}

void __attribute__((naked,noinline)) sub_FF0B8CDC_my() {
	asm volatile (
"                STMFD   SP!, {R4-R6,LR} \n"
"                LDR     R5, =0x5884 \n"
"                MOV     R4, R0 \n"
"                LDR     R0, [R5,#4] \n"
"                CMP     R0, #1 \n"
"                LDRNE   R1, =0x14D \n"
"                LDRNE   R0, =0xFF0B8B14 \n"	//  ; "Shutter.c"
"                BLNE    _DebugAssert \n"
"                CMN     R4, #0xC00 \n"
"                LDREQSH R4, [R5,#2] \n"
"                CMN     R4, #0xC00 \n"
"                LDREQ   R1, =0x153 \n"
"                LDRNE   R0, =0xFF0B8B14 \n"	//  ; "Shutter.c"
"                STRH    R4, [R5,#2] \n"
"                BLEQ    _DebugAssert \n"
"                MOV     R0, R4 \n"
"                BL      apex2us \n"		// patched
"				 B	     sub_FF0B8D20 \n"	// continue in firmware
);
}
