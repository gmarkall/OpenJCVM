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

#ifndef _directory_h_
#define _directory_h_

#include "base.h"

class StaticFieldSizeInfo : public DebugSupportedClass{
public:
	u2 imageSize;
	u2 arrayInitCount;
	u2 arrayInitSize;
	StaticFieldSizeInfo(u2 imageSize, u2 arrayInitCount, u2 arrayInitSize){
		this->imageSize = imageSize;
		this->arrayInitCount = arrayInitCount;
		this->arrayInitSize = arrayInitSize;
	}
	virtual void displayInfo()
	{
		std::cout<<"Static Field Size Info:"<<std::endl;
		std::cout<<"Image Size:"<<(int)this->imageSize<<std::endl;
		std::cout<<"Array Init Count:"<<(int)arrayInitCount<<std::endl;
		std::cout<<"Array Init Size:"<<(int)arrayInitSize<<std::endl;
	}
};

class CustomComponentInfo : public DebugSupportedClass{
public:
	u1 componentTag;
	u2 size;
	u1 AIDLength;
	u1* AID;
	CustomComponentInfo(){
		AID = NULL;
		AIDLength = 0;
		size = 0;
	}
	CustomComponentInfo(u1 compTag, u2 csize, u1 *AID, u1 AIDLength){
		this->componentTag = compTag;
		this->size = csize;
		this->AID = AID;
		this->AIDLength = AIDLength;
	}
	virtual ~CustomComponentInfo(){
		delete AID;
		AID = NULL;
		this->AIDLength = 0;
	}

	virtual void displayInfo()
	{
	}
};

class DirectoryComponent :public DebugSupportedClass{
public:
	u2 componentSizes[11];
	StaticFieldSizeInfo* pStaticFieldSize;
	u1 importCount;
	u1 appletCount;
	u1 customCount;
	CustomComponentInfo** pCustomComponents;
	void displayInfo()
	{
		this->pStaticFieldSize->displayInfo();
		std::cout<<"Import count:"<<(int)this->importCount<<std::endl;
		std::cout<<"Applet count:"<<(int)this->appletCount<<std::endl;
		std::cout<<"Custom count:"<<(int)this->customCount<<std::endl;

		for (int i=0;i<11;i++)
		{
			std::cout<<"Component Size:"<<componentSizes[i]<<std::endl;
		}
	}
	DirectoryComponent(StaticFieldSizeInfo* sfsi,u1 importCount,u1 appletCount, u1 customCount){
		this->pStaticFieldSize = sfsi;
		this->importCount = importCount;
		this->appletCount = appletCount;
		this->customCount = customCount;

		if(customCount>0)
		{
			pCustomComponents=new CustomComponentInfo*[customCount];
			for(u1 i=0;i<customCount;i++){
				pCustomComponents[i] = new CustomComponentInfo;
			}
		}
		else
		{
			pCustomComponents = NULL;
		}
	}

	virtual ~DirectoryComponent(){
		if(pCustomComponents!=NULL)
		{
			for(u1 i=0;i<customCount;i++){
				delete pCustomComponents[i];
			}
		}
		delete pCustomComponents;
		delete pStaticFieldSize;
	}
};

#endif
