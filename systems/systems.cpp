#include "utilities.h"

///Global Variables
int _ending{};
int _dungeon{};
int _current_dungeon{};
int _gameover{};
float _dtxt{}; ///Which text within the dungeon the player was on
std::string _fname{}; ///Used to define the name for a new save file

inline void game_over()
{
    extern int _gameover;
    _gameover = 1;
    bcn::bcn_buffer_flush();
    std::cout << "\nGame Over!";
    bcn::program_pause();
    ///Here is were I need to get back to main()
}

inline int gameover_check()
{
    extern int _gameover;
    if(_gameover == 1)
    {
        return 1;
    } else {
        return 0;
    }
}


///The below is only a test. Test it VERY CAREFULLY before actually using it in the
///full program
void save_thread()
{
    using namespace std::chrono_literals;
    ///This is a function that should run parallel to the main
    ///program. This function should maintain a copy of the games
    ///state.
    do
    {
        if(_dungeon >= _current_dungeon)
        {
            std::ofstream sav("data01.sav");
            ///Save code goes below
            sav << _dungeon << "\n" << _dtxt;
            ///Save code goes above
            sav.close();
        }
        ///This waits 10 seconds before allowing the loop to restart
        std::this_thread::sleep_for(2s);
    } while (_ending == 0);
    return;
}

void regress_check()///Prevents saving if the player goes back to the main menu
{
    do
    {
        if(_current_dungeon < _dungeon)
        {
            _current_dungeon = _dungeon;
        }
    }while(_ending == 0);
    return;
}
