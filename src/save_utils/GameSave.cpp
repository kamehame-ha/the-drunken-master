//
// Created by mrlek on 10.05.2025.
//

#include "GameSave.h"

GameSave::GameSave() = default;

auto GameSave::save(PlayerData& data) -> void {
    auto filename = "../../saves/" + data.name + ".txt";

    std::ofstream file(filename);
    if (!file.is_open()) {
        fmt::print("Failed to open save file: {}\n", filename);
    }

    file << "hp->" << data.hp << "\n"
         << "ad->" << data.ad << "\n"
         << "move_speed->" << data.move_speed << "\n"
         << "name->" << data.name << "\n"
         << "exp_level->" << data.exp_level << "\n"
         << "exp->" << data.exp << "\n"
         << "current_chapter->" << data.current_chapter << "\n"
         << "current_level->" << data.current_level << "\n";

    if (!file.good()) {
        fmt::print("Failed to write to save: {}\n", filename);
    }

    file.close();
    fmt::print("Saved {}\n", filename);
}

auto GameSave::load(const std::string& name) -> PlayerData& {
    auto data = &player_data;

    auto filename = "../../saves/" + name + ".txt";

    std::ifstream file(filename);
    if (!file.is_open()) {
        fmt::print("Failed to open save file: {}\n", filename);
    }

    std::vector<std::string> requiredKeys = {
        "hp", "ad", "move_speed", "name",
        "exp_level", "exp", "current_chapter", "current_level"
    };

    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;
        line = trimmer(line);
        if (line.empty()) continue;

        size_t sep = line.find("->");
        if (sep == std::string::npos) {
            fmt::print("Line {}: Missing '->' separator\n", lineNum);
        }

        std::string key = trimmer(line.substr(0, sep));
        std::string value = trimmer(line.substr(sep + 2));

        // Check if key is valid
        auto it = std::find(requiredKeys.begin(), requiredKeys.end(), key);
        if (it == requiredKeys.end()) {
            fmt::print("Line {}: Unknown key '{}'\n", lineNum, key);
        }

        // Remove found key from requirements
        requiredKeys.erase(it);

        try {
            if (key == "hp") data->hp = std::stoi(value);
            else if (key == "ad") data->ad = std::stoi(value);
            else if (key == "move_speed") data->move_speed = std::stof(value);
            else if (key == "name") data->name = value;
            else if (key == "exp_level") data->exp_level = std::stoi(value);
            else if (key == "exp") data->exp = std::stoi(value);
            else if (key == "current_chapter") data->current_chapter = std::stoi(value);
            else if (key == "current_level") data->current_level = std::stoi(value);
        } catch (const std::exception& e) {
            fmt::print("Line {}: Invalid value for {} - {}\n", lineNum, key, e.what());
        }
    }

    if (!requiredKeys.empty()) {
        fmt::print("Missing required fields: ");
        for (const auto& key : requiredKeys) fmt::print("{} ", key);
        fmt::print("\n");
    }

    fmt::print("Loaded {}\n", filename);
    file.close();
    return *data;
}

auto GameSave::newGame() -> void {
    player_data.name = nameGenerator();
    auto name = player_data.name;
    namespace fs = std::filesystem;
    auto const path = fs::path("../../saves/" + name + ".txt");

    if (fs::exists(path)) {
        fmt::print("Save file with that name already exists: {}\n", name);
    } else {
        std::ofstream file(path);

        if (!file) {
            fmt::print("Failed to create save file: {}\n", name);
        }

        file << "hp->" << 100 << "\n"
         << "ad->" << 10 << "\n"
         << "move_speed->" << 300 << "\n"
         << "name->" << name << "\n"
         << "exp_level->" << 1 << "\n"
         << "exp->" << 0 << "\n"
         << "current_chapter->" << 1 << "\n"
         << "current_level->" << 1 << "\n";

        file.close();

        fmt::print("New save file {} created\n", name);
    }
}

auto GameSave::nameGenerator() -> std::string {
    std::vector<std::string> prefixes = {
        "Shadow", "Dark", "Mighty", "Epic", "Savage",
        "Steel", "Iron", "Thunder", "Frost", "Blaze",
        "Ghost", "Phantom", "Storm", "Night", "Wolf",
        "Dragon", "Viper", "Titan", "Omega", "Alpha",
        "Neon", "Cyber", "Rogue", "Warlord", "Inferno"
    };

    std::vector<std::string> suffixes = {
        "Slayer", "Hunter", "Warrior", "Knight", "Assassin",
        "Mage", "Wizard", "Reaper", "Guardian", "Destroyer",
        "Bandit", "Raider", "Champion", "Legend", "Overlord",
        "Viper", "Fang", "Blade", "Striker", "Crusher",
        "Phoenix", "Titan", "Specter", "Warden", "Berserker"
    };

    int prefix_i = Dice(prefixes.size()).roll();
    int suffix_i = Dice(suffixes.size()).roll();

    return fmt::format("{}{}{}", prefixes[prefix_i], suffixes[suffix_i], Dice(1000).roll());
}


auto GameSave::trimmer(const std::string& s) -> std::string {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;
    auto end = s.end();
    while (end != start && std::isspace(*(end-1))) --end;
    return {start, end};
}