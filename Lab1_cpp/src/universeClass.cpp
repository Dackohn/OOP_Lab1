#include "universeClass.h"

/*-------------------------------------
 Function for classifying by universe
 -------------------------------------*/
string Universe::classifyCharacter(Character& character) {
    string classification = "Unknown Species or Universe";
        int maxMatches = 0;

        // Classify by planet first (strongest identifier)
        if (character.getPlanet() == "Kashyyyk") {
            return "Wookie: star-wars";
        } else if (character.getPlanet() == "Endor") {
            return "Ewok: star-wars";
        } else if (character.getPlanet() == "Asgard") {
            return "Asgardian: Marvel";
        } else if (character.getPlanet() == "Betelgeuse") {
            return "Betelgeusian: hitch-hicker";
        } else if (character.getPlanet() == "Vogsphere") {
            return "Vogon: hitch-hicker";
        } else if (character.getPlanet() == "Earth") {
            int elfMatches = 0;
            int dwarfMatches = 0;

            for (const string& trait : character.getTraits()) {
                if (trait == "BLONDE" || trait == "POINTY_EARS") {
                    elfMatches++;
                }
                if (trait == "SHORT" || trait == "BULKY") {
                    dwarfMatches++;
                }
            }

            if (elfMatches > dwarfMatches && (character.getAge() > 200)) {
                return "Elf: rings";
            }
            if (dwarfMatches >= elfMatches && character.getAge() <= 200) {
                return "Dwarf: rings";
            }
        }

        // Handle cases where planet is missing (rely on traits + age)
        if (classification == "Unknown Species or Universe") {
            if(character.getIsHumanoidDataPresent() == true){
                // Check for non-humanoid species first
                if (!character.getIsHumanoid()) {
                    int wookieMatches = 0;
                    int ewokMatches = 0;
                    int vogonMatches = 0;

                    for (const string& trait : character.getTraits()) {
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
                    if (wookieMatches > maxMatches && character.getAge() <= 400) {
                        classification = "Wookie: star-wars";
                        maxMatches = wookieMatches;
                    }
                    if (ewokMatches > maxMatches && character.getAge() <= 60) {
                        classification = "Ewok: star-wars";
                        maxMatches = ewokMatches;
                    }
                    if (vogonMatches > maxMatches && character.getAge() <= 200) {
                        classification = "Vogon: hitch-hicker";
                        maxMatches = vogonMatches;
                    }
                } else { // Handle humanoid species
                    int asgardianMatches = 0;
                    int betelgeusianMatches = 0;
                    int elfMatches = 0;
                    int dwarfMatches = 0;

                    for (const string& trait : character.getTraits()) {
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
                    if (asgardianMatches > maxMatches && character.getAge() <= 5000) {
                        classification = "Asgardian: Marvel";
                        maxMatches = asgardianMatches;
                    }
                    if (betelgeusianMatches > maxMatches && character.getAge() <= 100) {
                        classification = "Betelgeusian: hitch-hicker";
                        maxMatches = betelgeusianMatches;
                    }
                    if (elfMatches > maxMatches && (character.getAge() > 200 )) {
                        classification = "Elf: rings";
                        maxMatches = elfMatches;
                    }
                    if (dwarfMatches > maxMatches && character.getAge() <= 200) {
                        classification = "Dwarf: rings";
                        maxMatches = dwarfMatches;
                    }
                }
            }
        }

        if (classification == "Unknown Species or Universe") {
            int wookieMatches = 0;
            int ewokMatches = 0;
            int vogonMatches = 0;
            int asgardianMatches = 0;
            int betelgeusianMatches = 0;
            int elfMatches = 0;
            int dwarfMatches = 0;

            for (const string& trait : character.getTraits()) {
                if (trait == "HAIRY" || trait == "TALL") {
                    wookieMatches++;
                }
                if (trait == "SHORT" || trait == "HAIRY") {
                    ewokMatches++;
                }
                if (trait == "GREEN" || trait == "BULKY") {
                    vogonMatches++;
                }
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
            if (wookieMatches > maxMatches && character.getAge() <= 400) {
                classification = "Wookie: star-wars";
                maxMatches = wookieMatches;
            }
            if (ewokMatches > maxMatches && character.getAge() <= 60) {
                classification = "Ewok: star-wars";
                maxMatches = ewokMatches;
            }
            if (vogonMatches > maxMatches && character.getAge() <= 200) {
                classification = "Vogon: hitch-hicker";
                maxMatches = vogonMatches;
            }
            if (asgardianMatches > maxMatches && character.getAge() <= 5000) {
                classification = "Asgardian: Marvel";
                maxMatches = asgardianMatches;
            }
            if (betelgeusianMatches > maxMatches && character.getAge() <= 100) {
                classification = "Betelgeusian: hitch-hicker";
                maxMatches = betelgeusianMatches;
            }
            if (elfMatches > maxMatches && (character.getAge() > 5000)) {
                classification = "Elf: rings";
                maxMatches = elfMatches;
            }
            if (dwarfMatches > maxMatches && character.getAge() <= 200) {
                classification = "Dwarf: rings";
                maxMatches = dwarfMatches;
            }
        }

        // Classify by age alone if traits are missing
        if (classification == "Unknown Species or Universe") {
            if (character.getAge() > 5000) {
                return "Elf: rings";
            } else if (character.getAge() > 200 && character.getAge() <= 5000) {
                return "Asgardian: Marvel";
            } else if (character.getAge() <= 60) {
                return "Ewok: star-wars";
            } else if (character.getAge() <= 100) {
                return "Betelgeusian: hitch-hicker";
            } else if (character.getAge() <= 200) {
                return "Vogon: hitch-hicker";
            }
        }

        return classification;
}

// Add character to the universe
void Universe::addCharacter(Character& character) {
    characters.push_back(character);
}

// Display all characters and their classifications
void Universe::displayCharacters() {
    for (auto& character : characters) {
        character.display();
        cout << "Classification: " << classifyCharacter(character) << endl;
        cout << "-------------------" << endl;
    }
}


// Get all characters from the universe
vector<Character> Universe::getCharacters() {
    return characters;
}