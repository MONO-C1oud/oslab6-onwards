#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct bruh {
  int high;
  int low;
};

int main() {
	struct bruh s1;
	s1.low = 10;
	s1.high = 15;

	printf("%d %d", s1.low, s1.high);
}
