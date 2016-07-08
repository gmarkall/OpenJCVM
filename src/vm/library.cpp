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
