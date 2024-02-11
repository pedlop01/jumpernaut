#include <string>
#include <fstream>
#include <iostream>

class FileLoader {
public:
    bool loadFile(const std::string& filePath);
    const std::string& getContent() const;


private:
    std::string content_;
};