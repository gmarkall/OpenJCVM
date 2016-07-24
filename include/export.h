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

#ifndef _export_h_
#define _export_h_

#include "base.h"

class ClassExportInfo : public DebugSupportedClass
{
public:
	u2 classOffset;
	u1 staticFieldCount;
	u1 staticMethodCount;
	u2* pStaticFieldOffsets;
	u2* pStaticMethodOffsets;
	ClassExportInfo(u2 classOffset, u1 staticFieldCount, u1 staticMethodCount)
	{
		this->classOffset = classOffset;
		this->staticFieldCount = staticFieldCount;
		this->staticMethodCount = staticMethodCount;
		pStaticFieldOffsets = new u2[staticFieldCount];
		pStaticMethodOffsets = new u2[staticMethodCount];
	}

	void displayInfo()
	{
		int i = 0;

		COUT<<"\t\tClass Offset = "<<(int)this->classOffset<<ENDL;
		COUT<<"\t\tStatic Field Count = "<<(int)this->staticFieldCount<<ENDL;
		COUT<<"\t\tStatic Method Count = "<<(int)this->staticMethodCount <<ENDL;
		for(i=0;i<this->staticFieldCount;i++)
		{
			COUT<<"\t\t\tStatic Field Offset: "<<this->pStaticFieldOffsets[i]<<ENDL;
		}
		for(i=0;i<this->staticMethodCount;i++)
		{
			COUT<<"\t\t\tStatic Method Offset: "<<this->pStaticMethodOffsets[i]<<ENDL;
		}
	}
};

class ExportComponent : public DebugSupportedClass
{
public:
	int classCount;
	ClassExportInfo** pClassExport;

	ExportComponent(int clc)
	{
		this->classCount = clc;
		pClassExport = new ClassExportInfo*[clc];
	};

	virtual ~ExportComponent()
	{
		for(int i=0;i<this->classCount;i++)
		{
			delete pClassExport[i];
			pClassExport[i] = NULL;
		}
		delete pClassExport;
		pClassExport = NULL;
	};

	void displayInfo()
	{
		int i=0;
		COUT<<"Begin Export Component"<<ENDL;
		COUT<<"\tExported Class Count: "<<this->classCount<<ENDL;
		for(i=0;i<this->classCount;i++)
		{
			this->pClassExport[i]->displayInfo();
		}
		COUT<<"End Export Component"<<ENDL;
	}
};

#endif
