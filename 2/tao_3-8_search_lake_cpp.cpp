#include <assert.h>
#include <string.h>
#include <iostream>

#define N 5
#define M 5
#define LAKE_LIMIT 5

struct direction {
  int x;
  int y;
} all_dirs[] = { { -1, 0 },{ -1, -1 },{ 0, -1 },{ 1, -1 },{ 1, 0 },{ 1, 1 },{ 0, 1 },{ -1, 1 } };

struct map {
  char bmp[N][M];  //地图，1 表示被水覆盖，0 表示陆地
  bool sign[N][M]; //此位置是否搜索过，初始值都是 false
};

bool SearchLake(struct map *map, int x, int y, int count)
{
  bool isLake = false;
  for (struct direction & dir : all_dirs) {
    int nx = x + dir.x;
    int ny = y + dir.y;
    if ((nx >= 0 && nx < N) && (ny >= 0 && nx < M) && //位置有效性判断
        (!map->sign[nx][ny]) && (map->bmp[nx][ny] == 1)) {
      count++;
      // printf("#### {%s, %s, %d} [%d, %d] direction: (%d, %d), count = %d ####\n",
      //        __FILE__, __func__, __LINE__, x, y, dir.x, dir.y, count);
      map->sign[nx][ny] = true;
      if ((count >= LAKE_LIMIT) || SearchLake(map, nx, ny, count)) {
        isLake = true;
        break;
      }
    }
  }

  return isLake;
}

int main(int argc, char *argv[])
{
  struct map map = {
    .bmp = {
      {0, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 1, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 1, 1},
    },
    .sign = {},
  };

  std::cout << ">>> 2,2 <<<" << std::endl;
  assert(SearchLake(&map, 2, 2, 0));
  memset(map.sign, 0, sizeof(map.sign));
  std::cout << ">>> 4,4 <<<" << std::endl;
  assert(!SearchLake(&map, 4, 4, 0));

  return 0;
}

