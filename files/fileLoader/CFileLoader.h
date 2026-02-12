//
// Created by Share on 12.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CFILELOADER_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CFILELOADER_H
#pragma once

#include "../../errors/CError/CError.h"
#include "../../result/CResult.h"
#include "../dataInstance/CDataInstance.h"
#include <string>
#include <fstream>

class CFileLoader {
  public:
    static CResult<void, CError> loadData(const std::string& sPathName, CDataInstance& cOutputData);

  private:
    // metody
    static CResult<void, CError> vValidateIDim(CDataInstance& cOutputData);

    static CResult<void, CError> vReadAndSetPermutation(std::ifstream& fFile, CDataInstance& cOutputData);
    static CResult<void, CError> vReadAndSetNodeCoordSection(std::ifstream& fFile, CDataInstance& cOutputData);
    static CResult<void, CError> vReadAndSetDemandSection(std::ifstream& fFile, CDataInstance& cOutputData);
    static CResult<void, CError> vReadAndSetDepotSection(std::ifstream& fFile, CDataInstance& cOutputData);

    // metoda szablonowa- pobiera ze strumiena i ustawia dla danego settera
    // wartosc w instancji CDataInstance T typ arguemntu settera
    template <typename T>
    static void vReadAndSet(std::ifstream& fFile, CDataInstance& cData, void (CDataInstance::*pSetter)(T));

    // pola statyczne
    static const std::string FILE_VALUE_NAME;
    static const std::string FILE_VALUE_TYPE;
    static const std::string FILE_VALUE_DIMENSION;
    static const std::string FILE_VALUE_CAPACITY;
    static const std::string FILE_VALUE_NUM_GROUPS;
    static const std::string FILE_VALUE_PERMUTATION;
    static const std::string FILE_VALUE_NODE_COORD_SECTION;
    static const std::string FILE_VALUE_DEMAND_SECTION;
    static const std::string FILE_VALUE_DEPOT_SECTION;
};

template <typename T>
void CFileLoader::vReadAndSet(std::ifstream& fFile, CDataInstance& cData, void (CDataInstance::*pSetter)(T)) {
  std::string sTrash;
  fFile >> sTrash; // skip ":"

  T value;
  fFile >> value; // pobranie wartosci

  // wywolanie settera przez wskaznik na obiekt CData
  (cData.*pSetter)(value);
}

#endif //MIN_PROJEKT_MATEUSZ_ZADROZNY_CFILELOADER_H