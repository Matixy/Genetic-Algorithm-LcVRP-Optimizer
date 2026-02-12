//
// Created by Share on 16.01.2026.
//

#include "CEvaluator.h"
#include "../files/fileLoader/CFileLoader.h"
#include "../utils/CArrayUtils.h"
#include "individual/CIndividual.h"

#include <cmath>
#include <iostream>

const double CEvaluator::INVALID_INDIVIDUAL_FITNESS = 99999.9;

// metody

CResult<void, CError> CEvaluator::bConfigure(std::string sPathName) {
  vClear(); // wyczyszczenie obiektu przed konfiguracja

  pcData = new CDataInstance();
  CResult<void, CError> result = CFileLoader::loadData(sPathName, *pcData);

  // jezeli wczytanie z pliku sie nie powiodlo wyczysc obiekt i przekaz bledy wyzej
  if (!result.bIsSuccess()) {
    vClear();
    return result;
  }

  vCalculateDistanceMatrix(); // oblicz macierz odleglosci
  int iNumTrucks = pcData->getINumGroups();

  // inicjacja ustawienie rozmiaru
  vTruckCurrentPos.resize(iNumTrucks);
  vTruckActualCapacity.resize(iNumTrucks);
  vTruckDist.resize(iNumTrucks);
  vTruckUsed.resize(iNumTrucks);

  return result;
}

double CEvaluator::dEvaluate(const CIndividual* pcIndividual) {
  // zabezpieczenie przy wywolaniu metody gdy instancja nie zostala skonfigurowana
  if (!pcIndividual || pcData == NULL) {
    return INVALID_INDIVIDUAL_FITNESS;
  }

  const std::vector<int>& vGenotype = pcIndividual->getGenotype(); // pobranie genotypu
  const std::vector<int>& vPermutations = pcData->getVPermutation();
  const std::vector<int>& vDemands = pcData->getVDemandSection();

  // zabezpieczenie czy rozmiary genotypow sa zgodne z parametrami z pliku
  if (vGenotype.size() != getGenotypeSize() && vGenotype.size() != this->pcData->getVPermutation().size()) {
    return INVALID_INDIVIDUAL_FITNESS;
  }

  // przygotowanie zmiennych lokalnych
  int iCapacity = pcData->getICapacity();
  int iDepotIndex = 0;

  double dTotalDistance = 0.0;

  // reset buforow wektorow
  vClearBufforMatrix();

  // obliczenie tras dla kazdego tira
  for (int i = 0; i < vGenotype.size(); i++) {
    int iTruck = vGenotype[i]; // pobranie tira
    int iTargetIndex = vPermutations[i] - 1; // pobranie do jakiego punktu ma przejechac
    int iDemand = vDemands[iTargetIndex]; // pobranie wagi paczki

    vTruckUsed[iTruck] = true; // zmiana flagi

    // sprawdzenie pojemnosci
    if (vTruckActualCapacity[iTruck] + iDemand > iCapacity) {
      vTruckDist[iTruck] += vDistMatrix[vTruckCurrentPos[iTruck]][iDepotIndex]; // doliczenie trasy powrotu do depotu
      vTruckCurrentPos[iTruck] = 0; // powrot do depotu
      vTruckActualCapacity[iTruck] = 0; // oproznienie tira
    }

    vTruckDist[iTruck] += vDistMatrix[vTruckCurrentPos[iTruck]][iTargetIndex]; // doliczenie dlugosci trasy do klienta
    vTruckActualCapacity[iTruck] += iDemand; // zaladowanie pojemnosci jaka trzeba zabrac od klienta do tira
    vTruckCurrentPos[iTruck] = iTargetIndex; // aktualizacja pozycji tira
  }

  // powrot do depotu dla ciezarowek
  dTotalDistance += vReturnToDepot();

  return dTotalDistance;
}

double CEvaluator::dCalculateDistance(const Coordinate &c1, const Coordinate &c2) {
  return std::hypot(c1.x - c2.x, c1.y - c2.y);
}

void CEvaluator::vClear() {
  if (pcData != NULL) {
    delete pcData;
    pcData = NULL;
  }
}

void CEvaluator::vCalculateDistanceMatrix() {
  if (pcData == NULL) return;

  int iDim = pcData->getIDimension();
  const std::vector<Coordinate>& vCords = pcData->getVNodeCoordSection();

  vDistMatrix.assign(iDim, std::vector<double>(iDim, 0.0));

  for (int i = 0; i < iDim; i++) {
    for (int j = 0; j < iDim; j++) {
      vDistMatrix[i][j] = dCalculateDistance(vCords[i], vCords[j]);
    }
  }
}

void CEvaluator::vClearBufforMatrix() {
  std::fill(vTruckCurrentPos.begin(), vTruckCurrentPos.end(), 0);
  std::fill(vTruckActualCapacity.begin(), vTruckActualCapacity.end(), 0);
  std::fill(vTruckDist.begin(), vTruckDist.end(), 0.0);
  std::fill(vTruckUsed.begin(), vTruckUsed.end(), false);
}

double CEvaluator::vReturnToDepot() {
  int iNumOfTrucks = pcData->getINumGroups();
  int iDepotIndex = 0;
  double dist = 0;

  for (int i = 0; i < iNumOfTrucks; i++) {
    if (vTruckUsed[i]) {
      // Dodaj drogę z ostatniego klienta do Depotu
      vTruckDist[i] += vDistMatrix[vTruckCurrentPos[i]][iDepotIndex];
      dist += vTruckDist[i];
    }
  }

  return dist;
}

// konstruktory

CEvaluator::CEvaluator() {
  pcData = NULL;
}

// destruktor

CEvaluator::~CEvaluator() {
  vClear();
};

// gettery i settery

int CEvaluator::getGenotypeSize() const {
  if (pcData == NULL) {
    return 0;
  }

  return pcData->getIDimension() - 1;
}

int CEvaluator::getNumberOfTrucks() const {
  if (pcData == NULL) {
    return 0;
  }

  return pcData->getINumGroups();
}

int CEvaluator::dGetDist(int x, int y) const {
  return vDistMatrix.at(x).at(y);
}
