#pragma once

#include "ofxSpout2Receiver.h"

using namespace ofxSpout2;

Receiver::Receiver() {
	;
}

void Receiver::setup() {
	mReceiver = new SpoutReceiver;
	mbInitialized = false;
	SenderName[0] = 0;
}

bool Receiver::isSetup()
{
	if(mbInitialized)
		return true;

	else
		return false;
}

void Receiver::showSenders() {
	mReceiver->SelectSenderPanel();
}

int Receiver::getSenderCount()
{
	return mReceiver->GetSenderCount();
}

string Receiver::getSenderName(int index, char* name)
{
	
	//static char* charName;
	//static int MaxNameSize;

	mReceiver->GetSenderName(index, name, 256);

	string senderName;
	//char myName[];
	//strcpy (senderName, charName);
	return senderName;
}

void Receiver::getSenderInfo(const char *name, unsigned int width, unsigned int height)
{
	// static const char* name;
	// static unsigned int width;
	// static unsigned int height;
	static HANDLE handy;
	static DWORD wordy;

	 mReceiver->GetSenderInfo(name, width, height, handy, wordy );
}

unsigned int Receiver::getSenderWidth(string serverName)
{
	const char* myName = serverName.c_str();
	unsigned int width;
	unsigned int height;
	HANDLE handy;
	DWORD wordy;
	mReceiver->GetSenderInfo(myName, width, height, handy, wordy );
	return  width;
}

unsigned int Receiver::getSenderHeight(string serverName)
{
	const char* myName = serverName.c_str();
	unsigned int width;
	unsigned int height;
	HANDLE handy;
	DWORD wordy;
	mReceiver->GetSenderInfo(myName, width, height, handy, wordy );
	return  height;
}

void Receiver::setActiveSender(string senderName)
{
	mReceiver->ReleaseReceiver();

	unsigned int width, height;
	char name[256];
	strcpy(SenderName, senderName.c_str());
   mReceiver->SetActiveSender(SenderName);
    if (mReceiver->CreateReceiver(SenderName, width, height, true))  {

mTexture.allocate(width, height, GL_RGBA);
mbInitialized = true;
std::cout << "Active Sender = "<< SenderName << endl;

return;

}
else {
std::cout << "- No sender detected \n";
}


}

void Receiver::release()
{
	mReceiver->ReleaseReceiver();
	mbInitialized = false;
}

void Receiver::updateTexture() {
	if (!mbInitialized) {
		unsigned int width, height;
		if (mReceiver->CreateReceiver(SenderName, width, height, true)) {
			mTexture.allocate(width, height, GL_RGBA);
			mbInitialized = true;
			return;
		}
		else {
			ofLogWarning("ofxSpout", "No sender detected");
		}
	}

	else { // mbInitialized
		assert(mTexture.isAllocated() && "Texture not allocated but receiver initialized!");
		unsigned int preWidth = mTexture.getWidth();
		unsigned int preHeight = mTexture.getHeight();

		unsigned int width, height;
		if (mReceiver->ReceiveTexture(SenderName, width, height, mTexture.getTextureData().textureID, mTexture.getTextureData().textureTarget)) {
			if (width != preWidth || height != preHeight) { // in case of size change, reallocate
				mTexture.allocate(width, height, GL_RGBA);
				return;
			}
		}
		else {
			// receiving failed
			mReceiver->ReleaseReceiver();
			mbInitialized = false;
		}
	}
}

void Receiver::exit() {
	if(mReceiver != NULL && mbInitialized)
		mReceiver->ReleaseReceiver();
}