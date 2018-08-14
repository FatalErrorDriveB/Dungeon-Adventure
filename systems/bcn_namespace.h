#ifndef BCN_H
#define BCN_H
/*
This file contains all the useful code that I wish to reuse over the course of multiple programs.
All functions are under the namespace BCN, which stands for Brandon's Custom Namespace,
*/

///Inclusions
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <sstream>
#include <cstdlib>
#include <ctime>

namespace bcn
{

	inline int cin_input_check()
	{
		if(std::cin.fail())
		{
		    ///Checks for valid cin input and clear the buffer if invalid
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "\nInvalid input, please try again.\n\n";
			return 1; ///Invalid input
		} else {
			return 0; ///No input problems
		}///If statement end
	}///End cin_input_check


    inline void program_pause()
    {
        ///This function pauses the program until the user presses the enter key
        std::cout << "\nPress \'Enter\' to continue...";
        std::cin.clear();
        std::cin.get();
        std::cout << std::endl;
        return;
    }///End program pause


    inline void invalid_choice(std::string user_input)
    {
        ///Tells the user that their choice wasn't one of the options provided
        ///Remember to pass in the cin variable or this function won't run
        std::cout << "\n" << user_input << ", is not a valid option, please try again.\n\n";
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        bcn::program_pause();
        std::system("clear");
    }


    inline void bcn_random()
    {
        ///Generates a random seed for the rng
        ///Use only once at start of program
        srand(time(NULL));
    }///End bcn_random


    inline void bcn_buffer_flush() ///Used to clear the cout/cin buffer
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::system("clear");
    }


    class DATA_HANDLER
    {
        private:
            inline void create(std::string file_name) ///Creates a new file to hold data.
                {
                    std::ofstream outfile (file_name + ".sav");
                    ///All data should be gathered from it's own function and
                    ///called here.
                    outfile.close();
                }///End file creation

        public:

                inline std::string convert_to_lower(std::string str) ///Converts a string to lowercase
                {
                    std::locale temp{};
                    std::string temp2{};
                    for(std::string::size_type i = 0; i < str.length(); i++)
                    {
                        temp2 += std::tolower(str[i], temp);
                    }
                return temp2;
                }


        inline bool fexists(const std::string& file_name) ///Checks if file exist
                {
                    /// 1 = file exist
                    /// 0 = does not exist
                    std::ifstream ifile(file_name.c_str());
                    return (bool)ifile;
                }


        void new_file()
            {
                /*
                This function is used to make a new save file and check if
                the file already exist. If the file exist it ask if the user wishes to
                overwrite.

                If the user doesn't enter a name it should default to "save" however this does not work.
                It will not crash or cause issue, it will just keep waiting for input.
                */
                ///Variables
                std::string file_name{};
                int valid_input{};
                int exist{};
                std::string overwrite{};

                name:
                std::cout << "\nEnter a name for your saved data: ";
                std::cin >> file_name;
                valid_input = bcn::cin_input_check();
                if (valid_input == 1)
                {
                    goto name;
                }

                exist = fexists(file_name + ".sav");
                if(exist == 1)
                {
                    int temp{};
                    overwrite_old_file:
                    std::cout << "\nA file with this name already exist, do you want to overwrite it?\n";
                    std::cout << "Please enter \'yes\', \'no\', or \'x\' to cancel the save operation: ";
                    std::cin >> overwrite;
                    temp = bcn::cin_input_check();
                    if(temp == 1)
                    {
                        goto overwrite_old_file;
                    }

                    overwrite = convert_to_lower(overwrite); ///HERE IF FILE HAS PROBLEM
                    if(overwrite == "yes")
                    {
                        create(file_name);
                        std::cout << "\n\nSave successful!\n";
                    }
                    else if (overwrite == "no")
                    {
                        goto name;
                    } else if (overwrite == "x")
                    {
                        std::cout << "\n\nNo data was saved!\n";
                    } else {
                        std::cout << "\nYour response was not understood, please try again...\n";
                        bcn::program_pause();
                        goto overwrite_old_file;
                    }///end overwrite
                } else {
                create(file_name);
                std::cout << "\n\nSave successful!\n";
                }///End if exist

            }///End new save file

        };///End Data_Handler class



        class bcn_file_handler
        {
            private:

                std::string file_reader(std::istream& is)
                {
                    ///This function is used to read from files line
                    ///by line
                    ///NOTE:If you forget the _ character at the end of your files
                    ///     this will NOT run.

                    std::stringstream ss;
                    std::string line;
                    do
                    {
                        std::getline(is,line);
                        ss << line + "\n";
                    } while (line != "_");

                    return ss.str();
                }


                void file_read(std::string path)
                {
                    ///This function reads data from the file
                    ///specified in the path and prints it
                    ///out to the screen

                    ///NOTE: This function relies on file_reader()

                    ///Pointers
                    bcn::DATA_HANDLER fdata;

                    ///Variables
                    std::string foput{""};
                    int good_file{};

                    ///Start
                    std::ifstream txt (path);
                    good_file = fdata.fexists(path);
                    if (good_file == 1)
                    {
                        foput = file_reader(txt);
                        std::cout << foput << "\n";
                    } else {
                        std::cout << "Error " << path << " not found.\n";
                        std::cout << "Please report this error.\n";
                        txt.close();
                        exit(EXIT_FAILURE);
                    }
                    txt.close();
                }///End file_read

            public:

                inline void automate_text_read(std::string fname, int clear_text)
                {
                    ///Call this function with (file path,clear)
                    ///Clear = 1 clears the terminal
                    ///clear = 0 does not clear the terminal
                    bcn::bcn_file_handler bcn_file;
                    bcn_file.file_read(fname);
                    bcn::program_pause();
                    if(clear_text == 1)
                    {
                        std::system("clear");
                    }
                    return;
                }///End automate_text_read

        };///End bcn_file_handler

}///End of BCN namespace

#endif // BCN_H
