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

#ifndef _staticfield_h_
#define _staticfield_h_

class ArrayInitInfo : public DebugSupportedClass
{
private:
	u1 type;
	u2 count;
public:
	u1* pValues;
	ArrayInitInfo(u1 type, u2 count)
	{
		this->type = type;
		this->count = count;
		this->pValues = new u1[count];
	};

	virtual ~ArrayInitInfo()
	{
		this->count = 0;
		delete this->pValues;
		this->pValues = NULL;
	};

	virtual void displayInfo()
	{
		COUT<<"\t\tArray Init Info: ";
		for(int i=0;i<(int)this->count;i++)
		{
			COUT<<(int)(this->pValues[i])<<" ";
		}
		COUT<<ENDL;
	}
};

class StaticFieldComponent : public DebugSupportedClass
{
public:
	u2 imageSize;
	u2 referenceCount;
	u2 arrayInitCount;
	ArrayInitInfo** pArrayInit;
	u2 defaultValueCount;
	u2 nonDefaultValueCount;
	u1* pNonDefaultValues;
	u1 *pStaticFieldImage;
	StaticFieldComponent(u2 imagesize, u2 refercount, u2 arrayinitcount)
	{
		this->imageSize = imagesize;
		this->referenceCount = refercount;
		this->arrayInitCount = arrayinitcount;
		this->pArrayInit = new ArrayInitInfo*[this->arrayInitCount];
		this->pStaticFieldImage = new u1[imagesize];

		//Build segment 1 and segment 2 data.
		//Segment 1 - arrays of primitive types initialized by <clinit> methods.
		//Segment 2 - reference types initialized to null, including arrays.
		for(imageCounter=0;imageCounter<(int)this->referenceCount;imageCounter++)
		{
			this->pStaticFieldImage[imageCounter] = 0;
		}
	};
	void beginBuildNonDefaultValues(u2 defaultvaluecount,u2 nondefaultvaluecount)
	{
		this->defaultValueCount = defaultvaluecount;
		this->nonDefaultValueCount = nondefaultvaluecount;
		this->pNonDefaultValues = new u1[nondefaultvaluecount];
		int i;
		//Update segment 3
		//Segment 3 - primitive types initialized to default values.
		for(i=0;i<this->defaultValueCount;i++)
		{
			this->pStaticFieldImage[imageCounter++] = 0;			
		}
	};

	void EndBuildNonDefaultValues()
	{
		//Update segment 4
		//Segment 4 - primitive types initialized to non-default values.
		for(int i=0;i<this->nonDefaultValueCount;i++)
		{
			this->pStaticFieldImage[imageCounter++] = this->pNonDefaultValues[i];
		}
		delete this->pNonDefaultValues;
		this->pNonDefaultValues = NULL;
	};

	virtual ~StaticFieldComponent()
	{
		this->imageSize = 0;
		this->referenceCount = 0;
		this->arrayInitCount = 0;
		this->defaultValueCount = 0;
		this->nonDefaultValueCount = 0;
		delete this->pArrayInit;
		this->pArrayInit = NULL;
		delete this->pStaticFieldImage;
		this->pStaticFieldImage = NULL;
	};

	virtual void displayInfo()
	{
		COUT<<"Begin Static Field"<<ENDL;
		COUT<<"\tImage size : "<<(int)this->imageSize<<ENDL;
		COUT<<"\tReference Count: "<<(int)this->referenceCount<<ENDL;
		COUT<<"\tArray Init Count: "<<(int)this->arrayInitCount<<ENDL;
		int i = 0;
		for(i=0;i<(int)this->arrayInitCount;i++)
		{
			this->pArrayInit[i]->displayInfo();
		}
		COUT<<"\tDefault value count : "<<(int)this->defaultValueCount<<ENDL;
		COUT<<"\tNon default value count: "<<(int)this->nonDefaultValueCount<<ENDL;
		//COUT<<"Non default value: ";
		//for(i=0;i<(int)this->nonDefaultValueCount;i++)
		//{
		//	COUT<<(int)(this->pNonDefaultValues[i])<<" ";
		//}
		//COUT<<ENDL;

		COUT<<"\tBegin Static Field Image..."<<ENDL;
		COUT<<"\t";
		for(i=0;i<this->imageSize;i++)
		{
			COUT<<(int)this->pStaticFieldImage[i]<<" ";
		}
		COUT<<ENDL;
		COUT<<"\tEnd Static Field Image"<<ENDL;

		COUT<<"End static field"<<ENDL;
	};
private:
	int imageCounter;
};

#endif
