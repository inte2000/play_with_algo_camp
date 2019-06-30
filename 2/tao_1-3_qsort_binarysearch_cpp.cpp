#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>

static void swap(int *num, int a, int b) {
  if (a == b)
    return ;
  num[a] ^= num[b];
  num[b] ^= num[a];
  num[a] ^= num[b];
}

static int partion(int *num, int s, int e) {
  int middle = num[e];
  int low = s;

  for (int i = s; i < e; ++i) {
    if (num[i] < middle) {
      if (i != low)
        swap(num, i, low);
      low++;
    }
  }
  swap(num, e, low);
  return low;
}

static void qsort(int *num, int s, int e) {
  if (s >= e)
    return ;

  int middle = partion(num, s, e);
  qsort(num, s, middle - 1);
  qsort(num, middle + 1, e);
}

static void quick_sort(int *num, int n) {
  qsort(num, 0, n - 1);
}

static int binary_search(int *num, int n, int f) {
  int s = 0;
  int e = n - 1;

  while (s <= e) {
    int middle = s + (e - s) / 2;
    int d = num[middle];
    if (d == f) {
      return middle;
    } else if (d < f) {
      s = middle + 1;
    } else {
      e = middle - 1;
    }
  }

  return -1;
}

int main(int argc, char *argv[]) {
  int size;
  srand(time(NULL));
  size = 20 + random() % 100;

  int num[size];
  srand(time(NULL));
  for (int i = 0; i < size; ++i) {
    num[i] = rand() % 1000;
    for (int j = 0; j < i; ++j) {
      if (num[j] == num[i]) {
        i--;
        break;
      }
    }
  }

  // std::cout << ">>>>>> ";
  // for (int i = 0; i < size; ++i) {
  //   std::cout << num[i];
  //   if (i != size - 1)
  //     std::cout << ",";
  // }
  // std::cout << std::endl;
  quick_sort(num, size);
  // std::cout << "<<<<<< ";
  // for (int i = 0; i < size; ++i) {
  //       std::cout << num[i];
  //   if (i != size - 1)
  //     std::cout << ",";
  // }
  // std::cout << std::endl;

  for (int i = 0; i < 20; ++i) {
    int res;
    int idx = random() % size;
    res = binary_search(num, size, num[idx]);
    if (idx != res) {
      std::cout << "binary search fail" << std::endl;
      return -1;
    }
  }

  std::cout << size << " binary search ok" << std::endl;
  return 0;
}
