#include "../systems/utilities.h"

///Global Pointers
bcn::bcn_file_handler gc_txt;
bcn::DATA_HANDLER data;
RNG_ENCOUNTER fight;

///Global Variable calls
extern int _dungeon;
extern float _dtxt;

int glow_cave_entrance() ///Return 0 will move to next dungeon | Return 1 will loop back to main menu
{
    ///Variables
    std::string user_input{};
    _dungeon = 1;

    ///This function handles the entrance of the cave
    _dtxt = 1.0;
    gc_txt.automate_text_read("dungeon/glow_cave/entrance",1);

    ///Player decision
    player_choice:
        std::cout << "[What do you want to do?] \n[Take the Left path | Type: left]\n";
        std::cout << "[Take the Right path | Type: right]\n";
        std::cout << "[Save the game | Type: save]\n";
        std::cout << "Please type your choice: ";
        std::cin >> user_input;
        if(bcn::cin_input_check() == 1)
        {
            bcn::invalid_choice(user_input);
            goto player_choice;
        }
        user_input = data.convert_to_lower(user_input);
        if(user_input == "left")
        {
            ///Code for left path
            if(glow_cave_left() == 0)
            {
                ///Continue to next part
            } else {
                return 1; ///Send you back to main menu
            }

        } else if(user_input == "right") {

            ///Code for right path
            if(glow_cave_right() == 0)
            {
                ///Continue to next part
            } else {
                return 1; ///Send you back to main menu
            }

        } else if(user_input == "save") {

            ///Code for save
            std::cout << "Save\n";

        } else {
            bcn::invalid_choice(user_input);
            goto player_choice;
        }///End player_choice if statement

        ///Next Part Of Code
        if(glow_cave_hidden_entrance() == 1) {return 1;}

    return 1;
}


int glow_cave_left()
{
    fight.trigger_fight();
    if(gameover_check() == 1) ///Call this EVERY time after trigger_fight()
    {
        return 1;
    }///Ends game if player dies

    _dtxt = 2.1;
    gc_txt.automate_text_read("dungeon/glow_cave/left",1);
    return 0;
}


int glow_cave_right()
{
    fight.trigger_fight();
    if(gameover_check() == 1) ///Call this EVERY time after trigger_fight()
    {
        return 1;
    }///Ends game if player dies

    ///Start text here
    _dtxt = 2.2;
    gc_txt.automate_text_read("dungeon/glow_cave/right",1);
    return 0;
}


int glow_cave_hidden_entrance()
{
    ///A battle needs to be forced here
    battle("Bandit");
    if(gameover_check() == 1) ///Call this EVERY time after trigger_fight()
    {
        return 1;
    }///Ends game if player dies

    ///Hidden Room text below here
    _dtxt = 3.0;

    return 0;
}
