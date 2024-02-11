#include "file_loader.h"

bool FileLoader::loadFile(const std::string& filePath) {
    std::ifstream fileStream(filePath);

    if (!fileStream) {
        std::cerr << "No se pudo abrir el archivo: " << filePath << std::endl;
        return false;
    }
    content_.assign((std::istreambuf_iterator<char>(fileStream)),
                    std::istreambuf_iterator<char>());

    return true;
}

const std::string& FileLoader::getContent() const {
    return content_;
}