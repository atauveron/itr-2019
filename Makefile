.SUFFIXES:
.SUFFIXES:.cpp .h .o

SDIR= src
_SRC= timespec.cpp \
	Calibrator.cpp \
	Chrono.cpp \
	Countdown.cpp \
	CpuLoop.cpp \
	Looper.cpp \
	Timer.cpp \
	PeriodicTimer.cpp \
	PosixThread.cpp \
	Thread.cpp \
	Mutex.cpp \
	Semaphore.cpp \
	main.cpp
_DEP=	timespec.h \
	Calibrator.h \
	Chrono.h \
	Countdown.h \
	CpuLoop.h \
	Looper.h \
	Timer.h \
	PeriodicTimer.h \
	PosixThread.h \
	Thread.h \
	Mutex.h \
	Semaphore.h \
	Fifo.h
SRC= $(patsubst %,$(SDIR)/%,$(_SRC))
DEP= $(patsubst %,$(SDIR)/%,$(_DEP))

ODIR= build
_OBJ= $(_SRC:.cpp=.o)
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))

BDIR=	bin
_BIN= a.out
BIN= $(patsubst %,$(BDIR)/%,$(_BIN))

# CMP= g++
CMP= ~/ITR/Zed/cross/bin/arm-linux-g++
OPT= -std=c++11 -g -Wall -fbounds-check
LIB= -lrt -pthread

all: obj bin $(BIN)

$(BIN): $(OBJ) $(DEP)
	$(CMP) $(OPT) -o $@ $(OBJ) $(LIB)
	@echo Build successful

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp $(DEP)
	$(CMP) $(OPT) -o $@ -c $< $(LIB)

obj:
	@mkdir -p $(ODIR)

bin:
	@mkdir -p $(BDIR)

.PHONY: clean

clean:
	$(RM) $(OBJ) $(BIN)
	$(RM) -r $(ODIR) $(BDIR)

