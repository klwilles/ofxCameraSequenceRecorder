/** Camera Sequence Recorder -- creates sequential images from video feed.

    Copyright (C) 2010  Kenneth Willes

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "ofxCameraSequenceRecorder.h"



void ofxCameraSequenceRecorder::setup(int _x, int _y, int _image_width, int _image_height, string _filetype){

    image_width = _image_width;
    image_height = _image_height;

    x = _x;
    y = _y;

    is_recording = false;

    grabber.initGrabber(image_width, image_height);
    image.allocate(image_width, image_height, OF_IMAGE_COLOR);

    counter = 0;
    folder_name = "";
    filetype = _filetype;

}

void ofxCameraSequenceRecorder::update(){

    grabber.grabFrame();
    //setFromPixels(unsigned char * pixels, int w, int h, int newType, bool bOrderIsRGB)
    image.setFromPixels(grabber.getPixels(), image_width, image_height, OF_IMAGE_COLOR);

    if(is_recording==true){
        // save to file
        image.saveImage(folder_name+"/img_"+ofToString(counter)+"."+filetype);
        printf("saving # %i\n", counter);
        counter++;

    }

}

void ofxCameraSequenceRecorder::draw(){

    // bottom bar
    ofSetColor(0,0,0);
    ofRect(x,y,image_width, 20);

    // instructions
    string status = "";
    if(is_recording==false){ status = "STOPPED"; } else { status = "RECORDING"; }
    string fps = ofToString(ofGetFrameRate(), 0);
    ofSetColor(255,255,255);
    ofDrawBitmapString("STATUS: "+status+" | press 's' to start/stop, 'l' to list devices | fps: "+fps, 10,15);

    // camera feed
    image.draw(x, y+20, image_width, image_height);

    // visual feedback, red when recording
    if(is_recording==true){
        ofNoFill();
        ofSetColor(255,0,0);
        ofRect(x+5,y+25,image_width-10, image_height-10);
        ofFill();
    }

}

void ofxCameraSequenceRecorder::listAttachedCameraDevices(){
    grabber.listDevices();
}


void ofxCameraSequenceRecorder::keyPressed(int key){
    switch(key){
        case 's':
            is_recording = (is_recording==true) ? false : true;
            if(is_recording==true){
                counter = 0;
                if(createNewTimeStampDirectory()==false){
					is_recording = false;
				}
            }
            break;
        case 'l':
            listAttachedCameraDevices();
            break;
    }

}

bool ofxCameraSequenceRecorder::createNewTimeStampDirectory(){

	ofSetDataPathRoot("./data/"); // relative to data

    folder_name =
    "capture-"+ofToString(ofGetYear())
    +ofToString(ofGetMonth())
    +ofToString(ofGetDay())+"-"
    +ofToString(ofGetHours())
    +ofToString(ofGetMinutes())
    +ofToString(ofGetSeconds());

   string dir = ofToDataPath(folder_name);
   cout << "\n\nCreating new directory for capture: " << dir << endl;

   File file_handle(dir);
   bool success = false;
   try{
      success = file_handle.createDirectory();
   }catch( Poco::Exception &except ){
      ofLog(OF_LOG_ERROR, "Could not make directory");
      return false;
   }

   if(success==false)ofLog(OF_LOG_WARNING, "Could not make directory because it already exists");
   return success;

}
