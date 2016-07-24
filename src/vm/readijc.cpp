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

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int readBin(char* srcFileName, unsigned char* dataBuffer)
{
	int iCount = 0;
	int iTotal = 0;
	int iLine = 0;

	unsigned char cTemp;

	FILE* fStream;

	if((fStream = fopen(srcFileName, "rb"))==NULL)
	{
		cerr<<"Cannot open file:" <<srcFileName<<endl;
		return -1;
	}

	while(!feof(fStream))
	{
		iCount = fread(&cTemp, sizeof(unsigned char), 1, fStream);
		if(ferror(fStream))
		{
			cerr<<"Read error from file:" <<srcFileName<<endl;
			break;
		}
		else
		{
			dataBuffer[iTotal++] = cTemp;
		}
	}

	fclose(fStream);

	return iTotal;
}

int outputHex(unsigned char* dataBuffer,int iLength)
{
	for(int i=0;i<iLength;i++)
	{
		printf("%.2x",(unsigned int)dataBuffer[i]);
		if(i%8 == 0)
		{
			printf("\n");
		}
	}
	return 0;
}


