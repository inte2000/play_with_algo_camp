#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <iomanip>
#include <iostream>

static void usage(char *argv[]) {
  std::cout << "usage: " << argv[0] << "  <digit>" << std::endl;
}

static int root (float a, float *res) {
  float xn;
  float xn1 = a / 2.0;

  if (res == nullptr)
    return -1;

  for (int count = 0; count < 10000; ++count) {
    xn = xn1;
    xn1 = (xn + a / xn) / 2.0;
    if (std::abs(xn1 - xn) <= 0.0001) {
      *res = xn1;
      return 0;
    }
  }
  *res = xn1;
  return -1;
}

int main(int argc, char *argv[])
{
  float f, res;
  char *end;

  if (argc != 2) {
    usage(argv);
    return -1;
  }

  f = strtof(argv[1], &end);
  if (end != argv[1] + strlen(argv[1])) {
    usage(argv);
    return -1;
  }

  if (root(f, &res) < 0) {
    std::cout << std::fixed << "The squart root of " << f << " is ?" << res <<  std::endl;
    return -1;
  } else {
    std::cout << std::fixed << "The squart root of " << f << " is " << res << std::endl;
    return 0;
  }
}
