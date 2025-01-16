#include <ctime>
#include <iostream>
#include <windows.h>
#include <cstring>
#include <conio.h>

using namespace std;

const int Size = 10;
char arr_player_map[Size][Size];
char arr_computer_map[Size][Size];

char arr_chek_double_shot[Size][Size];

void Game();

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Map(char arr[Size][Size])
{
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            arr[i][j] = '~';
        }
    }
}
/*int num_ships = 4;
    //1 палуба
    for (int i = 0; i < 4; i++) {
        int x, y;
        do {
            x = rand() % Size;
            y = rand() % Size;
        } while (arr[x][y] == 'S');

        arr[x][y] = 'S';
    }
    //2 палуба
    for (int i = 0; i < num_ships; i++)
    {
        int x, y;
        int dir;
        bool place = false;

        while(!place)
        {
            x = rand() % Size;
            y = rand() % Size;
            dir = rand() % 2;

            if(dir == 0)
            {
                if(y + 1 < Size && arr[x][y] != 'S' && arr[x][y + 1] != 'S')
                {
                    arr[x][y] = 'S';
                    arr[x][y + 1] = 'S';
                    place = true;
                }
            }
            if(dir == 1)
            {
                if(x + 1 < Size && arr[x][y] != 'S' && arr[x + 1][y] != 'S')
                {
                    arr[x][y] = 'S';
                    arr[x + 1][y] = 'S';
                    place = true;
                }
            }
        }
    }*/
void Ships(char arr[Size][Size])
{
    int arr_ships_size[] = { 4,3,3,2,2,2,1,1,1,1 };
    int num_ship = sizeof(arr_ships_size) / sizeof(arr_ships_size[0]);
    int x, y, dir;

    for (int i = 0; i < num_ship; i++)
    {
        bool place = false;

        while (!place)
        {
            bool can_pls = true;

            x = rand() % Size;
            y = rand() % Size;
            dir = rand() % 2;

            for (int j = 0; j < arr_ships_size[i]; j++)
            {
                int dir_X = x + (dir == 1 ? j : 0);
                int dir_Y = y + (dir == 0 ? j : 0);

                if (dir_X >= Size || dir_Y >= Size || arr[dir_X][dir_Y] == 'S')
                {
                    can_pls = false;
                    break;
                }
            }

            for (int j = 0; j <= arr_ships_size[i]; j++)
            {
                for (int k = -1; k <= 1; k++)
                {
                    for (int a = -1; a <= 1; a++)
                    {
                        int check_X = x + (dir == 1 ? j : 0) + a;
                        int check_Y = y + (dir == 0 ? j : 0) + k;

                        if (check_X >= 0 && check_X < Size && check_Y >= 0 && check_Y < Size)
                        {
                            if (arr[check_X][check_Y] == 'S')
                            {
                                can_pls = false;
                                break;
                            }
                        }
                    }
                }
            }

            if (can_pls)
            {
                for (int j = 0; j < arr_ships_size[i]; j++)
                {
                    int dir_X = x + (dir == 1 ? j : 0);
                    int dir_Y = y + (dir == 0 ? j : 0);
                    arr[dir_X][dir_Y] = 'S';
                }
                place = true;
            }
        }
    }
}

void Print(char arr[Size][Size], int cursorX, int cursorY, bool isComputer = false)
{
    cout << "\t\t\t\t\t\t\033[44m   A B C D E F G H I J  " << endl;
    cout << "\t\t\t\t\t\t +---------------------+\033[0m" << endl;
    for (int i = 0; i < Size; i++)
    {
        cout << "\t\t\t\t\t\t\033[44m" << i << "|\033[0m ";
        for (int j = 0; j < Size; j++)
        {
            if (i == cursorY && j == cursorX)
            {
                cout << "\033[92m^ \033[0m";
            }
            else if (isComputer && arr[i][j] == 'S')
            {
                cout << "~ ";
            }
            else if (arr[i][j] == 'S')
            {
                cout << "\033[41mS";

                if (!(j + 1 < Size && arr[i][j + 1] == 'S'))
                {
                    cout << "\033[0m ";
                }
                else
                {
                    cout << " ";
                }
            }
            else if (arr[i][j] == 'X') {
                cout << "\033[41mX\033[0m ";
            }
            else if (arr[i][j] == 'O') {
                cout << "\033[47mO\033[0m ";
            }
            else {
                cout << arr[i][j] << " ";
            }
        }
        cout << "\033[44m|\033[0m" << endl;
    }
    cout << "\t\t\t\t\t\t\033[44m +---------------------+\033[0m" << endl;
}

//void Map(char arr_player_map[10][10]) 
//{
//    cout << "\033[47;34m   A B C D E F G H I J  " << endl;
//    cout << " +---------------------+\033[0m" << endl;
//    for(int i = 0; i < 10; i++)
//    {
//        cout << "\033[47;34m" << i << "|\033[0m ";
//        for(int j = 0; j < 10; j++)
//        {
//            cout << "\033[44m";
//            cout << arr_player_map[i][j] << " ";
//            if (j == 10 - 1)
//            {
//                cout << "\033[47;34m|\033[0m";
//            }
//        }
//        cout << endl;
//    }
//    cout << "\033[47;34m +---------------------+\033[0m" << endl;
//}

void BotBattle(int menu_complexity)
{
    if (menu_complexity == 0)
    {
        int X_shoot = 0;
        int Y_shoot = 0;

        bool shoot_chek_comp = false;
        do {

            X_shoot = rand() % 10;
            Y_shoot = rand() % 10;


            if (arr_player_map[Y_shoot][X_shoot] == 'S')
            {
                arr_player_map[Y_shoot][X_shoot] = 'X';
                shoot_chek_comp = false;
            }
            else if (arr_player_map[Y_shoot][X_shoot] == 'X')
            {
                arr_player_map[Y_shoot][X_shoot] = 'X';
                shoot_chek_comp = true;
            }
            else
            {
                arr_player_map[Y_shoot][X_shoot] = 'O';
                shoot_chek_comp = true;
            }
        } while (!shoot_chek_comp);
    }
    else if (menu_complexity == 1)
    {

        int X_shoot = 0;
        int Y_shoot = 0;

        bool shoot_chek_comp = false;
        bool hit = false;

        int dir_bot;
        do {
            if (!hit)
            {
                X_shoot = rand() % 10;
                Y_shoot = rand() % 10;
            }
            else
            {
                dir_bot = rand() % 2;
                Y_shoot += (dir_bot == 1 ? 1 : 0);
                X_shoot += (dir_bot == 0 ? 1 : 0);
                if (X_shoot >= Size || Y_shoot >= Size)
                {
                    hit = false;
                    continue;
                }
            }
            if (arr_chek_double_shot[Y_shoot][X_shoot] != '+')
            {
                if (arr_player_map[Y_shoot][X_shoot] == 'S')
                {
                    arr_player_map[Y_shoot][X_shoot] = 'X';
                    shoot_chek_comp = false;
                    hit = true;
                }
                else if (arr_player_map[Y_shoot][X_shoot] == 'X')
                {
                    arr_player_map[Y_shoot][X_shoot] = 'X';
                    shoot_chek_comp = true;
                    hit = false;
                }
                else
                {
                    arr_player_map[Y_shoot][X_shoot] = 'O';
                    shoot_chek_comp = true;
                    hit = false;
                }
                arr_chek_double_shot[Y_shoot][X_shoot] = '+';
            }
        } while (!shoot_chek_comp);
    }
    else if (menu_complexity == 2)
    {
        int X_shoot = 0;
        int Y_shoot = 0;

        bool shoot_chek_comp = false;
        do {

            X_shoot = rand() % 10;
            Y_shoot = rand() % 10;


            if (arr_player_map[Y_shoot][X_shoot] == 'S')
            {
                arr_player_map[Y_shoot][X_shoot] = 'X';
                shoot_chek_comp = true;
            }
            else if (arr_player_map[Y_shoot][X_shoot] == 'X')
            {
                arr_player_map[Y_shoot][X_shoot] = 'X';
                shoot_chek_comp = false;
            }
            else
            {
                arr_player_map[Y_shoot][X_shoot] = 'O';
                shoot_chek_comp = false;
            }
        } while (!shoot_chek_comp);
    }
}



bool checkWin(char arr[Size][Size])
{
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (arr[i][j] == 'S')
            {
                return false;
            }
        }
    }
    return true;
}


void Game()
{
    bool Main_menu = true;

    int next;
    int complexity = 0;

    while (Main_menu)
    {
        cout << "\x1B[2J\x1B[H";
        setlocale(0, "");

        int menu_complexity = 0;

        int X_Axis = 0;
        int Y_Axis = 0;

        bool shoot_chek;
        bool batl_levl = true;

        char input;


        string menu[4] = { "\033[36m\
\t\t\t\t+=======================================================+\n\
\t\t\t\t| _   _                  _   _           _   _   _      |\n\
\t\t\t\t|| \\ | | __ ___   ____ _| | | |__   __ _| |_| |_| | ___ |\n\
\t\t\t\t||  \\| |/ _` \\ \\ / / _` | | | '_ \\ / _` | __| __| |/ _ \\|\n\
\t\t\t\t|| |\\  | (_| |\\ V / (_| | | | |_) | (_| | |_| |_| |  __/|\n\
\t\t\t\t||_| \\_|\\__,_| \\_/ \\__,_|_| |_.__/ \\__,_|\\__|\\__|_|\\___||\n\
\t\t\t\t+=======================================================+\033[37m\n",
"\
\t\t\t\t\t\t ____  _             \n\
\t\t\t\t\t\t|  _ \\| | __ _ _   _ \n\
\t\t\t\t\t\t| |_) | |/ _` | | | |\n\
\t\t\t\t\t\t|  __/| | (_| | |_| |\n\
\t\t\t\t\t\t|_|   |_|\\__,_|\\__, |\n\
\t\t\t\t\t\t               |___/ \
",
"\t\t\t\t\t\t ____        _           \n\
\t\t\t\t\t\t|  _ \\ _   _| | ___  ___ \n\
\t\t\t\t\t\t| |_) | | | | |/ _ \\/ __|\n\
\t\t\t\t\t\t|  _ <| |_| | |  __/\\__ \\\n\
\t\t\t\t\t\t|_| \\_\\\\__,_|_|\\___||___/\n\
",
"\t\t\t\t\t\t _____      _ _   \n\
\t\t\t\t\t\t| ____|_  _(_) |_ \n\
\t\t\t\t\t\t|  _| \\ \\/ / | __|\n\
\t\t\t\t\t\t| |___ >  <| | |_ \n\
\t\t\t\t\t\t|_____/_/\\_\\_|\\__|" };
        int list_menu = 1;
        char get;
        while (true)
        {
            //system("cls");
            cout << "\x1B[H";
            for (int i = 0; i < 4; i++)
            {
                if (i == list_menu)
                {
                    setColor(10);
                }
                else
                {
                    setColor(7);
                }
                cout << menu[i] << endl;
            }
            /* for(int i = 0; i < Size; i++)
             {

                 if (i == Y_Axis)
                 {
                     pozition_Y = true;
                 }
                 for(int j = 0; j < Size; j++)
                 {
                     if (j == X_Axis && pozition_Y)
                     {
                         setColor(14);
                     }
                     else
                     {
                         setColor(7);
                     }
                 }
             }*/
            get = _getch();
            if (get == 'w' || get == 'W')
            {
                list_menu--;
                if (list_menu < 1)
                {
                    list_menu = 3;
                }
            }
            else if (get == 's' || get == 'S')
            {
                list_menu++;
                if (list_menu > 3)
                {
                    list_menu = 1;
                }
            }
            if (get == 'e' || get == 'E')
            {
                break;
            }
        }
        //setColor(7);
        //----------------------------------------------------------------------
        switch (list_menu)
        {
        case 1:
            char get_menu_complexity;
            while (true)
            {
                system("cls");
                cout << "\033[0m================================================================================================================" << endl;
                string v_coml[3] = { "\t\t\t Бот Валера: Сложность(легкая) ", "\t\t\t Бот Антон: Сложность(средняя)","\t\t\t Бот Арбуз(Тайд): Сложность(Чем глубже тем больнее)" };
                for (int i = 0; i < 3; i++)
                {
                    if (i == menu_complexity)
                    {
                        setColor(10);
                    }
                    else
                    {
                        setColor(7);
                    }
                    cout << v_coml[i] << endl;
                }
                cout << "\033[0m================================================================================================================" << endl;
                get_menu_complexity = _getch();
                if (get_menu_complexity == 'w' || get_menu_complexity == 'W')
                {
                    menu_complexity--;
                    if (menu_complexity < 0)
                    {
                        menu_complexity = 2;
                    }
                }
                else if (get_menu_complexity == 's' || get_menu_complexity == 'S')
                {
                    menu_complexity++;
                    if (menu_complexity > 2)
                    {
                        menu_complexity = 0;
                    }
                }
                if (get_menu_complexity == 'e' || get_menu_complexity == 'E')
                {
                    break;
                }
            }
            system("cls");

            setlocale(0, "");
            srand(time(0));

            Map(arr_player_map);
            Map(arr_computer_map);

            Ships(arr_player_map);
            Ships(arr_computer_map);

            while (batl_levl)
            {
                do {
                    shoot_chek = false;
                    system("cls");

                    cout << "\t\t\t\t\t\t  Поле Компьютера" << endl;
                    Print(arr_computer_map, X_Axis, Y_Axis, true);

                    cout << "\t\t\t\t\t\t  Поле Игрока" << endl;
                    Print(arr_player_map, -1, -1);

                    input = _getch();
                    if (input == 'w' || input == 'W')
                    {
                        Y_Axis--;
                    }
                    else if (input == 'd' || input == 'D')
                    {
                        X_Axis++;
                    }
                    else if (input == 's' || input == 'S')
                    {
                        Y_Axis++;
                    }
                    else if (input == 'a' || input == 'A')
                    {
                        X_Axis--;
                    }
                    else if (input == 'l' || input == 'L')
                    {
                        batl_levl = false;
                        break;
                    }
                    else if (input == 'e' || input == 'E')
                    {
                        if (arr_computer_map[Y_Axis][X_Axis] == 'S')
                        {
                            arr_computer_map[Y_Axis][X_Axis] = 'X';
                            shoot_chek = false;
                        }
                        else if (arr_computer_map[Y_Axis][X_Axis] == 'X')
                        {
                            arr_computer_map[Y_Axis][X_Axis] = 'X';
                            shoot_chek = true;
                        }
                        else
                        {
                            arr_computer_map[Y_Axis][X_Axis] = 'O';
                            shoot_chek = true;
                        }
                    }
                } while (!shoot_chek);
                /*bool shoot_chek_comp = false;
                bool temp = false;
                do {

                    X_shoot = rand() % 10;
                    Y_shoot = rand() % 10;


                    if (arr_player_map[Y_shoot][X_shoot] == 'S')
                    {
                        arr_player_map[Y_shoot][X_shoot] = 'X';
                    }
                    else if (arr_player_map[Y_shoot][X_shoot] == 'X')
                    {
                        arr_player_map[Y_shoot][X_shoot] = 'X';
                        shoot_chek_comp = false;
                        temp = true;
                    }
                    else
                    {
                        arr_player_map[Y_shoot][X_shoot] = 'O';
                        shoot_chek_comp = true;
                        temp = false;
                    }
                } while (!shoot_chek_comp);*/
                BotBattle(menu_complexity);

                if (checkWin(arr_computer_map))
                {
                    cout << "\t\t\t\tВы победили! Все корабли противника потоплены!" << endl;
                    next = _getch();
                    break;
                }
                if (checkWin(arr_player_map))
                {
                    cout << "\t\t\t\tВы проиграли! Все ваши корабли потоплены!" << endl;
                    next = _getch();
                    break;
                }
            }
            break;
        case 2:
            cout << "\x1B[2J\x1B[H";
            cout << "\t\t\t\t\t\tОб игре" << endl;
            //system("cls");
            cout << "================================================================================================================" << endl;
            cout << "\t\t\tИгра \"Морской бой\"" << endl;
            cout << "\t\t\tДлительность партии: 10-15 минут" << endl;
            cout << "\t\t\tИгроков: 2 (3 варианта противника)" << endl;
            cout << "\t\t\tРасстановка (рандом)" << endl;
            cout << "\t\t\tУправление на (WASD),  кнопка взаимодействия (E)" << endl;
            cout << "\t\t\tФигуры " << endl;
            cout << "\t\t\t1 корабль — ряд из 4 клеток («четырёхпалубный»; линкор)" << endl;
            cout << "\t\t\t2 корабля — ряд из 3 клеток («трёхпалубные»; крейсера)" << endl;
            cout << "\t\t\t3 корабля — ряд из 2 клеток («двухпалубные»; эсминцы)" << endl;
            cout << "\t\t\t4 корабля — 1 клетка («однопалубные»; торпедные катера)" << endl;
            cout << "===================================================================================================================" << endl;
            cout << "Нажмите любу клавишу что-бы выйти: ";
            next = _getch();
            cout << "\x1B[2J\x1B[H";
            if (next == 'e' || next == 'E')
            {
                cout << "\x1B[2J\x1B[H";
                string Developers = "\t\t\t\t\t\tРазработчики\n\t\tПрограммист, Гейм дизайнер, Художник, UI/UX-дизайнеры, Тестировщик\n\t\t\t\t\t\tДенисов Роман\n\n\t\t\t\t\t  Программист,Сценарист\n\t\t\t\t\t   Кутаренко Ростислав\n\n\t\t\t\t\tТестировщик,Поставщик жижи\n\t\t\t\t\t    Жидков Анатолий\n\n\t\t\t\t\t\t  Не папа:(\n\t\t\t\t\t\tПрытков Егор\n\n\n\t\t\t\t\tНа разработку ушло 5 банок пива ";
                for (int i = 0; i < Developers.length(); i++)
                {
                    cout << Developers[i];
                    Sleep(7);
                }
                next = _getch();
                cout << "\x1B[2J\x1B[H";
            }
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "error";
            break;
        }
    }
}

int main()
{
    Game();
}