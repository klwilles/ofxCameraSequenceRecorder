ofxCameraSequenceRecorder - A Bare Bones Video Camera Recorder / Sequence Grabber
=========================

Record frame-by-frame sequences with this OpenFrameworks addon

I created a very simple app that grabs still images from a camera that is connected to your computer and saves the image in a sequence to a time stamp folder in the data directory. 

You can then use a program like AfterEffects to quickly edit and create a movie from the sequence. 

There might be some better video recorders out there already, but I couldn't find any right away so I thought it would just be better to create my own and share--hopefully others will find it useful. 

Press 's' to toggle recording on/off
press 'l' to list attached devices. 

Every time a recording starts again, a new time stamp directory is created with the image sequence. 

It has been tested on a mac and pc. On the mac side of things, it won't run properly unless you compile it through xcode--in other words you can't run it directly from the .app. On the PC, you can just run the exe and it works fine. Be sure to have the data directory on the same level as the exe. 