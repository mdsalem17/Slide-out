#include <Grapic.h>
using namespace grapic;


const int DIM = 9;
const int DIM_SPRITE = 32;


void init()
{
	
}




void draw()
{
	
}


int main(int , char ** )
{
	
    bool stop=false;
	winInit("SlideOut", 500,500);
	//init
	while( !stop )
    {
        backgroundColor( 100, 80, 200, 255 );
        winClear();
        //draw
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

