#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "glowa.h"


bool Wczytaj_Napis(char **napis)
{
	char c;
	int licznik = 0;
	char *pomocnicznyNapis = NULL;
	while ((c = getchar()) != '\n')
	{
		pomocnicznyNapis = (char *)realloc(pomocnicznyNapis, licznik * sizeof(char) + 1);
		if (pomocnicznyNapis != NULL)
		{
			pomocnicznyNapis[licznik] = c;
			licznik++;
		}
		else 
		{
			free(pomocnicznyNapis);
			printf("\nBlad podczas wczytywania danych");
			while ((c = getchar()) != '\n') continue;
			return 0;
		}

	}
	if (pomocnicznyNapis != NULL)
	{
		pomocnicznyNapis[licznik] = '\0';
		*napis = pomocnicznyNapis;
		return 1;

	}
	else
	{
		return 0;
	}
	//*napis = pomocnicznyNapis;
	//return 1;
}
