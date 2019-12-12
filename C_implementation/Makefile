ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

C_COMPILER=gcc
ifeq ($(shell uname -s), Darwin)
C_COMPILER=clang
endif

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

TARGET_BASE=AllTests
TARGET = $(TARGET_BASE)$(TARGET_EXTENSION)

SRC_FILES=\
	unity/src/unity.c \
	unity/extras/fixture/src/unity_fixture.c \
	src/CircularBuffer.c \
	test/CircularBuffer_Test.c \
	test/test_runners/CircularBuffer_TestRunner.c \
	test/test_runners/AllTests.c

INC_DIRS=-Iunity/src -Iunity/extras/fixture/src -Iinclude

SYMBOLS=-DUNITY_FIXTURE_NO_EXTRAS

all: clean default

default:
	@$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) -o $(TARGET)
	@-./$(TARGET) # -v

clean:
	$(CLEANUP) $(TARGET)

ci: CFLAGS += -Werror
ci: default
