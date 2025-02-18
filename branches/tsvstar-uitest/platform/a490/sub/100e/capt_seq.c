#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)0x57F8;	// ??? ROM:FFD10DA8 "ShutterSoundTask"

#include "../../../generic/capt_seq.c"

// ROM:FFC5919C task_CaptSeqTask()

void __attribute__((naked,noinline)) capt_seq_task() {
	asm volatile (
			"STMFD   SP!, {R3-R7,LR}\n"
			"LDR     R7, =0x33284\n"
			"LDR     R6, =0x26C0\n"
"loc_FFC591A8:\n"
			"LDR     R0, [R6,#4]\n"
			"MOV     R2, #0\n"
			"MOV     R1, SP\n"
			"BL      sub_FFC28AA4\n"
			"TST     R0, #1\n"
			"BEQ     loc_FFC591D4\n"
			"LDR     R1, =0x5B4\n"
			"LDR     R0, =0xFFC58DA8\n"
			"BL      sub_FFC0F680\n"
			"BL      sub_FFC0F438\n"
			"LDMFD   SP!, {R3-R7,PC}\n"
"loc_FFC591D4:\n"
			"LDR     R0, [SP]\n"
			"LDR     R1, [R0]\n"
			"CMP     R1, #0x1D\n"
			"ADDLS   PC, PC, R1,LSL#2\n"
			"B       loc_FFC593E4\n"
			"B       loc_FFC59260\n"
			"B       loc_FFC59268\n"
			"B       loc_FFC59290\n"
			"B       loc_FFC592A4\n"
			"B       loc_FFC5929C\n"
			"B       loc_FFC592AC\n"
			"B       loc_FFC592B4\n"
			"B       loc_FFC592C0\n"
			"B       loc_FFC59318\n"
			"B       loc_FFC592A4\n"
			"B       loc_FFC59320\n"
			"B       loc_FFC5932C\n"
			"B       loc_FFC59334\n"
			"B       loc_FFC5933C\n"
			"B       loc_FFC59344\n"
			"B       loc_FFC5934C\n"
			"B       loc_FFC59354\n"
			"B       loc_FFC5935C\n"
			"B       loc_FFC59368\n"
			"B       loc_FFC59370\n"
			"B       loc_FFC59378\n"
			"B       loc_FFC59380\n"
			"B       loc_FFC59388\n"
			"B       loc_FFC59394\n"
			"B       loc_FFC5939C\n"
			"B       loc_FFC593A4\n"
			"B       loc_FFC593AC\n"
			"B       loc_FFC593B4\n"
			"B       loc_FFC593C0\n"
			"B       loc_FFC593F0\n"
"loc_FFC59260:\n"
			"BL      sub_FFC59A74\n"
			"BL      shooting_expo_param_override\n"      // +
			"B       loc_FFC592B8\n"
"loc_FFC59268:\n"
			"MOV     R0, #0xC\n"
			"BL      sub_FFC5D758\n"
			"TST     R0, #1\n"
			"LDR     R0, [SP]\n"
			"MOVNE   R1, #1\n"
			"LDRNE   R2, [R0,#0xC]\n"
			"MOVNE   R0, #1\n"
			"BNE     loc_FFC59310\n"
			"BL      sub_FFC5950C_my\n"  //--------->
			"B       loc_FFC593F0\n"
"loc_FFC59290:\n"
			"MOV     R0, #1\n"
			"BL      sub_FFC59CFC\n"
			"B       loc_FFC593F0\n"
"loc_FFC5929C:\n"
			"BL      sub_FFC596E0\n"
			"B       loc_FFC593F0\n"
"loc_FFC592A4:\n"
			"BL      sub_FFC59A54\n"
			"B       loc_FFC593F0\n"
"loc_FFC592AC:\n"
			"BL      sub_FFC59A5C\n"
			"B       loc_FFC593F0\n"
"loc_FFC592B4:\n"
			"BL      sub_FFC59C0C\n"
"loc_FFC592B8:\n"
			"BL      sub_FFC574B4\n"
			"B       loc_FFC593F0\n"
"loc_FFC592C0:\n"
			"LDR     R4, [R0,#0xC]\n"
			"BL      sub_FFC59A64\n"
			"MOV     R0, R4\n"
			"BL      sub_FFD0FD5C\n"
			"TST     R0, #1\n"
			"MOV     R5, R0\n"
			"BNE     loc_FFC59300\n"
			"BL      sub_FFC69634\n"
			"STR     R0, [R4,#0x18]\n"
			"MOV     R0, R4\n"
			"BL      sub_FFD10CCC\n"
			"MOV     R0, R4\n"
			"BL      sub_FFD1106C\n"
			"MOV     R5, R0\n"
			"LDR     R0, [R4,#0x18]\n"
			"BL      sub_FFC6986C\n"
"loc_FFC59300:\n"
			"BL      sub_FFC59A54\n"
			"MOV     R2, R4\n"
			"MOV     R1, #9\n"
			"MOV     R0, R5\n"
"loc_FFC59310:\n"
			"BL      sub_FFC578AC\n"
			"B       loc_FFC593F0\n"
"loc_FFC59318:\n"
			"BL      sub_FFC59C74\n"
			"B       loc_FFC592B8\n"
"loc_FFC59320:\n"
			"LDR     R0, [R7,#0x4C]\n"
			"BL      sub_FFC5A01C\n"
			"B       loc_FFC593F0\n"
"loc_FFC5932C:\n"
			"BL      sub_FFC5A2CC\n"
			"B       loc_FFC593F0\n"
"loc_FFC59334:\n"
			"BL      sub_FFC5A360\n"
			"B       loc_FFC593F0\n"
"loc_FFC5933C:\n"
			"BL      sub_FFD0FF88\n"
			"B       loc_FFC593F0\n"
"loc_FFC59344:\n"
			"BL      sub_FFD10180\n"
			"B       loc_FFC593F0\n"
"loc_FFC5934C:\n"
			"BL      sub_FFD10214\n"
			"B       loc_FFC593F0\n"
"loc_FFC59354:\n"
			"BL      sub_FFD102D4\n"
			"B       loc_FFC593F0\n"
"loc_FFC5935C:\n"
			"MOV     R0, #0\n"
			"BL      sub_FFD104CC\n"
			"B       loc_FFC593F0\n"
"loc_FFC59368:\n"
			"BL      sub_FFD1061C\n"
			"B       loc_FFC593F0\n"
"loc_FFC59370:\n"
			"BL      sub_FFD106AC\n"
			"B       loc_FFC593F0\n"
"loc_FFC59378:\n"
			"BL      sub_FFD1076C\n"
			"B       loc_FFC593F0\n"
"loc_FFC59380:\n"
			"BL      sub_FFC59E58\n"
			"B       loc_FFC593F0\n"
"loc_FFC59388:\n"
			"BL      sub_FFC59E94\n"
			"BL      sub_FFC26C7C\n"
			"B       loc_FFC593F0\n"
"loc_FFC59394:\n"
			"BL      sub_FFD103A0\n"
			"B       loc_FFC593F0\n"
"loc_FFC5939C:\n"
			"BL      sub_FFD103E4\n"
			"B       loc_FFC593F0\n"
"loc_FFC593A4:\n"
			"BL      sub_FFC5BF9C\n"
			"B       loc_FFC593F0\n"
"loc_FFC593AC:\n"
			"BL      sub_FFC5C01C\n"
			"B       loc_FFC593F0\n"
"loc_FFC593B4:\n"
			"BL      sub_FFC5C078\n"
			"BL      sub_FFC5C038\n"
			"B       loc_FFC593F0\n"
"loc_FFC593C0:\n"
			"LDRH    R0, [R7,#0x8C]\n"
			"CMP     R0, #4\n"
			"LDRNEH  R0, [R7]\n"
			"SUBNE   R12, R0, #0x8200\n"
			"SUBNES  R12, R12, #0x2A\n"
			"BNE     loc_FFC593F0\n"
			"BL      sub_FFC5C01C\n"
			"BL      sub_FFC5C3BC\n"
			"B       loc_FFC593F0\n"
"loc_FFC593E4:\n"
			"LDR     R1, =0x70B\n"
			"LDR     R0, =0xFFC58DA8\n"
			"BL      sub_FFC0F680\n"	//DebugAssert
"loc_FFC593F0:\n"
			"LDR     R0, [SP]\n"
			"LDR     R1, [R0,#4]\n"
			"LDR     R0, [R6]\n"
			"BL      sub_FFC28814\n"
			"LDR     R4, [SP]\n"
			"LDR     R0, [R4,#8]\n"
			"CMP     R0, #0\n"
			"LDREQ   R1, =0x132\n"
			"LDREQ   R0, =0xFFC58DA8\n"
			"BLEQ    sub_FFC0F680\n"
			"MOV     R0, #0\n"
			"STR     R0, [R4,#8]\n"
			"B       loc_FFC591A8\n"
	);
}


void __attribute__((naked,noinline)) sub_FFC5950C_my(){ //
	asm volatile(
			"STMFD   SP!, {R3-R5,LR}\n"
			"LDR     R4, [R0,#0xC]\n"
			"LDR     R0, [R4,#8]\n"
			"ORR     R0, R0, #1\n"
			"STR     R0, [R4,#8]\n"
			"BL      sub_FFC59A64\n"
			"MOV     R0, R4\n"
			"BL      sub_FFC59E0C\n"
			"MOV     R0, R4\n"
			"BL      sub_FFD0F9C8\n"
			"CMP     R0, #0\n"
			"MOV     R0, R4\n"
			"BEQ     loc_FFC5955C\n"
			"BL      sub_FFD0FA54\n"
			"TST     R0, #1\n"
			"MOVNE   R2, R4\n"
			"LDMNEFD SP!, {R3-R5,LR}\n"
			"MOVNE   R1, #1\n"
			"BNE     sub_FFC578AC\n"
			"B       loc_FFC59560\n"
"loc_FFC5955C:\n"
			"BL      sub_FFD0FA18\n"
"loc_FFC59560:\n"
			"MOV     R0, #0\n"
			"STR     R0, [SP]\n"
			"LDR     R0, =0x33284\n"
			"MOV     R2, #2\n"
			"LDRH    R0, [R0,#0x8A]\n"
			"MOV     R1, SP\n"
			"CMP     R0, #3\n"
			"LDRNE   R0, [R4,#0xC]\n"
			"CMPNE   R0, #1\n"
			"MOVHI   R0, #1\n"
			"STRHI   R0, [SP]\n"
			"LDR     R0, =0x127\n"
			"BL      sub_FFC69374\n"
			"BL      sub_FFC69634\n"
			"STR     R0, [R4,#0x18]\n"
			"MOV     R0, R4\n"
			"BL      sub_FFD10CCC\n"
			"BL      sub_FFD116EC\n"
			"MOV     R0, R4\n"
			"BL      sub_FFD10D94_my\n"			//---------->
			"MOV     R5, R0\n"
			"BL      capt_seq_hook_raw_here\n"	// +
			"BL      sub_FFC5C01C\n"
			"BL      sub_FFC5C064\n"
			"BL      sub_FFC5C0A4\n"
			"MOV     R2, R4\n"
			"MOV     R1, #1\n"
			"MOV     R0, R5\n"
			"BL      sub_FFC578AC\n"
			"BL      sub_FFD11020\n"
			"CMP     R0, #0\n"
			"LDRNE   R0, [R4,#8]\n"
			"ORRNE   R0, R0, #0x2000\n"
			"STRNE   R0, [R4,#8]\n"
			"LDMFD   SP!, {R3-R5,PC}\n"
	);
}




void __attribute__((naked,noinline)) sub_FFD10D94_my(){ //
	asm volatile(
			"STMFD   SP!, {R0-R8,LR}\n"
			"MOV     R4, R0\n"
			"BL      sub_FFD11880\n"
			"MOV     R1, #0xFFFFFFFF\n"
			"BL      sub_FFC28848\n"
			"LDR     R5, =0x57F8\n"
			"LDR     R0, [R5,#0xC]\n"
			"CMP     R0, #0\n"
			"BNE     loc_FFD10DE4\n"
			"MOV     R1, #1\n"
			"MOV     R0, #0\n"
			"BL      sub_FFC0F4B4\n"
			"STR     R0, [R5,#0xC]\n"
			"MOV     R3, #0\n"
			"STR     R3, [SP]\n"
			"LDR     R3, =0xFFD1085C\n"
			"LDR     R0, =0xFFD10FF8\n"
			"MOV     R2, #0x400\n"
			"MOV     R1, #0x17\n"
			"BL      sub_FFC0F480\n"	// KernelCreateTask
"loc_FFD10DE4:\n"
			"MOV     R2, #4\n"
			"ADD     R1, SP, #8\n"
			"MOV     R0, #0x8A\n"
			"BL      sub_FFC694A4\n"	// PT_GetPropertyCaseString
			"TST     R0, #1\n"
			"LDRNE   R1, =0x3B4\n"		// 0x3BA
			"LDRNE   R0, =0xFFD10A88\n"
			"BLNE    sub_FFC0F680\n"	// DebugAssert
			"LDR     R6, =0x33340\n"
			"LDR     R7, =0x33284\n"
			"LDR     R3, [R6]\n"
			"LDRSH   R2, [R6,#0xC]\n"
			"LDRSH   R1, [R6,#0xE]\n"
			"LDR     R0, [R7,#0x80]\n"
		//	"BL      nullsub_57\n"
			"BL      sub_FFC455B0\n"
			"LDR     R3, =0x5800\n"
			"STRH    R0, [R4,#0xA4]\n"
			"SUB     R2, R3, #4\n"
			"STRD    R2, [SP]\n"
			"MOV     R1, R0\n"
			"LDRH    R0, [R7,#0x54]\n"
			"LDRSH   R2, [R6,#0xC]\n"
			"SUB     R3, R3, #8\n"
			"BL      sub_FFD11EEC\n"
			"BL      wait_until_remote_button_is_released\n"     // +
			"BL      capt_seq_hook_set_nr\n"                     // +
			"B       sub_FFD10E48\n"                             // continue function in firmware
	);
}

/*************************************************************/

// ROM:FFC91388 task_ExpDrvTask
void __attribute__((naked,noinline)) exp_drv_task(){
	asm volatile(
			"STMFD   SP!, {R4-R8,LR}\n"
			"SUB     SP, SP, #0x20\n"
			"LDR     R8, =0xBB8\n"
			"LDR     R7, =0x38B4\n"
			"LDR     R5, =0x3C674\n"
			"MOV     R0, #0\n"
			"ADD     R6, SP, #0x10\n"
			"STR     R0, [SP,#0xC]\n"
"loc_FFC913A8:\n"
			"LDR     R0, [R7,#0x20]\n"
			"MOV     R2, #0\n"
			"ADD     R1, SP, #0x1C\n"
			"BL      sub_FFC28AA4\n"
			"LDR     R0, [SP,#0xC]\n"
			"CMP     R0, #1\n"
			"BNE     loc_FFC913F4\n"
			"LDR     R0, [SP,#0x1C]\n"
			"LDR     R0, [R0]\n"
			"CMP     R0, #0x13\n"
			"CMPNE   R0, #0x14\n"
			"CMPNE   R0, #0x15\n"
			"CMPNE   R0, #0x16\n"
			"BEQ     loc_FFC91558\n"
			"CMP     R0, #0x28\n"
			"BEQ     loc_FFC914E0\n"
			"ADD     R1, SP, #0xC\n"
			"MOV     R0, #0\n"
			"BL      sub_FFC91338\n"
"loc_FFC913F4:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"LDR     R1, [R0]\n"
			"CMP     R1, #0x2E\n"
			"BNE     loc_FFC91424\n"
			"LDR     R0, [SP,#0x1C]\n"
			"BL      sub_FFC92690\n"
			"LDR     R0, [R7,#0x1C]\n"
			"MOV     R1, #1\n"
			"BL      sub_FFC28814\n"
			"BL      sub_FFC0F438\n"	// ExitTask
			"ADD     SP, SP, #0x20\n"
			"LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC91424:\n"
			"CMP     R1, #0x2D\n"
			"BNE     loc_FFC91440\n"
			"LDR     R2, [R0,#0x8C]!\n"
			"LDR     R1, [R0,#4]\n"
			"MOV     R0, R1\n"
			"BLX     R2\n"
			"B       loc_FFC91980\n"
"loc_FFC91440:\n"
			"CMP     R1, #0x26\n"
			"BNE     loc_FFC91490\n"
			"LDR     R0, [R7,#0x1C]\n"
			"MOV     R1, #0x80\n"
			"BL      sub_FFC28848\n"
			"LDR     R0, =0xFFC8DB04\n"
			"MOV     R1, #0x80\n"
			"BL      sub_FFD084B4\n"
			"LDR     R0, [R7,#0x1C]\n"
			"MOV     R2, R8\n"
			"MOV     R1, #0x80\n"
			"BL      sub_FFC28754\n"
			"TST     R0, #1\n"
			"LDRNE   R1, =0xE5F\n"
			"BNE     loc_FFC9154C\n"
"loc_FFC9147C:\n"
			"LDR     R1, [SP,#0x1C]\n"
			"LDR     R0, [R1,#0x90]\n"
			"LDR     R1, [R1,#0x8C]\n"
			"BLX     R1\n"
			"B       loc_FFC91980\n"
"loc_FFC91490:\n"
			"CMP     R1, #0x27\n"
			"BNE     loc_FFC914D8\n"
			"ADD     R1, SP, #0xC\n"
			"BL      sub_FFC91338\n"
			"LDR     R0, [R7,#0x1C]\n"
			"MOV     R1, #0x100\n"
			"BL      sub_FFC28848\n"
			"LDR     R0, =0xFFC8DB14\n"
			"MOV     R1, #0x100\n"
			"BL      sub_FFD0873C\n"
			"LDR     R0, [R7,#0x1C]\n"
			"MOV     R2, R8\n"
			"MOV     R1, #0x100\n"
			"BL      sub_FFC28754\n"
			"TST     R0, #1\n"
			"BEQ     loc_FFC9147C\n"
			"LDR     R1, =0xE69\n"
			"B       loc_FFC9154C\n"
"loc_FFC914D8:\n"
			"CMP     R1, #0x28\n"
			"BNE     loc_FFC914F0\n"
"loc_FFC914E0:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"ADD     R1, SP, #0xC\n"
			"BL      sub_FFC91338\n"
			"B       loc_FFC9147C\n"
"loc_FFC914F0:\n"
			"CMP     R1, #0x2B\n"
			"BNE     loc_FFC91508\n"
			"BL      sub_FFC80FC0\n"
			"BL      sub_FFC81BE8\n"
			"BL      sub_FFC81738\n"
			"B       loc_FFC9147C\n"
"loc_FFC91508:\n"
			"CMP     R1, #0x2C\n"
			"BNE     loc_FFC91558\n"
			"LDR     R0, [R7,#0x1C]\n"
			"MOV     R1, #4\n"
			"BL      sub_FFC28848\n"
			"LDR     R1, =0xFFC8DB34\n"
			"LDR     R0, =0xFFFFF400\n"
			"MOV     R2, #4\n"
			"BL      sub_FFC80A3C\n"
			"BL      sub_FFC80CC4\n"
			"LDR     R0, [R7,#0x1C]\n"
			"MOV     R2, R8\n"
			"MOV     R1, #4\n"
			"BL      sub_FFC28670\n"
			"TST     R0, #1\n"
			"BEQ     loc_FFC9147C\n"
			"LDR     R1, =0xE91\n"
"loc_FFC9154C:\n"
			"LDR     R0, =0xFFC8E174\n"
			"BL      sub_FFC0F680\n"
			"B       loc_FFC9147C\n"
"loc_FFC91558:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"MOV     R4, #1\n"
			"LDR     R1, [R0]\n"
			"CMP     R1, #0x11\n"
			"CMPNE   R1, #0x12\n"
			"BNE     loc_FFC915C8\n"
			"LDR     R1, [R0,#0x7C]\n"
			"ADD     R1, R1, R1,LSL#1\n"
			"ADD     R1, R0, R1,LSL#2\n"
			"SUB     R1, R1, #8\n"
			"LDMIA   R1, {R2-R4}\n"
			"STMIA   R6, {R2-R4}\n"
			"BL      sub_FFC8FCC4\n"
			"LDR     R0, [SP,#0x1C]\n"
			"LDR     R1, [R0,#0x7C]\n"
			"LDR     R3, [R0,#0x8C]\n"
			"LDR     R2, [R0,#0x90]\n"
			"ADD     R0, R0, #4\n"
			"BLX     R3\n"
			"LDR     R0, [SP,#0x1C]\n"
			"BL      sub_FFC92A58\n"
			"LDR     R0, [SP,#0x1C]\n"
			"LDR     R1, [R0,#0x7C]\n"
			"LDR     R3, [R0,#0x94]\n"
			"LDR     R2, [R0,#0x98]\n"
			"ADD     R0, R0, #4\n"
			"BLX     R3\n"
			"B       loc_FFC918C0\n"
"loc_FFC915C8:\n"
			"CMP     R1, #0x13\n"
			"CMPNE   R1, #0x14\n"
			"CMPNE   R1, #0x15\n"
			"CMPNE   R1, #0x16\n"
			"BNE     loc_FFC91680\n"
			"ADD     R3, SP, #0xC\n"
			"MOV     R2, SP\n"
			"ADD     R1, SP, #0x10\n"
			"BL      sub_FFC8FFA0\n"
			"CMP     R0, #1\n"
			"MOV     R4, R0\n"
			"CMPNE   R4, #5\n"
			"BNE     loc_FFC9161C\n"
			"LDR     R0, [SP,#0x1C]\n"
			"MOV     R2, R4\n"
			"LDR     R1, [R0,#0x7C]!\n"
			"LDR     R12, [R0,#0x10]!\n"
			"LDR     R3, [R0,#4]\n"
			"MOV     R0, SP\n"
			"BLX     R12\n"
			"B       loc_FFC91654\n"
"loc_FFC9161C:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"CMP     R4, #2\n"
			"LDR     R3, [R0,#0x90]\n"
			"CMPNE   R4, #6\n"
			"BNE     loc_FFC91668\n"
			"LDR     R12, [R0,#0x8C]\n"
			"MOV     R0, SP\n"
			"MOV     R2, R4\n"
			"MOV     R1, #1\n"
			"BLX     R12\n"
			"LDR     R0, [SP,#0x1C]\n"
			"MOV     R2, SP\n"
			"ADD     R1, SP, #0x10\n"
			"BL      sub_FFC91040\n"
"loc_FFC91654:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"LDR     R2, [SP,#0xC]\n"
			"MOV     R1, R4\n"
			"BL      sub_FFC912D8\n"
			"B       loc_FFC918C0\n"
"loc_FFC91668:\n"
			"LDR     R1, [R0,#0x7C]\n"
			"LDR     R12, [R0,#0x8C]\n"
			"ADD     R0, R0, #4\n"
			"MOV     R2, R4\n"
			"BLX     R12\n"
			"B       loc_FFC918C0\n"
"loc_FFC91680:\n"
			"CMP     R1, #0x22\n"
			"CMPNE   R1, #0x23\n"
			"BNE     loc_FFC916CC\n"
			"LDR     R1, [R0,#0x7C]\n"
			"ADD     R1, R1, R1,LSL#1\n"
			"ADD     R1, R0, R1,LSL#2\n"
			"SUB     R1, R1, #8\n"
			"LDMIA   R1, {R2-R4}\n"
			"STMIA   R6, {R2-R4}\n"
			"BL      sub_FFC8F214\n"
			"LDR     R0, [SP,#0x1C]\n"
			"LDR     R1, [R0,#0x7C]\n"
			"LDR     R3, [R0,#0x8C]\n"
			"LDR     R2, [R0,#0x90]\n"
			"ADD     R0, R0, #4\n"
			"BLX     R3\n"
			"LDR     R0, [SP,#0x1C]\n"
			"BL      sub_FFC8F508\n"
			"B       loc_FFC918C0\n"
"loc_FFC916CC:\n"
			"ADD     R1, R0, #4\n"
			"LDMIA   R1, {R2,R3,R12}\n"
			"STMIA   R6, {R2,R3,R12}\n"
			"LDR     R1, [R0]\n"
			"CMP     R1, #0x25\n"
			"ADDLS   PC, PC, R1,LSL#2\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC91780\n"
			"B       loc_FFC91780\n"
			"B       loc_FFC91788\n"
			"B       loc_FFC91790\n"
			"B       loc_FFC91790\n"
			"B       loc_FFC91790\n"
			"B       loc_FFC91780\n"
			"B       loc_FFC91788\n"
			"B       loc_FFC91790\n"
			"B       loc_FFC91790\n"
			"B       loc_FFC917A8\n"
			"B       loc_FFC917A8\n"
			"B       loc_FFC91894\n"
			"B       loc_FFC9189C\n"
			"B       loc_FFC9189C\n"
			"B       loc_FFC9189C\n"
			"B       loc_FFC9189C\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC91798\n"
			"B       loc_FFC917A0\n"
			"B       loc_FFC917A0\n"
			"B       loc_FFC917B4\n"
			"B       loc_FFC917B4\n"
			"B       loc_FFC917BC\n"
			"B       loc_FFC917EC\n"
			"B       loc_FFC9181C\n"
			"B       loc_FFC9184C\n"
			"B       loc_FFC9187C\n"
			"B       loc_FFC9187C\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC918A0\n"
			"B       loc_FFC91884\n"
			"B       loc_FFC9188C\n"
"loc_FFC91780:\n"
			"BL      sub_FFC8E01C\n"
			"B       loc_FFC918A0\n"
"loc_FFC91788:\n"
			"BL      sub_FFC8E2A0\n"
			"B       loc_FFC918A0\n"
"loc_FFC91790:\n"
			"BL      sub_FFC8E4A8\n"
			"B       loc_FFC918A0\n"
"loc_FFC91798:\n"
			"BL      sub_FFC8E720\n"
			"B       loc_FFC918A0\n"
"loc_FFC917A0:\n"
			"BL      sub_FFC8E918\n"
			"B       loc_FFC918A0\n"
"loc_FFC917A8:\n"
			"BL      sub_FFC8EBD4_my\n"		//---------->
			"MOV     R4, #0\n"
			"B       loc_FFC918A0\n"
"loc_FFC917B4:\n"
			"BL      sub_FFC8ED14\n"
			"B       loc_FFC918A0\n"
"loc_FFC917BC:\n"
			"LDRH    R1, [R0,#4]\n"
			"STRH    R1, [SP,#0x10]\n"
			"LDRH    R1, [R5,#2]\n"
			"STRH    R1, [SP,#0x12]\n"
			"LDRH    R1, [R5,#4]\n"
			"STRH    R1, [SP,#0x14]\n"
			"LDRH    R1, [R5,#6]\n"
			"STRH    R1, [SP,#0x16]\n"
			"LDRH    R1, [R0,#0xC]\n"
			"STRH    R1, [SP,#0x18]\n"
			"BL      sub_FFC92704\n"
			"B       loc_FFC918A0\n"
"loc_FFC917EC:\n"
			"LDRH    R1, [R0,#4]\n"
			"STRH    R1, [SP,#0x10]\n"
			"LDRH    R1, [R5,#2]\n"
			"STRH    R1, [SP,#0x12]\n"
			"LDRH    R1, [R5,#4]\n"
			"STRH    R1, [SP,#0x14]\n"
			"LDRH    R1, [R5,#6]\n"
			"STRH    R1, [SP,#0x16]\n"
			"LDRH    R1, [R5,#8]\n"
			"STRH    R1, [SP,#0x18]\n"
			"BL      sub_FFC92870\n"
			"B       loc_FFC918A0\n"
"loc_FFC9181C:\n"
			"LDRH    R1, [R5]\n"
			"STRH    R1, [SP,#0x10]\n"
			"LDRH    R1, [R0,#6]\n"
			"STRH    R1, [SP,#0x12]\n"
			"LDRH    R1, [R5,#4]\n"
			"STRH    R1, [SP,#0x14]\n"
			"LDRH    R1, [R5,#6]\n"
			"STRH    R1, [SP,#0x16]\n"
			"LDRH    R1, [R5,#8]\n"
			"STRH    R1, [SP,#0x18]\n"
			"BL      sub_FFC9291C\n"
			"B       loc_FFC918A0\n"
"loc_FFC9184C:\n"
			"LDRH    R1, [R5]\n"
			"STRH    R1, [SP,#0x10]\n"
			"LDRH    R1, [R5,#2]\n"
			"STRH    R1, [SP,#0x12]\n"
			"LDRH    R1, [R5,#4]\n"
			"STRH    R1, [SP,#0x14]\n"
			"LDRH    R1, [R5,#6]\n"
			"STRH    R1, [SP,#0x16]\n"
			"LDRH    R1, [R0,#0xC]\n"
			"STRH    R1, [SP,#0x18]\n"
			"BL      sub_FFC929BC\n"
			"B       loc_FFC918A0\n"
"loc_FFC9187C:\n"
			"BL      sub_FFC8F06C\n"
			"B       loc_FFC918A0\n"
"loc_FFC91884:\n"
			"BL      sub_FFC8F60C\n"
			"B       loc_FFC918A0\n"
"loc_FFC9188C:\n"
			"BL      sub_FFC8F848\n"
			"B       loc_FFC918A0\n"
"loc_FFC91894:\n"
			"BL      sub_FFC8F9C4\n"
			"B       loc_FFC918A0\n"
"loc_FFC9189C:\n"
			"BL      sub_FFC8FB60\n"
"loc_FFC918A0:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"LDR     R1, [R0,#0x7C]\n"
			"LDR     R3, [R0,#0x8C]\n"
			"LDR     R2, [R0,#0x90]\n"
			"ADD     R0, R0, #4\n"
			"BLX     R3\n"
			"CMP     R4, #1\n"
			"BNE     loc_FFC91908\n"
"loc_FFC918C0:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"MOV     R2, #0xC\n"
			"LDR     R1, [R0,#0x7C]\n"
			"ADD     R1, R1, R1,LSL#1\n"
			"ADD     R0, R0, R1,LSL#2\n"
			"SUB     R4, R0, #8\n"
			"LDR     R0, =0x3C674\n"
			"ADD     R1, SP, #0x10\n"
			"BL      sub_FFE7E060\n"
			"LDR     R0, =0x3C680\n"
			"MOV     R2, #0xC\n"
			"ADD     R1, SP, #0x10\n"
			"BL      sub_FFE7E060\n"
			"LDR     R0, =0x3C68C\n"
			"MOV     R2, #0xC\n"
			"MOV     R1, R4\n"
			"BL      sub_FFE7E060\n"
			"B       loc_FFC91980\n"
"loc_FFC91908:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"LDR     R0, [R0]\n"
			"CMP     R0, #0xB\n"
			"BNE     loc_FFC91950\n"
			"MOV     R3, #0\n"
			"STR     R3, [SP]\n"
			"MOV     R3, #1\n"
			"MOV     R2, #1\n"
			"MOV     R1, #1\n"
			"MOV     R0, #0\n"
			"BL      sub_FFC8DE24\n"
			"MOV     R3, #0\n"
			"STR     R3, [SP]\n"
			"MOV     R3, #1\n"
			"MOV     R2, #1\n"
			"MOV     R1, #1\n"
			"MOV     R0, #0\n"
			"B       loc_FFC9197C\n"
"loc_FFC91950:\n"
			"MOV     R3, #1\n"
			"MOV     R2, #1\n"
			"MOV     R1, #1\n"
			"MOV     R0, #1\n"
			"STR     R3, [SP]\n"
			"BL      sub_FFC8DE24\n"
			"MOV     R3, #1\n"
			"MOV     R2, #1\n"
			"MOV     R1, #1\n"
			"MOV     R0, #1\n"
			"STR     R3, [SP]\n"
"loc_FFC9197C:\n"
			"BL      sub_FFC8DF64\n"
"loc_FFC91980:\n"
			"LDR     R0, [SP,#0x1C]\n"
			"BL      sub_FFC92690\n"
			"B       loc_FFC913A8\n"
	);
}

void __attribute__((naked,noinline)) sub_FFC8EBD4_my(){ //
	asm volatile(
		 "STMFD   SP!, {R4-R8,LR}\n"
		"LDR     R7, =0x38B4\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x3E\n"
		"BL      sub_FFC28848\n"
		"LDRSH   R0, [R4,#4]\n"
		"MOV     R2, #0\n"
		"MOV     R1, #0\n"
		"BL      sub_FFC8DB88\n"
		"MOV     R6, R0\n"
		"LDRSH   R0, [R4,#6]\n"
		"BL      sub_FFC8DC98\n"
		"LDRSH   R0, [R4,#8]\n"
		"BL      sub_FFC8DCF0\n"
		"LDRSH   R0, [R4,#0xA]\n"
		"BL      sub_FFC8DD48\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"MOV     R1, #0\n"
		"BL      sub_FFC8DDA0\n"
		"MOV     R5, R0\n"
		"LDR     R0, [R4]\n"
		"LDR     R8, =0x3C68C\n"
		"CMP     R0, #0xB\n"
		"MOVEQ   R6, #0\n"
		"MOVEQ   R5, #0\n"
		"BEQ     loc_FFC8EC68\n"
		"CMP     R6, #1\n"
		"BNE     loc_FFC8EC68\n"
		"LDRSH   R0, [R4,#4]\n"
		"LDR     R1, =0xFFC8DAF4\n"
		"MOV     R2, #2\n"
		"BL      sub_FFD08608\n"
		"STRH    R0, [R4,#4]\n"
		"MOV     R0, #0\n"
		"STR     R0, [R7,#0x28]\n"
		"B       loc_FFC8EC70\n"
"loc_FFC8EC68:\n"
		"LDRH    R0, [R8]\n"
		"STRH    R0, [R4,#4]\n"
"loc_FFC8EC70:\n"
		"CMP     R5, #1\n"
		"LDRNEH  R0, [R8,#8]\n"
		"BNE     loc_FFC8EC8C\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"LDR     R1, =0xFFC8DB78\n"
		"MOV     R2, #0x20\n"
		"BL      sub_FFC926C0\n"
"loc_FFC8EC8C:\n"
		"STRH    R0, [R4,#0xC]\n"
		"LDRSH   R0, [R4,#6]\n"
		"BL      sub_FFC80D30_my\n"		//----------->
		"LDRSH   R0, [R4,#8]\n"
		"MOV     R1, #1\n"
		"BL      sub_FFC81480\n"
		"MOV     R1, #0\n"
		"ADD     R0, R4, #8\n"
		"BL      sub_FFC81508\n"
		"LDRSH   R0, [R4,#0xE]\n"
		"BL      sub_FFC88EAC\n"
		"LDR     R4, =0xBB8\n"
		"CMP     R6, #1\n"
		"BNE     loc_FFC8ECE4\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #2\n"
		"BL      sub_FFC28754\n"
		"TST     R0, #1\n"
		"LDRNE   R1, =0x5A3\n"
		"LDRNE   R0, =0xFFC8E174\n"
		"BLNE    sub_FFC0F680\n"
"loc_FFC8ECE4:\n"
		"CMP     R5, #1\n"
		"LDMNEFD SP!, {R4-R8,PC}\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #0x20\n"
		"BL      sub_FFC28754\n"
		"TST     R0, #1\n"
		"LDRNE   R1, =0x5A8\n"
		"LDRNE   R0, =0xFFC8E174\n"
		"LDMNEFD SP!, {R4-R8,LR}\n"
		"BNE     sub_FFC0F680\n"
		"LDMFD   SP!, {R4-R8,PC}\n"
	);
}

void __attribute__((naked,noinline)) sub_FFC80D30_my(){ //
	asm volatile(
			"STMFD   SP!, {R4-R6,LR}\n"
			"LDR     R5, =0x35A8\n"
			"MOV     R4, R0\n"
			"LDR     R0, [R5,#4]\n"
			"CMP     R0, #1\n"
			"LDRNE   R1, =0x146\n"
			"LDRNE   R0, =0xFFC80B34\n"
			"BLNE    sub_FFC0F680\n"
			"CMN     R4, #0xC00\n"
			"LDREQSH R4, [R5,#2]\n"
			"CMN     R4, #0xC00\n"
			"MOVEQ   R1, #0x14C\n"
			"LDREQ   R0, =0xFFC80B34\n"
			"STRH    R4, [R5,#2]\n"
			"BLEQ    sub_FFC0F680\n"
			"MOV     R0, R4\n"
		//  "BL      _sub_FFD7C39C\n"		// -
			"BL      apex2us\n"				// +
			"MOV     R4, R0\n"
		//	"BL      nullsub_39\n"
			"MOV     R0, R4\n"
			"BL      sub_FFCB7E98\n"
			"TST     R0, #1\n"
			"LDRNE   R1, =0x151\n"
			"LDMNEFD SP!, {R4-R6,LR}\n"
			"LDRNE   R0, =0xFFC80B34\n"
			"BNE     sub_FFC0F680\n"
			"LDMFD   SP!, {R4-R6,PC}\n"
	);
}
