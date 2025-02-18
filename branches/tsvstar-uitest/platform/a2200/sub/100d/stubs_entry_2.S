#include "stubs_asm.h"

#define NULLSUB 0xFF810B24

// Not found
//NHSTUB(kbd_pwr_off,					NULLSUB) // automaticaly found now
NHSTUB(kbd_pwr_on,          		NULLSUB)

// Override stubs_entry.S
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFA9BB08)
NHSTUB(MakeAFScan,					0xFF8DA094)
//NHSTUB(mkdir,						0xFF837218) // automaticaly found now

NHSTUB(LockAndRefresh,				0xFF8A46A0)
NHSTUB(UnlockAndRefresh,			0xFF8A4704)

//NHSTUB(SetFileAttributes,			0xFFB370D8) // automaticaly found now

NHSTUB(platformsub_kbd_fetch_data,	0xFF8602B4)

