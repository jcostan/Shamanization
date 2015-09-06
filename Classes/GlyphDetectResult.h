//
//  GlyphDetectResult.h
//  Shamanization
//
//  Created by Joao Pedro da Costa Nunes on 9/6/15.
//
//

#ifndef __Shamanization__GlyphDetectResult__
#define __Shamanization__GlyphDetectResult__

#include "cocos2d.h"
#include "GlyphMaster.h"

using namespace cocos2d;

class GlyphDetectResult {
    
    
public:
    
    GlyphMaster *bestMatch;
    float bestScore;
    bool sucess;    
};

#endif /* defined(__Shamanization__GlyphDetectResult__) */
