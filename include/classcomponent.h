#ifndef _classcomponent_h_
#define _classcomponent_h_

#include "component.h"

class AbstractClassInfo : public DebugSupportedClass{
public:
	bool isShareable;
	int iinterfaceCount;

	virtual bool isInterface() = 0;

	AbstractClassInfo(u1 bitfield)
	{
		isShareable = ((bitfield & 0x40) == 0x40);
		iinterfaceCount = (int)(bitfield & 0x0F);
	};
	AbstractClassInfo()
    {
    };
};

class InterfaceInfo :public AbstractClassInfo{
public:
	u2* superinterfaces;
	InterfaceInfo(u1 bitfield):AbstractClassInfo(bitfield)
	{
		superinterfaces = new u2[this->iinterfaceCount];
	};
	virtual ~InterfaceInfo()
	{
		delete superinterfaces;
		superinterfaces = NULL;
	}

	virtual bool isInterface()
	{
		return true;
	};

	virtual void displayInfo()
	{
		for(int i=0;i<this->iinterfaceCount;i++)
		{
			COUT<<"\t\tSuper interface ["<<i<<"]="<<superinterfaces[i]<<ENDL;
		}
	};
};

class ImplementedInterfaceInfo{
public:
	u2 interfaces;
	u1 count;
	u1* index;

};

class ClassInfo :public AbstractClassInfo{
public:
	ClassRef superClassRef;
	u1 declaredInstanceSize;
	u1 firstReferenceToken;
	u1 referenceCount;
	u2* publicVirtualMethodTable;
	u2* packageVirtualMethodTable;
	ImplementedInterfaceInfo** interfaces;

	u1 publicMethodTableBase;
	u1 publicMethodTableCount;
	u1 packageMethodTableBase;
	u1 packageMethodTableCount;

	ClassInfo(u1 bitfield) : AbstractClassInfo(bitfield)
	{
		publicVirtualMethodTable = NULL;				
		packageVirtualMethodTable = NULL;

		//this->superClassRef.classref<<ENDL;
		this->declaredInstanceSize = 0;
		this->firstReferenceToken = 0;
		this->referenceCount = 0;
		this->publicMethodTableBase = 0;
		this->publicMethodTableCount = 0;
		this->packageMethodTableBase = 0;
		this->packageMethodTableCount = 0;
	};

	virtual ~ClassInfo()
	{
		delete publicVirtualMethodTable;
		delete packageVirtualMethodTable;
		publicVirtualMethodTable = NULL;				
		packageVirtualMethodTable = NULL;
	};

	virtual bool isInterface()
	{
		return false;
	};

	void setPublicMethodTable(u1 tableBase, u1 tableCount)
	{
		this->publicMethodTableBase = tableBase;
		this->publicMethodTableCount = tableCount;
		this->publicVirtualMethodTable = new u2[tableCount];
	};

	void setPackageMethodTable(u1 tableBase, u1 tableCount)
	{
		this->packageMethodTableBase = tableBase;
		this->packageMethodTableCount = tableCount;
		this->packageVirtualMethodTable = new u2[tableCount];
	};

	virtual void displayInfo()
	{
		int i = 0;
		COUT<<"\tInterface count: "<<(int)this->iinterfaceCount<<ENDL;
		COUT<<"\tSuper class:"<<(int)this->superClassRef.classref<<ENDL;
		COUT<<"\tDeclared instance size: "<<(int)this->declaredInstanceSize<<ENDL;
		COUT<<"\tFirst reference token: "<<(int)this->firstReferenceToken<<ENDL;
		COUT<<"\tReference Count: "<<(int)this->referenceCount<<ENDL;
		COUT<<"\tPublic method table base:"<<(int)this->publicMethodTableBase<<ENDL;
		COUT<<"\tPublic method table count:"<<(int)this->publicMethodTableCount<<ENDL;
		COUT<<"\tPackage method table base: "<<(int)this->packageMethodTableBase<<ENDL;
		COUT<<"\tPackage method table count: "<<(int)this->packageMethodTableCount<<ENDL;

		for (i=0; i<publicMethodTableCount;i++)
		{
			if(0==i)
			{
				COUT<<"\tPublic virtual method table:"<<ENDL;				
			};
			COUT<<"\t\tMethod "<<i<<" : "<<(int)this->publicVirtualMethodTable[i]<<ENDL;			
		};

		for (i=0; i<packageMethodTableCount;i++)
		{
			if(0==i)
			{
				COUT<<"\tPackage virtual method table:"<<ENDL;				
			};
			COUT<<"\t\tMethod "<<i<<" : "<<(int)this->packageVirtualMethodTable[i]<<ENDL;			
        };
	};
};

class ClassComponent :public DebugSupportedClass{
private:
	int iIntCount;
	int iClsCount;
public:
	AbstractClassInfo** pClasses;
	ClassComponent(int iInterfaceCount, int iClassCount)
	{
		this->iIntCount = iInterfaceCount;
		this->iClsCount = iClassCount;
		pClasses = new AbstractClassInfo*[this->iIntCount+this->iClsCount];
	};

	static bool isInterface(u1 bitfield)
	{
		return (bitfield & 0x80) == 0x80;
	};
	static bool isShareable(u1 bitfield)
	{
		return (bitfield & 0x40) == 0x40;
	};
	virtual void displayInfo(void){
		COUT<<"Begin Class Component"<<ENDL;
		for(int i=0;i<iIntCount+iClsCount;i++)
		{
			pClasses[i]->displayInfo();
		}
		COUT<<"End Class Component"<<ENDL;
	};
};
		
#endif
