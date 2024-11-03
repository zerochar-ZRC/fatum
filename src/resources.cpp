#include "../include/fatum/resources.h"
using namespace fatum;


std::string ResourceLoader::crypt(std::string_view text) {
    constexpr static const std::string_view key{ "FATUM" };
    std::string result;
    std::size_t i = 0;
    for (const char c : text) {
        result += c ^ key[i];
        i = (i + 1) % key.size();
    }
    return result;
}

void ResourceLoader::unload(unsigned index) {
    _cached.erase(_cached.begin()+index);
}

std::string ResourceLoader::get(unsigned index) {
    return _cached.at(index);
}

unsigned ResourceLoader::load(std::string_view name) {
    unsigned index = _cached.size();
    _cached[index] = exctract(name);
    return index;
}

std::string ResourceLoader::exctract(std::string_view name) {
    if (!_initialize) return "";
    auto it = std::ranges::find_if(_views,
        [name](const std::string& n)->bool { return n == name; },
        &ResourceLoader::ShortView::name
    );

    ResourceLoader::ShortView view = *it;
    std::string resource(view.size, '\0');
    _file.seekg(view.begin, std::ios_base::beg);
    _file.read(resource.data(), view.size);

    resource = crypt(resource);

    return resource;
}

bool ResourceLoader::initialize(std::filesystem::path zrp_path) {
    if (_initialize) return true;
    if (!fs::exists(zrp_path)) return false;
    if (!zrp_path.extension().compare("zrc")) return false;
    _file_path = std::move(zrp_path);
    _file.open(_file_path, std::ios::binary);
    if (!_file.is_open()) return false;

    char digits_buff = 0;
    _file.read(&digits_buff, 1);

    int digits = digits_buff - '0';
    _file.seekg(-digits, std::ios::end);
    std::string zrc_size_buff(digits, '\0');
    _file.read(zrc_size_buff.data(), digits);

    int zrc_size = std::atoi(zrc_size_buff.data());
    std::string zrc(zrc_size, '\0');
    _file.seekg(1, std::ios::beg);
    _file.read(zrc.data(), zrc_size);
    std::string zrc_buff{};
    zrc_buff.reserve(zrc_size);

    unsigned int index = 0;

    std::string name(150, '\0');
    unsigned begin,end;
    for (const char c : crypt(zrc)) {
        if (c != ',' && c != '}') {
            zrc_buff.push_back(c);
            continue;
        }
        switch (index += 1) {
        case 1:
            name = zrc_buff;
            break;
        case 2:
            begin = 1 + zrc_size + std::stoi(zrc_buff.c_str());
            break;
        case 3:
            index = 0;
            end = 1 + zrc_size + std::stoi(zrc_buff.c_str());
            _views.emplace_back(
                name,
                begin, 
                end 
            );
            break;
        }
        zrc_buff.clear();
    }
    _initialize = true;
    return true;
}
ResourceLoader& ResourceLoader::getInstance(){
    static ResourceLoader instance{};
    return instance;
}