#pragma once
#include "ofMain.h"

class sequence : public ofThread
{
public:
  void setPath( string path );
  void getNextFrame();
  void updateSequence();
  void drawFrame( float x, float y, float w, float h, bool preserveAspect = false);
  void initialize( string path );
  void initialize( string path, int slength );
  bool getIsInitialized();
  void swapSequenceBuffers();
  void getNewFrames();
  bool hasNewFrames;
  int getWidth();
  int getHeight();
  
private:
  vector<ofFile> frames;
  vector<ofFile> newFrames;
  void cleanNewFrames();
  int sequenceSize;
  int sequenceIndex;
  ofImage sequenceFrame;
  string sequencePath;
  bool isInitialized;
  void threadedFunction();

  int sequenceLength;
  
  bool forceLength;
};
