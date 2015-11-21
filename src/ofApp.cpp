#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
//  ofLogToFile( "log.txt", true );
  ofSetFrameRate(30);
  
  
  
  //LOAD SETTINGS
  settingsLoaded = false;
  if(xml.load("settings.xml"))
    settingsLoaded = true;
  else
    ofLog(OF_LOG_ERROR, "SETTINGS NOT FOUND");
  
  framerate = ofToInt( xml.getValue("framerate", "1" ) );
  targetFrameTime = 1.0/(float)framerate;
  ofLog(OF_LOG_NOTICE, "target frametime = " + ofToString( targetFrameTime ) + " seconds" );
  
  sequencePath1 = xml.getValue("path", "~/Desktop/redundantCapturedFrames/" );
  ofLog(OF_LOG_NOTICE, "sequence 1 path: " + sequencePath1 );
  
  sequenceCheckInterval = ofToInt( xml.getValue( "checkinterval", "666" ) );
  ofLog(OF_LOG_NOTICE, "sequence check interval = " + ofToString( sequenceCheckInterval ) + " seconds" );
  
  int sequenceForceLength = ofToInt( xml.getValue("forcelength", "300" ));
  ofLog(OF_LOG_NOTICE, "sequence force length = " + ofToString(sequenceForceLength ) + " seconds");

  sequence1.initialize(sequencePath1, sequenceForceLength);
  
  bool forceSize = ofToBool(xml.getValue("forcesize", "false"));
  if(forceSize)
  {
    ofSetFullscreen(false);
    ofSetWindowShape(sequence1.getWidth(), sequence1.getWidth());
  }
  


  totalFrameTime = 0;
  preserveAspect = false;
}






//------------------------------------------------------------------------------
void ofApp::update()
{
  if(sequence1.hasNewFrames)
  {
    sequence1.swapSequenceBuffers();
  }
}




//------------------------------------------------------------------------------
void ofApp::draw()
{
  ofClear(126);
  
  if(sequence1.getIsInitialized())
    sequence1.drawFrame( 0.0, 0.0, ofGetWidth(), ofGetHeight(), preserveAspect);
  
  
  if(ofGetElapsedTimeMillis() - sequenceCheckTimer > (float)sequenceCheckInterval * 1000.0)
    sequence1.getNewFrames();
  
  
  totalFrameTime += ofGetLastFrameTime();
  
  
  if(totalFrameTime > targetFrameTime){
    sequence1.getNextFrame();
    totalFrameTime = 0;
  }
  
}




//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
  if(key == 'r')
    sequence1.getNewFrames();

  if(key == 'a')
      preserveAspect = !preserveAspect;

  if(key == 'f')
  {
      ofSetFullscreen(false);
      ofSetWindowShape(sequence1.getWidth(), sequence1.getWidth());
  }

  if(key == 'F')
      ofSetFullscreen(true);

}



//--------------------------------------------------------------
void ofApp::exit()
{
  ofLogWarning("Exit called at " + ofGetTimestampString());

}




