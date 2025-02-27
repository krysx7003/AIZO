#include <iostream>
#include <stdlib.h>     
#include <time.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <chrono>
//Pliki do zapisu zadeklarowane globalnie
std::ofstream insertFileInt;
std::ofstream heapFileInt;
std::ofstream shellFile1Int;
std::ofstream shellFile2Int;
std::ofstream quickFileLInt;
std::ofstream quickFileMInt;
std::ofstream quickFileRInt;
std::ofstream quickFileRanInt;
std::ofstream insertFileFloat;
std::ofstream heapFileFloat;
std::ofstream shellFile1Float;
std::ofstream shellFile2Float;
std::ofstream quickFileLFloat;
std::ofstream quickFileMFloat;
std::ofstream quickFileRFloat;
std::ofstream quickFileRanFloat;

class Tabel{
//Zmienne zadeklarowane globalnie w klasie
int tabelLength;
int * tabInt;
float * tabFloat;   
public:
    void PrintInt(){
        //Program wypisuje elementy typu int tablicy jeden po drugim
        for(int i=0;i<tabelLength;i++)
        {    
            std::cout<<tabInt[i]<<", ";
        }
        std::cout<<"\n";//Koniec tablicy, program wypisuje znak nowa linia
    }
    void PrintFloat(){
        //Program wypisuje elementy typu float tablicy jeden po drugim
        for(int i=0;i<tabelLength;i++)
        {
            std::cout<<tabFloat[i]<<", ";
        }
        std::cout<<"\n";//Koniec tablicy, program wypisuje znak nowa linia
    }
    void PartialSort(int sortAmmount){
        //Program do wyznaczonej części tablic wstawia kolejne rosnące liczby
        for(int i=0;i<sortAmmount;i++){
            tabInt[i]=i;
            tabFloat[i]=i*0.1;
        }
        //Program wypełnia stworzone tablice liczbami losowymi
        for(int i=sortAmmount;i<tabelLength;i++)
        {   
            tabInt[i]= rand()% (RAND_MAX - sortAmmount + 1) + sortAmmount;
            tabFloat[i]= (float)(rand() % (RAND_MAX - sortAmmount + 1) + sortAmmount) / (float)(rand() % (RAND_MAX - sortAmmount + 1) + sortAmmount); ;
        }
    }
    int GetLength(){
        //Program zwraca długość tablicy
        return tabelLength;
    }
    void CopyTableInt(int newTabelInt[],float newTabelFloat[]){
        //Program kopiuje zawartość wygenerowanych tablic
        std::copy(tabInt,tabInt+tabelLength,newTabelInt);
        std::copy(tabFloat,tabFloat+tabelLength,newTabelFloat);
    }
    void ClearTabels(){
        //Program czyści pamięć by uniknąć wycieku pamięci
        delete[] tabInt;
        tabInt = nullptr;
        delete[] tabFloat;
        tabFloat = nullptr;
    }
    //Konstruktor klasy tabel
    Tabel(int length)
    {
        srand(time(NULL));//Program tworzy nowe ziarno losowości
        tabelLength = length;//Ustawienie długości tablicy
        //Program tworzy tablice dynamiczną typu float i int o zadanej długości 
        tabInt = new int[tabelLength];
        tabFloat = new float[tabelLength];
        //Program wypełnia stworzone tablice liczbami losowymi
        for(int i=0;i<tabelLength;i++)
        {
            tabInt[i]= rand();
            tabFloat[i]= (float)(rand()) / (float)(rand());
        }

    }
};
class SortAlg{
public:
    //Zmienne zadeklarowane globalnie w klasie
    int *toBeSortedInt;
    float *toBeSortedFloat;
    int timesSorted;
    int length;
    bool test;
    virtual bool CheckCorrectInt(){
        //Program sprawdza czy tablica jest niemalejąca
        for(int i=0;i<length-1;i++){
            if(toBeSortedInt[i]>toBeSortedInt[i+1]){
                return false;
            }
        }
        return true;
    }
    virtual bool CheckCorrectFloat(){
        //Program sprawdza czy tablica jest niemalejąca
        for(int i=0;i<length-1;i++){
            if(toBeSortedFloat[i]>toBeSortedFloat[i+1]){
                return false;
            }
        }
        return true;
    }
    void Refresh(Tabel tab){
        if(timesSorted!=0){
            Clear();//Cyszczenie zawartości tabel
        }
        //Program tworzy tablice dynamiczną typu float i int o zadanej długości 
        toBeSortedInt = new int[length];
        toBeSortedFloat = new float[length];  
        tab.CopyTableInt(toBeSortedInt,toBeSortedFloat);//Program ustawia zawrtość tabel na nieposortowane
    }
    virtual void Clear(){
        //Program czyści pamięć by uniknąć wycieku pamięci
        delete[] toBeSortedInt;
        toBeSortedInt = nullptr;
        delete[] toBeSortedFloat;
        toBeSortedFloat = nullptr;
    }
    //Konstruktor używany w symulacji
    SortAlg(Tabel tab){
        timesSorted=0;
        test = false;
        //Ustawienie długości
        length =tab.GetLength();
        //Program tworzy tablice dynamiczną typu float i int o zadanej długości 
        toBeSortedInt = new int[length];
        toBeSortedFloat = new float[length];
        Refresh(tab);
    }
    //Konstruktor testowy
    SortAlg(int newToBeSortedInt[],float newToBeSortedFloat[],int newLength){
        test = true;
        //Ustawienie długości
        length = newLength;
        //Przekazywane są tablice na potrzeby testów
        toBeSortedInt = newToBeSortedInt;
        toBeSortedFloat = newToBeSortedFloat;
    }
};
class Insert : public SortAlg{
//Sortowanie przez wstawianie
public:
    //Tablice zadeklarowane globalnie w klasie
    int *sortedInt;
    float *sortedFloat;
    int *GetSortedInt(){
        //Nadpisanie funkcji GetSortedInt ponieważ Insert sort nie jest w miejscu(wynik nie jest w tablicy toBeSorted)
        //Program zwraca posortowaną tablice typu int
        return sortedInt;
    }
    float *GetSortedFloat(){
        //Nadpisanie funkcji GetSortedFloat ponieważ Insert sort nie jest w miejscu(wynik nie jest w tablicy toBeSorted)
        //Program zwraca posortowaną tablice typu float
        return sortedFloat;
    }
    bool CheckCorrectInt()override{
        //Nadpisanie funkcji CheckCorrectInt ponieważ Insert sort nie jest w miejscu(wynik nie jest w tablicy toBeSorted)
        //Program sprawdza czy tablica jest niemalejąca
        for(int i=0;i<length-1;i++){
            if(sortedInt[i]>sortedInt[i+1]){
                return false;
            }
        }
        return true;
    }
    bool CheckCorrectFloat()override{
        //Nadpisanie funkcji CheckCorrectFloat ponieważ Insert sort nie jest w miejscu(wynik nie jest w tablicy toBeSorted)
        //Program sprawdza czy tablica jest niemalejąca
        for(int i=0;i<length-1;i++){
            if(sortedFloat[i]>sortedFloat[i+1]){
                return false;
            }
        }
        return true;
    }
    void Clear()override{
        //Nadpisanie funkcji Clear ponieważ Insert sort nie jest w miejscu(potrzebuje więcej tablic)
        //Program czyści pamięć by uniknąć wycieku pamięci
        delete[] toBeSortedInt;
        toBeSortedInt = nullptr;
        delete[] toBeSortedFloat;
        toBeSortedFloat = nullptr;
        delete[] sortedInt;
        sortedInt = nullptr;
        delete[] sortedFloat;
        sortedFloat = nullptr;
    }
    void InsertSortInt(){
        sortedInt = new int[length];//Program tworzy tablice dynamiczną typu float o zadanej długości 
        int lastId = 0;//Indeks ostatniej liczby w nowej tablicy
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        sortedInt[0]=toBeSortedInt[0];//Pierwszy element zostaje wstawiony poza pętlą
        for(int i=1;i<length;i++){
            int j=lastId;
            //Zaczynając od końca elementy przesuwane są w prawo tak długo jak większe są od i-tego elementu tablicy toBeSortedInt
            while (j >= 0 && toBeSortedInt[i] < sortedInt[j]) {
                sortedInt[j + 1] = sortedInt[j];
                j--;
            }
            sortedInt[j + 1] = toBeSortedInt[i];//Wstawienie i-tego elementu tablicy toBeSortedInt w odpowiednie miejce posortowanej tablicy
            lastId++;//Zwiększenie ostattniej pozycji o 1
        } 
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania

        if(CheckCorrectInt()==true){
            if(test==false){insertFileInt<<duration.count()<<";";}
            else{std::cout<<"Tabela jest niemalejąca\n";}
        }else{
            insertFileInt<<"niepoprawne sortowanie"<<";";//Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        }       
    }
    void InsertSortFloat(){
        sortedFloat = new float[length];//Program tworzy tablice dynamiczną typu float o zadanej długości 
        int lastId = 0;//Indeks ostatniej liczby w nowej tablicy
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        sortedFloat[0]=toBeSortedFloat[0];//Pierwszy element zostaje wstawiony poza pętlą
        for(int i=1;i<length;i++){
            int j=lastId;
            //Zaczynając od końca elementy przesuwane są w prawo tak długo jak większe są od i-tego elementu tablicy toBeSortedInt
            while (j >= 0 && toBeSortedFloat[i] < sortedFloat[j]) {
                sortedFloat[j + 1] = sortedFloat[j];
                j--;
            }
            sortedFloat[j + 1] = toBeSortedFloat[i];//Wstawienie i-tego elementu tablicy toBeSortedInt w odpowiednie miejce posortowanej tablicy
            lastId++;//Zwiększenie ostattniej pozycji o 1
        } 
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        if(CheckCorrectFloat()==true){
            if(test==false){insertFileFloat<<duration.count()<<";";}
            else{std::cout<<"Tabela jest niemalejąca\n";}
        }else{
            insertFileFloat<<"niepoprawne sortowanie"<<";";//Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        }   
    }
    //Konstruktor używany w symulacji
    Insert(Tabel tab):SortAlg(tab){}
    //Konstruktor testowy
    Insert(int newToBeSortedInt[],float newToBeSortedFloat[],int newLength):SortAlg(newToBeSortedInt,newToBeSortedFloat,newLength){}
    };

class Heap : public SortAlg{
//Sortowanie przez kopcowanie
public:
    void TurnToHeapInt(int lengthToCheck,int parent){
        int largest = parent;//Zakłada prawdziwość właściwości kopca
        int rightChild = 2*parent+1;//Tabica indeksowana od 0, dzieci rodzica wyliczone ze wzoru
        int leftChild = 2*parent+2;//Tabica indeksowana od 0, dzieci rodzica wyliczone ze wzoru
        //Jeżeli nie przekroczono długości ciągu/podciągu i jeżeli lewe dziecko >rodzic
        if (leftChild < lengthToCheck && toBeSortedInt[leftChild] > toBeSortedInt[largest]){
            //Zmiana największego indeksu
            largest = leftChild;
        }
        //Jeżeli nie przekroczono długości ciągu/podciągu i jeżeli praw dziecko >wynik poprzedniego działania     
        if (rightChild < lengthToCheck && toBeSortedInt[rightChild] > toBeSortedInt[largest]){
            //Zmiana największego indeksu
            largest = rightChild;
        }  
        //Jeżeli właściwość kopca jest nieprawdziwa  
        if (largest != parent) {
            //Zmiana największego elementu z rodzicem
            std::swap(toBeSortedInt[parent], toBeSortedInt[largest]);
            //Przywrócenie właściwości kopca
            TurnToHeapInt(lengthToCheck, largest);
        }
        
    }
    void HeapSortInt(){
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        //Nadanie tablic własności kopca maksymalnego, ostatni rodzic jest length/2 elementem tablicy dalej są tylko liście
        for(int i=(length/2);i>=0;i--){
            TurnToHeapInt(length,i);
        }
        //Program sortuje przez kopcowanie całą tablice
        for(int i=length-1;i>0;i--){
            //Zamiana pierwszego elementu(największego) z ostatnim
            std::swap(toBeSortedInt[0],toBeSortedInt[i]);
            //Przywrócenie właściwości kopca dla pozostałych elementów
            TurnToHeapInt(i,0);
        }
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        if(CheckCorrectInt()){
            if(test==false){heapFileInt<<duration.count()<<";";}
            else{std::cout<<"Tabela jest niemalejąca\n";}
        }else{
            heapFileInt<<"niepoprawne sortowanie"<<";";//Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        } 
    }
    void TurnToHeapFloat(int lengthToCheck,int parent){
        int largest = parent;//Zakłada prawdziwość właściwości kopca
        int rightChild = 2*parent+1;//Tabica indeksowana od 0, dzieci rodzica wyliczone ze wzoru
        int leftChild = 2*parent+2;//Tabica indeksowana od 0, dzieci rodzica wyliczone ze wzoru
        //Jeżeli nie przekroczono długości ciągu/podciągu i jeżeli lewe dziecko >rodzic
        if (leftChild < lengthToCheck && toBeSortedFloat[leftChild] > toBeSortedFloat[largest]){
            //Zmiana największego indeksu
            largest = leftChild;
        }
        //Jeżeli nie przekroczono długości ciągu/podciągu i jeżeli praw dziecko >wynik poprzedniego działania     
        if (rightChild < lengthToCheck && toBeSortedFloat[rightChild] > toBeSortedFloat[largest]){
            //Zmiana największego indeksu 
            largest = rightChild;
        }
        //Jeżeli właściwość kopca jest nieprawdziwa   
        if (largest != parent) {
            //Zmiana największego elementu z rodzicem
            std::swap(toBeSortedFloat[parent], toBeSortedFloat[largest]);
            //Przywrócenie właściwości kopca
            TurnToHeapFloat(lengthToCheck, largest);
        }
    }
    void HeapSortFloat(){
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        //Nadanie tablic własności kopca maksymalnego, ostatni rodzic jest length/2 elementem tablicy dalej są tylko liście
        for(int i=(length/2);i>=0;i--){
            TurnToHeapFloat(length,i);
        }
        //Program sortuje przez kopcowanie całą tablice
        for(int i=length-1;i>0;i--){
            //Zamiana pierwszego elementu(największego) z ostatnim
            std::swap(toBeSortedFloat[0],toBeSortedFloat[i]);
            //Przywrócenie właściwości kopca dla pozostałych elementów
            TurnToHeapFloat(i,0);
        }
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        if(CheckCorrectFloat()){
            if(test==false){heapFileFloat<<duration.count()<<";";}
            else{std::cout<<"Tabela jest niemalejąca\n";}
        }else{
            heapFileFloat<<"niepoprawne sortowanie"<<";";//Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        }
        
    }
    //Konstruktor używany w symulacji
    Heap(Tabel tab):SortAlg(tab){}
    //Konstruktor testowy
    Heap(int newToBeSortedInt[],float newToBeSortedFloat[],int newLength):SortAlg(newToBeSortedInt,newToBeSortedFloat,newLength){}
    };
class Shell : public SortAlg{
//Sortowanie algorytmem shella
public:
    void ShellSort1Int(){
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        //Program tworzy szczeline 
        for(int gap=length/2;gap>0;gap/=2){//Przy każdej iteracj sczelina jest dzielona na 2
            //Program wybiera elementy oddzielone od siebie o szczelinę
            for(int i=gap;i<length;i++){
                //I-ty element zostaje tymczasowo zapisany
                int tmp=toBeSortedInt[i];
                int j;
                //Program porównuje elementy oddzielone od siebie o szczelinę
                for(j=i;j>=gap && toBeSortedInt[j-gap]>tmp;j=j-gap){
                    //Program przesuwa elementy na odpowiedzie miejsce 
                    toBeSortedInt[j] = toBeSortedInt[j-gap];
                }
                //Element tymczasowy zostaje zapisany w j-tym elemencie tablicy
                toBeSortedInt[j]=tmp;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        if(CheckCorrectInt()){
            if(test==false){shellFile1Int<<duration.count()<<";";}
            else{std::cout<<"Tabela jest niemalejąca\n";}
        }else{
            shellFile1Int<<"niepoprawne sortowanie"<<";";//Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        }
          
    }
    void ShellSort1Float(){
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        //Program tworzy szczeline 
        for(int gap=length/2;gap>0;gap/=2){//Przy każdej iteracj sczelina jest dzielona na 2
            //Program wybiera elementy oddzielone od siebie o szczelinę
            for(int i=gap;i<length;i++){
                //I-ty element zostaje tymczasowo zapisany 
                float tmp=toBeSortedFloat[i];
                int j;
                //Program porównuje elementy oddzielone od siebie o szczelinę
                for(j=i;j>=gap && toBeSortedFloat[j-gap]>tmp;j=j-gap){
                    //Program przesuwa elementy na odpowiedzie miejsce 
                    toBeSortedFloat[j] = toBeSortedFloat[j-gap];
                }
                //Element tymczasowy zostaje zapisany w j-tym elemencie tablicy
                toBeSortedFloat[j]=tmp;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        if(CheckCorrectFloat()){
            if(test==false){shellFile1Float<<duration.count()<<";";}
            else{std::cout<<"Tabela jest niemalejąca\n";}
        }else{
            shellFile1Float<<"niepoprawne sortowanie"<<";";//Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        }
         
    }
    void ShellSort2Int(){
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        //Program tworzy szczeline 
        for(int k = 1; (1 << k) - 1 < length; ++k){//Przy każdej iteracj sczelina jest przesuwana bitowo o 1 bit(mnożona razy 2) a następnie odejmowane jest 1
            int gap = (1 << k) - 1;
            //Program wybiera elementy oddzielone od siebie o szczelinę
            for(int i=gap;i<length;i++){
                //I-ty element zostaje tymczasowo zapisany 
                int tmp=toBeSortedInt[i];
                int j;
                //Program porównuje elementy oddzielone od siebie o szczelinę
                for(j=i;j>=gap && toBeSortedInt[j-gap]>tmp;j=j-gap){
                    //Program przesuwa elementy na odpowiedzie miejsce 
                    toBeSortedInt[j] = toBeSortedInt[j-gap];
                }
                //Element tymczasowy zostaje zapisany w j-tym elemencie tablicy
                toBeSortedInt[j]=tmp;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        if(CheckCorrectInt()){
            if(test==false){shellFile2Int<<duration.count()<<";";}
            else{std::cout<<"Tabela jest niemalejąca\n";}
        }else{
            shellFile2Int<<"niepoprawne sortowanie"<<";";//Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        }
          
    }
    void ShellSort2Float(){
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        //Program tworzy szczeline 
        for(int k = 1; (k*2) - 1 < length; ++k){//Przy każdej iteracj sczelina jest przesuwana bitowo o 1 bit(mnożona razy 2) a następnie odejmowane jest 1 
            int gap = (k*2) - 1;
            //Program wybiera elementy oddzielone od siebie o szczelinę
            for(int i=gap;i<length;i++){
                //I-ty element zostaje tymczasowo zapisany 
                float tmp=toBeSortedFloat[i];
                int j;
                for(j=i;j>=gap && toBeSortedFloat[j-gap]>tmp;j=j-gap){
                    //Program przesuwa elementy na odpowiedzie miejsce
                    toBeSortedFloat[j] = toBeSortedFloat[j-gap];
                }
                //Element tymczasowy zostaje zapisany w j-tym elemencie tablicy
                toBeSortedFloat[j]=tmp;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        if(CheckCorrectFloat()){
            if(test==false){shellFile2Float<<duration.count()<<";";}
            else{std::cout<<"Tabela jest niemalejąca\n";}
        }else{
            shellFile2Float<<"niepoprawne sortowanie"<<";";//Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        }
          
    }
    //Konstruktor używany w symulacji
    Shell(Tabel tab):SortAlg(tab){}
    //Konstruktor testowy
    Shell(int newToBeSortedInt[],float newToBeSortedFloat[],int newLength):SortAlg(newToBeSortedInt,newToBeSortedFloat,newLength){}
    };
class Quick : public SortAlg{
//Klas Qucik odowiada za szybkie sortowanie
public:
    int mode;
    void setMode(int newMode){
        mode=newMode;//Ustaw wybrany tryb
    }
    void IncMode(){
        mode++;//Zwiększenie trybu o 1
        //Jeśli przekracza zakres cofnięcie do 1
        if(mode>4){
            mode=1;
        }
    }
    int ChosePivotInt(int start,int stop){
        //Wybór indeksu pivota
        switch (mode)
        {
            case 1:
                return start;//Skrajnie lewy
                break;
            case 2:
                return (start+stop)/2;//Środkowy
                break;
            case 3:
                return stop;//Skrajnie prawy
                break;
            case 4:
                return rand()% (stop - start + 1) + start;//Losowy z zakresu start-stop
                break;
            default:
                return 0;
        }
    }
    void QuickSortInt(int start,int stop){
        
        int i = start;//Indeks i to początek ciągu/podciągu
        int j = stop;//Indeks j to koniec ciągu/podciągu
        int pivot = toBeSortedInt[ChosePivotInt(start,stop)];//Wybór wartości pivota według wybranego trybu
        while (i <= j) {
            //Iteracja z obu końców tablicy
            //Jeżeli i-ty element jest mniejszy od pivota zostaje wybrany
            while (toBeSortedInt[i] < pivot) {
                i++;
            }
            //Jeżeli j-ty element jest większy od pivota zostaje wybrany
            while (toBeSortedInt[j] > pivot) {
                j--;
            }
            //Jeżeli ideksy się nie przecięły
            if (i <= j) {
                //Wybrane elementy zostają zamienione 
                std::swap(toBeSortedInt[i], toBeSortedInt[j]);
                i++;
                j--;
            }
        }
        //Warunkowa rekurencja
        if (start < j) {
            QuickSortInt(start, j);
        }
        if (i < stop) {
            QuickSortInt(i, stop);
        }
        
    }
    void QuickSortPrepInt(){
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        QuickSortInt(0,length-1);
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Dla aktualnego trybu program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        //Jeżeli sortowanie jest niepoprawne program zwraca tą informacje
        switch (mode)
        {
        case 1:
            if(CheckCorrectInt()){
                if(test==false){quickFileLInt<<duration.count()<<";";}
                else{std::cout<<"Tabela jest niemalejąca\n";}                
            }
            else{quickFileLInt<<"niepoprawne sortowanie";}
            break;
        case 2:
            if(CheckCorrectInt()){
                if(test==false){quickFileMInt<<duration.count()<<";";}
                else{std::cout<<"Tabela jest niemalejąca\n";}
            }
            else{quickFileMInt<<"niepoprawne sortowanie";}
            break;
        case 3:
            if(CheckCorrectInt()){
                if(test==false){quickFileRInt<<duration.count()<<";";}
                else{std::cout<<"Tabela jest niemalejąca\n";}
            }
            else{quickFileMInt<<"niepoprawne sortowanie";}
            break;
        case 4:
            if(CheckCorrectInt()){
                if(test==false){quickFileRanInt<<duration.count()<<";";}
                else{std::cout<<"Tabela jest niemalejąca\n";}
            }
            else{quickFileMInt<<"niepoprawne sortowanie";}
            break;
        }
    }
    float ChosePivotFloat(int start,int stop){
        //Wybór indeksu pivota
        switch (mode)
        {
            case 1:
                return start;//Skrajnie lewy
                break;
            case 2:
                return (start+stop)/2;//Środkowy
                break;
            case 3:
                return stop;//Skrajnie prawy
                break;
            case 4:
                return rand()% (stop - start + 1) + start;//Losowy z zakresu start-stop
                break;
            default:
                return 0;
        }
    }
    void QuickSortFloat(int start,int stop){ 
        int i = start;//Indeks i to początek ciągu/podciągu
        int j = stop;//Indeks j to koniec ciągu/podciągu
        float pivot = toBeSortedFloat[ChosePivotInt(start,stop)];//Wybór wartości pivota według wybranego trybu
        while (i <= j) {
            //Iteracja z obu końców tablicy
            //Jeżeli i-ty element jest mniejszy od pivota zostaje wybrany
            while (toBeSortedFloat[i] < pivot) {
                i++;
            }
            //Jeżeli j-ty element jest większy od pivota zostaje wybrany
            while (toBeSortedFloat[j] > pivot) {
                j--;
            }
            //Jeżeli ideksy się nie przecięły
            if (i <= j) {
                //Wybrane elementy zostają zamienione 
                std::swap(toBeSortedFloat[i], toBeSortedFloat[j]);
                i++;
                j--;
            }
        }
        //Warunkowa rekurencja
        if (start < j) {
            QuickSortFloat(start, j);
        }
        if (i < stop) {
            QuickSortFloat( i, stop);
        }
        
    }
    void QuickSortPrepFloat(){
        auto start = std::chrono::high_resolution_clock::now();//Początek pomiaru czasu
        QuickSortFloat(0,length-1);
        //time measurement
        auto end = std::chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        std::chrono::duration<double, std::nano> duration = end - start;//Czas wykonania zapisany w ns
        //Dla aktualnego trybu program sprawdza poprawność sortowania i jeżeli obiekt nie jest w trybie testowym to zapisuje czas wykonania
        switch (mode)
        {
        case 1:
            if(CheckCorrectFloat()){
                if(test==false){quickFileLFloat<<duration.count()<<";";}
                else{std::cout<<"Tabela jest niemalejąca\n";}
            }
            else{quickFileLFloat<<"niepoprawne sortowanie";}
            break;
        case 2:
            if(CheckCorrectFloat()){
                if(test==false){quickFileMFloat<<duration.count()<<";";}
                else{std::cout<<"Tabela jest niemalejąca\n";}
            }
            else{quickFileMFloat<<"niepoprawne sortowanie";}
            break;
        case 3:
            if(CheckCorrectFloat()){
                if(test==false){quickFileRFloat<<duration.count()<<";";}
                else{std::cout<<"Tabela jest niemalejąca\n";}
            }
            else{quickFileMFloat<<"niepoprawne sortowanie";}
            break;
        case 4:
            if(CheckCorrectFloat()){
                if(test==false){quickFileRanFloat<<duration.count()<<";";}
                else{std::cout<<"Tabela jest niemalejąca\n";}
            }
            else{quickFileMFloat<<"niepoprawne sortowanie";}
            break;
        }
        
    }
    //Konstruktor używany w symulacji
    Quick(Tabel tab):SortAlg(tab){
        mode =1;//Bazowo używany jest tryb 1(pivot skrajnie lewy)
    }
    //Konstruktor testowy
    Quick(int newToBeSortedInt[],float newToBeSortedFloat[],int newLength,int newMode):SortAlg(newToBeSortedInt,newToBeSortedFloat,newLength){
        mode=newMode;
    }
    };    

class Simulation{
    //Nazwy zdeklarowane w całej klasie dla wygody
    std::string insertName ="InsertSortResoult.txt";
    std::string heapName = "HeapSortResoult.txt";
    std::string shellName = "ShellSortResoult.txt";
    std::string quickName = "QuickSortResoult.txt";
    void CallAllSorts(Insert insertSort,Heap heapSort,Shell shellSort,Quick quickSort,Tabel tab){
        //Program wywołuje sortowanie przez wstawianie
        insertSort.Refresh(tab);//Odświerzenie tablic obiektu insertSort
        insertSort.InsertSortInt();//Sortowanie tablicy typu int
        insertSort.InsertSortFloat();//Sortowanie tablicy typu float
        insertSort.Clear();//Zwolnienie pamięci
        //Program wywołuje sortowanie przez kopcowanie
        heapSort.Refresh(tab);//Odświerzenie tablic obiektu heapSort
        heapSort.HeapSortInt();//Sortowanie tablicy typu int
        heapSort.HeapSortFloat();//Sortowanie tablicy typu float
        heapSort.Clear();//Zwolnienie pamięci
        //Program wywołuje sortowanie Shella o wyrazie ogólnym floor(length/(2^k))
        shellSort.Refresh(tab);//Odświerzenie tablic obiektu shellSort
        shellSort.ShellSort1Int();//Sortowanie tablicy typu int
        shellSort.ShellSort1Float();//Sortowanie tablicy typu float
        shellSort.Clear();//Zwolnienie pamięci
        //Program wywołuje sortowanie Shella o wyrazie ogólnym (2^k)-1
        shellSort.Refresh(tab);//Odświerzenie tablic obiektu shellSort
        shellSort.ShellSort2Int();//Sortowanie tablicy typu int
        shellSort.ShellSort2Float();//Sortowanie tablicy typu float
        shellSort.Clear();//Zwolnienie pamięci
        //Program wywołuje sortowanie szybkie przy wyborze pivota skrajnie lewego
        quickSort.Refresh(tab);//Odświerzenie tablic obiektu quickSort
        if(tab.GetLength()<40000){
            quickSort.QuickSortPrepInt();//Sortowanie tablicy typu int
            quickSort.QuickSortPrepFloat();//Sortowanie tablicy typu float  
        }else{
            quickFileLFloat<<"0;";
            quickFileLInt<<"0;";
        }
        quickSort.IncMode();//Zmienia tryb wyboru pivota na 2 (środkowy)
        quickSort.Clear();//Zwolnienie pamięci
        //Program wywołuje sortowanie szybkie przy wyborze pivota  środkowego
        quickSort.Refresh(tab);//Odświerzenie tablic obiektu quickSort
        quickSort.QuickSortPrepInt();//Sortowanie tablicy typu int
        quickSort.QuickSortPrepFloat();//Sortowanie tablicy typu float
        quickSort.IncMode();//Zmienia tryb wyboru pivota na 3(skrajnie prawy)
        quickSort.Clear();//Zwolnienie pamięci
        //Program wywołuje sortowanie szybkie przy wyborze pivota skrajnie prawego
        quickSort.Refresh(tab);//Odświerzenie tablic obiektu quickSort
        if(tab.GetLength()<40000){
            quickSort.QuickSortPrepInt();//Sortowanie tablicy typu int
            quickSort.QuickSortPrepFloat();//Sortowanie tablicy typu float  
        }else{
            quickFileRFloat<<"0;";
            quickFileRInt<<"0;";
        }
        quickSort.IncMode();//Zmienia tryb wyboru pivota na 4(losowy)
        quickSort.Clear();//Zwolnienie pamięci
        //Program wywołuje sortowanie szybkie przy wyborze pivota losowego
        quickSort.Refresh(tab);//Odświerzenie tablic obiektu quickSort
        quickSort.QuickSortPrepInt();//Sortowanie tablicy typu int
        quickSort.QuickSortPrepFloat();//Sortowanie tablicy typu float
        quickSort.IncMode();//Zmienia tryb wyboru pivota na 1(skrajnie lewy)
        quickSort.Clear();//Zwolnienie pamięci
    }
    void OpenAllFiles(){
        //Program otwiera wszystkie pliki tekstowe według wybranej konwencj
        insertFileInt.open("Int"+insertName,std::ios_base::app);
        heapFileInt.open("Int"+heapName,std::ios_base::app);
        shellFile1Int.open("Int"+shellName.substr(0,9)+"1"+shellName.substr(10,shellName.length()),std::ios_base::app);
        shellFile2Int.open("Int"+shellName.substr(0,9)+"2"+shellName.substr(10,shellName.length()),std::ios_base::app);
        quickFileLInt.open("IntL"+quickName,std::ios_base::app);
        quickFileMInt.open("IntM"+quickName,std::ios_base::app);
        quickFileRInt.open("IntR"+quickName,std::ios_base::app);
        quickFileRanInt.open("IntRan"+quickName,std::ios_base::app);
        insertFileFloat.open("Float"+insertName,std::ios_base::app);
        heapFileFloat.open("Float"+heapName,std::ios_base::app);
        shellFile1Float.open("Float"+shellName.substr(0,9)+"1"+shellName.substr(10,shellName.length()),std::ios_base::app);
        shellFile2Float.open("Float"+shellName.substr(0,9)+"2"+shellName.substr(10,shellName.length()),std::ios_base::app);
        quickFileLFloat.open("FloatL"+quickName,std::ios_base::app);
        quickFileMFloat.open("FloatM"+quickName,std::ios_base::app);
        quickFileRFloat.open("FloatR"+quickName,std::ios_base::app);
        quickFileRanFloat.open("FloatRan"+quickName,std::ios_base::app);
    }
    void AllPrint(std::string stringToWrite){
        //We wszystkich plikach wypisywane jest new line
        insertFileInt<<stringToWrite;
        heapFileInt<<stringToWrite;
        shellFile1Int<<stringToWrite;
        shellFile2Int<<stringToWrite;
        quickFileLInt<<stringToWrite;
        quickFileMInt<<stringToWrite;
        quickFileRInt<<stringToWrite;
        quickFileRanInt<<stringToWrite;
        insertFileFloat<<stringToWrite;
        heapFileFloat<<stringToWrite;
        shellFile1Float<<stringToWrite;
        shellFile2Float<<stringToWrite;
        quickFileLFloat<<stringToWrite;
        quickFileMFloat<<stringToWrite;
        quickFileRFloat<<stringToWrite;
        quickFileRanFloat<<stringToWrite;
    }
    void CloseAllFiles(){
        //Program zmyka wszystkie pliki tekstowe
        insertFileInt.close();
        heapFileInt.close();
        shellFile1Int.close();
        shellFile2Int.close();
        quickFileLInt.close();
        quickFileMInt.close();
        quickFileRInt.close();
        quickFileRanInt.close();
        insertFileFloat.close();
        heapFileFloat.close();
        shellFile1Float.close();
        shellFile2Float.close();
        quickFileLFloat.close();
        quickFileMFloat.close();
        quickFileRFloat.close();
        quickFileRanFloat.close();
    }
public:
    void Start(int tabelLength,int tabelCount){
        srand (time(NULL));//Program tworzy nowe ziarno losowości
        insertName ="InsertSortResoult.txt";
        heapName = "HeapSortResoult.txt";
        shellName = "ShellSortResoult.txt";
        quickName = "QuickSortResoult.txt";
        OpenAllFiles();//Otwierane są pliki tekstowe w konwencj typNazwaSortResoult.txt
        AllPrint(std::to_string(tabelLength)+"\n");
        CloseAllFiles();
        for(int i=0;i<tabelCount;i++)
        {
            Tabel tab(tabelLength);//Program wywołuje konstruktor obiektu Tabel
            int length =tab.GetLength();//Program pobiera długość tablic z obiektu tab
            int timesSorted=0;
            //Program używa konstuktorów dla wszystkich algorytmów sortowania, przekazywane są obie tablice(int i float)
            Insert insertSort(tab);
            Heap heapSort(tab);
            Shell shellSort(tab);
            Quick quickSort(tab);
            //Program sortuje w pełni nieposortowane tablice
            OpenAllFiles();//Otwierane są pliki tekstowe w konwencj typNazwaSortResoult.txt
            
            CallAllSorts(insertSort,heapSort,shellSort,quickSort,tab);
            CloseAllFiles();
            //Program sortuje w 1/3 posortowane tablice
            tab.PartialSort(length/3);//Program ustawia pierwsze length/3 liczb na 1,2,3... lub 0.1,0.2,0.3,...
            timesSorted++;
            OpenAllFiles();//Otwierane są pliki tekstowe w konwencj typNazwaSortResoult1/3.txt
            CallAllSorts(insertSort,heapSort,shellSort,quickSort,tab);
            CloseAllFiles();
            //Program sortuje w 2/3 posortowane tablice
            tab.PartialSort(length*2/3);//Program ustawia pierwsze length*2/3 liczb na 1,2,3... lub 0.1,0.2,0.3,...
            timesSorted++;
            OpenAllFiles();//Otwierane są pliki tekstowe w konwencj typNazwaSortResoult2/3.txt
            CallAllSorts(insertSort,heapSort,shellSort,quickSort,tab);
            CloseAllFiles();
            //Program sortuje w pełni posortowane tablice
            tab.PartialSort(length);//Program wszystkie liczby na 1,2,3... lub 0.1,0.2,0.3,...
            timesSorted++;
            OpenAllFiles();//Otwierane są pliki tekstowe w konwencj typNazwaSortResoultFull.txt
            CallAllSorts(insertSort,heapSort,shellSort,quickSort,tab);
            AllPrint("\n");
            CloseAllFiles();
        }
    }
};
int length;
//Tablice zadeklarowane globalnie dla wygody
int *tabelInt;
float *tabelFloat;
int *sortedTabelInt;
float *sortedTabelFloat;
int tableLength,tableCount;
void menu();
void menuAlg(int length,char choiceOftype){
    //Podstawowe tekstowe menu wyboru algorytmu
    std::cout<<"=====================================\n";
    std::cout<<"           Wybierz Algorytm          \n";
    std::cout<<"=====================================\n";
    std::cout<<"1.Insert Sort\n";
    std::cout<<"2.Heap Sort\n";
    std::cout<<"3.Shell Sort(N/(2^k))\n";
    std::cout<<"4.Shell Sort((2^k)-1)\n";
    std::cout<<"5.Quick Sort(pivot skrajny lewy)\n";
    std::cout<<"6.Quick Sort(pivot skrajny prawy)\n";
    std::cout<<"7.Quick Sort(pivot srodek)\n";
    std::cout<<"8.Quick Sort(pivot losowy)\n";
    std::cout<<"9.Wroc do menu\n";
    std::cout<<"=====================================\n";
    int choice;
    //Program używa konstuktorów testowych dla wszystkich algorytmów sortowania, przekazywane są obie tablice(int i float)
    Insert ins(sortedTabelInt,sortedTabelFloat,length);
    Heap hea(sortedTabelInt,sortedTabelFloat,length);
    Shell she(sortedTabelInt,sortedTabelFloat,length);
    Quick qui(sortedTabelInt,sortedTabelFloat,length,1);
    std::cout<<"Wybierz akcje: ";//Zapytanie do użytkownika
    std::cin>>choice;
    switch (choice)
    {
    case 1:
        std::cout<<"=====================================\n";
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype=='i'){
            ins.InsertSortInt();//Program wykonuje sortowanie tablicy int algorytmem insert sort
            sortedTabelInt=ins.GetSortedInt();//Program przekazuje posortowaną tablice do sortedTabelInt
        }else{
            ins.InsertSortFloat();//Program wykonuje sortowanie tablicy float algorytmem insert sort
            sortedTabelFloat=ins.GetSortedFloat();//Program przekazuje posortowaną tablice do sortedTabelFloat
        }
        break;
    case 2:
        std::cout<<"=====================================\n";
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype=='i'){
            hea.HeapSortInt();//Program wykonuje sortowanie tablicy int algorytmem heap sort
        }
        else{
            hea.HeapSortFloat();//Program wykonuje sortowanie tablicy float algorytmem heap sort
        }   
        break;
    case 3:
        std::cout<<"=====================================\n";
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype=='i'){
            she.ShellSort1Int();//Program wykonuje sortowanie tablicy int algorytmem shell sort o wyrazie ogólnym(floor(length/(2^k)))
        }
        else{
            she.ShellSort1Float();//Program wykonuje sortowanie tablicy float algorytmem shell sort o wyrazie ogólnym(floor(length/(2^k)))
        }       
        break;
    case 4:
        std::cout<<"=====================================\n";
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype=='i'){
            she.ShellSort2Int();//Program wykonuje sortowanie tablicy int shell sort o wyrazie ogólnym(floor((2^k)-1))
        }
        else{
            she.ShellSort2Float();//Program wykonuje sortowanie tablicy float shell sort o wyrazie ogólnym(floor((2^k)-1)) 
        }       
        break;
    case 5:
        std::cout<<"=====================================\n";
        qui.setMode(1);
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype=='i'){
            qui.QuickSortPrepInt();//Program wykonuje sortowanie tablicy int algorytmem quick sort(pivot skrajnie lewy)
        }
        else{
           qui.QuickSortPrepFloat();//Program wykonuje sortowanie tablicy float algorytmem quick sort(pivot skrajnie lewy)
        }       
        break;
    case 6:
        std::cout<<"=====================================\n";
        qui.setMode(2);
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype=='i'){
            qui.QuickSortPrepInt();//Program wykonuje sortowanie tablicy int algorytmem quick sort(pivot środkowy)
        }
        else{
           qui.QuickSortPrepFloat();//Program wykonuje sortowanie tablicy float algorytmem quick sort(pivot środkowy)
        }      
        break;
    case 7:
        std::cout<<"=====================================\n";
        qui.setMode(3);
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype=='i'){
            qui.QuickSortPrepInt();//Program wykonuje sortowanie tablicy int algorytmem quick sort(pivot skrajnie prawy)
        }
        else{
           qui.QuickSortPrepFloat();//Program wykonuje sortowanie tablicy float algorytmem quick sort(pivot skrajnie prawy)
        }     
        break;
    case 8:
        std::cout<<"=====================================\n";
        qui.setMode(4);
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype=='i'){
            qui.QuickSortPrepInt();//Program wykonuje sortowanie tablicy int algorytmem quick sort(pivot losowy)
        }
        else{
           qui.QuickSortPrepFloat();//Program wykonuje sortowanie tablicy float algorytmem quick sort(pivot losowy)
        }
        break; 
    case 9:
        std::cout<<"=====================================\n";
        menu();//Program wraca do menu
        break;       
    }

}

void menu(){
    //Podstawowe tekstowe menu
    std::cout<<"=====================================\n";
    std::cout<<"                Menu                 \n";
    std::cout<<"=====================================\n";
    std::cout<<"1.Wczytaj tablice z pliku\n";
    std::cout<<"2.Wygeneruj losowa tablice\n";
    std::cout<<"3.Wyswietl otatnio utworzona tablice\n";
    std::cout<<"4.Uruchom wybrany algorytm\n";
    std::cout<<"5.Wyswietl posortowana tablice\n";
    std::cout<<"6.Uruchom symulacje\n";
    std::cout<<"7.Zakoncz program\n";
    std::cout<<"=====================================\n";
    std::cout<<"Wybierz akcje: ";//Zapytanie do użytkownika
    int choice;
    char choiceOftype;
    std::fstream file;
    std::string fileName;
    std::string buffor;
    Simulation sim;
    std::cin>>choice;//Użytkownik wybiera liczbę z zakresu 1-7
    switch (choice)
    {
    case 1:
        std::cout<<"=====================================\n";
        std::cout<<"Podaj nazwe pliku do wczytania: ";//Zapytanie do użytkownika
        std::cin>>fileName;//Użytkownik podaje nazwę pliku
        std::cout<<"Podaj typ danych(i/f):";//Zapytanie do użytkownika
        std::cin>>choiceOftype;//Użytkownik podaje typ danych i-int,f-float
        file.open(fileName,std::ios::in);//Program otwiera plik o nazwie podanej przez użytkownika,flaga std::ios::in oznacza że plik używany będzie do odczytu
        getline(file,buffor);//Program pobiera pierwszą linijkę pliku do buffora
        length= std::stoi(buffor);//Według założeń pierwsza linjka pliku to długość tablicy
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype =='i'){
            tabelInt = new int[length];//Program tworzy tablice dynamiczną typu int o długości pobranej z pliku
            //Program pobiera kolejne linje pliku i zapisuje je w bufforze
            for(int i=0;i<length;i++){
                getline(file,buffor);
                tabelInt[i]= std::stoi(buffor);//Funkcja stoi zmienia zmienną string na int
            }
        }
        if(choiceOftype =='f'){
            tabelFloat = new float[length];//Program tworzy tablice dynamiczną typu float o długości pobranej z pliku
            //Program pobiera kolejne linje pliku i zapisuje je w bufforze
            for(int i=0;i<length;i++){
                getline(file,buffor);
                tabelFloat[i]= std::stof(buffor);//Funkcja stof zmienia zmienną string na float
            }
        }
        file.close();//Plik zostaje zamknięty
        menu();//Rekurencja
        break;
    case 2:
        std::cout<<"=====================================\n";
        std::cout<<"Podaj dlugosc tablicy: ";//Zapytanie do użytkownika
        std::cin>>length;//Użytkownik podaje długość tablicy
        std::cout<<"Podaj typ danych(i/f):";//Zapytanie do użytkownika
        std::cin>>choiceOftype;//Użytkownik podaje typ danych i-int,f-float
        srand(time(NULL));//Program tworzy nowe ziarno losowości
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        tabelInt = new int[length];//Program tworzy tablice dynamiczną typu int o długości podanej przez użytkownika
        tabelFloat = new float[length];//Program tworzy tablice dynamiczną typu float o długości podanej przez użytkownika
        if(choiceOftype =='i'){    
            //Program wypełnia stworzoną tablicę losowymi liczbami typu int jedna po drugiej
            for(int i=0;i<length;i++)
            {
                tabelInt[i]= rand();
            }
        }
        if(choiceOftype =='f'){ 
            //Program wypełnia stworzoną tablicę losowymi liczbami typu float jedna po drugiej
            for(int i=0;i<length;i++)
            {
                tabelFloat[i]= (float)(rand()) / (float)(rand());
            }
        }
        menu();//Rekurencja
        break;
    case 3:
        std::cout<<"=====================================\n";
        std::cout<<"Podaj typ danych(i/f):";//Zapytanie do użytkownika
        std::cin>>choiceOftype;//Użytkownik podaje typ danych i-int,f-float
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype =='i'){
            //Program wypisuje elementy typu int tablicy jeden po drugim
            for(int i=0;i<length;i++)
            {
                std::cout<<tabelInt[i]<<", ";
            }
            std::cout<<"\n";//Koniec tablicy, program wypisuje znak nowa linia
        }
        if(choiceOftype =='f'){
            //Program wypisuje elementy typu float tablicy jeden po drugim
            for(int i=0;i<length;i++)
            {
                std::cout<<tabelFloat[i]<<", ";
            }
            std::cout<<"\n";//Koniec tablicy, program wypisuje znak nowa linia
        }
        menu();//Rekurencja
        break;
    case 4:
        std::cout<<"=====================================\n";
        std::cout<<"Podaj typ danych(i/f):";//Zapytanie do użytkownika
        std::cin>>choiceOftype;//Użytkownik podaje typ danych i-int,f-float
        //Jeśli podany typ jest poprawny to program tworzy nowe tablice dynamicze do posortowania
        if(choiceOftype =='i' || choiceOftype =='f'){
            sortedTabelInt = new int[length];
            sortedTabelFloat = new float[length];
            //Program kopjuje zawrtość tabelInt i tabelFloat tak by orginalne tabele nie zostały nadpisane
            std::copy(tabelInt,tabelInt+length,sortedTabelInt);
            std::copy(tabelFloat,tabelFloat+length,sortedTabelFloat);
            menuAlg(length,choiceOftype);//Wywołanie menu wyboru algorytmów
        }
        else{
            std::cout<<"Niepoprawny znak";//Program zwraca użytkownikowi informacje o błędnym wyborze
        }
        menu();//Rekurencja
        break;
    case 5:
        std::cout<<"=====================================\n";
        std::cout<<"Podaj typ danych(i/f):";//Zapytanie do użytkownika
        std::cin>>choiceOftype;//Użytkownik podaje typ danych i-int,f-float
        //Zależnie od wybranego typu program wykonuje odpowiednie instrukcje
        if(choiceOftype =='i'){
            //Program wypisuje elementy typu int tablicy jeden po drugim
            for(int i=0;i<length;i++)
            {
                std::cout<<sortedTabelInt[i]<<", ";
            }
            std::cout<<"\n";//Koniec tablicy, program wypisuje znak nowa linia
        }
        if(choiceOftype =='f'){
            //Program wypisuje elementy typu float tablicy jeden po drugim
            for(int i=0;i<length;i++)
            {
                std::cout<<sortedTabelFloat[i]<<", ";
            }
            std::cout<<"\n";//Koniec tablicy, program wypisuje znak nowa linia
        }
        menu();//Rekurencja
        break;
    case 6:
        std::cout<<"=====================================\n";
        std::cout<<"Podaj długość tablic: ";
        std::cin>>tableLength;
        std::cout<<"Podaj ilość powtórzeń: ";
        std::cin>>tableCount;
        sim.Start(tableLength,tableCount);//Program startuje symulacje
        menu();//Rekurencja
        break;
    case 7:
        std::cout<<"=====================================\n";
        std::cout<<"Koniec Programu\n";//Program się kończy
        break;    
    default:
        menu();//Rekurencja
        break;
    }
}
int main(){
    menu();//Wyświetla menu
    return 0;
}    