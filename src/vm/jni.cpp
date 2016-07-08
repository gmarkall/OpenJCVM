#include "jni.h"
#include "native.h"

CardLibrary* buildJNI()
{
	CardLibrary* pCL = new CardLibrary();

	u1* pAID = new u1[8];
	pAID[0] = 0xA0;
	pAID[1]=0xFF;
	pAID[2]=0x0;
	pAID[3]=0x0;
	pAID[4]=0x0;
	pAID[5]=0x0;
	pAID[6]=0x0;
	pAID[7]=0x1;
	//AID on jni package is 0xA0:0xFF:0x00:0x00:0x00:0x00:0x00:0x01
	
	PackageInfo* pPI = new PackageInfo(pAID,8,1,0);//pAID, length ==8 , version 1.0
	
	HeaderComponent* pHC = new HeaderComponent(pPI,2,1,0);//version 2.1

	pCL->pHeader = pHC;

	//===

	ExportComponent* pEC = new ExportComponent(1); 

	ClassExportInfo* pCEI_JCFDriver = new ClassExportInfo(0,0,2);//2 static method
	pCEI_JCFDriver->pStaticMethodOffsets[0] = NATIVE_METHOD_START + 2;
	pCEI_JCFDriver->pStaticMethodOffsets[1] = NATIVE_METHOD_START + 3;
	pEC->pClassExport[0] = pCEI_JCFDriver;
	
	pCL->pExport = pEC;

	//===
	// Native function table
	//===
	natives[2] = JCFDriver__methodMissing;
	natives[3] = JCFDriver__registerApplet;
	
	return pCL;
}

void JCFDriver__registerApplet(void)
{
	COUT<<"Calling JCFDriver registerApplet method..."<<ENDL;
	u2 appletID = VirtualMachine::pop();
	COUT<<(int)appletID<<" is registered into JCRE!"<<ENDL;
}

void JCFDriver__methodMissing(void)
{
	COUT<<"Method missing..."<<ENDL;
}
