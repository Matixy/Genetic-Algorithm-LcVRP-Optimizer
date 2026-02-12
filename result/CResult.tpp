//
// Created by mateu on 3.12.2025.
//

#include <stdlib.h>

#include "CResult.h"

// CRESULT<T,E>
//metody

template<typename T, typename E>
CResult<T, E> CResult<T, E>::cOk(const T &cValue) {
  return CResult<T, E>(cValue);
}

template<typename T, typename E>
CResult<T, E> CResult<T, E>::cFail(E *pcError) {
  return CResult<T, E>(pcError);
}

template<typename T, typename E>
CResult<T, E> CResult<T, E>::cFail(std::vector<E *> &vErrors) {
  return CResult<T, E>(vErrors);
}

template<typename T, typename E>
bool CResult<T, E>::bIsSuccess() const {
  return pcValue != NULL;
}

template<typename T, typename E>
void CResult<T, E>::vCopy(const CResult<T, E> &cOther) {
  if (cOther.pcValue != NULL) {
    pcValue = new T(*cOther.pcValue);
  } else {
    pcValue = NULL;
  }

  if (!cOther.vErrors.empty()) {
    for (int i = 0; i < cOther.vErrors.size(); i++) {
      vErrors.push_back(new E(*cOther.vErrors.at(i)));
    }
  }
}

template<typename T, typename E>
void CResult<T, E>::vClear() {
  if (pcValue != NULL) {
    delete pcValue;
    pcValue = NULL;
  }

  for (int i = 0; i < vErrors.size(); i++) {
    delete vErrors.at(i);
  }
  vErrors.clear();
}

// operatory

template<typename T, typename E>
CResult<T, E> & CResult<T, E>::operator=(const CResult<T, E> &cOther) {
  // zabezpieczenie przed przypisaniem samego siebie
  if (this == &cOther) {
    return *this;
  }

  vClear();
  vCopy(cOther);
  return *this;
}


// konstuktory

template<typename T, typename E>
CResult<T, E>::CResult(const T& cValue) {
  pcValue = new T(cValue);
}

template<typename T, typename E>
CResult<T, E>::CResult(E* pcError) {
  pcValue = NULL;
  vErrors.push_back(pcError);
}

template<typename T, typename E>
CResult<T, E>::CResult(std::vector<E *>& vErrors) {
  pcValue = NULL;

  // przekopiowanie bledow do obiektu
  for (int i = 0; i < vErrors.size(); i++) {
    this->vErrors.push_back(vErrors[i]);
  }
}

template<typename T, typename E>
CResult<T, E>::CResult(const CResult<T, E>& cOther) {
  vCopy(cOther);
}

// destruktor

template<typename T, typename E>
CResult<T, E>::~CResult() {
  vClear();
}

// gettery i settery

template<typename T, typename E>
T CResult<T, E>::cGetValue() const {
  if (pcValue == NULL) { // zwrocenie get value na bledzie
    return T(); // obiekt domyslny typu T
  }

  return *pcValue;
}

template<typename T, typename E>
const std::vector<E *> & CResult<T, E>::vGetErrors() const {
  return vErrors;
}

// CRESULT<void,E>

//metody

template<typename E>
CResult<void, E> CResult<void, E>::cOk() {
  return CResult<void, E>();
}

template<typename E>
CResult<void, E> CResult<void, E>::cFail(E *pcError) {
  return CResult<void, E>(pcError);
}

template<typename E>
CResult<void, E> CResult<void, E>::cFail(std::vector<E*> &vErrors) {
  return CResult<void, E>(vErrors);
}

template<typename E>
bool CResult<void, E>::bIsSuccess() {
  return vErrors.empty();
}

template<typename E>
void CResult<void, E>::vCopy(const CResult<void, E> &cOther) {
  for (int i = 0; i < cOther.vErrors.size(); i++) {
    vErrors.push_back(new E(*cOther.vErrors.at(i)));
  }
}

template<typename E>
void CResult<void, E>::vClear() {
  // przekopiowanie bledow do obiektu
  for (int i = 0; i < vErrors.size(); i++) {
    delete vErrors.at(i);
  }
  vErrors.clear();
}

// operatory
template<typename E>
CResult<void, E> & CResult<void, E>::operator=(const CResult<void, E> &cOther) {
  if (this == &cOther) {
    return *this;
  }

  vClear();
  vCopy(cOther);
  return *this;
}

// konstruktory

// dla sukcesu (pusty konstruktor-> brak bledow, wektor vErrors pusty)
template<typename E>
CResult<void, E>::CResult() {
}

template<typename E>
CResult<void, E>::CResult(E *pcError) {
  if (pcError != NULL) {
    this->vErrors.push_back(pcError);
  }
}

template<typename E>
CResult<void, E>::CResult(std::vector<E *> &vErrors) {
  for (int i = 0; i < vErrors.size(); i++) {
    this->vErrors.push_back(new E(*vErrors[i]));
  }
}

template<typename E>
CResult<void, E>::CResult(const CResult<void, E> &cOther) {
  vCopy(cOther);
}

// destruktor

template<typename E>
CResult<void, E>::~CResult() {
  vClear();
}

// gettery i settery

template<typename E>
const std::vector<E *> & CResult<void, E>::vGetErrors() const {
  return vErrors;
}

// metody
template<typename TE>
CResult<TE *, TE> CResult<TE*, TE>::cOk(TE *pcValue) {
  return CResult<TE *, TE>(pcValue);
}

template<typename TE>
CResult<TE *, TE> CResult<TE*, TE>::cFail(TE *pcError) {
  return CResult<TE *, TE>(NULL,pcError);
}

template<typename TE>
CResult<TE *, TE> CResult<TE*, TE>::cFail(std::vector<TE *> &vErrors) {
  return CResult<TE *, TE>(vErrors);
}

template<typename TE>
bool CResult<TE*, TE>::bIsSuccess() {
  return pcValue != NULL;
}

template<typename TE>
void CResult<TE*, TE>::vCopy(const CResult<TE *, TE> &cOther) {
  if (cOther.pcValue != NULL) {
    pcValue = new TE(*cOther.pcValue);
  } else {
    pcValue = NULL;
  }

  if (!cOther.vErrors.empty()) {
    for (int i = 0; i < cOther.vErrors.size(); i++) {
      vErrors.push_back(new TE(*cOther.vErrors.at(i)));
    }
  }
}

template<typename TE>
void CResult<TE*, TE>::vClear() {
  if (pcValue != NULL) {
    delete pcValue;
    pcValue = NULL;
  }

  for (int i = 0; i < vErrors.size(); i++) {
    delete vErrors.at(i);
  }
  vErrors.clear();
}

// operatory

template<typename TE>
CResult<TE *, TE> & CResult<TE*, TE>::operator=(const CResult<TE *, TE> &cOther) {
  if (this == &cOther) {
    return *this;
  }

  vClear();
  vCopy(cOther);
  return *this;
}

// konstuktory
template<typename TE>
CResult<TE*, TE>::CResult(const CResult<TE *, TE> &cOther) {
  vCopy(cOther);
}

template<typename TE>
CResult<TE*, TE>::CResult(TE *pcValue) {
  if (pcValue != NULL) {
    this->pcValue = new TE(*pcValue);
  } else {
    this->pcValue = NULL;
  }
}

template<typename TE>
CResult<TE*, TE>::CResult(TE* pcValue,TE* pcError) {
  if (pcValue != NULL) {
    this->pcValue = new TE(*pcValue);
  } else {
    this->pcValue = 0;
  }

  vErrors.push_back(new TE(*pcError));
}

template<typename TE>
CResult<TE*, TE>::CResult(std::vector<TE *> &vErrors) {
  for (int i = 0; i < vErrors.size(); i++) {
    this->vErrors.push_back(new TE(*vErrors.at(i)));
  }
}

// destruktor
template<typename TE>
CResult<TE*, TE>::~CResult() {
  vClear();
}

// settery i gettery
template<typename TE>
TE * CResult<TE*, TE>::pcGetValue() {
  if (pcValue == NULL) {
    return TE();
  }

  return pcValue;
}

template<typename TE>
std::vector<TE *> & CResult<TE*, TE>::vGetErrors() {
  return vErrors;
}