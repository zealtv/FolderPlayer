#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "sequence.h"



class ofApp: public ofBaseApp
{
public:
  void setup();
  void update();
  void exit();
  void draw();
  void keyPressed(int key);
  
  int framerate;
  
  bool settingsLoaded;
  
  ofxXmlSettings xml;
  
  sequence sequence1;
  
  int sequenceCheckInterval;
  int sequenceCheckTimer;
  
  float totalFrameTime;
  float targetFrameTime;
  string sequencePath1;
  bool preserveAspect;
  
};
