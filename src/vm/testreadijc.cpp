#include "cardapplet.h"
#include "installer.h"
#include "readijc.h"

void
testReadIJC(char* ijcFileName)
{
	unsigned char *dataBuffer = new unsigned char[10000];
	int iDataLength = readBin(ijcFileName, dataBuffer);
	//outputHex(dataBuffer,iDataLength);
	CardApplet* capp = (CardApplet*) buildApplet(dataBuffer, iDataLength);
	capp->displayInfo();
}

int
main(int argc, char **argv)
{
  return 0;
}
