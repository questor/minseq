
//version 0.5

#pragma once

#define LINUX

#ifdef LINUX
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

// VT100 codes:
#define ioClearScreen()     printf("\033[2J")

#define resetAttributes() printf("\033[0m")
#define enableBold()      printf("\033[1m")
#define disableBold()	  printf("\033[21m")
#define enableDim()		  printf("\033[2m")
#define disableDim()	  printf("\033[22m")
#define enableUnderline() printf("\033[4m")
#define disableUnderline() printf("\033[24m")
#define enableBlink()	  printf("\033[5m")
#define disableBlink()    printf("\033[25m")
#define enableInvert()	  printf("\033[7m")
#define disableInvert()   printf("\033[27m")

#define setForeground(x)  printf("\033[3%im", x)
#define setBackground(x)  printf("\033[4%im", x)

#define saveScreen()      printf("\033[?47h")
#define restoreScreen()   printf("\033[?47l")

#define cursorHome()      printf("\033[H")		//move cursor to 0,0
#define cursorMove(y,x)   printf("\033[%i;%iH", y, x)
#define cursorHide()      printf("\033[?25l")
#define cursorShow()      printf("\033[?25h")
#define cursorSave()      printf("\033[s")
#define cursorRestore()   printf("\033[u")

#define sendNewline()     printf("\n")

#define colorBlack        0
#define colorRed     	  1
#define colorGreen  	  2
#define colorYellow  	  3 
#define colorBlue    	  4
#define colorMagenta 	  5
#define colorCyan    	  6
#define colorWhite   	  7

#include <vector>
#include <string>

class TextIO {
public:
	TextIO() {
		getSize(windowWidth, windowHeight);
		cursorPosInList = 0;
		posX = 1;
		posY = 1;
		markRedraw();
	}

	void moveCursorUp() {
		cursorPosInList -= 1;
		markRedraw();
	}
	void moveCursorDown() {
		cursorPosInList += 1;
		markRedraw();
	}

	void setCursor(int x, int y) {
		cursorMove(y, x);
	}
	void clearScreen() {
		ioClearScreen();
	}

	int getListCursorPos() {
		//be careful, is only checked against bounds in the doListSelection!
		return cursorPosInList;
	}

	void doListSelection(std::vector<std::string> &listToUse) {
		if(redrawNeeded == false)
			return;
		redrawNeeded = false;

		ioClearScreen();

		if(cursorPosInList < 0)
			cursorPosInList = 0;
		if(cursorPosInList > listToUse.size()-1)
			cursorPosInList = listToUse.size()-1;

		const int numberVisibleListElements = 5;

		int numberElementsToPrint = numberVisibleListElements;
		if(listToUse.size() < numberElementsToPrint)
			numberElementsToPrint = listToUse.size();

		int startToPrint = cursorPosInList - numberElementsToPrint / 2;
		if(startToPrint+numberElementsToPrint > listToUse.size()) {
			startToPrint -= startToPrint+numberElementsToPrint-listToUse.size();
		}
		if(startToPrint < 0)
			startToPrint = 0;

		for(int i=0; i<numberElementsToPrint; ++i) {
			cursorMove(posY+i, posX);
			if(startToPrint + i == cursorPosInList) {
				enableInvert();
			}
			
			printf("%s", listToUse[startToPrint+i].c_str());

			if(startToPrint + i == cursorPosInList) {
				disableInvert();
			}
		}
		sendNewline();			//buffering of stdout will be flushed when a newline is seen
	}

	void markRedraw() {
		redrawNeeded = true;
	}

protected:
	void getSize(int &width, int &height) {
#ifdef LINUX
		struct winsize ws;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
		width = ws.ws_col;
		height = ws.ws_row;
#endif
#ifdef _WIN32
	    CONSOLE_SCREEN_BUFFER_INFO csbi;
	    int columns, rows;

	    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif
	}

	int posX, posY;
	int viewWidth, viewHeight;
	int windowWidth, windowHeight;
	int cursorPosInList;
	bool redrawNeeded;
};

