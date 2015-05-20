//
//  metaball.cpp
//  metaballTest01
//
//  Created by Koji Sakai on 2015/02/26.
//
//
// drawing routine was ported from metaball_oldUI.jsx

// ToDo
// ターゲットポインタを可変長配列に

#include "metaball.h"

float ofxMetaball2d::threshold = 30;

ofxMetaball2d::ofxMetaball2d(){
    center = ofVec2f(0, 0);
    radius = 0.0;
    target = NULL;
    update();
}

ofxMetaball2d::ofxMetaball2d(ofPoint _center, float _radius, ofxMetaball2d * _target = NULL){
    center = _center;
    radius = _radius;
    target = _target;
    update();
}

void ofxMetaball2d::update(){
    path.clear();
    path.setCircleResolution(64);
    path.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    path.setFillColor(ofColor(255));
    path.circle(center, radius);
    
    if (target != NULL) {
        cDist = center.distance(target->center);
        bDist = cDist - (radius + target->radius);
        avrRadius = (radius + target->radius) / 2;
        
        if (bDist < avrRadius) {
            ofPoint o1 = center;
            ofPoint o2 = target->center;
            float r = avrRadius;
            float r1 = radius;
            float r2 = target->radius;
            float d = cDist;
            
            if (r1 == 0 || r2 == 0) return;
            if (d <= abs(r1 - r2)) return;
            if (d > r1 + r2) {
                float r3 = 2 * (r1 - r2);
                float dr = d * d + r1 * r1 - r2 * r2;
                float r4 = equation2_min(r3 * r3,
                                         2 * dr * r3 - 8 * d * d * r1,
                                         dr * dr - 4 * d * d * r1 * r1);
                if (r4 != 0) {
                    r = MAX(abs(r4) * 1.1, r);
                }
            }
            float ot1 = atan2(o2.y - o1.y, o2.x - o1.x);
            float ot2 = ot1 + PI;
            float t = 2 * (r * (r + r1 + r2) + r1 * r2);
            if (t == 0) return;
            t = acos((2 * r * (r + r1 + r2) + (r1 * r1 + r2 * r2 - d * d)) / t);
            if (isnan(t)) return;
            
            float rr1 = r + r1;
            float rr2 = r + r2;
            float t2 = acos( (d * d + rr1 * rr1 - rr2 * rr2) / (2 * d * rr1) );
            float t3 = PI - t2 - t;
            
            float h = getHandleLengthBase(t) * r;
            
            ofPoint bezierPnt[8];
          
            bezierPnt[0] = setPnt(o1, ot1 - t2, r1);
            bezierPnt[1] = setPnt(bezierPnt[0], ot1 - t2 + HALF_PI, h);
            bezierPnt[3] = setPnt(o2, ot2 + t3, r2);                        // anchor
            bezierPnt[2] = setPnt(bezierPnt[3], ot2 + t3 - HALF_PI, h);     // handle
            bezierPnt[4] = setPnt(o2, ot2 - t3, r2);
            bezierPnt[5] = setPnt(bezierPnt[4], ot2 - t3 + HALF_PI, h);
            bezierPnt[7] = setPnt(o1, ot1 + t2, r1);                        // anchor
            bezierPnt[6] = setPnt(bezierPnt[7], ot1 + t2 - HALF_PI, h);     // handle
            
            path.moveTo(bezierPnt[0]);
            path.bezierTo(bezierPnt[1], bezierPnt[2], bezierPnt[3]);
            path.lineTo(bezierPnt[4]);
            path.bezierTo(bezierPnt[5], bezierPnt[6], bezierPnt[7]);
            path.close();
        }
    } else {
        path.close();
    }
    
}

void ofxMetaball2d::draw(){
    path.draw();
}

void ofxMetaball2d::setCenter(ofPoint _center) {
    center = _center;
    update();
}

void ofxMetaball2d::setRadius(float _radius) {
    radius = _radius;
    update();
}

ofPoint ofxMetaball2d::getCenter(){
    return center;
}

void ofxMetaball2d::setTarget(ofxMetaball2d *_target){
    target = _target;
    update();
}



ofPoint ofxMetaball2d::setPnt(ofPoint _center, float _angle, float _dist){
    return ofPoint(_center.x + cos(_angle) * _dist,
                   _center.y + sin(_angle) * _dist );
}

float ofxMetaball2d::equation2_min(float a, float b, float c){
    if(a == 0) return b == 0 ? 0 : -c / b;
    a *= 2;
    float d = b * b - 2 * a * c;
    if (d < 0) return;
    float rd = sqrt(d);
    if (d > 0) {
        return MIN((-b + rd) / a, (-b - rd) / a);
    } else {
        return -b / a;
    }
}

float ofxMetaball2d::getHandleLengthBase(float theta){
    return 4 / 3 * (1 - cos( theta / 2 )) / sin( theta / 2 );
    
}








