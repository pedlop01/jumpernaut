#include <nlohmann/json.hpp>
#include <string>
#include <memory>

using json = nlohmann::json;

class JsonFileManager {
public:
    JsonFileManager(const std::string& filename);

    void read();
    void write();
    void print();
    void addEntry(const std::string& key, const json& value);
    const json& getData() const;

    std::shared_ptr<nlohmann::json> findPtr(const nlohmann::json &jsonArray, const std::string &key, const std::string &value) const;
    nlohmann::json find(const nlohmann::json &jsonArray, const std::string &key, const std::string &value) const;

private:
    std::string filename_;
    json data_;
};