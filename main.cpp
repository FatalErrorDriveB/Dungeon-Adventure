#include "systems/utilities.h"

///Remember, all prototyping and inclusions are handled within the utilities.h

///You'll forget this so here's a reminder.
///When you work with other .cpp files DO NOT include them in the
///project tree. Add them with #include "file.cpp" in utilities.h
///The reason is that Code Blocks compiles the main, it will
///than try and compile other .cpp files, but they were already
///compiled with main, so it throws a redecleration error.

///Text files MUST be distributed with the exe file or it will not work.

int main()
{
    ///Global Variable initialization
    extern int _ending;
    ///Threading
    std::thread t1(save_thread);
    std::thread t2(regress_check);

    ///Random seed initialize
    bcn::bcn_random(); ///This simply set's up the random number generator seed | Do not call a second time

    ///NOTE: DO NOT forget to include _ at the end of ALL text files!
    restart:
        extern int _gameover;
        _gameover = 0;
        int menu_choice{};

        ///Start
        menu_choice = main_menu();
        if(menu_choice == 0)
        {
            new_game();
        } else if(menu_choice == 1) {
            if(_dungeon == 1)
            {
                std::cout << "Game Loaded\n";
                bcn::program_pause();
                goto glow_cave;
            } ///Else if statements go here for the load function
        } else {
            goto end_program;
        }///End main menu

        ///Perhaps use labels to allow jumping to where the player last saved

        glow_cave: ///Labels are used for load jumping
            if(glow_cave_entrance() == 1){bcn::bcn_buffer_flush(); goto restart;} ///All function calls in main() past here should look like this


        ///Below here begins the closing of the program
        ///Only code needed to close the program should be below here
        ///This is where the program ends and the threads are joined
        end_program:
            _ending = 1;
            std::cout << "\nClosing program...\n";
            t1.join(); ///Take around 2 seconds to reconcile
            t2.join();
            return 0;
}

int main_menu()
{
    bcn::DATA_HANDLER txt;
    std::string p_input{};
    do
    {
        std::cout << "\tDungeon Adventure\n";
        std::cout << "New Game [New]\n";
        std::cout << "Load a Save File [Load]\n";
        std::cout << "Exit the game [Quit]\n";
        std::cout << "Please type your choice: ";
        std::cin >> p_input;
        bcn::cin_input_check();
        p_input = txt.convert_to_lower(p_input);
        bcn::bcn_buffer_flush();

        if(p_input == "new")
        {
            return 0;
        } else if(p_input == "load") {
            ///Make a function to take the data from data.sav and load
            ///it into the correct variables. The rest is handled after
            ///the return

            return 1;
        } else if(p_input != "quit"){
            std::cout << "\nChoice not understood, please try again.\n";
            bcn::program_pause();
            system("clear");
        }

    }while(p_input != "quit");
    return 2;
}



void new_game()
{
    extern int _gameover;
    _gameover = 0;
    ///Pointers
    bcn::bcn_file_handler txt; ///Pointer for text file path

    ///NOTE: DO NOT forget to include _ at the end of ALL text files!

    txt.automate_text_read("game_text/main_story_intro/01.bin",1);
    txt.automate_text_read("game_text/main_story_intro/02.bin",1);
    txt.automate_text_read("game_text/main_story_intro/03.bin",1);
    txt.automate_text_read("game_text/main_story_intro/04.bin",1);
}
