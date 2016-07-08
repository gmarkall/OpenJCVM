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

//Test headers
#include "readijc.h"
//#include "../vm_tests/Unit/testReadUx.h"

using namespace std;

int testReadIJC(char* ijcFileName)
{
	//TestReadUx::testReadUx();
	unsigned char* dataBuffer=new unsigned char[10000];
	int iDataLength = readBin(ijcFileName,dataBuffer);
	//outputHex(dataBuffer,iDataLength);
	CardApplet* capp = (CardApplet*)buildApplet(dataBuffer,iDataLength);
	capp->displayInfo();
	return 0;
}

int testReadDescriptorComp(char* capFileName)
{
	unsigned char* dataBuffer=new unsigned char[10000];
	int iDataLength = readBin(capFileName,dataBuffer);
	unsigned char* pDescriptorComponent = dataBuffer;

	int iPosd = 0;


#define READU1 readU1(pDescriptorComponent,&iPosd)
#define READU2 readU2(pDescriptorComponent,&iPosd)
	//if (sizes[TAG_DESCRIPTOR_COMP-1] !=0){
	u1 tag = READU1;
	COUT<<"The tag for descriptor component is "<<(int)tag<<ENDL;
	u2 dclength = READU2;
	COUT<<"The length for the descriptor component is "<<(int)dclength<<ENDL;
	int count= (int)READU1;
	DescriptorComponent* _pDesComp = new DescriptorComponent(count);

	ClassDescriptorInfo** pcdis = new ClassDescriptorInfo*[count];
	for(int i=0;i<count;i++)
	{
		u1 token = READU1;
		u1 accessflag = READU1;
		ClassRef* pThisClassRef = new ClassRef(READU2);
		u1 interfacecount = READU1;
		u2 fieldcount = READU2;
		u2 methodcount = READU2;
		ClassDescriptorInfo* pcdi = new ClassDescriptorInfo(token,accessflag,*pThisClassRef,interfacecount,fieldcount,methodcount);

		int j=0;
		for(j=0;j<interfacecount;j++)
		{
			pcdi->interfaces[j] = new ClassRef(READU2);
		};

		for(j=0;j<fieldcount;j++)
		{
			u1 token = READU1;
			u1 accessflg = READU1;
			u1 byte1 = READU1;
			u1 byte2 = READU1;
			u1 byte3 = READU1;
			u2 wtype = READU2;
			FieldDescriptorInfo* _pfdi = new FieldDescriptorInfo(token,accessflg,byte1,byte2,byte3,wtype);
			pcdi->fields[j] = _pfdi;
		};

		for(j=0;j<methodcount;j++)
		{
			u1 token = READU1;
			u1 af = READU1;
			u2 mo = READU2;
			u2 to = READU2;
			u2 bc = READU2;
			u2 ehc = READU2;
			u2 ehi = READU2;
			MethodDescriptorInfo* _pmdi = new MethodDescriptorInfo(token,af,mo,to,bc,ehc,ehi);
			pcdi->methods[j] = _pmdi;
		};

		pcdis[i] = pcdi;
	};

	_pDesComp->classes = pcdis;

	u2 cpcount = READU2;
	COUT<<"Constant pool count = "<<cpcount<<ENDL;
	TypeDescriptorInfo* ptdi = new TypeDescriptorInfo(cpcount);
	for(u2 k=0;k<cpcount;k++)
	{
		ptdi->pConstantPoolTypes[k] = READU2;
	};

	TypeDesc** ptds = new TypeDesc*[255];
	int icPtds=0;
	int itdCount=0;
	while(iPosd<dclength)
	{
		u1 nbcount = READU1;
		TypeDesc* _ptd = new TypeDesc(nbcount);
		u1 l=0;
		int ll=0;
		COUT<<"Value: length = "<<(int)nbcount<<"\t";
		for(l=0;l<(nbcount+1)/2;l++)
		{
			u1 _val = READU1;
			u1 _high = readHighShift(_val);
			_ptd->pTypes[ll++] = _high;
			COUT<<(int)_ptd->pTypes[ll-1]<<" ";
			if(ll == nbcount)
				continue;
			_ptd->pTypes[ll++] = readLow(_val);
			COUT<<(int)_ptd->pTypes[ll-1]<<" ";
		}
		COUT<<ENDL;
		itdCount++;
	}
	ptdi->setTypeDesc(ptds,itdCount);
	_pDesComp->types = ptdi;

	_pDesComp->displayInfo();

		COUT<<"Descriptor OK!"<<ENDL;
	//}

	return 0;
}

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

	//for(i=1;i<argc-2;i++)
	for(i=1;i<argc-1;i++)
	{
		int iDataLength = readBin(argv[i],dataBuffer);
		CardLibList::libList.push_back(buildApplet(dataBuffer,iDataLength));
	}

	for(libItr = CardLibList::libList.begin();libItr!=CardLibList::libList.end();++libItr)
	{
		(*libItr)->displayInfo();
	}

	//testReadIJC(argv[1]);
	//testReadDescriptorComp("Descriptor.cap");
	testRunApplet(argv[i]);

	//CardApplet* pEngine=buildAppletEngine(argv[i+1]);
	//pEngine->install();

	cin.get();
	return 0;
}
