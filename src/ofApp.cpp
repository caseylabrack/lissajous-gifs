#include "ofApp.h"
#include "gif.h"

using namespace glm;

GifWriter g;

void ofApp::randomize () {
	freqX = ceilf(ofRandom(24));
	freqY = ceilf(ofRandom(24));
	modX = 	ceilf(ofRandom(24));
	modY = 	ceilf(ofRandom(24));
}

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetFrameRate(30);
	randomize();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	
}

void ofApp::drawVertFromIndex (float i) {
	ofCurveVertex(
		sin(i * freqX + ofDegToRad((float)(ofGetFrameNum()*4))) * cos(i * modX) * ofGetWidth()/2,
		sin(i * freqY) * cos(i * modY) * ofGetHeight()/2
	);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::white);
	
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofNoFill();  
	ofSetColor(0, 0, 0, 255);

	ofBeginShape();	
	float i = 0;
	drawVertFromIndex(i); // control point
	for (i = 0; i < PI * 2; i += PI * 2 / 360) drawVertFromIndex(i);
	drawVertFromIndex(i); // control point
	ofEndShape();
	ofPopMatrix();
	
	if(saving) {
		if(cFrame < numFrames) {
			screen.grabScreen(0,0,ofGetWidth(),ofGetHeight());
			GifWriteFrame(&g, screen.getPixels().getData(), ofGetWidth(), ofGetHeight(), 3);
			cFrame++;
		} else {
			GifEnd(&g);
			saving = false;
			cFrame = 0;
		}

		ofSetColor(ofColor::red);
		ofDrawBitmapString("saving...", 10, 20);		
	}
	
    
    ofSetColor(ofColor::black);
	ofDrawBitmapString(
		"freqX: " + ofToString(freqX) + 
		" freqY: " + ofToString(freqY) + 
		" modX: " + ofToString(modX) + 
		" modY: " + ofToString(modY), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case OF_KEY_LEFT:
		freqX = freqX < 25 ? freqX + 1 : 0;
		break;
		
		case OF_KEY_RIGHT:
		freqY = freqY < 25 ? freqY + 1 : 0;
		break;
		
		case OF_KEY_UP:
		modX = modX < 25 ? modX + 1 : 0;
		break;

		case OF_KEY_DOWN:
		modY = modY < 25 ? modY + 1 : 0;
		break;
		
		case 'r':
		randomize();
		break;
		
		case ' ':
		if(!saving) {
			saving = true;
			GifBegin(	&g, 
						ofToDataPath("lissajous_" + 
						ofToString(freqX) + "_" + 
						ofToString(freqY) + "_" + 
						ofToString(modX) + "_" + 
						ofToString(modY) + 
						".gif").c_str(), 
						ofGetWidth(), ofGetHeight(), 3
					);			
		}
		break;
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	randomize();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
