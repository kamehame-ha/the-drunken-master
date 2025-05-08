//
// Created by mrlek on 08.05.2025.
//

#include "LevelParser.h"

//
// Podczas pisania tego parsera posłużyłem się tymi stronami:
// https://cplusplus.com/reference/regex/
// https://cplusplus.com/doc/tutorial/files/
// https://www.geeksforgeeks.org/stringstream-c-applications/
//

LevelParser::LevelParser(const std::string &filename): info(), filename(filename) {
    this->info = LevelInfo();
    this->filename = filename;
}


auto LevelParser::parse() -> LevelInfo  {
    parse_filename();
    parse_file_content();
    return info;
}

auto LevelParser::parse_filename() -> void {
    auto pattern = std::regex(R"(level_(\d+)-(\d+)\.txt$)");
    std::smatch matches;

    if (!std::regex_search(filename, matches, pattern)) {
        fmt::print("Wrong filename format for : {}\n", filename);
    }

    info.chapter = std::stoi(matches[1].str());
    info.level = std::stoi(matches[2].str());
}

auto LevelParser::parse_file_content() -> void {
    std::ifstream file("../../levels/" + filename);
    if (!file.is_open()) {
        fmt::print("File could not be opened : {}\n", filename);
    }

    auto line = std::string();
    int line_num = 0;

    while (std::getline(file, line)) {
        line_num++;
        line_parser(line, line_num);
    }
}

auto LevelParser::line_parser(const std::string &line, int line_num) -> void {
    std::string trimmed = trimmer(line);
    if (trimmed.empty()) return;

    const size_t separator = trimmed.find("->");
    if (separator == std::string::npos) {
        fmt::print("Could not find separator\n", line);
    }

    ObjectData obj;
    obj.name = trimmer(trimmed.substr(0, separator));
    std::string args_str = trimmer(trimmed.substr(separator + 2));

    std::vector<float> args;
    argument_parser(args_str, line_num, args);

    if (args.size() != 4) {
        fmt::print("Wrong number of arguments (expected 4): {}\n", args_str);
    }

    obj.size_x = args[0];
    obj.size_y = args[1];
    obj.position_x = args[2];
    obj.position_y = args[3];

    info.objects.push_back(std::move(obj));
}

auto LevelParser::argument_parser(const std::string &args_str, int line_num, std::vector<float> &args) -> void {
    std::stringstream ss(args_str);
    std::string token;

    while (std::getline(ss, token, ',')) {
        token = trimmer(token);

        if (token.empty()) {
            fmt::print("Empty argument");
        }

        try {
            args.push_back(std::stof(token));
        } catch (...) {
            fmt::print("Invalid float value : {}\n", token);
        }
    }
}

auto LevelParser::trimmer(const std::string &s) -> std::string {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) start++;
    auto end = s.end();
    while (end != start && std::isspace(*(end-1))) end--;
    return {start, end};
}