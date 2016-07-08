#include "installer.h"
#include "vm.h"
#include <iostream>

AbstractApplet* buildApplet(unsigned char* dataBuffer, int dataLength)
{
	CardApplet* newapplet=new CardApplet();
	int iPos = 0;
	u1 c1;

	c1=dataBuffer[iPos];

	// Read Header Component

	if(c1!=TAG_HEADER_COMP){
		std::cerr<<"Not an applet!"<<std::endl;
	}
	else
	{
		iPos+=7;
		
		u1 appletMinVer  = dataBuffer[iPos++];
		u1 appletMajVer  = dataBuffer[iPos++];
		u1 appletFlags   = dataBuffer[iPos++];
		u1 packageMinVer = dataBuffer[iPos++];
		u1 packageMajVer = dataBuffer[iPos++];
		u1 aidLength     = dataBuffer[iPos++];
		u1* aid          = new u1[(int)aidLength];
		for(int i=0;i<aidLength;i++)
		{
			aid[i]=dataBuffer[iPos++];						
		}

		PackageInfo* pi = new PackageInfo(aid,aidLength,packageMajVer,packageMinVer);
		newapplet->pHeader = new HeaderComponent(pi,appletMajVer,appletMinVer,appletFlags);
		
	}

	//Read Directory Component
	c1=dataBuffer[iPos];
	std::cout<<"Directory Component Tag is :"<<(int)c1<<std::endl;

	iPos+=3;

	u2 sizes[11];

	int i = 0;

	for(i=0;i<11;i++)
	{
		sizes[i] = readU2(dataBuffer,&iPos);
	}

	u2 imageSize = readU2(dataBuffer,&iPos);
	u2 arrayInitCount = readU2(dataBuffer,&iPos);
	u2 arrayInitSize = readU2(dataBuffer,&iPos);

	StaticFieldSizeInfo* pSfsi = new StaticFieldSizeInfo(imageSize,arrayInitCount,arrayInitSize);

	u1 importCount = readU1(dataBuffer,&iPos);
	u1 appletCount = readU1(dataBuffer,&iPos);
	u1 customCount = readU1(dataBuffer,&iPos);

	newapplet->pDir = new DirectoryComponent(pSfsi,importCount,appletCount,customCount);

	for(i=0;i<11;i++)
	{
		newapplet->pDir->componentSizes[i]=sizes[i];
	}

	//Split the IJC file into component blocks.
	//std::cout<<"Next char is"<<(int)readU1(dataBuffer,&iPos)<<std::endl;

	u1* pAppletComponent = new u1[sizes[TAG_APPLET_COMP-1]];
	u1* pImportComponent = new u1[sizes[TAG_IMPORT_COMP-1]];
	u1* pConstantPoolComponent = new u1[sizes[TAG_CONSTANTPOOL_COMP-1]];
	u1* pClassComponent = new u1[sizes[TAG_CLASS_COMP-1]];
	u1* pMethodComponent = new u1[sizes[TAG_METHOD_COMP-1]];
	u1* pStaticFieldComponent = new u1[sizes[TAG_STATICFIELD_COMP-1]];
	u1* pReferenceLocationComponent = new u1[sizes[TAG_REFERENCELOCATION_COMP-1]];
	u1* pExportComponent = new u1[sizes[TAG_EXPORT_COMP-1]];
	u1* pDescriptorComponent = new u1[sizes[TAG_DESCRIPTOR_COMP-1]];
	u1* pDebugComponent = new u1[sizes[TAG_DEBUG_COMP-1]];

	int compLength = 0;
	
	while(iPos<dataLength-1)
	{
		switch(c1=readU1(dataBuffer,&iPos))
		{
			case TAG_IMPORT_COMP:
				std::cout<<"Import component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pImportComponent+i)=readU1(dataBuffer,&iPos);
				break;
			case TAG_APPLET_COMP:
				std::cout<<"Applet component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pAppletComponent+i)=readU1(dataBuffer,&iPos);
				break;
			case TAG_CONSTANTPOOL_COMP:
				std::cout<<"Constant pool component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pConstantPoolComponent+i)=readU1(dataBuffer,&iPos);
				break;
			case TAG_CLASS_COMP:
				std::cout<<"Class component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pClassComponent+i)=readU1(dataBuffer,&iPos);
				break;
			case TAG_METHOD_COMP:
				std::cout<<"Method component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pMethodComponent+i)=readU1(dataBuffer,&iPos);
				break;
			case TAG_STATICFIELD_COMP:
				std::cout<<"Static field component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pStaticFieldComponent+i)=readU1(dataBuffer,&iPos);
				break;
			case TAG_REFERENCELOCATION_COMP:
				std::cout<<"Reference location component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pReferenceLocationComponent+i)=readU1(dataBuffer,&iPos);
				break;
			case TAG_EXPORT_COMP:
				std::cout<<"Export component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pExportComponent+i)=readU1(dataBuffer,&iPos);
				break;
			case TAG_DESCRIPTOR_COMP:
				std::cout<<"Descriptor component: "<<(int)(compLength=readU2(dataBuffer,&iPos))<<std::endl;
				for(i=0;i<compLength;i++)
					*(pDescriptorComponent+i)=readU1(dataBuffer,&iPos);
				break;
			default:
				std::cout<<"Error Component: "<<(int)c1<<std::endl;
				break;
		}
	}

	//Parse applet component
	int iPosa = 0;
#define READU1 readU1(pAppletComponent,&iPosa)
#define READU2 readU2(pAppletComponent,&iPosa)
	if (sizes[TAG_APPLET_COMP-1] !=0)
	{
	u1 appletcount = READU1;
	AppletComponent* pAC = new AppletComponent(appletcount);
	u1 aidlength = 0;
	u1 aid = 0;
	Applet* _a_applet;
	for(int ia=0;ia<(int)appletcount;ia++)
	{
		aidlength = READU1;
		_a_applet = new Applet(aidlength);
		for(int iaid=0;iaid<aidlength;iaid++)
		{
			_a_applet->pAID[iaid] = READU1;
		}
		_a_applet->installMethodOffset = READU2;
		pAC->applets[ia] = _a_applet;
	}

	newapplet->pApplet = pAC;
	}
	else
	{
		newapplet->pApplet = NULL;
	}
#undef READU2
#undef READU1

	//Parse import component
	int iPosimp = 0;
#define READU1 readU1(pImportComponent,&iPosimp)
#define READU2 readU2(pImportComponent,&iPosimp)
	if (sizes[TAG_IMPORT_COMP-1] !=0)
	{
		u1 pcount = READU1;
		COUT<<"Imported package count = "<<(int)pcount<<ENDL;
		ImportComponent* pIC = new ImportComponent(pcount);

		for(int ii=0;ii<pcount;ii++)
		{
			u1 packageMinVer = READU1;
			u1 packageMajVer = READU1;
			u1 aidLength     = READU1;
			u1* aid          = new u1[(int)aidLength];
			for(int i=0;i<aidLength;i++)
			{
				aid[i]=READU1;						
			}

			PackageInfo* pi = new PackageInfo(aid,aidLength,packageMajVer,packageMinVer);
			pIC->packages[ii] = pi;
		}

		newapplet->pImport = pIC;
	}
#undef READU2
#undef READU1

	//Parse class component
	int iPosl = 0;
#define READU1 readU1(pClassComponent,&iPosl)
#define READU2 readU2(pClassComponent,&iPosl)

	int classCompLength = sizes[TAG_CLASS_COMP-1];
	COUT<<"byte code length = "<<classCompLength<<ENDL;

	AbstractClassInfo** pACIs = new AbstractClassInfo*[256]; //Maximum class component number is 256.

	int iclassCount = 0;
	int iinterfaceCount = 0;
	int iabsClassCount = 0;

	while(iPosl<classCompLength-1)
	{
	
		u1 _c_bitfield = READU1;
		AbstractClassInfo* pACI;
		COUT<<"Class bit field: "<<(int)_c_bitfield<<ENDL;
		if(ClassComponent::isInterface(_c_bitfield))
		{
			pACI = new InterfaceInfo(_c_bitfield);
			for(int _c_intercount=0;_c_intercount<pACI->iinterfaceCount;_c_intercount++)
			{
				((InterfaceInfo*)pACI)->superinterfaces[_c_intercount]= READU2;
			}
			iinterfaceCount++;
		}
		else
		{
			pACI = new ClassInfo(_c_bitfield);
			((ClassInfo*)pACI)->superClassRef.classref = READU2;
			((ClassInfo*)pACI)->declaredInstanceSize = READU1;
			((ClassInfo*)pACI)->firstReferenceToken = READU1;
			((ClassInfo*)pACI)->referenceCount = READU1;
			u1 _c_publicMethodTableBase = READU1;
			u1 _c_publicMethodTableCount = READU1;
			u1 _c_packageMethodTableBase = READU1;
			u1 _c_packageMethodTableCount = READU1;
			((ClassInfo*)pACI)->setPublicMethodTable(_c_publicMethodTableBase,_c_publicMethodTableCount);
			((ClassInfo*)pACI)->setPackageMethodTable(_c_packageMethodTableBase, _c_packageMethodTableCount);
			for(i=0;i<(int)_c_publicMethodTableCount;i++)
			{
				(((ClassInfo*)pACI)->publicVirtualMethodTable)[i] = READU2;
			
			}

			for(i=0;i<(int)_c_packageMethodTableCount;i++)
			{
				(((ClassInfo*)pACI)->packageVirtualMethodTable)[i] = READU2;
			}
			iclassCount++;
		}
		pACIs[iabsClassCount++] = pACI;
	}

	ClassComponent* pCC = new ClassComponent(iinterfaceCount,iclassCount);
	pCC->pClasses = pACIs;

	newapplet->pClass = pCC;

#undef READU2
#undef READU1

	//Parse constant pool component
	int iPosc = 0;
#define READU1 readU1(pConstantPoolComponent,&iPosc)
#define READU2 readU2(pConstantPoolComponent,&iPosc)
	u2 constcount = READU2;
	u1 _c_tag;
	u1 _c_value1;
	u1 _c_value2;
	u1 _c_value3;
	COUT<<"Constant Pool Count = "<<constcount<<ENDL;
	ConstantPoolComponent* pCPC = new ConstantPoolComponent(constcount);
	for(int ic=0;ic<(int)constcount;ic++)
	{
		_c_tag = READU1;
		_c_value1 = READU1;
		_c_value2 = READU1;
		_c_value3 = READU1;
		pCPC->addConst(_c_tag,_c_value1,_c_value2,_c_value3);		
	}
	
	newapplet->pConstPool = pCPC;
#undef READU2
#undef READU1

	//Parse reference location component
	int iPosr = 0;
#define READU1 readU1(pReferenceLocationComponent,&iPosr)
#define READU2 readU2(pReferenceLocationComponent,&iPosr)
	u2 byteIndexCount = READU2;
	COUT<<"Byte Index Count = "<<byteIndexCount<<ENDL;
	ReferenceLocationComponent* pRlc = new ReferenceLocationComponent(byteIndexCount);
	for(int ir=0;ir<(int)byteIndexCount;ir++)
	{
		*(pRlc->offsetsToByteIndices+ir) = READU1;
	}

	u2 byte2IndexCount = READU2;
	COUT<<"Byte2 Index Count = "<<byte2IndexCount<<ENDL;
	pRlc->setOffsetsToByte2Indices(byte2IndexCount);
	for(int ir2=0;ir2<(int)byte2IndexCount;ir2++)
	{
		*(pRlc->offsetsToByte2Indices+ir2) = READU1;
	}

	newapplet->pRefLoc = pRlc;

#undef READU2
#undef READU1

	//Parse static image component
	int iPoss = 0;
#define READU1 readU1(pStaticFieldComponent,&iPoss)
#define READU2 readU2(pStaticFieldComponent,&iPoss)
	u2 _s_imagesize = READU2;
	u2 _s_referencecount = READU2;
	u2 _s_arrayInitCount = READU2;
	StaticFieldComponent* pSfc = new StaticFieldComponent(_s_imagesize,_s_referencecount,_s_arrayInitCount);
	ArrayInitInfo *pAII;

	u1 _s_type;
	u2 _s_count;
	//u1 _s_value;

	for(int is=0;is<(int)_s_arrayInitCount;is++)
	{
		_s_type = READU1;
		_s_count = READU2;
		pAII = new ArrayInitInfo(_s_type,_s_count);
		for(int isc=0;isc<(int)_s_count;isc++)
		{
			pAII->pValues[isc] = READU1;
		}

		pSfc->pArrayInit[is] = pAII;
	}

	u2 _s_dvc = READU2;
	u2 _s_ndvc = READU2;
	
	pSfc->beginBuildNonDefaultValues(_s_dvc,_s_ndvc);
	for(int isvc=0;isvc<(int)_s_ndvc;isvc++)
	{
		pSfc->pNonDefaultValues[isvc] = READU1;
	}
	pSfc->EndBuildNonDefaultValues();

	newapplet->pStaticField = pSfc;

#undef READU2
#undef READU1

	//Parse method component
	int iPosm = 0;
#define READU1 readU1(pMethodComponent,&iPosm)
#define READU2 readU2(pMethodComponent,&iPosm)

	u1 handlerCount = READU1;
	MethodComponent* pmc = new MethodComponent(handlerCount);	
	
	for(int im=0;im<handlerCount;im++)
	{
		pmc->pExceptionHandlers[im]->startOffset=READU2;
		pmc->pExceptionHandlers[im]->activeLength= READU2;
		pmc->pExceptionHandlers[im]->handlerOffset = READU2;
		pmc->pExceptionHandlers[im]->catchTypeIndex = READU2;
	}

	pmc->pMethodInfo = pMethodComponent;

	/* Note: For test only

	int bytecodeLength = sizes[TAG_METHOD_COMP-1];
	COUT<<"byte code length = "<<bytecodeLength<<ENDL;

	int mCount = 0;

	while(iPosm<bytecodeLength-1){
		COUT<<"\nMethod :"<<mCount++<<ENDL;
		COUT<<"Method Offset: "<<(int)iPosm<<ENDL;

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
			VirtualMachine::runStatic(pMethodComponent, &iPosm);
		}
		else
		{
		COUT<<"Max stack: "<<(int)readLow(flags)<<ENDL;
		u1 bitField = READU1;
			COUT<<"Numbers of parameters: "<<(int)readHighShift(bitField)<<ENDL;
		COUT<<"Max Locals:"<<(int)readLow(bitField)<<ENDL;
		VirtualMachine::runStatic(pMethodComponent, &iPosm);
		}
	}
	*/
	newapplet->pMethod = pmc;
#undef READU2
#undef READU1

	int iPose = 0;
#define READU1 readU1(pExportComponent,&iPose)
#define READU2 readU2(pExportComponent,&iPose)
	if (sizes[TAG_EXPORT_COMP-1] !=0)
	{
		u1 classCount = READU1;
		COUT<<"Class Count = "<<(int)classCount<<ENDL;

		ExportComponent *pEC = new ExportComponent(classCount);
		
		for(int _ie=0;_ie<classCount;_ie++)
		{
			u2 _co = READU2;
			u1 _sfc = READU1;
			u1 _smc = READU1;
			pEC->pClassExport[_ie] = new ClassExportInfo(_co,_sfc,_smc);
			for(int _isf=0;_isf<_sfc;_isf++)
			{
				pEC->pClassExport[_ie]->pStaticFieldOffsets[_isf]= READU2;
			}
			for(int _ism=0;_ism<_smc;_ism++)
			{
				pEC->pClassExport[_ie]->pStaticMethodOffsets[_ism]=READU2;
			}
		}

		newapplet->pExport = pEC;
	}

#undef READU2
#undef READU1


	int iPosd = 0;
#define READU1 readU1(pDescriptorComponent,&iPosd)
#define READU2 readU2(pDescriptorComponent,&iPosd)
	if (sizes[TAG_DESCRIPTOR_COMP-1] !=0){
		u2 dclength = sizes[TAG_DESCRIPTOR_COMP-1];

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

		newapplet->pDescriptor = _pDesComp;
	}
	//else{
	//	COUT<<"No descriptor.cap!"<<ENDL;
	//	std::cin.get();
	//}

	if(newapplet->pApplet == NULL)
	{
		CardLibrary* pCL = newapplet->cloneLibrary();
		delete newapplet;
		return pCL;
	}
	else
	{
	return newapplet; 
    }
}
