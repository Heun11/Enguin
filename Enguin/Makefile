LIBNAME=Enguin
LIBRARY=lib$(LIBNAME).a
CODEDIR=.
ROOTDIR=.

#$(info [${var}])

CC=gcc
OPTFLAGS=-O0
DEPFLAGS=-MP -MD
INCDIRS:=$(shell find $(ROOTDIR) -type d)
CFLAGS=-Wall -Werror -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPTFLAGS) $(DEPFLAGS)
CFILES:=$(shell find $(CODEDIR) -name '*.c')

OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

all: $(LIBRARY)
	@echo $(OBJECTS)

$(LIBRARY): $(OBJECTS)
	ar -rcs $(LIBRARY) $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) $(DEPFILES)

see:
	find . -name '*'

-include $(DEPFILES)
