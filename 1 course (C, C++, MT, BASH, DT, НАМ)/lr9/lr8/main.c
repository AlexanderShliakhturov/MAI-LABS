#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main() {

	int i = -10, j = -10, l = 6, x, y, z;
	if (((i - 20) * (i - 20) / 100 + (j * j) / 25) <= 1)
	{
		printf("popadaet v zadannuu oblast ");
		printf("k(%d) i(%d) j(%d) l(%d)\n", 0, i, j, l);
		return 0;
	}

	int k;
	bool flag = false;

	for (k = 1; k <= 50; ++k) {
		x = i;
		y = j;
		z = l;
		i = abs(max(min(x + y, x + z) % 30, max(x + z, y + k) % 25));

		j = abs(x + k) % 10+ abs(y + k) % 10+ abs(z + k) % 10;

		l = (x * x * x + y * y * y + z * z * z - k) % 35;

		if (((i - 20) * (i - 20) / 100 + (j * j) / 25) <= 1) {
			flag = true;
			break;
		}

		//else continue;
	}
	if (flag) {
		printf("popadaet v zadannuu oblast ");
		printf("k(%d) i(%d) j(%d) l(%d)\n", k, i, j, l);
	}
	else {
		printf("Ne popadaet v oblast za 50 shagov k(%d) i(%d) j(%d) l(%d)\n", 50, i, j, l);
	}

	if (k <= 50) {

	}
	else {

	}
	return 0;
}

