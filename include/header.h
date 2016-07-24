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

#ifndef _header_h_
#define _header_h_

#include "base.h"
#include "component.h"

class HeaderComponent{
public:
	//Size and magic number are not important for the header component.

	u1 minorVersion;
	u1 majorVersion;
	u1 flags;
	PackageInfo* pThisPackage;
	HeaderComponent(PackageInfo* pi,u1 javaCardMajorVersion,u1 javaCardMinorVersion, u1 flag)
	{
		this->pThisPackage = pi;
		this->majorVersion = javaCardMajorVersion;
		this->minorVersion = javaCardMinorVersion;
		this->flags = flag;
	};
	virtual ~HeaderComponent()
	{
		delete pThisPackage;
	};
	void displayInfo()
	{
		this->pThisPackage->displayInfo();
		//COUT<<"Applet version:"<<std::hex<<(int)this->majorVersion<<"."<<(int)this->minorVersion<<ENDL;
		COUT<<"Header"<<ENDL;
		COUT<<"\tmagic number: 0xDECA, 0xFFED"<<ENDL;
		COUT<<"\tjava card version:"<<std::hex<<(int)this->majorVersion<<"."<<(int)this->minorVersion<<ENDL;
		COUT<<"\tFlags: "<<(int)this->flags<<ENDL;
		if(pThisPackage!=NULL)
		{
			pThisPackage->displayInfo();
		}
	};
};

#endif
