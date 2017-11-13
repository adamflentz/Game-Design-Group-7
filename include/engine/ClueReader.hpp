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
    Item itemHigh;
    Item itemLow;
    std::vector<std::string> info;
    std::vector<std::string> cluesSpec;
    std::vector<std::string> cluesVague;

private:
    int getNumChild(rapidxml::xml_node<> *parent);
    std::string items;
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *root; // xml root node
};

#endif
