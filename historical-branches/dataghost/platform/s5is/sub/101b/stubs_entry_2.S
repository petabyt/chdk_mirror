#include "stubs_asm.h"

NHSTUB(SleepTask                              ,0xFF82AB58)
NHSTUB(CreateTask                             ,0xFF81B8FC)
NHSTUB(ExitTask                               ,0xFF81BB8C)
NHSTUB(AllocateMemory                         ,0xFFA410A8)

// Look over all these again, some point to a B sub_.... so that's unnecessary.
NHSTUB(ExecuteEventProcedure                  ,0xFF81BE9C)
NHSTUB(FreeMemory                             ,0xFFA41094)
NHSTUB(GetCurrentTargetDistance               ,0xFF9511A4)
NHSTUB(GetSystemTime                          ,0xFFA411A4)
NHSTUB(ints_disable                           ,0xFF81058C) // Actually identified as IRQdisable by signatures
NHSTUB(ints_enable                            ,0xFF8105B4) // Actually identified as IRQenable by signatures
NHSTUB(memcmp                                 ,0xFF81E664)
NHSTUB(memcpy                                 ,0xFF8B3200)
NHSTUB(memset                                 ,0xFFA64B94)
NHSTUB(Close                                  ,0xFF825CC4)
NHSTUB(Open                                   ,0xFF825C9C)
NHSTUB(Read                                   ,0xFF825D6C)
NHSTUB(Write                                  ,0xFF825D70)
NHSTUB(Lseek                                  ,0xFF825ECC)
NHSTUB(strcmp                                 ,0xFF81E5FC)
NHSTUB(strcpy                                 ,0xFF81E5A8)
NHSTUB(strlen                                 ,0xFF81E640)
NHSTUB(TakeSemaphore                          ,0xFF81B798)
NHSTUB(vsprintf                               ,0xFF81E528)    // first sub called in FADBGPrintf
NHSTUB(GetFocusLensSubjectDistance            ,0xFF952444)    // returns 0. What's wrong?
NHSTUB(GetZoomLensCurrentPoint                ,0xFF957CBC)
NHSTUB(GetZoomLensCurrentPosition             ,0xFF957CC0)
NHSTUB(RefreshPhysicalScreen                  ,0xFF8B2D90)
NHSTUB(GetPropertyCase                        ,0xFF87479C)    // PT_GetPropertyCaseString
NHSTUB(SetPropertyCase                        ,0xFF8746AC)    // PT_SetPropertyCaseString
NHSTUB(VbattGet                               ,0xFF822204)    
NHSTUB(GetParameterData                       ,0xFF972F60) // Guess but it seems correct. IDA incorrectly identified sub_FF97245C as GetParameterData
NHSTUB(SetParameterData                       ,0xFF972ED4) // Idem, with different address though :)
NHSTUB(IsStrobeChargeCompleted                ,0xFF8DB534)


// these (open, write, close) are educated guesses but not 100% certain
NHSTUB(open                                   ,0xFF819F68)
NHSTUB(write                                  ,0xFF81A260)
NHSTUB(close                                  ,0xFF81A018)
NHSTUB(lseek                                  ,0xFF825E04) // Lseek_0
NHSTUB(read                                   ,0xFF81A200) // Read

NHSTUB(Fopen_Fut                              ,0xFF825668)
NHSTUB(Fwrite_Fut                             ,0xFF8257A8)
NHSTUB(Fclose_Fut                             ,0xFF8256A8)
NHSTUB(Fread_Fut                              ,0xFF825754)
NHSTUB(Fseek_Fut                              ,0xFF825848)

NHSTUB(Remove                                 ,0xFF825D0C)
NHSTUB(rename                                 ,0xFF825D98)

NHSTUB(stat                                   ,0xFF825ED0)
NHSTUB(openfastdir                            ,0xFFA2786C)
NHSTUB(readfastdir                            ,0xFFA27900)
NHSTUB(closefastdir                           ,0xFFA279D0)

NHSTUB(opendir                                ,0xFFA2786C) // OpenFastDir
NHSTUB(ReadFastDir                            ,0xFFA27900)
NHSTUB(closedir                               ,0xFFA279D0) // CloseFastDir
NHSTUB(mkdir                                  ,0xFF826068)

NHSTUB(GetDrive_ClusterSize                   ,0xFF856D08)
NHSTUB(GetDrive_TotalClusters                 ,0xFF856D3C)
NHSTUB(GetDrive_FreeClusters                  ,0xFF856DA8)

NHSTUB(LockMainPower                          ,0xFF877D30)
NHSTUB(UnlockMainPower                        ,0xFF877C8C)

NHSTUB(GetCurrentAvValue                      ,0xFF952D94)
NHSTUB(MoveFocusLensToDistance                ,0xFFA0D41C)
NHSTUB(MoveZoomLensWithPoint                  ,0xFF957B34)
NHSTUB(SetZoomActuatorSpeedPercent            ,0xFF957C70)

NHSTUB(malloc                                 ,0xFF813A2C)
NHSTUB(free                                   ,0xFF813B00)
NHSTUB(FreeUncacheableMemory                  ,0xFF82AD08)
NHSTUB(AllocateUncacheableMemory              ,0xFF82ACD4)

NHSTUB(rand                                   ,0xFF81E76C)
NHSTUB(srand                                  ,0xFF81BCEC)
NHSTUB(_log10                                 ,0xFFA92E10)
NHSTUB(_pow                                   ,0xFFA92F80)
NHSTUB(_log                                   ,0xFFA93ECC)
NHSTUB(_sqrt                                  ,0xFFA95234)

NHSTUB(qsort                                  ,0xFF9CA224)

NHSTUB(strstr                                 ,0xFF9C9D44)
NHSTUB(strncpy                                ,0xFF81E5C0)
NHSTUB(strrchr                                ,0xFF8B31D8)
NHSTUB(strncmp                                ,0xFF8B3168)
NHSTUB(strchr                                 ,0xFF8B31B4)
NHSTUB(strcat                                 ,0xFF8B312C)
NHSTUB(strtol                                 ,0xFF831CE4)

NHSTUB(LocalTime                              ,0xFF870604)

NHSTUB(UpdateMBROnFlash                       ,0xFF856AD0)

NHSTUB(UniqueLedOn                            ,0xFF913AF4)
NHSTUB(UniqueLedOff                           ,0xFF913B7C)

NHSTUB(SetAutoShutdownTime                    ,0xFF877E90)


NHSTUB(phySw                                  ,0xFF8235A0)
NHSTUB(phySw_p1                               ,0xFF8239A4) // called from phySw
NHSTUB(phySw_p2                               ,0xFF823244) // called when phySw_p1 returns 1
NHSTUB(NewTaskShell                           ,0xFF874268) // starts new shell on Console. GUI output?

NHSTUB(kbd_read_keys                          ,0xFF8238C8) // Called in kbd.c (originally called from phySw_p1, line 3)
NHSTUB(kbd_p1_f                               ,0xFF8239A4) // is phySw_p1
NHSTUB(kbd_p1_f_cont                          ,0xFF8239B0) // after call to kbd_read_keys
NHSTUB(kbd_p2_f                               ,0xFF823244) // is phySw_p2
NHSTUB(kbd_read_keys_r2                       ,0xFF84D3E4) // called from kbd_read_keys



// Possibly useful but not yet necessary
NHSTUB(GetCCDTemperature                      ,0xFF8504F4) // Unknown units, doesn't really seem to respond
NHSTUB(GetBatteryTemperature                  ,0xFF850564) // Unknown units, doesn't really seem to respond to frozen batteries
NHSTUB(GetOpticalTemperature                  ,0xFF8505D4) // Unknown units, doesn't really seem to respond
NHSTUB(OpenMShutter                           ,0xFFA0BE08)
NHSTUB(CloseMShutter                          ,0xFFA0BDD0)
NHSTUB(PutOutNdFilter                         ,0xFFA0BD38) // Doesn't really work on S5, sometimes crashes camera
NHSTUB(PutInNdFilter                          ,0xFFA0BD00) // Doesn't really work on S5, sometimes crashes camera
NHSTUB(SSAPI_ExtStrobeCharged                 ,0xFF8287EC) // Functionality unknown. Implied effect implemented in IsStrobeChargeCompleted



///////////
// Following functions are for dgmod
NHSTUB(GetISPitchPWM,                   0xFFA12184)
NHSTUB(GetISYawPWM,                     0xFFA12180)
NHSTUB(GetISShiftLensPitchPosition,     0xFFA12284)
NHSTUB(GetISShiftLensYawPosition,       0xFFA12288)
NHSTUB(SetISPitchPWM,                   0xFFA121B8)
NHSTUB(SetISYawPWM,                     0xFFA121CC)
NHSTUB(MoveISLensToTopLimitPosition,    0xFFA120D4)
NHSTUB(MoveISLensToBottomLimitPosition, 0xFFA120C0)
NHSTUB(MoveISLensToLeftLimitPosition,   0xFFA120AC)
NHSTUB(MoveISLensToRightLimitPosition,  0xFFA12098)
NHSTUB(MoveISLensToCentralPosition,     0xFFA12280)

NHSTUB(GetISHallDevicePitchOffset,      0xFFA120FC) // returns char
NHSTUB(GetISHallDeviceYawOffset,        0xFFA120F8) // returns char
NHSTUB(GetISHallDevicePitchGain,        0xFFA120F4) // returns char
NHSTUB(GetISHallDeviceYawGain,          0xFFA120F0) // returns char
NHSTUB(GetISGyroPitchOffset,            0xFFA12020) // returns unknown, treat as long (sub just returns 0)
NHSTUB(GetISGyroYawOffset,              0xFFA12018) // idem
NHSTUB(GetISGyroPitchGain,              0xFFA12150) // returns char
NHSTUB(GetISGyroYawGain,                0xFFA1214C) // returns char
NHSTUB(GetISLensCenterShiftAaxis,       0xFFA11FF4) // returns unknown, treat as long (sub just returns 0)
NHSTUB(GetISLensCenterShiftBaxis,       0xFFA11FFC) // idem
NHSTUB(GetISLensEViAaxis,               0xFFA1228C) // returns short
NHSTUB(GetISLensEViBaxis,               0xFFA122A0) // returns short
NHSTUB(GetISLensDampAaxis,              0xFFA122B4) // returns short
NHSTUB(GetISLensDampBaxis,              0xFFA122B8) // returns short

// Second set of IS lens controls
NHSTUB(GetISDriveAaxis,                 0xFF86035C) // short
NHSTUB(GetISDriveBaxis,                 0xFF860380) // short
NHSTUB(GetISPositionAaxis,              0xFF8603A4) // short
NHSTUB(GetISPositionBaxis,              0xFF8603C8) // short
NHSTUB(GetISHallOffsetAaxis,            0xFF8604E8) // char
NHSTUB(GetISHallOffsetBaxis,            0xFF86050C) // char
NHSTUB(GetISHallGainAaxis,              0xFF860530) // char
NHSTUB(GetISHallGainBaxis,              0xFF860554) // char
NHSTUB(GetISGyroGainAaxis,              0xFF860578) // char
NHSTUB(GetISGyroGainBaxis,              0xFF86059C) // char
NHSTUB(GetISCoefficientP_A,             0xFF8609A0) // short
NHSTUB(GetISCoefficientP_B,             0xFF860AB0) // short
NHSTUB(GetISCoefficientI_A,             0xFF860ACC) // short
NHSTUB(GetISCoefficientI_B,             0xFF860AE8) // short
NHSTUB(GetISCoefficientD_A,             0xFF860B04) // short
NHSTUB(GetISCoefficientD_B,             0xFF860B20) // short
NHSTUB(GetISPLFAaxis,                   0xFF8608B8) // short
NHSTUB(GetISPLFBaxis,                   0xFF8608D4) // short
NHSTUB(GetISLPFAaxis,                   0xFF860908) // short
NHSTUB(GetISLPFBaxis,                   0xFF860924) // short
NHSTUB(GetISDbgData,                    0xFF860620) // long but needs argument (char *)! investigate before use
NHSTUB(GetISADData,                     0xFF860694) // void but needs argument (char *)! investigate before use, just does printf and doesn't return actual data
NHSTUB(GetISDampAaxis,                  0xFF86080C) // short
NHSTUB(GetISDampBaxis,                  0xFF860828) // short
NHSTUB(GetISEViAaxis,                   0xFF860844) // short (GetISLensEViAAxis)
NHSTUB(GetISEViBaxis,                   0xFF860868) // short
NHSTUB(GetISHallOut1Amp,                0xFF8607DC) // void, just prints
NHSTUB(ISActive,                        0xFF860B3C) // unknown, complex

NHSTUB(GetWBStruct,                     0xFFA0CB8C)

NHSTUB(MuteOffPhysicalScreen,           0xFF8883D0)


NHSTUB(PostLEDMessage,                  0xFF84CF8C)

NHSTUB(TurnOnDisplay,                   0xFF888358)
NHSTUB(TurnOffDisplay,                  0xFF888370)
NHSTUB(TurnOnBackLight,                 0xFF888388)
NHSTUB(TurnOffBackLight,                0xFF8883A0)
NHSTUB(SwitchOnDisplay,                 0xFFA0FD7C)
NHSTUB(SwitchOffDisplay,                0xFFA0FD44)

NHSTUB(StopContinuousVRAMData,          0xFFA10388)

NHSTUB(GetShutterReadyStateVar,         0xFF8166D4)

NHSTUB(DispSwCon_MuteOffPhysicalScreen, 0xFF87D180)
NHSTUB(DispSwCon_DisableMute,           0xFF87CF4C)
NHSTUB(DispSw_Unlock,                   0xFF87CE58)


///////////
// FOLLOWING FUNCTION NOT FOUND, points to nullsub. Function does not exist
// where it is to be expected according to A720 firmware. Copied it from A720
// and hooked in boot.c
//NHSTUB(time, 0xFF81096C)


///////////
// The following functions were not found in the S5 firmware. They do not
// seem to be required but for some reason someone made this list.
// Point to nullsub for immediate return
// nullsub_1: 0xFF81096C (S5)
NSTUB(CreatePhysicalVram,		 0xFF81096C)
NSTUB(CreateTaskStrict,			 0xFF81096C)
NSTUB(DisableDispatch,			 0xFF81096C)
NSTUB(DisplayImagePhysicalScreen,	 0xFF81096C)
NSTUB(EnableDispatch,			 0xFF81096C)
NSTUB(ioctl,					 0xFF81096C)
NSTUB(iosDevAdd,				 0xFF81096C)
NSTUB(iosDrvInstall,			 0xFF81096C)
NSTUB(isalpha,					 0xFF81096C)
NSTUB(isdigit,					 0xFF81096C)
NSTUB(islower,					 0xFF81096C)
NSTUB(isspace,					 0xFF81096C)
NSTUB(isupper,					 0xFF81096C)
NSTUB(localtime,				 0xFF81096C)
NSTUB(MakeDirectory,			 0xFF81096C)
NSTUB(memPartAlloc,				 0xFF81096C)
NSTUB(memPartFindMax,			 0xFF81096C)
NSTUB(Mount_FileSystem,			 0xFF81096C)
NSTUB(PhySw_testgpio,			 0xFF81096C)
NSTUB(ProtectFile,				 0xFF81096C)
NSTUB(readdir,					 0xFF81096C)
NSTUB(rewinddir,				 0xFF81096C)
NSTUB(taskCreateHookAdd,			 0xFF81096C)
NSTUB(taskDeleteHookAdd,			 0xFF81096C)
NSTUB(taskIdListGet,			 0xFF81096C)
NSTUB(taskLock,				 0xFF81096C)
NSTUB(taskName,				 0xFF81096C)
NSTUB(taskResume,				 0xFF81096C)
NSTUB(taskSuspend,				 0xFF81096C)
NSTUB(taskUnlock,				 0xFF81096C)
NSTUB(utime,					 0xFF81096C)
NSTUB(Unmount_FileSystem,		 0xFF81096C)
NSTUB(UIFS_WriteFirmInfoToFile,	 0xFF81096C)
NSTUB(kbd_pwr_off,				 0xFF81096C) // Does not even exist, I think
NSTUB(kbd_pwr_on,				 0xFF81096C) // Does not even exist, I think


