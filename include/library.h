#ifndef _library_h_
#define _library_h_

#include "cardapplet.h"

#include <list>

class CardLibList
{
public:
static std::list<AbstractApplet*> libList;
	static CardLibrary* findLibrary(PackageInfo* pPI);
};

#endif
