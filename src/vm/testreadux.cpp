#include <iostream>
#include <string.h>
#include "base.h"

bool testReadUx(void);
bool testReadU1(void);
bool testReadU2(void);
bool testReadU4(void);

bool verbose = false;

int
main(int argc, char **argv)
{
  if (argc > 1 && (strcmp(argv[1], "-v") == 0))
    verbose = true;

  if (testReadUx())
    return 0;
  else
    return 1;
}

bool
testReadUx()
{
  bool res1 = testReadU1();
  bool res2 = testReadU2();
  bool res4 = testReadU4();

  return res1 && res2 && res4;
}

template<typename T>
bool check(T expected, T actual)
{
  bool good = (expected == actual);
  if (!good || verbose)
    std::cout << (good ? "OK" : "NOK") << std::endl;
  return good;
}

bool
testReadU1()
{
  u1 dataBuffer[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  u1 expectedBuffer[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  int pos = 0;
  bool good = true;
  for (size_t i = 0; i < 10; i++)
  {
    bool current = check(readU1(dataBuffer, &pos), expectedBuffer[i]);
    good = good && current;
  }

  return good;
}

bool
testReadU2()
{
  u1 dataBuffer[10] = { 1, 2, 1, 4, 1, 6, 1, 8, 1, 10 };
  u2 expectedBuffer[5] = { 0x102, 0x104, 0x106, 0x108, 0x10A };

  int pos = 0;
  bool good = true;

  for (size_t i = 0; i < 5; i++)
  {
    bool current = check(readU2(dataBuffer, &pos), expectedBuffer[i]);
    good = good && current;
  }

  return good;
};

bool
testReadU4()
{
  u1 dataBuffer[12] = { 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1 };
  u4 expectedBuffer[3] = { 1, 0x101, 0x10101 };

  int pos = 0;
  bool good;

  for (size_t i = 0; i < 3; i++)
  {
    bool current = check(readU4(dataBuffer, &pos), expectedBuffer[i]);
    good = good && current;
  }

  return good;
};
