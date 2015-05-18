#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofSetCircleResolution(64);
    oneShot = false;
    
    circleLeft.setCenter(ofPoint(ofGetWidth() / 2, ofGetHeight() / 2));
    circleLeft.setRadius(130);
    circleLeft.setTarget(&circleRight);
    circleLeft.update();
    
    circleRight.setCenter(ofPoint(512, 384));
    circleRight.setRadius(150);
    circleRight.update();
}

//--------------------------------------------------------------
void ofApp::update(){
    circleRight.update();
    circleLeft.update();
    
    circleLeft.center = ofPoint(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::draw(){
    if( oneShot ){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }
    
    
    
    circleLeft.draw();
    circleRight.draw();
    
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
