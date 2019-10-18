#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "glowa.h"

bool PokazStos(stosu_element *gora)
{
	char c;
	if (gora != NULL)
	{
		
		printf("\n%5.5lf \t + \t (%5.5lf)j", gora->liczba.real, gora->liczba.urojona);
		PokazStos(gora->poprzedni);
	}
	return 1;
}

liczba_zespolona pop(stosu_element **gora)
{
	char c;
	liczba_zespolona wynik; // sprawdzic cos takiego wynik = gora->liczba
	stosu_element *chwilowy = NULL;
	chwilowy = (stosu_element *)calloc(1, sizeof(stosu_element));

	
		chwilowy = (*gora)->poprzedni;
	

	wynik.real = (*gora)->liczba.real;
	wynik.urojona = (*gora)->liczba.urojona;

	*gora = chwilowy;

	return wynik;
}

bool push(liczba_zespolona dane, stosu_element **gora)
{
	char c;
	stosu_element * nowy_element = NULL;
	nowy_element = (stosu_element *)calloc(1, sizeof(stosu_element)); // na 99,9% do usuniecia##########################################

	if (nowy_element == NULL)
	{
		printf("\nBlad podczas odkladania na stos");
		while ((c = getchar()) != '\n') continue;
		return NULL;
	}

	nowy_element->liczba.real = dane.real;
	nowy_element->liczba.urojona = dane.urojona;
	nowy_element->poprzedni = *gora;


	*gora = nowy_element;
	return 1;
}