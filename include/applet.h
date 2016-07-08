#ifndef _applet_h_
#define _applet_h_

#include "base.h"

class Applet :public DebugSupportedClass
{
private:
	u1 AIDLength;
public:
	u1* pAID;
	u2 installMethodOffset;
	Applet(int aidlength)
	{
		this->AIDLength = aidlength;
		pAID = new u1[this->AIDLength];
	};
	~Applet()
	{
		this->AIDLength = 0;
		delete pAID;
		pAID = NULL;
	};
	void displayInfo()
	{
		COUT<<"\t\tApplet AID: "<<(int)this->AIDLength<<" ";
		for(int i=0;i<this->AIDLength;i++)
		{
			COUT<<(int)this->pAID[i]<<" ";
}
		COUT<<ENDL;
		COUT<<"\t\tInstall method offset: "<<(int)this->installMethodOffset<<ENDL;
	};
};

class AppletComponent :public DebugSupportedClass
{
private:
	u1 count;
public:
	Applet** applets;
	AppletComponent(u1 appletCount)
	{
		this->count = appletCount;
		this->applets = new Applet*[this->count];
	};
	virtual ~AppletComponent()
	{
		this->count = 0;
		delete this->applets;
		this->applets = NULL;
	};
	void displayInfo()
	{
		COUT<<"Begin Applet Component"<<ENDL;
		COUT<<"\tApplet counter: "<<(int)this->count<<ENDL;
		for(int i=0;i<this->count;i++)
		{
			this->applets[i]->displayInfo();
		}
		COUT<<"End Applet Component"<<ENDL;
	};
};

#endif
