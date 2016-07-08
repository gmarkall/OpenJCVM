#ifndef _component_h_
#define _component_h_

#include "base.h"

const unsigned char TAG_HEADER_COMP = 0x01;
const unsigned char TAG_DIR_COMP    = 0x02;
const unsigned char TAG_APPLET_COMP = 0x03;
const unsigned char TAG_IMPORT_COMP = 0x04;
const unsigned char TAG_CONSTANTPOOL_COMP = 0x05;
const unsigned char TAG_CLASS_COMP = 0x06;
const unsigned char TAG_METHOD_COMP = 0x07;
const unsigned char TAG_STATICFIELD_COMP = 0x08;
const unsigned char TAG_REFERENCELOCATION_COMP = 0x09;
const unsigned char TAG_EXPORT_COMP = 0x0A;
const unsigned char TAG_DESCRIPTOR_COMP = 0x0B;
const unsigned char TAG_DEBUG_COMP = 0x0C;

const u1 ACC_PUBLIC    = 0x01;
const u1 ACC_PRIVATE   = 0x02;
const u1 ACC_PROTECTED = 0x04;
const u1 ACC_STATIC    = 0x08;
const u1 ACC_FINAL     = 0x10;

const u1 ACC_ABSTRACT  = 0x40;
const u1 ACC_INIT      = 0x80;

const u2 TYPE_VOID               = 0x0001;
const u2 TYPE_BOOLEAN            = 0x0002;
const u2 TYPE_BYTE               = 0x0003;
const u2 TYPE_SHORT              = 0x0004;
const u2 TYPE_INT                = 0x0005;
const u2 TYPE_REFERRENCE         = 0x0006;
const u2 TYPE_ARRAY_OF_BOOLEAN   = 0x000A;
const u2 TYPE_ARRAY_OF_BYTE      = 0x000B;
const u2 TYPE_ARRAY_OF_SHROT     = 0x000C;
const u2 TYPE_ARRAY_OF_INT       = 0x000D;
const u2 TYPE_ARRAY_OF_REFERENCE = 0x000E;

class PackageInfo : public DebugSupportedClass{
public:
	u1 minorVersion;
	u1 majorVersion;
	u1 AIDLength;
	u1* AID;

	PackageInfo(u1* AID, u1 AIDLength, u1 majorVersion, u1 minorVersion){
		this->AID = AID;
		this->AIDLength = AIDLength;
		this->majorVersion = majorVersion;
		this->minorVersion = minorVersion;
	}

	virtual ~PackageInfo(){
		delete this->AID;
		this->AID = NULL;
	}

	bool operator == (PackageInfo& p2)
	{
		if(this->majorVersion != p2.majorVersion) return false;
		if(this->minorVersion != p2.minorVersion) return false;
		if(this->AIDLength != p2.AIDLength) return false;
		for(int i=0;i<this->AIDLength;i++)
		{
			if(this->AID[i]!=p2.AID[i]) return false;
		}
		return true;
	}

	void displayInfo()
	{
		std::cout<<"Package AID: ";
		for(int i=0;i<this->AIDLength;i++)
		{
			std::cout<<std::hex<<(int)this->AID[i]<<" ";
		}
		std::cout<<std::endl;

		std::cout<<"Package version: ";
		std::cout<<std::hex<<(int)this->majorVersion;
		std::cout<<".";
		std::cout<<std::hex<<(int)this->minorVersion;

		std::cout<<std::endl;
	}
};

class ClassRef
{
public:
	u2 classref;
	ClassRef(u2 classref)
	{
		this->classref = classref;
	}
	ClassRef()
	{
		this->classref = 0;
	};
	bool operator ==(ClassRef& cf)
	{
		return(this->classref == cf.classref);
	};
};

class AccessFlag : public DebugSupportedClass
{
private:
	u1 value;
public:
	AccessFlag(u1 val)
	{
		this->value = val;
	};

	bool isPublic()
	{
		return (this->value & ACC_PUBLIC) == ACC_PUBLIC;
	};

	bool isPrivate()
	{
		return (this->value & ACC_PRIVATE) == ACC_PRIVATE;
	};

	bool isProtected()
	{
		return (this->value & ACC_PROTECTED) == ACC_PROTECTED;
	};

	bool isStatic()
	{
		return (this->value & ACC_STATIC) == ACC_STATIC;
	};

	bool isFinal()
	{
		return (this->value & ACC_FINAL) == ACC_FINAL;
	};

	bool isAbstract()
	{
		return (this->value & ACC_ABSTRACT) == ACC_ABSTRACT;
	};

	bool isInit()
	{
		return (this->value & ACC_INIT) == ACC_INIT;
	};

	virtual ~AccessFlag()
	{
	};

	void displayInfo()
	{
		if(this->isPublic())
		{
			COUT<<"Public ";
		};
		if(this->isAbstract())
		{
			COUT<<"Abstract ";
		};
		if(this->isFinal())
		{
			COUT<<"Final ";
		};
		if(this->isInit())
		{
			COUT<<"Init ";
		};
		if(this->isPrivate())
		{
			COUT<<"Private ";
		};
		if(this->isProtected())
		{
			COUT<<"Protected ";
		};
		if(this->isStatic())
		{
			COUT<<"Static ";
		};
		COUT<<ENDL;
	};
};

#endif
