#ifndef _include_import_H_
#define _include_import_H_

#include "component.h"

class ImportComponent : public DebugSupportedClass
{
private:
	u1 count;
public:
	PackageInfo** packages;	
	ImportComponent(u1 packagecount)
	{
		this->count = packagecount;
		packages = new PackageInfo*[this->count];
	};
	virtual ~ImportComponent()
	{
		this->count = 0;
		delete packages;
		packages = NULL;
	};
	virtual void displayInfo()
	{
		COUT<<"Begin Import Component"<<ENDL;
		for(int i=0;i<this->count;i++)
		{
			packages[i]->displayInfo();
		}
		COUT<<"End Import Component"<<ENDL;
	};
};

#endif
