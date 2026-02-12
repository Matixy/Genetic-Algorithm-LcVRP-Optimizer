//
// Created by Share on 12.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CDATAINSTANCE_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CDATAINSTANCE_H
#pragma once

#include <string>
#include <vector>

// idiom reprezentujacy koordynaty
struct Coordinate {
  // pola
  float x;
  float y;

  // konstruktory
  Coordinate() : x(0), y(0) {}
  Coordinate(float x, float y) : x(x), y(y) {}
};

class CDataInstance {
  public:
  // konstruktor
  CDataInstance(); // konstruktor domyslny

  // settery i gettery

  std::string getSInstanceName() const;
  void setSInstanceName(std::string sInstanceName);

  std::string getSTypeName() const;
  void setSTypeName(std::string sTypeName);

  int getIDimension() const;
  void setIDimension(int iDimension);

  int getICapacity() const;
  void setICapacity(int iCapacity);

  int getINumGroups() const;
  void setINumGroups(int iNumGroups);

  std::vector<int> getVPermutation() const;
  void setVPermutation(std::vector<int>& vPermutation);

  std::vector<Coordinate> getVNodeCoordSection() const;
  void setVNodeCoordSection(std::vector<Coordinate>& vNodeCoordSection);

  std::vector<int> getVDemandSection() const;
  void setVDemandSection(std::vector<int>& vDemandSection);

  Coordinate getCorDepotSection() const;
  void setCorDepotSection(Coordinate& corDepotSection);

private:
  // metody

  // pola statyczne

  // pola
  std::string sInstanceName;
  std::string sTypeName;

  int iDimension;
  int iCapacity;
  int iNumGroups;

  std::vector<int> vPermutation;
  std::vector<Coordinate> vNodeCoordSection;
  std::vector<int> vDemandSection;
  Coordinate corDepotSection;
};


#endif //MIN_PROJEKT_MATEUSZ_ZADROZNY_CDATAINSTANCE_H