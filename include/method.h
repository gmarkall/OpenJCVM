#ifndef _method_h_
#define _method_h_
#include "base.h"
#include "vm.h"
#include "native.h"

class ExceptionHandlerInfo{
public:
	u2 startOffset;
	u2 activeLength;
	u2 handlerOffset;
	u2 catchTypeIndex;
};

class MethodHeaderInfo{
public:
	u1 flags;
	u1 maxStack;
	u1 nargs;
	u1 maxLocals;
};

class MethodInfo{
public:
	MethodHeaderInfo* pMethodHeaderInfo;
	u1* bytecodes;
};

class MethodComponent :public DebugSupportedClass{
public:
	u1 handlerCount;
	ExceptionHandlerInfo** pExceptionHandlers;
	u1* pMethodInfo;
	static bool isExtended(u1 flag)
	{
		return (flag & 0x80) == 0x80;
	};

	static bool isAbstract(u1 flag)
	{
		return (flag & 0x40) == 0x40;
	};

	MethodComponent(u1 handlerCount)
	{
		this->handlerCount = handlerCount;
		pExceptionHandlers = new ExceptionHandlerInfo*[handlerCount];
		for(int i=0;i<(int)handlerCount;i++)
			pExceptionHandlers[i]=new ExceptionHandlerInfo();
	};

	virtual ~MethodComponent(){
		for(int i=0;i<(int)handlerCount;i++)
		{
			delete pExceptionHandlers[i];
			pExceptionHandlers[i]= NULL;
		}
		delete pExceptionHandlers;
		pExceptionHandlers = NULL;			
	};

	void executeByteCode(u2 offset, AbstractApplet* pCA)
	{
		//Add for native method execution.
		if(offset>=NATIVE_METHOD_START)
		{
			(*natives[offset-NATIVE_METHOD_START])();
			return;
		}

		int iPosm2 = offset;
#define READU1 readU1(pMethodInfo,&iPosm2)
#define READU2 readU2(pMethodInfo,&iPosm2)

		u1 flags = READU1;
		
		COUT<<"Flag = "<<(int)flags<<ENDL;
		COUT<<"\tIs extended?"<<MethodComponent::isExtended(flags)<<ENDL;
		COUT<<"\tIs abstract?"<<MethodComponent::isAbstract(flags)<<ENDL;

		if(MethodComponent::isExtended(flags))
		{
			u1 maxStack = READU1;
			u1 nargs = READU1;
			u1 maxLocals = READU1;
			COUT<<"Max stack: "<<(int)maxStack<<ENDL;
			COUT<<"Numbers of parameters: "<<(int)nargs<<ENDL;
			COUT<<"Max Locals:"<<(int)maxLocals<<ENDL;
			VirtualMachine::runStatic(pMethodInfo, &iPosm2,pCA,maxStack,nargs,maxLocals);
		}
		else
		{
			u1 maxStack = readLow(flags);
			COUT<<"Max stack: "<<(int)maxStack<<ENDL;
			u1 bitField = READU1;
			u1 nargs = readHighShift(bitField);
			u1 maxLocals = readLow(bitField);
			COUT<<"Numbers of parameters: "<<(int)nargs<<ENDL;
			COUT<<"Max Locals:"<<(int)maxLocals<<ENDL;
			VirtualMachine::runStatic(pMethodInfo, &iPosm2,pCA,maxStack,nargs,maxLocals);
		}
#undef READU2
#undef READU1
	}

	virtual void displayInfo(){
		std::cout<<"Handler Counter:"<<(int)this->handlerCount<<std::endl;
		for(int i=0;i<(int)handlerCount;i++)
		{
			std::cout<<"Exception "<<i<<std::endl;
			std::cout<<"Start Offset:"<<pExceptionHandlers[i]->startOffset<<std::endl;
			std::cout<<"Active Length:"<<pExceptionHandlers[i]->activeLength<<std::endl;
			std::cout<<"Handler Offset:"<<pExceptionHandlers[i]->handlerOffset<<std::endl;
			std::cout<<"Catch type index:"<<pExceptionHandlers[i]->catchTypeIndex<<std::endl;
		}
	};
};

#endif
