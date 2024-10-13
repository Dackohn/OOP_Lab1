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
        cout << "Planet: " << (planet.empty() ? "Unknown" : planet) << endl;
        cout << "Age: " << (age == -1 ? "Unknown" : to_string(age)) << endl;
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

    string classifyCharacter(const Character& character) const {
    string classification = "Unknown Species or Universe";
    int maxMatches = 0;

    // Classify by planet first (strongest identifier)
    if (character.planet == "Kashyyyk") {
        return "Wookie: Star Wars";
    } else if (character.planet == "Endor") {
        return "Ewok: Star Wars";
    } else if (character.planet == "Asgard") {
        return "Asgardian: Marvel";
    } else if (character.planet == "Betelgeuse") {
        return "Betelgeusian: Hitchhiker";
    } else if (character.planet == "Vogsphere") {
        return "Vogon: Hitchhiker";
    } else if (character.planet == "Earth") {
        int elfMatches = 0;
        int dwarfMatches = 0;

        for (const string& trait : character.traits) {
            if (trait == "BLONDE" || trait == "POINTY_EARS") {
                elfMatches++;
            }
            if (trait == "SHORT" || trait == "BULKY") {
                dwarfMatches++;
            }
        }

        if (elfMatches > dwarfMatches && (character.age > 200 || character.age == -1)) {
            return "Elf: Lord of the Rings";
        }
        if (dwarfMatches >= elfMatches && character.age <= 200) {
            return "Dwarf: Lord of the Rings";
        }
    }

    // Handle cases where planet is missing (rely on traits + age)
    if (classification == "Unknown Species or Universe") {
        // Check for non-humanoid species first
        if (!character.isHumanoid) {
            int wookieMatches = 0;
            int ewokMatches = 0;
            int vogonMatches = 0;

            for (const string& trait : character.traits) {
                if (trait == "HAIRY" || trait == "TALL") {
                    wookieMatches++;
                }
                if (trait == "SHORT" || trait == "HAIRY") {
                    ewokMatches++;
                }
                if (trait == "GREEN" || trait == "BULKY") {
                    vogonMatches++;
                }
            }

            // Prioritize by highest trait match count
            if (wookieMatches > maxMatches && character.age <= 400) {
                classification = "Wookie: Star Wars";
                maxMatches = wookieMatches;
            }
            if (ewokMatches > maxMatches && character.age <= 60) {
                classification = "Ewok: Star Wars";
                maxMatches = ewokMatches;
            }
            if (vogonMatches > maxMatches && character.age <= 200) {
                classification = "Vogon: Hitchhiker";
                maxMatches = vogonMatches;
            }
        } else { // Handle humanoid species
            int asgardianMatches = 0;
            int betelgeusianMatches = 0;
            int elfMatches = 0;
            int dwarfMatches = 0;

            for (const string& trait : character.traits) {
                if (trait == "BLONDE" || trait == "TALL") {
                    asgardianMatches++;
                }
                if (trait == "EXTRA_ARMS" || trait == "EXTRA_HEAD") {
                    betelgeusianMatches++;
                }
                if (trait == "BLONDE" || trait == "POINTY_EARS") {
                    elfMatches++;
                }
                if (trait == "SHORT" || trait == "BULKY") {
                    dwarfMatches++;
                }
            }

            // Prioritize by highest trait match count
            if (asgardianMatches > maxMatches && character.age <= 5000) {
                classification = "Asgardian: Marvel";
                maxMatches = asgardianMatches;
            }
            if (betelgeusianMatches > maxMatches && character.age <= 100) {
                classification = "Betelgeusian: Hitchhiker";
                maxMatches = betelgeusianMatches;
            }
            if (elfMatches > maxMatches && (character.age > 200 || character.age == -1)) {
                classification = "Elf: Lord of the Rings";
                maxMatches = elfMatches;
            }
            if (dwarfMatches > maxMatches && character.age <= 200) {
                classification = "Dwarf: Lord of the Rings";
                maxMatches = dwarfMatches;
            }
        }
    }

    // Classify by age alone if traits are missing
    if (classification == "Unknown Species or Universe") {
        if (character.age > 5000) {
            return "Elf: Lord of the Rings";
        } else if (character.age > 200 && character.age <= 5000) {
            return "Asgardian: Marvel";
        } else if (character.age <= 60) {
            return "Ewok: Star Wars";
        } else if (character.age <= 100) {
            return "Betelgeusian: Hitchhiker";
        } else if (character.age <= 200) {
            return "Vogon: Hitchhiker";
        }
    }

    return classification;
}




public:
    Universe(string name) : universe_name(name) {}

    void addCharacter(const Character& character) {
        characters.push_back(character);
    }

    void displayCharacters() const {
        cout << "Universe: " << universe_name << endl;
        for (const auto& character : characters) {
            character.display();
            cout << "Classification: " << classifyCharacter(character) << endl;
            cout << "-------------------" << endl;
        }
    }
};

int main() {
    ifstream inputFile("input.json");
    json jsonData;
    inputFile >> jsonData;

    Universe universalClassification("Universal Classification");

    for (const auto& item : jsonData["input"]) {
        Character character(item);
        universalClassification.addCharacter(character);
    }

    universalClassification.displayCharacters();

    return 0;
}
