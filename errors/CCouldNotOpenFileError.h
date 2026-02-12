//
// Created by Share on 13.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CCOULDNOTOPENFILEERROR_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CCOULDNOTOPENFILEERROR_H
#include <string>

#include "CError/CError.h"


class CCouldNotOpenFileError: public CError {
    public:
        CCouldNotOpenFileError(const std::string& sDescription);

    private:
        const static std::string ERROR_TYPE;
};

#endif //MIN_PROJEKT_MATEUSZ_ZADROZNY_CCOULDNOTOPENFILE_H