#include "ofApp.h"
#include "ofAppGLFWWindow.h"

int main()
{
  //ofSetLogLevel(OF_LOG_ERROR);
  //ofSetLogLevel(OF_LOG_VERBOSE);
  ofSetLogLevel(OF_LOG_NOTICE);
  ofSetupOpenGL(1280, 720, OF_WINDOW);
  ofRunApp(new ofApp());
}
