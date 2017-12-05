#ifndef CONFIGURATIONS_STORE
#define CONFIGURATIONS_STORE

#include <map>
// A global configurations map
class Config
{
public:
    // Maps controller index to player number
    std::map<int, int> player_map; // this is for controllers so the name should change
    // Maps player number to character
    std::map<int, std::string> other_map; // Maps

    int num_players = 1;

    float time_Per_Phase = 5.0;
};

#endif
