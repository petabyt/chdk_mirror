#315F
PLATFORMID=12639

PLATFORMOS=dryos

MEMBASEADDR=0x1900
RESTARTSTART=0x50000
MEMISOSTART=0xA6234
MEMISOSIZE=0x55000
ROMBASEADDR=0xff810000

TARGET_PRIMARY=$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/PRIMARY.BIN

PLFLAGS=-DMEMBASEADDR=$(MEMBASEADDR) -DMEMISOSTART=$(MEMISOSTART) -DMEMISOSIZE=$(MEMISOSIZE)
PLFLAGS+=-DRESTARTSTART=$(RESTARTSTART)
