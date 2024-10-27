#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <vector>
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

class Character {
private:
    int id;
    bool isHumanoid;
    bool isHumanoidDataPresent;
    string planet;
    int age;
    vector<string> traits;
    string universe;
    string race;
public:
    Character(const json& data);
    void setUniverse(string classification);
    void display();
    int getId();
    bool getIsHumanoid();
    bool getIsHumanoidDataPresent();
    string getPlanet();
    int getAge();
    vector<string> getTraits();
    string getUniverse();
    string getRace();
};

#endif
