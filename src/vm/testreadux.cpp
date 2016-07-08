#include <iostream>
#include "base.h"

class TestReadUx
{
public:
        static void testReadUx();
private:
        static void testReadU1();
        static void testReadU2();
        static void testReadU4();
};

int main(int argc, char **argv)
{
  TestReadUx t;
  t.testReadUx();
}

void TestReadUx::testReadUx()
{
	testReadU1();
	testReadU2();
	testReadU4();
};

void TestReadUx::testReadU1()
{
	u1 dataBuffer[10]={1,2,3,4,5,6,7,8,9,10};
	int iPos = 0;
	
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)1?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)2?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)3?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)4?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)5?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)6?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)7?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)8?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)9?"OK":"NOK")<<std::endl;
	std::cout<<(readU1(dataBuffer,&iPos)==(u1)10?"OK":"NOK")<<std::endl;
};

void TestReadUx::testReadU2()
{
	u1 dataBuffer[10]={1,2,1,4,1,6,1,8,1,10};
	int iPos = 0;
	
	std::cout<<(readU2(dataBuffer,&iPos)==(u2)0x102?"OK":"NOK")<<std::endl;
	std::cout<<(readU2(dataBuffer,&iPos)==(u2)0x104?"OK":"NOK")<<std::endl;
	std::cout<<(readU2(dataBuffer,&iPos)==(u2)0x106?"OK":"NOK")<<std::endl;
	std::cout<<(readU2(dataBuffer,&iPos)==(u2)0x108?"OK":"NOK")<<std::endl;
	std::cout<<(readU2(dataBuffer,&iPos)==(u2)0x10A?"OK":"NOK")<<std::endl;
};

void TestReadUx::testReadU4()
{
	u1 dataBuffer[12]={0,0,0,1,0,0,1,1,0,1,1,1};
	int iPos = 0;

	std::cout<<(readU4(dataBuffer,&iPos)==(u4)1?"OK":"NOK")<<std::endl;
	std::cout<<(readU4(dataBuffer,&iPos)==(u4)0x101?"OK":"NOK")<<std::endl;
	std::cout<<(readU4(dataBuffer,&iPos)==(u4)0x10101?"OK":"NOK")<<std::endl;
};
