#include "conf.h"

// from sx10
void change_video_tables(int a, int b){
}

// from sx10, not sure if the values are right, seems to work

void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
"	STMFD	SP!, {R2-R8,LR} \n"                
"	LDR	R8, =0x442 \n"                       
"	LDR	R7, =0x2710 \n"                      
"	LDR	R4, =0x5AD8 \n"                      
"	MOV	R6, #0 \n"                           
"	MOV	R5, #1 \n"                           
"loc_FF91A6C4:\n"
"	LDR	R0, [R4, #0x18] \n"                  
"	MOV	R2, #0 \n"                           
"	ADD	R1, SP, #4 \n"                       
"	BL	sub_FF826978 \n"                      
"	LDR	R0, [R4, #0x20] \n"                  
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF91A794 \n"                     
"	LDR	R0, [SP, #4] \n"                     
"	LDR	R1, [R0] \n"                         
"	SUB	R1, R1, #2 \n"                       
"	CMP	R1, #9 \n"                           
"	ADDLS	PC, PC, R1, LSL #2 \n"             
"	B	loc_FF91A794 \n"                       
"	B	loc_FF91A748 \n"                       
"	B	loc_FF91A768 \n"                       
"	B	loc_FF91A778 \n"                       
"	B	loc_FF91A780 \n"                       
"	B	loc_FF91A750 \n"                       
"	B	loc_FF91A788 \n"                       
"	B	loc_FF91A758 \n"                       
"	B	loc_FF91A794 \n"                       
"	B	loc_FF91A790 \n"                       
"	B	loc_FF91A720 \n"                       
"loc_FF91A720:\n"
"	LDR	R0, =0xFF91A3C0 \n"                  
"	STR	R6, [R4, #0x34] \n"                  
"	STR	R0, [R4, #0x9C] \n"                  
"	LDR	R0, =0xFF9199E0 \n"                  
"	LDR	R2, =0xFF9198FC \n"                  
"	LDR	R1, =0x2BDB0 \n"                     
"	STR	R6, [R4, #0x24] \n"                  
"	BL	sub_FF8B11AC \n"                      
"	STR	R5, [R4, #0x38] \n"                  
"	B	loc_FF91A794 \n"                       
"loc_FF91A748:\n"
"   BL      unlock_optical_zoom\n" //  +
"	BL	sub_FF91A4C8 \n"                      
"	B	loc_FF91A794 \n"                       
"loc_FF91A750:\n"
"	BL	sub_FF91A064_my\n"  // -- >                   
"	B	loc_FF91A794 \n"                       
"loc_FF91A758:\n"
"	LDR	R1, [R0, #0x18] \n"                  
"	LDR	R0, [R0, #4] \n"                     
"	BL	sub_FFA37D50 \n"                      
"	B	loc_FF91A794 \n"                       
"loc_FF91A768:\n"
"	LDR	R0, [R4, #0x38] \n"                  
"	CMP	R0, #5 \n"                           
"	STRNE	R5, [R4, #0x28] \n"                
"	B	loc_FF91A794 \n"                       
"loc_FF91A778:\n"
"	BL	sub_FF919D4C \n"                      
"	B	loc_FF91A794 \n"                       
"loc_FF91A780:\n"
"	BL	sub_FF919A2C \n"                      
"	B	loc_FF91A794 \n"                       
"loc_FF91A788:\n"
"	BL	sub_FF919888 \n"                      
"	B	loc_FF91A794 \n"                       
"loc_FF91A790:\n"
"	BL	sub_FF91A8FC \n"                      
"loc_FF91A794:\n"
"	LDR	R1, [SP, #4] \n"                     
"	LDR	R3, =0xFF9196EC \n"                  
"	STR	R6, [R1] \n"                         
"	STR	R8, [SP] \n"                         
"	LDR	R0, [R4, #0x1C] \n"                  
"	MOV	R2, R7 \n"                           
"	BL	sub_FF8272CC \n"                      
"	B	loc_FF91A6C4 \n"           
 );
}

void __attribute__((naked,noinline)) sub_FF91A064_my(){
 asm volatile(
"	STMFD	SP!, {R4-R9,LR} \n"                
"	SUB	SP, SP, #0x44 \n"                    
"	MOV	R7, #0 \n"                           
"	LDR	R6, =0x5AD8 \n"                      
"	MOV	R4, R0 \n"                           
"	STR	R7, [SP, #0x34] \n"                  
"	STR	R7, [SP, #0x2C] \n"                  
"	LDR	R0, [R6, #0x38] \n"                  
"	MOV	R8, #4 \n"                           
"	CMP	R0, #3 \n"                           
"	STREQ	R8, [R6, #0x38] \n"                
"	LDR	R0, [R6, #0x9C] \n"                  
"	BLX	R0 \n"                               
"	LDR	R0, [R6, #0x38] \n"                  
"	CMP	R0, #4 \n"                           
"	BNE	loc_FF91A1B4 \n"                     
"	ADD	R3, SP, #0x2C \n"                    
"	ADD	R2, SP, #0x30 \n"                    
"	ADD	R1, SP, #0x34 \n"                    
"	ADD	R0, SP, #0x38 \n"                    
"	BL	sub_FFA37DEC \n"                      
"	CMP	R0, #0 \n"                           
"	MOV	R5, #1 \n"                           
"	BNE	loc_FF91A0E0 \n"                     
"	LDR	R1, [R6, #0x28] \n"                  
"	CMP	R1, #1 \n"                           
"	BNE	loc_FF91A1C8 \n"                     
"	LDR	R1, [R6, #0x4C] \n"                  
"	LDR	R2, [R6, #0x3C] \n"                  
"	CMP	R1, R2 \n"                           
"	BCC	loc_FF91A1C8 \n"                     
"loc_FF91A0E0:\n"
"	CMP	R0, #0x80000001 \n"                  
"	STREQ	R8, [R6, #0x50] \n"                
"	BEQ	loc_FF91A118 \n"                     
"	CMP	R0, #0x80000003 \n"                  
"	STREQ	R5, [R6, #0x50] \n"                
"	BEQ	loc_FF91A118 \n"                     
"	CMP	R0, #0x80000005 \n"                  
"	MOVEQ	R0, #2 \n"                         
"	BEQ	loc_FF91A114 \n"                     
"	CMP	R0, #0x80000007 \n"                  
"	STRNE	R7, [R6, #0x50] \n"                
"	BNE	loc_FF91A118 \n"                     
"	MOV	R0, #3 \n"                           
"loc_FF91A114:\n"
"	STR	R0, [R6, #0x50] \n"                  
"loc_FF91A118:\n"
"	LDR	R0, =0x2BDE4 \n"                     
"	LDR	R0, [R0, #8] \n"                     
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF91A130 \n"                     
"	BL	sub_FF844AAC \n"                      
"	B	loc_FF91A134 \n"                       
"loc_FF91A130:\n"
"	BL	sub_FF919888 \n"                      
"loc_FF91A134:\n"
"	LDR	R0, [R4, #0x1C] \n"                  
"	LDR	R1, [R4, #0x20] \n"                  
"	ADD	R3, SP, #0x3C \n"                    
"	MVN	R2, #1 \n"                           
"	ADD	R7, SP, #0x18 \n"                    
"	STMIA	R7, {R0-R3} \n"                    
"	LDR	R2, [R6, #0x64] \n"                  
"	LDR	R3, [R6, #0x68] \n"                  
"	MOV	R0, #0 \n"                           
"	ADD	R1, SP, #0x40 \n"                    
"	ADD	R7, SP, #8 \n"                       
"	STMIA	R7, {R0-R3} \n"                    
"	MOV	R3, #0 \n"                           
"	MOV	R2, #0x40 \n"                        
"	STRD	R2, [SP] \n"                        
"	LDMIB	R4, {R0,R1} \n"                    
"	LDR	R3, =0x2BDFC \n"                     
"	MOV	R2, R9 \n"                           
"	BL	sub_FF9FBAE0 \n"                      
"	LDR	R0, [R6, #0x10] \n"                  
"	MOV	R1, #0x3E8 \n"                       
"	BL	sub_FF826D94 \n"                      
"	CMP	R0, #9 \n"                           
"	BEQ	loc_FF91A24C \n"                     
"	LDR	R0, [SP, #0x3C] \n"                  
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF91A268 \n"                     
"	MOV	R0, #1 \n"                           
"	BL	sub_FF9FBB88 \n"                      
"	BL	sub_FF9FBBC4 \n"                      
"	MOV	R0, #5 \n"                           
"	STR	R0, [R6, #0x38] \n"                  
"loc_FF91A1B4:\n"
"	ADD	SP, SP, #0x44 \n"                    
"	LDMFD	SP!, {R4-R9,PC} \n"                
"loc_FF91A1BC:\n"
"	BL	sub_FF8745A0 \n"                      
"	MOV	R0, #1 \n"                           
"	B	loc_FF91A308 \n"                       
"loc_FF91A1C8:\n"
"	LDR	R12, [SP, #0x34] \n"                 
"	CMP	R12, #0 \n"                          
"	BEQ	loc_FF91A368 \n"                     
"	STR	R5, [R6, #0x2C] \n"                  
"	LDR	R0, [R6, #0x4C] \n"                  
"	LDR	R8, [R4, #0xC] \n"                   
"	CMP	R0, #0 \n"                           
"	LDRNE	LR, [SP, #0x38] \n"                
"	BNE	loc_FF91A294 \n"                     
"	LDR	R0, [R4, #0x1C] \n"                  
"	LDR	R1, [R4, #0x20] \n"                  
"	ADD	R3, SP, #0x3C \n"                    
"	MVN	R2, #0 \n"                           
"	ADD	R9, SP, #0x18 \n"                    
"	STMIA	R9, {R0-R3} \n"                    
"	LDR	R0, [SP, #0x2C] \n"                  
"	LDR	R2, [R6, #0x64] \n"                  
"	LDR	R3, [R6, #0x68] \n"                  
"	ADD	R1, SP, #0x40 \n"                    
"	ADD	R9, SP, #8 \n"                       
"	STMIA	R9, {R0-R3} \n"                    
"	LDR	R3, [SP, #0x30] \n"                  
"	STR	R12, [SP] \n"                        
"	STR	R3, [SP, #4] \n"                     
"	LDMIB	R4, {R0,R1} \n"                    
"	LDR	R3, [SP, #0x38] \n"                  
"	MOV	R2, R8 \n"                           
"	BL	sub_FF9FBAE0 \n"                      
"	LDR	R0, [R6, #0x10] \n"                  
"	MOV	R1, #0x3E8 \n"                       
"	BL	sub_FF826D94 \n"                      
"	CMP	R0, #9 \n"                           
"	BNE	loc_FF91A25C \n"                     
"loc_FF91A24C:\n"
"	BL	sub_FFA382B8 \n"                      
"	MOV	R0, #0x90000 \n"                     
"	STR	R5, [R6, #0x38] \n"                  
"	B	loc_FF91A1BC \n"                       
"loc_FF91A25C:\n"
"	LDR	R0, [SP, #0x3C] \n"                  
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF91A278 \n"                     
"loc_FF91A268:\n"
"	BL	sub_FFA382B8 \n"                      
"	MOV	R0, #0xA0000 \n"                     
"	STR	R5, [R6, #0x38] \n"                  
"	B	loc_FF91A1BC \n"                       
"loc_FF91A278:\n"
"	MOV	R0, #1 \n"                           
"	BL	sub_FF9FBB88 \n"                      
"	LDR	R0, [SP, #0x40] \n"                  
"	LDR	R1, [SP, #0x38] \n"                  
"	ADD	LR, R1, R0 \n"                       
"	LDR	R1, [SP, #0x34] \n"                  
"	SUB	R12, R1, R0 \n"                      
"loc_FF91A294:\n"
"	LDR	R0, [R4, #0x1C] \n"                  
"	LDR	R2, [R6, #0x48] \n"                  
"	LDR	R1, [R4, #0x20] \n"                  
"	ADD	R3, SP, #0x3C \n"                    
"	ADD	R9, SP, #0x18 \n"                    
"	STMIA	R9, {R0-R3} \n"                    
"	LDR	R0, [SP, #0x2C] \n"                  
"	LDR	R2, [R6, #0x64] \n"                  
"	LDR	R3, [R6, #0x68] \n"                  
"	ADD	R1, SP, #0x40 \n"                    
"	ADD	R9, SP, #8 \n"                       
"	STMIA	R9, {R0-R3} \n"                    
"	LDR	R3, [SP, #0x30] \n"                  
"	STR	R12, [SP] \n"                        
"	STR	R3, [SP, #4] \n"                     
"	LDMIB	R4, {R0,R1} \n"                    
"	MOV	R3, LR \n"                           
"	MOV	R2, R8 \n"                           
"	BL	sub_FF9FBAE0 \n"                      
"	LDR	R0, [R6, #0x10] \n"                  
"	MOV	R1, #0x3E8 \n"                       
"	BL	sub_FF826D94 \n"                      
"	CMP	R0, #9 \n"                           
"	BNE	loc_FF91A310 \n"                     
"	BL	sub_FFA382B8 \n"                      
"	MOV	R0, #0x90000 \n"                     
"	STR	R5, [R6, #0x38] \n"                  
"	BL	sub_FF8745A0 \n"                      
"	MOV	R0, #0 \n"                           
"loc_FF91A308:\n"
"	BL	sub_FF9FBB88 \n"                      
"	B	loc_FF91A1B4 \n"                       
"loc_FF91A310:\n"
"	LDR	R0, [SP, #0x3C] \n"                  
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF91A330 \n"                     
"	BL	sub_FFA382B8 \n"                      
"	MOV	R0, #0xA0000 \n"                     
"	STR	R5, [R6, #0x38] \n"                  
"	BL	sub_FF8745A0 \n"                      
"	B	loc_FF91A1B4 \n"                       
"loc_FF91A330:\n"
"	MOV	R0, #0 \n"                           
"	BL	sub_FF9FBB88 \n"                      
"	LDR	R0, [SP, #0x38] \n"                  
"	LDR	R1, [SP, #0x40] \n"                  
"	BL	sub_FFA38014 \n"                      
"	LDR	R0, [R6, #0x48] \n"                  
"	LDR	R3, =0x5B40 \n"                      
"	ADD	R1, R0, #1 \n"                       
"	STR	R1, [R6, #0x48] \n"                  
"	STR	R3, [SP] \n"                         
"	LDR	R0, [SP, #0x40] \n"                  
"	SUB	R3, R3, #4 \n"                       
"	MOV	R2, #0xF \n"                         
"	BL	sub_FFA361B8 \n"                      
"   LDR     R0, =0x5B40-4\n" // +  //VERIFY_SD780 Is this good
"   BL      set_quality\n" // +  //VERIFY_SD780 Is this good
"loc_FF91A368:\n"
"	LDR	R0, [R6, #0x4C] \n"                  
"	ADD	R0, R0, #1 \n"                       
"	STR	R0, [R6, #0x4C] \n"                  
"	LDR	R1, [R6, #0x74] \n"                  
"	MUL	R0, R1, R0 \n"                       
"	LDR	R1, [R6, #0x70] \n"                  
"	BL	sub_FFACA1A4 \n"                      
"	MOV	R4, R0 \n"                           
"	BL	sub_FFA382F0 \n"                      
"	LDR	R1, [R6, #0x6C] \n"                  
"	CMP	R1, R4 \n"                           
"	BNE	loc_FF91A3A4 \n"                     
"	LDR	R0, [R6, #0x30] \n"                  
"	CMP	R0, #1 \n"                           
"	BNE	loc_FF91A3B8 \n"                     
"loc_FF91A3A4:\n"
"	LDR	R1, [R6, #0x80] \n"                  
"	MOV	R0, R4 \n"                           
"	BLX	R1 \n"                               
"	STR	R4, [R6, #0x6C] \n"                  
"	STR	R7, [R6, #0x30] \n"                  
"loc_FF91A3B8:\n"
"	STR	R7, [R6, #0x2C] \n"                  
"	B	loc_FF91A1B4 \n"                       
 );
}

