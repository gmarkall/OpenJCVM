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
