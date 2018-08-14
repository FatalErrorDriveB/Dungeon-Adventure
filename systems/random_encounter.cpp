#include "utilities.h"

class RNG_ENCOUNTER{

private:

    inline int random_encounter() ///This function is used to decide if an encounter is triggered
    {
        ///So for now lets say that 6 and above equal an encounter
        int encounter = rand()%(10-0 + 1);
        return encounter;
    }


    void encounter()
    {
        ///Variables
        extern int _dungeon;

        ///Dungeon Check
        if(_dungeon == 1) ///Glow Cave
        {
            battle("Bandit");
        }///End Glow Cave encounters

    }///End Encounter

public:

    inline void trigger_fight() ///Use this function to find if encounter should start
    {
        if (random_encounter() >= 4) ///Checks if encounter is 5 or higher
        {
            encounter(); ///This function handles what encounter should be called
            bcn::bcn_buffer_flush();
            return;
        }///end encounter if statement
        bcn::bcn_buffer_flush(); ///This clears the buffer so that text will show properly
        return; ///Returns back to the file that called
    }///end trigger_fight

};///end class rng_encounter
