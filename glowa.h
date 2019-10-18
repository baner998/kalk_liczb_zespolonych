#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define LICZBA_REALNA 1
#define LICZBA_UROJONA 2
#define SYMBOL_UROJENIA 3
#define OPERATOR 4
#define ODPORNOSC_NA_DZIALANIE_KLASYCZNE 5
//w przypadku gdy program wczytuje liczba po liczbie np jesli podany dwie liczby z czêœci¹ tylko realn¹
//to zostan¹ one przedzielone {0,0} na stosie poniewa¿ program wykrywa co jest ostatni¹ wartosci¹ wprowadzon¹
//gdy z kolei przestawi sie ostatniPrzypadek=0 to podczas dzia³ania podstawowego program sprawdza co jest ostatni¹ wartoœci¹
//i jeœli ostatnio by³o "0" to nie wykona dzialania
//dlatego konieczne bylo zdefiniowanie kolejnego warunku


// nevermind - zmieniono warunki
typedef struct {

	double real;
	double urojona;

}liczba_zespolona;

typedef struct element {

	liczba_zespolona liczba;
	struct element *poprzedni;

}stosu_element;


bool PokazStos(stosu_element *gora);

bool push(liczba_zespolona dane, stosu_element **gora);

liczba_zespolona pop(stosu_element **gora);

bool Wczytaj_Napis(char **napis);

bool NoweMenu();

bool NaprawNapis(char **zepsutyNapis, int miejsceBledu);

bool AnalizaWyrazenia(char **wyrazenie);

bool dodawanie(liczba_zespolona liczba1, liczba_zespolona liczba2, liczba_zespolona *wynik);

bool odejmowanie(liczba_zespolona liczba1, liczba_zespolona liczba2, liczba_zespolona *wynik);

bool mnozenie(liczba_zespolona liczba1, liczba_zespolona liczba2, liczba_zespolona *wynik);

bool dzielenie(liczba_zespolona liczba1, liczba_zespolona liczba2, liczba_zespolona *wynik);