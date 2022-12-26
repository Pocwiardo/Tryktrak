//POP 2020-12-18 projekt 1 Poæwiardowski Jakub AIR 3 184827
//Microsoft Visual Studio Community 2019 16.7.6, MSVC 2019

#include <iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;


void rysujPlansze(unsigned poleB[], unsigned poleCZ[], string graczB, string graczCZ, int bazaB, int bazaCZ, int zbiteB, int zbiteCZ);

void kostka(int& x, int& y);


bool domB(unsigned poleB[], int zbiteB); //funkcja sprawdzaj¹ca czy wszystkie piony s¹ na ostatnim polu, co umo¿liwia schodzenie do domu

int sprawdzRuchyB(unsigned poleB[], unsigned poleCZ[], int ile, int zbiteB); //funkcja sprawdzaj¹ca ile ruchów dostêpnych ma gracz bia³y

void wczytajPozycjeBialy(unsigned pole[], unsigned poleOp[], int& pozycja, int ile, int zbite);

void ruchBialy(unsigned poleB[], unsigned poleCZ[], int& zbiteB, int& zbiteCZ, int ile, int& bazaB);


bool domCZ(unsigned poleCZ[], int zbiteCZ);

int sprawdzRuchyCZ(unsigned poleCZ[], unsigned poleB[], int ile, int zbiteCZ);

void wczytajPozycjeCzarny(unsigned pole[], unsigned poleOp[], int& pozycja, int ile, int zbite);

void ruchCzarny(unsigned poleCZ[], unsigned poleB[], int& zbiteCZ, int& zbiteB, int ile, int& bazaCZ);



int main()
{
    unsigned poleB[24] = { 0,0,0,0,0,5,0,3,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,2 }; //tablice ustanawiaj¹ce iloœæ pionów na poszczególnych pozycjach na pocz¹tku gry
    unsigned poleCZ[24] = { 2,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,3,0,5,0,0,0,0,0 };
    int zbiteCZ = 0;
    int zbiteB = 0;
    int bazaCZ = 0;
    int bazaB = 0;
    bool graBialy;
    string graczB, graczCZ; //nazwy graczy

    cout << "TRYKTRAK" << endl;
    cout << "---------------------------" << endl;
    cout << "Podaj nazwe gracza grajacego bialymi: ";
    getline(cin, graczB);
    cout << "Podaj nazwe gracza grajacego czarnymi: ";
    getline(cin, graczCZ);

    int x, y;
    do {
        cout << graczB << ", rzuc kostka: ";  //losowanie kto ma zacz¹æ
        system("pause");
        srand(time(NULL));
        x = rand() % 6 + 1;
        cout << graczB << ", wyrzuciles " << x << endl;
        cout << graczCZ << ", rzuc kostka: ";
        system("pause");
        y = rand() % 6 + 1;
        cout << graczCZ << ", wyrzuciles " << y << endl;     
        if (x > y) {
            cout << graczB << " zaczyna!" << endl;
            graBialy = 1;
        }
        else if (x < y) {
            cout << graczCZ << " zaczyna!" << endl;
            graBialy = 0;
        }
        else cout << "Te same liczby, jeszcze raz" << endl;
    } while (x == y);

    system("pause");
    system("cls");
    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);

    while (bazaCZ < 15 && bazaB < 15)
    {
        
        if (graBialy) {
            cout << "Kolej " << graczB << endl;
            cout << graczB << ", rzuc kostkami" << endl;
            system("pause");
            int k1;
            int k2;
            kostka(k1, k2);
            int ile;

            if (k1 == k2) {
                ile = k1;
                cout << "Wylosowales dwie " << ile << "! Masz 4 ruchy.\n";
                for (int i = 0; i < 4; i++) {
                    if (zbiteB > 0) {
                        cout << "Nastapi proba przywrocenia zbitego pionka na "<< ile <<" pozycje..." << endl;
                        system("pause");
                        if (poleCZ[24 - ile] < 2) { //je¿eli na polu przeciwnika jest 0 lub 1 pion
                            poleB[24 - ile]++;
                            zbiteB--;
                            if (poleCZ[24 - ile] == 1) {
                                poleCZ[24 - ile] = 0;   //jeœli na docelowym polu jest pion przeciwnika, zostaje on zbity
                                zbiteCZ++;
                            }
                        }
                        else {
                            cout << "Ruch niemozliwy!" << endl;
                            system("pause");
                            break;
                        }
                       
                    }
                    else ruchBialy(poleB, poleCZ, zbiteB, zbiteCZ, ile, bazaB);
                    
                    system("cls");
                    
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);

                    if (bazaB == 15) break;
                }
            }
            else {
                cout << "Wylosowales: " << k1 << " i " << k2 << "!" << endl;
                if (zbiteB > 0) {
                    cout << "Musisz wrocic zbitymi pionami do gry. Zaczynasz od poczatku planszy. ";
                }
                cout << "O ile pozycji chcesz sie ruszyc najpierw?";

                cin >> ile;
                while (ile != k1 && ile != k2) {
                    cout << "Nieprawidlowy wybor, sprobuj ponownie\n";
                    cin >> ile;
                }
                if (ile == k1) {
                    ruchBialy(poleB, poleCZ, zbiteB, zbiteCZ, k1, bazaB);
                    if (bazaB == 15) break; //jesli po pierwszym ruchu wszystkie pionki s¹ ju¿ w bazie, drugi nie jest wykonywany
                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);
                    ruchBialy(poleB, poleCZ, zbiteB, zbiteCZ, k2, bazaB);
                    
                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);
                }
                else if (ile == k2) {
                    ruchBialy(poleB, poleCZ, zbiteB, zbiteCZ, k2, bazaB);
                    if (bazaB == 15) break;
                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);
                    ruchBialy(poleB, poleCZ, zbiteB, zbiteCZ, k1, bazaB);
                    
                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);
                }
                
            }
            graBialy = 0;
        }
        else {
            cout << "Kolej " << graczCZ << endl;
            cout << graczCZ << ", rzuc kostkami" << endl;
            system("pause");
            int k1;
            int k2;
            kostka(k1, k2);
            int ile;

            if (k1 == k2) {
                ile = k1;
                cout << "Wylosowales dwie " << ile << "! Masz 4 ruchy.\n";
                for (int i = 0; i < 4; i++) {
                    if (zbiteCZ > 0) {
                        cout << "Nastapi proba przywrocenia zbitego pionka na " << ile << " pozycje..." << endl;
                        system("pause");
                        if (poleB[ile - 1] < 2) {
                            poleCZ[ile - 1]++;
                            zbiteCZ--;
                            if (poleB[ile - 1] == 1) {
                                poleB[ile - 1] = 0;
                                zbiteB++;
                            }
                        }
                        else {
                            cout << "Ruch niemozliwy!" << endl;
                            system("pause");
                            break;
                        }

                    }
                    else ruchCzarny(poleCZ, poleB, zbiteCZ, zbiteB, ile, bazaCZ);

                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);

                    if (bazaCZ == 15) break;
                }
            }
            else {
                cout << "Wylosowales: " << k1 << " i " << k2 << "!" << endl;

                if (zbiteCZ > 0) {
                    cout << "Musisz wrocic zbitymi pionami do gry. Zaczynasz od poczatku planszy. ";
                }

                cout << "O ile pozycji chcesz sie ruszyc najpierw?";
                cin >> ile;

                while (ile != k1 && ile != k2) {
                    cout << "Nieprawidlowy wybor, sprobuj ponownie\n";
                    cin >> ile;
                }

                if (ile == k1) {
                    ruchCzarny(poleCZ, poleB, zbiteCZ, zbiteB, k1, bazaCZ);
                    if (bazaCZ == 15) break;
                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);
                    ruchCzarny(poleCZ, poleB, zbiteCZ, zbiteB, k2, bazaCZ);

                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);
                }
                else if (ile == k2) {
                    ruchCzarny(poleCZ, poleB, zbiteCZ, zbiteB, k2, bazaCZ);
                    if (bazaCZ == 15) break;
                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);
                    ruchCzarny(poleCZ, poleB, zbiteCZ, zbiteB, k1, bazaCZ);

                    system("cls");
                    rysujPlansze(poleB, poleCZ, graczB, graczCZ, bazaB, bazaCZ, zbiteB, zbiteCZ);
                }

            }
            graBialy = 1;
        }
    }

    if (bazaB >= 15) cout << "Wygrywa "<<graczB<<"!" << endl;
    else if (bazaCZ >= 15) cout << "Wygrywa "<<graczCZ<<"!" << endl;

}


void rysujPlansze(unsigned poleB[], unsigned poleCZ[], string graczB, string graczCZ, int bazaB, int bazaCZ, int zbiteB, int zbiteCZ) {
    cout << graczB << ": " << bazaB << " \t";
    cout << graczCZ << ": " << bazaCZ << endl;
    cout << "##########################" << endl;
    for (int i = 0; i < 12; i++) {
        string cz = "";
        string b = "";
        cout << i + 1 << " ";
        if (i < 9) cout << " "; //gdy wyswietlana liczba rzêdu jest jednocyfrowa, nale¿y dodaæ spacjê by szerokoœæ kolumny z numeracj¹ by³a jednakowa 
        if (poleB[i] > 0) {
            for (int j = 0; j < poleB[i]; j++) b += "B";
            cout << left << setw(10) << b;
        }
        else if (poleCZ[i] > 0) {
            for (int j = 0; j < poleCZ[i]; j++)   cz += "C";
            cout << left << setw(10) << cz;
        }
        else cout << "          ";

        cz = "";
        b = "";

        if (poleB[23 - i] > 0) {
            for (int j = 0; j < poleB[23 - i]; j++) b += "B";
            cout << right << setw(10) << b;
        }
        else if (poleCZ[23 - i] > 0) {
            for (int j = 0; j < poleCZ[23 - i]; j++)   cz += "C";
            cout << right << setw(10) << cz;
        }
        else cout << "          ";
        cout << " " << 24 - i;

        if (i == 5) { //Wyswietlanie pola zbitych
            b = "";
            cz = "";
            cout << endl;
            cout << "--------------------------" << endl;
            cout << "|";
            for (int k = 0; k < zbiteB; k++) b += "B";
            cout << left << setw(12) << b;
            for (int k = 0; k < zbiteCZ; k++) cz += "C";
            cout << right << setw(12) << cz << "|" << endl;
            cout << "--------------------------";
        }
        cout << endl;
    }
    cout << "##########################" << endl;
    cout << endl;
}

void kostka(int& x, int& y) {
    srand(time(NULL));
    x = rand() % 6 + 1;
    y = rand() % 6 + 1;
}



bool domB(unsigned poleB[], int zbiteB) { //funkcja sprawdzaj¹ca czy wszystkie pionki s¹ ju¿ w miejscu umo¿liwiaj¹cym schodzenie do domu
    int suma = 0;
    for (int i = 6; i < 24; i++) {
        suma += poleB[i];
    }
    if (suma == 0 && zbiteB == 0) return 1;
    else return 0;
}


int sprawdzRuchyB(unsigned poleB[], unsigned poleCZ[], int ile, int zbiteB) {
    int ruchy = 0;
    if (domB(poleB, zbiteB)) {
        for (int i = 0; i < 8; i++) {
            if (poleB[i] > 0) {
                if (poleCZ[i - ile] < 2 || i - ile < 0) ruchy++; //gdy piony s¹ na pozycjach umo¿liwiajacych zejœcie do domu, mo¿liwe s¹ ruchy poza planszê
            }
        }
    }
    else {
        for (int i = 0; i < 24; i++) {
            if (poleB[i] > 0) {
                if (poleCZ[i - ile] < 2 && !(i - ile < 0)) ruchy++; //ruch jest mozliwy gdy na pozycji docelowej nie ma wiêcej ni¿ jednego piona przeciwnika i nie wychodzi siê za planszê
            }
        }
    }
    return ruchy;
}


void wczytajPozycjeBialy(unsigned pole[], unsigned poleOp[], int& pozycja, int ile, int zbite) {
    cin >> pozycja;

    while (pole[pozycja - 1] < 1) {
        cout << "Na podanej pozycji nie ma twoich pionow! Wybierz inna pozycje: ";
        cin >> pozycja;
    }

    if (domB(pole, zbite)) {                          //w przypadku gdy wszystkie pionki s¹ w polu umo¿liwiaj¹cym powrot do domu, nie ma koniecznosci, a nawet nie nalezy wykluczac sytuacji wychodzenia za planszê
        while (pozycja - 1 - ile >= 0 && poleOp[pozycja - 1 - ile] > 1) { //tablice nalezy sprawdzac tylko jezeli poza nia nie wyszlismy
            cout << "Dla podanej pozycji nie ma mozliwych ruchow! Wybierz inna pozycje: ";
            cin >> pozycja;
        }
    }
    else {                                            //Podczas gry nale¿y wykluczyæ sytuacje w których na docelowym polu jest wiecej ni¿ jeden pion przeciwnika lub gracz chce wyjœæ poza planszê
        while (poleOp[pozycja - 1 - ile] > 1 || pozycja - 1 - ile < 0) {
            cout << "Dla podanej pozycji nie ma mozliwych ruchow! Wybierz inna pozycje: ";
            cin >> pozycja;
        }
    }

    pozycja -= 1; //w tablicy indeksy s¹ numerowane od 0, a w grze od 1, dlategote¿ nale¿y zmniejszyæ liczbê aby by³a zgodna z oczekiwaniami graczy

}


void ruchBialy(unsigned poleB[], unsigned poleCZ[], int& zbiteB, int& zbiteCZ, int ile, int& bazaB) {
    int pozycja;
    if (zbiteB > 0) {
        cout << "Proba przywrocenia zbitego pionka na " << ile << " pole" << endl;
        system("pause");
        if (poleCZ[24 - ile] < 2) {
            poleB[24 - ile]++;
            zbiteB--;
            if (poleCZ[24 - ile] == 1) {
                poleCZ[24 - ile] = 0;
                zbiteCZ++;
            }
        }
        else {
            cout << "Ruch niemozliwy! Strata kolejki" << endl;
            system("pause");
            return;
        }
    }
    else if (domB(poleB, zbiteB)) {
        if (sprawdzRuchyB(poleB, poleCZ, ile, zbiteB) > 0) {
            cout << "Podaj pozycje do przesuniecia sie o " << ile << " pozycji. Mozesz juz schodzic pionkami do domu" << endl;
            wczytajPozycjeBialy(poleB, poleCZ, pozycja, ile, zbiteB);

            if (pozycja - ile < 0) {
                bazaB++;
                poleB[pozycja]--;
                cout << "zdobywasz punkt!" << endl;
                system("pause");
            }
            else {
                poleB[pozycja]--;
                poleB[pozycja - ile]++;
                if (poleCZ[pozycja - ile] == 1) {
                    poleCZ[pozycja - ile] = 0;
                    zbiteCZ++;
                }
            }
        }
        else {
            cout << "Brak mozliwych ruchow! " << endl;
            system("pause");
            return;
        }
    }
    else {
        if (sprawdzRuchyB(poleB, poleCZ, ile, zbiteB) > 0) {

            cout << "Wybierz pion do ruszenia sie o " << ile << " pozycji (podaj jego aktualna pozycje) ";
            wczytajPozycjeBialy(poleB, poleCZ, pozycja, ile, zbiteB);
            poleB[pozycja]--;
            poleB[pozycja - ile]++;
            if (poleCZ[pozycja - ile] == 1) {
                poleCZ[pozycja - ile] = 0;
                zbiteCZ++;
            }
        }
        else {
            cout << "Brak mozliwych ruchow! " << endl;
            return;
        }
    }
}


//dla czarnych pionów funkcje s¹ analogiczne. Wydzielone s¹ jednak dlatego, ¿e kieruje nimi nieco inna mechanika (bia³e poruszaj¹ siê od pola 24 do 1, a czarne od 1 do 24)

bool domCZ(unsigned poleCZ[], int zbiteCZ) {
    int suma = 0;
    for (int i = 0; i < 18; i++) {
        suma += poleCZ[i];
    }
    if (suma == 0 && zbiteCZ == 0) return 1;
    else return 0;
}


int sprawdzRuchyCZ(unsigned poleCZ[], unsigned poleB[], int ile, int zbiteCZ) {
    int ruchy = 0;
    if (domCZ(poleCZ, zbiteCZ)) {
        for (int i = 16; i < 24; i++) {
            if (poleCZ[i] > 0) {
                if (poleB[i + ile] < 2 || i + ile > 23) ruchy++; //gdy piony s¹ na pozycjach umo¿liwiajacych zejœcie do domu, mo¿liwe s¹ ruchy poza planszê
            }
        }
    }
    else {
        for (int i = 0; i < 24; i++) {
            if (poleCZ[i] > 0) {
                if (poleB[i + ile] < 2 && !(i + ile > 23)) ruchy++; //ruch jest mozliwy gdy na pozycji docelowej nie ma wiêcej ni¿ jednego piona przeciwnika i nie wychodzi siê za planszê
            }
        }
    }
    return ruchy;
}


void wczytajPozycjeCzarny(unsigned pole[], unsigned poleOp[], int& pozycja, int ile, int zbite) {
    cin >> pozycja;

    while (pole[pozycja - 1] < 1) {
        cout << "Na podanej pozycji nie ma twoich pionow! Wybierz inna pozycje: ";
        cin >> pozycja;
    }

    if (domB(pole, zbite)) {                          //w przypadku gdy wszystkie pionki s¹ w polu umo¿liwiaj¹cym powrot do domu, nie ma koniecznosci, a nawet nie nalezy wykluczac sytuacji wychodzenia za planszê
        while (pozycja - 1 + ile <= 23 && poleOp[pozycja - 1 + ile] > 1) { //tablice nalezy sprawdzac tylko jezeli poza nia nie wyszlismy
            cout << "Dla podanej pozycji nie ma mozliwych ruchow! Wybierz inna pozycje: ";
            cin >> pozycja;
        }
    }
    else {                                            //Podczas gry nale¿y wykluczyæ sytuacje w których na docelowym polu jest wiecej ni¿ jeden pion przeciwnika lub gracz chce wyjœæ poza planszê
        while (poleOp[pozycja - 1 + ile] > 1 || pozycja - 1 + ile > 23) {
            cout << "Dla podanej pozycji nie ma mozliwych ruchow! Wybierz inna pozycje: ";
            cin >> pozycja;
        }
    }
    pozycja -= 1; //w tablicy indeksy s¹ numerowane od 0, a w grze od 1, dlategote¿ nale¿y zmniejszyæ liczbê aby by³a zgodna z oczekiwaniami graczy

}


void ruchCzarny(unsigned poleCZ[], unsigned poleB[], int& zbiteCZ, int& zbiteB, int ile, int& bazaCZ) {
    int pozycja;
    if (zbiteCZ > 0) {
        cout << "Proba przywrocenia zbitego pionka na " << ile << " pole" << endl;
        system("pause");
        if (poleB[ile - 1] < 2) {
            poleCZ[ile - 1]++;
            zbiteCZ--;
            if (poleB[ile - 1] == 1) {
                poleB[ile - 1] = 0;
                zbiteB++;
            }
        }
        else {
            cout << "Ruch niemozliwy! Strata kolejki" << endl;
            system("pause");
            return;
        }
    }
    else if (domCZ(poleCZ, zbiteCZ)) {
        if (sprawdzRuchyCZ(poleCZ, poleB, ile, zbiteCZ) > 0) {
            cout << "Podaj pozycje do przesuniecia sie o " << ile << " pozycji. Mozesz juz schodzic pionkami do domu" << endl;
            wczytajPozycjeCzarny(poleB, poleCZ, pozycja, ile, zbiteB);

            if (pozycja + ile > 23) {
                bazaCZ++;
                poleB[pozycja]--;
                cout << "zdobywasz punkt!" << endl;
                system("pause");
            }
            else {
                poleCZ[pozycja]--;
                poleCZ[pozycja + ile]++;
                if (poleB[pozycja + ile] == 1) {
                    poleB[pozycja + ile] = 0;
                    zbiteB++;
                }
            }
        }
        else {
            cout << "Brak mozliwych ruchow! " << endl;
            system("pause");
            return;
        }
    }
    else {
        if (sprawdzRuchyCZ(poleCZ, poleB, ile, zbiteCZ) > 0) {

            cout << "Wybierz pion do ruszenia sie o " << ile << " pozycji (podaj jego aktualna pozycje) ";
            wczytajPozycjeCzarny(poleCZ, poleB, pozycja, ile, zbiteCZ);
            poleCZ[pozycja]--;
            poleCZ[pozycja + ile]++;
            if (poleB[pozycja + ile] == 1) {
                poleB[pozycja + ile] = 0;
                zbiteB++;
            }
        }
        else {
            cout << "Brak mozliwych ruchow! " << endl;
            return;
        }
    }
}
