IDIR = include
CXX = g++
LDFLAGS=-lm -L/usr/lib64 -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_dialog
WINCXX32 = i686-w64-mingw32-g++
WINCXX64 = x86_64-w64-mingw32-g++

CXXFLAGS = -std=c++14 -O2 -Wall -I$(IDIR)
DEBUGFLAGS = -std=c++14 -g -Wall -I$(IDIR)

ODIR = obj
SDIR = src
OUTDIR = .
DEBUGODIR = obj/Debug
DEBUGDIR = bin/Debug
WINODIR32 = obj/Windows32
WINDIR32 = bin/Windows32

WINODIR64 = obj/Windows64
WINDIR64 = bin/Windows64

GENMOD = TicTacToe BigBoard SmallBoard Cell Cursor Colors Utilities

_DEPS = 
DEPS = $(patsubst %, $(IDIR)/%.h, $(_DEPS) $(GENMOD))

_OBJ = main
OBJ = $(patsubst %, $(ODIR)/%.o, $(_OBJ) $(GENMOD))

DEBUGOBJ = $(patsubst %, $(DEBUGODIR)/%.o, $(_OBJ) $(GENMOD))

WINOBJ32 = $(patsubst %, $(WINODIR32)/%.o, $(_OBJ) $(GENMOD))
WINOBJ64 = $(patsubst %, $(WINODIR64)/%.o, $(_OBJ) $(GENMOD))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS)

$(OUTDIR)/Supertictactoe.exe: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

$(DEBUGODIR)/%.o: $(SDIR)/%.cpp $(DEPS) 
	$(CXX) -c -o $@ $< $(DEBUGFLAGS)

$(DEBUGDIR)/SuperTicTacToeDebug: $(DEBUGOBJ)
	$(CXX) -o $@ $^ $(DEBUGFLAGS) 

$(WINODIR32)/%.o: $(SDIR)/%.cpp $(DEPS) 
	$(WINCXX32) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS)

$(WINDIR32)/Supertictactoe.exe: $(WINOBJ32)
	$(WINCXX32) -o $@ $^ $(CXXFLAGS)

$(WINODIR64)/%.o: $(SDIR)/%.cpp $(DEPS) 
	$(WINCXX64) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS)

$(WINDIR64)/Supertictactoe.exe: $(WINOBJ64)
	$(WINCXX64) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

