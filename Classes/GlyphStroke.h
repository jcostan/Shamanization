//
//  GlyphStroke.h
//  Shamanization
//
//  Created by Joao Pedro da Costa Nunes on 9/6/15.
//
//

#ifndef __Shamanization__GlyphStroke__
#define __Shamanization__GlyphStroke__

#include "cocos2d.h"

using namespace cocos2d;

class GlyphStroke {
    
    void addPoint(Point *point);
    void initWithPoints(PointArray *points);
    
public:
    
    PointArray *points;
    
};

#endif /* defined(__Shamanization__GlyphStroke__) */
