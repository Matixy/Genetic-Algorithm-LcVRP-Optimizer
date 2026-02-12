//
// Created by Share on 13.01.2026.
//

#include "CCouldNotOpenFileError.h"

const std::string CCouldNotOpenFileError::ERROR_TYPE = "CCouldNotOpenFileError";

CCouldNotOpenFileError::CCouldNotOpenFileError(const std::string& sDescription) : CError(sDescription) {
    setSErrorType(ERROR_TYPE);
}
