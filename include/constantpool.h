#ifndef constant_pool_h_
#define constant_pool_h_

#include "component.h"

class CpInfo{
public:
	u1 Tag;
	u1 info[3];
	virtual void displayCpInfo() = 0;
};

class ConstantClassInfo : public CpInfo{
public:
	ConstantClassInfo(u1 tag,u1 byte1, u1 byte2)
	{
		this->Tag = tag;
		this->info[0] = byte1;
		this->info[1] = byte2;
	}
	void displayCpInfo()
	{
		COUT<<"Class ref is "<<(int)info[0]<<" "<<(int)info[1]<<ENDL;
	}
};

class ConstantInstanceFieldRefInfo :public CpInfo{
	public:
	ConstantInstanceFieldRefInfo(u1 tag,u1 byte1, u1 byte2, u1 byte3)
	{
		this->Tag = tag;
		this->info[0] = byte1;
		this->info[1] = byte2;
		this->info[2] = byte3;
	}
	void displayCpInfo()
	{
		COUT<<"Instance field ref is class -> "<<(int)info[0]<<" "<<(int)info[1]<<" /token -> "<<(int)info[2]<<ENDL;
	}
};

class ConstantVirtualMethodRefInfo :public CpInfo{
	public:
	ConstantVirtualMethodRefInfo(u1 tag,u1 byte1, u1 byte2, u1 byte3)
	{
		this->Tag = tag;
		this->info[0] = byte1;
		this->info[1] = byte2;
		this->info[2] = byte3;
	}
	void displayCpInfo()
	{
		COUT<<"Virtual Method ref is class -> "<<(int)info[0]<<" "<<(int)info[1]<<" /token -> "<<(int)info[2]<<ENDL;
	}
};

class ConstantSuperMethodRefInfo :public CpInfo{
	public:
	ConstantSuperMethodRefInfo(u1 tag,u1 byte1, u1 byte2,u1 byte3)
	{
		this->Tag = tag;
		this->info[0] = byte1;
		this->info[1] = byte2;
		this->info[2] = byte3;
	}
	void displayCpInfo()
	{
		COUT<<"Super method ref is class -> "<<(int)info[0]<<" "<<(int)info[1]<<" /token -> "<<(int)info[2]<<ENDL;
	}
};

class ConstantStaticFieldRefInfo :public CpInfo{
	public:
	ConstantStaticFieldRefInfo(u1 tag,u1 byte1, u1 byte2,u1 byte3)
	{
		this->Tag = tag;
		this->info[0] = byte1;
		this->info[1] = byte2;
		this->info[2] = byte3;
	}
	void displayCpInfo()
	{
		COUT<<"Static Field Reference is package : "<<(int)info[0]<<" /class: "<<(int)info[1]<<" /token: "<<(int)info[2]<<ENDL;
	}
};

class ConstantStaticMethodRefInfo :public CpInfo{
	public:
	ConstantStaticMethodRefInfo(u1 tag,u1 byte1, u1 byte2,u1 byte3)
	{
		this->Tag = tag;
		this->info[0] = byte1;
		this->info[1] = byte2;
		this->info[2] = byte3;
	}
	void displayCpInfo()
	{
		COUT<<"Static Method Reference is package : "<<(int)info[0]<<" /class: "<<(int)info[1]<<" /token: "<<(int)info[2]<<ENDL;
	}
};

class ConstantPoolComponent :public DebugSupportedClass{
private:
	int cpCount;
public:
	u2 count;
	CpInfo** pConstantPool;
	void addConst(u1 tag, u1 byte1, u1 byte2, u1 byte3)
	{
		switch(tag)
		{
		case 1:
			pConstantPool[cpCount]=new ConstantClassInfo(tag,byte1,byte2);						
			break;
		case 2:
			pConstantPool[cpCount] = new ConstantInstanceFieldRefInfo(tag,byte1,byte2,byte3);
			break;
		case 3:
			pConstantPool[cpCount] = new ConstantVirtualMethodRefInfo(tag,byte1,byte2,byte3);
			break;
		case 4:
			pConstantPool[cpCount] = new ConstantSuperMethodRefInfo(tag,byte1,byte2,byte3);
			break;
		case 5:
			pConstantPool[cpCount] = new ConstantStaticFieldRefInfo(tag,byte1,byte2,byte3);
			break;
		case 6:
			pConstantPool[cpCount] = new ConstantStaticMethodRefInfo(tag,byte1,byte2,byte3);
			break;
		default:
			COUT<<"Unknown Ref:(";
			break;
		}
		pConstantPool[cpCount]->displayCpInfo();
		cpCount++;
	};

	ConstantPoolComponent(u2 count)
	{
		this->pConstantPool = new CpInfo*[count];
		this->cpCount = 0;
	};
	virtual ~ConstantPoolComponent()
	{
		delete pConstantPool;
		pConstantPool = NULL;
		this->cpCount = 0;
	};

	virtual void displayInfo()
	{

	};
};

#endif
