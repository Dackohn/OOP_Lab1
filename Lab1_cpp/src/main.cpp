#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/nlohmann/json.hpp"
#include "characterClass.cpp"
#include "universeClass.cpp"

using json = nlohmann::json;
using namespace std;

class View {
public:
    static void startClassification(Universe& universe){
        json universeJson;
        string classification;
        for (auto& character : universe.getCharacters()) {
            classification = universe.classifyCharacter(character);
            // Set the universe for the character based on classification
            character.setUniverse(classification);

            // Create a JSON object for the current character
            json characterJson;
            characterJson["id"] = character.getId();
            characterJson["isHumanoid"] = character.getIsHumanoid();
            characterJson["planet"] = character.getPlanet();
            characterJson["age"] = character.getAge();
            characterJson["traits"] = character.getTraits();
            characterJson["universe"] = character.getUniverse();
            characterJson["classification"] = classification;

            // Append the character JSON object to the respective universe in universeJson
            universeJson[character.getUniverse()].push_back(characterJson);
            for (auto it = universeJson.begin(); it != universeJson.end(); ++it) {
                const string universeName = it.key();
                const json& characters = it.value();

                string fileName = "../output/" + universeName + ".json";
                saveToJson(fileName, characters.dump(4));
            }
        }
    }
    static void saveToJson(string fileName, auto data) {
            ofstream outputFile(fileName);
            
            if (outputFile.is_open()) {
                outputFile << data;
                outputFile.close();
                cout << "Data " << " written to " << fileName << endl;
            }
        }
    };


int main() {
    ifstream inputFile("../res/input.json");
    json jsonData;
    inputFile >> jsonData;

    Universe universalClassification;

    for (const auto& item : jsonData["input"]) {
        Character character(item);
        universalClassification.addCharacter(character);
    }
    // universalClassification.displayCharacters();
    
    View view;
    view.startClassification(universalClassification);

    return 0;
}
