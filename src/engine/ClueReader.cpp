// #include "engine/ClueReader.hpp"
// #include "engine/Random.hpp"
// #include <fstream>
// #include <iostream>
//
// // Reads the json and stores it in j
// void ClueReader::readFile(std::string file) {
//     std::ifstream i(file);
//     i >> j;
// }
//
// // Populates vector of info based on the items
// void ClueReader::populateInfo() {
//     // info for itemHigh
//     int sz = j.at("info").at(itemHigh.type).size();
//     for (int i = 0; i < sz; i++) {
//         info.push_back(j.at("info").at(itemHigh.type)[i]);
//     }
//     // info for itemLow if it's a seperate item type
//     if (itemLow.type != itemHigh.type){
//         sz = j.at("info").at(itemLow.type).size();
//         for (int i = 0; i < sz; i++) {
//             info.push_back(j.at("info").at(itemLow.type)[i]);
//         }
//     }
// }
//
// // adds clues to clues vectors
// void ClueReader::populateClues(std::string y, int z) {
//     cluesSpec.push_back(j.at(y)[z].at("clues").at("specific"));
//     cluesVague.push_back(j.at(y)[z].at("clues").at("vague"));
// }
//
// // Randomly selects an item inflicting high damage and an item inflicting low damage
// void ClueReader::selectItems() {
//     SelectStream(1); //used for random
//
//     // select high damage item
//     int randH = Equilikely(0, j.at("high").size() - 1);
//     itemHigh.name = j.at("high")[randH].at("name");
//     itemHigh.type = j.at("high")[randH].at("type");
//     populateClues("high", randH);
//
//     // select a low damage item
//     int randL = Equilikely(0, j.at("low").size() - 1);
//     itemLow.name = j.at("low")[randL].at("name");
//     itemLow.type = j.at("low")[randL].at("type");
//     populateClues("low", randL);
//
//     populateInfo();
// }
