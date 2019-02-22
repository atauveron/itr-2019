.SUFFIXES:
.SUFFIXES:.cpp .h .o

SDIR= src
_SRC= timespec.cpp \
	main.cpp
_DEP=	timespec.h
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
OPT= -g -Wall -fbounds-check
LIB= -lrt

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

