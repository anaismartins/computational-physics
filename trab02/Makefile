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
NameTrab := main_trab02

lib: $(LIBDIR)/libFC.a

$(LIBDIR)/libFC.a: $(OBJ)
	@echo make lib...
	ar ruv $@ $^
	ranlib $@

#%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a
#	@echo compiling and linking...
#	$(CC) -I src $< -o $(BINDIR)/$@ -L lib -l FC $(ROOTLIB)

trab02: $(BINDIR)/$(NameTrab).o $(LIBDIR)/libFC.a
	@echo compiling and linking...
	$(CC) -I src $< -o $(BINDIR)/$(NameTrab).exe -L lib -l FC $(ROOTLIB)

$(BINDIR)/%.o: %.C | $(INC)
	@echo compiling... $<
	$(CC) -I src -I $(ROOTINC) -c $< -o $@


####### clean

tilde := $(wildcard bin/*~)
exe := $(wildcard bin/*.exe)
obj := $(wildcard bin/*.o)
rmlib := lib/libFC.a
#$(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)

clean:
	@echo cleaning dir...
	rm -f $(obj) $(exe) $(tilde) $(rmlib)
