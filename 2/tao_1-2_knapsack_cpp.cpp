#include <iostream>

struct object {
  int weight;
  int price;
#define OBJ_STATUS_UNSELECTED	0
#define OBJ_STATUS_SELECTED	1
#define OBJ_STATUS_UNAVAILABLE	2
  int status;
};

struct {
  int totalc;
  struct object objs[7];
} knapsack = {
  .totalc = 150,
  .objs = {
    {
      .weight = 35,
      .price = 10,
    },
    {
      .weight = 30,
      .price = 40,
    },
    {
      .weight = 60,
      .price = 30,
    },
    {
      .weight = 50,
      .price = 50,
    },
    {
      .weight = 40,
      .price = 35,
    },
    {
      .weight = 10,
      .price = 40,
    },
    {
      .weight = 25,
      .price = 30,
    },
  }
};

typedef int policy_func(void);

static int policy_func_price(void) {
  int idx = -1;
  int max = 0;

  for (int i = 0; i < sizeof(knapsack.objs) / sizeof(knapsack.objs[0]); ++i) {
    struct object *obj = &knapsack.objs[i];
    if (obj->status == 0 && max < obj->price) {
      idx = i;
      max = obj->price;
    }
  }

  return idx;
}

static int policy_func_weight(void) {
  int idx = -1;
  int min = 0x7fffffff;

  for (int i = 0; i < sizeof(knapsack.objs) / sizeof(knapsack.objs[0]); ++i) {
    struct object *obj = &knapsack.objs[i];
    if (obj->status == 0 && min > obj->weight) {
      idx = i;
      min = obj->weight;
    }
  }

  return idx;
}

static int policy_func_density(void) {
  int idx = -1;
  float max = 0;

  for (int i = 0; i < sizeof(knapsack.objs) / sizeof(knapsack.objs[0]); ++i) {
    struct object *obj = &knapsack.objs[i];
    float density = (float)obj->price / obj->weight;
    if (obj->status == 0 && max < density) {
      idx = i;
      max = density;
    }
  }

  return idx;
}

static void greedy_algo(policy_func func) {
  int idx;
  int totalc = knapsack.totalc;

  while ((idx = func()) >= 0) {
    struct object *obj = &knapsack.objs[idx];
    if (totalc >= obj->weight) {
      totalc -= obj->weight;
      obj->status = OBJ_STATUS_SELECTED;
      std::cout << "  select " << idx + 1 << ": wi = " << obj->weight << ", pi = " << obj->price << std::endl;
    } else {
      obj->status = OBJ_STATUS_UNAVAILABLE;
    }
  }
}

static void reset() {
  for (int i = 0; i < sizeof(knapsack.objs) / sizeof(knapsack.objs[0]); ++i)
    knapsack.objs[i].status = OBJ_STATUS_UNSELECTED;
}

int main(int argc, char *argv[]) {
  // for (int i = 0; i < sizeof(knapsack.objs) / sizeof(knapsack.objs[0]); ++i) {
  //   std::cout << i << ": wi = " << knapsack.objs[i].weight << ", pi = " << knapsack.objs[i].price <<
  //       ", status = " << knapsack.objs[i].status << std::endl;
  // }

  std::cout << ">>> policy_func_price <<<" << std::endl;
  greedy_algo(policy_func_price);
  std::cout << ">>> policy_func_weight <<<" << std::endl;
  reset();
  greedy_algo(policy_func_weight);
  std::cout << ">>> policy_func_density <<<" << std::endl;
  reset();
  greedy_algo(policy_func_density);

  return 0;
}
