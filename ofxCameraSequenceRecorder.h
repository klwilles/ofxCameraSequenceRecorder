#ifndef _OFX_CAMERA_SEQUENCE_RECORDER
#define _OFX_CAMERA_SEQUENCE_RECORDER

/** Sequence Recorder -- creates sequential images from video feed.

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

#include "ofMain.h"
#include "Poco/File.h"
#include "Poco/Path.h"

using Poco::File;
using Poco::Path;


class ofxCameraSequenceRecorder {

	public:

		void setup(int _x=0, int _y=0, int _image_width=640, int _image_height=480, string _filetype="jpg");
		void update();
		void draw();

		void keyPressed(int key);
		void listAttachedCameraDevices();
		bool createNewTimeStampDirectory();
        string folder_name;
        string filetype; // ie jpg, png

		int image_width; // this should match your video source
		int image_height; // this should match your video source

		int x; // x location of where things are drawn
		int y; // y location of where things are drawn

		ofVideoGrabber grabber; // for live camera access
		ofImage image; // for sequence of images

        bool is_recording;
		int counter; // counter is used for labeling

};

#endif
