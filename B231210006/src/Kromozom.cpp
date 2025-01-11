/** 
* @file Kromozom.cpp
* @description Kromozom sınıfının metotlarının tanımlandığı dosyadır. Bağlı liste yapısı ile genleri temsil eden 
               bir yapı kurar, çaprazlama ve mutasyon işlemlerini gerçekleştirir ve verileri dosya giriş-çıkışı 
               üzerinden yönetir.
* @course 1. Öğretim - C grubu
* @assignment 1. Ödev
* @date 9/11/2024
* @author Mısra Meral [E-posta: misra.meral@ogr.sakarya.edu.tr]
*/

#include <iostream>
#include "../include/Kromozom.h"
#include "../include/Gen.h"
#include <fstream>
#include <sstream>
#include <cmath> 
#include <string>
using namespace std;

Kromozom::Kromozom() : bas(nullptr), sonraki(nullptr) {}

void Kromozom::dosyadanOku(const string& dosyaAdi, Kromozom*& popBas, int& popBoyutu)
{
    ifstream dosya(dosyaAdi);
    if (!dosya.is_open()) 
    {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    string satir;
    while (getline(dosya, satir)) 
    {
        Kromozom* yeniKromozom = new Kromozom();
        istringstream iss(satir);
        string genDeger;

        while (iss >> genDeger) 
        {
            yeniKromozom->genEkle(genDeger);
        }

        if (!popBas) 
        {
            popBas = yeniKromozom;
        } 
        else 
        {
            Kromozom* gecici = popBas;
            while (gecici->sonraki) 
            {
                gecici = gecici->sonraki;
            }
            gecici->sonraki = yeniKromozom;
        }
        ++popBoyutu;
    }

    dosya.close();
}

int Kromozom::uzunluk() const 
{
    int uzunluk = 0;
    Gen* gecici = bas;
    while (gecici) 
    {
        ++uzunluk;
        gecici = gecici->sonraki;
    }
    return uzunluk;
}


void Kromozom::genEkle(const string& genDeger) 
{
    Gen* yeniGen = new Gen(genDeger);
    if (!bas) 
    {
        bas = yeniGen;
    } 
    else 
    {
        Gen* gecici = bas;
        while (gecici->sonraki) 
        {
            gecici = gecici->sonraki;
        }
        gecici->sonraki = yeniGen;
    }
}



void Kromozom::ekranaYazdir() const 
{
    
    if (!bas) return;
    string enSoldakiGen = bas->genDeger;

    
    Gen* gecici = bas->sonraki;
    string sonuc = enSoldakiGen;

    while (gecici) 
    {
        if (gecici->genDeger < enSoldakiGen) 
        {
            sonuc = gecici->genDeger;
        }
        gecici = gecici->sonraki;
    }

    cout << sonuc << " ";
}



void Kromozom::caprazlamaYap(Kromozom*& popBas, int& popBoyutu, int ilk, int ikinci) 
{
    Kromozom* kromozom1 = popBas;
    Kromozom* kromozom2 = popBas;

   
    for (int i = 0; i < ilk; ++i) kromozom1 = kromozom1->sonraki;
    for (int i = 0; i < ikinci; ++i) kromozom2 = kromozom2->sonraki;

    
    int uzunluk1 = kromozom1->uzunluk();
    int uzunluk2 = kromozom2->uzunluk();

   
    int orta1Sol = floor(uzunluk1 / 2.0); 
    int orta1Sag = (floor(uzunluk1 / 2.0) == ceil(uzunluk1 / 2.0)) ? orta1Sol : orta1Sol + 1;

    int orta2Sol = floor(uzunluk2 / 2.0); 
    int orta2Sag = (floor(uzunluk2 / 2.0) == ceil(uzunluk2 / 2.0)) ? orta2Sol : orta2Sol + 1;

   
    Kromozom* yeniKromozom1 = new Kromozom();
    Kromozom* yeniKromozom2 = new Kromozom();

    
    Gen* gecici = kromozom1->bas;
    for (int i = 0; i < orta1Sol; ++i) 
    {
        yeniKromozom1->genEkle(gecici->genDeger);
        gecici = gecici->sonraki;
    }

    gecici = kromozom2->bas;
    for (int i = 0; i < orta2Sag; ++i) 
    { 
        gecici = gecici->sonraki;
    }
    while (gecici) 
    {
        yeniKromozom1->genEkle(gecici->genDeger);
        gecici = gecici->sonraki;
    }

    gecici = kromozom1->bas;
    for (int i = 0; i < orta1Sag; ++i)
    { 
        gecici = gecici->sonraki;
    }
    while (gecici) 
    {
        yeniKromozom2->genEkle(gecici->genDeger);
        gecici = gecici->sonraki;
    }

    gecici = kromozom2->bas;
    for (int i = 0; i < orta2Sol; ++i) 
    { 
        yeniKromozom2->genEkle(gecici->genDeger);
        gecici = gecici->sonraki;
    }

    Kromozom* son = popBas;
    while (son->sonraki) 
    {
        son = son->sonraki;
    }
    son->sonraki = yeniKromozom1;
    yeniKromozom1->sonraki = yeniKromozom2;


    popBoyutu += 2;
}

void Kromozom::otomatikIslemler(const string & dosyaAdi, Kromozom * ilkKromozom, int& popBoyutu)
{
    ifstream dosya(dosyaAdi); 
    if (!dosya.is_open()) 
    {
        cout << "Islemler dosyasi acilamadi!" << endl;
        return;
    }

    string satir;
    while (getline(dosya, satir)) 
    {
        stringstream ss(satir);
        char islemTuru;
        int param1, param2;

        ss >> islemTuru >> param1 >> param2;

        if (islemTuru == 'C') 
        {
            if (param1 >= 0 && param1 < popBoyutu && param2 >= 0 && param2 < popBoyutu && param1 != param2) 
            {
                ilkKromozom->caprazlamaYap(ilkKromozom, popBoyutu, param1, param2);
            }
            else 
            {
                cout << "Caprazlama icin gecersiz parametreler: " << param1 << ", " << param2 << endl;
            }
        } 
        else if (islemTuru == 'M') 
        {
            if (param1 >= 0 && param1 < popBoyutu) 
            {
                ilkKromozom->mutasyonYap(ilkKromozom, popBoyutu, param1, param2);
            }
            else 
            {
                cout << "Mutasyon icin gecersiz parametreler: " << param1 << ", " << param2 << endl;
            }
        } 
        else 
        {
            cout << "Gecersiz islem turu: " << islemTuru << endl;
        }
    }

    dosya.close();

}

void Kromozom::mutasyonYap(Kromozom*& popBas, int popBoyutu, int kromozomNumarasi, int genSutunNumarasi) 
{
    
    if (kromozomNumarasi < 0 || kromozomNumarasi >= popBoyutu) 
    {
        cout << "Gecersiz kromozom numarasi!" << endl;
        return;
    }


    Kromozom* hedefKromozom = popBas;
    for (int i = 0; i < kromozomNumarasi; ++i) 
    {
        hedefKromozom = hedefKromozom->sonraki;
    }


    Gen* gecici = hedefKromozom->bas;
    for (int i = 0; i < genSutunNumarasi; ++i) 
    {
        if (gecici == nullptr) {
            cout << "Gecersiz gen sütun numarasi!" << endl;
            return;
        }
        gecici = gecici->sonraki;
    }

    if (gecici) 
    {
        gecici->genDeger = 'X';
    } 
    else 
    {
        cout << "Gen bulunamadi!" << endl;
    }
}



void Kromozom::temizle(Kromozom *& popBas)
{
    Kromozom* geciciKromozom;
    
    while (popBas != nullptr) {
        Gen* geciciGen = popBas->bas;
        while (geciciGen != nullptr) {
            Gen* silinecekGen = geciciGen;
            geciciGen = geciciGen->sonraki; 
            delete silinecekGen; 
        }
        
        geciciKromozom = popBas;
        popBas = popBas->sonraki; 
        delete geciciKromozom; 
    }

    popBas = nullptr;
}
