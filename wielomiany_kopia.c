#include <stdio.h>
#include <stdbool.h>

#define STOPIEN 12

void zerowanie(int wiel[]){
    ;
}

int getchar_without_space(){
    int i = getchar();
    while(i == ' ') i = getchar();
    return i;
}


int wczytywanie_liczby(int i, int *stopien){ //wczytuje liczbe i wpisuje ja do stopien

    int aktualne;
    aktualne = i - 48;
    i = getchar();

    while(i != '-' && i != '+' && i != '\n' && i!='x'){
        aktualne *= 10;
        aktualne += i - 48;
        i = getchar();
    }

    *stopien = aktualne;

    return i;
}

int x(int znak, int wspol, int wiel[]){ // wpisuje x do tabeli, zwraca 0 jezeli koniec wielomianu -1/1 jezeli + lub -
    int i = getchar();
    int stopien = 1;

    if(i == '-' || i == '+' || i == '\n'){
        wiel[stopien+1] = znak * wspol;
        return i;
    }
    //i = '^'

    i = getchar();
    i = wczytywanie_liczby(i, &stopien);
    wiel[stopien+1] = znak * wspol;
    return i;
}


int czytanie_pojedynczego_wielomianu(int i,int wiel[]){

    int znak = 1;
    int stopien;
    int wspol = 1;

    while(i == ' ') i = getchar();

    if(i == '0'){ 
        zerowanie(wiel);
        return 0;
    }

    if(i == '+') i = getchar();
    
    if(i == '-'){
        znak = -1;
        i = getchar();
    }
    
    if(i == 'x'){
        wspol = 1;
        return x(znak,wspol,wiel);
    }
    i = wczytywanie_liczby(i, &wspol); //i to liczba
    if(i == 'x'){
        return x(znak,wspol,wiel);
    }
    wiel[1] = znak * wspol; //to znaczy ze to wielomian stopnia zero
    return 0;
}

int czytanie_wielomianu(int wiel[]){
    int i = getchar();
    while(i != '\n' && i != 0){
        i = czytanie_pojedynczego_wielomianu(i, wiel);
    }
    return 0;
}


int stopien_wielomianu(int a[]){
    int stopien = 0;
    for(int i = 1; i<STOPIEN; i++){
        if(a[i]) stopien = i-1; 
    }
    return stopien;
}

int suma(int a[], int b[]){
    for(int i = 1; i<STOPIEN; i++){
        a[i] += b[i];
    }
    a[0] = stopien_wielomianu(a);
    return 1;
}

int iloczyn(int a[], int b[]){
    int pom[STOPIEN];

    for(int i = 1; i<STOPIEN; i++){
        pom[i] = a[i];
        a[i] = 0;
    }

    for(int i= 1; i < STOPIEN; i++){
        for(int j = 1; j < STOPIEN; j++){ 
            if((j+i)-1 < STOPIEN){
                a[i+j-1] += (pom[j] * b[i]);
            }   
        }
    }
    a[0] = stopien_wielomianu(a);
    return 1;
}



int main(void){

    int a[STOPIEN] = {3,1,0,2,1,0,0,0,0,0,0,0};
    int b[STOPIEN] = {0,2,0,0,0,0,0,0,0,0,0,0};

    czytanie_wielomianu(a);

    //iloczyn(a,b);
    
    for(int i = 0; i < STOPIEN; i++){
        printf("%d ",a[i]);
    }
    printf("\n");

    return 0;
}