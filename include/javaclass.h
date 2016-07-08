#ifndef _java_class_h_
#define _java_class_h_

#include "base.h"
#include "component.h"

class JavaClass :
	public DebugSupportedClass
{
public:
	ClassRef thisClass;
	ClassRef superClass;
	int declaredInstanceSize;
	u2* pInstance;
	JavaClass(ClassRef thisclass,ClassRef superclass,int instancesize);
	~JavaClass(void);
	void displayInfo();
};

#endif
