#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    uint32_t inst;
    uint32_t mask;
    uint32_t ignore;
    char cmd[8];
    int is_adr;
} Instr;

/*
Cond	0 C	I	Opcode				S	Rn	Rd	Operand2		
Cond	0 0 0 0 0 0					A	S	Rd	Rn	Rs	1 0 0 1	Rm
Cond	0 0 0 0 1				U	A	S	RdHi	RdLo	Rs	1 0 0 1	Rm
Cond	0 0 0 1 0				B			Rn	Rd	0 0 0 0	1 0 0 1	Rm
Cond	0 1	I	P	U	B	W	L	Rn	Rd	Offset		
Cond	1 0 0		P	U	S	W	L	Rn	Register List			
Cond	0 0 0		P	U	1	W	L	Rn	Rd	Offsetl	1 S H 1	Offset2
Cond	0 0 0		P	U	0	W	L	Rn	Rd	0 0 0 0	1 S H 1	Rm
Cond	1 0 1		L	Offset								
Cond	0 0 0 1			0 0 1 0				1111	1111	1111	0 0 0 1	Rn
Cond	1 1 0		P	U	N	W	L	Rn	CRd	CPNum	Offset	
Cond	1 1 1 0			Opl				CRn	CRd	CPNum	Op2  0	CRm
Cond	1 1 1 0			Opl			L	CRn	Rd	CPNum	Op2  1	CRm
Cond	1 1 1 1			SWI Number								
*/

/* ARM instructions */ /*
                       {0xe1a00000, 0xffffffff, "nop"},
                       {0x012FFF10, 0x0ffffff0, "bx%c\t%0-3r"},
                       {0x00000090, 0x0fe000f0, "mul%c%20's\t%16-19r, %0-3r, %8-11r"},
                       {0x00200090, 0x0fe000f0, "mla%c%20's\t%16-19r, %0-3r, %8-11r, %12-15r"},
                       {0x01000090, 0x0fb00ff0, "swp%c%22'b\t%12-15r, %0-3r, [%16-19r]"},
                       {0x00800090, 0x0fa000f0, "%22?sumull%c%20's\t%12-15r, %16-19r, %0-3r, %8-11r"},
                       {0x00a00090, 0x0fa000f0, "%22?sumlal%c%20's\t%12-15r, %16-19r, %0-3r, %8-11r"},
                       {0x00000090, 0x0e100090, "str%c%6's%h\t%12-15r, %s"},
                       {0x00100090, 0x0e100090, "ldr%c%6's%h\t%12-15r, %s"},
                       {0x00000000, 0x0de00000, "and%c%20's\t%12-15r, %16-19r, %o"},
                       {0x00200000, 0x0de00000, "eor%c%20's\t%12-15r, %16-19r, %o"},
                       {0x00400000, 0x0de00000, "sub%c%20's\t%12-15r, %16-19r, %o"},
                       {0x00600000, 0x0de00000, "rsb%c%20's\t%12-15r, %16-19r, %o"},
                       {0x00800000, 0x0de00000, "add%c%20's\t%12-15r, %16-19r, %o"},
                       {0x00a00000, 0x0de00000, "adc%c%20's\t%12-15r, %16-19r, %o"},
                       {0x00c00000, 0x0de00000, "sbc%c%20's\t%12-15r, %16-19r, %o"},
                       {0x00e00000, 0x0de00000, "rsc%c%20's\t%12-15r, %16-19r, %o"},
                       {0x0120f000, 0x0db6f000, "msr%c\t%22?scpsr%C, %o"},
                       {0x010f0000, 0x0fbf0fff, "mrs%c\t%12-15r, %22?scpsr"},
                       {0x01000000, 0x0de00000, "tst%c%p\t%16-19r, %o"},
                       {0x01200000, 0x0de00000, "teq%c%p\t%16-19r, %o"},
                       {0x01400000, 0x0de00000, "cmp%c%p\t%16-19r, %o"},
                       {0x01600000, 0x0de00000, "cmn%c%p\t%16-19r, %o"},
                       {0x01800000, 0x0de00000, "orr%c%20's\t%12-15r, %16-19r, %o"},
                       {0x01a00000, 0x0de00000, "mov%c%20's\t%12-15r, %o"},
                       {0x01c00000, 0x0de00000, "bic%c%20's\t%12-15r, %16-19r, %o"},
                       {0x01e00000, 0x0de00000, "mvn%c%20's\t%12-15r, %o"},
                       {0x04000000, 0x0e100000, "str%c%22'b%t\t%12-15r, %a"},
                       {0x06000000, 0x0e100ff0, "str%c%22'b%t\t%12-15r, %a"},
                       {0x04000000, 0x0c100010, "str%c%22'b%t\t%12-15r, %a"},
                       {0x06000010, 0x0e000010, "undefined"},
                       {0x04100000, 0x0c100000, "ldr%c%22'b%t\t%12-15r, %a"},
                       {0x08000000, 0x0e100000, "stm%c%23?id%24?ba\t%16-19r%21'!, %m%22'^"},
                       {0x08100000, 0x0e100000, "ldm%c%23?id%24?ba\t%16-19r%21'!, %m%22'^"},
                       {0x0a000000, 0x0e000000, "b%24'l%c\t%b"},
                       {0x0f000000, 0x0f000000, "swi%c\t%0-23x"},
                       */

/*
Instr instrs[] = {
//    {0x00000000 , 0x00000000, 0x00000000 },	// adc
{0x00800000 , 0x0df00000, 0x02000000 },	// add
{0x00000000 , 0x0de00000, 0x02000000 },	// and
{0x0a000000 , 0x0e000000, 0x00ffffff },	// b, bl
{0x01c00000 , 0x0de00000, 0x02000000 },	// bic
//    {0x00000000 , 0x00000000, 0x00000000 },	// bkpt
//    {0x00000000 , 0x00000000, 0x00000000 },	// blx
//    {0x00000000 , 0x00000000, 0x00000000 },	// blx
//    {0x00000000 , 0x00000000, 0x00000000 },	// bx
//    {0x00000000 , 0x00000000, 0x00000000 },	// cdp
//    {0x00000000 , 0x00000000, 0x00000000 },	// clz
{0x01700000 , 0x0df00000, 0x02000000 },	// cmn
{0x01500000 , 0x0df00000, 0x02000000 },	// cmp
//    {0x00000000 , 0x00000000, 0x00000000 },	// eor
//    {0x00000000 , 0x00000000, 0x00000000 },	// ldc
//    {0x00000000 , 0x00000000, 0x00000000 },	// ldm
//    {0x00000000 , 0x00000000, 0x00000000 },	// ldm
//    {0x00000000 , 0x00000000, 0x00000000 },	// ldm
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldr
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrb
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrbt
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrh
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrsb
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrsh
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrt
//    {0x00000000 , 0x00000000, 0x00000000 },	// mcr
//    {0x00000000 , 0x00000000, 0x00000000 },	// mla
{0x01a00000 , 0x0de00000, 0x02000000 },	// mov
//    {0x00000000 , 0x00000000, 0x00000000 },	// mrc
//    {0x00000000 , 0x00000000, 0x00000000 },	// mrs
//    {0x00000000 , 0x00000000, 0x00000000 },	// msr
//    {0x00000000 , 0x00000000, 0x00000000 },	// mul
//    {0x00000000 , 0x00000000, 0x00000000 },	// mvn
//    {0x00000000 , 0x00000000, 0x00000000 },	// orr
//    {0x00000000 , 0x00000000, 0x00000000 },	// rsb
//    {0x00000000 , 0x00000000, 0x00000000 },	// rsc
//    {0x00000000 , 0x00000000, 0x00000000 },	// scb
//    {0x00000000 , 0x00000000, 0x00000000 },	// smlal
//    {0x00000000 , 0x00000000, 0x00000000 },	// smull
//    {0x00000000 , 0x00000000, 0x00000000 },	// src
//    {0x00000000 , 0x00000000, 0x00000000 },	// stm
//    {0x00000000 , 0x00000000, 0x00000000 },	// stm
/// {0x00000000 , 0x00000000, 0x00000000 },	// str
/// {0x00000000 , 0x00000000, 0x00000000 },	// strb
/// {0x00000000 , 0x00000000, 0x00000000 },	// strbt
/// {0x00000000 , 0x00000000, 0x00000000 },	// strh
/// {0x00000000 , 0x00000000, 0x00000000 },	// strt
{0x00400000 , 0x0de00000, 0x02000000 },	// sub
//    {0x00000000 , 0x00000000, 0x00000000 },	// swi
//    {0x00000000 , 0x00000000, 0x00000000 },	// swp
//    {0x00000000 , 0x00000000, 0x00000000 },	// swpb
//    {0x00000000 , 0x00000000, 0x00000000 },	// teq
{0x01100000 , 0x0df00000, 0x02000000 },	// tst
//    {0x00000000 , 0x00000000, 0x00000000 },	// umlal
//    {0x00000000 , 0x00000000, 0x00000000 },	// umull

{ 0, 0, 0 }
};
// */

/*
Instr instrs[] = {
{0x00a00000 , 0x0de00000, 0x02000fff, "adc" },
{0x00800000 , 0x0de00000, 0x02000fff, "add" },
{0x00000000 , 0x0de00000, 0x02000fff, "and" },
{0x0a000000 , 0x0e000000, 0x00ffffff, "b, bl" },
{0x01c00000 , 0x0de00000, 0x02000fff, "bic" },
{0xe1200070 , 0xfff000f0, 0x000fff0f, "bkpt" },
{0xfa000000 , 0xfe000000, 0x00ffffff, "blx" },
{0x01200030 , 0x0ff000f0, 0x000fff00, "blx" },
{0x01200010 , 0x0ff000f0, 0x000fff00, "bx" },
{0x0e000000 , 0x0f000010, 0x00000000, "cdp" },
{0x01600010 , 0x0ff000f0, 0x000f0f00, "clz" },
{0x01700000 , 0x0df00000, 0x0200ffff, "cmn" },
{0x01500000 , 0x0df00000, 0x0200ffff, "cmp" },
{0x00200000 , 0x0de00000, 0x02000fff, "eor" },
{0x0c100000 , 0x0e100000, 0x000000ff, "ldc" },
{0x08100000 , 0x0e500000, 0x00000000, "ldm" },
{0x08500000 , 0x0e708000, 0x00000000, "ldm" },
{0x08508000 , 0x0e508000, 0x00000000, "ldm" },
{0x04100000 , 0x0c500000, 0x02000fff, "ldr" },
{0x04500000 , 0x0c500000, 0x02000fff, "ldrb" },
{0x04700000 , 0x0f700000, 0x02000fff, "ldrbt" },
{0x001000b0 , 0x0e1000f0, 0x00400f0f, "ldrh" },
{0x001000d0 , 0x0e1000f0, 0x00400f0f, "ldrsb" },
{0x001000f0 , 0x0e1000f0, 0x00400f0f, "ldrsh" },
{0x04300000 , 0x0d700000, 0x02000fff, "ldrt" },
{0x0e000010 , 0x0f100010, 0x00000000, "mcr" },
{0x00200090 , 0x0fe000f0, 0x00000000, "mla" },
{0x01a00000 , 0x0de00000, 0x020f0fff, "mov" },
{0x0e100010 , 0x0f100010, 0x00000000, "mrc" },
{0x01000000 , 0x0fb00000, 0x000f0fff, "mrs" },
{0x03200000 , 0x0fb00000, 0x0000f000, "msr" },
{0x01200000 , 0x0fb000f0, 0x0000ff00, "msr" },
{0x00000090 , 0x0fe000f0, 0x0000f000, "mul" },
{0x01e00000 , 0x0de00000, 0x020f0fff, "mvn" },
{0x01800000 , 0x0de00000, 0x02000fff, "orr" },
{0x00600000 , 0x0de00000, 0x02000fff, "rsb" },
{0x00e00000 , 0x0de00000, 0x02000fff, "rsc" },
{0x00c00000 , 0x0de00000, 0x02000fff, "sbc" },
{0x00e00090 , 0x0fe000f0, 0x00000000, "smlal" },
{0x00c00090 , 0x0fe000f0, 0x00000000, "smull" },
{0x0c000000 , 0x0e100000, 0x000000ff, "stc" },
{0x08000000 , 0x0e500000, 0x00000000, "stm" },
{0x08400000 , 0x0e700000, 0x00000000, "stm" },
{0x04000000 , 0x0c500000, 0x02000fff, "str" },
{0x04400000 , 0x0c500000, 0x02000fff, "strb" },
{0x04600000 , 0x0d700000, 0x02000fff, "strbt" },
{0x000000b0 , 0x0e1000f0, 0x00400f0f, "strh" },
{0x04200000 , 0x0d700000, 0x02000fff, "strt" },
{0x00400000 , 0x0de00000, 0x02000fff, "sub" },
{0x0f000000 , 0x0f000000, 0x00000000, "swi" },
{0x01000090 , 0x0ff000f0, 0x00000f00, "swp" },
{0x01400090 , 0x0ff000f0, 0x00000f00, "swpb" },
{0x01300000 , 0x0df00000, 0x0200ffff, "teq" },
{0x01100000 , 0x0df00000, 0x0200ffff, "tst" },
{0x00a00090 , 0x0fe000f0, 0x00000000, "umlal" },
{0x00800090 , 0x0fe000f0, 0x00000000, "umull" },
{ 0, 0, 0 , "" }
};
*/

//*
Instr instrs[] = {
    //  {0x00a00000 , 0x0de00000, 0x02000000, "adc" },
    {0x008f0000 , 0x0def0000, 0x0ff00fff, "add", 1 },
    {0x00800000 , 0x0de00000, 0x020f0fff, "add", 0 },
    {0x02000000 , 0x0fe00000, 0x00000fff, "and", 0 },
    {0x0a000000 , 0x0e000000, 0xf0ffffff, "b, bl", 0 },
    {0x01c00000 , 0x0de00000, 0x02000fff, "bic", 0 },
    //  {0xe1200070 , 0xfff000f0, 0x00000000, "bkpt" },
    //  {0xfa000000 , 0xfe000000, 0x00ffffff, "blx" },
    //  {0x01200030 , 0x0ff000f0, 0x00000000, "blx" },
    //  {0x01200010 , 0x0ff000f0, 0x00000000, "bx" },
    //  {0x0e000000 , 0x0f000010, 0x00000000, "cdp" },
    //  {0x01600010 , 0x0ff000f0, 0x00000000, "clz" },
    {0x01700000 , 0x0df00000, 0x02000000, "cmn", 0 },
    {0x01500000 , 0x0df00000, 0x02000fff, "cmp", 0 },
    //  {0x00200000 , 0x0de00000, 0x02000000, "eor" },
    //  {0x0c100000 , 0x0e100000, 0x00000000, "ldc" },
    {0x08100000 , 0x0e500000, 0x0000ffff, "ldm", 0 },
    //  {0x08500000 , 0x0e708000, 0x00000000, "ldm" },
    //  {0x08508000 , 0x0e508000, 0x00000000, "ldm" },
    {0x041f0000 , 0x0c5f0000, 0x0ff00fff, "ldr", 1 },
    {0x04100000 , 0x0c500000, 0x02000fff, "ldr", 0 },
    //  {0x04500000 , 0x0c500000, 0x02000000, "ldrb" },
    //  {0x04700000 , 0x0f700000, 0x02000000, "ldrbt" },
    //  {0x001000b0 , 0x0e1000f0, 0x00400000, "ldrh" },
    //  {0x001000d0 , 0x0e1000f0, 0x00400000, "ldrsb" },
    //  {0x001000f0 , 0x0e1000f0, 0x00400000, "ldrsh" },
    //  {0x04300000 , 0x0d700000, 0x02000000, "ldrt" },
    //  {0x0e000010 , 0x0f100010, 0x00000000, "mcr" },
    //  {0x00200090 , 0x0fe000f0, 0x00000000, "mla" },
    {0x01af0000 , 0x0def0000, 0x0ff00fff, "mov", 1 },
    {0x01a00000 , 0x0de00000, 0x02000fff, "mov", 0 },
    //  {0x0e100010 , 0x0f100010, 0x00000000, "mrc" },
    //  {0x01000000 , 0x0fb00000, 0x00000000, "mrs" },
    //  {0x03200000 , 0x0fb00000, 0x00000000, "msr" },
    //  {0x01200000 , 0x0fb000f0, 0x00000000, "msr" },
    {0x00000090 , 0x0fe000f0, 0x00000000, "mul", 0 },
    {0x01ef0000 , 0x0def0000, 0x0ff00fff, "mvn", 1 },
    {0x01e00000 , 0x0de00000, 0x02000fff, "mvn", 0 },
    //  {0x01800000 , 0x0de00000, 0x02000000, "orr" },
    {0x00600000 , 0x0de00000, 0x02000000, "rsb", 0 },
    {0x00e00000 , 0x0de00000, 0x02000000, "rsc", 0 },
    //  {0x00c00000 , 0x0de00000, 0x02000000, "sbc" },
    //  {0x00e00090 , 0x0fe000f0, 0x00000000, "smlal" },
    //  {0x00c00090 , 0x0fe000f0, 0x00000000, "smull" },
    //  {0x0c000000 , 0x0e100000, 0x00000000, "stc" },
    {0x08000000 , 0x0e500000, 0x0000ffff, "stm", 0 },
    //  {0x08400000 , 0x0e700000, 0x00000000, "stm" },
    {0x04000000 , 0x0c500000, 0x02000fff, "str", 0 },
    {0x04400000 , 0x0c500000, 0x02000fff, "strb", 0 },
    //  {0x04600000 , 0x0d700000, 0x02000000, "strbt" },
    //  {0x000000b0 , 0x0e1000f0, 0x00400000, "strh" },
    //  {0x04200000 , 0x0d700000, 0x02000000, "strt" },
    {0x004f0000 , 0x0def0000, 0x0ff00fff, "sub", 1 },
    {0x00400000 , 0x0de00000, 0x02000fff, "sub", 0 },
    //  {0x0f000000 , 0x0f000000, 0x00000000, "swi" },
    //  {0x01000090 , 0x0ff000f0, 0x00000000, "swp" },
    //  {0x01400090 , 0x0ff000f0, 0x00000000, "swpb" },
    //  {0x01300000 , 0x0df00000, 0x02000000, "teq" },
    {0x01100000 , 0x0df00000, 0x02000000, "tst", 0 },
    //  {0x00a00090 , 0x0fe000f0, 0x00000000, "umlal" },
    //  {0x00800090 , 0x0fe000f0, 0x00000000, "umull" },
    { 0, 0, 0 , "" }
};
// */

void usage()
{
    printf("gensig <primary> <base> <proc_name> <proc_vaddr> <proc_size>\n");
    exit(1);
}

int bits (uint32_t v) {
    int i, res=0;

    for (i=0; i<32; ++i)
        res+=(v>>i)&1;

    return res;
}

uint32_t buf[1024];

void dump_sig(uint32_t pos, int size, FILE *f)
{
    int i, j;
    char tbuf[1024];
    int finish = 0;
    int wcount = 0;

    int offset_mask = 0;
    if (size < 0)
    {
        size = -size;
        offset_mask = 0xfff;
    }

    fseek(f, pos, SEEK_SET);
    i = fread(buf, 4, size, f);

    for (i=0;i<size;++i){
        tbuf[0]=0;
        for (j=0;instrs[j].inst | instrs[j].mask;j++){
            if ((buf[i] & instrs[j].mask) == instrs[j].inst){
                uint32_t ignore = ~instrs[j].ignore | offset_mask;
                //if (!instrs[j].is_adr)
				{
                    if (!tbuf[0]) 
                        sprintf(tbuf, "\t{ %3d, 0x%08x, 0x%08x }, //", i, buf[i] & ignore, ignore);
                    sprintf(tbuf+strlen(tbuf), " %s:%d:0x%08X", instrs[j].cmd, bits(instrs[j].mask), buf[i]);
                    wcount++;
                    if ((buf[i] == 0xe1a0f00e) /* "mov pc,lr" aka "ret" */
                        && (size*100/wcount) > 75){
                            sprintf(tbuf+strlen(tbuf), "\t/* RET found, stopping... */");
                            finish = 1;
                    }
                }
                break;
       	    }
       	}
        if (tbuf[0]) 
            printf("%s\n", tbuf);
        if (finish)
            break;
    }
    printf("\t/* %d/%d */\n",wcount, size);
}

int main(int argc, char **argv)
{
    char *proc_name;
    FILE *f;
    uint32_t base;
    uint32_t pos, lnk_pos;
    uint32_t size, lnk_size;
//    int i,j;
//    int wcount;
//    char tbuf[1024];
//    int finish;

    if (argc != 8)
        usage();

    f = fopen(argv[1], "r+b");

    if (f == NULL)
        usage();

    base = strtoul(argv[2], NULL, 0);
    proc_name = argv[3];
    pos = strtoul(argv[4], NULL, 0) - base;
    size = strtoul(argv[5], NULL, 0);
    lnk_pos = strtoul(argv[6], NULL, 0);
    if (lnk_pos != 0) lnk_pos -= base;
    lnk_size = strtoul(argv[7], NULL, 0);
//    wcount = 0;

    printf("static FuncSig func_sig_%s[] = {\n",proc_name);

    dump_sig(pos,size,f);

    if (lnk_pos != 0)
    {
        printf("\t{ -1, %d, -2 },\n",size-1);
        dump_sig(lnk_pos,lnk_size,f);
    }
    printf("\t{ -1, -1, -1 },\n");
    printf("};\n\n");

    fclose(f);

    return 0;
}

