#include "lolevel.h"
#include "platform.h"
#include "core.h"

// enable fix for Canon PTPIP data->recv_data not correctly handling multiple calls
#define PTPIP_RECV_DATA_FIX 1

const char * const new_sa = &_end;

// Forward declarations

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_RotaryEncoder();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_TricInitTask();
extern void task_PtpipController();

extern void handle_jogdial();

/*----------------------------------------------------------------------
    spytask
-----------------------------------------------------------------------*/
void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    (void)ua; (void)ub; (void)uc; (void)ud; (void)ue; (void)uf;
    core_spytask();
}

/*----------------------------------------------------------------------
    CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask()
{
    _CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);
}

/*
//unsigned rbval=0;
void task_blinker()
{
#if 0
    unsigned v=*(volatile unsigned *)(0x9808);
    unsigned pat=0;
    if(v & 0x80000){
        pat |=1;
    }
    if(v & 0x100000){
        pat |=2;
    }
    if(v & 0x200000){
        pat |=4;
    }
    if(v & 0x400000){
        pat |=8;
    }
    if(v & 0x800000){
        pat |=0x10;
    }
    while(1) {
        int i;
        for(i=0;i<5;i++) {
            *(volatile int*)0xd20b0994 = 0x4d0002;
            if((pat >> i) & 1) {
                msleep(1000);
            } else {
                msleep(250);
            }
            *(volatile int*)0xd20b0994 = 0x4c0003;
            msleep(500);
        }
        msleep(5000);
    }
#endif
#if 0
    int delay=1000;
    if(rbval == 0x12345678) {
        delay=100;
    }
    while(1) {
        *(volatile int*)0xd20b0994 = 0x4d0002;
        msleep(delay);
        *(volatile int*)0xd20b0994 = 0x4c0003;
        msleep(delay);
    }
#endif
    while(1) {
        *(volatile int*)0xd20b0994 = 0x4d0002;
        msleep(250);
        *(volatile int*)0xd20b0994 = 0x4c0003;
        msleep(250);
    }
}

void CreateTask_blinker()
{
    _CreateTask("blinker", 0x19, 0x200, task_blinker, 0);
}
*/

/*----------------------------------------------------------------------
    boot()

    Main entry point for the CHDK code
-----------------------------------------------------------------------*/

/*************************************************************/
//  -f=chdk -s=0xfc02000d -c=43
void __attribute__((naked,noinline)) boot() {
    asm volatile ( // 0xfc02000c
"    movw    r0, #0x4000\n"
"    movt    r0, #0\n"
"    mov     sp, r0\n"
"    bl      sub_fc02007e\n"
"    ldr     r2, =0xc0242010\n"
"    ldr     r1, [r2]\n"
"    orr     r1, r1, #1\n"
"    str     r1, [r2]\n"
"    ldr     r0, =0xfcdcd810\n" // code copied from ROM
"    ldr     r1, =0x010e1000\n" // to RAM
"    ldr     r3, =0x010fc278\n"
"loc_fc02002a:\n"
"    cmp     r1, r3\n"
"    itt     lo\n"
"    ldrlo   r2, [r0], #4\n"
"    strlo   r2, [r1], #4\n"
"    blo     loc_fc02002a\n"
"    ldr     r0, =0x010e1000\n"
"    ldr     r1, =0x0001b278\n"
"    bl      sub_fc0db23e\n"    // cache stuff for RAM code
"    ldr     r0, =0xfcde8a88\n" // code copied from ROM
"    ldr     r1, =0xbfe10800\n" // to TCM
"    ldr     r3, =0xbfe1633d\n"
"loc_fc020046:\n"
"    cmp     r1, r3\n"
"    itt     lo\n"
"    ldrlo   r2, [r0], #4\n"
"    strlo   r2, [r1], #4\n"
"    blo     loc_fc020046\n"
// Install CreateTask patch
// use half words in case source or destination not word aligned
// CreateTask is in ROM :(, use CreateTask_Low (bfe10b84) instead
        "adr     r0, patch_CreateTask\n"    // src: Patch data
        "ldr     r1, =hook_CreateTask_low\n"    // dest: Address to patch (hook_ has thumb bit off)
        "add     r2, r0, #8\n" // two words - note may clobber more than 2 instructions!
"task_hook_loop:\n"
        "ldrh   r3, [r0],#2\n"
        "strh   r3, [r1],#2\n"
        "cmp    r0,r2\n"
        "blo    task_hook_loop\n"
"    ldr     r0, =0xfcda103c\n" // DATA copied
"    ldr     r1, =0x00008000\n" // to RAM
"    ldr     r3, =0x000347d4\n"
"loc_fc02005a:\n"
"    cmp     r1, r3\n"
"    itt     lo\n"
"    ldrlo   r2, [r0], #4\n"
"    strlo   r2, [r1], #4\n"
"    blo     loc_fc02005a\n"
"    ldr     r3, =0x000347d4\n" // BSS
"    ldr     r1, =0x003976c0\n"
"    mov.w   r2, #0\n"
"loc_fc020070:\n"
"    cmp     r3, r1\n"
"    it      lo\n"
"    strlo   r2, [r3], #4\n"
"    blo     loc_fc020070\n"
//"    ldr pc,=0xfc05c939\n" // -> fw
"    blx     patch_mzrm_sendmsg\n"
"    b.w     sub_fc05c938_my\n" // ->

        "patch_CreateTask:\n"
        "ldr.w   pc, [pc,#0]\n"             // Do jump to absolute address CreateTask_my
        ".long   CreateTask_low_my + 1\n"           // has to be a thumb address
);
}

#ifdef PTPIP_RECV_DATA_FIX
extern int _ClearEventFlag(int ef, int what);

extern void _ptpip_recv_data_cb(int x, int y, int z);
extern void _reset_some_ptpip_struct(unsigned *x);
extern int ptpip_pktdet_ef;

int ptpip_recv_data_cb_my(int x, int y, int z, unsigned lr)
{
    // return value is ignored in stock firmware
    _ptpip_recv_data_cb(x,y,z);

    // bail if return address not case in FUN_fc21fe8e when recv_data has recieved max size but more data left
    if(lr != 0xfc21fee3) {
        return 0;
    }
    // x is PTP data->handle, 0xcc offset from ptpip data->recv_data (fc22117e) at fc221256
    unsigned *p = *(unsigned **)(x + 0xcc);
    // shouldn't ever be null but bail if it is
    if(!p) {
        return 0;
    }
    // other cases which wouldn't hit problem function FUN_fc162848
    // p[0x29] corresponds to check at fc21feec
    // p[3] & 1 at fc21fef2
    if(p[0x29] == 0 || (p[3] & 1)) {
        return 0;
    }
    // block task_PtpipPacketDetector until next recv_data call (set by FUN_fc220608 -> FUN_fc162a6c)
    _ClearEventFlag(ptpip_pktdet_ef,2);
    // resets some per-read variables + cb, should get re-initialized on next recv_data call
    _reset_some_ptpip_struct(&p[0x2a]);
    // set state var like FUN_fc21fe8e for this case (fc21fefa), check in FUN_fc220608 sets eventflag bit 2 based on this
    p[1] = 1;
    return 1; // signal asm hook to skip rest of calling function
}

// hook to replace FUN_fc221104
int __attribute__((naked,noinline)) hook_ptpip_recv_data_cb(int x, int y, int z) {
    asm volatile (
"mov r3, lr\n" // copy lr to 4th arg for patch check
"push {lr}\n"
"bl ptpip_recv_data_cb_my\n" // easier in C code, return value tells wether to modify return address
"pop {lr}\n"
"cbnz r0,ptpip_recv_data_fix\n"
"bx lr\n" // normal return
"ptpip_recv_data_fix:\n"
"pop {r4,r5,r6,r7,r8,r9,r10,pc}\n" // bypass rest of calling function if hook returned nz (equivalent to fc21ff0a)
    );
}

/*
modify messages recieved by task_PtpipController to install hook
message structure is
command number (0-3)
callback 1 func
callback 1 arg
callback 2 func (optional, only used in cmd 1
callback 2 arg
messages are posted using fc162652
*/
void ptpip_ctrl_msg_hook(unsigned *msg)
{
    // cmd 1 is sent from FUN_fc22067c when reading data
    if(msg[0] == 1 && msg[1] == 0xfc220609) { // cmd 1 callback function of interest (others are used in other cases)
        unsigned *p = (unsigned *)(msg[2]); // argument block for func
        if(p) {
            // callback set in ptpip data->recv_data at fc22124e, called by FUN_fc21fe8e on completion
            // of recv_data
            if(p[1] == 0xfc221105) { 
                p[1] = ((unsigned)hook_ptpip_recv_data_cb) | 1; // gcc (10) seems to get the thumb bit right, but harmless
            }
        }
    }
}

void __attribute__((naked,noinline)) task_ptpipcontroller_my() {
    asm volatile (
// task_PtpipController 0xfc162553
"    push    {r4, r5, lr}\n"
"    ldr     r4, =0x0000fd5c\n"
"    sub     sp, #0x1c\n"
"loc_fc162558:\n"
"    movs    r2, #0\n"
"    add     r1, sp, #0x18\n"
"    ldr     r0, [r4, #0xc]\n"
"    bl      sub_fc3446ae\n" // ReceiveMessageQueue
"    lsls    r0, r0, #0x1f\n"
"    bne     loc_fc1625c0\n"
"    ldr     r1, [sp, #0x18]\n"
"    movs    r2, #0x14\n"
"    add     r0, sp, #4\n"
"    mov     r5, r1\n"
"    blx     sub_fc301dec\n" // j_dry_memcpy
"    ldr     r0, [r4, #0x10]\n"
"    mov     r1, r5\n"
"    bl      sub_fc41fb26\n"
"add r0, sp, #4\n" // pointer to message
"bl ptpip_ctrl_msg_hook\n"
"    ldr     r0, [sp, #4]\n"
"    cmp     r0, #3\n"
"    beq     loc_fc1625c0\n"
"    cbz     r0, loc_fc162596\n"
"    cmp     r0, #1\n"
"    beq     loc_fc16259c\n"
"    cmp     r0, #2\n"
"    bne     loc_fc1625b4\n"
"    ldrd    r1, r0, [sp, #8]\n"
"    blx     r1\n"
"    bl      sub_fc162a4c\n"
"    b       loc_fc162558\n"
"loc_fc162596:\n"
"    bl      sub_fc1626ea\n"
"    b       loc_fc162558\n"
"loc_fc16259c:\n"
"    ldrd    r1, r0, [sp, #8]\n"
"    blx     r1\n"
"mov r1,r0\n"
"    lsls    r0, r0, #0x1f\n"
"    beq     loc_fc162558\n"
"    ldr     r0, [sp, #0x10]\n"
"    cmp     r0, #0\n"
"    beq     loc_fc162558\n"
"    ldrd    r1, r0, [sp, #0x10]\n"
"    blx     r1\n"
"    b       loc_fc162558\n"
"loc_fc1625b4:\n"
"    movs    r2, #0xcb\n"
"    movs    r0, #0\n"
"    ldr     r1, =0xfc16272c\n" //  *"PTPIPController.c"
"    bl      _DebugAssert\n"
"    b       loc_fc162558\n"
"loc_fc1625c0:\n"
"    bl      sub_fc162a18\n"
"    movs    r0, #0\n"
"    str     r0, [r4, #8]\n"
"    ldr     r0, [r4, #0x14]\n"
"    movs    r1, #1\n"
"    bl      _SetEventFlag\n"
"    bl      _ExitTask\n"
"    add     sp, #0x1c\n"
"    movs    r0, #0\n"
"    pop     {r4, r5, pc}\n"
".ltorg\n"
    );
}
#endif // PTPIP_RECV_DATA_FIX


/*************************************************************/
/*
    Custom function called in mzrm_sendmsg via logging function pointer (normally disabled)
    Checks if called from function that is updating the Canon UI.
    Updates CHDK bitmap settings and sets flag to update CHDK UI.
*/
void __attribute__((naked,noinline))
debug_logging_my(char* fmt, ...)
{
    (void)fmt;  // unused parameter
    asm volatile (
            //LR = Return address
            "    ldr     r0, =mzrm_sendmsg_ret_adr\n"   // Is return address in mzrm_sendmsg function?
            "    cmp     r0, lr\n"
            "    beq     chk_msg_type\n"
            "exit_debug_logging_my:\n"
            "    bx      lr\n"

            "chk_msg_type:\n"
            // mzrm_sendmsg 'msg' value (2nd parameter, saved in r11)
            "    ldr     r1, [r11]\n"                   // message type
            "    cmp     r1, 0x25\n"                    // message type XimrExe
            "    beq     do_ui_update\n"
            "    cmp     r1, 0x26\n"                    // message type XimrExeGain
            "    bne     exit_debug_logging_my\n"
            "do_ui_update:\n"
            "    ldr     r0, [r11,0x0c]\n"              // address of Ximr context in 'msg'
            "    b       update_ui\n"
    );
}

/*
    Install and enable custom logging function for mzrm_sendmsg.
*/
void
patch_mzrm_sendmsg ()
{
    extern int debug_logging_flag;
    extern void (*debug_logging_ptr)(char* fmt, ...);

    // Each bit in debug_logging_flag enables logging in different areas of the firmware code - only set the bit required for mzrm logging.
    debug_logging_flag = 0x200;
    debug_logging_ptr = debug_logging_my;
}

/*************************************************************/
void __attribute__((naked,noinline)) CreateTask_low_my() {
asm volatile (
// CreateTask_low has entry point in r0, use r1 
"    push   {r1}\n"
//R0 = Pointer to task function to create
"    ldr     r1, =task_CaptSeq\n"       // DryOS original code function ptr.
"    cmp     r1, r0\n"                  // is the given taskptr equal to our searched function?
"    itt     eq\n"                      // EQ block
"    ldreq   r0, =capt_seq_task\n"      // if so replace with our task function base ptr.
"    orreq   r0, #1\n"                  // make sure it's a thumb address (may not be needed?)
"    beq     exitHook\n"                // below compares not necessary if this check has found something.

"    LDR     R1, =task_TricInitTask\n"
"    CMP     R1, R0\n"
"    itt     eq\n"
"    LDREQ   R0, =TricInitTask_my\n"
"    orreq   r0, #1\n"
"    BEQ     exitHook\n"

// exp_drv probably not needed for extended exposure, probably works up to 1024s, but required for < 1/3200
"    LDR     R1, =task_ExpDrv\n"
"    CMP     R1, R0\n"
"    itt     eq\n"
"    LDREQ   R0, =exp_drv_task\n"
"    orreq   r0, #1\n"
"    BEQ     exitHook\n"

#ifdef PTPIP_RECV_DATA_FIX
// hook to fix Canon firmware bug which breaks multiple recv_data calls in ptpip
"    LDR     R1, =task_PtpipController\n"
"    CMP     R1, R0\n"
"    itt     eq\n"
"    LDREQ   R0, =task_ptpipcontroller_my\n"
"    orreq   r0, #1\n"
"    BEQ     exitHook\n"
#endif // PTPIP_RECV_DATA_FIX

// note FileWrite does not exist on sx730

// not implemented
/*
"    LDR     R0, =task_MovieRecord\n"
"    CMP     R0, R3\n"
"    LDREQ   R3, =movie_record_task\n"
"    BEQ     exitHook\n"
*/

"    ldr     r1, =task_InitFileModules\n"
"    cmp     r1, r0\n"
"    itt     eq\n"
"    ldreq   r0, =init_file_modules_task\n"
"    orreq   r0, #1\n"
"exitHook:\n" 
// restore overwritten register(s)
"    pop    {r1}\n"
// Execute overwritten instructions from original code, then jump to firmware
// NOTE number of instructions duplicated here depends on size of original ROM code
// instructions. Must replace 8 bytes + any paritially overwritten instructions
// -s=CreateTask_low -c=3 -f=chdk
"    push.w  {r4, r5, r6, r7, r8, lr}\n" // 32 bit + 4
"    sub     sp, #0x20\n" // 16 bit, + 2
"    ldrd    r7, r8, [sp, #0x3c]\n" // 32 bit + 4 = 10
"    ldr.w   pc, =(hook_CreateTask_low + 10 + 1) \n"  // Continue in firmware (thumb bit set)
".ltorg\n"
);
}
//
// -f=chdk -s=0xfc05c939 -eret
void __attribute__((naked,noinline)) sub_fc05c938_my() {
// startup key checks handled in sub_fc589910_my
    asm volatile (
"    push    {r4, lr}\n"
#if defined(CHDK_NOT_IN_CANON_HEAP)
"    ldr     r4, =0x003976c0\n"
#else
    "ldr     r4, =new_sa\n"             // +
    "ldr     r4, [r4]\n"                // +
#endif
"    sub     sp, #0x78\n"
"    ldr     r0, =0x006ce000\n"
"    ldr     r1, =0x000adf44\n"
"    subs    r0, r0, r4\n"
"    cmp     r0, r1\n"
"    bhs     loc_fc05c94a\n"
"loc_fc05c948:\n"
"    b       loc_fc05c948\n"
"loc_fc05c94a:\n"
"    ldr     r1, =0x00008078\n"
"    mov.w   r0, #0x80000\n"
"    str     r0, [r1]\n"
"    ldr     r1, =0x0000807c\n"
"    ldr     r0, =0x42281000\n"
"    str     r0, [r1]\n"
"    ldr     r1, =0x00008080\n"
"    ldr     r0, =0x42283000\n"
"    str     r0, [r1]\n"
"    movs    r1, #0x78\n"
"    mov     r0, sp\n"
"    blx     sub_fc301dfc\n" // j_bzero
"    ldr     r0, =0x0060ff00\n"
"    ldr     r1, =0x000be100\n"
"    stm.w   sp, {r0, r1, r4}\n"
"    ldr     r1, =0x00601fbc\n"
"    subs    r2, r1, r4\n"
"    strd    r2, r1, [sp, #0xc]\n"
"    str     r0, [sp, #0x14]\n"
"    movs    r0, #0x22\n"
"    str     r0, [sp, #0x18]\n"
"    movs    r0, #0xc8\n"
"    str     r0, [sp, #0x1c]\n"
"    movw    r0, #0x2b0\n"
"    str     r0, [sp, #0x20]\n"
"    movs    r0, #0xfa\n"
"    str     r0, [sp, #0x24]\n"
"    movw    r0, #0x11a\n"
"    str     r0, [sp, #0x28]\n"
"    movs    r0, #0x85\n"
"    str     r0, [sp, #0x2c]\n"
"    movs    r0, #0x40\n"
"    str     r0, [sp, #0x30]\n"
"    movs    r0, #4\n"
"    str     r0, [sp, #0x34]\n"
"    movs    r0, #0\n"
"    str     r0, [sp, #0x38]\n"
"    movs    r0, #0x10\n"
"    str     r0, [sp, #0x5c]\n"
"    movs    r2, #0\n"
"    lsls    r0, r0, #8\n"
"    str     r0, [sp, #0x60]\n"
//"    ldr     r1, =0xfc05cacd\n"
"    ldr     r1, =sub_fc05cacc_my\n" // ->
"    asrs    r0, r0, #4\n"
"    str     r0, [sp, #0x64]\n"
"    lsls    r0, r0, #5\n"
"    str     r0, [sp, #0x68]\n"
"    mov     r0, sp\n"
"    blx     sub_fc3017dc\n"
"    add     sp, #0x78\n"
"    pop     {r4, pc}\n"
".ltorg\n"
    );
}

// -f=chdk -s=0xfc05cacd -c=54
void __attribute__((naked,noinline)) sub_fc05cacc_my() {
    asm volatile (
"    push    {r4, lr}\n"
"    ldr     r4, =0xfc05cb74\n" //  *"/_term"
"    bl      sub_fc05d9c0\n"
"    ldr     r0, =0x00008310\n"
"    ldr     r1, [r0]\n"
"    ldr     r0, =0x00008078\n"
"    ldr     r0, [r0]\n"
"    adds    r0, #8\n"
"    cmp     r1, r0\n"
"    bhs     loc_fc05cae8\n"
"    ldr     r0, =0xfc05cb84\n" //  *"USER_MEM size checking"
"    bl      sub_fc05cb5e\n"
"loc_fc05cae8:\n"
"    bl      sub_fc074640\n"
"    ldr     r1, =0xbfe10000\n"
// note capdis bad output
//"    mov.w   r2, #-0x11111112\n"
"    mov.w   r2, #0xeeeeeeee\n"
"    ldr     r3, =0xbfe10800\n"
"loc_fc05caf4:\n"
"    stm     r1!, {r2}\n"
"    cmp     r1, r3\n"
"    blo     loc_fc05caf4\n"
"    bl      sub_fc074652\n"
"    bl      sub_fc3a8c68\n"
"    cmp     r0, #0\n"
"    bge     loc_fc05cb0c\n"
"    ldr     r0, =0xfc05cba4\n" //  *"dmSetup"
"    bl      sub_fc05cb5e\n"
"loc_fc05cb0c:\n"
"    bl      sub_fc05e23c\n"
"    cmp     r0, #0\n"
"    bge     loc_fc05cb1a\n"
"    ldr     r0, =0xfc05cbac\n" //  *"termDriverInit"
"    bl      sub_fc05cb5e\n"
"loc_fc05cb1a:\n"
"    mov     r0, r4\n"
"    bl      sub_fc05e2ca\n"
"    cmp     r0, #0\n"
"    bge     loc_fc05cb2a\n"
"    ldr     r0, =0xfc05cbbc\n" //  *"termDeviceCreate"
"    bl      sub_fc05cb5e\n"
"loc_fc05cb2a:\n"
"    mov     r0, r4\n"
"    bl      sub_fc05cdcc\n"
"    cmp     r0, #0\n"
"    bge     loc_fc05cb3a\n"
"    ldr     r0, =0xfc05cbd0\n" //  *"stdioSetup"
"    bl      sub_fc05cb5e\n"
"loc_fc05cb3a:\n"
"    bl      sub_fc05cf10\n"
"    cmp     r0, #0\n"
"    bge     loc_fc05cb48\n"
"    ldr     r0, =0xfc05cbdc\n" //  *"stdlibSetup"
"    bl      sub_fc05cb5e\n"
"loc_fc05cb48:\n"
"    bl      sub_fc061684\n"
"    cmp     r0, #0\n"
"    bge     loc_fc05cb56\n"
"    ldr     r0, =0xfc05cbe8\n" //  *"extlib_setup"
"    bl      sub_fc05cb5e\n"
"loc_fc05cb56:\n"
"    pop.w   {r4, lr}\n"
//"    b.w     loc_fc05cd70\n"
"    b.w     sub_fc05cd70_my\n" // ->
    ".ltorg\n"
    );
}

//  -f=chdk -s=0xfc05cd71 -eret
void __attribute__((naked,noinline)) sub_fc05cd70_my() {
    asm volatile (
"    push    {r3, lr}\n"
"    bl      sub_fc05d018\n"
"    bl      sub_fc05cf34\n"
"    bl      sub_fc0648f0\n" // IsNormalCameraMode_FW
"    bl      sub_fc589910_my\n" // -> startup key checks, like sx710 fc0cf0ee
"    cbnz    r0, loc_fc05cd8a\n"
"    bl      sub_fc05d006\n"
"loc_fc05cd88:\n"
"    b       loc_fc05cd88\n"
"loc_fc05cd8a:\n"
"    bl      sub_fc369126\n"
"    ldr     r1, =0x006ce000\n"
"    movs    r0, #0\n"
"    bl      sub_fc3519e8\n"
"    movs    r3, #0\n"
"    str     r3, [sp]\n"
//"    ldr     r3, =0xfc05ccf5\n" //  task_Startup
"    ldr     r3, =task_Startup_my\n" //  ->
"    movs    r2, #0\n"
"    movs    r1, #0x19\n"
"    ldr     r0, =0xfc05cdc4\n" //  *"Startup"
"    bl      _CreateTask\n"
"    movs    r0, #0\n"
"    pop     {r3, pc}\n"
    ".ltorg\n"
    );
}

// -f=chdk -s=0xfc589911 -eret
void __attribute__((naked,noinline)) sub_fc589910_my() {
    asm volatile (
"    push.w  {r2, r3, r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}\n"
"    movs    r4, #0\n"
"    mov     fp, r0\n"
"    mov     r5, r4\n"
//"    bl      sub_fc505e80\n" // nullsub
"    movs    r0, #0x97\n"
"    bl      sub_fc506672\n" // MMIO 0xd20b025c (sub = return (*(0xd20b0000 + r0*4) << 15) < 0 )
"    movs    r6, #1\n"
"    bic.w   sb, r6, r0\n"
"    movs    r0, #0x8a\n"
"    bl      sub_fc506672\n" // MMIO 0xd20b0228
"    bic.w   r8, r6, r0\n"
"    movs    r0, #0\n"
"    bl      sub_fc505e7c\n" // return 1
"    cbz     r0, loc_fc589946\n"
"    movs    r0, #0x98\n"
"    bl      sub_fc506672\n" // MMIO 0xd20b0260
"    bic.w   r4, r6, r0\n"
"loc_fc589946:\n"
"    movw    r0, #0x10e\n"
"    bl      sub_fc506672\n" // MMIO 0xd20b0438
"    bic.w   r7, r6, r0\n"
"    movs    r0, #1\n"
"    bl      sub_fc505e7c\n" // return 1
"    cbz     r0, loc_fc589964\n"
"    movs    r0, #2\n"
"    bl      sub_fc506672\n" // MMIO 0xd20b0008
"    bic.w   r5, r6, r0\n"
"loc_fc589964:\n"
"    movw    r0, #0x186\n"
"    bl      sub_fc506672\n" // MMIO 0xd20b0618
"    mov     sl, r6\n"
"    bics    r6, r0\n"
"    cmp.w   fp, #0\n"
"    beq     loc_fc58999a\n" // this section not present in sx710, possibly related to USB wake / charge?
"    cbz     r4, loc_fc58998a\n"
"    movw    r0, #0x12c\n" 
"    bl      _SleepTask\n" // Sleep(300)
"    movs    r0, #0x98\n"
"    bl      sub_fc506672\n" // MMIO 0xd20b0260 (again)
"    bic.w   r4, sl, r0\n"
"loc_fc58998a:\n"
"    orr.w   r0, sb, r8\n"
"    orr.w   r1, r4, r7\n"
"    orrs    r0, r1\n"
"    orrs    r0, r5\n"
"    orrs    r0, r6\n"         // check all hardware related bits checked above
//"    beq     loc_fc5899b0\n" // old behavior, skip to return if none set
"    bne     loc_fc58999a\n"   // new behavior, go to final code if any set
    "mov  r8, #1\n"            // otherwise, act as if play was held (r8 guessed based on sx710)
"loc_fc58999a:\n"
"    strd    r5, r6, [sp]\n"
"    mov     r3, r7\n"
"    mov     r2, r4\n"
"    mov     r1, r8\n"
"    mov     r0, sb\n"
"    bl      sub_fc505e84\n"
//"    bl      sub_fc505e82\n" // nullsub
"    movs    r0, #1\n"
//"loc_fc5899b0:\n"
"    pop.w   {r2, r3, r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}\n"
    ".ltorg\n"
    );
}

// -f=chdk -s=task_Startup -c=34
void __attribute__((naked,noinline)) task_Startup_my() {
    asm volatile (
// task_Startup 0xfc05ccf5
"    push    {r4, lr}\n"
"    bl      sub_fc0dc368\n" // CreateTask ClockSave
"    ldr     r0, =0x41121000\n"
"    mov.w   r1, #0x20000\n"
"    bl      sub_fc3a8790\n" // unknown, similar to sx710 fc38df1c
"    cbz     r0, loc_fc05cd10\n"
"    movs    r2, #0x95\n"
"    movs    r0, #0\n"
"    ldr     r1, =0xfc05cdb0\n" //  *"Startup.c"
"    bl      _DebugAssert\n"
"loc_fc05cd10:\n"
"    bl      sub_fc05cfe0\n" // manipulates MMIOs, related to ClkEnabler_DUKE.c (like sx710 fc055f00)
//"    bl      sub_fc0dc400\n" // nullsub
"    bl      sub_fc081478\n" // ?
// SD startup reset for UHS support https://chdk.setepontos.com/index.php?topic=13089.msg132583#msg132583
"    bl      sub_010e19de\n" // similar to sx710 010e182c, called from func following func which creates SD1stinit task
//"    bl      sub_fc0dc486\n" // StartDiskboot
//"    bl      CreateTask_blinker\n"
"    bl      sub_fc3a88be\n"
"    bl      sub_fc074688\n"
"    bl      sub_fc05d134\n"
"    bl      sub_fc05d0c8\n" // "InitExDrivers.c", Omar init
"    bl      sub_fc0814ae\n" // StartWDT (and a lot of other stuff)
"    bl      sub_fc3a8818\n"
"    bl      sub_fc07468e\n" // UiMemory.C Ctrl*
//"    bl      sub_fc589826\n" // CreateTask PhySw
"    bl      sub_fc589826_my\n" // CreateTask PhySw
"    bl      CreateTask_spytask\n" 
"    bl      init_required_fw_features\n" // added
"    bl      sub_fc27ec44\n" // SsTask etc
"    bl      sub_fc0746a4\n"
"    bl      sub_fc093948\n"
"    bl      sub_fc0dbeda\n" // Battery.c
"    bl      sub_fc093a78\n" // task_Bye
"    bl      sub_fc0dc288\n"
"    bl      sub_fc0dbe96\n" // BatteryTask
//"    bl      sub_fc05d138\n" // nullsub
"    bl      sub_fc32d346\n"
"    bl      sub_fc0dbe68\n"
"    pop.w   {r4, lr}\n"
//"    b.w     loc_fc0dc33e\n"
"    ldr     pc,=0xfc0dc33f\n"
    ".ltorg\n"
    );
}

// -f=chdk -s=0xfc589827 -c=19
void __attribute__((naked,noinline)) sub_fc589826_my() {
    asm volatile (
"    push    {r2, r3, r4, lr}\n"
"    bl      sub_fc0fd7ac\n"
"    bl      sub_fc06486e\n" // IsFactoryMode_FW
"    cbnz    r0, loc_fc589836\n"
"    bl      sub_fc0fd750\n" // OpLog.Start_FW
"loc_fc589836:\n"
"    ldr     r4, =0x00008190\n" //  physw_run
"    ldr     r0, [r4, #4]\n"
"    cmp     r0, #0\n"
"    bne     loc_fc589856\n"
"    movs    r3, #1\n"
"    movs    r2, #0\n"
"    movs    r1, #0x13\n"
"    strd    r2, r3, [sp]\n"
//"    ldr     r3, =0xfc589801\n" //  task_PhySw
"    ldr     r3, =mykbd_task\n"
"    ldr     r0, =0xfc589bc4\n" //  *"PhySw"
//"    movw    r2, #0x800\n"
"    movw    r2, #0x2000\n" // adjusted 0x800 -> 0x2000
"    bl      sub_fc34b9c2\n" // CreateTaskStrictly_alt
"    str     r0, [r4, #4]\n"
"loc_fc589856:\n"
//"    b       loc_fc589554\n" // jumps over unrelated code to pop in stock firmware
"    pop     {r2, r3, r4, pc}\n"
    ".ltorg\n"
    );
}

// -f=chdk -s=task_InitFileModules -eret
void __attribute__((naked,noinline)) init_file_modules_task() {
    asm volatile (
// task_InitFileModules 0xfc0972a5
"    push    {r4, r5, r6, lr}\n"
"    movs    r0, #6\n"
//"    bl      sub_fc32ca18\n" //  return
"    bl      sub_fc099270\n"
"    movs    r4, r0\n"
"    movw    r5, #0x5006\n"
"    beq     loc_fc0972c0\n"
"    movs    r1, #0\n"
"    mov     r0, r5\n"
"    bl      _PostLogicalEventToUI\n"
"loc_fc0972c0:\n"
"    bl      sub_fc09929a\n"
"    BL      core_spytask_can_start\n" // + CHDK: Set "it's-safe-to-start" flag for spytask
"    cmp     r4, #0\n"
"    bne     loc_fc0972d4\n" //  return
"    mov     r0, r5\n"
"    pop.w   {r4, r5, r6, lr}\n"
"    movs    r1, #1\n"
"    b.w     _PostLogicalEventToUI\n"
"loc_fc0972d4:\n"
"    pop     {r4, r5, r6, pc}\n"
    ".ltorg\n"
    );
}

/*
    *** workaround ***
    Init stuff to avoid asserts on cameras running DryOS r54+
    https://chdk.setepontos.com/index.php?topic=12516.0
    Execute this only once
 */
void init_required_fw_features(void) {
    extern void _init_focus_eventflag();

    _init_focus_eventflag();
    extern int av_override_semaphore;
    extern int _CreateBinarySemaphoreStrictly(int x, int y);
    av_override_semaphore = _CreateBinarySemaphoreStrictly(0,0);
}

void __attribute__((naked,noinline)) kbd_p1_f_cont_my ()
{
// -f=chdk -s=kbd_p1_f_cont -c=18 -jfw
    asm volatile(
// kbd_p1_f_cont 0xfc589b4f
"    ldr     r3, =0x0003578c\n" //  physw_status
"    movs    r0, #2\n"
"    mov     r5, sp\n"
"    add.w   r6, r3, #0x24\n"
"loc_fc589b58:\n"
"    add.w   r1, r6, r0, lsl #2\n"
"    ldr.w   r2, [r3, r0, lsl #2]\n"
"    ldr     r7, [r1, #0xc]\n"
"    ldr     r1, [r1, #0x18]\n"
"    and.w   r2, r2, r7\n"
"    eor.w   r2, r2, r1\n"
"    str.w   r2, [r5, r0, lsl #2]\n"
"    subs    r0, r0, #1\n"
"    bpl     loc_fc589b58\n"
"    ldr     r2, =0x0003578c\n" //  physw_status
"    mov     r0, sp\n"
"    adds    r2, #0x18\n"
"    sub.w   r1, r2, #0xc\n"
//"    bl      sub_fc589620\n"
"    bl      sub_fc589620_my\n" // + 
"    ldr     pc, =0xfc589b83\n" // Continue in firmware
    ".ltorg\n"
    );
}

extern int physw_override;
// -f=chdk -s=0xfc589621 -c=4 -jfw
void __attribute__((naked,noinline)) sub_fc589620_my()
{
    asm volatile(
"    push.w  {r0, r1, r2, r3, r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}\n"
"    ldr     r4, =0x000357b0\n"
"    mov     r5, r0\n"
"    ldr     r0, =physw_override\n" // +
"    ldr.w   r0, [r0]\n" // + use CHDK override value
//"    mov.w   r0, #-1\n"
"    ldr     pc, =0xfc58962d\n" // Continue in firmware
    );
}

// fix for FI2 boot, see https://chdk.setepontos.com/index.php?topic=11316.msg136622#msg136622
// -f=chdk -s=task_TricInitTask -c=35
void __attribute__((naked,noinline)) TricInitTask_my()
{
    asm volatile(
// task_TricInitTask 0xfc521929
"    push.w  {r0, r1, r2, r3, r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}\n"
"    movs    r0, #8\n"
"    ldr     r1, =0xfc521b54\n" //  *"InitTskStart"
"    bl      sub_fc350df2\n"
"    ldr.w   sl, =0x0001c440\n"
"    movw    fp, #0x1000\n"
"    ldr     r4, =0x0001c43c\n"
"    movs    r2, #0\n"
"    ldr     r1, =0x0703870f\n"
"    ldr     r0, [r4]\n"
"    bl      sub_fc3699c0\n" // WaitForAnyEventFlag
"    lsls    r0, r0, #0x1f\n"
"    beq     loc_fc52195e\n"
"    movs    r0, #8\n"
"    ldr     r1, =0xfc521b6c\n" //  *"ER IniTskWait"
"    bl      sub_fc350e52\n"
"    ldr     r1, =0x0001c428\n"
"    movs    r0, #0\n"
"    str     r0, [r1]\n"
"    pop.w   {r0, r1, r2, r3, r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}\n"
"loc_fc52195e:\n"
"    ldr     r4, =0x0001c43c\n"
"    add     r1, sp, #0xc\n"
"    ldr     r0, [r4]\n"
"    bl      sub_fc369c1a\n" // GetEventFlagValue
"    ldr     r1, [sp, #0xc]\n"
"    ldr     r0, [r4]\n"
"    bl      sub_fc369bea\n" // ClearEventFlag
"    ldr     r0, =0x02000003\n"
"    ldr     r7, [sp, #0xc]\n"
"    tst     r7, r0\n"
"    beq     sub_fc521a62\n" // loc -> sub
"    lsls    r0, r7, #0x1f\n"
"    beq     sub_fc521982\n" // loc -> sub

"    ldr     r0, =0xd2020074\n" // + MMIO ref'd from fc412414, via end of fc521e06
"    ldr     r0, [r0]\n"        // + nonzero when core already running
"    subs    r0, #0\n"          // +
"    beq     tric1\n"           // +
"    ldr     r0, [r4]\n"        // +
"    mov     r1, #0x80\n"       // +
"    bl      _SetEventFlag\n"   // + core already initialized, set the SmacIdleCmp eventflag here
"tric1:\n"                      // +

"    bl      sub_fc521e06\n"
"    ldr     pc,=0xfc5219ef\n" // b to ldr pc
    ".ltorg\n"
    );
}
#ifdef CAM_HAS_JOGDIAL
// -f=chdk -s=kbd_p2_f -eret
void __attribute__((naked,noinline)) kbd_p2_f_my() {
    asm volatile(
// kbd_p2_f 0xfc58955d
"loc_fc58955c:\n"
"    push.w  {r4, r5, r6, r7, r8, lr}\n"
"    ldr     r6, =0x000357b0\n"
"    sub     sp, #0x18\n"
"    add     r7, sp, #8\n"
"    subs    r6, #0xc\n"
"    b       loc_fc58959e\n"
"loc_fc58956a:\n"
"    ldr     r1, =0x000357b0\n"
"    add     r3, sp, #8\n"
"    ldrb.w  r0, [sp, #4]\n"
"    add     r2, sp, #0x14\n"
"    subs    r1, #0x18\n"
"    bl      sub_fc5064a4\n"
"    cbnz    r0, loc_fc589584\n"
"    ldr     r1, [sp, #0x14]\n"
"    movs    r0, #0\n"
"    bl      sub_fc5894ce\n"
"loc_fc589584:\n"
"    movs    r0, #2\n"
"loc_fc589586:\n"
"    ldr.w   r1, [r7, r0, lsl #2]\n"
"    cbz     r1, loc_fc589596\n"
"    ldr.w   r2, [r6, r0, lsl #2]\n"
"    bics    r2, r1\n"
"    str.w   r2, [r6, r0, lsl #2]\n"
"loc_fc589596:\n"
"    subs    r0, r0, #1\n"
"    sxtb    r0, r0\n"
"    cmp     r0, #0\n"
"    bge     loc_fc589586\n"
"loc_fc58959e:\n"
"    ldr     r0, =0x000357b0\n"
"    add     r1, sp, #4\n"
"    subs    r0, #0xc\n"
"    bl      sub_fc5061d2\n"
"    cmp     r0, #0\n"
"    bne     loc_fc58956a\n"
"    ldr.w   r8, =0x000357b0\n"
"    movs    r4, #0\n"
"loc_fc5895b2:\n"
"    movs    r5, #0\n"
"    ldr.w   r0, [r6, r4, lsl #2]\n"
"    ldr.w   r1, [r8, r4, lsl #2]\n"
"    ands    r0, r1\n"
"    str.w   r0, [r6, r4, lsl #2]\n"
"    b       loc_fc58960a\n"
"loc_fc5895c4:\n"
"    lsrs    r0, r5\n"
"    lsls    r0, r0, #0x1f\n"
"    beq     loc_fc589602\n"
"    ldr     r1, =0x000357b0\n"
"    add.w   r0, r5, r4, lsl #5\n"
"    add     r3, sp, #8\n"
"    subs    r1, #0x18\n"
"    add     r2, sp, #0x14\n"
"    uxtb    r0, r0\n"
"    bl      sub_fc5064a4\n"
"    cbnz    r0, loc_fc5895e6\n"
"    ldr     r1, [sp, #0x14]\n"
"    movs    r0, #1\n"
"    bl      sub_fc5894ce\n"
"loc_fc5895e6:\n"
"    mov     r0, r4\n"
"    b       loc_fc5895fe\n"
"loc_fc5895ea:\n"
"    ldr.w   r1, [r7, r0, lsl #2]\n"
"    cbz     r1, loc_fc5895fa\n"
"    ldr.w   r2, [r6, r0, lsl #2]\n"
"    bics    r2, r1\n"
"    str.w   r2, [r6, r0, lsl #2]\n"
"loc_fc5895fa:\n"
"    adds    r0, r0, #1\n"
"    sxtb    r0, r0\n"
"loc_fc5895fe:\n"
"    cmp     r0, #3\n"
"    blt     loc_fc5895ea\n"
"loc_fc589602:\n"
"    ldr.w   r0, [r6, r4, lsl #2]\n"
"    adds    r5, r5, #1\n"
"    uxtb    r5, r5\n"
"loc_fc58960a:\n"
"    cmp     r0, #0\n"
"    bne     loc_fc5895c4\n"
"    adds    r4, r4, #1\n"
"    sxtb    r4, r4\n"
"    cmp     r4, #3\n"
"    blt     loc_fc5895b2\n"
//"    bl      sub_fc505f82\n"
"    bl      sub_fc505f82_my\n"
"    add     sp, #0x18\n"
"    pop.w   {r4, r5, r6, r7, r8, pc}\n" 
".ltorg\n"
    );
}
// -f=chdk -s=0xfc505f83 -c=9
void __attribute__((naked,noinline)) sub_fc505f82_my() {
    asm volatile(
"    push    {r4, lr}\n"
"    ldr     r4, =0x00009ad8\n"
"    ldr     r0, [r4, #8]\n"
"    bl      sub_fc50a904\n"
"    bl      sub_fc3d45a0\n"
"    ldr     r0, [r4, #0xc]\n"
"    bl      sub_fc50a834\n"
"    bl      handle_jogdial\n"  // +
"    cmp     r0, #0\n"          // +
"    beq     no_scroll\n"       // +
"    bl      sub_fc50addc\n"    // handles scrollwheel(s), void function, no args
//"    pop.w   {r4, lr}\n"
"no_scroll:\n"                  // +
"    pop   {r4, pc}\n"          // +
//"    b.w     loc_fc50addc\n"
".ltorg\n"
    );
}
#endif
