#include <iostream>

void sort(int *s, int n) {
  for (int i = 2; i <= n; ++i) {
    if (s[i] < s[i - 1]) {
      int j = i;
      s[0] = s[i];
      // 不同判断j是否越界
      while (s[j - 1] > s[0]) {
        s[j] = s[j - 1];
        j--;
      }
      s[j] = s[0];
    }
  }
}

int main(int argc, char *argv[])
{
  int s[10] = {99, 8, 7, 2, 3, 1, 5, 6, 9, 4};

  sort(s, 9);
  std::cout << "s: ";
  for (int i = 1; i < 10; ++i)
    std::cout << s[i] << " ";
  std::cout << std::endl;

  return 0;
}
