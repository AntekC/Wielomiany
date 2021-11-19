#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define STOPIEN 12

int getchar_without_space(){// funkcja zwraca znak z wejścia ale pomija spacje
    int i = getchar();
    while(i == ' '){
        i = getchar();
    }
    return i;
}

int stopien_wielomianu(int wiel[]){// zwraca stopien wielomianu z podanej tabeli
    int stopien = 0;
    for(int i = 1; i<STOPIEN; ++i){
        if(wiel[i] != 0) stopien = i-1; 
    }
    return stopien;
}

int wczytywanie_liczby(int i, int *liczba){// wczytuje liczbe z wyjscia i przypisuje ją do podanej zmiennej, zwraca kolejny znak z wyjścia
    assert(isdigit(i));
    int aktualne = i - '0';

    i = getchar_without_space();
    while(i != '-' && i != '+' && i != '\n' && i!='x'){
        aktualne *= 10;
        aktualne += i - '0';
        i = getchar_without_space();
    }
    *liczba = aktualne;
    return i;
}

int wczytywanie_jednomianu(int znak, int wspol, int wiel[]){ // wpisuje jednomian do tabeli i zwraca kolejny znak z wyjścia
    int i = getchar_without_space();
    int stopien = 1;

    if(i == '-' || i == '+' || i == '\n'){
        wiel[stopien+1] = znak * wspol;
        return i;
    }
    assert(i == '^');
    i = getchar_without_space();
    i = wczytywanie_liczby(i, &stopien);
    wiel[stopien+1] = znak * wspol;

    return i;
}

int czytanie_jednomianu(int i,int wiel[]){// czyta pojedyńczy jednomian i wpisuje go do podanej tabeli, zwraca kolejny znak z wyjścia
    int znak = 1;
    int wspol = 1;

    if(i == '0'){
        i = getchar_without_space();
        return i;
    }

    if(i == '+'){
        i = getchar_without_space();
    }
    
    if(i == '-'){
        znak = -1;
        i = getchar_without_space();
    }

    if(i == 'x'){
        wspol = 1;
        return wczytywanie_jednomianu(znak,wspol,wiel);
    }

    assert(isdigit(i));
    i = wczytywanie_liczby(i, &wspol);

    if(i == 'x'){
        return wczytywanie_jednomianu(znak,wspol,wiel);
    }

    wiel[1] = znak * wspol;

    return i;
}

void czytanie_wielomianu(int wiel[]){// czyta wielomian z wejscia i wpisywanie go podanej tabeli
    int i = getchar_without_space();
    while(i != '\n'){
        i = czytanie_jednomianu(i, wiel);
    }
    wiel[0] = stopien_wielomianu(wiel);
}

void suma(int a[], int b[]){// wpisuje sume wielomanu a i b do tabeli a
    for(int i = 1; i<STOPIEN; ++i){
        a[i] += b[i];
    }
    a[0] = stopien_wielomianu(a);
}

void iloczyn(int a[], int b[]){ //wpisuje iloczyn wielomianu a i b do tabeli a
    int pom[STOPIEN];

    for(int i = 1; i<STOPIEN; ++i){
        pom[i] = a[i];
        a[i] = 0;
    }

    for(int i= 1; i < STOPIEN; ++i){
        for(int j = 1; j < STOPIEN; ++j){ 
            if((j+i)-1 < STOPIEN){
                a[i+j-1] += (pom[j] * b[i]);
            }   
        }
    }
    a[0] = stopien_wielomianu(a);
}

void wypisywanie_wielomianu_stopnia_0_1(int wiel[]){// wypisuje wielomian stopnia pierwszego lub zerowego
    if(wiel[0] == 0) printf("%d\n",wiel[1]);
    if(wiel[0] == 1){
        if(wiel[2] == -1) printf("-x");
        else if(wiel[2] == 1) printf("x");
        else printf("%dx",wiel[2]);

        if(wiel[1] > 0) printf(" + %d\n",wiel[1]);
        else if(wiel[1] <0) printf(" - %d\n",(-1) * wiel[1]);
        else printf("\n");
    }
}

void wypisywanie_wielomianu(int wiel[]){// wyspisuje wielomian z tablicy na standardowe wyjśćie

    if( wiel[0] < 2){
        wypisywanie_wielomianu_stopnia_0_1(wiel);
    } else { // wypisywanie wielomianu stopnia wiekszego od 1
        if(wiel[wiel[0]+1] == 1) printf("x^%d",wiel[0]);
        else if(wiel[wiel[0]+1] == -1) printf("-x^%d",wiel[0]);
        else printf("%dx^%d", wiel[wiel[0]+1], wiel[0]);
        
        for(int i = wiel[0]; i > 2; i--){
            if(wiel[i] != 0){
                if(wiel[i] == 1) printf(" + x^%d",i-1);
                else if(wiel[i] == -1) printf(" - x^%d",i-1);
                else if(wiel[i] < 1) printf(" - %dx^%d",wiel[i]*(-1),i-1);
                else if(wiel[i] > 1) printf(" + %dx^%d",wiel[i],i-1);
            }
        }

        if(wiel[2] != 0){
            if(wiel[2] == -1) printf(" - x");
            else if(wiel[2] == 1) printf(" + x");
            else if(wiel[2] > 1) printf(" + %dx",wiel[2]);
            else printf(" - %dx",wiel[2]*(-1));
        }

        if(wiel[1] != 0){
            if(wiel[1] > 0) printf(" + %d",wiel[1]);
            else printf(" - %d",wiel[1]*(-1));
        }
        printf("\n");
    }

}

void kalkulator(int a[],int b[]){// wykonuje dodawanie i mnozenie na wielomanach dopoki nie napotka '.'
    int operacja = getchar();
    while(operacja != '.'){
        for(int i = 0; i<STOPIEN; ++i) b[i] = 0;
        czytanie_wielomianu(b);
        if(operacja == '+') suma(a,b);
        if(operacja == '*') iloczyn(a,b);
        wypisywanie_wielomianu(a);
        operacja = getchar();
    }
}

int main(void){

    int a[STOPIEN], b[STOPIEN];

    for(int i = 0; i<STOPIEN; ++i){
        a[i] = 0;
        b[i] = 0;
    }
    
    kalkulator(a,b);

    return 0;
}