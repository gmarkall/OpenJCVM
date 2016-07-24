/**
 * Copyright 2008 - present Oliver Lusing / Louis Liu
 *
 * This file is part of OpenJCVM; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation version 2.
 *
 * You should have received a copy of the GNU General Public License along with
 * OpenJCVM; see the file COPYING. If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef _cardapplet_h_
#define _cardapplet_h_

#include "header.h"
#include "directory.h"
#include "applet.h"
#include "import.h"
#include "constantpool.h"
#include "classcomponent.h"
#include "method.h"
#include "referenceLocation.h"
#include "staticfield.h"
#include "descriptor.h"
#include "export.h"

class AbstractApplet :public DebugSupportedClass
{
public:
	HeaderComponent*            pHeader;
	DirectoryComponent*         pDir;
	ImportComponent*            pImport;
	ClassComponent*             pClass;
	StaticFieldComponent*       pStaticField;
	MethodComponent*            pMethod;
	ReferenceLocationComponent* pRefLoc;
	ConstantPoolComponent*      pConstPool;
	DescriptorComponent*        pDescriptor;
	ExportComponent*            pExport;

	AbstractApplet(){
		pHeader = NULL;
		pDir    = NULL;
		pImport      = NULL;
		pMethod = NULL;
		pStaticField = NULL;
		pRefLoc = NULL;
		pConstPool   = NULL;
		pClass       = NULL;
		pDescriptor  = NULL;
		pExport      = NULL;
	}

	virtual ~AbstractApplet(){
		delete pHeader;
		delete pDir;
		delete pImport;
		delete pStaticField;
		delete pRefLoc;
		delete pMethod;
		delete pConstPool;
		delete pClass;
		delete pDescriptor;
		delete pExport;

		pHeader      = NULL;
		pDir         = NULL;
		pImport      = NULL;
		pMethod      = NULL;
		pStaticField = NULL;
		pRefLoc      = NULL;
		pConstPool   = NULL;
		pClass       = NULL;
		pDescriptor  = NULL;
		pExport      = NULL;
	}

	virtual void displayInfo()
	{
		pHeader->displayInfo();

		if(pDir != NULL)
		{
			pDir->displayInfo();
		}

		if(pClass != NULL)
		{
			pClass->displayInfo();
		}
		if(pImport != NULL)
		{
			pImport->displayInfo();
		}
		if(pRefLoc != NULL)
		{
			pRefLoc->displayInfo();
		}
		if(pConstPool != NULL)
		{
			pConstPool->displayInfo();
		}
		if(pStaticField !=NULL)
		{
			pStaticField->displayInfo();
		}
		if(pMethod != NULL)
		{
			pMethod->displayInfo();
		}
		if(pExport!=NULL)
		{
			pExport->displayInfo();
		}
	}
};

class CardLibrary : public AbstractApplet
{
public:
	bool isThisLibrary(PackageInfo* pPI)
	{
		return (*(this->pHeader->pThisPackage) == *pPI);
	}

	void displayInfo()
	{
		COUT<<ENDL<<"Begin library"<<ENDL;
		AbstractApplet::displayInfo();
		COUT<<"End library!"<<ENDL<<ENDL;
	}
};

class CardApplet : public AbstractApplet
{
public:
	AppletComponent* pApplet;

	CardApplet() : AbstractApplet()
	{
		pApplet      = NULL;
	};

	virtual ~CardApplet()
	{
		//AbstractApplet::~AbstractApplet();
		//Louis: It is useless to call deconstructor explicitly.
		delete pApplet;
		pApplet      = NULL;
	}

	CardLibrary* cloneLibrary()
	{
		CardLibrary* pCL = new CardLibrary();
		pCL->pHeader = this->pHeader;
		pCL->pDir = this->pDir;
		pCL->pClass = this->pClass;
		pCL->pConstPool= this->pConstPool;
		pCL->pDescriptor= this->pDescriptor;
		pCL->pImport= this->pImport;
		pCL->pMethod= this->pMethod;
		pCL->pRefLoc= this->pRefLoc;
		pCL->pStaticField= this->pStaticField;
		pCL->pExport = this->pExport;

		pHeader      = NULL;
		pDir         = NULL;
		pImport      = NULL;
		pMethod      = NULL;
		pStaticField = NULL;
		pRefLoc      = NULL;
		pConstPool   = NULL;
		pClass       = NULL;
		pDescriptor  = NULL;
		pExport      = NULL;

		return pCL;
	}

	void install()
	{
		COUT<<"Start installing..."<<ENDL;
		if(this->pApplet == NULL)
		{
			COUT<<"Not an applet!"<<ENDL;
			//exit(0x6F00);
            return;
		}
		else
		{
			COUT<<"Install command from "<<(int)this->pApplet->applets[0]->installMethodOffset<<ENDL;
			this->pMethod->executeByteCode((int)this->pApplet->applets[0]->installMethodOffset,this);
	}
		COUT<<"Install finished!"<<ENDL;
	};

	void process()
	{
	};

	void displayInfo()
	{
		COUT<<ENDL<<"Begin Applet"<<ENDL;
		AbstractApplet::displayInfo();
		pApplet->displayInfo();
		COUT<<"End applet!"<<ENDL;
		COUT<<ENDL;
	}
};

#endif
