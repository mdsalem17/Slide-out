#include "Background.h"

const Color Color::operator + (const Color& operandeDroite){
    Color resultatAddition;
    resultatAddition.r = r + operandeDroite.r;
    resultatAddition.g = g + operandeDroite.g;
    resultatAddition.b = b + operandeDroite.b;
    return resultatAddition;
}

Color::Color(unsigned int _r, unsigned int _g, unsigned int _b){
        r=_r;
        g=_g;
        b=_b;
}

Color::~Color(){
    r=0;
    g=0;
    b=0;
}

Background::Background(){
    nbColors=5;
    initBackground();
}

void Background::initBackground(){
    
    Color c;
    Color cplus;
    
    c.r = rand() % 255;
    c.g = rand() % 255;
    c.b = rand() % 255;
    
    tabColor.push_back(c);
    
    for(unsigned int i = 1 ; i < nbColors ; i++){
        cplus.r = rand() % 50;
        cplus.g = rand() % 20;
        cplus.b = rand() % 50;
        tabColor.push_back(c+cplus);
    }
}

Background::~Background(){
	nbColors=0;
}
