//
//  GlyphMaster.h
//  Shamanization
//
//  Created by Joao Pedro da Costa Nunes on 9/6/15.
//
//

#ifndef __Shamanization__GlyphMaster__
#define __Shamanization__GlyphMaster__

#include "cocos2d.h"
#include "GlyphStroke.h"

using namespace cocos2d;
using namespace std;

class GlyphMaster {
    
    void addPoint(Point *point);
    void startStroke();
    void endStroke();
    void createTemplate();
    void createUnistrokes();
    void permuteStrokeOrders(int count);
    
public:
    
    GlyphStroke *currentStroke;
    
    PointArray *temp;
    PointArray *strokes;
    PointArray *strokeOrders;
    PointArray *unistroke;
    PointArray *permutedStrokeOrders;
    
    string name;
};

#endif /* defined(__Shamanization__GlyphMaster__) */
