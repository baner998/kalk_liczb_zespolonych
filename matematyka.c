#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "glowa.h"

bool dodawanie(liczba_zespolona liczba1 , liczba_zespolona liczba2 , liczba_zespolona *wynik)
{
	wynik->real = liczba1.real + liczba2.real;
	wynik->urojona = liczba1.urojona + liczba2.urojona;

	return 1;
}

bool odejmowanie(liczba_zespolona liczba1, liczba_zespolona liczba2, liczba_zespolona *wynik)
{
	wynik->real = liczba1.real - liczba2.real;
	wynik->urojona = liczba1.urojona - liczba2.urojona;

	return 1;
}

bool mnozenie(liczba_zespolona liczba1, liczba_zespolona liczba2, liczba_zespolona *wynik)
{
	wynik->real = liczba1.real * liczba2.real - liczba1.urojona * liczba2.urojona;
	wynik->urojona = liczba1.urojona * liczba2.real + liczba2.urojona * liczba1.real;

	return 1;
}

bool dzielenie(liczba_zespolona liczba1, liczba_zespolona liczba2, liczba_zespolona *wynik)
{
	char c;
	if (liczba2.real == 0 && liczba2.urojona == 0)
	{
		printf("\nBlad podczas dzielenia : mianownik to 0");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}
	else
	{
		wynik->real    = (liczba1.real * liczba2.real + liczba1.urojona * liczba2.urojona) / (liczba2.real*liczba2.real + liczba2.urojona * liczba2.urojona);
		wynik->urojona = (liczba1.urojona * liczba2.real - liczba1.real * liczba2.urojona) / (liczba2.real*liczba2.real + liczba2.urojona * liczba2.urojona);
	}

	return 1;
}