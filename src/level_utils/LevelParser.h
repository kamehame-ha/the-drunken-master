//
// Created by mrlek on 08.05.2025.
//

#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <fmt/base.h>


class LevelParser {
public:
    struct ObjectData {
        std::string name;
        float size_x;
        float size_y;
        float position_x;
        float position_y;
    };

    struct LevelInfo {
        int chapter;
        int level;
        std::vector<ObjectData> objects;
    };

    explicit LevelParser(const std::string& filename);

    auto parse() -> LevelInfo;

private:
    LevelInfo info;
    std::string filename;

    auto parse_filename() -> void;
    auto parse_file_content() -> void;
    auto line_parser(const std::string& line, int line_num) -> void;
    auto argument_parser(const std::string& args_str, int line_num, std::vector<float>& args) -> void;

    static auto trimmer(const std::string& line) -> std::string;;
};



#endif //LEVELPARSER_H
