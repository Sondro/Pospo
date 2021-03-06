
#ifndef Globals_h
#define Globals_h

#include "ofMain.h"

class Globals {
public:
    static Globals* Instance();
    void init(ofFbo * ori);
    
    ofFbo * pass1, * pass2, * pass3;
    ofTrueTypeFont * uiFontTitle, * uiFontValue;
    
    int menuSize = 480;
protected:
    Globals();
    Globals(const Globals &);
    Globals &operator=(const Globals &);
private:
    static Globals * instance;
};

#endif
