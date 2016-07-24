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

#ifndef base_h_
#define base_h_

#include <cstdlib>
#include <iostream>

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

typedef signed char s1;
typedef signed short s2;
typedef signed int s4;

#define NATIVE_METHOD_START 60000
//const int NATIVE_METHOD_START = 63000;

class DebugSupportedClass{
public:
	virtual void displayInfo()=0;
};

u1 inline readU1(u1* dataBuffer, int* iPos)
{
	u1 temp = dataBuffer[*iPos];
	(*iPos)++;
	return temp;
};

s1 inline readS1(u1* dataBuffer, int* iPos)
{
	s1 temp = (s1)(dataBuffer[*iPos]);
	(*iPos)++;
	return temp;
};

u2 inline readU2(u1* dataBuffer, int* iPos)
{
	u2 temp = (((u2)dataBuffer[*iPos]&0x00FF) << 8) + (u2)dataBuffer[*iPos+1];
	(*iPos)+=2;
	return temp;
};

s2 inline readS2(u1* dataBuffer, int* iPos)
{
	s2 temp = (((s2)dataBuffer[*iPos]) << 8) + (s2)dataBuffer[*iPos+1];
	(*iPos)+=2;
	return temp;
};

u4 inline readU4(u1* dataBuffer, int* iPos)
{
	u4 temp = ((u4)(dataBuffer[*iPos])<<24)+((u4)dataBuffer[*iPos+1]<<16)+((u4)(dataBuffer[*iPos+2])<<8)+(u4)dataBuffer[*iPos+3];
	(*iPos) += 4;
	return temp;
};

s4 inline readS4(u1* dataBuffer, int* iPos)
{
	s4 temp = ((s4)(dataBuffer[*iPos])<<24)+((s4)dataBuffer[*iPos+1]<<16)+((s4)(dataBuffer[*iPos+2])<<8)+(s4)dataBuffer[*iPos+3];
	(*iPos) += 4;
	return temp;
};

u1 inline readHigh(u1 data)
{
	return data & 0xF0;
};

u1 inline readLow(u1 data)
{
	return data & 0x0F;
};

u1 inline readHighShift(u1 data)
{
	return (data & 0xF0)>>4;
};

u2 inline makeU2(u1 byte1, u1 byte2)
{
	return byte1*0x100+byte2;
}

s4 inline makeInt(s2 short1,s2 short2)
{
	return short1*0x10000+short2;
}

s2 inline getShortHigh(s4 value)
{
	return value/0x10000;
}

s2 inline getShortLow(s4 value)
{
	return value % 0x10000;
}

#define COUT std::cout
#define ENDL std::endl

#endif /*end base_h_ */
