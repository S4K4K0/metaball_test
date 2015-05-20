//
//  metaball.h
//  metaballTest01
//
//  Created by Koji Sakai on 2015/02/26.
//
//

#ifndef __metaballTest01__metaball__
#define __metaballTest01__metaball__

#include "ofMain.h"

class ofxMetaball2d{
public:
    ofxMetaball2d();
    ofxMetaball2d(ofPoint, float, ofxMetaball2d*);
    
    ofPoint center;
    float radius;
    ofxMetaball2d *target;
    static float threshold;
    ofPath path;
    
    void update();
    void draw();
    void setCenter(ofPoint);
    void setRadius(float);
    ofPoint getCenter();
    void setTarget(ofxMetaball2d*);
    float getRadius();
    
private:
    bool isAdhered = false;
    float cDist; // the center distance between target
    float bDist; // the boundary distance between target
    float avrRadius; // average radius of 2 circles
    ofPath shape;
    
    ofPoint setPnt(ofPoint _center, float _angle, float _dist);
    float equation2_min(float a, float b, float c);
    float getHandleLengthBase(float theta);
};

#endif /* defined(__metaballTest01__metaball__) */
