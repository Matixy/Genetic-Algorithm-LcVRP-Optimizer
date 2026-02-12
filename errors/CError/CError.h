//
// Created by mateu on 3.12.2025.
//

#ifndef MATEUSZ_ZADROZNY_LISTA4_CERROR_H
#define MATEUSZ_ZADROZNY_LISTA4_CERROR_H
#pragma once
#include <string>

class CError {
  public:
    // metody
    std::string toString();

    // konstruktor
    CError(std::string sDescription);

    // gettery i settery
    std::string getSDescription() const;

    void setSDescription(const std::string& sDescription);

    std::string getSErrorType() const;

    void setSErrorType(const std::string& sErrorType);

  private:
    std::string sDescription;
    std::string sErrorType;
};


#endif //MATEUSZ_ZADROZNY_LISTA4_CERROR_H