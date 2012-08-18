
#
# Config macros
#
TPLIB_MAJOR_VER = 1
TPLIB_MINOR_VER = 0.1
TPLIB_VER = $(TPLIB_MAJOR_VER).$(TPLIB_MINOR_VER)

#
# Tools & flags macros
#
AR = ar
AFLAGS = rcs
CC = gcc
CFLAGS = -Wall -fPIC -I./include
CXX = g++
CXXFLAGS = -Wall -fPIC -I./include
LDFLAGS = 

#
# action macros
#
MKOBJ = $(CXX) $(CXXFLAGS) -o $@ -c $<
MKDLL = $(CXX) $(CXXFLAGS) -shared -Wl,-soname,$@ -o $@.$(TPLIB_MINOR_VER) $+
MKTEST = $(CXX) -o $@ $+ -static $(LDFLAGS) -Llib -ltp

#
# Macro's to be lazy.
#
OBJECTS = obj/RuntimeConfiguration.o
TESTS = obj/tests/RuntimeConfiguration

all: static shared tests

tags:
	ctags $+

clean:
	rm -rf obj/*.o
	rm -rf obj/tests/*

static: lib/libtp.a
shared: lib/libtp.so.$(TPLIB_MAJOR_VER)

# Do I really need to test against both the static and shared targets? Probably...
tests: $(TESTS)
	for app in $+; do \
		echo "Running tests for `basename $$app`"; \
		env LD_LIBRARY_PATH=./lib ./$$app ; done


lib/libtp.a: $(OBJECTS)
	$(AR) $(AFLAGS) $@ $+

lib/libtp.so.$(TPLIB_MAJOR_VER): $(OBJECTS)
	$(MKDLL)

.PHONEY: clean tests

#
# House keeping
#

obj/RuntimeConfiguration.o: src/RuntimeConfiguration.cc
	$(MKOBJ)

obj/tests/RuntimeConfiguration.o: tests/RuntimeConfiguration.cc
	$(MKOBJ)

obj/tests/RuntimeConfiguration: obj/tests/RuntimeConfiguration.o
	$(MKTEST)

obj/Log.o: src/Log.cc
	$(MKOBJ)

obj/LogSink.o: src/LogSink.cc
	$(MKOBJ)
