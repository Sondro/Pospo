#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(40);
    
    
    ui.setup(ofGetWidth()-260, 0, 260, ofGetHeight());
    
    filters.push_back(new FilterBasic());
    filters.push_back(new FilterChromaticAberration());
    filters.push_back(new FilterBlur());
    filters.push_back(new FilterBloom());
    filters.push_back(new FilterVignette());
    filters.push_back(new FilterGrain());
    
    original.load("init.jpg");
    original.resize(original.getWidth()/4, original.getHeight()/4);
    initFilter();
    process();
}

//--------------------------------------------------------------
void ofApp::update(){
    ui.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate((ofGetWidth()-260)/2, ofGetHeight()/2);
    ofTranslate(camera.x, camera.y);
    float sca = pow(1.5, zoom);
    ofScale(sca, sca);
    ofSetColor(80);
    ofDrawRectangle(-2, -2, 4, 4);
    ofSetColor(255);
    if(viewOriginal) {
        if(original.isAllocated())
            original.draw(original.getWidth()*-0.5, original.getHeight()*-0.5);
    }
    else {
        if(pospo.isAllocated())
            pospo.draw(pospo.getWidth()*-0.5, pospo.getHeight()*-0.5);
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ui.draw();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '+') zoom = ofClamp(zoom+1, -5, 5);
    if(key == '-') zoom = ofClamp(zoom-1, -5, 5);
    if(key == 'r') initFilter();
    if(key == 'p') process();
    if(key == ' ') viewOriginal = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' ') viewOriginal = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(movedCamera) {
        camera.x += mouseX-ofGetPreviousMouseX();
        camera.y += mouseY-ofGetPreviousMouseY();
    }
    
    ui.mouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    movedCamera = x<ofGetWidth()-260;
    
    ui.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    movedCamera = false;
    
    ui.mouseReleased(x, y);
    updateUI();
    
    process();
}


//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
    if(x<ofGetWidth()-260) {
        zoom += scrollY*0.2;
        zoom = ofClamp(zoom, -5, 5);
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ui.setup(ofGetWidth()-260, 0, 260, ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    original.load(dragInfo.files[0]);
    initFilter();
}

void ofApp::initFilter(){
    pospo.allocate(original.getWidth(), original.getHeight());
    
    ofSetColor(255);
    for(int i = 0; i < filters.size(); i++){
        filters[i]->init(&pospo);
    }
    
    updateUI();
}

void ofApp::updateUI(){
    ui.clear();
    
    float auxHeight = 0;
    for(int i = 0; i < filters.size(); i++){
        filters[i]->layout.y = auxHeight;
        ui.addComponent(&filters[i]->layout);
        auxHeight += filters[i]->layout.getHeight();
    }
    
}

void ofApp::process(){
    ofSetColor(255);
    pospo.begin();
    original.draw(0, 0);
    pospo.end();
    for(int i = 0; i < filters.size(); i++) {
        if(filters[i]->getEnable()) filters[i]->process(&pospo);
    }
}
