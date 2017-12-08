#ifndef CLUEREADER_HPP
#define CLUEREADER_HPP
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <string>
#include <vector>

struct Item {
    std::string name;
    std::string type;
};

class ClueReader {
public:
    void readFile(std::string filename);
    void selectItems();
    std::vector<std::string> getInfo();
    std::vector<std::string> getCluesJackpot();
    std::vector<std::string> getCluesSpec();
    std::vector<std::string> getCluesVague();
    std::vector<std::string> getCluesWorthless();
    Item getItemHigh();
    Item getItemLow();

private:
    int getNumChild(rapidxml::xml_node<> *parent);
    std::string items;
    Item itemHigh;
    Item itemLow;
    std::vector<std::string> info;
    std::vector<std::string> cluesJackpot;
    std::vector<std::string> cluesSpec;
    std::vector<std::string> cluesVague;
    std::vector<std::string> cluesWorthless;
    rapidxml::xml_document<> doc;
};

#endif
