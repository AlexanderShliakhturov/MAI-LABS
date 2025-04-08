#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> // для функции isdigit

int main()
{
	int k, ch, fir, sec, thir, num, sum;
	int zer = 0;
	sum = 0;
	thir = -1;
	sec = 0;
	fir = 0;
	k = 0;
	while ((ch = getchar()) != EOF)
	{

		if (!isdigit(ch))
		{
			if (thir != -1)
			{
				fir = sec;
				sec = thir;
				thir = -1;
				zer = 0;
				k++;
			}
			else
				continue;
		}
		else
		{
			zer = zer * 10 + (ch - '0');
			thir = zer;
		}
		// printf("ch = %c, fir = %d, sec = %d, thir = %d\n", ch, fir, sec, thir);
	}
	printf("k = %d, ch = %c, fir = %d, sec = %d, thir = %d\n", k, ch, fir, sec, thir);

	if ((thir == -1) && (sec != 0) && (fir != 0)) // три и более чисел, после третьего есть символы
	{
		num = fir;
		printf("prenultimate number is %d \n", fir);
	}
	else if ((thir != 0) && (sec != 0) && (fir != 0)) // три и более чисел, после третьего нет символов
	{
		num = sec;
		printf("prenultimate number is %d \n", sec);
	}
	else if ((fir != 0) && (sec != 0) && (thir == -1)) // два числа, после второго есть символы
	{
		num = fir;
		printf("prenultimate number is %d \n", fir);
	}
	else if (((fir == 0) && (sec == 0) && (thir != 0)) || ((fir == 0) && (sec != 0) && (thir == -1))) // одно число
	{
		num = 0;
		printf("no prenultimate number or number is 0\n");
	}
	else if ((fir == 0) && (sec != 0) && (thir != 0)) // два числа, после второго нет символов
	{
		num = sec;
		printf("prenultimate number is %d \n", sec);
	}
	else if ((fir == 0) && (sec == 0) && (thir == 0))
	{
		num = 0;
		printf("no prenultimate number or number is 0\n");
	}

	while (num > 0)
	{
		sum += num % 10;
		num /= 10;
	}
	/*if (sum = 0)
	{
		printf("prenultimate number is %d \n", sec);
	}*/

	printf("Summ of digit : %d\n", sum);
	return 0;

	return 0;
}