#include <iostream>
#include <list>

//Component headers
#include "header.h"
#include "directory.h"
#include "descriptor.h"

//Functional headers
#include "installer.h"
#include "library.h"
#include "javalang.h"
#include "jni.h"
#include "readijc.h"

using namespace std;


int testRunApplet(char* ijcFileName)
{
	unsigned char* dataBuffer=new unsigned char[10000];
	int iDataLength = readBin(ijcFileName,dataBuffer);

	CardApplet* capp = (CardApplet*)buildApplet(dataBuffer,iDataLength);
	capp->displayInfo();

	capp->install();
	capp->process();
	return 0;
}

CardApplet* buildAppletEngine(char* ijcFileName)
{
	unsigned char* dataBuffer=new unsigned char[10000];
	int iDataLength = readBin(ijcFileName,dataBuffer);

	CardApplet* capp = (CardApplet*)buildApplet(dataBuffer,iDataLength);
	capp->displayInfo();

	return capp;
}

int main(int argc, char* argv[])
{
	int i=1;
	unsigned char* dataBuffer=new unsigned char[10000];

	list<AbstractApplet*>::const_iterator libItr;

	if(argc<2){
		std::cout<<"Usage: "<<argv[0]<<" library1.ijc library2.ijc ... applet.ijc"<<std::endl;
		//std::cout<<"Usage: "<<argv[0]<<"library1.ijc library2.ijc ... applet.ijc engine.ijc"<<std::endl;
		exit(1);
	}

	CardLibList::libList.push_back(buildJavaLang());
	CardLibList::libList.push_back(buildJNI());

	for(i=1;i<argc-1;i++)
	{
		int iDataLength = readBin(argv[i],dataBuffer);
		CardLibList::libList.push_back(buildApplet(dataBuffer,iDataLength));
	}

	for(libItr = CardLibList::libList.begin();libItr!=CardLibList::libList.end();++libItr)
	{
		(*libItr)->displayInfo();
	}

	testRunApplet(argv[i]);

	cin.get();
	return 0;
}
