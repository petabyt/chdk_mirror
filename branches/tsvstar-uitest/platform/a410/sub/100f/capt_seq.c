#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x68D0; //@ffd2a474

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FFD2A438_my(long p)
{
  asm volatile (
"                 STMFD   SP!, {R4,R5,LR}\n"
"                 LDR     R3, =0x745E4\n"
"                 LDR     R5, =0x68CC\n"
"                 SUB     SP, SP, #4\n"
"                 LDR     R1, =0xFFFFFFFF\n"
"                 STR     R0, [R5]\n"
"                 LDR     R0, [R3]\n"
"                 BL      sub_FFC10974\n"
"                 BL      sub_FFD2FF70\n"
"                 BL      wait_until_remote_button_is_released\n" //+
"                 LDR     R0, [R0,#0x7C]\n"
"                 BL      sub_FFD2A3AC\n"
"                 BL      capt_seq_hook_set_nr\n" //+
"                 LDR     R3, =0x68D4\n"
"                 LDR     R0, [R3]\n"
"                 BL      sub_FFC8A7E8\n"
"                 B       sub_FFD2A474\n"
  );
} //

void __attribute__((naked,noinline)) sub_FFD2748C_my(long p)
{
  asm volatile (
"                 STMFD   SP!, {R4,R5,LR}\n"
"                 LDR     R5, [R0,#0xC]\n"
"                 BL      sub_FFD2FD14\n"
"                 CMP     R0, #0\n"
"                 BNE     loc_FFD274A4\n"
"                 BL      sub_FFD2FD20\n"
" loc_FFD274A4:\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FFD2927C\n"
"                 TST     R0, #1\n"
"                 MOV     R2, R5\n"
"                 MOV     R1, #1\n"
"                 BEQ     loc_FFD274C4\n"
"                 LDMFD   SP!, {R4,R5,LR}\n"
"                 B       sub_FFD25A64\n"
" loc_FFD274C4:\n"
"                 BL      sub_FFD24EA0\n"
"                 MOV     R4, R0\n"
"                 BL      sub_FFC157D4\n"
"                 ADD     R3, R5, R5,LSL#1\n"
"                 ADD     R4, R4, R3,LSL#5\n"
"                 STR     R0, [R4,#4]\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FFD2AC4C\n"
"                 BL      sub_FFD297F0\n"
"                 BL      sub_FFD29790\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FFD2A438_my\n"
"                 BL      capt_seq_hook_raw_here\n" //+
"                 MOV     R2, R5\n"
"                 MOV     R1, #1\n"
"                 BL      sub_FFD25A64\n"
"                 LDMFD   SP!, {R4,R5,LR}\n"
"                 B       sub_FFD2A634\n"
  );
} 

void __attribute__((naked,noinline)) capt_seq_task()    //IDA task_CaptSeqTask
{
  asm volatile (//copy from orig fw @ffd276bc
"                 STMFD   SP!, {R4,LR}\n"
"                 SUB     SP, SP, #4\n"
"                 MOV     R4, SP\n"
"                 B       loc_FFD27814\n"
" loc_FFD276CC:\n"
"                 LDR     R2, [SP]\n"
"                 LDR     R3, [R2]\n"
"                 MOV     R0, R2\n"
"                 CMP     R3, #0x14\n"
"                 LDRLS   PC, [PC,R3,LSL#2]\n"
"                 B       loc_FFD277E8\n"
"                 .long loc_FFD27738\n"
"                 .long loc_FFD27744\n"
"                 .long loc_FFD2774C\n"
"                 .long loc_FFD2775C\n"
"                 .long loc_FFD27754\n"
"                 .long loc_FFD27764\n"
"                 .long loc_FFD2776C\n"
"                 .long loc_FFD27778\n"
"                 .long loc_FFD27780\n"
"                 .long loc_FFD2778C\n"
"                 .long loc_FFD27794\n"
"                 .long loc_FFD2779C\n"
"                 .long loc_FFD277A4\n"
"                 .long loc_FFD277AC\n"
"                 .long loc_FFD277B4\n"
"                 .long loc_FFD277C0\n"
"                 .long loc_FFD277C8\n"
"                 .long loc_FFD277D0\n"
"                 .long loc_FFD277D8\n"
"                 .long loc_FFD277E0\n"
"                 .long loc_FFD277FC\n"
" loc_FFD27738:\n"
"                 BL      sub_FFD28ED8\n"
"                 BL      shooting_expo_param_override\n" //+
"                 BL      sub_FFD255CC\n"
"                 B       loc_FFD277F8\n"
" loc_FFD27744:\n"
"                 BL      sub_FFD2748C_my\n" //hope this is the right one...
"                 B       loc_FFD277F8\n"
" loc_FFD2774C:\n"
"                 BL      sub_FFD2926C\n"
"                 B       loc_FFD277F8\n"
" loc_FFD27754:\n"
"                 BL      sub_FFD28138\n"
"                 B       loc_FFD277F8\n"
" loc_FFD2775C:\n"
"                 BL      sub_FFD281E8\n"
"                 B       loc_FFD277F8\n"
" loc_FFD27764:\n"
"                 BL      sub_FFD283DC\n"
"                 B       loc_FFD277F8\n"
" loc_FFD2776C:\n"
"                 BL      sub_FFD28FCC\n"
"                 BL      sub_FFD255CC\n"
"                 B       loc_FFD277F8\n"
" loc_FFD27778:\n"
"                 BL      sub_FFD2753C\n"
"                 B       loc_FFD277F8\n"
" loc_FFD27780:\n"
"                 BL      sub_FFD29034\n"
"                 BL      sub_FFD255CC\n"
"                 B       loc_FFD277F8\n"
" loc_FFD2778C:\n"
"                 BL      sub_FFD281E8\n"
"                 B       loc_FFD277F8\n"
" loc_FFD27794:\n"
"                 BL      sub_FFD2992C\n"
"                 B       loc_FFD277F8\n"
" loc_FFD2779C:\n"
"                 BL      sub_FFD29BB4\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277A4:\n"
"                 BL      sub_FFD29C1C\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277AC:\n"
"                 BL      sub_FFD29CD4\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277B4:\n"
"                 MOV     R0, #0\n"
"                 BL      sub_FFD29D6C\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277C0:\n"
"                 BL      sub_FFD29EBC\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277C8:\n"
"                 BL      sub_FFD29F30\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277D0:\n"
"                 BL      sub_FFD29FE8\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277D8:\n"
"                 BL      sub_FFD2A0B8\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277E0:\n"
"                 BL      sub_FFD2A0E4\n"
"                 B       loc_FFD277F8\n"
" loc_FFD277E8:\n"
"                 MOV     R1, #0x2DC\n"
"                 LDR     R0, =0xFFD27238\n"
"                 ADD     R1, R1, #2\n"
"                 BL      sub_FFC03B58\n"
" loc_FFD277F8:\n"
"                 LDR     R2, [SP]\n"
" loc_FFD277FC:\n"
"                 LDR     R3, =0x7456C\n"
"                 LDR     R1, [R2,#4]\n"
"                 LDR     R0, [R3]\n"
"                 BL      sub_FFC107D8\n"
"                 LDR     R0, [SP]\n"
"                 BL      sub_FFD272B4\n"
" loc_FFD27814:\n"
"                 LDR     R3, =0x74570\n"
"                 MOV     R1, R4\n"
"                 LDR     R0, [R3]\n"
"                 MOV     R2, #0\n"
"                 BL      sub_FFC10F94\n"
"                 TST     R0, #1\n"
"                 BEQ     loc_FFD276CC\n"
"                 MOV     R1, #0x24C\n"
"                 LDR     R0, =0xFFD27238\n"
"                 ADD     R1, R1, #3\n"
"                 BL      sub_FFC03B58\n"
"                 BL      sub_FFC12724\n"
"                 ADD     SP, SP, #4\n"
"                 LDMFD   SP!, {R4,PC}\n"


  );
}

void __attribute__((naked,noinline)) exp_drv_task(){
 asm volatile(// @ffcdb028
"                 STMFD   SP!, {R4-R8,LR}\n"
"                 SUB     SP, SP, #0x14\n"
"                 MOV     R7, SP\n"
"                 B       loc_FFCDB31C\n"
" loc_FFCDB038:\n"
"                 CMP     R2, #0x19\n"
"                 BNE     loc_FFCDB050\n"
"                 LDR     R0, [R12,#0x34]\n"
"                 MOV     LR, PC\n"
"                 LDR     PC, [R12,#0x30]\n"
"                 B       loc_FFCDB088\n"
" loc_FFCDB050:\n"
"                 SUB     R3, R2, #0x16\n"
"                 CMP     R3, #1\n"
"                 BHI     loc_FFCDB068\n"
"                 MOV     R0, R12\n"
"                 BL      sub_FFCDAFD0\n"
"                 B       loc_FFCDB078\n"
" loc_FFCDB068:\n"
"                 CMP     R2, #0x18\n"
"                 BNE     loc_FFCDB094\n"
"                 BL      sub_FFC93338\n"
"                 BL      sub_FFC951B0\n"
" loc_FFCDB078:\n"
"                 LDR     R3, [SP]\n"
"                 LDR     R0, [R3,#0x34]\n"
"                 MOV     LR, PC\n"
"                 LDR     PC, [R3,#0x30]\n"
" loc_FFCDB088:\n"
"                 LDR     R0, [SP]\n"
"                 BL      sub_FFCD9444\n"
"                 B       loc_FFCDB31C\n"
" loc_FFCDB094:\n"
"                 CMP     R2, #0xC\n"
"                 MOV     R8, #1\n"
"                 BNE     loc_FFCDB104\n"
"                 LDR     R1, [R12,#0x24]\n"
"                 ADD     R1, R1, R1,LSL#1\n"
"                 ADD     R1, R12, R1,LSL#1\n"
"                 ADD     R6, SP, #0x0C\n"
"                 SUB     R1, R1, #2\n"
"                 MOV     R2, #6\n"
"                 MOV     R0, R6\n"
"                 BL      sub_FFE6C6B4\n" // memcpy
"                 LDR     R0, [SP]\n"
"                 BL      sub_FFCDA670\n"
"                 LDR     R3, [SP]\n"
"                 LDR     R1, [R3,#0x24]\n"
"                 LDR     R2, [R3,#0x34]\n"
"                 ADD     R0, R3, #4\n"
"                 MOV     LR, PC\n"
"                 LDR     PC, [R3,#0x30]\n"
"                 LDR     R0, [SP]\n"
"                 BL      sub_FFCDA7F4\n"
"                 LDR     R3, [SP]\n"
"                 ADD     R0, R3, #4\n"
"                 LDR     R1, [R3,#0x24]\n"
"                 LDR     R2, [R3,#0x3C]\n"
"                 MOV     LR, PC\n"
"                 LDR     PC, [R3,#0x38]\n"
"                 B       loc_FFCDB2CC\n"
" loc_FFCDB104:\n"
"                 SUB     R3, R2, #0xD\n"
"                 CMP     R3, #1\n"
"                 BHI     loc_FFCDB184\n"
"                 ADD     R6, SP, #0x0C\n"
"                 ADD     R5, SP, #0x04\n"
"                 MOV     R0, R12\n"
"                 MOV     R1, R6\n"
"                 MOV     R2, R5\n"
"                 BL      sub_FFCDA870\n"
"                 MOV     R4, R0\n"
"                 CMP     R4, #3\n"
"                 CMPNE   R4, #1\n"
"                 BNE     loc_FFCDB164\n"
"                 LDR     R12, [SP]\n"
"                 MOV     R0, R5\n"
"                 LDR     R1, [R12,#0x24]\n"
"                 MOV     R2, R4\n"
"                 LDR     R3, [R12,#0x34]\n"
"                 MOV     LR, PC\n"
"                 LDR     PC, [R12,#0x30]\n"
"                 MOV     R1, R4\n"
"                 LDR     R0, [SP]\n"
"                 BL      sub_FFCDAFB0\n"
"                 B       loc_FFCDB2CC\n"
" loc_FFCDB164:\n"
"                 LDR     R12, [SP]\n"
"                 MOV     R2, R4\n"
"                 ADD     R0, R12, #4\n"
"                 LDR     R1, [R12,#0x24]\n"
"                 LDR     R3, [R12,#0x34]\n"
"                 MOV     LR, PC\n"
"                 LDR     PC, [R12,#0x30]\n"
"                 B       loc_FFCDB2CC\n"
" loc_FFCDB184:\n"
"                 CMP     R2, #0x14\n"
"                 BNE     loc_FFCDB1D8\n"
"                 LDR     R1, [R12,#0x24]\n"
"                 ADD     R1, R1, R1,LSL#1\n"
"                 ADD     R1, R12, R1,LSL#1\n"
"                 ADD     R6, SP, #0x0C\n"
"                 SUB     R1, R1, #2\n"
"                 MOV     R2, #6\n"
"                 MOV     R0, R6\n"
"                 BL      sub_FFE6C6B4\n" // memcpy
"                 LDR     R0, [SP]\n"
"                 BL      sub_FFCDA1D0\n"
"                 LDR     R3, [SP]\n"
"                 ADD     R0, R3, #4\n"
"                 LDR     R1, [R3,#0x24]\n"
"                 LDR     R2, [R3,#0x34]\n"
"                 MOV     LR, PC\n"
"                 LDR     PC, [R3,#0x30]\n"
"                 LDR     R0, [SP]\n"
"                 BL      sub_FFCDA3A0\n"
"                 B       loc_FFCDB2CC\n"
" loc_FFCDB1D8:\n"
"                 ADD     R6, SP, #0x0C\n"
"                 ADD     R1, R12, #4\n"
"                 MOV     R0, R6\n"
"                 MOV     R2, #6\n"
"                 BL      sub_FFE6C6B4\n" // memcpy
"                 LDR     R12, [SP]\n"
"                 LDR     R3, [R12]\n"
"                 MOV     R0, R12\n"
"                 CMP     R3, #0x15\n"
"                 LDRLS   PC, [PC,R3,LSL#2]\n"
"                 B       loc_FFCDB2B8\n"
"                 .long loc_FFCDB25C\n"
"                 .long loc_FFCDB264\n"
"                 .long loc_FFCDB26C\n"
"                 .long loc_FFCDB26C\n"
"                 .long loc_FFCDB25C\n"
"                 .long loc_FFCDB264\n"
"                 .long loc_FFCDB26C\n"
"                 .long loc_FFCDB26C\n"
"                 .long loc_FFCDB284\n"
"                 .long loc_FFCDB284\n"
"                 .long loc_FFCDB2A8\n"
"                 .long loc_FFCDB2B0\n"
"                 .long loc_FFCDB2B8\n"
"                 .long loc_FFCDB2B8\n"
"                 .long loc_FFCDB2B8\n"
"                 .long loc_FFCDB274\n"
"                 .long loc_FFCDB27C\n"
"                 .long loc_FFCDB290\n"
"                 .long loc_FFCDB298\n"
"                 .long loc_FFCDB298\n"
"                 .long loc_FFCDB2B8\n"
"                 .long loc_FFCDB2A0\n"
" loc_FFCDB25C:\n"
"                 BL      sub_FFCD9920\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB264:\n"
"                 BL      sub_FFCD9A5C\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB26C:\n"
"                 BL      sub_FFCD9B8C\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB274:\n"
"                 BL      sub_FFCD9D60\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB27C:\n"
"                 BL      sub_FFCD9E68\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB284:\n"
"                 BL      sub_FFCD9F2C_my\n" //
"                 MOV     R8, #0\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB290:\n"
"                 BL      sub_FFCD9FF0\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB298:\n"
"                 BL      sub_FFCDA0D8\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB2A0:\n"
"                 BL      sub_FFCDA430\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB2A8:\n"
"                 BL      sub_FFCDA504\n"
"                 B       loc_FFCDB2B4\n"
" loc_FFCDB2B0:\n"
"                 BL      sub_FFCDA5F0\n"
" loc_FFCDB2B4:\n"
"                 LDR     R12, [SP]\n"
" loc_FFCDB2B8:\n"
"                 ADD     R0, R12, #4\n"
"                 LDR     R1, [R12,#0x24]\n"
"                 LDR     R2, [R12,#0x34]\n"
"                 MOV     LR, PC\n"
"                 LDR     PC, [R12,#0x30]\n"
" loc_FFCDB2CC:\n"
"                 CMP     R8, #1\n"
"                 BNE     loc_FFCDB2F4\n"
"                 LDR     R1, [SP]\n"
"                 LDR     R3, [R1,#0x24]\n"
"                 ADD     R3, R3, R3,LSL#1\n"
"                 ADD     R1, R1, R3,LSL#1\n"
"                 MOV     R0, R6\n"
"                 SUB     R1, R1, #2\n"
"                 BL      sub_FFCD97D8\n"
"                 B       loc_FFCDB314\n"
" loc_FFCDB2F4:\n"
"                 MOV     R0, #1\n"
"                 MOV     R1, R0\n"
"                 MOV     R2, R0\n"
"                 BL      sub_FFCD977C\n"
"                 MOV     R0, #1\n"
"                 MOV     R1, R0\n"
"                 MOV     R2, R0\n"
"                 BL      sub_FFCD9898\n"
" loc_FFCDB314:\n"
"                 LDR     R0, [SP]\n"
"                 BL      sub_FFCD9444\n"
" loc_FFCDB31C:\n"
"                 LDR     R3, =0x506C0\n"
"                 MOV     R2, #0\n"
"                 LDR     R0, [R3]\n"
"                 MOV     R1, R7\n"
"                 BL      sub_ffc10f94\n" // ReceiveMessageQueue
"                 LDR     R12, [SP]\n"
"                 LDR     R2, [R12]\n"
"                 CMP     R2, #0x1A\n"
"                 BNE     loc_FFCDB038\n"
"                 MOV     R0, R12\n"
"                 BL      sub_FFCD9444\n"
"                 LDR     R3, =0x506BC\n"
"                 MOV     R1, #1\n"
"                 LDR     R0, [R3]\n"
"                 BL      sub_ffc107d8\n" // SetEventFlag
"                 BL      sub_ffc12724\n" // ExitTask
"                 ADD     SP, SP, #0x14\n"
"                 LDMFD   SP!, {R4-R8,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FFCD9F2C_my(){//
 asm volatile(
"                 STMFD   SP!, {R4,R5,LR}\n"
"                 LDR     R3, =0x506BC\n"
"                 MOV     R4, R0\n"
"                 MOV     R1, #0xE\n"
"                 LDR     R0, [R3]\n"
"                 BL      sub_ffc10974\n" // ClearEventFlag
"                 MOV     R1, #0\n"
"                 LDRSH   R0, [R4,#4]\n"
"                 BL      sub_FFCD94E4\n"
"                 MOV     R5, R0\n"
"                 LDRSH   R0, [R4,#6]\n"
"                 BL      sub_FFCD9614\n"
"                 LDRSH   R0, [R4,#8]\n"
"                 BL      sub_FFCD96B0\n"
"                 LDR     R3, [R4]\n"
"                 CMP     R3, #9\n"
"                 MOVEQ   R5, #0\n"
"                 CMP     R5, #1\n"
"                 LDR     R1, =0xFFCD9474\n"
"                 MOV     R2, #2\n"
"                 BNE     loc_FFCD9F98\n"
"                 LDRSH   R0, [R4,#4]\n"
"                 BL      sub_FFE18CD8\n"
"                 LDR     R2, =0x506E8\n"
"                 MOV     R3, #0\n"
"                 STR     R3, [R2]\n"
"                 B       loc_FFCD9F9C\n"
" loc_FFCD9F98:\n"
"                 BL      sub_FFCD974C\n"
" loc_FFCD9F9C:\n"
"                 STRH    R0, [R4,#4]\n"
"                 LDRSH   R0, [R4,#6]\n"
"                 BL      sub_FFC92FD0_my\n" //
"                 BL      sub_FFC94F54\n"
"                 LDRSH   R0, [R4,#8]\n"
"                 MOV     R1, #1\n"
"                 BL      sub_FFC94D70\n"
"                 MOV     R1, #0\n"
"                 ADD     R0, R4, #8\n"
"                 BL      sub_FFC94E34\n"
"                 CMP     R5, #1\n"
"                 MOV     R1, #2\n"
"                 MOV     R2, #0\n"
"                 LDMNEFD SP!, {R4,R5,PC}\n"
"                 LDR     R3, =0x506BC\n"
"                 LDR     R0, [R3]\n"
"                 LDMFD   SP!, {R4,R5,LR}\n"
"                 LDR     PC, =0xFFC107C8\n"
 );
}

void __attribute__((naked,noinline)) sub_FFC92FD0_my() {
 asm volatile(
"                 STMFD   SP!, {R4,LR}\n"
"                 LDR     R3, =0x5074\n"
"                 LDR     R2, [R3]\n"
"                 MOV     R3, R0,LSL#16\n"
"                 CMP     R2, #1\n"
"                 MOV     R1, #0x110\n"
"                 LDR     R0, =0xFFC9296C\n"
"                 MOV     R4, R3,ASR#16\n"
"                 BEQ     loc_FFC92FF8\n"
"                 BL      sub_ffc03b58\n" // DebugAssert
" loc_FFC92FF8:\n"
"                 MOV     R1, #0x114\n"
"                 CMN     R4, #0xC00\n"
"                 LDR     R3, =0x36C06\n"
"                 LDR     R0, =0xFFC9296C\n"
"                 ADD     R1, R1, #2\n"
"                 LDREQSH R4, [R3]\n"
"                 LDRNE   R3, =0x36C06\n"
"                 CMN     R4, #0xC00\n"
"                 STRH    R4, [R3]\n"
"                 BNE     loc_FFC93024\n"
"                 BL      sub_ffc03b58\n" // DebugAssert
" loc_FFC93024:\n"
"                 MOV     R0, R4\n"
"                 BL      apex2us\n" //
"                 BL      sub_FFC92524\n"
"                 TST     R0, #1\n"
"                 MOV     R1, #0x118\n"
"                 LDR     R0, =0xFFC9296C\n"
"                 LDMEQFD SP!, {R4,PC}\n"
"                 LDMFD   SP!, {R4,LR}\n"
"                 B       sub_ffc03b58\n" // DebugAssert
 );
}

