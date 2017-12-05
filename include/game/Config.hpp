#ifndef CONFIGURATIONS_STORE
#define CONFIGURATIONS_STORE

#include <map>
// A global configurations map
class Config
{
public:
    enum CHARACTER { BRO = 0, SIS = 1, DAD = 2, MOM = 3};
    // Maps controller index to player number
    std::map<int, int> player_map;
    // Maps player number to character
    std::map<int, CHARACTER> char_map; // Maps

    int num_players = 1;

    float time_Per_Phase = 5.0;
};

#endif
