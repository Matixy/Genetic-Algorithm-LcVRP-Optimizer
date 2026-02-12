cmake_minimum_required(VERSION 3.6)
project(min_projekt_mateusz_zadrozny)

set(CMAKE_CXX_STANDARD 26)

# dodanie sciezki aby moc zapisywac/odczytywać pliki w folderach projektu
add_compile_definitions(PROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(min_projekt_mateusz_zadrozny main.cpp
        files/fileLoader/CFileLoader.cpp
        files/fileLoader/CFileLoader.h
        files/dataInstance/CDataInstance.cpp
        files/dataInstance/CDataInstance.h
        result/CResult.h
        consoleInterface/CConsoleInterface.cpp
        consoleInterface/CConsoleInterface.h
        errors/CError/CError.cpp
        result/CResult.tpp
        errors/CCouldNotOpenFileError.cpp
        errors/CCouldNotOpenFileError.h
        errors/CInvalidVariableFormatError.cpp
        errors/CInvalidVariableFormatError.h
        errors/CDimensionIsNotSetError.cpp
        errors/CDimensionIsNotSetError.h
        errors/CPermutationIncompleteError.cpp
        errors/CPermutationIncompleteError.h
        errors/CArgumentOutOfBoundError.cpp
        errors/CArgumentOutOfBoundError.h
        errors/CFieldNotFoundInFileError.cpp
        errors/CFieldNotFoundInFileError.h
        optimizer/CEvaluator.cpp
        optimizer/CEvaluator.h
        optimizer/individual/CIndividual.cpp
        optimizer/individual/CIndividual.h
        optimizer/individual/mutationStrategy/IMutationStrategy.h
        optimizer/individual/crossStrategy/ICrossStrategy.h
        optimizer/individual/mutationStrategy/CMutationSwap.cpp
        optimizer/individual/mutationStrategy/CMutationSwap.h
        utils/CRandomGeneratorUtil.cpp
        utils/CRandomGeneratorUtil.h
        optimizer/individual/crossStrategy/COnePointCross.cpp
        optimizer/individual/crossStrategy/COnePointCross.h
        optimizer/CGeneticAlgorithm.cpp
        optimizer/CGeneticAlgorithm.h
        utils/CArrayUtils.h
        utils/CArrayUtils.tpp
)
