#include <stdio.h>

#include "callback.h"

int f1(void *data);
int f2(void *data);
int f3(void *data);

int main(int argc, char **argv)
{
  callback_table *cbt;
  int r;

  cbt = callback_initialize();
  if (!cbt)
    return 1;

  r = callback_create(cbt, "tag1");
	printf("callback_create(cbt=%p, 'tag1') = %d\n", cbt, r);

  r = callback_create(cbt, "tag2");
	printf("callback_create(cbt=%p, 'tag2') = %d\n", cbt, r);

  r = callback_create(cbt, "tag3");
	printf("callback_create(cbt=%p, 'tag3') = %d\n", cbt, r);

  r = callback_register(cbt, "tag1", entry, f1);
	printf("callback_register(cbt=%p, 'tag1', entry, %p) = %d\n", cbt, f1, r);

  r = callback_by_tag(cbt, "tag1", entry, (void *)1);
  printf("callback_by_tag(cbt=%p, 'tag1', entry, (void *)1) = %d\n", cbt, r);

  r = callback_by_index(cbt, 0, entry, (void *)1);
  printf("callback_by_index(cbt=%p, 0, entry, (void *)1) = %d\n", cbt, r);

  r = callback_by_index(cbt, 0, fail, (void *)1);
  printf("callback_by_index(cbt=%p, 0, fail, (void *)4) = %d\n", cbt, r);

  r = callback_by_index(cbt, 3, entry, (void *)1);
  printf("callback_by_index(cbt=%p, 3, entry, (void *)4) = %d\n", cbt, r);

  return 0;
}

int f1(void *data)
{
  printf("f1(%p)\n", data);

  return 0;
}

int f2(void *data)
{
  printf("f2(%p)\n", data);

  return 0;
}

int f3(void *data)
{
  printf("f3(%p)\n", data);

  return 0;
}

