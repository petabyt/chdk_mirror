#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 3 //model specific
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * pdc and name are always needed
 */
typedef struct
{
    int unkn1, unkn2, unkn3, unkn4, unkn5;
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    char name[32];
} fwt_data_struct;

#include "../../../generic/filewrite.c"

//filewritetask

void __attribute__((naked,noinline)) filewritetask() { //sub_FFA1E5B0_my
asm volatile (
      "    STMFD   SP!, {R1-R5,LR} \n" 
      "    LDR     R4, =0xBF3C \n" 
"loc_FFA1E5B8:\n"
      "    LDR     R0, [R4, #0x10] \n" 
      "    MOV     R2, #0 \n" 
      "    ADD     R1, SP, #8 \n" 
      "    BL      sub_FF827098 \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_FFA1E5E8 \n" 
      "    LDR     R0, [SP, #8] \n" 
      "    LDR     R1, [R0] \n" 
      "    CMP     R1, #1 \n" 
      "    BNE     loc_FFA1E5F0 \n" 
      "    LDR     R0, [R4, #8] \n" 
      "    BL      sub_FF827584 \n" 
"loc_FFA1E5E8:\n"
      "    BL      sub_FF81B184 \n" 
      "    LDMFD   SP!, {R1-R5,PC} \n" 
"loc_FFA1E5F0:\n"
      "    SUB     R1, R1, #2 \n" 
      "    CMP     R1, #5 \n" 
      "    ADDLS   PC, PC, R1, LSL #2 \n" 
      "    B       loc_FFA1E5B8 \n" 
      "    B       loc_FFA1E618 \n" 
      "    B       loc_FFA1E67C \n" 
      "    B       loc_FFA1E684 \n" 
      "    B       loc_FFA1E684 \n" 
      "    B       loc_FFA1E684 \n" 
      "    B       loc_FFA1E68C \n" 
"loc_FFA1E618:\n"
      "    MOV     R0, #0 \n" 
      "    STR     R0, [SP] \n" 
"loc_FFA1E620:\n"
      "    LDR     R0, [R4, #0x10] \n" 
      "    MOV     R1, SP \n" 
      "    BL      sub_FF8272DC \n" 
      "    LDR     R0, [SP] \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     loc_FFA1E64C \n" 
      "    LDR     R0, [R4, #0x10] \n" 
      "    MOV     R2, #0 \n" 
      "    ADD     R1, SP, #4 \n" 
      "    BL      sub_FF827098 \n" 
      "    B       loc_FFA1E620 \n" 
"loc_FFA1E64C:\n"
      "    LDR     R0, [R4] \n" 
      "    CMN     R0, #1 \n" 
      "    BEQ     loc_FFA1E670 \n" 
//      "    BL      sub_FF823AF4 \n"   //- Close
      "    BL      fwt_close\n"         //+
      "    MVN     R0, #0 \n" 
      "    STR     R0, [R4] \n" 
      "    LDR     R0, =0xB1CF4 \n" 
      "    BL      sub_FF8555B0 \n" 
      "    BL      sub_FF853C58 \n" 
"loc_FFA1E670:\n"
      "    LDR     R0, [R4, #0xC] \n" 
      "    BL      sub_FF827584 \n" 
      "    B       loc_FFA1E5B8 \n" 
"loc_FFA1E67C:\n"
      "    BL      sub_FFA1E850_my \n" //-> open
      "    B       loc_FFA1E5B8 \n" 
"loc_FFA1E684:\n"
      "    BL      sub_FFA1E98C_my \n" //-> write
      "    B       loc_FFA1E5B8 \n" 
"loc_FFA1E68C:\n"
      "    BL      sub_FFA1EA88_my \n" //-> close
      "    B       loc_FFA1E5B8 \n" 
      ".ltorg\n"    //+
    );
}


void __attribute__((naked,noinline)) sub_FFA1E850_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4-R8,LR} \n" 
      "    MOV     R4, R0 \n" 
      "    ADD     R0, R0, #0x2C \n" 
      "    SUB     SP, SP, #0x38 \n" 
      "    BL      sub_FF8555B0 \n" 
      "    MOV     R1, #0 \n" 
      "    BL      sub_FF853C08 \n" 
      "    LDR     R0, [R4, #0xC] \n" 
      "    BL      sub_FF851F18 \n" 
      "    LDR     R7, [R4, #8] \n" 
      "    LDR     R8, =0x1B6 \n" 
      "    ADD     R6, R4, #0x2C \n" 
      "    LDR     R5, [R4, #0xC] \n" 
//hook start
      "STMFD SP!, {R4-R12,LR}\n"
      "MOV R0, R4\n"
      "BL filewrite_main_hook\n"
      "LDMFD SP!, {R4-R12,LR}\n"
//hook end
      "    MOV     R0, R6 \n" 
      "    MOV     R1, R7 \n" 
      "    MOV     R2, R8 \n" 
//      "    BL      sub_FF823ACC \n"   //- Open
      "    BL      fwt_open\n"          //+
      "LDR PC, =0xFFA1E894\n"           //+ jump back to ROM
/*      "    CMN     R0, #1 \n"         //@sub_FFA1E850+0x44
      "    BNE     loc_FFA1E8F4 \n" 
      "    MOV     R0, R6 \n" 
      "    BL      sub_FF823FD4 \n" 
      "    MOV     R2, #0xF \n" 
      "    MOV     R1, R6 \n" 
      "    MOV     R0, SP \n" 
      "    BL      sub_FFAD1868 \n" 
      "    LDR     R0, =0x41FF \n" 
      "    MOV     R1, #0 \n" 
      "    STRB    R1, [SP, #0xF] \n" 
      "    STR     R0, [SP, #0x20] \n" 
      "    MOV     R0, #0x10 \n" 
      "    ADD     R2, SP, #0x24 \n" 
      "    STMIA   R2, {R0,R1,R5} \n" 
      "    ADD     R1, SP, #0x20 \n" 
      "    MOV     R0, SP \n" 
      "    STR     R5, [SP, #0x30] \n" 
      "    STR     R5, [SP, #0x34] \n" 
      "    BL      sub_FF85351C \n" 
      "    MOV     R2, R8 \n" 
      "    MOV     R1, R7 \n" 
      "    MOV     R0, R6 \n" 
      "    BL      sub_FF823ACC \n" 
"loc_FFA1E8F4:\n"
      "    LDR     R5, =0xBF3C \n" 
      "    CMN     R0, #1 \n" 
      "    STR     R0, [R5] \n" 
      "    BNE     loc_FFA1E930 \n" 
      "    ADD     R0, R4, #0x2C \n" 
      "    BL      sub_FF8555B0 \n" 
      "    BL      sub_FF853C58 \n" 
      "    LDR     R1, [R5, #0x14] \n" 
      "    CMP     R1, #0 \n" 
      "    ADDNE   SP, SP, #0x38 \n" 
      "    LDMNEFD SP!, {R4-R8,LR} \n" 
      "    LDRNE   R0, =0x9200001 \n" 
      "    BXNE    R1 \n" 
"loc_FFA1E928:\n"
      "    ADD     SP, SP, #0x38 \n" 
      "    LDMFD   SP!, {R4-R8,PC} \n" 
"loc_FFA1E930:\n"
      "    LDR     R0, =0xB1CF4 \n" 
      "    MOV     R2, #0x20 \n" 
      "    ADD     R1, R4, #0x2C \n" 
      "    BL      sub_FFAD19D0 \n" 
      "    MOV     R1, R4 \n" 
      "    MOV     R0, #4 \n" 
      "    BL      sub_FFA1E508 \n" 
      "    B       loc_FFA1E928 \n" */
    );
}


void __attribute__((naked,noinline)) sub_FFA1E98C_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4-R10,LR} \n" 
      "    MOV     R4, R0 \n" 
      "    LDR     R0, [R0] \n" 
      "    CMP     R0, #4 \n" 
      "    LDREQ   R6, [R4, #0x18] \n" 
      "    LDREQ   R7, [R4, #0x14] \n" 
      "    BEQ     loc_FFA1E9C8 \n" 
      "    CMP     R0, #5 \n" 
      "    LDREQ   R6, [R4, #0x20] \n" 
      "    LDREQ   R7, [R4, #0x1C] \n" 
      "    BEQ     loc_FFA1E9C8 \n" 
      "    CMP     R0, #6 \n" 
      "    BNE     loc_FFA1E9DC \n" 
      "    LDR     R6, [R4, #0x28] \n" 
      "    LDR     R7, [R4, #0x24] \n" 
"loc_FFA1E9C8:\n"
      "    CMP     R6, #0 \n" 
      "    BNE     loc_FFA1E9EC \n" 
"loc_FFA1E9D0:\n"
      "    MOV     R1, R4 \n" 
      "    MOV     R0, #7 \n" 
      "    B       loc_FFA1EA80 \n" 
"loc_FFA1E9DC:\n"
      "    LDR     R1, =0x205 \n" 
      "    LDR     R0, =0xFFA1E96C \n" 
      "    BL      sub_FF81B1CC \n" 
      "    B       loc_FFA1E9D0 \n" 
"loc_FFA1E9EC:\n"
      "    LDR     R9, =0xBF3C \n" 
      "    MOV     R5, R6 \n" 
"loc_FFA1E9F4:\n"
      "    LDR     R0, [R4, #4] \n" 
      "    CMP     R5, #0x1000000 \n" 
      "    MOVLS   R8, R5 \n" 
      "    MOVHI   R8, #0x1000000 \n" 
      "    BIC     R1, R0, #0xFF000000 \n" 
      "    CMP     R1, #0 \n" 
      "    BICNE   R0, R0, #0xFF000000 \n" 
      "    RSBNE   R0, R0, #0x1000000 \n" 
      "    CMPNE   R8, R0 \n" 
      "    MOVHI   R8, R0 \n" 
      "    LDR     R0, [R9] \n" 
      "    MOV     R2, R8 \n" 
      "    MOV     R1, R7 \n" 
//      "    BL      sub_FF823BA0 \n"   //- Write
      "    BL      fwt_write\n"         //+
      "    LDR     R1, [R4, #4] \n" 
      "    CMP     R8, R0 \n" 
      "    ADD     R1, R1, R0 \n" 
      "    STR     R1, [R4, #4] \n" 
      "    BEQ     loc_FFA1EA54 \n" 
      "    LDR     R0, =0x10B1 \n" 
      "    BL      sub_FF878BA8 \n" 
      "    LDR     R1, =0x9200005 \n" 
      "    STR     R1, [R4, #0x10] \n" 
      "    B       loc_FFA1E9D0 \n" 
"loc_FFA1EA54:\n"
      "    SUB     R5, R5, R0 \n" 
      "    CMP     R5, R6 \n" 
      "    ADD     R7, R7, R0 \n" 
      "    LDRCS   R0, =0xFFA1E96C \n" 
      "    MOVCS   R1, #0x234 \n" 
      "    BLCS    sub_FF81B1CC \n" 
      "    CMP     R5, #0 \n" 
      "    BNE     loc_FFA1E9F4 \n" 
      "    LDR     R0, [R4] \n" 
      "    MOV     R1, R4 \n" 
      "    ADD     R0, R0, #1 \n" 
"loc_FFA1EA80:\n"
      "    LDMFD   SP!, {R4-R10,LR} \n" 
      "    B       sub_FFA1E508 \n" 
    );
}


void __attribute__((naked,noinline)) sub_FFA1EA88_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4,R5,LR} \n" 
      "    LDR     R5, =0xBF3C \n" 
      "    MOV     R4, R0 \n" 
      "    LDR     R0, [R5] \n" 
      "    SUB     SP, SP, #0x1C \n" 
      "    CMN     R0, #1 \n" 
      "    BEQ     loc_FFA1EABC \n" 
//      "    BL      sub_FF823AF4 \n"   //- Close
      "    BL      fwt_close\n"         //+
      "    CMP     R0, #0 \n" 
      "    LDRNE   R0, =0x9200003 \n" 
      "    STRNE   R0, [R4, #0x10] \n" 
      "    MVN     R0, #0 \n" 
      "    STR     R0, [R5] \n" 
"loc_FFA1EABC:\n"
      "LDR PC, =0xFFA1EABC\n"           //+ jump back to ROM
/*      "    LDR     R0, [R4, #0x10] \n" 
      "    TST     R0, #1 \n" 
      "    BNE     loc_FFA1EB04 \n" 
      "    LDR     R0, =0x81FF \n" 
      "    ADD     R1, SP, #4 \n" 
      "    STR     R0, [SP, #4] \n" 
      "    MOV     R0, #0x20 \n" 
      "    STR     R0, [SP, #8] \n" 
      "    LDR     R0, [R4, #4] \n" 
      "    STR     R0, [SP, #0xC] \n" 
      "    LDR     R0, [R4, #0xC] \n" 
      "    STR     R0, [SP, #0x10] \n" 
      "    LDR     R0, [R4, #0xC] \n" 
      "    STR     R0, [SP, #0x14] \n" 
      "    LDR     R0, [R4, #0xC] \n" 
      "    STR     R0, [SP, #0x18] \n" 
      "    ADD     R0, R4, #0x2C \n" 
      "    BL      sub_FF85351C \n" 
"loc_FFA1EB04:\n"
      "    ADD     R0, R4, #0x2C \n" 
      "    BL      sub_FF8555B0 \n" 
      "    BL      sub_FF853C58 \n" 
      "    LDR     R1, [R5, #0x14] \n" 
      "    CMP     R1, #0 \n" 
      "    LDRNE   R0, [R4, #0x10] \n" 
      "    BLXNE   R1 \n" 
      "    ADD     SP, SP, #0x1C \n" 
      "    LDMFD   SP!, {R4,R5,PC} \n" */
    );
}

