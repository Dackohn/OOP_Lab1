#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "characterClass.cpp"
#include "universeClass.cpp"

using json = nlohmann::json;
using namespace std;

class View {
public:
    static void saveToJson(Universe& universe) {
        // Create a JSON object to hold characters grouped by universe
        json universeJson;
        string classification;
        for (auto& character : universe.getCharacters()) {
            classification = universe.classifyCharacter(character);
            // Set the universe for the character based on classification
            character.setUniverse(classification);

            // Create a JSON object for the current character
            json characterJson;
            characterJson["id"] = character.id;
            characterJson["isHumanoid"] = character.isHumanoid;
            characterJson["planet"] = character.planet;
            characterJson["age"] = character.age;
            characterJson["traits"] = character.traits;
            characterJson["universe"] = character.universe;
            characterJson["classification"] = classification;

            // Append the character JSON object to the respective universe in universeJson
            universeJson[character.universe].push_back(characterJson);
        }

        // Save the grouped characters to a file for each universe
        for (auto it = universeJson.begin(); it != universeJson.end(); ++it) {
            const string universeName = it.key();
            const json& characters = it.value();

            string fileName = "../output/" + universeName + ".json";

            ofstream outputFile(fileName);
            
            if (outputFile.is_open()) {
                outputFile << characters.dump(4);
                outputFile.close();
                cout << "Data for universe '" << universeName << "' written to " << fileName << endl;
            }
        }
    }
};


int main() {
    ifstream inputFile("../res/input.json");
    json jsonData;
    inputFile >> jsonData;
    View view;

    Universe universalClassification;

    for (const auto& item : jsonData["input"]) {
        Character character(item);
        universalClassification.addCharacter(character);
    }

    universalClassification.displayCharacters();

    view.saveToJson(universalClassification);

    return 0;
}
