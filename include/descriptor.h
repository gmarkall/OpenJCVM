#ifndef descriptor_h_
#define descriptor_h_

#include "component.h"

class FieldRef
{
	
};

class StaticFieldRef : public FieldRef
{
};

class InstanceFieldRef : public FieldRef
{
};

class Type : public DebugSupportedClass
{
public:
	u2 value;
	Type()
	{
		this->value = 0;
	};

	Type(u2 val)
	{
		this->value = val;
	};

	bool isPrimitiveType()
	{
		return (value & 0x80) == 0x80; 
	};

	bool isReferenceType()
	{
		return (value & 0x80) == 0x0;
	};

	void displayInfo()
	{
	};
};

class PrimitiveType : public Type
{
	void displayInfo()
	{
		Type::displayInfo();
		switch(this->value & 80)
		{
		case TYPE_BOOLEAN:
			COUT<<"Type: boolean"<<ENDL;
			break;
		case TYPE_BYTE:
			COUT<<"Type: byte"<<ENDL;
			break;
		case TYPE_SHORT:
			COUT<<"Type: short"<<ENDL;
			break;
		case TYPE_INT:
			COUT<<"Type: int"<<ENDL;
			break;
		default:
			COUT<<"Type: Unknown"<<ENDL;
			break;
		}
		
	};
};

class ReferenceType : public Type
{
	void displayInfo()
	{
		Type::displayInfo();
	};
};

class FieldDescriptorInfo : public DebugSupportedClass
{
public:
	u1 token;
	AccessFlag* pAF;
	FieldRef* pFieldRef;
	Type* pFieldtype;
	FieldDescriptorInfo(u1 token,u1 accessflag,u1 fieldref1,u1 fieldref2,u1 fieldref3,u2 type)
	{
		this->token = token;
		pAF = new AccessFlag(accessflag);
		if(pAF->isStatic())
		{
			pFieldRef = new StaticFieldRef();
		}
		else
		{
			pFieldRef = new InstanceFieldRef();
		}
	};
	virtual ~FieldDescriptorInfo()
	{
		delete pFieldRef;
		pFieldRef = NULL;
		delete pFieldtype;
		pFieldtype = NULL;
	};
	void displayInfo()
	{
		COUT<<"Field Info:"<<ENDL;
		COUT<<"\tToken:"<<(int)this->token<<ENDL;
		COUT<<"Access Flag: ";
		this->pAF->displayInfo();
	}
};

class MethodDescriptorInfo : public DebugSupportedClass
{
public:
	u1 token;
	AccessFlag* pAF;
	u2 methodOffset;
	u2 typeOffset;
	u2 bytecodeCount;
	u2 exceptionHandlerCount;
	u2 exceptionHandlerIndex;
	MethodDescriptorInfo(u1 token,u1 af,u2 mo,u2 to,u2 bc,u2 ehc,u2 ehi)
	{
		this->token = token;
		pAF = new AccessFlag(af);
		this->methodOffset = mo;
		this->typeOffset = to;
		this->bytecodeCount = bc;
		this->exceptionHandlerCount = ehc;
		this->exceptionHandlerIndex = ehi;
	}
	void displayInfo()
	{
		COUT<<"\tMethod Info:"<<ENDL;
		COUT<<"\tToken "<<(int)this->token<<ENDL;
		COUT<<"\tAccess Flag ";
		pAF->displayInfo();
		COUT<<"\tMethod offset "<<(int)this->methodOffset<<ENDL;
		COUT<<"\tType offset "<<(int)this->typeOffset<<ENDL;
		COUT<<"\tByte code count "<<(int)this->bytecodeCount<<ENDL;
		COUT<<"\tException handler count "<<(int)this->exceptionHandlerCount<<ENDL;
		COUT<<"\tException handler index "<<(int)this->exceptionHandlerIndex<<ENDL;
	}
};

class ClassDescriptorInfo : public DebugSupportedClass
{
public:
	u1 token;
	u1 accessFlags;
	ClassRef thisClassRef;
	u1 interfaceCount;
	u2 fieldCount;
	u2 methodCount;
	ClassRef** interfaces;	
	FieldDescriptorInfo** fields;
	MethodDescriptorInfo** methods;
	ClassDescriptorInfo(u1 token, u1 accessflags, ClassRef pThisRef, u1 interfacecount,u2 fieldcount, u2 methodcount)
	{
		this->token = token;
		this->accessFlags = accessflags;
		this->thisClassRef = pThisRef;
		this->interfaceCount = interfacecount;
		this->fieldCount = fieldcount;
		this->methodCount = methodcount;
		interfaces = new ClassRef*[this->interfaceCount];
		fields = new FieldDescriptorInfo*[this->fieldCount];
		methods = new MethodDescriptorInfo*[this->methodCount];
	};

	virtual ~ClassDescriptorInfo()
	{
		this->interfaceCount = 0;
		this->fieldCount = 0;
		this->methodCount = 0;
		delete this->interfaces;
		delete this->fields;
		delete this->methods;

		this->interfaces = NULL;
		this->fields = NULL;
		this->methods = NULL;
	};

	void displayInfo()
	{
		int i =0;
		COUT<<"Token is " <<(int)this->token<<ENDL;
		COUT<<"Access Flag is "<<(int)this->accessFlags<<ENDL;
		COUT<<"Class ref is "<<(int)this->thisClassRef.classref<<ENDL;
		COUT<<"Interfaces number: "<<(int)this->interfaceCount<<ENDL;
		COUT<<"Field number: "<<(int)this->fieldCount<<ENDL;
		COUT<<"Method number: "<<(int)this->methodCount<<ENDL;

		COUT<<"Interfaces: "<<ENDL;
		for(i=0;i<this->interfaceCount;i++)
		{
			COUT<<"\t Interface - "<<(int)this->interfaces[i]->classref<<ENDL;
		};
		COUT<<"Fields:"<<ENDL;
		for(i=0;i<this->fieldCount;i++)
		{
			fields[i]->displayInfo();
		}
		for(i=0;i<this->methodCount;i++)
		{
			this->methods[i]->displayInfo();
		}
	};
};

class TypeDesc
{
public:
	int nibbleCount;
	u1* pTypes;
	TypeDesc(int nibblecount)
	{
		this->nibbleCount = nibblecount;
		pTypes = new u1[nibbleCount];
	};

	virtual ~TypeDesc()
	{
		this->nibbleCount = 0;
		delete pTypes;
		pTypes = NULL;
	};
};

class TypeDescriptorInfo : public DebugSupportedClass
{
public:
	int constPoolCount;
	int typeDescCount;//Not a standard member
	u2* pConstantPoolTypes;
	TypeDesc** pTypeDesc;			
	TypeDescriptorInfo(u2 cpCount)
	{
		this->constPoolCount = (int) cpCount;
		pConstantPoolTypes = new u2[this->constPoolCount];
		pTypeDesc = NULL;
	}
	void setTypeDesc(TypeDesc** ptd, int ptdlength)
	{
		this->pTypeDesc = ptd;
		this->typeDescCount = ptdlength;
	}

	virtual ~TypeDescriptorInfo()
	{
		this->constPoolCount = 0;
		this->typeDescCount = 0;
		delete this->pConstantPoolTypes;
		this->pConstantPoolTypes = NULL;
		delete this->pTypeDesc;
		this->pTypeDesc = NULL;
	}

	void displayInfo()
	{
	}
};

class DescriptorComponent : public DebugSupportedClass
{
public:
	u1 classCount;
	ClassDescriptorInfo** classes;
	TypeDescriptorInfo* types;

	DescriptorComponent(int count)
	{
		this->classCount = count;
		this->classes = new ClassDescriptorInfo*[classCount];
	};

	virtual ~DescriptorComponent()
	{
		this->classCount = 0;
		delete this->classes;
		this->classes = NULL;
	};

	void displayInfo(){
		COUT<<"The class count is "<<(int)this->classCount<<ENDL;
		for(int i=0;i<this->classCount;i++)
		{
			this->classes[i]->displayInfo();
		}
	}
};

#endif
