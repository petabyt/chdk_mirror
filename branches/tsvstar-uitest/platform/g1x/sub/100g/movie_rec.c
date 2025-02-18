#include "conf.h"

void change_video_tables(int a, int b){
}

void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

// @ 0xff1ca8a4
void __attribute__((naked,noinline)) movie_record_task(){ 

 asm volatile(
		"STMFD   SP!, {R2-R10,LR}\n"
		"LDR     R6, =0xFF1C98F4\n" //nullsub_163
		"LDR     R7, =0xFF1CA310\n" //sub_FF1CA310
		"LDR     R4, =0x9DA0\n"
		"LDR     R9, =0x6D6\n"
		"LDR     R10, =0x2710\n"
		"MOV     R8, #1\n"
		"MOV     R5, #0\n"
"loc_FF1CA8C4:\n"
		"LDR     R0, [R4,#0x24]\n"
		"MOV     R2, #0\n"
		"ADD     R1, SP, #4\n"
		"BL      sub_FF029EA8\n"
		"LDR     R0, [R4,#0x2C]\n"
		"CMP     R0, #0\n"
		"LDRNE   R0, [R4,#0xC]\n"
		"CMPNE   R0, #2\n"
		"LDRNE   R0, [R4,#0x44]\n"
		"CMPNE   R0, #6\n"
		"BNE     loc_FF1CAA00\n"
		"LDR     R0, [SP,#4]\n"
		"LDR     R1, [R0]\n"
		"SUB     R1, R1, #2\n"
		"CMP     R1, #0xD\n"
		"ADDCC   PC, PC, R1,LSL#2\n"
"                B       loc_FF1CAA00\n"
"                B       loc_FF1CA9A0\n"
"                B       loc_FF1CA9C4\n"
"                B       loc_FF1CA9D4\n"
"                B       loc_FF1CA9DC\n"
"                B       loc_FF1CA9E4\n"
"                B       loc_FF1CA9EC\n"
"                B       loc_FF1CA9A8\n"
"                B       loc_FF1CA9F4\n"
"                B       loc_FF1CA9B4\n"
"                B       loc_FF1CAA00\n"
"                B       loc_FF1CA9FC\n"
"                B       loc_FF1CA96C\n"
"                B       loc_FF1CA93C\n"

"loc_FF1CA93C:\n"
// jumptable FF1CA8C8 entry 12
		"STR     R5, [R4,#0x40]\n"
		"STR     R5, [R4,#0x30]\n"
		"STR     R5, [R4,#0x34]\n"
		"STRH    R5, [R4,#6]\n"
		"STR     R6, [R4,#0xD8]\n"
		"STR     R7, [R4,#0xF4]\n"
		"LDR     R0, [R4,#0xC]\n"
		"ADD     R0, R0, #1\n"
		"STR     R0, [R4,#0xC]\n"
		"MOV     R0, #6\n"
		"STR     R0, [R4,#0x44]\n"
		"B       loc_FF1CA98C\n"
"loc_FF1CA96C:\n"
// jumptable FF1CA8C8 entry 11
		"STR     R5, [R4,#0x40]\n"
		"STR     R5, [R4,#0x30]\n"
		"STR     R6, [R4,#0xD8]\n"
		"STR     R7, [R4,#0xF4]\n"
		"LDR     R0, [R4,#0xC]\n"
		"ADD     R0, R0, #1\n"
		"STR     R0, [R4,#0xC]\n"
		"STR     R8, [R4,#0x44]\n"
"loc_FF1CA98C:\n"
		"LDR     R2, =0xFF1C8E88\n" //sub_FF1C8E88
		"LDR     R1, =0xC4620\n"
		"LDR     R0, =0xFF1C8F9C\n" //sub_FF1C8F9C
		"BL      sub_FF046660\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9A0:\n"
// jumptable FF1CA8C8 entry 0
		"BL      sub_FF1C9E20\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9A8:\n"
// jumptable FF1CA8C8 entry 6
		"LDR     R1, [R4,#0xF4]\n"
		"BLX     R1\n"

"                LDR 	 R0, =0x9E24 \n"         //added - Found @FF1CA7C8 & FF1CA810 (0x9E28 - 4)
"                BL		 set_quality \n"         //added

		"B       loc_FF1CAA00\n"
"loc_FF1CA9B4:\n"
// jumptable FF1CA8C8 entry 8
		"LDR     R1, [R0,#0x18]\n"
		"LDR     R0, [R0,#4]\n"
		"BL      sub_FF36A0D4\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9C4:\n"
// jumptable FF1CA8C8 entry 1
		"LDR     R0, [R4,#0x44]\n"
		"CMP     R0, #5\n"
		"STRNE   R8, [R4,#0x34]\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9D4:\n"
// jumptable FF1CA8C8 entry 2
		"BL      sub_FF1C9558\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9DC:\n"
// jumptable FF1CA8C8 entry 3
		"BL      sub_FF1C9250\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9E4:\n"
// jumptable FF1CA8C8 entry 4
		"BL      sub_FF1C8FF4\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9EC:\n"
// jumptable FF1CA8C8 entry 5
		"BL      sub_FF1C8C1C\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9F4:\n"
// jumptable FF1CA8C8 entry 7
		"BL      sub_FF1C8B9C\n"
		"B       loc_FF1CAA00\n"
"loc_FF1CA9FC:\n"
// jumptable FF1CA8C8 entry 10
		"BL      sub_FF1CAF3C\n"
"loc_FF1CAA00:\n"
// jumptable FF1CA8C8 default entry
// jumptable FF1CA8C8 entry 9
		"LDR     R1, [SP,#4]\n"
		"LDR     R3, =0xFF1C8938\n" //aMovierecorder_ ; "MovieRecorder.c"
		"STR     R5, [R1]\n"
		"STR     R9, [SP]\n"
		"LDR     R0, [R4,#0x28]\n"
		"MOV     R2, R10\n"
		"BL      sub_FF02A820\n"
		"B       loc_FF1CA8C4\n"
 );
}

