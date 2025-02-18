#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)0x6134;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FFD483A4_my(long p)
{
  asm volatile (
              "STMFD   SP!, {R4-R6,LR}\n"
              "LDR     R3, =0x64DDC\n"
              "LDR     R5, =0x6130\n"
              "SUB     SP, SP, #4\n"
              "LDR     R1, =0xFFFFFFFF\n"
              "STR     R0, [R5]\n"
              "LDR     R0, [R3]\n"
              "BL      sub_FFC0FB44\n"
              "LDR     R3, =0x8F480\n"
              "LDR     R0, [R3,#0x74]\n"
              "BL      sub_FFC8BFB8\n"
              "BL      sub_FFD482F8\n"
             
              "LDR     R3, =0x6138\n"
              "LDR     R0, [R3]\n"
              "BL      sub_FFC8C454\n"
            "BL      wait_until_remote_button_is_released\n"
              "BL      capt_seq_hook_set_nr\n"
              "B       sub_FFD483E0\n"
  );
}

void __attribute__((naked,noinline)) sub_FFD45048_my(long p)
{
  asm volatile (
              "STMFD   SP!, {R4,LR}\n"
              "LDR     R4, [R0,#0xC]\n"
              "BL      sub_FFD4D73C\n"
              "CMP     R0, #0\n"
              "BNE     loc_FFD45060\n"
              "BL      sub_FFD4D748\n"
    "loc_FFD45060:\n"
              "MOV     R0, #0xC\n"
              "BL      sub_FFD4D75C\n"
              "TST     R0, #1\n"
              "MOV     R2, R4\n"
              "MOV     R0, R4\n"
              "BEQ     loc_FFD45088\n"
              "MOV     R0, #1\n"
              "MOV     R1, R0\n"
              "LDMFD   SP!, {R4,LR}\n"
              "B       sub_FFD43578\n"
    "loc_FFD45088:\n"
              "BL      sub_FFD47160\n"
              "TST     R0, #1\n"
              "MOV     R2, R4\n"
              "MOV     R1, #1\n"
              "BEQ     loc_FFD450A4\n"
              "LDMFD   SP!, {R4,LR}\n"
              "B       sub_FFD43578\n"
    "loc_FFD450A4:\n"
              "BL      sub_FFD85D18\n"
              "BL      sub_FFC146EC\n"
              "LDR     R2, =0x8F3C4\n"
              "ADD     R3, R4, R4,LSL#1\n"
              "STR     R0, [R2,R3,LSL#5]\n"
              "MOV     R0, R4\n"
              "BL      sub_FFD48B10\n"
              "BL      sub_FFD47664\n"
              "BL      sub_FFD47600\n"
              "MOV     R0, R4\n"

              "BL      sub_FFD483A4_my\n"
              "BL      capt_seq_hook_raw_here\n"

             // "BL      sub_FFD483A4\n"

              "MOV     R2, R4\n"
              "MOV     R1, #1\n"
              "BL      sub_FFD43578\n"
              "LDMFD   SP!, {R4,LR}\n"
              "B       sub_FFD4859C\n"
  );
}


void __attribute__((naked,noinline)) capt_seq_task()
{
  asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "SUB     SP, SP, #4\n"
          "MOV     R4, SP\n"
          "B       loc_FFD455BC\n"
    "loc_FFD45464:\n"
          "LDR     R2, [SP,#0xC-0xC]\n"
          "LDR     R3, [R2]\n"
          "MOV     R0, R2\n"
          "CMP     R3, #0x15\n"
          "LDRLS   PC, [PC,R3,LSL#2]\n"
          "B       loc_FFD45590\n"
          ".long loc_FFD454D4\n"
          ".long loc_FFD454E0\n"
          ".long loc_FFD454E8\n"
          ".long loc_FFD454F8\n"
          ".long loc_FFD454F0\n"
          ".long loc_FFD45500\n"
          ".long loc_FFD45508\n"
          ".long loc_FFD45514\n"
          ".long loc_FFD4551C\n"
          ".long loc_FFD45528\n"
          ".long loc_FFD45530\n"
          ".long loc_FFD45538\n"
          ".long loc_FFD45540\n"
          ".long loc_FFD45548\n"
          ".long loc_FFD45550\n"
          ".long loc_FFD4555C\n"
          ".long loc_FFD45564\n"
          ".long loc_FFD4556C\n"
          ".long loc_FFD45574\n"
          ".long loc_FFD45580\n"
          ".long loc_FFD45588\n"
          ".long loc_FFD455A4\n"
    "loc_FFD454D4:\n"
          "BL      sub_FFD46DB8\n"
          "BL      shooting_expo_param_override\n"   // +
        //  "BL	 handle_is_off\n"
          "BL      sub_FFD4311C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD454E0:\n"
     			//"BL      sub_FFD45048\n"
          "BL      sub_FFD45048_my\n"
					"B       loc_FFD455A0\n"
    "loc_FFD454E8:\n"
          "BL      sub_FFD47150\n"
          "B       loc_FFD455A0\n"
    "loc_FFD454F0:\n"
          "BL      sub_FFD4601C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD454F8:\n" //shooting but. rel.
          "BL      sub_FFD46454\n"
       //   "BL	 handle_is_on\n"            //+
          "B       loc_FFD455A0\n"
    "loc_FFD45500:\n"
          "BL      sub_FFD46464\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45508:\n"
          "BL      sub_FFD46E9C\n"
          "BL      sub_FFD4311C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45514:\n"
          "BL      sub_FFD45154\n"
          "B       loc_FFD455A0\n"
    "loc_FFD4551C:\n"
          "BL      sub_FFD46F04\n"
          "BL      sub_FFD4311C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45528:\n"
          "BL      sub_FFD46454\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45530:\n"
          "BL      sub_FFD476A4\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45538:\n"
          "BL      sub_FFD479E8\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45540:\n"
          "BL      sub_FFD47A6C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45548:\n"
          "BL      sub_FFD47B5C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45550:\n"
          "MOV     R0, #0\n"
          "BL      sub_FFD47C24\n"
          "B       loc_FFD455A0\n"
    "loc_FFD4555C:\n"
          "BL      sub_FFD47D90\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45564:\n"
          "BL      sub_FFD47E24\n"
          "B       loc_FFD455A0\n"
    "loc_FFD4556C:\n"
          "BL      sub_FFD47EE0\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45574:\n"
          "MOV     R0, #1\n"
          "BL      sub_FFD47C24\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45580:\n"
          "BL      sub_FFD47FCC\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45588:\n"
          "BL      sub_FFD48020\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45590:\n"
          "MOV     R1, #0x36C\n"
          "LDR     R0, =0xFFD44DD4\n"
          "ADD     R1, R1, #1\n"
          "BL      sub_FFC03AE8\n"
    "loc_FFD455A0:\n"
          "LDR     R2, [SP,#0xC-0xC]\n"
    "loc_FFD455A4:\n"
          "LDR     R3, =0x64D64\n"
          "LDR     R1, [R2,#4]\n"
          "LDR     R0, [R3]\n"
          "BL      sub_FFC0F9A8\n"
          "LDR     R0, [SP,#0xC-0xC]\n"
          "BL      sub_FFD44E50\n"
    "loc_FFD455BC:\n"
          "LDR     R3, =0x64D68\n"
          "MOV     R1, R4\n"
          "LDR     R0, [R3]\n"
          "MOV     R2, #0\n"
          "BL      sub_FFC100C0\n"
          "TST     R0, #1\n"
          "BEQ     loc_FFD45464\n"
          "MOV     R1, #0x2A4\n"
          "LDR     R0, =0xFFD44DD4\n"
          "ADD     R1, R1, #3\n"
          "BL      sub_FFC03AE8\n"
          "BL      _ExitTask\n"
          "BL      sub_FFC1161C\n"
          "ADD     SP, SP, #4\n"
          "LDMFD   SP!, {R4,PC}\n"
  );
}

/*************************************************************/
void __attribute__((naked,noinline)) exp_drv_task(){
 asm volatile(
"                STMFD   SP!, {R4-R8,LR}\n"
"                SUB     SP, SP, #0x14\n"
"                MOV     R7, SP\n"
"                B       loc_FFCF4804\n"
"loc_FFCF4418:\n"
"                CMP     R2, #0x1F\n"
"                BNE     loc_FFCF4430\n"
"                LDR     R0, [R12,#0x50]\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R12,#0x4C]\n"
"                B       loc_FFCF4490\n"
"loc_FFCF4430:\n"
"                CMP     R2, #0x1A\n"
"                BNE     loc_FFCF4444\n"
"                MOV     R0, R12\n"
"                BL      sub_FFCF4338\n"
"                B       loc_FFCF4480\n"
"loc_FFCF4444:\n"
"                CMP     R2, #0x1B\n"
"                BNE     loc_FFCF4458\n"
"                MOV     R0, R12\n"
"                BL      sub_FFCF4374\n"
"                B       loc_FFCF4480\n"
"loc_FFCF4458:\n"
"                SUB     R3, R2, #0x1C\n"
"                CMP     R3, #1\n"
"                BHI     loc_FFCF4470\n"
"                MOV     R0, R12\n"
"                BL      sub_FFCF43B0\n"
"                B       loc_FFCF4480\n"
"loc_FFCF4470:\n"
"                CMP     R2, #0x1E\n"
"                BNE     loc_FFCF449C\n"
"                BL      sub_FFC9E504\n" //Shutter.c:372
"                BL      sub_FFCA02F4\n" //ImgGain.c:436
"loc_FFCF4480:\n"
"                LDR     R3, [SP]\n"
"                LDR     R0, [R3,#0x50]\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R3,#0x4C]\n"
"loc_FFCF4490:\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FFCF1E2C\n"
"                B       loc_FFCF4804\n"
"loc_FFCF449C:\n"
"                CMP     R2, #0xD\n"
"                MOV     R8, #1\n"
"                BNE     loc_FFCF450C\n"
"                LDR     R1, [R12,#0x40]\n"
"                ADD     R1, R1, R1,LSL#1\n"
"                ADD     R1, R12, R1,LSL#1\n"
"                ADD     R6, SP, #0xC\n"
"                SUB     R1, R1, #2\n"
"                MOV     R2, #6\n"
"                MOV     R0, R6\n"
"                BL      _memcpy\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FFCF33E8\n"
"                LDR     R3, [SP]\n"
"                LDR     R1, [R3,#0x40]\n"
"                LDR     R2, [R3,#0x50]\n"
"                ADD     R0, R3, #4\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R3,#0x4C]\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FFCF356C\n"
"                LDR     R3, [SP]\n"
"                ADD     R0, R3, #4\n"
"                LDR     R1, [R3,#0x40]\n"
"                LDR     R2, [R3,#0x58]\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R3,#0x54]\n"
"                B       loc_FFCF47B4\n"
"loc_FFCF450C:\n"
"                SUB     R3, R2, #0xE\n"
"                CMP     R3, #1\n"
"                BHI     loc_FFCF45C8\n"
"                ADD     R6, SP, #0xC\n"
"                ADD     R5, SP, #4\n"
"                MOV     R0, R12\n"
"                MOV     R1, R6\n"
"                MOV     R2, R5\n"
"                BL      sub_FFCF35E8\n"
"                MOV     R4, R0\n"
"                CMP     R4, #5\n"
"                CMPNE   R4, #1\n"
"                BNE     loc_FFCF4560\n"
"                LDR     R12, [SP]\n"
"                MOV     R0, R5\n"
"                LDR     R1, [R12,#0x40]\n"
"                MOV     R2, R4\n"
"                LDR     R3, [R12,#0x50]\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R12,#0x4C]\n"
"                B       loc_FFCF4598\n"
"loc_FFCF4560:\n"
"                CMP     R4, #6\n"
"                CMPNE   R4, #2\n"
"                BNE     loc_FFCF45A8\n"
"                LDR     R12, [SP]\n"
"                MOV     R0, R5\n"
"                MOV     R1, R8\n"
"                MOV     R2, R4\n"
"                LDR     R3, [R12,#0x50]\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R12,#0x4C]\n"
"                MOV     R1, R6\n"
"                LDR     R0, [SP]\n"
"                MOV     R2, R5\n"
"                BL      sub_FFCF4174\n"
"loc_FFCF4598:\n"
"                MOV     R1, R4\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FFCF4318\n"
"                B       loc_FFCF47B4\n"
"loc_FFCF45A8:\n"
"                LDR     R12, [SP]\n"
"                MOV     R2, R4\n"
"                ADD     R0, R12, #4\n"
"                LDR     R1, [R12,#0x40]\n"
"                LDR     R3, [R12,#0x50]\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R12,#0x4C]\n"
"                B       loc_FFCF47B4\n"
"loc_FFCF45C8:\n"
"                SUB     R3, R2, #0x17\n"
"                CMP     R3, #1\n"
"                BHI     loc_FFCF4620\n"
"                LDR     R1, [R12,#0x40]\n"
"                ADD     R1, R1, R1,LSL#1\n"
"                ADD     R1, R12, R1,LSL#1\n"
"                ADD     R6, SP, #0xC\n"
"                SUB     R1, R1, #2\n"
"                MOV     R2, #6\n"
"                MOV     R0, R6\n"
"                BL      _memcpy\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FFCF2E54\n"
"                LDR     R3, [SP]\n"
"                ADD     R0, R3, #4\n"
"                LDR     R1, [R3,#0x40]\n"
"                LDR     R2, [R3,#0x50]\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R3,#0x4C]\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FFCF30EC\n"
"                B       loc_FFCF47B4\n"
"loc_FFCF4620:\n"
"                ADD     R6, SP, #0xC\n"
"                ADD     R1, R12, #4\n"
"                MOV     R2, #6\n"
"                MOV     R0, R6\n"
"                BL      _memcpy\n"
"                LDR     R12, [SP]\n"
"                LDR     R3, [R12]\n"
"                MOV     R2, R12\n"
"                CMP     R3, #0x19\n"
"                LDRLS   PC, [PC,R3,LSL#2]\n"
"                B       loc_FFCF47A0\n"
"                .long loc_FFCF46B4\n"
"                .long loc_FFCF46C0\n"
"                .long loc_FFCF46CC\n"
"                .long loc_FFCF46CC\n"
"                .long loc_FFCF46B4\n"
"                .long loc_FFCF46C0\n"
"                .long loc_FFCF46CC\n"
"                .long loc_FFCF46CC\n"
"                .long loc_FFCF46F0\n"
"                .long loc_FFCF46F0\n"
"                .long loc_FFCF4774\n"
"                .long loc_FFCF4780\n"
"                .long loc_FFCF4790\n"
"                .long loc_FFCF47A0\n"
"                .long loc_FFCF47A0\n"
"                .long loc_FFCF47A0\n"
"                .long loc_FFCF46D8\n"
"                .long loc_FFCF46E4\n"
"                .long loc_FFCF4700\n"
"                .long loc_FFCF470C\n"
"                .long loc_FFCF4734\n"
"                .long loc_FFCF475C\n"
"                .long loc_FFCF475C\n"
"                .long loc_FFCF47A0\n"
"                .long loc_FFCF47A0\n"
"                .long loc_FFCF4768\n"
"loc_FFCF46B4:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF23D0\n"
"                B       loc_FFCF479C\n"
"loc_FFCF46C0:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF250C\n"
"                B       loc_FFCF479C\n"
"loc_FFCF46CC:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF263C\n"
"                B       loc_FFCF479C\n"
"loc_FFCF46D8:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF2810\n"
"                B       loc_FFCF479C\n"
"loc_FFCF46E4:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF2918\n"
"                B       loc_FFCF479C\n"
"loc_FFCF46F0:\n"
"                MOV     R0, R2\n"
//"                BL      sub_FFCF29DC\n" // ->
"                BL      sub_FFCF29DC_my\n" // ->
"                MOV     R8, #0\n"
"                B       loc_FFCF479C\n"
"loc_FFCF4700:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF2A9C\n"
"                B       loc_FFCF479C\n"
"loc_FFCF470C:\n"
"                MOV     R0, R2\n"
"                LDRH    R2, [R2,#4]\n"
"                LDR     R3, =0x4023C\n"
"                STRH    R2, [SP,#0xC]\n"
"                LDRH    R1, [R3,#4]\n"
"                STRH    R1, [SP,#0x10]\n"
"                LDRH    R3, [R3,#2]\n"
"                STRH    R3, [SP,#0xE]\n"
"                BL      sub_FFCF2C24\n"
"                B       loc_FFCF479C\n"
"loc_FFCF4734:\n"
"                LDR     R3, =0x4023C\n"
"                LDRH    R1, [R3]\n"
"                STRH    R1, [SP,#0xC]\n"
"                MOV     R0, R2\n"
"                LDRH    R2, [R2,#6]\n"
"                STRH    R2, [SP,#0xE]\n"
"                LDRH    R3, [R3,#4]\n"
"                STRH    R3, [SP,#0x10]\n"
"                BL      sub_FFCF2CB8\n"
"                B       loc_FFCF479C\n"
"loc_FFCF475C:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF2D38\n"
"                B       loc_FFCF479C\n"
"loc_FFCF4768:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF317C\n"
"                B       loc_FFCF479C\n"
"loc_FFCF4774:\n"
"                MOV     R0, R2\n"
"                BL      sub_FFCF3250\n"
"                B       loc_FFCF479C\n"
"loc_FFCF4780:\n"
"                MOV     R0, R2\n"
"                MOV     R1, #0\n"
"                BL      sub_FFCF333C\n"
"                B       loc_FFCF479C\n"
"loc_FFCF4790:\n"
"                MOV     R0, R2\n"
"                MOV     R1, #1\n"
"                BL      sub_FFCF333C\n"
"loc_FFCF479C:\n"
"                LDR     R12, [SP]\n"
"loc_FFCF47A0:\n"
"                ADD     R0, R12, #4\n"
"                LDR     R1, [R12,#0x40]\n"
"                LDR     R2, [R12,#0x50]\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R12,#0x4C]\n"
"loc_FFCF47B4:\n"
"                CMP     R8, #1\n"
"                BNE     loc_FFCF47DC\n"
"                LDR     R1, [SP]\n"
"                LDR     R3, [R1,#0x40]\n"
"                ADD     R3, R3, R3,LSL#1\n"
"                ADD     R1, R1, R3,LSL#1\n"
"                MOV     R0, R6\n"
"                SUB     R1, R1, #2\n"
"                BL      sub_FFCF2240\n"
"                B       loc_FFCF47FC\n"
"loc_FFCF47DC:\n"
"                MOV     R0, #1\n"
"                MOV     R1, R0\n"
"                MOV     R2, R0\n"
"                BL      sub_FFCF21E4\n"
"                MOV     R0, #1\n"
"                MOV     R1, R0\n"
"                MOV     R2, R0\n"
"                BL      sub_FFCF22FC\n"
"loc_FFCF47FC:\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FFCF1E2C\n"
"loc_FFCF4804:\n"
"                LDR     R3, =0x40234\n"
"                MOV     R2, #0\n"
"                LDR     R0, [R3]\n"
"                MOV     R1, R7\n"
"                BL      sub_FFC100C0\n" //ReceiveMessageQueue
"                LDR     R12, [SP]\n"
"                LDR     R2, [R12]\n"
"                CMP     R2, #0x20\n"
"                BNE     loc_FFCF4418\n"
"                MOV     R0, R12\n"
"                BL      sub_FFCF1E2C\n"
"                LDR     R3, =0x40230\n"
"                MOV     R1, #1\n"
"                LDR     R0, [R3]\n"
"                BL      sub_FFC0F9A8\n"// SetEventFlag
"                BL      _ExitTask\n"
"                ADD     SP, SP, #0x14\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
 );
}
void __attribute__((naked,noinline)) sub_FFCF29DC_my(){
 asm volatile(
"                STMFD   SP!, {R4,R5,LR}\n"
"                LDR     R3, =0x40230\n"
"                MOV     R4, R0\n"
"                MOV     R1, #0xE\n"
"                LDR     R0, [R3]\n"
"                BL      sub_FFC0FB44\n" //ClearEventFlag
"                MOV     R1, #0\n"
"                LDRSH   R0, [R4,#4]\n"
"                BL      sub_FFCF1F08\n"
"                MOV     R5, R0\n"
"                LDRSH   R0, [R4,#6]\n"
"                BL      sub_FFCF207C\n"
"                LDRSH   R0, [R4,#8]\n"
"                BL      sub_FFCF2118\n"
"                LDR     R3, [R4]\n"
"                CMP     R3, #9\n"
"                MOVEQ   R5, #0\n"
"                CMP     R5, #1\n"
"                LDR     R1, =0xFFCF1E60\n"
"                MOV     R2, #2\n"
"                BNE     loc_FFCF2A48\n"
"                LDRSH   R0, [R4,#4]\n"
"                BL      sub_FFE81ADC\n" //IrisController.c:178
"                LDR     R2, =0x4025C\n"
"                MOV     R3, #0\n"
"                STR     R3, [R2]\n"
"                B       loc_FFCF2A4C\n"
"loc_FFCF2A48:\n"
"                BL      sub_FFCF21B4\n"
"loc_FFCF2A4C:\n"
"                STRH    R0, [R4,#4]\n"
"                LDRSH   R0, [R4,#6]\n"
"                BL      sub_FFC9E18C_my\n" //Shutter.c:276 ->
"                LDRSH   R0, [R4,#8]\n"
"                MOV     R1, #1\n"
"                BL      sub_FFC9FEB4\n" //ImgGain.c:292
"                MOV     R1, #0\n"
"                ADD     R0, R4, #8\n"
"                BL      sub_FFC9FF74\n" //ImgGain.c:316
"                CMP     R5, #1\n"
"                MOV     R1, #2\n"
"                MOV     R2, #0\n"
"                LDMNEFD SP!, {R4,R5,PC}\n"
"                LDR     R3, =0x40230\n"
"                LDR     R0, [R3]\n"
"                LDMFD   SP!, {R4,R5,LR}\n"
"                B       sub_FFC0F998\n"
 );
}
void __attribute__((naked,noinline)) sub_FFC9E18C_my() { // __Shutter_c__276
 asm volatile(
"                STMFD   SP!, {R4,LR}\n"
"                LDR     R3, =0x5334\n"
"                LDR     R2, [R3]\n"
"                MOV     R1, #0x114\n"
"                MOV     R3, R0,LSL#16\n"
"                CMP     R2, #1\n"
"                ADD     R1, R1, #1\n"
"                LDR     R0, =0xFFC9DC08\n" // "Shutter.c"
"                MOV     R4, R3,ASR#16\n"
"                BEQ     loc_FFC9E1B8\n"
"                BL      sub_FFC03AE8\n" // DebugAssert
"loc_FFC9E1B8:\n"
"                MOV     R1, #0x118\n"
"                CMN     R4, #0xC00\n"
"                LDR     R3, =0x32DF6\n"
"                LDR     R0, =0xFFC9DC08\n" // "Shutter.c"
"                ADD     R1, R1, #3\n"
"                LDREQSH R4, [R3]\n"
"                LDRNE   R3, =0x32DF6\n"
"                CMN     R4, #0xC00\n"
"                STRH    R4, [R3]\n"
"                BNE     loc_FFC9E1E4\n"
"                BL      sub_FFC03AE8\n" // DebugAssert
"loc_FFC9E1E4:\n"
"                MOV     R0, R4\n"
//"                BL      sub_FFC9F288\n"
"                BL      apex2us\n" // + 
"                MOV     R4, R0\n"
"                BL      sub_FFCC625C\n"
"                MOV     R0, R4\n"
"                BL      sub_FFC9D7C0\n"
"                TST     R0, #1\n"
"                MOV     R1, #0x120\n"
"                LDR     R0, =0xFFC9DC08\n" // "Shutter.c"
"                LDMEQFD SP!, {R4,PC}\n"
"                LDMFD   SP!, {R4,LR}\n"
"                B       sub_FFC03AE8\n" // DebugAssert
 );
}

