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

