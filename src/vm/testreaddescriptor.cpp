#include <iostream>

#include "installer.h"
#include "readijc.h"

using namespace std;

int testReadDescriptorComp(char* capFileName);

int main (int argc, char **argv)
{
  if (argc < 2)
  {
    cout << "Usage: test_readdescriptor <descriptor file>" << endl;
    exit(1);
  }
  return testReadDescriptorComp(argv[1]);
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
	cout << "The tag for descriptor component is " << (int)tag << endl;

        if ((int)tag != 11)
        {
          cout << "Expected tag to be 11." << endl;
          return 1;
        }

	u2 dclength = READU2;
	cout << "The length for the descriptor component is " <<(int)dclength << endl;

        if ((int)dclength != 61)
        {
          cout << "Expected length to be 61" << endl;
          return 1;
        }

	int count = (int)READU1;
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
	cout << "Constant pool count = " << cpcount << endl;

        if ((int)cpcount != 2)
        {
          cout << "Expected constant pool count to be 2." << endl;
          return 1;
        }

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
		cout << "Value: length = " << (int)nbcount << "\t";
		for(l=0;l<(nbcount+1)/2;l++)
		{
			u1 _val = READU1;
			u1 _high = readHighShift(_val);
			_ptd->pTypes[ll++] = _high;
			cout << (int)_ptd->pTypes[ll-1] << " ";
			if(ll == nbcount)
				continue;
			_ptd->pTypes[ll++] = readLow(_val);
			cout << (int)_ptd->pTypes[ll-1] << " ";
		}
		cout << endl;
		itdCount++;
	}
	ptdi->setTypeDesc(ptds,itdCount);
	_pDesComp->types = ptdi;

	_pDesComp->displayInfo();

	cout << "Descriptor OK!" << endl;
	//}

	return 0;
}

