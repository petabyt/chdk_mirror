#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)0x48A0;//--->xiefei change

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) capt_seq_task() {
 asm volatile (
                 "STMFD   SP!, {R3-R7,LR}\n"                        
                 "LDR        R7, =0x1217C\n"
                 "LDR        R6, =0x2820\n"
 "loc_FFC4906C:\n"                           
                 "LDR     R0, [R6,#4]\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, SP\n"
                 "BL      sub_FFC16370\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FFC49098\n"
                 "LDR     R1, =0x588\n"
                 "LDR     R0, =0xFFC48C68\n"     
                 "BL      sub_FFC0B284\n"   
                 "BL      sub_FFC0B23C\n"
                 "LDMFD   SP!, {R3-R7,PC}\n"
 "loc_FFC49098:\n"                                               
                 "LDR     R0, [SP]\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x1D\n"
                 "ADDLS   PC, PC, R1,LSL#2\n"
                 "B       loc_FFC49294\n"
 "loc_FFC490AC:\n"                                          
                 "B       loc_FFC49124\n"                 
 "loc_FFC490B0:\n"                                     
                 "B       loc_FFC4912C\n"               
 "loc_FFC490B4:\n"                                        
                 "B       loc_FFC49154\n"             
 "loc_FFC490B8:\n"                                      
                 "B       loc_FFC49168\n"               
 "loc_FFC490BC:\n"                                    
                 "B       loc_FFC49160\n"                
 "loc_FFC490C0:\n"                                       
                 "B       loc_FFC49170\n"              
 "loc_FFC490C4:\n"                                       
                 "B       loc_FFC49178\n"               
 "loc_FFC490C8:\n"                                       
                 "B       loc_FFC49184\n"
 "loc_FFC490CC:\n"                                            
                 "B       loc_FFC491DC\n"                   
 "loc_FFC490D0:\n"                                             
                 "B       loc_FFC49168\n"                     
 "loc_FFC490D4:\n"                                           
                 "B       loc_FFC491E4\n"                   
 "loc_FFC490D8:\n"                                             
                 "B       loc_FFC491F0\n"                    
 "loc_FFC490DC:\n"                                             
                 "B       loc_FFC491F8\n"                  
 "loc_FFC490E0:\n"                                           
                 "B       loc_FFC49200\n"             
 "loc_FFC490E4:\n"                                            
                 "B       loc_FFC49208\n"                  
 "loc_FFC490E8:\n"                               
                 "B       loc_FFC49210\n"                    
 "loc_FFC490EC:\n"                                            
                 "B       loc_FFC49218\n"                    
 "loc_FFC490F0:\n"                                           
                 "B       loc_FFC49220\n"                    
 "loc_FFC490F4:\n"                                           
                " B       loc_FFC4922C\n"                      
 "loc_FFC490F8:\n"                                           
                " B       loc_FFC49234\n"                     
 "loc_FFC490FC:\n"                                           
                 "B       loc_FFC4923C\n"
 "loc_FFC49100:\n"                                           
                 "B       loc_FFC49244\n"                      
 "loc_FFC49104:\n"                                             
                 "B       loc_FFC4924C\n"                        
 "loc_FFC49108:\n"                                             
                 "B       loc_FFC49258\n"                      
 "loc_FFC4910C:\n"                                              
                 "B       loc_FFC49260\n"                      
 "loc_FFC49110:\n"                                              
                 "B       loc_FFC49268\n"                       
 "loc_FFC49114:\n"                                               
                 "B       loc_FFC49270\n"                        
 "loc_FFC49118:\n"                                              
                 "B       loc_FFC49278\n"                       
 "loc_FFC4911C:\n"                                              
                " B       loc_FFC49284\n"                       
 "loc_FFC49120:\n"                                              
                 "B       loc_FFC492A0\n"                      
 "loc_FFC49124:\n"                                                                                            
                 "BL      sub_FFC4993C\n"
                 "BL      shooting_expo_param_override\n"      // +
                 "B       loc_FFC4917C\n"
 "loc_FFC4912C:\n"                                                                                                       
                 "MOV     R0, #0xC\n"
                 "BL      sub_FFC4D434\n"
                 "TST     R0, #1\n"
                 "LDR     R0, [SP]\n"
                 "MOVNE   R1, #1\n"
                 "LDRNE   R2, [R0,#0xC]\n"
                 "MOVNE   R0, #1\n"
                 "BNE     loc_FFC491D4\n"
                // "BL      sub_FFC493BC\n"
                 "BL      sub_FFC4327C_my\n"  //--------->
             //    "BL      capt_seq_hook_raw_here\n"  //+
                 "B       loc_FFC492A0\n"
 "loc_FFC49154:\n"                         								
                 "MOV     R0, #1\n"
                 "BL      sub_FFC49B48\n"
                 "B       loc_FFC492A0\n"
 "loc_FFC49160:\n"                                      
                 "BL      sub_FFC495A0\n"                  
                 "B       loc_FFC492A0\n"                    
 "loc_FFC49168:\n"                                             
                 "BL      sub_FFC4991C\n"                   
                 "B       loc_FFC492A0\n"                  
 "loc_FFC49170:\n"                                             
                 "BL      sub_FFC49924\n"                   
                 "B       loc_FFC492A0\n"                  
 "loc_FFC49178:\n"                                             
                 "BL      sub_FFC49A68\n"                 
 "loc_FFC4917C:\n"                                             
                 "BL      sub_FFC47158\n"                   
                 "B       loc_FFC492A0\n"                  
 "loc_FFC49184:\n"                                             
                 "LDR     R4, [R0,#0xC]\n" 
                 "BL      sub_FFC4992C\n" 
                 "MOV     R0, R4\n" 
                 "BL      sub_FFCFB4E8\n" 
                 "TST     R0, #1\n" 
                 "MOV     R5, R0\n" 
                 "BNE     loc_FFC491C4\n" 
                 "BL      sub_FFC5958C\n" 
                 "STR     R0, [R4,#0x18]\n" 
                 "MOV     R0, R4\n" 
                 "BL      sub_FFCFC384\n" 
                 "MOV     R0, R4\n" 
                 "BL      sub_FFCFC758\n" 
                 "MOV     R5, R0\n" 
                 "LDR     R0, [R4,#0x18]\n" 
                 "BL      sub_FFC597A0\n" 
 "loc_FFC491C4:\n"                                                      
                 "BL      sub_FFC4991C\n"                              
                 "MOV     R2, R4 \n"                                   
                 "MOV     R1, #9 \n"                                  
                 "MOV     R0, R5  \n"                                
 "loc_FFC491D4:\n"                                                     
                 "BL      sub_FFC475A0\n"                         
                 "B       loc_FFC492A0\n"                          
 "loc_FFC491DC:\n"                                                     
                 "BL      sub_FFC49AC8\n" 
                 "B       loc_FFC4917C\n" 
 "loc_FFC491E4:\n"                   																
                 "LDR     R0, [R7,#0x4C]\n" 
                 "BL      sub_FFC49E58\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC491F0:\n"                        																	
                 "BL      sub_FFC4A100\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC491F8:\n"                           																			
                 "BL      sub_FFC4A194\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49200:\n"                         													
                 "BL      sub_FFCFB708\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49208:\n"                      												
                 "BL      sub_FFCFB8E8\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49210:\n"                        																		
                 "BL      sub_FFCFB978\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49218:\n"                            																	
                 "BL      sub_FFCFBA20\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49220:\n"                            						
                 "MOV     R0, #0\n" 
                 "BL      sub_FFCFBBDC\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC4922C:\n"                          														
                 "BL      sub_FFCFBD14\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49234:\n"                                                        
                 "BL      sub_FFCFBDA4\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC4923C:\n"                                                   
                 "BL      sub_FFCFBE64\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49244:\n"                          
                 "BL      sub_FFC49CB0\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC4924C:\n"                                                         
                 "BL      sub_FFC49CDC\n" 
                 "BL      sub_FFC14634\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49258:\n"                      											
                 "BL      sub_FFCFBADC\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49260:\n"                            									
                 "BL      sub_FFCFBB20\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49268:\n"                                                    
                 "BL      sub_FFC4BCA0\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49270:\n"                                              
                 "BL      sub_FFC4BCFC\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49278:\n"                                              
                 "BL      sub_FFC4BD58\n" 
                 "BL      sub_FFC4BD18\n" 
                 "B       loc_FFC492A0\n" 
"loc_FFC49284:\n"                                         
                 "LDRH    R0, [R7,#0x90]\n" 
                 "CMP     R0, #4\n" 
                 "BLNE    sub_FFC4BFC4\n" 
                 "B       loc_FFC492A0\n" 
 "loc_FFC49294:\n"                            
                 "LDR     R1, =0x6C9\n" 
                 "LDR     R0, =0xFFC48C68\n" 
                 "BL      sub_FFC0B284\n" 
 "loc_FFC492A0:\n"                                              
                 "LDR     R0, [SP]\n" 
                 "LDR     R1, [R0,#4]\n" 
                 "LDR     R0, [R6]\n" 
                 "BL      sub_FFC514E4\n" 
                 "LDR     R4, [SP]\n" 
                 "LDR     R0, [R4,#8]\n" 
                 "CMP     R0, #0\n" 
                 "LDREQ   R1, =0x12B\n" 
              //   "ADREQ   R0, aSsshoottask_c\n"
                 	"LDREQ    R0,=0xFFC48C68\n"
                 "BLEQ    sub_FFC0B284\n" 
                 "MOV     R0, #0\n" 
                 "STR     R0, [R4,#8]\n" 
                 "B       loc_FFC4906C\n" 

 );
} 



void __attribute__((naked,noinline)) sub_FFC4327C_my(){ 
 asm volatile(
                 "STMFD   SP!, {R3-R5,LR}\n"
                 "LDR     R4, [R0,#0xC]\n"
                 "LDR     R0, [R4,#8]\n"
                 "ORR     R0, R0, #1\n"
                 "STR     R0, [R4,#8]\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC450E0\n"
                 "BL      sub_FFC4992C\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FFC49C64\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FFCFB158\n"
                 "CMP     R0, #0\n"
                 "MOV     R0, R4\n"
                 "BEQ     loc_FFC49414\n"
                 "BL      sub_FFCFB1E4\n"
                 "TST     R0, #1\n"
                 "MOVNE   R2, R4\n"
                 "LDMNEFD SP!, {R3-R5,LR}\n"
                 "MOVNE   R1, #1\n"
                 "BNE     sub_FFC475A0\n"
                 "B       loc_FFC49418\n"
 "loc_FFC49414:\n"                                                
                 "BL      sub_FFCFB1A8\n"
 "loc_FFC49418:\n"                                            
                 "MOV     R0, #0\n"
                 "STR     R0, [SP]\n"
                 "LDR     R0, =0x1217C\n"
                 "MOV     R2, #2\n"
                 "LDRH    R0, [R0,#0x8E]\n"
                 "MOV     R1, SP\n"
                 "CMP     R0, #3\n"
                 "LDRNE   R0, [R4,#0xC]\n"
                 "CMPNE   R0, #1\n"
                 "MOVHI   R0, #1\n"
                 "STRHI   R0, [SP]\n"
                 "LDR     R0, =0x123\n"
                 "BL      sub_FFC592F8\n"
                 "BL      sub_FFD1CF9C\n"
                 "BL      sub_FFC5958C\n"
                 "STR     R0, [R4,#0x18]\n"
                 "MOV     R0, R4\n"               
                 "BL      sub_FFCFC384\n"
                 "BL      sub_FFCFCEC0\n"
                 "MOV     R0, R4\n"
                // "BL      sub_FFCFC44C\n"
                  "BL      sub_FFCE97F4_my\n"             //---------->
			     "MOV     R5, R0\n"

                 "BL      capt_seq_hook_raw_here\n"      // +

                 "BL      sub_FFC4BCFC\n"
                 "BL      sub_FFC4BD44\n"
                 "BL      sub_FFC4BD84\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FFC475A0\n"
                 "BL      sub_FFCFC6FC\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R0, [R4,#8]\n"
                 "ORRNE   R0, R0, #0x2000\n"
                 "STRNE   R0, [R4,#8]\n"
                 "LDMFD   SP!, {R3-R5,PC}\n"
 );
}



void __attribute__((naked,noinline)) sub_FFCE97F4_my(){ // 
 asm volatile(
                 "STMFD   SP!, {R0-R8,LR}\n"
                 "MOV     R4, R0\n"
                 "BL      sub_FFCFD02C\n"
                 "MOV     R1, #0xFFFFFFFF\n"
                 "LDR    R1,=0xFFFFFFFF\n"
                 "BL      sub_FFC51518\n"
                 "LDR     R5, =0x5AD8\n"
                 "LDR     R0, [R5,#0xC]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFCFC49C\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FFC16BB8\n"
                 "STR     R0, [R5,#0xC]\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =0xFFCFBF54\n"
              //   "ADR     R0, aShuttersoundta\n"     
                   "LDR     R0,=0xFFCFC6C4\n"                                          
                 "MOV     R2, #0x400\n"
                 "MOV     R1, #0x17\n"
                 "BL      sub_FFC16B84\n"
 "loc_FFCFC49C:\n"                                                                                 
                 "MOV     R2, #4\n"
                 "ADD     R1, SP, #8\n"
                 "MOV     R0, #0x8A\n"
                 "BL      sub_FFC593FC\n"
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x3A7\n"
             //    "ADRNE   R0, aSscaptureseq_c\n"  
             		"LDRNE    R0,=0xFFCFC1C0\n"                              
                 "BLNE    sub_FFC0B284\n"
                 "LDR     R7, =0x12238\n"
                 "LDR     R8, =0x1217C\n"
                 "LDRSH   R1, [R7,#0xE]\n"
                 "LDR     R0, [R8,#0x84]\n"
                 "BL      sub_FFCC34D8\n"
                 "BL      sub_FFC32BD0\n"
                 "LDR     R3, =0x5AE0\n"
                 "STRH    R0, [R4,#0x9C]\n"
                 "SUB     R2, R3, #4\n"
                 "STRD    R2, [SP]\n"
                 "MOV     R1, R0\n"
                 "LDRH    R0, [R8,#0x54]\n"
                 "LDRSH   R2, [R7,#0xC]\n"
                 "SUB     R3, R3, #8\n"
                 "BL      sub_FFCFD610\n"
                   "BL      wait_until_remote_button_is_released\n"     // +
                 "BL      capt_seq_hook_set_nr\n"                     // +
                  "B                sub_FFCFC4F8\n"                     // continue function in firmware
 );
}

