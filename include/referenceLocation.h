#ifndef reference_location_h_
#define reference_location_h_

#include "base.h"
class ReferenceLocationComponent : public DebugSupportedClass
{
public:
	u2 byteIndexCount;
	u1* offsetsToByteIndices;
	u2 byte2IndexCount;
	u1* offsetsToByte2Indices;
	ReferenceLocationComponent(u2 bic)
	{
		this->byteIndexCount = bic;
		offsetsToByteIndices = new u1[(int)bic];
	}

	void setOffsetsToByte2Indices(u2 bic2)
	{
		this->byte2IndexCount = bic2;
		offsetsToByte2Indices = new u1[(int)bic2];
	}

	ReferenceLocationComponent(u2 bic, u2 bic2)
	{
		this->byteIndexCount = bic;
		this->byte2IndexCount = bic2;
		offsetsToByteIndices = new u1[(int)bic];
		offsetsToByte2Indices = new u1[(int)bic2];
	};
	virtual ~ReferenceLocationComponent()
	{
		delete offsetsToByteIndices;
		offsetsToByteIndices=NULL;
		delete offsetsToByte2Indices;
		offsetsToByteIndices=NULL;
	}

	virtual void displayInfo()
	{
		COUT<<"offsets to Byte indices is - ";
		for(int i=0;i<this->byteIndexCount;i++)
		{
			COUT<<std::hex<<(int)(*(this->offsetsToByteIndices+i))<<" ";
		}
		COUT<<ENDL;
		COUT<<"offsets to Byte2 indices is - ";
		for(int i1=0;i1<this->byte2IndexCount;i1++)
		{
			COUT<<std::hex<<(int)(*(this->offsetsToByte2Indices+i1))<<" ";
		}
		COUT<<ENDL;
	}
};

#endif
