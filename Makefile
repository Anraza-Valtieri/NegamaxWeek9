CC       = cl
CFLAGS   = /nologo /c /Fo:
CXX      = cl
CXXFLAGS = /nologo /c /Fo:
LD       = link
LDFLAGS  = /nologo /out:
LDLIBS   = gdi32.lib user32.lib
RM       = del

TicTacToe2D.exe: TicTacToe2D.obj GUI.obj winbgi2.obj
	$(LD) $(LDFLAGS)TicTacToe2D.exe TicTacToe2D.obj GUI.obj winbgi2.obj $(LDLIBS)

GUI.obj: GUI.c GUI.h TicTacToe2D.h graphics2.h
	$(CC) $(CFLAGS) GUI.obj GUI.c

TicTacToe2D.obj: TicTacToe2D.c TicTacToe2D.h graphics2.h GUI.h
	$(CC) $(CFLAGS) TicTacToe2D.obj TicTacToe2D.c
	
winbgi2.obj: winbgi2.cpp graphics2.h
	$(CXX) $(CXXFLAGS) winbgi2.obj winbgi2.cpp
	
clean:
	$(RM) *.obj