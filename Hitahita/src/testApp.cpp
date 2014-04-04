#include "testApp.h"

void testApp::setup() {
    //画面設定
    ofBackgroundHex(0x000000);
    ofSetFrameRate(60);
    
    // Kinect初期設定
    // 深度とRGB情報のずれを補整
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    // 角度を調整(0度に)
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    // GUI
    /*
     gui.setup("ofxKinect Point Cloud", 0, 0, 400, ofGetHeight());
     gui.addPanel("Kinect Params", 1);
     gui.setWhichPanel(0);
     gui.setWhichColumn(0);
     gui.addToggle("Pick Color", "pick_color", false);
     gui.addSlider("Camera Tilt Angle", "angle", 0, -40, 40, true);
     gui.addSlider("Point size", "point_size", 2.0, 0.0, 10.0, false);
     gui.addSlider("Step size", "step", 2, 1, 10, true);
     gui.addSlider("Z position", "posz", -1000, -4000, 0, true);
     gui.addSlider("Z threshold", "thresh", 1000, 0, 4000, true);
     gui.addPanel("Kinect Images", 1);
     gui.setWhichPanel(1);
     gui.setWhichColumn(0);
     gui.addDrawableRect("Kinect Cam", &kinectCam, 320, 240);
     gui.addDrawableRect("Kinect Depth", &kinectDepth, 320, 240);
     gui.loadSettings("controlPanelSettings.xml");
     */
    gui.setup();
    gui.add(pick_color.set("pick color", true));
    gui.add(angle.set("angle", 0, -40, 40));
    gui.add(point_size.set("point size", 3.65, 0, 10.0));
    gui.add(step.set("step",3,1,10));
    gui.add(posz.set("Z position", -1000, -4000, 0));
    gui.add(thresh.set("Z thresh", 4000, 0, 10000));
     gui.add(suimen.set("water surface", 400, 0, 480));
    
}

void testApp::update() {
    kinect.setCameraTiltAngle(angle);
    // Kinect更新
    kinect.update();
    //    gui.update();
    if (kinect.isFrameNew()) {
        kinectCam.setFromPixels(kinect.getPixels(), kinect.width, kinect.height, OF_IMAGE_COLOR);
        kinectDepth.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
    }
}

void testApp::draw() {
    // ドラッグで視線を変更できるように(ofEasyCam)
    easyCam.begin();
    //ポイントクラウドの描画
    drawPointCloud();
    easyCam.end();
    gui.draw();
}

void testApp::drawPointCloud() {
    // 画面の幅と高さ
    int w = 640;
    int h = 480;
    // メッシュを生成
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // 設定した間隔で、画面の深度情報と色を取得してメッシュの頂点に設定
    //    int step = gui.getValueI("step");
    for(int y = 0; y < h; y += step) {
        for(int x = 0; x < w; x += step) {
            if(kinect.getDistanceAt(x, y) < thresh) {
                if (pick_color) {
                    if( y > suimen){
                     //   mesh.addColor(kinect.getColorAt(x,y));
                        mesh.addColor(ofFloatColor(0,0,255));
                    }else{
                        mesh.addColor(kinect.getColorAt(x,y));
                    }
                } else {
                    mesh.addColor(ofFloatColor(255,255,255));
                }
                mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
            }
        }
    }
    
    // メッシュの頂点を描画
    glPointSize(point_size);
    ofPushMatrix();
    ofScale(1, -1, -1);
    ofTranslate(0, 0, posz);
    glEnable(GL_DEPTH_TEST);
    mesh.drawVertices();
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
}

void testApp::exit() {
    // Kinect終了
    kinect.close();
}

void testApp::keyPressed (int key) {
    if (key == ' ') {
        //        gui.toggleView();
        easyCam.reset();
    }
    if (key == 'f') {
        ofToggleFullscreen();
    }
}

void testApp::mouseDragged(int x, int y, int button){
    //   	gui.mouseDragged(x, y, button);
}

void testApp::mousePressed(int x, int y, int button){
    //    	gui.mousePressed(x, y, button);
}

void testApp::mouseReleased(int x, int y, int button){
    //   gui.mouseReleased();
}

void testApp::windowResized(int w, int h)
{}
