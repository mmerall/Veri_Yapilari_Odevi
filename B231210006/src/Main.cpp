/** 
* @file main.cpp
* @description Bu dosya, genetik algoritma işlemlerini yöneten ana fonksiyonu içerir. Kullanıcıdan gelen girdilere göre 
*              kromozomlar üzerinde çaprazlama, mutasyon, ekrana yazdırma ve otomatik işlemler gibi genetik algoritma 
*              işlemleri gerçekleştirilir. Kromozomlar, popülasyon üzerinde yapılan değişikliklere göre güncellenir.
* @course 1. Öğretim - C grubu
* @assignment 1. Ödev
* @date 9/11/2024
* @author Mısra Meral [E-posta: misra.meral@ogr.sakarya.edu.tr]
*/

#include <iostream>
#include "../include/Kromozom.h"
#include "../include/Gen.h"
using namespace std;

int main() 
{
    int islem;
    Kromozom* ilkKromozom = nullptr; 
    int popBoyutu = 0; 
    
    Kromozom kromozom;
    kromozom.dosyadanOku("dna.txt", ilkKromozom, popBoyutu);

    while (true) 
    {
        cout << "Hangi islemi yapmak istersiniz?" << endl;
        cout << "1-Caprazlama, 2-Mutasyon, 3-Kromozomlari Ekrana Yaz, 4-Otomatik Islemler, 5-Cikis" << endl;
        cin >> islem;

        if (islem == 1) 
        {

            int caprazlamaIlk, caprazlamaIki;
        
            do 
            {
                cout << "Ilk kromozom hangi satirdan alinacak? ";
                cin >> caprazlamaIlk;
                if (caprazlamaIlk < 0 || caprazlamaIlk >= popBoyutu) 
                {
                    cout << "Gecersiz deger.Lutfen gecerli bir satir numarasi giriniz." << endl;
                }
            } while (caprazlamaIlk < 0 || caprazlamaIlk >= popBoyutu);


            do 
            {
                cout << "Ikinci kromozom hangi satirdan alinacak? ";
                cin >> caprazlamaIki;
                if (caprazlamaIki == caprazlamaIlk) 
                {
                    cout << "Farkli bir kromozom numarasi giriniz." << endl;
                }
                if (caprazlamaIki < 0 || caprazlamaIki >= popBoyutu) 
                {
                    cout << "Gecersiz deger.Lutfen gecerli bir satir numarasi giriniz." << endl;
                }
            } while (caprazlamaIki < 0 || caprazlamaIki >= popBoyutu || caprazlamaIki == caprazlamaIlk);

            
            ilkKromozom->caprazlamaYap(ilkKromozom, popBoyutu, caprazlamaIlk, caprazlamaIki);

            cout << endl << "Caprazlama islemi tamamlandi." << endl << endl;
        
    
    
        }

     
        else if (islem == 2)
        {
            int kromozomNumarasi, genSutunNumarasi;

            do 
            {
                cout << "Mutasyon yapilacak kromozom numarasini girin: ";
                cin >> kromozomNumarasi;
                if (kromozomNumarasi < 0 || kromozomNumarasi >= popBoyutu) {
                    cout << "Gecersiz kromozom numarasi" << endl;
                }
            } while (kromozomNumarasi < 0 || kromozomNumarasi >= popBoyutu);
     
            cout << "Mutasyon yapilacak gen sutun numarasini girin: ";
            cin >> genSutunNumarasi;

            ilkKromozom->mutasyonYap(ilkKromozom, popBoyutu, kromozomNumarasi, genSutunNumarasi);

            cout << endl << "Mutasyon islemi tamamlandi." << endl << endl;
        }

        

        else if (islem == 3)
        {
            Kromozom* anlik = ilkKromozom;

            while (anlik != nullptr)
            {
                anlik->ekranaYazdir(); 
                anlik = anlik->sonraki;
            }
            cout << endl << endl << "Ekrana yazma islemi tamamlandi." << endl << endl;
        }

        else if (islem == 4)
        {
            ilkKromozom->otomatikIslemler("islemler.txt", ilkKromozom, popBoyutu);
            cout << endl << "Otomatik islemler tamamlandi." << endl << endl;

        }
       
        else if (islem == 5) 
        {
            break;
        }

        else 
        {
            cout << "Gecersiz secenek! Lutfen gecerli bir secenek girin." << endl;
        }	
    }

    ilkKromozom->temizle(ilkKromozom);
    
    return 0;
}