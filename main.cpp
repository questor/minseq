
#include "rang/rang.hpp"

using namespace rang;

struct {
	enum EditScreenMode {
		eSong, eChain, ePhrase;
	};
	EditScreenMode mEditScreenMode;
} gEditorState;

void drawMenu(int x, int y) {
	rang::cursor::setPos(x,y);
	
	if(gEditorState.mEditScreenMode == gEditorState::eSong) {
		std::ccout << rang::bg::blue << rang::fg::bright_white;
	} else {
		std::ccout << rang::bg::black << rang::fg::bright_white;
	}
	std::ccout << "S";		//Song
	if(gEditorState.mEditScreenMode == gEditorState::eChain) {
		std::ccout << rang::bg::blue << rang::fg::bright_white;
	} else {
		std::ccout << rang::bg::black << rang::fg::bright_white;
	}
	std::ccout << "C";		//Chain
	if(gEditorState.mEditScreenMode == gEditorState::ePhrase) {
		std::ccout << rang::bg::blue << rang::fg::bright_white;
	} else {
		std::ccout << rang::bg::black << rang::fg::bright_white;
	}
	std::ccout << "P";		//Phrase
}

int main(int argc, char **argv) {
	rang::cursor::setVisible(false);

	gEditorState.mEditScreenMode = gEditorState::ePhrase;

	rang::cursor::setPos(10,10);
	std::cout << rang::bg::blue << "test" << rang::bg::reset;

	return 0;
}