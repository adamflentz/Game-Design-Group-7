#include "HouseHaunters.hpp"
////////////////////////////
// This is the House Haunters game (skeleton). In order to make the code really
// easy to understand it's commented way more than necessary.
// 
// Next check out include/HouseHaunters.hpp
///////////////////////////
int main(int argc, char** argv)
{
    // Create an instance of the House Haunters game engine
    HouseHauntersGame game;
    
    // Maybe potentially read in config files here
    // and then push them to the game

    /*game.width = config.width, etc.../**/
    
    // Let's start the game
    game.start();
    return 0;
}
