#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../core/Game.h"
#include <vector>

class Color{
    public:
        unsigned char r,g,b;
        const Color operator+ (const Color& operandeDroite);
        Color(unsigned int _r=0, unsigned int _g=255, unsigned int _b=0);
        ~Color();
};

class Background {
    public:
    int nbColors;
    std::vector <Color> tabColor;
    float velosity;

    Background();
    ~Background();
    void initBackground();
  
    private:

};

#endif
