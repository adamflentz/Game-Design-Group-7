#include "engine/ClueReader.hpp"
#include "engine/Random.hpp"
#include <fstream>
#include <iostream>

// Reads the json and stores it in j
void ClueReader::readFile(std::string file) {
    std::ifstream i(file);
    i >> j;
}

// Randomly selects an item inflicting high damage and an item inflicting low damage
void ClueReader::selectItems() {
    SelectStream(1); //used for random

    // select high damage item
    int randomHigh = Equilikely(0, j.at("high").size() - 1);
    itemHigh.name = j.at("high")[randomHigh].at("name");
    itemHigh.type = j.at("high")[randomHigh].at("type");

    std::cout << randomHigh << std::endl;
    std::cout << j.at("high")[randomHigh].at("name") << "" << std::endl;
    std::cout << j.at("high")[randomHigh].at("type") << "" << std::endl;

    // select a low damage item
    int randomLow = Equilikely(0, j.at("low").size() - 1);
    itemLow.name = j.at("low")[randomLow].at("name");
    itemLow.type = j.at("low")[randomLow].at("type");
}
