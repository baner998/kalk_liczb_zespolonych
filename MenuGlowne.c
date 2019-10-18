#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

#include "glowa.h"

bool NoweMenu()
{
	char c;
	char *DanaWejsciowa=NULL;
	stosu_element *gora = NULL;
	liczba_zespolona spopowana_liczba;
	liczba_zespolona liczbaPomocnicza = {0,0};

	int licznikGlowny = 0;

	liczba_zespolona liczbaDoObliczen1 = {0,0}; // bez inicjalizacji wywala blad
	liczba_zespolona liczbaDoObliczen2 = {0,0}; // bez inicjalizacji wywala blad
	liczba_zespolona wynikOperacji;

	int licznik1;
	int dlugoscWyrazenia;
	bool flagaBladu = 0;

	char *tablicaPomocnicza=NULL;
	char pierwszyZnak;
	int ostatniPrzypadek = 0;
	char wybor = 't'; // ot taka inicjalizacja bo w do{}while() sypa³o ze uzycie zmiennej niezainicjalizowanej
	bool odlozone = 0;
	bool BladStosu = 0; // ma zapobiegac odkladaniu na stos {0,0} w sytuacji gdy wybierzemy np: 12 enter 13 enter + enter - enter

	do
	{
		ostatniPrzypadek = 0;
		BladStosu = 0;
		printf("wczytaj wyraznie :");
		printf("\n(By wyjsc z programu nacisnij klawisz 'n')");
		printf("\n(By wyzerowac stos nacisnij klawisz 'z')");
		printf("\n");

		if (Wczytaj_Napis(&DanaWejsciowa) != 0)
		{
			if ((DanaWejsciowa[0] != 'z') && (DanaWejsciowa[0] != 'n'))
			{
				if (AnalizaWyrazenia(&DanaWejsciowa) == 1)	//mozliwosc wyslania do analizy pustego wyrazenia
				{
					while (DanaWejsciowa != NULL)
					{

						pierwszyZnak = DanaWejsciowa[0];
						if (pierwszyZnak != '\0')
						{
							switch (pierwszyZnak)
							{
							case 'j':
							case 'J':
							case 'i':
							case 'I':
								if ((ostatniPrzypadek == LICZBA_REALNA) || (ostatniPrzypadek == OPERATOR) || (ostatniPrzypadek == 0))
								{
									//nic wtedy nie rob
								}
								else if (ostatniPrzypadek == LICZBA_UROJONA)
								{
									liczbaPomocnicza.real = 0;		//chyba niekonieczne bo zatwianie po pushach
								}
								else if (ostatniPrzypadek == SYMBOL_UROJENIA)
								{
									//ta sytuacja zalatwiona juz w funkcji AnalizaWyrazenia()
								}
								NaprawNapis(&DanaWejsciowa, 0);
								ostatniPrzypadek = SYMBOL_UROJENIA;
								break;
							case ' ':
								NaprawNapis(&DanaWejsciowa, 0); //nie wiem narazie czy potrzebne ale walne na wszelki wypadek
								break;
							case '-':
							case '+':
							case '/':
							case ':':
							case '*':
							case 'x':
							case 'X':
								NaprawNapis(&DanaWejsciowa, 0);	// tutaj a nie na koncu po po drodze danaWejsciowa moze zaczac wskazywac na NULL
								if (gora == NULL)	// niekonieczny if bo przeciez potem jak sciaga to zawsze sprawdza
								{
									printf("\nwykryto nielegalna praktyke");
									printf("\nproba wykonywania operacji na pustym stosie");
									//printf("\nEnter by wprowadzi nowy ciag");
									while ((c = getchar()) != '\n') continue;
									DanaWejsciowa = NULL;	 // czy tak to ma byc?
									break;
								}
								if (ostatniPrzypadek == SYMBOL_UROJENIA)
								{
									liczbaPomocnicza.urojona = 1;
									push(liczbaPomocnicza, &gora);
									odlozone = 1;
									liczbaPomocnicza.real = 0;
									liczbaPomocnicza.urojona = 0;
									//NaprawNapis(&DanaWejsciowa , 0);
								}
								if (ostatniPrzypadek == LICZBA_REALNA)
								{
									//liczbaPomocnicza.urojona = 1;
									push(liczbaPomocnicza, &gora);
									odlozone = 1;
									liczbaPomocnicza.real = 0;
									liczbaPomocnicza.urojona = 0;
									//NaprawNapis(&DanaWejsciowa , 0);
								}
								if (gora != NULL)
								{
									liczbaDoObliczen2 = pop(&gora);
									if (gora != NULL)
									{
										liczbaDoObliczen1 = pop(&gora);
										switch (pierwszyZnak)
										{
										case '-':
											odejmowanie(liczbaDoObliczen1, liczbaDoObliczen2, &wynikOperacji);
											break;
										case '+':
											dodawanie(liczbaDoObliczen1, liczbaDoObliczen2, &wynikOperacji);
											break;
										case '/':
										case ':':
											dzielenie(liczbaDoObliczen1, liczbaDoObliczen2, &wynikOperacji);
											break;
										case '*':
										case 'x':
										case 'X':
											mnozenie(liczbaDoObliczen1, liczbaDoObliczen2, &wynikOperacji);
											break;
										default:
											printf("\nzakazana mozliwosc, co ty tu robisz?");
											while ((c = getchar()) != '\n') continue;
											break;
										}

										push(wynikOperacji, &gora);
										odlozone = 1;
									}
									else
									{
										push(liczbaDoObliczen2 , &gora);
										printf("\nNiewystarczajaca ilosc danych na stosie to wykonania operacji");
										BladStosu = 1;
										//printf("\nEnter by wprowadzi nowy ciag");
										while ((c = getchar()) != '\n') continue;
										DanaWejsciowa == NULL;
									}
								}
								else
								{
									printf("\nNiewystarczajaca ilosc danych na stosie to wykonania operacji");
									BladStosu = 1;
									//printf("\nEnter by wprowadzi nowy ciag");
									while ((c = getchar()) != '\n') continue;
									DanaWejsciowa == NULL;	 // czy tak to ma byc?
								}
								ostatniPrzypadek = OPERATOR;
								break;
							default:	//defaultowo tu powinny dojsc jakies liczby, wiec takie tez zalozenie

								if (ostatniPrzypadek == SYMBOL_UROJENIA)//symbol urojenia zawsze poprzedza czesc urojona ktora jest druga wartosci¹ w liczbie ktora zaraz wskoczy na stos
								{
									liczbaPomocnicza.urojona = strtod(DanaWejsciowa, &tablicaPomocnicza);
									DanaWejsciowa = tablicaPomocnicza;
									push(liczbaPomocnicza, &gora);
									odlozone = 1;
									liczbaPomocnicza.real = 0;
									liczbaPomocnicza.urojona = 0;
									ostatniPrzypadek = LICZBA_UROJONA;
								}
								else if ((ostatniPrzypadek == LICZBA_UROJONA) || (ostatniPrzypadek == OPERATOR) || (ostatniPrzypadek == 0))
								{
									liczbaPomocnicza.real = strtod(DanaWejsciowa, &tablicaPomocnicza);
									DanaWejsciowa = tablicaPomocnicza;
									//push(liczbaPomocnicza, &gora);

									ostatniPrzypadek = LICZBA_REALNA;
								}
								else if (ostatniPrzypadek == LICZBA_REALNA) // ten if tylko by byc pewnym ze kazdy przypadek jest pokryty, else w tym miejscu tez da rade
								{
									push(liczbaPomocnicza, &gora);
									odlozone = 1;
									liczbaPomocnicza.real = 0;	// nie konieczne
									liczbaPomocnicza.urojona = 0; // to w sumie tez nie potrzebne
									liczbaPomocnicza.real = strtod(DanaWejsciowa, &tablicaPomocnicza);
									DanaWejsciowa = tablicaPomocnicza;
									odlozone = 0;
								}
								else
								{

								}

								break;
							}
						}
						else
						{
							if (odlozone == 0)
							{
								if(BladStosu == 0) push(liczbaPomocnicza, &gora); // warunek zapobiega odk³adaniu na stos {0,0}
								liczbaPomocnicza.real = 0;
								liczbaPomocnicza.urojona = 0;
							}

							DanaWejsciowa = NULL;
							//printf("\nKoniec wyrazenia");
							printf("Aktualny stos : ");
							PokazStos(gora);
							while ((c = getchar()) != '\n') continue;
							odlozone = 0;

						}

					}

				}
				else
				{
					printf("\nPodane przez Ciebie wyrazenie jest niepoprawne");
				}
			}
			else 
			{
				wybor = DanaWejsciowa[0];
				//if (wybor != '\n') while ((c = getchar()) != '\n') continue;
				if (wybor == 'z')
				{
					while (gora != NULL) pop(&gora);
					ostatniPrzypadek = 0;
				}
			}
		}
		else
		{
			//printf("\nNie udalo sie wczytac napisu");		//nie podano wyrazenia
		}
		system("cls");
	} while (wybor != 'n');

	while (gora != NULL)
	{
		pop(&gora);
	}

	return 1;
}