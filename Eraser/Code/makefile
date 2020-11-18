BIN = Labb1

F_CPU = 16000000UL
MCU = atmega328p
BAUDRATE = 115200
PROGRAMMER = stk500v2
PORT = /dev/ttyS4

CC = avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
AVRSIZE=avr-size

SOURCES = \
		  main.c \
		  bluetooth.c \
		  timer.c \
		  driver.c \
		  led.c

CFLAGS = -g -Wall -pedantic -O2 -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c# Kompilator?aggor
LDFLAGS = -mmcu=$(MCU) # Länkar?aggor

OBJS = $(SOURCES:.c=.o)
OUT=${BIN}.elf ${BIN}.hex ${BIN}.lss

flash: all # Flasha/programmera arduinon – bygger vid behov
	avrdude -F -V -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUDRATE) -U flash:w:$(BIN).hex -v


all: $(OUT) # Bygg rubbet, men ?asha inte till target
    		# *.map Minneskon?guration = metadata
    		# *.elf Exekverbar binär, kan tryckas in i en debugger/analysverktyg = maskinkod + data + debugsymboler
    		# *.hex ELF strippad och konverterad till ihex – ?ashas till arduinon = maskinkod + data
    		# *.lss ELF’en översatt till assembler (!) + minnessegment + minnesinnehåll = assembler + data + metadata

$(OBJS): makefile

#%.o: %.c # Kompilerar .c filer till .o filer (-o $@ says to put the output of the compilation in the file named on the left side of the :)
#	$(CC) $(CFLAGS) $< -o $@

%.o:%.c
	$(COMPILE.c) -MD -o $@ $<
	@cp $*.d $*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS) # Länka
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

clean: # Rensa upp byggkatalogen
	@echo " Cleaning...";
	rm -f $(OUT) $(OBJS) *.map *.P *.out 
