#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

class Character {
public:
    int id;
    bool isHumanoid;
    string planet;
    int age;
    vector<string> traits;

    Character(const json& data) {
        id = data.value("id", -1);
        isHumanoid = data.value("isHumanoid", false);
        planet = data.value("planet", "Unknown");
        age = data.value("age", -1);
        traits = data.contains("traits") ? data["traits"].get<vector<string>>() : vector<string>{};
    }

    void display() const {
        cout << "ID: " << id << endl;
        cout << "Is Humanoid: " << (isHumanoid ? "Yes" : "No") << endl;
        if (!planet.empty()) {
            cout << "Planet: " << planet << endl;
        }
        if (age != -1) {
            cout << "Age: " << age << endl;
        } else {
            cout << "Age: Unknown" << endl;
        }
        if (!traits.empty()) {
            cout << "Traits: ";
            for (const auto& trait : traits) {
                cout << trait << " ";
            }
            cout << endl;
        } else {
            cout << "Traits: None" << endl;
        }
    }
};

class Universe {
private:
    string universe_name;
    vector<Character> characters;

public:
    Universe(string name) : universe_name(name) {}

    void addCharacter(const Character& character) {
        characters.push_back(character);
    }

    void displayCharacters() const {
        cout << "Universe: " << universe_name << endl;
        for (const auto& character : characters) {
            character.display();
            cout << "-------------------" << endl;
        }
    }
};

int main() {
    ifstream inputFile("test-input.json");
    json jsonData;
    inputFile >> jsonData;

    Universe starWars("Star Wars Universe");

    for (const auto& item : jsonData["input"]) {
        Character character(item);
        starWars.addCharacter(character);
    }

    starWars.displayCharacters();

    return 0;
}
