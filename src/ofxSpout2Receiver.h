#pragma once

#include "ofMain.h"
#include "Spout.h"

namespace ofxSpout2 {
	class Receiver {
	public:
		Receiver();

		void setup();

		bool isSetup();

		void release();

		// show the panel for possible senders and select one
		void showSenders();

		int getSenderCount();

		void getSenderInfo(const char *name, unsigned int width, unsigned int height);

		unsigned int getSenderWidth(string serverName);

		unsigned int getSenderHeight(string serverName);


		//bool getSenderName(int index, char* sendername, int MaxNameSize);

		string getSenderName(int index, char* name);

		void setActiveSender(string senderName);



		void updateTexture();

		// call updateTexture() in a draw() call before (not in update())
		ofTexture &getTexture() { return mTexture; }

		// call in ofApp::exit()
		void exit();

	private:
		SpoutReceiver *mReceiver;
		bool mbInitialized; ;
		char SenderName[256];
		ofTexture mTexture;
	};
}