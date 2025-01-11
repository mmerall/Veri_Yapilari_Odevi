#ifndef KROMOZOM_H
#define KROMOZOM_H
#include "../include/Gen.h"

class Kromozom {
public:
    Gen* bas;
    Kromozom* sonraki;

    Kromozom();

    void temizle(Kromozom*& popBas);

    void genEkle(const string& genDeger);
    void ekranaYazdir() const;
    int uzunluk() const;
    void dosyadanOku(const string& dosyaAdi, Kromozom*& popBas, int& popBoyutu);
    void mutasyonYap(Kromozom*& popBas, int popBoyutu, int kromozomNumarasi, int genSutunNumarasi);
    void caprazlamaYap(Kromozom*& popBas, int& popBoyutu, int ilk, int ikinci);
    void otomatikIslemler(const string& dosyaAdi, Kromozom* ilkKromozom, int& popBoyutu); 
    
   

};

#endif