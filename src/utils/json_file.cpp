#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include "json_file.h"
#include "log.h"

using json = nlohmann::json;


JsonFileManager::JsonFileManager(const std::string& filename) : filename_(filename) {
    // Implementación del constructor
}

    
const json& JsonFileManager::getData() const {
    return data_;
}

void JsonFileManager::read() {
    std::ifstream ifs(filename_);
    if (!ifs.is_open()) {
        fprintf(stderr,"Could not open file for reading: %s\n", filename_);
        return;
    }

    json j;
    ifs >> j;
    data_ = j;
    ifs.close();
}

void JsonFileManager::write() {
    std::ofstream ofs(filename_);
    if (!ofs.is_open()) {
        fprintf(stderr,"Could not open file for writing: %s\n", filename_);
        return;
    }

    ofs << data_.dump(4); // 4 is the indentation level for pretty printing
    ofs.close();
}

void JsonFileManager::print() {
    std::cout << data_.dump(4) << std::endl;
}

void JsonFileManager::addEntry(const std::string& key, const json& value) {
    data_[key] = value;
}

std::shared_ptr<nlohmann::json> JsonFileManager::findPtr(const nlohmann::json &jsonArray, const std::string &key, const std::string &value) const {
    if (jsonArray.is_array()) {
        for (const auto& item : jsonArray) {
            if (item.is_object() && item.contains(key) && item[key] == value) {
                return std::make_shared<nlohmann::json>(item);  // Retorna un puntero inteligente al objeto encontrado
            }
        }
    }
     std::cout << "retornó null: " << std::endl;
    return nullptr;
}

nlohmann::json JsonFileManager::find(const nlohmann::json &jsonArray, const std::string &key, const std::string &value) const {
    if (jsonArray.is_array()) {
        for (const auto& item : jsonArray) {
            if (item.is_object() && item.contains(key) && item[key] == value) {
                return item;  
            }
        }
    }
    return {};  
}



// int main() {
//     // JsonFileManager manager("example.json");

//     // // Ejemplo de uso
//     // manager.read();
//     // manager.addEntry("newKey", "newValue");
//     // manager.write();
//     // manager.print();

//     return 0;
// }