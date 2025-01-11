/** 
* @file Gen.cpp
* @description Gen sınıfının kurucu gövdesinin dosyası. Her bir genin değerini ve 
               bağlı listedeki bir sonraki gene işaret eden `sonraki` işaretçisini yönetir.
* @course 1. Öğretim - C grubu
* @assignment 1. Ödev
* @date 9/11/2024
* @author Mısra Meral [E-posta: misra.meral@ogr.sakarya.edu.tr]
*/


#include <iostream>
#include "../include/Gen.h"

using namespace std;

Gen::Gen(const string& genDeger) : genDeger(genDeger), sonraki(nullptr) {}