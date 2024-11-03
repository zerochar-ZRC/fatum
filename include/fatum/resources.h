#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>

#include <string_view>
#include <string>

#include <algorithm>
#include <unordered_map>


namespace fatum {
    namespace fs = std::filesystem;
    class ResourceLoader final { // no virtuals for it to be non-final
        struct ShortView {
            std::string name;
            unsigned begin, end, size;
            ShortView(std::string_view name, unsigned begin, unsigned end) :
                name(name), begin(begin), end(end), size(end - begin) {}
        };

        bool _initialize = false;

        std::vector< ShortView > _views;
        std::vector< std::string > _cached;

        fs::path _file_path;
        std::ifstream _file;
  

        std::string crypt(std::string_view);


        //architecture requires it to be singleton :(
        ResourceLoader() = default;
        ~ResourceLoader() { _file.close(); }
    public:

        std::string exctract(std::string_view);
        
        const std::vector< std::string >& getCached() { return _cached; };
        std::string get(unsigned);
        void unload(unsigned);
        unsigned load(std::string_view);


        bool initialize(fs::path);
        static ResourceLoader& getInstance();

        
    };
}