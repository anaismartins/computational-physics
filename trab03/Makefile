# Makefile

BINDIR := bin
LIBDIR := lib

CC := g++ -std=c++11

# src/ (declaracoes de funcoes, de classes + codigo)
# main/ (programas principais)
# bin/ (temporarios, .o, .exe)
# lib/ (bibliotecas) biblioteca FC

# making library
# - static: .a
# - shareable: .so

VPATH = main:src

ROOTLIB := $(shell root-config --libs)
ROOTINC := $(shell root-config --incdir)

SRC := $(wildcard src/*.C)
OBJ := $(patsubst %.C, $(BINDIR)/%.o, $(notdir $(SRC)))
INC := $(wildcard src/*.h)
NameBinTrab1 := $(BINDIR)/main_trab03_1
NameBinTrab2 := $(BINDIR)/main_trab03_2

lib: $(LIBDIR)/libFC.a

$(LIBDIR)/libFC.a: $(OBJ)
	@echo make lib...
	ar ruv $@ $^
	ranlib $@

#%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a
#	@echo compiling and linking...
#	$(CC) -I src $< -o $(BINDIR)/$@ -L lib -l FC $(ROOTLIB)

trab03: $(NameBinTrab1).o $(NameBinTrab2).o $(LIBDIR)/libFC.a
	@echo compiling and linking problem 1...
	$(CC) -I src $< -o $(NameBinTrab1).exe -L lib -l FC $(ROOTLIB)
	@echo compiling and linking problem 2...
	$(CC) -I src $(NameBinTrab2).o -o $(NameBinTrab2).exe -L lib -l FC $(ROOTLIB)

$(BINDIR)/%.o: %.C | $(INC)
	@echo compiling... $<
	$(CC) -I src -I $(ROOTINC) -c $< -o $@


####### clean

tilde := $(wildcard bin/*~)
exe := $(wildcard bin/*.exe)
obj := $(wildcard bin/*.o)
rmlib := $(wildcard lib/libFC.a)

clean:
	@echo cleaning dir...
	rm -f $(obj) $(exe) $(tilde) $(rmlib)
