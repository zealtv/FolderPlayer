#include "sequence.h"

//------------------------------------------------------------------------------
void sequence::initialize(string path)
{
  forceLength = false;
  isInitialized = false;
  setPath(path);
  updateSequence();
  isInitialized = true;
  sequenceLength = 300;
}


void sequence::initialize(string path, int slength)
{
  sequenceLength = slength;
  
  if(sequenceLength < 0)
    forceLength = false;
  else
    forceLength = true;
  
  isInitialized = false;
  setPath(path);
  updateSequence();
  isInitialized = true;
}


//------------------------------------------------------------------------------
void sequence::setPath(string path)
{
  sequencePath = path;
}



//------------------------------------------------------------------------------
void sequence::getNextFrame()
{
  
  
  if(!forceLength)
  {
    sequenceIndex += 1;
    if(sequenceIndex >= sequenceSize)
      sequenceIndex = 0;
  }
  else
  {
    //calculate normalized time to force a loop length
    float playhead = ofGetElapsedTimeMillis() % (sequenceLength * 1000);
    playhead = ofMap(playhead, 0.0, (sequenceLength * 1000), 0.0, sequenceSize);
    sequenceIndex = (int)playhead;
  }

  if( !sequenceFrame.loadImage(frames[sequenceIndex]) )
  {
      //remove unloadable frames
      ofLog(OF_LOG_NOTICE, "Removing unreadable frame");

      frames.erase(frames.begin() + sequenceIndex);
      sequenceSize = frames.size();

  }
}







//------------------------------------------------------------------------------
void sequence::updateSequence()
{
  ofDirectory dir( sequencePath );
  
  //only show png files
  dir.allowExt("png");
  
  //populate the directory object
  dir.listDir();
  dir.sort();
  
  frames = dir.getFiles();
  
  sequenceSize = frames.size();
  sequenceIndex = 0;
  
  if(sequenceSize > 0)
    sequenceFrame.loadImage(frames[sequenceIndex]);
  
  hasNewFrames = false;
}



//------------------------------------------------------------------------------
void sequence::drawFrame(float x, float y, float w, float h, bool preserveAspect)
{
    if(sequenceFrame.isAllocated())
    {
        float newW = getWidth();
        float newH = getHeight();


        //aspect preserving doesn't work on wide images.
        if(preserveAspect)
        {
            float screenRatio = ofGetWidth()/ofGetHeight();
            float sequenceRatio = getWidth()/getHeight();

            if(screenRatio > sequenceRatio)
                newH = newW * screenRatio;
            else
                newW = newH / screenRatio;

            //then!
            float scale = h/newW;
            newH *= scale;
            newW *= scale;
            int newX = x + ofGetWidth()/2.0 - newW/2.0;

            sequenceFrame.draw( newX, y, newW, newH );
        }
        else
            sequenceFrame.draw( x, y, w, h );
    }


}


//------------------------------------------------------------------------------
ofTexture& sequence::getFrameTextureReference()
{
  return sequenceFrame.getTextureReference();
}


//------------------------------------------------------------------------------
bool sequence::getIsInitialized()
{
  return isInitialized;
}



//------------------------------------------------------------------------------
void sequence::getNewFrames()
{
  startThread( true, false );
}



//------------------------------------------------------------------------------
void sequence::threadedFunction()
{
    while(isThreadRunning())
    {
        ofDirectory dir(sequencePath);

        //only show png files
        dir.allowExt("png");

        //populate the directory object
        dir.listDir();
        dir.sort();

        newFrames = dir.getFiles();

        //cleanNewFrames();
        //can't clean like this because it uses openGL


        if(newFrames.size() != frames.size() )
        {
          if(newFrames.size() > frames.size() ) ofLog( OF_LOG_NOTICE, "New frames found" );
          if(newFrames.size() < frames.size() ) ofLog( OF_LOG_WARNING, "FRAMES LOST!" );

          hasNewFrames = true;
          stopThread();
        }
        else
        {
            ofLog( OF_LOG_NOTICE, "No new frames found" );
            hasNewFrames = false;
            stopThread();
        }
    }

}



//------------------------------------------------------------------------------
void sequence::swapSequenceBuffers()
{
  ofLog( OF_LOG_NOTICE, "SWAPPING BUFFERS" );
  //cleanNewFrames();
  frames = newFrames;
  sequenceSize = frames.size();
  sequenceIndex %= sequenceSize;
  hasNewFrames = false;
}



//------------------------------------------------------------------------------
int sequence::getWidth()
{
  int x = 0;
  if(sequenceFrame.isAllocated())
    x = sequenceFrame.getWidth();
  
  return x;
}


//------------------------------------------------------------------------------
int sequence::getHeight()
{
  int y = 0;
  if(sequenceFrame.isAllocated())
    y = sequenceFrame.getHeight();
  
  return y;
}


//------------------------------------------------------------------------------
void sequence::cleanNewFrames()
{
    for(auto f : newFrames)
    {
        ofImage image;
        if(!image.loadImage(f))
        {
            //todo
            //remove f from newFrames if can't be loaded
            //(cull dud frames)
        }
    }
}
