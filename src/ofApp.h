#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "sequence.h"
#include "ofxGui.h"



class ofApp: public ofBaseApp
{
public:
  void setup();
  void update();
  void exit();
  void draw();
  void keyPressed(int key);
  
  bool settingsLoaded;
  
  ofxXmlSettings xml;
  
  sequence sequence1;
  

  int sequenceCheckTimer;
  
  float totalFrameTime;
  float targetFrameTime;

  int framerate;
  int sequenceCheckInterval;
  string sequencePath1;
  bool bPreserveAspect;
  bool bFullscreen;

  ofxFloatSlider gFramerate;
  ofxIntSlider gRefreshInterval;
  ofxLabel gSequencePath;
  //really want some sort of savable text entry




  
};
