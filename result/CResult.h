//
// Created by mateu on 3.12.2025.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CRESULT_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CRESULT_H
#pragma once
#include <vector>

template <typename T, typename E>
class CResult {
  public:
    //metody
    static CResult<T, E> cOk(const T& cValue);
    static CResult<T, E> cFail(E* pcError);
    static CResult<T, E> cFail(std::vector<E*>& vErrors);
    bool bIsSuccess() const;

    //operatory
    CResult<T, E>& operator=(const CResult<T, E>& cOther);

    // konstruktory
    CResult(const T& cValue);

    CResult(E* pcError);

    CResult(std::vector<E*>& vErrors);

    CResult(const CResult<T, E>& cOther);

    // destruktor
    ~CResult();

    // gettery i settery
    T cGetValue() const;

    const std::vector<E*>& vGetErrors() const;

  private:
    // metody
    void vCopy(const CResult<T, E>& cOther);
    void vClear();

    // pola
    T* pcValue;
    std::vector<E*> vErrors;
};

template<typename E>
class CResult<void, E> {
  public:
    // metody
    static CResult<void, E> cOk();
    static CResult<void, E> cFail(E* pcError);
    static CResult<void, E> cFail(std::vector<E*>& vErrors);
    bool bIsSuccess();

    // operatory
    CResult<void, E>& operator=(const CResult<void, E>& cOther);

    // konstrukotry
    CResult();
    CResult(E *pcError);
    CResult(std::vector<E*>& vErrors);
    CResult(const CResult<void, E>& cOther);

    // destruktor
    ~CResult();

    // gettery i settery
    const std::vector<E*>& vGetErrors() const;

  private:
    // metody
    void vCopy(const CResult<void, E>& cOther);
    void vClear();

    // pola
    std::vector<E*> vErrors;
};

template<typename TE>
class CResult<TE*, TE> {
  public:
    // metody
    static CResult<TE*, TE> cOk(TE* pcValue);
    static CResult<TE*, TE> cFail(TE* pcError);
    static CResult<TE*, TE> cFail(std::vector<TE*>& vErrors);
    bool bIsSuccess();

    // operatory
    CResult<TE*, TE>& operator=(const CResult<TE*, TE>& cOther);

    // konstruktor
    CResult(const CResult<TE*, TE>& cOther);
    CResult(TE* pcValue);
    CResult(TE* pcValue,TE* pcError);
    CResult(std::vector<TE*>& vErrors);

    // destruktor
    ~CResult();

    // gettery i settery
    TE* pcGetValue();
    std::vector<TE*>& vGetErrors();

  private:
    // metody
    void vCopy(const CResult<TE*, TE>& cOther);
    void vClear();

    // pola
    TE* pcValue;
    std::vector<TE*> vErrors;
};

#include "CResult.tpp"
#endif //MATEUSZ_ZADROZNY_LISTA4_CRESULT_H