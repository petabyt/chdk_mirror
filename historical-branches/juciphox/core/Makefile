topdir=../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

# warning: library order matters!
LDLIBS= -lgcc
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,-T,$(topdir)tools/link-boot.ld
LDOPTS+=-Wl,-N,-Ttext,$(MEMISOSTART)

all: main.bin

OBJS=entry.o nothumb.o main.o gui_draw.o gui_menu.o gui_palette.o gui_mbox.o \
     gui_reversi.o gui_debug.o gui_fselect.o gui_read.o gui.o kbd.o conf.o \
     histogram.o gui_batt.o gui_space.o gui_osd.o script.o curves.o raw.o gui_sokoban.o gui_calendar.o \
     gui_lang.o gui_bench.o gui_mpopup.o gui_grid.o motion_detector.o raw_merge.o \
     luascript.o edgeoverlay.o shot_histogram.o

gui.o: FORCE

FORCE:

nothumb.o: nothumb.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -marm -nostdinc -c -o $@ $<

main.bin: main.elf
	@echo $< \-\> $@
	$(OBJDUMP) -z -d main.elf > main.dump
	$(OBJCOPY) -O binary main.elf main.bin

main.elf: $(OBJS) $(topdir)platform/$(PLATFORM)/libplatform.a \
          $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/libplatformsub.a \
          $(topdir)lib/font/libfont.a $(topdir)lib/math/libmath.a \
          $(topdir)lib/ubasic/libubasic.a $(topdir)lib/lang/liblang.a \
          $(topdir)lib/lua/liblua.a
	@echo \-\> $@
	$(CC) $(CFLAGS) -o $@ --start-group $^  $(LDLIBS) --end-group $(LDFLAGS) $(LDOPTS)
	( $(NM) $@ | grep ' U ' > $@.syms ) && exit 1 || exit 0

	$(SIZE) $@ | tee $(topdir)size.txt
	@printf " %s-%s (%s, #%s): MEMISOSIZE used: 0x%s / %s\n" \
   $(PLATFORM) $(PLATFORMSUB) $(PLATFORMOS) $(PLATFORMID) \
   `tail -c16 $(topdir)size.txt | head -c6` $(MEMISOSIZE) >> $(topdir)bin/caminfo.txt
	rm -f $(topdir)size.txt

clean:
	rm -f $(OBJS) main.bin main.elf main.dump main.elf.syms

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
