#include "javaclass.h"
#include "native.h"

JavaClass::JavaClass(ClassRef thisclass, ClassRef superclass,int instancesize)
{
	this->thisClass = thisclass;
	this->superClass = superclass;
	this->declaredInstanceSize = instancesize;
	this->pInstance = new u2[instancesize];
};

JavaClass::~JavaClass(void)
{
	delete this->pInstance;
	this->pInstance = NULL;
	this->declaredInstanceSize = 0;
};

void JavaClass::displayInfo()
{
};

NativeFunction natives[100];

