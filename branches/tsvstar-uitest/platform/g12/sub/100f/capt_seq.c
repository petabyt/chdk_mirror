#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)(0x76fc+0x8); // in _sub_FF98F878__NRTable.c__0
#define NR_AUTO (0)							// have to explictly reset value back to 0 to enable auto

#include "../../../generic/capt_seq.c"

//void __attribute__((naked,noinline)) hangdebug() {
//	debug_led(1);
//	while(1);
//}

//@ FF88261C
void __attribute__((naked,noinline)) capt_seq_task() {

asm volatile (

	"STMFD SP!, {R3-R7,LR}\n"
	"LDR	R7, =0x2E38\n"
	"LDR	R4, =0x3BB24\n"
	"MOV	R6, #0\n"

"loc_FF88262C:\n"
	"LDR	R0, [R7,#4]\n"
	"MOV	R2, #0\n"
	"MOV	R1, SP\n"
	"BL		sub_FF83A460\n"
	"TST	R0, #1\n"
	"BEQ	loc_FF882658\n"
	"LDR	R1, =0x43F\n"
	"LDR	R0, =0xFF8820BC\n"	// aSsshoottask_c
	"BL		_DebugAssert\n"
	"BL		_ExitTask\n"
	"LDMFD SP!, {R3-R7,PC}\n"

"loc_FF882658:\n"
	"LDR	R0, [SP]\n"
	"LDR	R1, [R0]\n"
	"CMP	R1, #0x24\n"
	"ADDLS	PC, PC, R1,LSL#2\n"

"                B       loc_FF8828C4\n"
"loc_FF88266C:\n"
"                B       loc_FF882700\n"
"loc_FF882670:\n"
"                B       loc_FF882718\n"
"loc_FF882674:\n"
"                B       loc_FF88273C\n"
"loc_FF882678:\n"
"                B       loc_FF882750\n"
"loc_FF88267C:\n"
"                B       loc_FF882748\n"
"loc_FF882680:\n"
"                B       loc_FF88275C\n"
"loc_FF882684:\n"
"                B       loc_FF882764\n"
"loc_FF882688:\n"
"                B       loc_FF88276C\n"
"loc_FF88268C:\n"
"                B       loc_FF882778\n"
"loc_FF882690:\n"
"                B       loc_FF8827A0\n"
"loc_FF882694:\n"
"                B       loc_FF882784\n"
"loc_FF882698:\n"
"                B       loc_FF882790\n"
"loc_FF88269C:\n"
"                B       loc_FF882798\n"
"loc_FF8826A0:\n"
"                B       loc_FF8827A8\n"
"loc_FF8826A4:\n"
"                B       loc_FF8827B0\n"
"loc_FF8826A8:\n"
"                B       loc_FF8827B8\n"
"loc_FF8826AC:\n"
"                B       loc_FF8827C0\n"
"loc_FF8826B0:\n"
"                B       loc_FF8827C8\n"
"loc_FF8826B4:\n"
"                B       loc_FF8827D0\n"
"loc_FF8826B8:\n"
"                B       loc_FF8827D8\n"
"loc_FF8826BC:\n"
"                B       loc_FF8827E0\n"
"loc_FF8826C0:\n"
"                B       loc_FF8827E8\n"
"loc_FF8826C4:\n"
"                B       loc_FF8827F0\n"
"loc_FF8826C8:\n"
"                B       loc_FF8827FC\n"
"loc_FF8826CC:\n"
"                B       loc_FF882804\n"
"loc_FF8826D0:\n"
"                B       loc_FF882810\n"
"loc_FF8826D4:\n"
"                B       loc_FF882818\n"
"loc_FF8826D8:\n"
"                B       loc_FF882848\n"
"loc_FF8826DC:\n"
"                B       loc_FF882850\n"
"loc_FF8826E0:\n"
"                B       loc_FF882858\n"
"loc_FF8826E4:\n"
"                B       loc_FF882860\n"
"loc_FF8826E8:\n"
"                B       loc_FF882868\n"
"loc_FF8826EC:\n"
"                B       loc_FF882870\n"
"loc_FF8826F0:\n"
"                B       loc_FF882878\n"
"loc_FF8826F4:\n"
"                B       loc_FF882880\n"
"loc_FF8826F8:\n"
"                B       loc_FF88288C\n"
"loc_FF8826FC:\n"
"                B       loc_FF8828D0\n"

// jump table entry 0
"loc_FF882700:\n"

"		BL	shooting_expo_iso_override\n"  		    // added

"		BL	sub_FF882E00 \n"

"		BL	shooting_expo_param_override\n"  		// added

"		BL	sub_FF87FF5C \n"

"		MOV     R0, #0\n"							// added
"		STR     R0, [R4,#0x24]\n"					// added, fixes overrides  behavior at short shutter press (from S95)

//"		LDR	R0, [R4,#0x24] \n"						// above two lines make this code redundant
//"		CMP	R0, #0 \n"								// above two lines make this code redundant

//"		BLNE	sub_FF98C6A0 \n"					// above two lines make this code redundant
//"		BLNE	sub_FF98C6A0_my \n"					// patched (above two lines make this patch redundant)

"		B	loc_FF8828D0 \n"

// jump table entry 1
"loc_FF882718: \n"
"		LDRH	R1, [R4] \n"
"		LDR		R0, [R0,#0xC] \n"
"		SUB	R12, R1, #0x4200 \n"
"		SUBS	R12, R12, #0x2E \n"
"		BNE		loc_FF882734 \n"
"		BL		sub_FF98D484 \n"
"		B		loc_FF8828D0 \n"

"loc_FF882734: \n"
//"		BL		sub_FF98C4CC \n"
"		BL		sub_FF98C4CC_my \n"					// patched

"		B		loc_FF8828D0 \n"

// jump table entry 2
"loc_FF88273C: \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF883140 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 4
"loc_FF882748: \n"
"		BL	sub_FF882A98 \n"
"		B	loc_FF882754 \n"

// jump table entry 3
"loc_FF882750: \n"
"		BL	sub_FF882DE0 \n"
"loc_FF882754: \n"
"		STR	R6, [R4,#0x24] \n"
"		B	loc_FF8828D0 \n"

// jump table entry 5
"loc_FF88275C: \n"
"		BL	sub_FF882DE8 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 6
"loc_FF882764: \n"
"		BL	sub_FF883014 \n"
"		B	loc_FF88277C \n"

// jump table entry 7
"loc_FF88276C: \n"
"		LDR	R0, [R0,#0xC] \n"
"		BL	sub_FF98C708 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 8
"loc_FF882778: \n"
"		BL	sub_FF8830B0 \n"
"loc_FF88277C: \n"
"		BL	sub_FF87FF5C \n"
"		B	loc_FF8828D0 \n"

// jump table entry 10
"loc_FF882784: \n"
"		LDR	R0, [R4,#0x54] \n"
"		BL	sub_FF883808 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 11
"loc_FF882790: \n"
"		BL	sub_FF883B6C \n"
"		B	loc_FF8828D0 \n"

// jump table entry 12
"loc_FF882798: \n"
"		BL	sub_FF883BD0 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 9
"loc_FF8827A0: \n"
"		BL	sub_FF882DE0 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 13
"loc_FF8827A8: \n"
"		BL	sub_FF98B3B8 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 14
"loc_FF8827B0: \n"
"		BL	sub_FF98B608 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 15
"loc_FF8827B8: \n"
"		BL	sub_FF98B6D4 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 16
"loc_FF8827C0: \n"
"		BL	sub_FF98B7E8 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 17
"loc_FF8827C8: \n"
"		BL	sub_FF98B8E0 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 18
"loc_FF8827D0: \n"
"		MOV	R0, #0 \n"
"		B	loc_FF8827F4 \n"

// jump table entry 19
"loc_FF8827D8: \n"
"		BL	sub_FF98BEA0 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 20
"loc_FF8827E0: \n"
"		BL	sub_FF98BF44 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 21
"loc_FF8827E8: \n"
"		BL	sub_FF98C024 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 22
"loc_FF8827F0: \n"
"		MOV	R0, #1 \n"
"loc_FF8827F4: \n"
"		BL	sub_FF98BD28 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 23
"loc_FF8827FC: \n"
"		BL	sub_FF883380 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 24
"loc_FF882804: \n"
"		BL	sub_FF883428 \n"
"		BL	sub_FF98D9AC \n"
"		B	loc_FF8828D0 \n"

// jump table entry 25
"loc_FF882810: \n"
"		BL	sub_FF98BBB8 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 26
"loc_FF882818: \n"
"		MOV     R2, #2 \n"
"		ADD     R1, R4, #0x60 \n"
"		MOV     R0, #0x6F \n"
"		BL      _GetPropertyCase \n"
"		TST     R0, #1 \n"
"		LDRNE   R1, =0x531 \n"
"		LDRNE   R0, =0xFF8820BC \n"	// aSsshoottask_c
"		BLNE    _DebugAssert \n"
"		LDRH    R0, [R4,#0x60] \n"
"		CMP     R0, #1 \n"
"		BLEQ    sub_FF98BBAC \n"
"		B	loc_FF8828D0 \n"

// jump table entry 27
"loc_FF882848: \n"
"		BL	sub_FF98BC7C \n"
"		B	loc_FF8828D0 \n"

// jump table entry 28
"loc_FF882850: \n"
"		BL	sub_FF98DA7C \n"
"		B	loc_FF8828D0 \n"

// jump table entry 29
"loc_FF882858: \n"
"		BL	sub_FF837D1C \n"
"		B	loc_FF8828D0 \n"

// jump table entry 30
"loc_FF882860: \n"
"		BL	sub_FF8861E8 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 31
"loc_FF882868: \n"
"		BL	sub_FF886274 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 32
"loc_FF882870: \n"
"		BL	sub_FF98C15C \n"
"		B	loc_FF8828D0 \n"

// jump table entry 33
"loc_FF882878: \n"
"		BL	sub_FF98C1C0 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 34
"loc_FF882880: \n"
"		BL	sub_FF8862D0 \n"
"		BL	sub_FF886290 \n"
"		B	loc_FF8828D0 \n"

// jump table entry 35
"loc_FF88288C: \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF98CEAC \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF98CFDC \n"
"		LDRH	R0, [R4,#0x9C] \n"
"		CMP	R0, #4 \n"
"		LDRNEH	R0, [R4] \n"
"		SUBNE	R12, R0, #0x4200 \n"
"		SUBNES	R12, R12, #0x2A \n"
"		BNE	loc_FF8828D0 \n"
"		BL	sub_FF886274 \n"
"		BL	sub_FF886874 \n"
"		BL	sub_FF8866F0 \n"
"		B	loc_FF8828D0 \n"

// jump table default entry
"loc_FF8828C4: \n"
"		LDR	R1, =0x591 \n"
"		LDR	R0, =0xFF8820BC \n"	// aSsshoottask_c
"		BL	_DebugAssert \n"

// jump table entry 36
"loc_FF8828D0: \n"
"		LDR	R0, [SP] \n"
"		LDR	R1, [R0,#4] \n"
"		LDR	R0, [R7] \n"
"		BL	sub_FF88D27C \n"
"		LDR	R5, [SP] \n"
"		LDR	R0, [R5,#8] \n"
"		CMP	R0, #0 \n"
"		LDREQ	R1, =0x115 \n"
"		LDREQ	R0, =0xFF8820BC \n"	// aSsshoottask_c
"		BLEQ	_DebugAssert \n"
"		STR	R6, [R5,#8] \n"
"		B	loc_FF88262C \n"
	);
}

// @ FF98C4CC
void __attribute__((naked,noinline)) sub_FF98C4CC_my(){
asm volatile(
"                STMFD   SP!, {R3-R7,LR} \n"
"                LDR     R5, =0x3BB24 \n"
"                MOV     R4, R0 \n"
"                LDR     R0, [R5,#0x24] \n"
"                MOV     R6, #0 \n"
"                CMP     R0, #0 \n"
"                BNE     loc_FF98C508 \n"
"                MOV     R0, #0xC \n"
"                BL      sub_FF888028 \n"
"                TST     R0, #1 \n"
"                MOVNE   R2, R4 \n"
"                LDMNEFD SP!, {R3-R7,LR} \n"
"                MOVNE   R1, #1 \n"
"                MOVNE   R0, #1 \n"
"                BNE     sub_FF8805CC \n"

"loc_FF98C508: \n"
"                LDR     R0, [R4,#8] \n"
"                LDR     R7, =0x420C \n"
"                ORR     R0, R0, #1 \n"
"                STR     R0, [R4,#8] \n"
"                LDRH    R0, [R5] \n"
"                CMP     R0, R7 \n"
"                BEQ     loc_FF98C598 \n"
"                LDRH    R0, [R5,#0x9A] \n"
"                CMP     R0, #3 \n"
"                BEQ     loc_FF98C5E0 \n"
"                LDR     R0, [R4,#0xC] \n"
"                CMP     R0, #1 \n"
"                BLS     loc_FF98C5A4 \n"
"                LDRH    R0, [R5,#0x98] \n"
"                CMP     R0, #0 \n"
"                BNE     loc_FF98C5E0 \n"
"                LDRH    R0, [R5,#0x94] \n"
"                CMP     R0, #2 \n"
"                BNE     loc_FF98C5B0 \n"
"                BL      sub_FF8834E8 \n"
"                LDRH    R0, [R5] \n"
"                CMP     R0, R7 \n"
"                BEQ     loc_FF98C598 \n"
"                LDRH    R0, [R5,#0x9A] \n"
"                CMP     R0, #3 \n"
"                BEQ     loc_FF98C5E0 \n"
"                LDR     R0, [R4,#0xC] \n"
"                CMP     R0, #1 \n"
"                BLS     loc_FF98C5A4 \n"
"                LDRH    R0, [R5,#0x98] \n"
"                CMP     R0, #0 \n"
"                BNE     loc_FF98C5E0 \n"
"                LDRH    R0, [R5,#0x94] \n"
"                CMP     R0, #2 \n"
"                BEQ     loc_FF98C5DC \n"
"                B       loc_FF98C5B0 \n"

"loc_FF98C598: \n"
"                LDRH    R0, [R5,#0x9A] \n"
"                CMP     R0, #3 \n"
"                BEQ     loc_FF98C5E0 \n"

"loc_FF98C5A4: \n"
"                LDRH    R0, [R5,#0x98] \n"
"                CMP     R0, #0 \n"
"                BNE     loc_FF98C5E0 \n"

"loc_FF98C5B0: \n"
"                LDRH    R0, [R5,#0x94] \n"
"                CMP     R0, #1 \n"
"                BNE     loc_FF98C5E0 \n"
"                LDRH    R0, [R5] \n"
"                CMP     R0, R7 \n"
"                LDRNE   R0, [R4,#0xC] \n"
"                CMPNE   R0, #1 \n"
"                BLS     loc_FF98C5E0 \n"
"                LDR     R0, [R4,#0x10] \n"
"                CMP     R0, #1 \n"
"                BNE     loc_FF98C5E0 \n"

"loc_FF98C5DC: \n"
"                BL      sub_FF98DAB4 \n"

"loc_FF98C5E0: \n"
"                BL      sub_FF98DA7C \n"
"                BL      sub_FF882DF0 \n"
"                LDR     R0, [R5,#0x24] \n"			// before shot XXX
"                CMP     R0, #0 \n"
"                BNE     loc_FF98C678 \n"
"                MOV     R0, R4 \n"
"                BL      sub_FFB07058 \n"
"                TST     R0, #1 \n"
"                BNE     locret_FF98C69C \n"
"                MOV     R0, R4 \n"
"                BL      sub_FFB07474 \n"
"                BL      sub_FF98CC78 \n"
"                MOV     R6, #1 \n"
"                MOV     R0, #2 \n"
"                BL      sub_FF87DF10 \n"			// after pre-flash, before shot XXX

                 "BL      wait_until_remote_button_is_released\n"
                 "BL      capt_seq_hook_set_nr\n"                     // +

"                LDRH    R0, [R5] \n"
"                SUB     R12, R0, #0x8200 \n"
"                SUBS    R12, R12, #0x2D \n"
"                BNE     loc_FF98C668 \n"
"                MOV     R2, #2 \n"
"                ADD     R0, R2, #0x15C \n"
"                MOV     R1, SP \n"
"                STR     R6, [SP] \n"
"                BL      _GetPropertyCase \n"
"                TST     R0, #1 \n"
"                MOVNE   R1, #0xC3 \n"
//"                ADRNE   R0, aSscaptureseq_c \n"
"                LDRNE   R0, =0xFF98C77C \n"
"                BLNE    _DebugAssert \n"
"                LDRH    R0, [SP] \n"
"                CMP     R0, #1 \n"
"                STRHI   R6, [R4,#0xE4] \n"
"                BHI     loc_FF98C688 \n"
"                MOV     R0, #0 \n"
"                STR     R0, [R4,#0xE4] \n"

"loc_FF98C668: \n"
"                MOV     R0, R4 \n"
//"                BL      sub_FFB07970 \n"			// main flash / shot XXX
"                BL      sub_FFB07970_my \n"			// main flash / shot XXX
"                MOV     R6, R0 \n"
"                B       loc_FF98C68C \n"

"loc_FF98C678: \n"
"                LDR     R0, =0x7694 \n"
"                LDR     R0, [R0] \n"
"                CMP     R0, #0 \n"
"                BEQ     loc_FF98C68C \n"

"loc_FF98C688: \n"
"                MOV     R6, #0x1D \n"

"loc_FF98C68C: \n"
"                MOV     R1, R6 \n"
"                MOV     R0, R4 \n"
"                LDMFD   SP!, {R3-R7,LR} \n"
"                B       sub_FFB07164 \n"

"locret_FF98C69C: \n"
"                LDMFD   SP!, {R3-R7,PC} \n"
);
}

// @ FFB07970
void __attribute__((naked,noinline)) sub_FFB07970_my(){
 asm volatile(
"                STMFD   SP!, {R2-R6,LR} \n"
"                MOV     R5, R0 \n"
"                BL      sub_FF98D1A0 \n"
//"                MOVL    R1, 0xFFFFFFFF \n"
"				 MVN     R1, #0 \n"
"                BL      sub_FF88D2B0 \n"
"                LDR     R0, =0xFFB071D4 \n" //sub_FFB071D4
"                MOV     R1, R5 \n"
"                BL      sub_FF8C1CF0 \n"
"                MOV     R0, R5 \n"
"                BL      sub_FFB070EC \n"
"                MOV     R0, R5 \n"
"                BL      sub_FFB0755C \n"
"                MOV     R4, R0 \n"
"                LDR     R1, =0xDE80 \n"
"                MOV     R0, #0x8A \n"
"                MOV     R2, #4 \n"
"                BL      _GetPropertyCase \n"
"                TST     R0, #1 \n"
"                LDRNE   R1, =0x1F6 \n"
//"                ADRNE   R0, aSsstandardcapt ; "SsStandardCaptureSeq.c" \n"
"                LDRNE   R0, =0xFFB07AF8 \n"
"                BLNE    _DebugAssert \n"
"                BL      sub_FF885860 \n"
"                MOV     R0, R4 \n"
"                CMP     R0, #1 \n"
"                MOV     R4, #0 \n"
"                BEQ     loc_FFB07A10 \n"
"                CMP     R0, #2 \n"
"                BEQ     loc_FFB07A20 \n"
"                CMP     R0, #3 \n"
"                BEQ     loc_FFB07A44 \n"
"                CMP     R0, #7 \n"
"                BNE     sub_FFB07A60 \n"   // jump to firmware
"                MOV     R0, #0 \n"
"                BL      sub_FF8C1D20 \n"
"                MOV     R0, #4 \n"
"                STR     R0, [SP,#0x4] \n"

"loc_FFB07A00: \n"
"                ADD     R1, SP, #0x4 \n"
"                MOV     R0, R5 \n"
"                BL      sub_FFB077D4 \n"
"                B       loc_FFB07A3C \n"

"loc_FFB07A10: \n"
"                MOV     R0, #1 \n"
"                BL      sub_FF8C1D20 \n"
"                STR     R4, [SP,#0x4] \n"
"                B       loc_FFB07A00 \n"

"loc_FFB07A20: \n"
"                MOV     R0, #1 \n"
"                BL      sub_FF8C1D20 \n"
"                MOV     R0, #1 \n"
"                STR     R0, [SP,#0x4] \n"
"                MOV     R0, R5 \n"
"                ADD     R1, SP, #0x4 \n"
"                BL      sub_FFB07BCC \n"

"loc_FFB07A3C: \n"

"		BL      capt_seq_hook_raw_here\n"      		// added (16/2/2011, moved here so that long exposures work)

"                MOV     R6, R0 \n"
"                B       sub_FFB07A6C \n"   // jump to firmware

"loc_FFB07A44: \n"
"                MOV     R0, #1 \n"
"                BL      sub_FF8C1D20 \n"
"                ADD     R1, SP, #0x4 \n"
"                MOV     R0, R5 \n"
"                STR     R4, [SP,#0x4] \n"
"                BL      sub_FFB07850 \n"
"                B       loc_FFB07A3C \n"
	 );
}

/*************************************************************/
// @ FF8CC0D0
void __attribute__((naked,noinline)) exp_drv_task(){

 asm volatile(
"                STMFD   SP!, {R4-R9,LR} \n"
"                SUB     SP, SP, #0x24 \n"
"                LDR     R9, =0xBB8 \n"
"                LDR     R8, =0x4954 \n"
"                LDR     R6, =0x58380 \n"
"                MOV     R0, #0 \n"
"                ADD     R7, SP, #0x14 \n"
"                STR     R0, [SP,#0x10] \n"

"loc_FF8CC0F0: \n"
"                LDR     R0, [R8,#0x20] \n"
"                MOV     R2, #0 \n"
"                ADD     R1, SP, #0x20 \n"
"                BL      sub_FF83A460 \n"
"                LDR     R0, [SP,#0x10] \n"
"                CMP     R0, #1 \n"
"                BNE     loc_FF8CC13C \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R0, [R0] \n"
"                CMP     R0, #0x14 \n"
"                CMPNE   R0, #0x15 \n"
"                CMPNE   R0, #0x16 \n"
"                CMPNE   R0, #0x17 \n"
"                BEQ     loc_FF8CC2A0 \n"
"                CMP     R0, #0x29 \n"
"                BEQ     loc_FF8CC228 \n"
"                ADD     R1, SP, #0x10 \n"
"                MOV     R0, #0 \n"
"                BL      sub_FF8CC080 \n"

"loc_FF8CC13C: \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0] \n"
"                CMP     R1, #0x2F \n"
"                BNE     loc_FF8CC16C \n"
"                LDR     R0, [SP,#0x20] \n"
"                BL      sub_FF8CD4A8 \n"
"                LDR     R0, [R8,#0x1C] \n"
"                MOV     R1, #1 \n"
"                BL      sub_FF88D27C \n"
"                BL      _ExitTask \n"
"                ADD     SP, SP, #0x24 \n"
"                LDMFD   SP!, {R4-R9,PC} \n"

"loc_FF8CC16C: \n"
"                CMP     R1, #0x2E \n"
"                BNE     loc_FF8CC188 \n"
"                LDR     R2, [R0,#0x8C]! \n"
"                LDR     R1, [R0,#4] \n"
"                MOV     R0, R1 \n"
"                BLX     R2 \n"
"                B       loc_FF8CC790 \n"

"loc_FF8CC188: \n"
"                CMP     R1, #0x27 \n"
"                BNE     loc_FF8CC1D8 \n"
"                LDR     R0, [R8,#0x1C] \n"
"                MOV     R1, #0x80 \n"
"                BL      sub_FF88D2B0 \n"
"                LDR     R0, =0xFF8C7EC8 \n"
"                MOV     R1, #0x80 \n"
"                BL      sub_FF97EE88 \n"
"                LDR     R0, [R8,#0x1C] \n"
"                MOV     R2, R9 \n"
"                MOV     R1, #0x80 \n"
"                BL      sub_FF88D1BC \n"
"                TST     R0, #1 \n"
"                LDRNE   R1, =0x109D \n"
"                BNE     loc_FF8CC294 \n"

"loc_FF8CC1C4: \n"
"                LDR     R1, [SP,#0x20] \n"
"                LDR     R0, [R1,#0x90] \n"
"                LDR     R1, [R1,#0x8C] \n"
"                BLX     R1 \n"
"                B       loc_FF8CC790 \n"

"loc_FF8CC1D8: \n"
"                CMP     R1, #0x28 \n"
"                BNE     loc_FF8CC220 \n"
"                ADD     R1, SP, #0x10 \n"
"                BL      sub_FF8CC080 \n"
"                LDR     R0, [R8,#0x1C] \n"
"                MOV     R1, #0x100 \n"
"                BL      sub_FF88D2B0 \n"
"                LDR     R0, =0xFF8C7ED8 \n"
"                MOV     R1, #0x100 \n"
"                BL      sub_FF97F818 \n"
"                LDR     R0, [R8,#0x1C] \n"
"                MOV     R2, R9 \n"
"                MOV     R1, #0x100 \n"
"                BL      sub_FF88D1BC \n"
"                TST     R0, #1 \n"
"                BEQ     loc_FF8CC1C4 \n"
"                LDR     R1, =0x10A7 \n"
"                B       loc_FF8CC294 \n"

"loc_FF8CC220: \n"
"                CMP     R1, #0x29 \n"
"                BNE     loc_FF8CC238 \n"

"loc_FF8CC228: \n"
"                LDR     R0, [SP,#0x20] \n"
"                ADD     R1, SP, #0x10 \n"
"                BL      sub_FF8CC080 \n"
"                B       loc_FF8CC1C4 \n"

"loc_FF8CC238: \n"
"                CMP     R1, #0x2C \n"
"                BNE     loc_FF8CC250 \n"
"                BL      sub_FF8BA4F4 \n"
"                BL      sub_FF8BB100 \n"
"                BL      sub_FF8BAC6C \n"
"                B       loc_FF8CC1C4 \n"

"loc_FF8CC250: \n"
"                CMP     R1, #0x2D \n"
"                BNE     loc_FF8CC2A0 \n"
"                LDR     R0, [R8,#0x1C] \n"
"                MOV     R1, #4 \n"
"                BL      sub_FF88D2B0 \n"
"                LDR     R1, =0xFF8C7EF8 \n"
"                LDR     R0, =0xFFFFF400 \n"
"                MOV     R2, #4 \n"
"                BL      sub_FF8B9F70 \n"
"                BL      sub_FF8BA1F8 \n"
"                LDR     R0, [R8,#0x1C] \n"
"                MOV     R2, R9 \n"
"                MOV     R1, #4 \n"
"                BL      sub_FF88D0D8 \n"
"                TST     R0, #1 \n"
"                BEQ     loc_FF8CC1C4 \n"
"                LDR     R1, =0x10Cf \n"

"loc_FF8CC294: \n"
"                LDR     R0, =0xFF8C8590 \n"	//aExpdrv_c
"                BL      _DebugAssert \n"
"                B       loc_FF8CC1C4 \n"

"loc_FF8CC2A0: \n"
"                LDR     R0, [SP,#0x20] \n"
"                MOV     R5, #1 \n"
"                LDR     R1, [R0] \n"
"                CMP     R1, #0x12 \n"
"                CMPNE   R1, #0x13 \n"
"                BNE     loc_FF8CC308 \n"
"                LDR     R1, [R0,#0x7C] \n"
"                ADD     R1, R1, R1,LSL#1 \n"
"                ADD     R1, R0, R1,LSL#2 \n"
"                SUB     R1, R1, #8 \n"
"                LDMIA   R1, {R2-R4} \n"
"                STMIA   R7, {R2-R4} \n"
"                BL      sub_FF8CA7E8 \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R3, [R0,#0x8C] \n"
"                LDR     R2, [R0,#0x90] \n"
"                ADD     R0, R0, #4 \n"
"                BLX     R3 \n"
"                LDR     R0, [SP,#0x20] \n"
"                BL      sub_FF8CD8BC \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R2, [R0,#0x98] \n"
"                LDR     R3, [R0,#0x94] \n"
"                B       loc_FF8CC67C \n"

"loc_FF8CC308: \n"
"                CMP     R1, #0x14 \n"
"                CMPNE   R1, #0x15 \n"
"                CMPNE   R1, #0x16 \n"
"                CMPNE   R1, #0x17 \n"
"                BNE     loc_FF8CC3C0 \n"
"                ADD     R3, SP, #0x10 \n"
"                ADD     R2, SP, #0x04 \n"
"                ADD     R1, SP, #0x14 \n"
"                BL      sub_FF8CAA54 \n"
"                CMP     R0, #1 \n"
"                MOV     R4, R0 \n"
"                CMPNE   R4, #5 \n"
"                BNE     loc_FF8CC35C \n"
"                LDR     R0, [SP,#0x20] \n"
"                MOV     R2, R4 \n"
"                LDR     R1, [R0,#0x7C]! \n"
"                LDR     R12, [R0,#0x10]! \n"
"                LDR     R3, [R0,#4] \n"
"                ADD     R0, SP, #0x04 \n"
"                BLX     R12 \n"
"                B       loc_FF8CC394 \n"

"loc_FF8CC35C: \n"
"                LDR     R0, [SP,#0x20] \n"
"                CMP     R4, #2 \n"
"                LDR     R3, [R0,#0x90] \n"
"                CMPNE   R4, #6 \n"
"                BNE     loc_FF8CC3A8 \n"
"                LDR     R12, [R0,#0x8C] \n"
"                ADD     R0, SP, #0x04 \n"
"                MOV     R2, R4 \n"
"                MOV     R1, #1 \n"
"                BLX     R12 \n"
"                LDR     R0, [SP,#0x20] \n"
"                ADD     R2, SP, #0x04 \n"
"                ADD     R1, SP, #0x14 \n"
"                BL      sub_FF8CBDCC \n"

"loc_FF8CC394: \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R2, [SP,#0x10] \n"
"                MOV     R1, R4 \n"
"                BL      sub_FF8CC020 \n"
"                B       loc_FF8CC684 \n"

"loc_FF8CC3A8: \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R12, [R0,#0x8C] \n"
"                ADD     R0, R0, #4 \n"
"                MOV     R2, R4 \n"
"                BLX     R12 \n"
"                B       loc_FF8CC684 \n"

"loc_FF8CC3C0: \n"
"                CMP     R1, #0x23 \n"
"                CMPNE   R1, #0x24 \n"
"                BNE     loc_FF8CC46C \n"
"                LDR     R1, [R0,#0x7C] \n"
"                ADD     R1, R1, R1,LSL#1 \n"
"                ADD     R1, R0, R1,LSL#2 \n"
"                SUB     R1, R1, #8 \n"
"                LDMIA   R1, {R2-R4} \n"
"                STMIA   R7, {R2-R4} \n"
"                BL      sub_FF8C985C \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R3, [R0,#0x8C] \n"
"                LDR     R2, [R0,#0x90] \n"
"                ADD     R0, R0, #4 \n"
"                BLX     R3 \n"
"                LDR     R0, [SP,#0x20] \n"
"                BL      sub_FF8C9CA8 \n"
"                B       loc_FF8CC684 \n"

"loc_FF8CC46C: \n"
"                ADD     R1, R0, #4 \n"
"                LDMIA   R1, {R2-R4} \n"
"                STMIA   R7, {R2-R4} \n"
"                LDR     R1, [R0] \n"
"                CMP     R1, #0x26 \n"
"                ADDLS   PC, PC, R1,LSL#2 \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC488: \n"
"                B       loc_FF8CC524 \n"
"loc_FF8CC48C: \n"
"                B       loc_FF8CC524 \n"
"loc_FF8CC490: \n"
"                B       loc_FF8CC52C \n"
"loc_FF8CC494: \n"
"                B       loc_FF8CC534 \n"
"loc_FF8CC498: \n"
"                B       loc_FF8CC534 \n"
"loc_FF8CC49C: \n"
"                B       loc_FF8CC534 \n"
"loc_FF8CC4A0: \n"
"                B       loc_FF8CC524 \n"
"loc_FF8CC4A4: \n"
"                B       loc_FF8CC52C \n"
"loc_FF8CC4A8: \n"
"                B       loc_FF8CC534 \n"
"loc_FF8CC4AC: \n"
"                B       loc_FF8CC534 \n"
"loc_FF8CC4B0: \n"
"                B       loc_FF8CC54C \n"
"loc_FF8CC4B4: \n"
"                B       loc_FF8CC54C \n"
"loc_FF8CC4B8: \n"
"                B       loc_FF8CC658 \n"
"loc_FF8CC4BC: \n"
"                B       loc_FF8CC660 \n"
"loc_FF8CC4C0: \n"
"                B       loc_FF8CC660 \n"
"loc_FF8CC4C4: \n"
"                B       loc_FF8CC660 \n"
"loc_FF8CC4C8: \n"
"                B       loc_FF8CC660 \n"
"loc_FF8CC4CC: \n"
"                B       loc_FF8CC668 \n"
"loc_FF8CC4D0: \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC4D4: \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC4D8: \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC4DC: \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC4E0: \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC4E4: \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC4E8: \n"
"                B       loc_FF8CC53C \n"
"loc_FF8CC4EC: \n"
"                B       loc_FF8CC544 \n"
"loc_FF8CC4F0: \n"
"                B       loc_FF8CC544 \n"
"loc_FF8CC4F4: \n"
"                B       loc_FF8CC558 \n"
"loc_FF8CC4F8: \n"
"                B       loc_FF8CC558 \n"
"loc_FF8CC4FC: \n"
"                B       loc_FF8CC560 \n"
"loc_FF8CC500: \n"
"                B       loc_FF8CC598 \n"
"loc_FF8CC504: \n"
"                B       loc_FF8CC5D0 \n"
"loc_FF8CC508: \n"
"                B       loc_FF8CC608 \n"
"loc_FF8CC50C: \n"
"                B       loc_FF8CC640 \n"
"loc_FF8CC510: \n"
"                B       loc_FF8CC640 \n"
"loc_FF8CC514: \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC518: \n"
"                B       loc_FF8CC66C \n"
"loc_FF8CC51C: \n"
"                B       loc_FF8CC648 \n"
"loc_FF8CC520: \n"
"                B       loc_FF8CC650 \n"

"loc_FF8CC524: \n"
//"; jumptable FF8D0B70 entries 0,1,6      ; LOCATION: ExpDrv.c:928
"                BL      sub_FF8C8414 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC52C: \n"
//"; jumptable FF8D0B70 entries 2,7        ; LOCATION: ExpDrv.c:0
"                BL      sub_FF8C86B4 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC534: \n"
//"; jumptable FF8D0B70 entries 3-5,8,9    ; LOCATION: ExpDrv.c:0
"                BL      sub_FF8C88DC \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC53C: \n"
//"; jumptable FF8D0B70 entry 24           ; LOCATION: ExpDrv.c:2
"                BL      sub_FF8C8BB4 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC544: \n"
//"; jumptable FF8D0B70 entries 25,26      ; LOCATION: ExpDrv.c:0
"                BL      sub_FF8C8DCC \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC54C: \n"
//"; jumptable FF8D0B70 entries 10,11      ; LOCATION: ExpDrv.c:2
//"                BL      sub_FF8C90F0 \n"
"                BL      sub_FF8C90F0_my \n"  // patched
"                MOV     R5, #0 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC558: \n"
//"; jumptable FF8D0B70 entries 27,28      ; LOCATION: ExpDrv.c:0
"                BL      sub_FF8C9238 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC560: \n"
//"; jumptable FF8D0B70 entry 29
"                LDRH    R1, [R0,#4] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R6,#2] \n"
"                STRH    R1, [SP,#0x16] \n"
"                LDRH    R1, [R6,#4] \n"
"                STRH    R1, [SP,#0x18] \n"
"                LDRH    R1, [R6,#6] \n"
"                STRH    R1, [SP,#0x1A] \n"
"                LDRH    R1, [R0,#0xC] \n"
"                STRH    R1, [SP,#0x1C] \n"
"                LDRH    R1, [R6,#0xA] \n"
"                STRH    R1, [SP,#0x1E] \n"
"                BL      sub_FF8CD5B4 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC598: \n"
//"; jumptable FF8D0B70 entry 30
"                LDRH    R1, [R0,#4] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R6,#2] \n"
"                STRH    R1, [SP,#0x16] \n"
"                LDRH    R1, [R6,#4] \n"
"                STRH    R1, [SP,#0x18] \n"
"                LDRH    R1, [R6,#6] \n"
"                STRH    R1, [SP,#0x1A] \n"
"                LDRH    R1, [R6,#8] \n"
"                STRH    R1, [SP,#0x1C] \n"
"                LDRH    R1, [R6,#0xA] \n"
"                STRH    R1, [SP,#0x1E] \n"
"                BL      sub_FF8CD6BC \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC5D0: \n"
//"; jumptable FF8D0B70 entry 31
"                LDRH    R1, [R6] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R0,#6] \n"
"                STRH    R1, [SP,#0x16] \n"
"                LDRH    R1, [R6,#4] \n"
"                STRH    R1, [SP,#0x18] \n"
"                LDRH    R1, [R6,#6] \n"
"                STRH    R1, [SP,#0x1A] \n"
"                LDRH    R1, [R6,#8] \n"
"                STRH    R1, [SP,#0x1C] \n"
"                LDRH    R1, [R6,#0xA] \n"
"                STRH    R1, [SP,#0x1E] \n"
"                BL      sub_FF8CD770 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC608: \n"
//"; jumptable FF8D0B70 entry 32
"                LDRH    R1, [R6] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R6,#2] \n"
"                STRH    R1, [SP,#0x16] \n"
"                LDRH    R1, [R6,#4] \n"
"                STRH    R1, [SP,#0x18] \n"
"                LDRH    R1, [R6,#6] \n"
"                STRH    R1, [SP,#0x1A] \n"
"                LDRH    R1, [R0,#0xC] \n"
"                STRH    R1, [SP,#0x1C] \n"
"                LDRH    R1, [R6,#0xA] \n"
"                STRH    R1, [SP,#0x1E] \n"
"                BL      sub_FF8CD818 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC640: \n"
//"; jumptable FF8D0B70 entries 33,34      ; LOCATION: ExpDrv.c:6
"                BL      sub_FF8C9634 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC648: \n"
//"; jumptable FF8D0B70 entry 37           ; LOCATION: ExpDrv.c:10
"                BL      sub_FF8C9DAC \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC650: \n"
//"; jumptable FF8D0B70 entry 38           ; LOCATION: ExpDrv.c:6
"                BL      sub_FF8CA048 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC658: \n"
//"; jumptable FF8D0B70 entry 12           ; LOCATION: ExpDrv.c:2
"                BL      sub_FF8CA228 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC660: \n"
//"; jumptable FF8D0B70 entries 13-16      ; LOCATION: ExpDrv.c:128
"                BL      sub_FF8CA470 \n"
"                B       loc_FF8CC66C \n"

"loc_FF8CC668: \n"
//"; jumptable FF8D0B70 entry 17           ; LOCATION: ExpDrv.c:2
"                BL      sub_FF8CA5E0 \n"

"loc_FF8CC66C: \n"
//"; jumptable FF8D0B70 default entry
//"; jumptable FF8D0B70 entries 18-23,35,36
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0,#0x7C] \n"
"                LDR     R2, [R0,#0x90] \n"
"                LDR     R3, [R0,#0x8C] \n"

"loc_FF8CC67C: \n"
"                ADD     R0, R0, #4 \n"
"                BLX     R3 \n"

"loc_FF8CC684: \n"
"                LDR     R0, [SP,#0x20] \n"
"                LDR     R1, [R0] \n"
"                CMP     R1, #0x10 \n"
"                BEQ     loc_FF8CC6BC \n"
"                BGT     loc_FF8CC6AC \n"
"                CMP     R1, #1 \n"
"                CMPNE   R1, #4 \n"
"                CMPNE   R1, #0xE \n"
"                BNE     loc_FF8CC6CC \n"
"                B       loc_FF8CC6BC \n"

"loc_FF8CC6AC: \n"
"                CMP     R1, #0x13 \n"
"                CMPNE   R1, #0x17 \n"
"                CMPNE   R1, #0x1A \n"
"                BNE     loc_FF8CC6CC \n"

"loc_FF8CC6BC: \n"
"                LDRH    R1, [R6] \n"
"                STRH    R1, [SP,#0x14] \n"
"                LDRH    R1, [R6,#8] \n"
"                STRH    R1, [SP,#0x1C] \n"

"loc_FF8CC6CC: \n"
"                CMP     R5, #1 \n"
"                BNE     loc_FF8CC718 \n"
"                LDR     R1, [R0,#0x7C] \n"
"                MOV     R2, #0xC \n"
"                ADD     R1, R1, R1,LSL#1 \n"
"                ADD     R0, R0, R1,LSL#2 \n"
"                SUB     R4, R0, #8 \n"
"                LDR     R0, =0x58380 \n"
"                ADD     R1, SP, #0x14 \n"
"                BL      sub_FFBB3268 \n"
"                LDR     R0, =0x5838C \n"
"                MOV     R2, #0xC \n"
"                ADD     R1, SP, #0x14 \n"
"                BL      sub_FFBB3268 \n"
"                LDR     R0, =0x58398 \n"
"                MOV     R2, #0xC \n"
"                MOV     R1, R4 \n"
"                BL      sub_FFBB3268 \n"
"                B       loc_FF8CC790 \n"

"loc_FF8CC718: \n"
"                LDR     R0, [R0] \n"
"                MOV     R3, #1 \n"
"                CMP     R0, #0xB \n"
"                BNE     loc_FF8CC75C \n"
"                MOV     R2, #0 \n"
"                STRD    R2, [SP] \n"
"                MOV     R2, #1 \n"
"                MOV     R1, #1 \n"
"                MOV     R0, #0 \n"
"                BL      sub_FF8C81F4 \n"
"                MOV     R3, #1 \n"
"                MOV     R2, #0 \n"
"                STRD    R2, [SP] \n"
"                MOV     R2, #1 \n"
"                MOV     R1, #1 \n"
"                MOV     R0, #0 \n"
"                B       loc_FF8CC78C \n"

"loc_FF8CC75C: \n"
"                MOV     R2, #1 \n"
"                STRD    R2, [SP] \n"
"                MOV     R3, #1 \n"
"                MOV     R1, #1 \n"
"                MOV     R0, #1 \n"
"                BL      sub_FF8C81F4 \n"
"                MOV     R3, #1 \n"
"                MOV     R2, #1 \n"
"                MOV     R1, #1 \n"
"                MOV     R0, #1 \n"
"                STR     R3, [SP] \n"
"                STR     R3, [SP,#0x04] \n"

"loc_FF8CC78C: \n"
"                BL      sub_FF8C835C \n"

"loc_FF8CC790: \n"
"                LDR     R0, [SP,#0x20] \n"
"                BL      sub_FF8CD4A8 \n"
"                B       loc_FF8CC0F0 \n"
 );
}

// @ FF8C90F0
void __attribute__((naked,noinline)) sub_FF8C90F0_my() {
	asm volatile (
"                STMFD   SP!, {R4-R8,LR} \n"
"                LDR     R7, =0x4954 \n"
"                MOV     R4, R0 \n"
"                LDR     R0, [R7,#0x1C] \n"
"                MOV     R1, #0x3E \n"
"                BL      sub_FF88D2B0 \n"
"                LDRSH   R0, [R4,#4] \n"
"                MOV     R2, #0 \n"
"                MOV     R1, #0 \n"
"                BL      sub_FF8C7F4C \n"
"                MOV     R5, R0 \n"
"                LDRSH   R0, [R4,#6] \n"
"                BL      sub_FF8C8068 \n"
"                LDRSH   R0, [R4,#8] \n"
"                BL      sub_FF8C80C0 \n"
"                LDRSH   R0, [R4,#0xA] \n"
"                BL      sub_FF8C8118 \n"
"                LDRSH   R0, [R4,#0xC] \n"
"                MOV     R1, #0 \n"
"                BL      sub_FF8C8170 \n"
"                MOV     R6, R0 \n"
"                LDRSH   R0, [R4,#0xE] \n"
"                BL      sub_FF8CD554 \n"
"                LDR     R0, [R4] \n"
"                LDR     R8, =0x58398 \n"
"                CMP     R0, #0xB \n"
"                MOVEQ   R5, #0 \n"
"                MOVEQ   R6, #0 \n"
"                BEQ     loc_FF8C918C \n"
"                CMP     R5, #1 \n"
"                BNE     loc_FF8C918C \n"
"                LDRSH   R0, [R4,#4] \n"
"                LDR     R1, =0xFF8C7EB8 \n"
"                MOV     R2, #2 \n"
"                BL      sub_FF97F1D4 \n"
"                STRH    R0, [R4,#4] \n"
"                MOV     R0, #0 \n"
"                STR     R0, [R7,#0x28] \n"
"                B       loc_FF8C9194 \n"

"loc_FF8C918C: \n"
"                LDRH    R0, [R8] \n"
"                STRH    R0, [R4,#4] \n"

"loc_FF8C9194: \n"
"                CMP     R6, #1 \n"
"                LDRNEH  R0, [R8,#8] \n"
"                BNE     loc_FF8C91B0 \n"
"                LDRSH   R0, [R4,#0xC] \n"
"                LDR     R1, =0xFF8C7F3C \n"
"                MOV     R2, #0x20 \n"
"                BL      sub_FF8CD570 \n"

"loc_FF8C91B0: \n"
"                STRH    R0, [R4,#0xC] \n"
"                LDRSH   R0, [R4,#6] \n"
//"                BL      sub_FF8BA264 \n"
"                BL      sub_FF8BA264_my \n" // patched
"				B		sub_FF8C91BC \n"	// continue in firmware
	);
}

// @ FF8BA264
void __attribute__((naked,noinline)) sub_FF8BA264_my() {
	asm volatile (
"                STMFD   SP!, {R4-R6,LR} \n"
"                LDR     R5, =0x4638 \n"
"                MOV     R4, R0 \n"
"                LDR     R0, [R5,#4] \n"
"                CMP     R0, #1 \n"
"                LDRNE   R1, =0x146 \n"
"                LDRNE   R0, =0xFF8BA068 \n" //aShutter_c
"                BLNE    _DebugAssert \n"
"                CMN     R4, #0xC00 \n"
"                LDREQSH R4, [R5,#2] \n"
"                CMN     R4, #0xC00 \n"
"                MOVEQ   R1, #0x14C \n"
"                LDRNE   R0, =0xFF8BA068 \n" //aShutter_c
"                STRH    R4, [R5,#2] \n"
"                BLEQ    _DebugAssert \n"
"                MOV     R0, R4 \n"
"                BL      apex2us \n"	// patched
"				B		sub_FF8BA2A8 \n"	// continue in firmware
);
}
