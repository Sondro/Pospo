#ifndef FilterBlur_h
#define FilterBlur_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"

class FilterBlur : public Filter {
public:
    
    FilterBlur();
    
    void process(ofFbo * image);
    
    ofShader blurX, blurY;
    UISlider amount;
};

#endif
