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
