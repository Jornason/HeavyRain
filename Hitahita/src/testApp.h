#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
//#include "ofxControlPanel.h"
#include "ofxGui.h"

class testApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void drawPointCloud();
    
    void keyPressed (int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    ofxKinect kinect;
    //    int angle;
    ofEasyCam easyCam;
    //    ofxControlPanel gui;
    ofxPanel gui;
    ofImage kinectCam;
    ofImage kinectDepth;
    
    ofParameter<bool> pick_color;
    ofParameter<float> angle;
    ofParameter<float> point_size;
    ofParameter<int> step;
    ofParameter<float> posz;
    ofParameter<float> thresh;
    ofParameter<int> suimen;
     ofParameter<int> suimenX;
     ofParameter<int> suimenZ;
    
    ofBoxPrimitive box; //水面の直方体
    ofLight light;
    
};
