//
// Created by Share on 12.01.2026.
//

#include "CFileLoader.h"

#include <fstream>
#include <string>

#include "../../errors/CArgumentOutOfBoundError.h"
#include "../../errors/CCouldNotOpenFileError.h"
#include "../../errors/CDimensionIsNotSetError.h"
#include "../../errors/CFieldNotFoundInFileError.h"
#include "../../errors/CPermutationIncompleteError.h"

//deklaracja pol statycznych
const std::string CFileLoader::FILE_VALUE_NAME = "NAME";
const std::string CFileLoader::FILE_VALUE_TYPE = "TYPE";
const std::string CFileLoader::FILE_VALUE_DIMENSION = "DIMENSION";
const std::string CFileLoader::FILE_VALUE_CAPACITY = "CAPACITY";
const std::string CFileLoader::FILE_VALUE_NUM_GROUPS = "NUM_GROUPS";
const std::string CFileLoader::FILE_VALUE_PERMUTATION = "PERMUTATION";
const std::string CFileLoader::FILE_VALUE_NODE_COORD_SECTION = "NODE_COORD_SECTION";
const std::string CFileLoader::FILE_VALUE_DEMAND_SECTION = "DEMAND_SECTION";
const std::string CFileLoader::FILE_VALUE_DEPOT_SECTION = "DEPOT_SECTION";

static const std::string SEPARATOR_SIGN = "/";
static const std::string COULD_NOT_OPEN_FILE_ERROR = "Could not open file: ";
static const std::string NAME_NOT_FOUND_ERROR = "Name not found";
static const std::string TYPE_NOT_FOUND_ERROR = "Type not found";
static const std::string DIMENSION_NOT_FOUND_ERROR = "Dimension not found";
static const std::string CAPACITY_NOT_FOUND_ERROR = "Capacity not found";
static const std::string NUM_GROUPS_NOT_FOUND_ERROR = "Number of groups not found";
static const std::string PERMUTATION_NOT_FOUND_ERROR = "Permutation not found";
static const std::string NODE_COORD_SECTION_NOT_FOUND_ERROR = "Node coord section not found";
static const std::string DEMAND_SECTION_NOT_FOUND_ERROR = "demands not found";
static const std::string DEPOT_SECTION_NOT_FOUND_ERROR = "Deport section not found";
static const std::string DIMENSION_NOT_SET_ERROR = "dimension is not set or is invalid";
static const std::string PERMUTATION_INCOMPLETE_ERROR = "Permutation is incomplete";
static const std::string COORDINATE_ERROR = "Error reading coordinates: too litte coords";
static const std::string DEMANDS_ERROR = "Error reading demands too little demands";
static const std::string DEPOT_READ_ERROR = "Error reading Depot";
static const std::string DEPOT_EMPTY_ERROR = "Depot section is empty";
static const std::string NODE_CORD_SECTION_BEFORE_DEPOT_SECTION_ERROR = "node coord section must be loaded before depot section";
static const std::string DEPOT_INVALID_ERROR = "Invalid depot";

CResult<void, CError> CFileLoader::loadData(const std::string& sPathName, CDataInstance& cOutputData) {
  std::string sFullPath = std::string(PROJECT_SOURCE_DIR) + SEPARATOR_SIGN + sPathName; // pelna sciezka

  std::ifstream fFile(sFullPath, std::ios::in);

  // nie znaleziono pliku
  if (!fFile.is_open()) {
    return CResult<void, CError>::cFail(new CCouldNotOpenFileError(COULD_NOT_OPEN_FILE_ERROR + sFullPath));
  }

  // utworzenie flag sprawdzajacych czy dane pola zostaly wczytane
  bool bNameFound = false;
  bool bTypeFound = false;
  bool bDimFound = false;
  bool bCapFound = false;
  bool bNumGroupsFound = false;
  bool bPermutationFound = false;
  bool bCoordsFound = false;
  bool bDemandsFound = false;
  bool bDepotFound = false;

  std::string sWord;
  while (fFile >> sWord) {
    if (sWord == FILE_VALUE_NAME) {
      vReadAndSet(fFile, cOutputData, &CDataInstance::setSInstanceName);
      bNameFound = true;
    }
    if (sWord == FILE_VALUE_TYPE) {
      vReadAndSet(fFile, cOutputData, &CDataInstance::setSTypeName);
      bTypeFound = true;
    }
    if (sWord == FILE_VALUE_DIMENSION) {
      vReadAndSet(fFile, cOutputData, &CDataInstance::setIDimension);
      bDimFound = true;
    }
    if (sWord == FILE_VALUE_CAPACITY) {
      vReadAndSet(fFile, cOutputData, &CDataInstance::setICapacity);
      bCapFound = true;
    }
    if (sWord == FILE_VALUE_NUM_GROUPS) {
      vReadAndSet(fFile, cOutputData, &CDataInstance::setINumGroups);
      bNumGroupsFound = true;
    }
    if (sWord == FILE_VALUE_PERMUTATION) {
      CResult<void, CError> check = vReadAndSetPermutation(fFile, cOutputData);
      if (!check.bIsSuccess()) return check; // przekazanie bledu wyzej
      bPermutationFound = true;
    }
    if (sWord == FILE_VALUE_NODE_COORD_SECTION) {
      CResult<void, CError> check = vReadAndSetNodeCoordSection(fFile, cOutputData);
      if (!check.bIsSuccess()) return check; // przekazanie bledu wyzej
      bCoordsFound = true;
    }
    if (sWord == FILE_VALUE_DEMAND_SECTION) {
      CResult<void, CError> check = vReadAndSetDemandSection(fFile, cOutputData);
      if (!check.bIsSuccess()) return check; // przekazanie bledu wyzej
      bDemandsFound = true;
    }
    if (sWord == FILE_VALUE_DEPOT_SECTION) {
      CResult<void, CError> check = vReadAndSetDepotSection(fFile, cOutputData);
      if (!check.bIsSuccess()) return check; // przekazanie bledu wyzej
      bDepotFound = true;
    }
  }

  fFile.close();

  std::vector<CError*> vErrors;
  if (!bNameFound) vErrors.push_back(new CFieldNotFoundInFileError(NAME_NOT_FOUND_ERROR));
  if (!bTypeFound) vErrors.push_back(new CFieldNotFoundInFileError(TYPE_NOT_FOUND_ERROR));
  if (!bDimFound) vErrors.push_back(new CFieldNotFoundInFileError(DIMENSION_NOT_FOUND_ERROR));
  if (!bCapFound) vErrors.push_back(new CFieldNotFoundInFileError(CAPACITY_NOT_FOUND_ERROR));
  if (!bNumGroupsFound) vErrors.push_back(new CFieldNotFoundInFileError(NUM_GROUPS_NOT_FOUND_ERROR));
  if (!bPermutationFound) vErrors.push_back(new CFieldNotFoundInFileError(PERMUTATION_NOT_FOUND_ERROR));
  if (!bCoordsFound) vErrors.push_back(new CFieldNotFoundInFileError(NODE_COORD_SECTION_NOT_FOUND_ERROR));
  if (!bDemandsFound) vErrors.push_back(new CFieldNotFoundInFileError(DEMAND_SECTION_NOT_FOUND_ERROR));
  if (!bDepotFound) vErrors.push_back(new CFieldNotFoundInFileError(DEPOT_SECTION_NOT_FOUND_ERROR));

  if (!vErrors.empty()) {
    cOutputData = CDataInstance();
    return CResult<void, CError>::cFail(vErrors);
  }

  return CResult<void, CError>::cOk();
}

CResult<void, CError> CFileLoader::vValidateIDim(CDataInstance &cOutputData) {
  // walidacja czy zostal ustawiony poprawny dimension
  int iDim = cOutputData.getIDimension();
  if (iDim <= 0) {
    return CResult<void, CError>::cFail(new CDimensionIsNotSetError(DIMENSION_NOT_SET_ERROR));
  }

  return CResult<void, CError>::cOk();
}

CResult<void, CError> CFileLoader::vReadAndSetPermutation(std::ifstream& fFile, CDataInstance& cOutputData) {
  std::string sWord;
  fFile >> sWord;

  // wstepna walidacja dimension
  CResult<void, CError> check = vValidateIDim(cOutputData);
  if (!check.bIsSuccess()) return check; // wykryto blad

  int iDim = cOutputData.getIDimension();
  // stworzenie tymczasowego wektora
  std::vector<int> vTemp;
  vTemp.reserve(iDim - 1);

  for (int i = 0; i < iDim - 1; i++) {
    int iVal;

    // proba wczytanie liczb- nie udalo sie wczytac wyrzuc blad
    if (!(fFile >> iVal)) {
      return CResult<void, CError>::cFail(new CPermutationIncompleteError(PERMUTATION_INCOMPLETE_ERROR));
    }

    vTemp.push_back(iVal);
  }

  cOutputData.setVPermutation(vTemp); // ustawienie w instancji wektora
  return CResult<void, CError>::cOk();
}

CResult<void, CError> CFileLoader::vReadAndSetNodeCoordSection(std::ifstream& fFile, CDataInstance& cOutputData) {
  // wstepna walidacja dimension
  CResult<void, CError> check = vValidateIDim(cOutputData);
  if (!check.bIsSuccess()) return check; // wykryto blad

  int iDim = cOutputData.getIDimension();
  std::vector<Coordinate> vTemp;
  vTemp.reserve(iDim);

  for (int i = 0; i < iDim; i++) {
    int iId;
    double dX;
    double dY;

    // proba odczytu zmiennych
    if (!(fFile >> iId >> dX >> dY)) {
      return CResult<void, CError>::cFail(new CError(COORDINATE_ERROR));
    }

    vTemp.push_back(Coordinate(dX, dY));
  }

  cOutputData.setVNodeCoordSection(vTemp);
  return CResult<void, CError>::cOk();
}

CResult<void, CError> CFileLoader::vReadAndSetDemandSection(std::ifstream& fFile, CDataInstance& cOutputData) {
  // wstepna walidacja dimension
  CResult<void, CError> check = vValidateIDim(cOutputData);
  if (!check.bIsSuccess()) return check; // wykryto blad

  int iDim = cOutputData.getIDimension();
  std::vector<int> vTemp;
  vTemp.reserve(iDim);

  for (int i = 0; i < iDim; i++) {
    int iId;
    int iDemand;

    if (!(fFile >> iId >> iDemand)) {
      return CResult<void, CError>::cFail(new CArgumentOutOfBoundError(DEMANDS_ERROR));
    }

    vTemp.push_back(iDemand);
  }

  cOutputData.setVDemandSection(vTemp);
  return CResult<void, CError>::cOk();
}

CResult<void, CError> CFileLoader::vReadAndSetDepotSection(std::ifstream& fFile, CDataInstance& cOutputData) {
  int iId;

  // proba odczytu zmiennych
  if (!(fFile >> iId)) {
    return CResult<void, CError>::cFail(new CError(DEPOT_READ_ERROR));
  }

  // sprawdzenie czy magazyn istinieje (jest chociaz jeden index magazynu)
  if (iId == -1) {
    return CResult<void, CError>::cFail(new CError(DEPOT_EMPTY_ERROR));
  }

  const std::vector<Coordinate>& vCoords = cOutputData.getVNodeCoordSection();

  // sprawdzenie czy wczytano wspolrzedne
  if (vCoords.empty()) {
    return CResult<void, CError>::cFail(new CError(NODE_CORD_SECTION_BEFORE_DEPOT_SECTION_ERROR));
  }

  iId--; // dekrementacja id (poprawka na zliacznie od 0)

  // sprawdzenie zakresu
  if (iId < 0 || iId >= vCoords.size()) {
    return CResult<void, CError>::cFail(new CArgumentOutOfBoundError(DEPOT_INVALID_ERROR));
  }

  // ustawienie koordynatow magazynu
  Coordinate vCoord = vCoords[iId];
  cOutputData.setCorDepotSection(vCoord);

  return CResult<void, CError>::cOk();
}
