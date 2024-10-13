#include "characterClass.h"

// Constructor implementation
Character::Character(const json& data) {
    id = data.value("id", -1);
    
    // Check if "isHumanoid" exists
    if (data.contains("isHumanoid")) {
        isHumanoid = data["isHumanoid"].get<bool>();
        isHumanoidDataPresent = true;
    } else {
        isHumanoidDataPresent = false;
    }

    planet = data.value("planet", "Unknown");
    age = data.value("age", -1);
    traits = data.contains("traits") ? data["traits"].get<vector<string>>() : vector<string>{};
    universe = "Unknown";
    race = "Unknown";
}

// Method to set the universe classification
void Character::setUniverse(string classification) {
    auto delimiter_pos = classification.find(": ");
    if (delimiter_pos != string::npos) {
        race = classification.substr(0, delimiter_pos);
        universe = classification.substr(delimiter_pos + 2);
    }
}

// Method to display character information
void Character::display() {
    cout << "ID: " << id << endl;
    cout << "Is Humanoid: ";
    if (isHumanoidDataPresent) {
        cout << (isHumanoid ? "Yes" : "No") << endl;
    } else {
        cout << "Unknown" << endl;
    }
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
