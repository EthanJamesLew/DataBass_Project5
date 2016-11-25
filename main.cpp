#include "song.h"
#include "songtui.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  


int main(int argc, char* argv[])
{
	SongTUI tui = SongTUI();
	tui.renderMenu();
	tui.mainloop();
	tui.save();
	_CrtDumpMemoryLeaks();
	return 0;
}