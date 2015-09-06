//
//  Glyph.h
//  Shamanization
//
//  Created by Joao Pedro da Costa Nunes on 9/6/15.
//
//

#ifndef __Shamanization__Glyph__
#define __Shamanization__Glyph__

#include "cocos2d.h"

#include "GlyphMaster.h"
#include "GlyphDetectResult.h"

using namespace cocos2d;

class GlyphDetector {
    
    void addPoint(Point point);
    void addGlyph (GlyphMaster *glyph);
    void removeAllPoints();
    void reset();
    GlyphDetectResult *detect();
    
    
    
public:
    
    PointArray *points;
    PointArray *glyphs;
    int timeOutSec;
    
};

#endif /* defined(__Shamanization__Glyph__) */
