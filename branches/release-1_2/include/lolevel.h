#ifndef LOLEVEL_H
#define LOLEVEL_H

#ifndef LOW_LEVEL
#error File can be included when platform is built only!
#endif

#ifndef __arm__
#error File can be included in ARM mode only!
#endif

/* Canon stuff */
extern long *_GetSystemTime(long *t);
extern long _GetZoomLensCurrentPosition();
extern long _GetZoomLensCurrentPoint();
extern long _MoveZoomLensWithPoint(short *pos);
extern long _SetZoomActuatorSpeedPercent(short *perc);
extern volatile long zoom_busy;
extern long _GetFocusLensCurrentPosition();
extern long _GetFocusLensSubjectDistance();
extern long _GetFocusLensSubjectDistanceFromLens();
extern void _MoveFocusLensToDistance(short *dist);
#ifdef CAM_AV_OVERRIDE_IRIS_FIX
extern int _MoveIrisWithAv(short*);
#endif
extern void _PutInNdFilter();
extern void _PutOutNdFilter();
extern volatile long focus_busy;
extern long _GetCurrentAvValue();
extern long _GetCurrentTargetDistance();
extern long _GetPropertyCase(long opt_id, void *buf, long bufsize);
extern long _SetPropertyCase(long opt_id, void *buf, long bufsize);
extern long _IsStrobeChargeCompleted();
extern long _VbattGet();
extern int _GetBatteryTemperature();
extern int _GetCCDTemperature();
extern int _GetOpticalTemperature();
extern void _PT_PlaySound(short , void*);
extern void _RefreshPhysicalScreen(long f);
extern void _Unmount_FileSystem();
extern void _Mount_FileSystem();
extern void _SleepTask(long msec);
extern int _CreateTask (const char *name, int prio, int stack_size /*?*/,
                        void *entry, long parm /*?*/);
extern void _SleepTask(long msec);
extern void __attribute__((noreturn)) _ExitTask();
extern int _taskNameToId(char* taskName); // VxWorks only, task's name first letter must be 't', maximum 10 chars total 
extern const char *_taskName(int taskID); // VxWorks only for now
extern int _taskIdListGet(int *idlist,int max); // VxWorks only for now
extern void _taskSuspend(int taskId);
extern void _taskResume(int taskId);
extern int _errnoOfTaskGet(int tid);

extern long _SetEventFlag(void *flag, long what);
extern long _CheckAnyEventFlag(void *flag, long mask, long *res);
extern long _GetEventFlagValue(void *flag, long *res);

extern long _ReceiveMessageQueue(void *msgq, long *dst, long unk1 /* maybe size? */);

/* Canon stuff with nonoriginal naming */
extern long _GetParameterData(long id, void *buf, long size);
extern long _SetParameterData(long id, void *buf, long size);
#ifdef  CAM_DRYOS_2_3_R47
extern void _MakeSDCardBootable(int driveno);
#else
extern void _UpdateMBROnFlash(int driveno, long offset, char *str);
#endif

/* standart C library */
//extern int _creat (const char *name, int flags);
extern int _open (const char *name, int flags, int mode );
extern int _close (int fd);
extern int _write (int fd, void *buffer, long nbytes);
extern int _read (int fd, void *buffer, long nbytes);
extern int _lseek (int fd, long offset, int whence);
extern long _mkdir(const char *dirname);

extern int _Open (const char *name, int flags, int mode );
extern int _Close (int fd);
extern int _Write (int fd, const void *buffer, long nbytes);
extern int _Read (int fd, void *buffer, long nbytes);
extern int _Lseek (int fd, long offset, int whence);
extern int _Remove(const char *name);

extern long _Fopen_Fut(const char *filename, const char *mode);
extern long _Fclose_Fut(long file);
extern long _Fread_Fut(void *buf, long elsize, long count, long f);
extern long _Fwrite_Fut(const void *buf, long elsize, long count, long f);
extern long _Fseek_Fut(long file, long offset, long whence);
extern long _Fflush_Fut(long file);
extern long _Feof_Fut(long file);
extern long _Fflush_Fut(long file);
extern char *_Fgets_Fut(char *buf, int n, long f);
extern long _RenameFile_Fut(const char *oldname, const char *newname);
extern long _DeleteFile_Fut(const char *name);
extern long _MakeDirectory_Fut(const char *name,int unk);
extern long _DeleteDirectory_Fut(const char *name);

extern int _isdigit(int c);
extern int _isspace(int c);
extern int _isalpha(int c);
extern int _isupper(int c);
extern int _islower(int c);
extern int _ispunct(int c);
extern int _isxdigit(int c);

extern long _strlen(const char *s);
extern int _strcmp(const char *s1, const char *s2);
extern int _strncmp(const char *s1, const char *s2, long n);
extern char *_strchr(const char *s, int c);
extern char *_strcpy(char *dest, const char *src);
extern char *_strncpy(char *dest, const char *src, long n);
extern char *_strcat(char *dest, const char *app);
extern char *_strrchr(const char *s, int c);
extern char *_strpbrk(const char *s, const char *accept);

extern long _strtol(const char *nptr, char **endptr, int base);
extern unsigned long _strtoul(const char *nptr, char **endptr, int base);
// DRYOS: this function is called by strtol (mode=1) and strtoul (mode=0)
// easier to match with sig finder
extern long _strtolx(const char *nptr, char **endptr, int base, int mode);

extern int _tolower(int c);
extern int _toupper(int c);

extern int _vsprintf(char *buf, const char *fmt, __builtin_va_list va_list);

/**
 * No STUBS!
 * You can't use these two directly from THUMB code (core), only from platform.
 */
//extern int fprintf(FILE *fd, char*buf, ...);
extern int _printf(char *buf, ...);

extern void *_malloc(long size);
extern void _free(void *p);
extern void *_AllocateUncacheableMemory(long size);
extern void _FreeUncacheableMemory(void *p);

extern void *_memchr(const void *s, int c, int n);
extern void *_memcpy(void *dest, const void *src, long n);
extern void *_memset(void *s, int c, int n);
extern int _memcmp(const void *s1, const void *s2, long n);

extern void _qsort (void *__base, int __nelem, int __size, int (*__cmp)(const void *__e1, const void *__e2));

/* VxWorks */
extern long _taskLock();
extern long _taskUnlock();
extern int _taskCreateHookAdd (void *createHook);
extern int _taskDeleteHookAdd (void *deleteHook);
extern long _iosDevAdd(void*,void*,int);
extern long _iosDevDelete(void*);
extern long _iosDrvInstall(void*,void*,void*,void*,void*,void*,void*);
extern void _GiveSemaphore(int sem);

/* misc */
extern const char aPhysw;
extern long physw_run;
extern long physw_sleep_delay;
extern long _kbd_p1_f();
extern void _kbd_p2_f();
extern void _kbd_pwr_on();
extern void _kbd_pwr_off();
extern void _kbd_read_keys_r2(void*p);
extern long physw_status[3], physw_copy[3];

extern void __attribute__((naked,noinline)) mykbd_task();
extern void capt_seq_task();
extern void movie_record_task();
extern void init_file_modules_task();
extern void exp_drv_task();
extern void filewritetask();

void kbd_fetch_data(long *dst);

/*used to detect play or record mode without relying on physical switch positions
 values on most cameras:
  0 = startup in play
  1 = unknown, appears to happen in first play<->rec transition
  2 = record mode
  4 = canon menu in record mode
  3 = play after being in record mode at least once
  5 = transitioning between some record modes, such as movie
 values on very old vxworks cameras (ixus50_sd400, ixus700_sd500, s2is)
  0 = startup in play
  1 = rec
  2 = play
  3 = maybe transition ?
 address in all cases can be found with strings "MenuIn", "MenuOut"
*/
extern long playrec_mode;

extern void *led_table;
extern void _UniqueLedOn(void *addr, long brightness);
extern void _UniqueLedOff(void *addr);
struct led_control {int led_num; int action; int brightness; int blink_count;};
extern int _PostLEDMessage(struct led_control *);
extern int _LEDDrive(int led, int action);


extern long _LockMainPower();
extern long _UnlockMainPower();
extern void _SetAutoShutdownTime(int t);

/*
The following two functions post an event such as button press, switch change, cable connection change.
event:
  A number identifying the event. This number may vary between camera models. 
  See levent.c and levent.h for methods to identify events by name.
unk: 
  Unknown value, usually 0 in canon code. For jogdial messages, this is number of clicks.
return value:
  Unknown, possibly void.
*/
extern int  _PostLogicalEventForNotPowerType(int event, int unk);
extern int  _PostLogicalEventToUI(int event, int unk);
/*
Used in the canon code to modify the generation or delivery of events. For example, Canon 
mode override code sets 1 on the desired dial position, and zero on all others.
event: as described above for PostLogicalEvent*
state: if 1, the event will be generated/delivered as normal. If 0, the event is disabled/blocked.
*/
extern void _SetLogicalEventActive(unsigned event, unsigned state);
/* Somehow related to the above. Normally 0, set to 1 for script mode */
extern void _SetScriptMode(unsigned mode);


/* math */
extern int _rand(void);
extern void* _srand(unsigned int seed);

extern double __log(double x);
extern double __log10(double x);
extern double __pow(double x, double y);
extern double __sqrt(double x);

/* time */
extern int _utime(const char *file, void *newTimes);
extern unsigned long _time(/*time_t*/ unsigned long *timer);
extern void *_localtime(const /*time_t*/ unsigned long *_tod);
extern void *_LocalTime(const /*time_t*/ unsigned long *_tod, void * t_m); // DRYOS
extern long _strftime(char *s, unsigned long maxsize, const char *format, const /*struct tm*/ void *timp);
extern /*time_t*/ long _mktime(/*struct tm*/ void *timp); // VXWORKS
extern /*time_t*/ long _mktime_ext(void *tim_extp); // DRYOS, doesn't take a struct tm *

#ifdef CAM_DRYOS_2_3_R39
extern int _SetFileTimeStamp(const char *file_path, int time1, int time2);
extern int _SetFileAttributes(const char *fn, int attr);
#else
extern int _SetFileTimeStamp(int fd, int time1, int time2);
extern void _SetFileAttributes(int fd, int attr);
#endif

/* file */
extern int   _stat(const char *name, void *pStat);
extern unsigned long _GetDrive_ClusterSize(int drive);
extern unsigned long _GetDrive_TotalClusters(int drive);
extern unsigned long _GetDrive_FreeClusters(int drive);
extern int _WriteSDCard(unsigned int drive, unsigned int start_sect, unsigned int num_sect, void *buf);

extern void _UnsetZoomForMovie(void);
extern void _TurnOffMic(void);
extern void _TurnOnMic(void);

extern void _MakeAFScan(int*, int);
extern void _ExpCtrlTool_StartContiAE(int, int);
extern void _ExpCtrlTool_StopContiAE(int, int);

extern int some_flag_for_af_scan;
extern int parameter_for_af_scan;
extern short _SetAE_ShutterSpeed(short* tv);

extern void _EnterToCompensationEVF(void);
extern void _ExitFromCompensationEVF(void);

extern void _TurnOnBackLight(void);
extern void _TurnOffBackLight(void);
extern void _TurnOnDisplay(void);
extern void _TurnOffDisplay(void);

extern void _DoAFLock(void);
extern void _UnlockAF(void);

extern int _apex2us(int);

extern void _ScreenLock();
extern void _SetCurrentCaptureModeType();
extern unsigned _ExecuteEventProcedure(const char *name, ...);
// known in CHDK as _RefreshPhysicalScreen
//extern void _ScreenUnLock();

// 7 calls functions and sets some MMIOs, but doesn't disable caches and actually restart
// 3 skips one function call on some cameras, but does restart
extern void _Restart(unsigned option);

// boot an fir/fi2 file
extern void _reboot_fw_update(const char* bootfile);

// PTP
extern int _add_ptp_handler(int, void*, int);
extern void _set_control_event(int);
extern void _PB2Rec();
extern void _Rec2PB();

#ifdef OPT_EXMEM_MALLOC
// dryos + some vxworks only takes 3 params in reality
// on some vxworks the function that is easy to match with sig finder takes an additional param,
// set to zero in the real AllocateExMem
// versions that don't expect a 4th param will just ignore it
extern void *_exmem_alloc(int pool_id,int size,int unk,int unk2); 
#endif

// vxworks only
// used on a few cameras that don't have memPartInfoGet, see CAM_NO_MEMPARTINFO
extern int _memPartFindMax(int mempart_id); 
extern int _memPartInfoGet(int mempart_id,int *info);

#ifdef CAM_HAS_GPS
extern void _GPS_UpdateData();
#endif

#endif
