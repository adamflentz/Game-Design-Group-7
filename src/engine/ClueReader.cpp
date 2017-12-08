#include "engine/ClueReader.hpp"
#include "engine/Random.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace rapidxml;

// Turns the xml file into rapidxml nodes
void ClueReader::readFile(std::string filename) {

    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());
    doc.parse<0>(&content[0]);
}

// returns the number of children a node of a given xml node
int ClueReader::getNumChild(xml_node<> *parent) {
    int count = 0;
    for(xml_node<> *child = parent->first_node(); child; child = child->next_sibling()) {
        count++;
    }
    return count;
}

// Randomly selects an item inflicting high damage and an item inflicting low damage
// Then populates lists of clues and info based on the chosen items
void ClueReader::selectItems() {
    SelectStream(1); // used for random
    rapidxml::xml_node<> *root = doc.first_node();

    cluesJackpot.clear();
    cluesSpec.clear();
    cluesVague.clear();
    cluesWorthless.clear();

    // select a random high damage item
    int randH = Equilikely(0, getNumChild(root->first_node("high")) - 1);
    std::cout << "Random Number " << randH << std::endl;
    int n = 0;
    xml_node<> *itemH = root->first_node("high")->first_node();
    while(n != randH){
        itemH = itemH->next_sibling();
        n++;
    }

    itemHigh.name = itemH->first_node("name")->value();
    itemHigh.type = itemH->first_node("type")->value();
    std::cout << itemHigh.name << std::endl;
    auto clue_node = itemH->first_node("clues");
    if(clue_node){
        if(clue_node->first_node("jackpot")){
            // std::cout << "Jackpot: " << std::endl;
            // std::cout << itemH->first_node("clues")->first_node("jackpot")->value() << std::endl;
            cluesJackpot.push_back(clue_node->first_node("jackpot")->value());
        }
        if(clue_node->first_node("specific")){
            // std::cout << "Specific: " << std::endl;
            // std::cout << clue_node->first_node("specific")->value() << std::endl;
            cluesSpec.push_back(clue_node->first_node("specific")->value());
        }
        if(clue_node->first_node("vague")){
            // std::cout << "Vague: " << std::endl;
            // std::cout << clue_node->first_node("vague")->value() << std::endl;
            cluesVague.push_back(clue_node->first_node("vague")->value());
        }
        if(clue_node->first_node("worthless")){
            // std::cout << "Worthless: " << std::endl;
            // std::cout << clue_node->first_node("worthless")->value() << std::endl;
            cluesWorthless.push_back(clue_node->first_node("worthless")->value());
        }
    }

    // select a random low damage item
    int randL = Equilikely(0, getNumChild(root->first_node("low") - 1));
    n = 0;
    xml_node<> *itemL = root->first_node("low")->first_node();
    while(n != randL){
        itemL = itemL->next_sibling();
        n++;
    }

    itemLow.name = itemL->first_node("name")->value();
    itemLow.type = itemL->first_node("type")->value();
    cluesJackpot.push_back(itemL->first_node("clues")->first_node("jackpot")->value());
    cluesSpec.push_back(itemL->first_node("clues")->first_node("specific")->value());
    cluesVague.push_back(itemL->first_node("clues")->first_node("vague")->value());
    cluesWorthless.push_back(itemL->first_node("clues")->first_node("worthless")->value());

    // populate info
    xml_node<> *list = root->first_node("info")->first_node(itemHigh.type.c_str());
    for(xml_node<> *node = list->first_node(); node; node = node->next_sibling()) {
        info.push_back(node->value());
    }
    if (itemHigh.type != itemLow.type) {
        list = root->first_node("info")->first_node(itemLow.type.c_str());
        for(xml_node<> *node = list->first_node(); node; node = node->next_sibling()) {
            info.push_back(node->value());
        }
    }
}

std::vector<std::string> ClueReader::getInfo() {
    return info;
}

std::vector<std::string> ClueReader::getCluesJackpot(){
    return cluesJackpot;
}
std::vector<std::string> ClueReader::getCluesSpec() {
    return cluesSpec;
}

std::vector<std::string> ClueReader::getCluesVague() {
    return cluesVague;
}

std::vector<std::string> ClueReader::getCluesWorthless() {
    return cluesWorthless;
}

Item ClueReader::getItemHigh() {
    return itemHigh;
}

Item ClueReader::getItemLow() {
    return itemLow;
}
