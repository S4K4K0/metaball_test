#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofSetCircleResolution(64);
    oneShot = false;
    
    movingCircle.setCenter(ofPoint(mouseX, mouseY));
    movingCircle.setRadius(16);
    movingCircle.update();
    
    static const int num = 256;
    
    for (int i = 0; i < num; i++) {
        fixedCircles.push_back(ofxMetaball2d(ofPoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight())), ofRandom(2, 16), &movingCircle));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    movingCircle.center = ofPoint(mouseX, mouseY);
    movingCircle.update();

    for (int i = 0; i < fixedCircles.size(); i++) {
        fixedCircles[i].update();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if( oneShot ){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }

    movingCircle.draw();
    for (int i = 0; i < fixedCircles.size(); i++) {
        fixedCircles[i].draw();
    }

    ofDrawBitmapStringHighlight("framerate: " + ofToString(ofGetFrameRate()), ofPoint(10,10));
    
    if (oneShot) {
        ofEndSaveScreenAsPDF();
        oneShot = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        oneShot = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
