#include "conf.h"

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table1[9]={0x2000,0x38D,0x788,0x5800,0x9C5,0x14B8,0x10000,0x1C6A,0x3C45};
long def_table2[9]={0x1CCD,-0x2E1,-0x579,0x4F33,-0x7EB,-0xF0C,0xE666,-0x170A,-0x2BC6};

long table1[9], table2[9];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<9;i++) {table1[i]=(def_table1[i]*a)/b; table2[i]=(def_table2[i]*a)/b;}
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};

void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
                "STMFD   SP!, {R4,R5,LR}\n" 
                "SUB     SP, SP, #4\n"      
                "MOV     R5, SP\n"          
                "MOV     R4, #0\n"          
"loc_FFF26AD4:\n"                           
                "LDR     R3, =0xA2F90\n"    
                "MOV     R2, #0\n"          
                "LDR     R0, [R3]\n"        
                "MOV     R1, R5\n"          
                "BL      sub_FFEBD6E4\n" 
                "LDR     R3, =0xA30B0\n"    
                "LDR     R2, [R3]\n"        
                "CMP     R2, #0\n"          
                "BNE     loc_FFF26B80\n"    
                "LDR     R1, [SP]\n"        
                "LDR     R3, [R1]\n"        
                "SUB     R3, R3, #2\n"      
                "MOV     R0, R1\n"          
                "CMP     R3, #9\n"          
                "LDRLS   PC, [PC,R3,LSL#2]\n" 
                "B       loc_FFF26B84\n"    
                ".long loc_FFF26B44\n"
                ".long loc_FFF26B5C\n"
                ".long loc_FFF26B64\n"
                ".long loc_FFF26B6C\n"
                ".long loc_FFF26B4C\n"
                ".long loc_FFF26B74\n"
                ".long loc_FFF26B54\n"
                ".long loc_FFF26B84\n"
                ".long loc_FFF26B7C\n"
                ".long loc_FFF26B3C\n"
"loc_FFF26B3C:\n"                           
                                        
                "BL      sub_FFF26BF0\n"    
                "B       loc_FFF26B80\n"    
"loc_FFF26B44:\n"                           
                                        
                "BL      sub_FFF26DF8\n"    
                "B       loc_FFF26B80\n"    
"loc_FFF26B4C:\n"                           
                                        
                "BL      sub_FFF27174_my\n"   //----------> 
                "B       loc_FFF26B80\n"    
"loc_FFF26B54:\n"                           
                                        
                "BL      sub_FFF2799C\n"    
                "B       loc_FFF26B80\n"    
"loc_FFF26B5C:\n"                           
                                        
                "BL      sub_FFF27450\n"    
                "B       loc_FFF26B80\n"    
"loc_FFF26B64:\n"                           
                                        
                "BL      sub_FFF27B38\n"    
                "B       loc_FFF26B80\n"    
"loc_FFF26B6C:\n"                           
                                        
                "BL      sub_FFF27D18\n"    
                "B       loc_FFF26B80\n"    
"loc_FFF26B74:\n"                           
                                        
                "BL      sub_FFF27A24\n"    
                "B       loc_FFF26B80\n"    
"loc_FFF26B7C:\n"                           
                                        
                "BL      sub_FFF274A0\n"    
"loc_FFF26B80:\n"                           
                                        
                "LDR     R1, [SP]\n"        
"loc_FFF26B84:\n"                           

                "LDR     R3, =0xA2F94\n"    
                "STR     R4, [R1]\n"        
                "LDR     R0, [R3]\n"        
                "MOV     R2, R4\n"          
                "BL      sub_FFEBDAFC\n" 
                "B       loc_FFF26AD4\n"    
 );
}

void __attribute__((naked,noinline)) sub_FFF27174_my(){
 asm volatile(
                "STMFD   SP!, {R4-R11,LR}\n" 
                "LDR     R5, =0xA30C8\n"    
                "SUB     SP, SP, #0x3C\n"   
                "LDR     R3, [R5]\n"        
                "MOV     R2, #0\n"          
                "CMP     R3, #3\n"          
                "STR     R2, [SP,#0x2C]\n"  
                "MOV     R4, R0\n"          
                "STR     R2, [SP,#0x34]\n"  
                "MOVEQ   R3, #4\n"          
                "STREQ   R3, [R5]\n"        
                "LDR     R3, =0xA3174\n"    
                "MOV     LR, PC\n"          
                "LDR     PC, [R3]\n"        
                "LDR     R2, [R5]\n"        
                "CMP     R2, #4\n"          
                "BNE     loc_FFF27378\n"    
                "ADD     R0, SP, #0x38\n"   
                "ADD     R1, SP, #0x34\n"   
                "ADD     R2, SP, #0x30\n"   
                "ADD     R3, SP, #0x2C\n"   
                "BL      sub_FFF28894\n"    
                "CMP     R0, #0\n"          
                "BNE     loc_FFF271FC\n"    
                "LDR     R3, =0xA30B8\n"    
                "LDR     R2, [R3]\n"        
                "CMP     R2, #1\n"          
                "BNE     loc_FFF27210\n"    
                "LDR     R2, =0xA30F4\n"    
                "LDR     R1, =0xA30CC\n"    
                "LDR     R12, [R2]\n"       
                "LDR     R3, [R1]\n"        
                "CMP     R12, R3\n"         
                "BCC     loc_FFF27210\n"    
"loc_FFF271FC:\n"                           
                "BL      sub_FFF273C8\n"    
                "BL      sub_FFF2795C\n"    
                "MOV     R3, #5\n"          
                "STR     R3, [R5]\n"        
                "B       loc_FFF27378\n"    
"loc_FFF27210:\n"                           
                                        
                "LDR     R9, [SP,#0x34]\n"  
                "CMP     R9, #0\n"          
                "BEQ     loc_FFF272F8\n"    
                "LDR     R7, =0xA3110\n"    
                "LDR     R12, =0xA30FC\n"   
                "LDMIB   R4, {R0-R2}\n"     
                "LDR     R10, [R4,#0x18]\n" 
                "LDR     R6, [R7]\n"        
                "LDR     R7, [R4,#0x14]\n"  
                "LDR     R4, =0xA30BC\n"    
                "LDR     R8, [R12]\n"       
                "ADD     R5, SP, #0x2C\n"   
                "LDMIA   R5, {R5,LR}\n"     
                "MOV     R11, #1\n"         
                "LDR     R3, [SP,#0x38]\n"  
                "ADD     R12, SP, #0x28\n"  
                "STR     R11, [R4]\n"       
                "ADD     R4, SP, #0x24\n"   
                "STMEA   SP, {R9,LR}\n"     
                "STR     R5, [SP,#8]\n"     
                "STR     R12, [SP,#0xC]\n"  
                "STR     R8, [SP,#0x10]\n"  
                "STR     R6, [SP,#0x14]\n"  
                "STR     R7, [SP,#0x18]\n"  
                "STR     R10, [SP,#0x1C]\n" 
                "STR     R4, [SP,#0x20]\n"  
                "BL      sub_FFF2B924\n"    
                "LDR     R3, =0xA2F88\n"    
                "MOV     R1, #0x3E8\n"      
                "LDR     R0, [R3]\n"        
                "BL      sub_FFEBE2AC\n"    
                "CMP     R0, #9\n"          
                "BNE     loc_FFF272A4\n"    
                "BL      sub_FFF29124\n"    
                "LDR     R3, =0xA30C8\n"    
                "LDR     R0, =0xFFF2715C\n" 
                "B       loc_FFF272BC\n"    
"loc_FFF272A4:\n"                           
                "LDR     R4, [SP,#0x24]\n"  
                "CMP     R4, #0\n"          
                "BEQ     loc_FFF272C8\n"    
                "BL      sub_FFF29124\n"    
                "LDR     R3, =0xA30C8\n"    
                "LDR     R0, =0xFFF27168\n" 
"loc_FFF272BC:\n"                           
                "STR     R11, [R3]\n"       
                "BL      sub_FFEE0FAC\n"    
                "B       loc_FFF27378\n"    
"loc_FFF272C8:\n"                           
                "BL      sub_FFF2BAA0\n"    
                "LDR     R0, [SP,#0x38]\n"  
                "LDR     R1, [SP,#0x28]\n"  
                "BL      sub_FFF28D7C\n"    
                "LDR     R12, =0xA30F0\n"   
                "LDR     R3, [R12]\n"       
                "ADD     R3, R3, #1\n"      
                "LDR     R0, [SP,#0x28]\n"  
                "LDR     R1, =0xA3110\n"    
                "MOV     R2, R4\n"          
                "STR     R3, [R12]\n"       
                "BL      sub_FFE9A7F8_my\n"   //--------------> 
"loc_FFF272F8:\n"                           
                "LDR     R4, =0xA30F4\n"    
                "LDR     R2, =0xA311C\n"    
                "LDR     R3, [R4]\n"        
                "LDR     R1, [R2]\n"        
                "LDR     R12, =0xA3118\n"   
                "ADD     R3, R3, #1\n"      
                "MUL     R0, R1, R3\n"      
                "LDR     R1, [R12]\n"       
                "STR     R3, [R4]\n"        
                "BL      sub_FFCCDF80\n"       
                "LDR     R6, =0xA3114\n"    
                "MOV     R4, R0\n"          
                "BL      sub_FFF29160\n"    
                "LDR     R3, [R6]\n"        
                "CMP     R3, R4\n"          
                "BNE     loc_FFF2734C\n"    
                "LDR     R5, =0xA30C0\n"    
                "LDR     R3, [R5]\n"        
                "CMP     R3, #1\n"          
                "BNE     loc_FFF2736C\n"    
                "B       loc_FFF27350\n"    
"loc_FFF2734C:\n"                           
                "LDR     R5, =0xA30C0\n"    
"loc_FFF27350:\n"                           
                "LDR     R2, =0xA3158\n"    
                "MOV     R0, R4\n"          
                "MOV     LR, PC\n"          
                "LDR     PC, [R2]\n"        
                "MOV     R3, #0\n"          
                "STR     R3, [R5]\n"        
                "STR     R4, [R6]\n"        
"loc_FFF2736C:\n"                           
                "LDR     R7, =0xA30BC\n"    
                "MOV     R3, #0\n"          
                "STR     R3, [R7]\n"        
"loc_FFF27378:\n"                           
                                        
                "ADD     SP, SP, #0x3C\n"   
                "LDMFD   SP!, {R4-R11,PC}\n" 

 );
}


void __attribute__((naked,noinline)) sub_FFE9A7F8_my(){
 asm volatile(
                "STMFD   SP!, {R4-R8,LR}\n" 
                "LDR     R12, =0x7EC6C\n"   
                "LDR     R4, [R12]\n"       
                "LDR     R3, =0x7EC74\n"    
                "CMP     R4, #0\n"          
                "MOV     R8, R1\n"          
                "MOV     R7, R0\n"          
                "LDR     R1, [R3]\n"        
                "BEQ     loc_FFE9A830\n"    
                "LDR     R2, =0x7EC78\n"    
                "LDR     R3, [R2]\n"        
                "CMP     R3, #1\n"          
                "BNE     loc_FFE9A844\n"    
                "B       loc_FFE9A834\n"    
"loc_FFE9A830:\n"                           
                "LDR     R2, =0x7EC78\n"    
"loc_FFE9A834:\n"                           
                "MOV     R3, #0\n"          
                "STR     R3, [R2]\n"        
                "STR     R7, [R12]\n"       
                "B       loc_FFE9A8FC\n"    
"loc_FFE9A844:\n"                           
                "LDR     R2, =0x7EC70\n"    
                "LDR     R3, [R2]\n"        
                "LDR     R6, =table1\n"   // + 0xFFE9A6FC
                "ADD     R3, R3, R3,LSL#1\n" 
                "MOV     LR, R3,LSL#2\n"    
                "LDR     R2, [R6,LR]\n"     
                "LDR     R5, =table2\n"   // + 0xFFE9A720
                "RSB     R12, R2, R4\n"     
                "LDR     R3, [R5,LR]\n"     
                "CMP     R12, #0\n"         
                "RSB     R0, R3, R4\n"      
                "BLE     loc_FFE9A8A8\n"    
                "ADD     R3, R6, #4\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R12\n"         
                "ADDGE   R1, R1, #1\n"      
                "BGE     loc_FFE9A89C\n"    
                "ADD     R3, R6, #8\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R12\n"         
                "ADDGE   R1, R1, #2\n"      
                "ADDLT   R1, R1, #3\n"      
"loc_FFE9A89C:\n"                           
          //    "CMP     R1, #0x16\n"     // - 
          //    "MOVGE   R1, #0x16\n"     // - 
                "CMP     R1, #0x1A\n"     // + 
                "MOVGE   R1, #0x1A\n"     // + 

                "B       loc_FFE9A8E0\n"    
"loc_FFE9A8A8:\n"                           
                "CMP     R0, #0\n"          
                "BGE     loc_FFE9A8E0\n"    
                "ADD     R3, R5, #4\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R0\n"          
                "SUBLE   R1, R1, #1\n"      
                "BLE     loc_FFE9A8D8\n"    
                "ADD     R3, R5, #8\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R0\n"          
                "SUBLE   R1, R1, #2\n"      
                "SUBGT   R1, R1, #3\n"      
"loc_FFE9A8D8:\n"                           
                "CMP     R1, #0\n"          
                "MOVLT   R1, #0\n"          
"loc_FFE9A8E0:\n"                           
                                        
                "LDR     R0, =0x7EC74\n"    
                "LDR     R3, [R0]\n"        
                "CMP     R1, R3\n"          
                "LDRNE   R2, =0x7EC78\n"    
                "MOVNE   R3, #1\n"          
                "STRNE   R1, [R0]\n"        
                "STRNE   R3, [R2]\n"        
"loc_FFE9A8FC:\n"                           
                "LDR     R3, =0x7EC74\n"    
                "LDR     R2, =CompressionRateTable\n" 
                "LDR     R1, [R3]\n"        
                "LDR     R0, =0x7EC6C\n"    
                "LDR     R3, [R2,R1,LSL#2]\n" 

                "LDR     R1, =video_mode\n"      // +
                "LDR     R1, [R1]\n"             // +
                "LDR     R1, [R1]\n"             // +
                "CMP     R1, #1\n"               // +
                "LDREQ   R1, =video_quality\n"   // +     
                "LDREQ   R1, [R1]\n"             // +     
                "LDREQ   R3, [R1]\n"             // +     

                "STR     R7, [R0]\n"        
                "STR     R3, [R8]\n"        
                "LDMFD   SP!, {R4-R8,PC}\n" 
 );
}
