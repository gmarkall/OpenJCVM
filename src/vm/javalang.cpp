#include "javalang.h"
#include "native.h"

CardLibrary* buildJavaLang()
{
	CardLibrary* pCL = new CardLibrary();

	u1* pAID = new u1[7];
	pAID[0] = 0xA0;
	pAID[1]=0x0;
	pAID[2]=0x0;
	pAID[3]=0x0;
	pAID[4]=0x62;
	pAID[5]=0x0;
	pAID[6]=0x1;
	
	PackageInfo* pPI = new PackageInfo(pAID,7,1,0);
	
	HeaderComponent* pHC = new HeaderComponent(pPI,2,1,0);

	pCL->pHeader = pHC;

	//===

	ExportComponent* pEC = new ExportComponent(1);//12 should be the correct value. 

	ClassExportInfo* pCEI_Object = new ClassExportInfo(0,0,1);
	pCEI_Object->pStaticMethodOffsets[0] = NATIVE_METHOD_START + 0;
	pEC->pClassExport[0] = pCEI_Object;
	
	pCL->pExport = pEC;

	//===
	
	ClassComponent* pCC = new ClassComponent(0,1);

	ClassInfo* pCI_Object = new ClassInfo(0);
	pCI_Object->setPublicMethodTable(0,1);
	pCI_Object->publicVirtualMethodTable[0] = NATIVE_METHOD_START + 1; //java/lang/Object.equals(Ljava/lang/Object;)Z
	
	pCC->pClasses[0] = pCI_Object;

	pCL->pClass = pCC;

	//=== 
	// Native function table
	//===

	natives[0] = java_lang_Object;
	natives[1] = java_lang_Object__equals;

	return pCL;
}

void java_lang_Object(void)
{
	u2 obj = VirtualMachine::pop();
	COUT<<"\tCalling java.lang.Object.<init>()"<<ENDL;
}

void java_lang_Object__equals(void)
{
	u2 obj1 = VirtualMachine::pop();
	u2 obj2 = VirtualMachine::pop();

	COUT<<"\tCalling java/lang/Object.equals(Ljava/lang/Object;)Z"<<ENDL;

	if(obj1 == obj2)
	{
		VirtualMachine::push(1);
		COUT<<"\tObject "<<(int)obj1<<" == Object "<<(int)obj2<<ENDL;
	}
	else
	{
		VirtualMachine::push(0);
		COUT<<"\tObject "<<(int)obj1<<" != Object "<<(int)obj2<<ENDL;
	}
}
