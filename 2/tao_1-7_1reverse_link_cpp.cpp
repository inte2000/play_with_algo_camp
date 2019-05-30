#include <iostream>

struct node {
  int data;
  struct node *next;
};

struct node *reverse_link(struct node *head) {
  if (head == nullptr || head->next == nullptr)
    return head;

  struct node *new_head = reverse_link(head->next);
  head->next->next = head;
  head->next = nullptr;

  return new_head;
}

int main(int argc, char *argv[])
{
  struct node *tmp;
  struct node nodes[10];
  struct node *head = &nodes[0];

  for (int i = 0; i < 10; ++i) {
    nodes[i].data = i;
    if (i == 9)
      nodes[i].next = nullptr;
    else
      nodes[i].next = &nodes[i + 1];
  }

  tmp = head;
  std::cout << ">>> nodes <<<" << std::endl;
  while (tmp) {
    std::cout << "  node->data = " << tmp->data << std::endl;
    tmp = tmp->next;
  }

  head = reverse_link(head);

  tmp = head;
  std::cout << ">>> nodes <<<" << std::endl;
  while (tmp) {
    std::cout << "  node->data = " << tmp->data << std::endl;
    tmp = tmp->next;
  }

  return 0;
}
