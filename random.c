// generates the random numbers

#include <stdio.h>
#include <stdlib.h>

int main() {

	for (int i = 0; i < 50000; i++) {
		printf("%d\n", rand() % 1001);
	}

}