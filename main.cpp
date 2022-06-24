
#include <signal.h>

#include "utils/textio.h"
#include "utils/linuxinput.h"


struct EditorState {
	enum EditScreenMode {
		eSong, eChain, ePhrase
	};
	EditScreenMode mEditScreenMode;
} gEditorState;

void drawMenu(int x, int y) {
	cursorMove(x, y);
	
	setForeground(colorWhite);
	if(gEditorState.mEditScreenMode == EditorState::eSong) {
		setBackground(colorBlue);
	} else {
		setBackground(colorBlack);
	}
	printf("S");			//Song
	if(gEditorState.mEditScreenMode == EditorState::eChain) {
		setBackground(colorBlue);
	} else {
		setBackground(colorBlack);
	}
	printf("C");			//Chain
	if(gEditorState.mEditScreenMode == EditorState::ePhrase) {
		setBackground(colorBlue);
	} else {
		setBackground(colorBlack);
	}
	printf("P");			//Phrase
}

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

int main(int argc, char **argv) {
    set_conio_terminal_mode();

    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
    // for that.
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

	gEditorState.mEditScreenMode = EditorState::ePhrase;

	ioClearScreen();

    while (!interrupt_received) {
    	drawMenu(10, 10);
        if (kbhit()) {
            int c = getch();
            if (c == 'q' || c == 'Q') {
                interrupt_received = true;
            }
        }
    }

	return 0;
}

