
#include <stdio.h>
#include <stddef.h>

#define  SIZE 10
#define  P 3
#define  STEP 100000
#define  MOD 10007

int32_t main()
{
	uint32_t pow[SIZE] = {0};
	uint64_t index = 0;
	pow[index] = 1;
	for (int i = 1;i <= STEP; i++){
		uint32_t last = pow[index];
		index = (index + 1) % SIZE;
		pow[index] = last * P % MOD;
		if (i % 10000 == 0) {
			printf("%d^%d=%du(MOD %d)\n", P, i, pow[index], MOD);
		}
	}
	printf("Test power OK!\n");
	return 0;
}
