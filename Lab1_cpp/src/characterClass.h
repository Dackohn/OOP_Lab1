#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

class Character {
public:
    int id;
    bool isHumanoid;
    bool isHumanoidDataPresent;
    string planet;
    int age;
    vector<string> traits;
    string universe;
    string race;

    Character(const json& data);
    void setUniverse(string classification);
    void display();
};

#endif
