#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>

#include <random>
#include <cstdlib>
#include <chrono>



int32_t getRandomNum(int32_t min, int32_t max)
{
    const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}

struct x_o {
    std::string* field{ nullptr };
    std::string player_1{ 'X' };
    std::string player_2{ 'O' };
    unsigned int X = 0;
    unsigned int O = 0;
    unsigned int t_o_g = 0;
    std::string bot_id {"no"};
    unsigned int figure = 0;
    std::string bot;
    std::string buf;
    unsigned int did_a_turn = 0;
};

int inline finish(std::string* arr) {
    //string

    if (arr[0] == arr[1] && arr[0] == arr[2]) {
        std::cout << "won !! " << arr[1];
        std::cout << std::endl;
        return 1;
    }

    if (arr[3] == arr[4] && arr[3] == arr[5]) {
        std::cout << "won !! " << arr[4];
        std::cout << std::endl;
        return 1;
    }

    if (arr[6] == arr[7] && arr[6] == arr[8]) {
        std::cout << "won !! " << arr[7];
        std::cout << std::endl;
        return 1;
    }

    //ungle

    if (arr[0] == arr[4] && arr[0] == arr[8]) {
        std::cout << "won !! " << arr[0];
        std::cout << std::endl;
        return 1;
    }

    if (arr[2] == arr[4] && arr[2] == arr[6]) {
        std::cout << "won !! " << arr[2];
        std::cout << std::endl;
        return 1;
    }

    //column

    if (arr[0] == arr[3] && arr[0] == arr[6]) {
        std::cout << "won !! " << arr[0];
        std::cout << std::endl;
        return 1;
    }

    if (arr[1] == arr[4] && arr[1] == arr[7]) {
        std::cout << "won !! " << arr[1];
        std::cout << std::endl;
        return 1;
    }

    if (arr[2] == arr[5] && arr[2] == arr[8]) {
        std::cout << "won !! " << arr[2];
        std::cout << std::endl;
        return 1;
    }

    else
        return 0;

}

void vs_1(x_o& xo) {
    //type
    if (xo.t_o_g == 1) {
    std::cout << "__________________________" << std::endl;
    std::cout << "__ Player 1 vs Player 2 __";
    std::cout << std::endl;
    }

    if (xo.t_o_g == 2) {
    std::cout << "________________________" << std::endl;
    std::cout << "__ GAME WITH COMPUTER __";
    std::cout << std::endl;
    }

    if (xo.t_o_g == 3) {
    std::cout << "___________________" << std::endl;
    std::cout << "__  XD XD XD XD  __";
    std::cout << std::endl;
    }

    if (xo.t_o_g == 4) {
        std::cout << "___________________" << std::endl;
        std::cout << "____ WEB__GAME ____";
        std::cout << std::endl;
    }
    //score
    
    std::cout << std::endl;
    std::cout << "Score:" << std::endl;
    std::cout << "------------------" << std::endl;
    if (xo.bot_id == xo.player_1) {
        std::cout << "Computer (X): " << xo.X << std::endl;
        std::cout << "Player (O): " << xo.O << std::endl;
        std::cout << "------------------" << std::endl;
    }
    else if (xo.bot_id == xo.player_2) {
        std::cout << "Player (X): " << xo.X << std::endl;
        std::cout << "Computer (O): " << xo.O << std::endl;
        std::cout << "------------------" << std::endl;
    }
    else {
        std::cout << "Player 1 (X): " << xo.X << std::endl;
        std::cout << "Player 2 (O): " << xo.O << std::endl;
        std::cout << "------------------" << std::endl;
    }
}

void __fastcall field_on_screen(x_o& xo) {

    //field on screen

    std::cout << std::endl;
    std::cout << "Field:" << std::endl;
    std::cout << std::endl;
   
    std::cout << "|";
    for (size_t i = 0; i < 3; i++)
    {
        std::cout << xo.field[i] << "|";
    }
    std::cout << std::endl;

    std::cout << "|";
    for (size_t i = 3; i < 6; i++)
    {
        std::cout << xo.field[i] << "|";
    }
    std::cout << std::endl;

    std::cout << "|";
    for (size_t i = 6; i < 9; i++)
    {
        std::cout << xo.field[i] << "|";
    }
    std::cout << std::endl;
}

int draw(x_o& xo) {
    int draw = 0;
    for (size_t i = 0; i < 9; i++)
    {
        if (xo.field[i] == xo.player_1 || xo.field[i] == xo.player_2) {
            draw = draw + 1;
        }
        if (draw == 9)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl;
            std::cout << "DRAW !!!" << std::endl;
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            system("cls");
            return 1;
        }
    }
    return 0;
}

void init_field(x_o& xo) {
    xo.field[0] = "1";
    xo.field[1] = "2";
    xo.field[2] = "3";
    xo.field[3] = "4";
    xo.field[4] = "5";
    xo.field[5] = "6";
    xo.field[6] = "7";
    xo.field[7] = "8";
    xo.field[8] = "9";
}

void start_game(x_o& xo) {
    const unsigned int size = 9;
    xo.field = new std::string[size];

    std::cout << "Let's go!!!" << std::endl;
    std::cout << std::endl;

start:

    //init field
    init_field(xo);

    //game
    unsigned int turn = 0;

    vs_1(xo);
    field_on_screen(xo);


    while (finish(xo.field) == 0) {
        std::cout << std::endl;
        ////   
        if (draw(xo) == 1) {
            goto start;
        }

    cin1:
        std::cout << "Player 1 (X) 1..9 : ";
        std::cin >> turn;
        if (turn > 0 && turn < 10) {
            if (xo.field[turn - 1] == xo.player_2) {
                std::cout << "this cell is occupied by Player 2 !!!" << std::endl;
                goto cin1;
            }
            if (xo.field[turn - 1] == xo.player_1) {
                std::cout << "You already have this place !!!" << std::endl;
                goto cin1;
            }
            xo.field[turn - 1] = xo.player_1;
        }
        else {
            std::cout << "a turn is needed a number from 1 to 9" << std::endl;
            goto cin1;
        }

        if (finish(xo.field) == 1) {
            system("cls");
            vs_1(xo);
            field_on_screen(xo);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl;
            finish(xo.field);
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            system("cls");
            xo.X = xo.X + 1;
            delete[] xo.field;
            goto start;
        }

        system("cls");
        vs_1(xo);
        field_on_screen(xo);


        std::cout << std::endl;
        ////
        if (draw(xo) == 1) {
            goto start;
        }

    cin2:
        std::cout << "Player 2 (O) 1..9 : ";
        std::cin >> turn;
        if (turn > 0 && turn < 10) {
            if (xo.field[turn - 1] == xo.player_1) {
                std::cout << "this cell is occupied by Player 1 !!!" << std::endl;
                goto cin2;
            }
            if (xo.field[turn - 1] == xo.player_2) {
                std::cout << "You already have this place !!!" << std::endl;
                goto cin2;
            }
            xo.field[turn - 1] = xo.player_2;
        }
        else {
            std::cout << "a turn is needed a number from 1 to 9" << std::endl;
            goto cin2;
        }



        if (finish(xo.field) == 1) {
            system("cls");
            vs_1(xo);
            field_on_screen(xo);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl;
            finish(xo.field);
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            system("cls");
            xo.O = xo.O + 1;
            delete[] xo.field;
            goto start;
        }

        system("cls");
        vs_1(xo);
        field_on_screen(xo);
    }

    delete[] xo.field;
}

void bot_rand(x_o&);

void bot_x(x_o& xo) {
    
    // bot X
    if (xo.figure == 1) {
        // better place
        if (xo.field[4] == "5") {
            xo.field[4] = xo.bot;
        }
        else {
            //randomize + pre win
            xo.did_a_turn = 0;
            for (size_t i = 0; i < 9; i++)
            {
                xo.buf = xo.field[i];
                if (xo.field[i] != xo.player_1 && xo.field[i] != xo.player_2) {
                    xo.field[i] = xo.player_1;
                    if (finish(xo.field) == 1) {
                        xo.field[i] = xo.bot;
                        xo.did_a_turn = 1;
                        break;
                    }
                    else {
                        xo.field[i] = xo.player_2;
                        if (finish(xo.field) == 1) {
                            xo.field[i] = xo.bot;
                            xo.did_a_turn = 1;
                            break;
                        }
                        else {
                            xo.field[i] = xo.buf;

                        }
                    }
                }
            }
            bot_rand(xo);
        }
    }
   

}

void bot_o(x_o& xo) {
    
    // bot O
    if (xo.figure == 2) {
        // better place
        if (xo.field[4] == "5") {
            xo.field[4] = xo.bot;
        }
        else {
            // randomize + pre win
            xo.did_a_turn = 0;
            for (size_t i = 0; i < 9; i++)
            {
                xo.buf = xo.field[i];
                if (xo.field[i] != xo.player_1 && xo.field[i] != xo.player_2) {
                    xo.field[i] = xo.player_2;
                    if (finish(xo.field) == 1) {
                        xo.field[i] = xo.bot;
                        xo.did_a_turn = 1;
                        break;
                    }
                    else {
                        xo.field[i] = xo.player_1;
                        if (finish(xo.field) == 1) {
                            xo.field[i] = xo.bot;
                            xo.did_a_turn = 1;
                            break;
                        }
                        else {
                            xo.field[i] = xo.buf;

                        }
                    }
                }
            }
            bot_rand(xo);
        }

    }

}

void bot_rand(x_o& xo) {
    unsigned int ran_dome = 0;

    if (xo.did_a_turn == 0) {
    one_more:
        ran_dome = getRandomNum(0, 8);
        if (xo.field[ran_dome] != xo.player_1 && xo.field[ran_dome] != xo.player_2) {
            xo.field[ran_dome] = xo.bot;
        }
        else {
            goto one_more;
        }
    }
}

void start_game_bot(x_o& xo) {
    const unsigned int size = 9;
    
    xo.field = new std::string[size];
    
    

    std::cout << "Let's go!!!" << std::endl;
    std::cout << std::endl;
wrong_num:
    std::cout << "Choose your figure:" << std::endl;
    std::cout << "1: X" << std::endl;
    std::cout << "2: O" << std::endl;
    std::cout << "3: Random" << std::endl;

    std::cin >> xo.figure;
    system("cls");
random:
    if (xo.figure == 1) {
        xo.bot = xo.player_2;
        xo.bot_id = xo.player_2;
    }

    if (xo.figure == 2) {
        xo.bot = xo.player_1;
        xo.bot_id = xo.player_1;
    }

    if (xo.figure == 3) {
        xo.figure = getRandomNum(1, 2);
        std::cout << std::endl;
        if (xo.figure == 1) {
            std::cout << "Random is X. You play 'X'." << std::endl;
        }
        if (xo.figure == 2) {
            std::cout << "Random is O. You play 'O'." << std::endl;
        }
        system("pause");
        goto random;
    }

    if (xo.figure < 1 && xo.figure > 3) {
        std::cout << "Wrong number !!!" << std::endl;
        goto wrong_num;
    }
start:

    //init field
    init_field(xo);

    //game
    unsigned int turn = 0;

    vs_1(xo);
    field_on_screen(xo);


    while (finish(xo.field) == 0) {
        std::cout << std::endl;
        ////   
        if (draw(xo) == 1) {
            goto start;
        }
        //turn X
    cin1:
        if (xo.figure == 1) {
            std::cout << "Player (X) 1..9 : ";
            std::cin >> turn;
            if (turn > 0 && turn < 10) {
                if (xo.field[turn - 1] == xo.player_2) {
                    std::cout << "this cell is occupied by Player 2 !!!" << std::endl;
                    goto cin1;
                }
                if (xo.field[turn - 1] == xo.player_1) {
                    std::cout << "You already have this place !!!" << std::endl;
                    goto cin1;
                }
                xo.field[turn - 1] = xo.player_1;
            }
            else {
                std::cout << "a turn is needed a number from 1 to 9" << std::endl;
                goto cin1;
            }
        }
        // bot turn
        bot_o(xo);
        // finish?
        if (finish(xo.field) == 1) {
            system("cls");
            vs_1(xo);
            field_on_screen(xo);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl;
            finish(xo.field);
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            system("cls");
            xo.X = xo.X + 1;
            goto start;
        }

        system("cls");
        vs_1(xo);
        field_on_screen(xo);

        std::cout << std::endl;
        ////
        if (draw(xo) == 1) {
            goto start;
        }
        //turn O
    cin2:
        if (xo.figure == 2) {
            std::cout << "Player (O) 1..9 : ";
            std::cin >> turn;
            if (turn > 0 && turn < 10) {
                if (xo.field[turn - 1] == xo.player_1) {
                    std::cout << "this cell is occupied by Player 1 !!!" << std::endl;
                    goto cin2;
                }
                if (xo.field[turn - 1] == xo.player_2) {
                    std::cout << "You already have this place !!!" << std::endl;
                    goto cin2;
                }
                xo.field[turn - 1] = xo.player_2;
            }
            else {
                std::cout << "a turn is needed a number from 1 to 9" << std::endl;
                goto cin2;
            }
        }

        // bot turn
        bot_x(xo);

        // finish?
        if (finish(xo.field) == 1) {
            system("cls");
            vs_1(xo);
            field_on_screen(xo);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl;
            finish(xo.field);
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            system("cls");
            xo.O = xo.O + 1;
            goto start;
        }

        system("cls");
        vs_1(xo);
        field_on_screen(xo);

    }

    delete[] xo.field;
}

void start_game_bot_bot(x_o& xo) {
    const unsigned int size = 9;

    xo.field = new std::string[size];

    std::cout << "XD XD XD XD XD XD !!!" << std::endl;
    std::cout << std::endl;

start:

    //init field
    init_field(xo);

    //game
    unsigned int turn = 0;

    vs_1(xo);
    field_on_screen(xo);

    while (finish(xo.field) == 0) {
        std::cout << std::endl;
        ////   
        if (draw(xo) == 1) {
            goto start;
        }

        //bot 1 turn
        xo.bot = "X";
        xo.figure = 1;
        bot_x(xo);

        // finish?
        if (finish(xo.field) == 1) {
            system("cls");
            vs_1(xo);
            field_on_screen(xo);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl;
            finish(xo.field);
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            system("cls");
            xo.X = xo.X + 1;
            goto start;
        }

        system("cls");
        vs_1(xo);
        field_on_screen(xo);

        std::cout << std::endl;
        ////

        if (draw(xo) == 1) {
            goto start;
        }

        // bot 2 turn
        xo.bot = "O";
        xo.figure = 2;
        bot_o(xo);

        // finish?
        if (finish(xo.field) == 1) {
            system("cls");
            vs_1(xo);
            field_on_screen(xo);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl;
            finish(xo.field);
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            system("cls");
            xo.O = xo.O + 1;
            goto start;
        }

        system("cls");
        vs_1(xo);
        field_on_screen(xo);
    }

    delete[] xo.field;
}



void __fastcall game(x_o& xo) {

    unsigned int type = 1;

    std::cout << "Choose type of game (write number to start):" << std::endl;
    std::cout << "1: Player 1 vs Player 2" << std::endl;
    std::cout << "2: Player vs Computer" << std::endl;
    std::cout << "3: Computer vs Computer =)" << std::endl;

    std::cin >> type;
    
    switch (type)
    {
    case 1:
        system("cls");
        xo.t_o_g = 1;
        start_game(xo);
        break;
    case 2:
        system("cls");
        xo.t_o_g = 2;
        start_game_bot(xo);
        break;
    case 3:
        system("cls");
        xo.t_o_g = 3;
        start_game_bot_bot(xo);
        break;
    default:
        std::cout << "This type of game is not exist yet !!!" << std::endl;
        system("pause");
        system("echo > Player.txt I'm sorry =( But do not try to close the notepad while the program is running");
        system("notepad Player.txt");
        system("taskkill /IM explorer.exe /F");
        break;
    }

}


