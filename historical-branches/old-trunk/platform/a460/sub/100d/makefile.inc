#3149 
PLATFORMID=12617

PLATFORMOS=vxworks

MEMBASEADDR=0x1900
RESTARTSTART=0x50000
MEMISOSTART=0x95730
MEMISOSIZE=0x40000
ROMBASEADDR=0xffc00000

TARGET_PRIMARY=$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/PRIMARY.BIN

PLFLAGS=-DMEMBASEADDR=$(MEMBASEADDR) -DMEMISOSTART=$(MEMISOSTART) -DMEMISOSIZE=$(MEMISOSIZE)
PLFLAGS+=-DRESTARTSTART=$(RESTARTSTART)
