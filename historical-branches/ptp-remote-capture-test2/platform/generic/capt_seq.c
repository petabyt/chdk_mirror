// generic capt_seq fuctions
#include "asmsafe.h"
#include "conf.h"
#include "stdlib.h" // for NULL
#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

// some cams use different values
// note: many cams ROM also accepts a value of 3, meaning unknown
#ifndef NR_ON
#define NR_ON (2)
#endif
#ifndef NR_OFF
#define NR_OFF (1)
#endif

static long raw_save_stage;
static int imagesavecomplete=1;
#ifdef CAM_HAS_COMPLETEFILEWRITE_REPLACEMENT
/*
 * should be defined in capt_seq.c for cams that implement fwt_after_close()
 * only makes sense for VxWorks cams (and DryOS < r23)
 */
static int no_pt_completefilewrite=0;
#else
static int no_pt_completefilewrite=1;
#endif //CAM_HAS_COMPLETEFILEWRITE_REPLACEMENT

#ifdef CAM_CHDK_PTP_REMOTESHOOT
#include "remotecap_core.h"
static int ignore_current_write=0; //used by the platform routine to check whether to write the current file
#ifdef CAM_DRYOS
volatile int current_write_ignored=0; //needed to prevent nasty surprises with the current override code
#endif //CAM_DRYOS
#endif //CAM_CHDK_PTP_REMOTESHOOT

void __attribute__((naked,noinline)) capt_seq_hook_raw_here()
{
 asm volatile("STMFD   SP!, {R0-R12,LR}\n");

    imagesavecomplete=no_pt_completefilewrite; // TODO is there a better place to do this?

#ifdef PAUSE_FOR_FILE_COUNTER
    // Some cameras need a slight delay for the file counter to be updated correctly
    // before raw_savefile tries to get the file name & directory.
    // Add '#define PAUSE_FOR_FILE_COUNTER 100' in the camera firmware capt_seq.c file.
    // The value can be adjusted as needed for different cameras.
    if ( (conf.save_raw && is_raw_enabled()) // Only delay if RAW enabled (prevents slowdown in HQ burst mode)
#ifdef CAM_CHDK_PTP_REMOTESHOOT
        || (remotecap_get_target() & 7) //... or if remote shooting is active
#endif //CAM_CHDK_PTP_REMOTESHOOT
    )
    {
        int fc = get_file_counter();
        int tc = get_tick_count() + PAUSE_FOR_FILE_COUNTER;
        while ((get_file_counter() == fc) && (get_tick_count() < tc))
            _SleepTask(10);
    }
#endif

#ifdef CAM_CHDK_PTP_REMOTESHOOT
    if ( remotecap_get_target() != 0 ) //remote redirection
    {
        remotecap_raw_available();
    }
    else
#endif //CAM_CHDK_PTP_REMOTESHOOT
    {
        raw_save_stage = RAWDATA_AVAILABLE;
        core_rawdata_available(); //notifies spytask in core/main.c
        while (raw_save_stage != RAWDATA_SAVED){
        _SleepTask(10);
        }
    }
 asm volatile("LDMFD   SP!, {R0-R12,PC}\n");
}

#ifdef CAM_CHDK_PTP_REMOTESHOOT
#ifdef CAM_HAS_FILEWRITETASK_HOOK
/*
handle camera specific MAX_CHUNKS_FOR_JPEG, camp_ptp_data_chunk
get address and size of chunk N
returns NULL addr and zero size when max chunks reached
*/
static cam_ptp_data_chunk *jpeg_chunks;
#ifdef CAM_EXTENDED_FILEWRITETASK
static int jpeg_bytes_left;
static int jpeg_curr_session_chunk;
static int jpeg_file_offset;
static int jpeg_full_size;
#endif //CAM_EXTENDED_FILEWRITETASK
int filewrite_get_jpeg_chunk(char **addr,int *size,unsigned n,int *pos) {
#ifndef CAM_EXTENDED_FILEWRITETASK
    *pos=-1;
    if (n >= MAX_CHUNKS_FOR_JPEG || jpeg_chunks == NULL) {
        *addr=(char *)0xFFFFFFFF; // signals last chunk
        *size=0;
        return 0; // last chunk
    }
    *addr=(char *)jpeg_chunks[n].address;
    *size=jpeg_chunks[n].length;
    if (n < MAX_CHUNKS_FOR_JPEG-1) {
        if (jpeg_chunks[n+1].length==0) {
            return 0; // last chunk
        }
    }
    return 1; // not last chunk
#else
    if ( jpeg_chunks == NULL ) { //do we have a valid queue?
        int m=50;
        while (m>0) { //wait for at most 500ms
            _SleepTask(10);
            m--;
            if ( jpeg_chunks != NULL ) break;
        }
        if ( jpeg_chunks == NULL ) { //timeout, error
            *addr=(char *)0;
            *size=0;
            *pos=-1;
            return 0;
        }
    }
    if ( n == 0 ) { // first chunk for this shot
        jpeg_bytes_left = jpeg_full_size;
    }
    /*
     * handle multiple filewritetask invocations
     * return 0 for the last chunk
     * return 1 when there's an additional chunk in the current queue
     * return 2 when the current queue is done, but the file isn't
     */
    *addr=(char *)jpeg_chunks[jpeg_curr_session_chunk].address;
    *size=jpeg_chunks[jpeg_curr_session_chunk].length;
    jpeg_bytes_left -= *size;
    if (jpeg_curr_session_chunk == 0) {
        *pos=jpeg_file_offset; //only post file offset for the first chunk in the current queue
    }
    else {
        *pos=-1;
    }
    jpeg_curr_session_chunk++;
    if (jpeg_bytes_left>0) {
        if ( jpeg_curr_session_chunk < MAX_CHUNKS_FOR_JPEG ) {
            if (jpeg_chunks[jpeg_curr_session_chunk].length==0) { //last chunk of the current queue
                return 2;
            }
        }
        else {
            return 2;
        }
    }
    else {
        return 0; //last
    }

    return 1; //not last

#endif //CAM_EXTENDED_FILEWRITETASK
}

void filewrite_set_discard_jpeg(int state) {
    ignore_current_write = state;
}

void filewrite_main_hook(fwt_data_struct *fwt_data)
{
#ifdef CAM_EXTENDED_FILEWRITETASK
    // don't forget to #define FWT_CONDSEEK, FWT_MUSTSEEK
    jpeg_curr_session_chunk = 0;
    /*
     * file open flags are at offset 0xc for DryOS r50
     * these are the following for a "complicated" case (in order of appearance)
     * 0x8301: seek is needed (initial), value passed to open()
     * 0x8009: no seek
     * 0x8009: no seek
     * 0x8001: seek is needed (final)
     * 
     * for a simple case
     * 0x301
     * 
     * seek flag is at offset 0x50 for DryOS r50
     * 0: no seek
     * 2: seek                      -> FWT_MUSTSEEK
     * 3: seek if file offset != 0  -> FWT_CONDSEEK
     */
    switch ( fwt_data->seek_flag ) {
        case FWT_MUSTSEEK:
            jpeg_file_offset = fwt_data->file_offset;
            break;
        case FWT_CONDSEEK:
            if ( fwt_data->file_offset != 0 ) {
                jpeg_file_offset = fwt_data->file_offset;
                break;
            }
            //fall through
        default:
            jpeg_file_offset = -1; // no seek needed
            break;
    }
    jpeg_full_size = fwt_data->full_size;
#endif //CAM_EXTENDED_FILEWRITETASK
    jpeg_chunks = &(fwt_data->pdc[0]);
    remotecap_jpeg_available(&(fwt_data->name[0]));
    while (remotecap_hook_wait(RC_WAIT_FWTASK)) {
        _SleepTask(10);
    }
    jpeg_chunks=NULL;
}

#ifdef CAM_EXTENDED_FILEWRITETASK
void remotecap_jpeg_chunks_done() {
    jpeg_chunks=NULL;
}
#endif //CAM_EXTENDED_FILEWRITETASK

#endif //CAM_HAS_FILEWRITETASK_HOOK

#endif //CAM_CHDK_PTP_REMOTESHOOT

// wrapper function to store status on stack as this routine is called from assembly code in capt_seq_task()

void __attribute__((naked,noinline)) wait_until_remote_button_is_released(  ) 
{ 
asm volatile (
ASM_SAFE("BL _wait_until_remote_button_is_released\n")
 "	BX      LR \n"
	) ;
}


void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}

void __attribute__((naked,noinline)) capt_seq_hook_set_nr()
{
 asm volatile("STMFD   SP!, {R0-R12,LR}\n");
    switch (conf.raw_nr){
    case NOISE_REDUCTION_AUTO_CANON:
        // leave it alone
#if defined(NR_AUTO)			// If value defined store it (e.g. for G12 & SX30 need to reset back to 0 to enable auto)
        *nrflag = NR_AUTO;
#endif
        break;
    case NOISE_REDUCTION_OFF:
        *nrflag = NR_OFF;
        break;
    case NOISE_REDUCTION_ON:
        *nrflag = NR_ON;
        break;
    };

 camera_info.state.shutter_open_time = _time((void*)0);
 camera_info.state.shutter_open_tick_count = get_tick_count();

 asm volatile("LDMFD   SP!, {R0-R12,PC}\n");
}

#ifdef CAM_HAS_FILEWRITETASK_HOOK
// wrapper functions for use in filewritetask
#ifdef CAM_DRYOS
int fwt_open(const char *name, int flags, int mode) {
    if (!ignore_current_write) {
        return _Open(name, flags, mode);
    }
    current_write_ignored=1;
    return 255; // fake, invalid file descriptor
}

int fwt_write(int fd, const void *buffer, long nbytes) {
    if (!current_write_ignored) {
        return _Write(fd, buffer, nbytes);
    }
    return (int)nbytes; // "everything's written"
}

#ifdef CAM_EXTENDED_FILEWRITETASK
int fwt_lseek(int fd, long offset, int whence) {
    if (!current_write_ignored) {
        return _Lseek(fd, offset, whence);
    }
    return (int)offset; // "file position set to the requested value"
}
#endif // CAM_EXTENDED_FILEWRITETASK

int fwt_close (int fd) {
    if (!current_write_ignored) {
        return _Close(fd);
    }
    if (no_pt_completefilewrite) {
        imagesavecomplete=1;
    }
    ignore_current_write=0;
    current_write_ignored=0;
    return 0;
}
#else
/*
 * helper function for VxWorks camera
 * to be used when imagesavecomplete handling is needed
 */
int fwt_after_close (int param) {
    imagesavecomplete=1;
    return param;
}
#endif //CAM_DRYOS
#endif //CAM_HAS_FILEWRITETASK_HOOK

void supported_pt_completefilewrite() {
    no_pt_completefilewrite=0;
}

void image_save_completed() {
/* 
 * only called from the overridden PT_CompleteFileWrite eventproc
 */
    imagesavecomplete = 1;
    ignore_current_write = 0;
}

int is_image_save_complete() {
    return imagesavecomplete;
}
