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

#include "library.h"

//Find a library in the library list.

std::list<AbstractApplet*> CardLibList::libList;

CardLibrary* CardLibList::findLibrary(PackageInfo* pPI){
	std::list<AbstractApplet*>::const_iterator libItr2;

	for(libItr2 = libList.begin(); libItr2 !=libList.end(); ++libItr2)
	{
		if(((CardLibrary*)(*libItr2))->isThisLibrary(pPI))
			return (CardLibrary*)(*libItr2);
	}

	return NULL;
}
