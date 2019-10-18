#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

#include "glowa.h"

bool NaprawNapis(char **zepsutyNapis, int miejsceBledu)
{
	int rozmiarOrginalu;
	char *NapisPomocniczy = NULL;
	char c;
	int licznik;
	char *wskaznikPomocniczy;

	rozmiarOrginalu = strlen(*zepsutyNapis);
	for (licznik = miejsceBledu; licznik < rozmiarOrginalu - 1; licznik++)	//program nie potrafi przeciesc znaku konca stringa
	{

		(*zepsutyNapis)[licznik] = (*zepsutyNapis)[licznik + 1];
	}
	(*zepsutyNapis)[licznik] = '\0';
	
	wskaznikPomocniczy = *zepsutyNapis;

	return 1;

}

bool AnalizaWyrazenia(char **wyrazenie)
{
	int licznik1;
	int licznikDlaFora;
	bool flagaBladu = 0;
	char c;
	int OstatniRodzajZnaku = 0;
	char wybor;
	int licznikGlowny;

	if (*wyrazenie != NULL)
	{
		for (licznikGlowny = 0; (licznikGlowny < strlen(*wyrazenie)) && (flagaBladu == 0); licznikGlowny++)
		{
			if (licznikGlowny > 0 && (strchr("ijJI", (*wyrazenie)[licznikGlowny]) == 1))
			{

				if ((strchr("ijJI", (*wyrazenie)[licznikGlowny - 1]) == 1))
				{
					printf("\nWykryto nielegalna kombinacje znakow");
					printf("\n%s\n", *wyrazenie);
					for (licznikDlaFora = 0; licznikDlaFora < licznikGlowny - 1; licznikDlaFora++)
					{
						printf(" ");
					}
					printf("%c\n", 94);
					for (licznikDlaFora = 0; licznikDlaFora < licznikGlowny - 1; licznikDlaFora++)
					{
						printf(" ");
					}
					printf("%c", 124);
					printf("\npodales wiecej niz jeden symbol urojenia pod rzad\nco w mysl programu jest bledem");
					printf("\n(podwojne j)Czy poprawic dane usuwjac ten znak? ['t' - tak]\n[w przeciwnym razie - porzucenie wczytanego ciagu] : ");
					wybor = getchar();
					if (wybor != '\n')
					{
						while ((c = getchar()) != '\n') continue;
					}

					if (wybor == 't')
					{
						NaprawNapis(wyrazenie, licznikGlowny);
						flagaBladu = 0;
					}
					else
					{
						flagaBladu = 1;
						break;
					}
				}
			}
			else if (!strchr("ijJI,.0123456789-+*/:xX ", (*wyrazenie)[licznikGlowny]))	// moze na else if
			{
				printf("\n%s\n", *wyrazenie);
				for (licznikDlaFora = 0; licznikDlaFora < licznikGlowny; licznikDlaFora++)
				{
					printf(" ");
				}
				printf("%c\n", 94);
				for (licznikDlaFora = 0; licznikDlaFora < licznikGlowny; licznikDlaFora++)
				{
					printf(" ");
				}
				printf("%c", 124);
				printf("\n(nie liczba)Czy poprawic dane usuwjac ten znak? ['t' - tak]\n[w przeciwnym razie - porzucenie wczytanego ciagu] : ");
				wybor = getchar();
				if (wybor != '\n')
				{
					while ((c = getchar()) != '\n') continue;
				}

				if (wybor == 't')
				{
					NaprawNapis(wyrazenie, licznikGlowny);
					flagaBladu = 0;
				}
				else
				{
					flagaBladu = 1;
					break;
				}
			}

			system("cls");

		}
	}
	else
	{
		printf("\nPodales pusty wiersz");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}
	if (flagaBladu)
	{
		printf("\nOstatecznie podany przez Ciebie ciag nie jest poprawny");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}

	return 1;
}