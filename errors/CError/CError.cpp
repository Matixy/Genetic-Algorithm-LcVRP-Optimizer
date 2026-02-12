//
// Created by mateu on 3.12.2025.
//

#include "../CError/CError.h"

//metody

std::string CError::toString() {
  return "Error: " + getSErrorType() + ": " + getSDescription();
}

// konstrukor

CError::CError(std::string sDescription) {
  setSDescription(sDescription);
}

// settery i gettery

std::string CError::getSDescription() const {
  return sDescription;
}

void CError::setSDescription(const std::string& sDescription) {
  this->sDescription = sDescription;
}

std::string CError::getSErrorType() const {
  return sErrorType;
}

void CError::setSErrorType(const std::string &sErrorType) {
  this->sErrorType = sErrorType;
}
