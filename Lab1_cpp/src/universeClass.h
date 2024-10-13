#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <string>
#include "characterClass.h"

class Universe {
private:
    vector<Character> characters;

public:
    string classifyCharacter(Character& character);
    void addCharacter(Character& character);
    void displayCharacters();
    vector<Character> getCharacters();
};

#endif
