#include "utilities.h"

///Prototyping
int damage_calc();
int win_lose();
int enemy_turn(std::string);

///Global Variable | Only used for this file
int p_hp{10}, e_hp{10};
int tmp_num{};

void battle(std::string enemy)
{
    ///Pointers
    bcn::DATA_HANDLER str;
    ///Variables
    int battleing{0};
    std::string action{};
    p_hp = 10;
    e_hp = 10;
    tmp_num = 0;

    ///Simply use the string as the enemy name
    ///All battles are the same in this except
    ///for the names.
    system("clear");
    std::cout << "You\'ve encountered a " << enemy << "!\n\n";
    bcn::program_pause();
    bcn::bcn_buffer_flush();
    while(battleing == 0)
    {
        action_choice:
            system("clear");
            ///Fight Menu
            std::cout << "\tWhat would you like to do?\n";
            std::cout << "[Attack]\n";
            std::cout << "[Run]\n";
            std::cout << "Choice: ";
            std::cin >> action;
            bcn::cin_input_check();
            action = str.convert_to_lower(action);
            bcn::bcn_buffer_flush();
            if(action != "attack")
            {
                if(action != "run")
                {
                    std::cout << "\nSorry, your choice was not understood. Please try again.";
                    bcn::program_pause();
                    bcn::bcn_buffer_flush();
                    goto action_choice;
                }
            }///End of action choice

            ///Code below not running????
            ///Hp, Run, and enemy calculations go below here
            if(action == "attack")
            {
                std::cout << "\nYou attacked the " << enemy << "!\n";
                tmp_num = damage_calc();
                std::cout << "You did " << tmp_num << " damage!\n";
                e_hp -= tmp_num;
                std::cout << enemy << " has " << e_hp << " remaining!\n";
                bcn::program_pause();
            }else if(action == "run")
            {
                if((rand() % 5 + 1) > 3)
                {
                    std::cout << "\nYou escaped!\n";
                    return;
                } else {
                    std::cout << "You failed to escape!\n";
                }
            }///End player attack

            if(win_lose() == 1) ///Checks if the player or enemy is dead.
            {
                return;
            }

            tmp_num = enemy_turn(enemy);
            if (tmp_num == 2)
            {
                return;
            }

            if(win_lose() == 1) ///Checks if the player or enemy is dead.
            {
                game_over();
                return;
            }

        }///End of battle

        return;
}///End battle


int damage_calc()
{
    ///Variables
    int damage{}; ///May be used for both player and enemy
    int defend{}; ///May be used for both player and enemy
    int total_damage{}; ///May be used for both player and enemy

    damage = rand() % 10 + 1;
    defend = rand() % 10 + 1;
    total_damage = damage - defend;
    if(total_damage < 0)
    {
        total_damage = 0;
    }
    return total_damage;
}

int win_lose()
{
    if(p_hp <= 0)
    {
        return 1;
    }

    if(e_hp <= 0)
    {
        system("clear");
        std::cout << "You win!\n\n";
        bcn::program_pause();
        return 1;
    }
    return 0;
}

int enemy_turn(std::string enemy)
{
    if ((rand() % 5 + 1) <= 4)
    {
        ///Attack
        std::cout << "The " << enemy << " attacked!\n";
        tmp_num = damage_calc();
        std::cout << enemy << " did, " << tmp_num << " damage!\n";
        p_hp -= tmp_num;
        std::cout <<"You have " << p_hp << " remaining!\n";
        bcn::program_pause();
    } else {
        ///Run
        std::cout << enemy << " attempted to escape!\n";
        if((rand() % 5 + 1) > 3)
        {
            std::cout << "\n" << enemy << " escaped!\n";
            return 2;
        } else {
            std::cout << enemy << " failed to escape!\n";
            bcn::program_pause();
        }
    }///End attack or run

    return 0;
}///End enemy turn.
