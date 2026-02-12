//
// Created by Share on 12.01.2026.
//

#include "CDataInstance.h"

// konstruktor
CDataInstance::CDataInstance() {

}

// gettery i settery

std::string CDataInstance::getSInstanceName() const {
  return sInstanceName;
}
void CDataInstance::setSInstanceName(std::string sInstanceName) {
  this->sInstanceName = sInstanceName;
}

std::string CDataInstance::getSTypeName() const {
  return sTypeName;
}
void CDataInstance::setSTypeName(std::string sTypeName) {
  this->sTypeName = sTypeName;
}

int CDataInstance::getIDimension() const {
  return iDimension;
}
void CDataInstance::setIDimension(int iDimension) {
  this->iDimension = iDimension;
}

int CDataInstance::getICapacity() const {
  return iCapacity;
}
void CDataInstance::setICapacity(int iCapacity) {
  this->iCapacity = iCapacity;
}

int CDataInstance::getINumGroups() const {
  return iNumGroups;
}
void CDataInstance::setINumGroups(int iNumGroups) {
  this->iNumGroups = iNumGroups;
}

std::vector<int> CDataInstance::getVPermutation() const {
  return vPermutation;
}
void CDataInstance::setVPermutation(std::vector<int>& vPermutation) {
  this->vPermutation = vPermutation;
}

std::vector<Coordinate> CDataInstance::getVNodeCoordSection() const {
  return vNodeCoordSection;
}
void CDataInstance::setVNodeCoordSection(std::vector<Coordinate>& vNodeCoordSection) {
  this->vNodeCoordSection = vNodeCoordSection;
}

std::vector<int> CDataInstance::getVDemandSection() const {
  return vDemandSection;
}
void CDataInstance::setVDemandSection(std::vector<int>& vDemandSection) {
  this->vDemandSection = vDemandSection;
}

Coordinate CDataInstance::getCorDepotSection() const {
  return corDepotSection;
}
void CDataInstance::setCorDepotSection(Coordinate& corDepotSection) {
  this->corDepotSection = corDepotSection;
}
