#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


//                                                             <------(  Function Prototypes  )------>

bool loadData(string[][10], int &laptopCount, string[][3], int &usersCount, string announcement[5], int &announcementCount, string order[][4], int &ordersCount);
void storeLaptopsData(string[][10], int &laptopCount);
void storeUsersData(string[][3], int &usersCount);
void storeOrdersData(string[][4], int &ordersCount);
void storeAnnouncementsData(string[5], int &announcementCount);
string field(string record, int field);

string loginAs(string[][3], int &usersCount);
bool loginPage(string role, string[][3], int &usersCount);

string signupAs(string[][3], int &usersCount);
bool signupPage(string role, string[][3], int &usersCount);

string sudoSignupAs(string user[][3], int &usersCount);
bool sudoSignupPage(string inputRole, string user[][3], int &usersCount);

int adminPage();
int customerPage();
int managerPage();
int employeePage();

void laptopStockMenu(string laptop[][10], int &laptopCount);
void addLaptop(string[][10], int &laptopCount);
void updateLaptop(string[][10], int &laptopCount);
void removeLaptop(string[][10], int &laptopCount);
void displayLaptops(string[][10], int &laptopCount);
void displayLaptopsStock(string[][10], int &laptopCount);
void displayLaptopsCategories(string laptop[][10], int &laptopCount);
int checkLaptop(string, string, string, string laptop[][10], int &laptopCount);
int checkLaptopManu(string manufacturer, string laptop[][10], int &laptopCount);

void displayUsers(string user[][3], int &usersCount);
void displayEmployees(string user[][3], int &usersCount);

void makeAnnouncement(string announcement[5], int &announcementCount);
void viewAnnouncements(string announcement[5], int &announcementCount);

void placeOrder(string laptop[][10], string order[][4], int &laptopCount, int &ordersCount);
void orders(string laptop[][10], string order[][4], int &laptopCount, int &ordersCount);
void yourOrders(string laptop[][10], string order[][4], int &laptopCount, int &ordersCount);

void stockWorth(string laptop[][10], int &laptopCount);

bool validation(const string &str, string type);

void welcomeScreen();
void printHeader();
void comingSoon();
void contactAdmin();
void dummyData(string user[][3], string laptop[][10], int &usersCount, int &laptopCount);

int arrowy;
string currentUser;
int moveArrow(int input, int arrowLocation, int top, int bottom);
void printArrow(int);
void eraseArrow();
void cursor(bool);
void gotoxy(int, int);

//                                                           <------(  Start  )------>

main()
{

    string user[30][3];
    int usersCount = 0;
    string laptop[50][10];
    int laptopCount = 0;
    string order[20][4];
    int ordersCount = 0;
    string announcement[5];
    int announcementCount = 0;

    string role = "";
    int option = 0;

    cursor(0); //  Hiding Cursor

    welcomeScreen();

    if (!loadData(laptop, laptopCount, user, usersCount, announcement, announcementCount, order, ordersCount))
        return 0;

    while (role != "Exit")
    {
        role = loginAs(user, usersCount); //                              Role Selecter

        if (role == "Admin")
        {
            while (true)
            {
                option = adminPage();
                if (option == 1)
                    displayUsers(user, usersCount);
                else if (option == 2)
                    laptopStockMenu(laptop, laptopCount);
                else if (option == 3)
                    makeAnnouncement(announcement, announcementCount);
                else if (option == 4)
                    sudoSignupAs(user, usersCount);
                else if (option == 5)
                    stockWorth(laptop, laptopCount);
                else if (option == 6)
                    break;
            }
        }

        else if (role == "Manager")
        {
            while (true)
            {
                option = managerPage();
                if (option == 1)
                    displayEmployees(user, usersCount);
                else if (option == 2)
                    laptopStockMenu(laptop, laptopCount);
                else if (option == 3)
                    viewAnnouncements(announcement, announcementCount);
                else if (option == 4)
                    makeAnnouncement(announcement, announcementCount);
                else if (option == 5)
                    stockWorth(laptop, laptopCount);
                else if (option == 6)
                    break;
            }
        }

        else if (role == "Employee")
        {
            while (true)
            {
                option = employeePage();
                if (option == 1)
                    addLaptop(laptop, laptopCount);
                else if (option == 2)
                    orders(laptop, order, laptopCount, ordersCount);
                else if (option == 3)
                    viewAnnouncements(announcement, announcementCount);
                else if (option == 4)
                    displayLaptops(laptop, laptopCount);
                else if (option == 5)
                    break;
            }
        }

        else if (role == "Customer")
        {
            while (true)
            {
                option = customerPage();
                if (option == 1)
                    displayLaptops(laptop, laptopCount);
                else if (option == 2)
                    displayLaptopsCategories(laptop, laptopCount);
                else if (option == 3)
                    placeOrder(laptop, order, laptopCount, ordersCount);
                else if (option == 4)
                    yourOrders(laptop, order, laptopCount, ordersCount);
                else if (option == 5)
                    break;
            }
        }

        else if (role == "Signup")
            signupAs(user, usersCount);
    }

    storeLaptopsData(laptop, laptopCount);
    storeUsersData(user, usersCount);
    storeAnnouncementsData(announcement, announcementCount);
}

//                                                       <------(  Files Management  )------>

bool loadData(string laptop[][10], int &laptopCount, string user[][3], int &usersCount, string announcement[5], int &announcementCount, string order[][4], int &ordersCount)
{
    string record;
    bool laptopsFile = false, usersFile = false, announcementsFile = false, ordersFile = false;

    // Load Laptops

    fstream laptopsData;
    laptopsData.open("laptops.csv", ios::in);
    if (laptopsData.is_open())
    {
        while (getline(laptopsData, record))
        {
            laptop[laptopCount][0] = field(record, 1);
            laptop[laptopCount][1] = field(record, 2);
            laptop[laptopCount][2] = field(record, 3);
            laptop[laptopCount][3] = field(record, 4);
            laptop[laptopCount][4] = field(record, 5);
            laptop[laptopCount][5] = field(record, 6);
            laptop[laptopCount][6] = field(record, 7);
            laptop[laptopCount][7] = field(record, 8);
            laptop[laptopCount][8] = field(record, 9);
            laptopCount++;
        }
        laptopsData.close();
    }
    else
        laptopsFile = true;

    // Load Users

    fstream usersData;
    usersData.open("users.csv", ios::in);
    if (usersData.is_open())
    {
        while (getline(usersData, record))
        {
            user[usersCount][0] = field(record, 1);
            user[usersCount][1] = field(record, 2);
            user[usersCount][2] = field(record, 3);
            usersCount++;
        }
        usersData.close();
    }
    else
        usersFile = true;

    // Load Orders

    fstream ordersData;
    ordersData.open("orders.csv", ios::in);
    if (ordersData.is_open())
    {
        while (getline(ordersData, record))
        {
            order[ordersCount][0] = field(record, 1);
            order[ordersCount][1] = field(record, 2);
            order[ordersCount][2] = field(record, 3);
            order[ordersCount][3] = field(record, 4);
            ordersCount++;
        }
        ordersData.close();
    }
    else
        ordersFile = true;

    // Load Accouncements

    fstream announcementsData;
    announcementsData.open("announcements.txt", ios::in);
    if (announcementsData.is_open())
    {
        while (getline(announcementsData, record))
        {
            announcement[announcementCount] = record;
            announcementCount++;
        }
        announcementsData.close();
    }
    else
        announcementsFile = true;

    // if any file mixxing

    if (laptopsFile || usersFile || announcementsFile || ordersFile)
    {
        printHeader();

        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\t\t\t\t\t\tData Loading Failed\n\t\t\t\t\t\t-------------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tUnable to load data. Following files were not found:\n";

        Sleep(300);

        if (laptopsFile)
            cout << "\n\n\t\t\to) Laptops DataBase (laptops.csv)";
        if (usersFile)
            cout << "\n\n\t\t\to) Users DataBase (users.csv)";
        if (ordersFile)
            cout << "\n\n\t\t\to) Orders Database (orders.csv)";
        if (announcementsFile)
            cout << "\n\n\t\t\to) Announcements File (announcement.txt)";

        Sleep(300);
        cout << "\n\n\n\t\tPress any key to continue...";
        getch();

        printHeader();
        int arrowLocation = 1, input;
        int option = 0;

        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\tChoose any option:\n\t\t=================";
        cout << endl
             << endl;

        printArrow(11);

        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t1. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Create fresh blank files";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t2. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Exit Application";

        while (true)
        {
            input = getch();

            if (input == '1' || input == '2')
                option = input - '0';

            else if (input == 13)
            {
                option = arrowLocation;
            }

            else if (input == 224)
            {
                arrowLocation = moveArrow(input, arrowLocation, 11, 2);
            }

            if (option > 0 && option <= 2)
            {
                if (option == 1)
                {
                    storeLaptopsData(laptop, laptopCount);
                    storeUsersData(user, usersCount);
                    storeOrdersData(order, ordersCount);
                    storeAnnouncementsData(announcement, announcementCount);
                    return true;
                }
                else if (option == 2)
                {
                    return false;
                }
            }
        }
    }

    else
        return true;
}

void storeLaptopsData(string laptop[][10], int &laptopCount)
{
    string record;

    fstream laptopsData;
    laptopsData.open("laptops.csv", ios::out);
    if (laptopsData.is_open())
    {
        for (int i = 0; i < laptopCount; i++)
        {
            record = laptop[i][0] + "," + laptop[i][1] + "," + laptop[i][2] + "," + laptop[i][3] + "," + laptop[i][4] + "," + laptop[i][5] + "," + laptop[i][6] + "," + laptop[i][7] + "," + laptop[i][8] + "," + laptop[i][9];
            laptopsData << record;
            if (i != laptopCount)
                laptopsData << endl;
        }
        laptopsData.close();
    }
}

void storeUsersData(string user[][3], int &usersCount)
{
    string record;

    fstream usersData;
    usersData.open("users.csv", ios::out);
    if (usersData.is_open())
    {
        for (int i = 0; i < usersCount; i++)
        {
            record = user[i][0] + "," + user[i][1] + "," + user[i][2];
            usersData << record;
            if (i != usersCount)
                usersData << endl;
        }
        usersData.close();
    }
}

void storeOrdersData(string order[][4], int &ordersCount)
{
    string record;

    fstream ordersData;
    ordersData.open("orders.csv", ios::out);
    if (ordersData.is_open())
    {
        for (int i = 0; i < ordersCount; i++)
        {
            record = order[i][0] + "," + order[i][1] + "," + order[i][2] + "," + order[i][3];
            ordersData << record;
            if (i != ordersCount)
                ordersData << endl;
        }
        ordersData.close();
    }
}

void storeAnnouncementsData(string announcement[5], int &announcementCount)
{
    string record;

    fstream announcementsData;
    announcementsData.open("announcements.txt", ios::out);
    if (announcementsData.is_open())
    {
        for (int i = 0; i < announcementCount; i++)
        {
            record = announcement[i];
            announcementsData << record << endl;
        }
        announcementsData.close();
    }
}

string field(string record, int field)
{
    int commaNumber = 1;

    string currentItem;

    for (int i = 0; i < record.length(); i++)
    {
        if (record[i] == ',')
            commaNumber++;

        else if (commaNumber == field)
            currentItem += record[i];
    }

    return currentItem;
}

//                                                         <------(  Accounts  )------>

string loginAs(string user[][3], int &usersCount)
{
    int top = 11;
    string selectRole;
    while (true)
    {
        printHeader();

        int arrowLocation = 1, input, selection = 0;
        selectRole = "";

        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tLogin as:\n\t\t=========";

        printArrow(top);

        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t1. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Admin";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t2. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Manager";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t3. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Employee";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t4. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Customer";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t5. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Sign up instead";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t6. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Exit";

        while (true)
        {
            input = getch();

            if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6')
                break;

            else if (input == 13)
            {
                input = arrowLocation + '0';
                break;
            }

            else if (input == 224)
            {
                arrowLocation = moveArrow(input, arrowLocation, 11, 6);
            }
        }

        if (input == '1')
            selectRole = "Admin";
        else if (input == '2')
            selectRole = "Manager";
        else if (input == '3')
            selectRole = "Employee";
        else if (input == '4')
            selectRole = "Customer";
        else if (input == '5')
            return "Signup";
        else if (input == '6')
            return "Exit";

        if (loginPage(selectRole, user, usersCount))
        {
            return selectRole;
        }
    }
}

bool loginPage(string role, string user[][3], int &usersCount)
{

    string inputUsername;
    string inputPassword;
    int userNumber;

    while (true)
    {
        inputPassword = "";
        userNumber = -1;

        printHeader();
        cout << endl;

        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tEnter your ";
        SetConsoleTextAttribute(hConsole, 10);
        cout << role;
        SetConsoleTextAttribute(hConsole, 11);
        cout << " credientials:";
        cout << endl
             << endl
             << endl;

        SetConsoleTextAttribute(hConsole, 14);
        cout << "\t\t\tUsername: ";
        cout << "\n\n\t\t\tPassword: ";
        SetConsoleTextAttribute(hConsole, 15);

        cursor(1);
        gotoxy(34, 12);
        // cin >> inputUsername;

        bool condition = true;
        while (condition)
        {
            cursor(1);
            gotoxy(34, 12);
            // cin.ignore();
            getline(cin, inputUsername);
            if (!validation(inputUsername, "noSpace") || validation(inputUsername, "null"))
            {
                gotoxy(34, 12);
                cursor(0);
                SetConsoleTextAttribute(hConsole, 12);
                if (validation(inputUsername, "null"))
                    cout << "Please Enter some name                  ";
                else
                    cout << "Username can't contain Space           ";
                SetConsoleTextAttribute(hConsole, 15);
                getch();
                gotoxy(34, 12);
                cout << "                                       ";
                gotoxy(34, 12);

                cursor(1);
            }
            else
                condition = false;
        }

        gotoxy(34, 14);

        // cin >> inputPassword;

        int input = 0;
        string password;
        while (input != 13)
        {
            input = getch();
            if (input != 13 && input != 8)
            {
                cout << "*";

                inputPassword += input;
            }
        }

        cursor(0);

        for (int i = 0; i <= usersCount; i++)
        {
            if (inputUsername == user[i][0])
            {
                userNumber = i;
                break;
            }
        }

        if (inputPassword == user[userNumber][1] && role == user[userNumber][2])
        {
            currentUser = user[userNumber][0];
            SetConsoleTextAttribute(hConsole, 10);
            cout << "\n\n\t\t\t\t\t\tLogin Successful\n\t\t\t\t\t\t----------------\n";
            SetConsoleTextAttribute(hConsole, 15);
            getch();

            return true;
        }

        else
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n\n\t\t\t\t\t\tLogin Failed\n\t\t\t\t\t\t------------";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "\n\n\t\tInvalid Credientials.\n\n\t\tPress any key to continue...";
            getch();

            printHeader();
            int arrowLocation = 1, input;
            int option = 0;

            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t\tChoose any option:\n\t\t=================";
            cout << endl
                 << endl;

            printArrow(11);

            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t1. ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "Retry Login";
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n\n\t2. ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "Go Back to Login Page";

            while (true)
            {
                input = getch();

                if (input == '1' || input == '2')
                    option = input - '0';

                else if (input == 13)
                {
                    option = arrowLocation;
                }

                else if (input == 224)
                {
                    // input = getch();
                    // if (input == 72) // up
                    // {
                    //     if (arrowLocation > 1)
                    //     {
                    //         arrowLocation--;
                    //         eraseArrow();
                    //         printArrow(arrowy - 2);
                    //     }
                    // }

                    // else if (input == 80)
                    // {
                    //     if (arrowLocation < 2)
                    //     {
                    //         arrowLocation++;
                    //         eraseArrow();
                    //         printArrow(arrowy + 2);
                    //     }
                    // }

                    arrowLocation = moveArrow(input, arrowLocation, 11, 2);
                }

                if (option > 0 && option <= 2)
                {
                    if (option == 1)
                        break;
                    else if (option == 2)
                        return false;
                }
            }
        }
    }
}

string signupAs(string user[][3], int &usersCount)
{
    printHeader();

    int arrowLocation = 1, input;
    int signupAs = 0;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\t\tSignup as:\n\t\t==========";
    cout << endl
         << endl;

    printArrow(11);

    SetConsoleTextAttribute(hConsole, 12);
    cout << "\t1. ";
    SetConsoleTextAttribute(hConsole, 8);
    cout << "Admin";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t2. ";
    SetConsoleTextAttribute(hConsole, 8);
    cout << "Manager";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t3. ";
    SetConsoleTextAttribute(hConsole, 8);
    cout << "Employee";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t4. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Customer";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t5. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "login Instead";

    while (true)
    {
        input = getch();

        if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5')
            signupAs = input - '0';

        else if (input == 13)
        {
            signupAs = arrowLocation;
        }

        else if (input == 224)
        {
            arrowLocation = moveArrow(input, arrowLocation, 11, 5);
        }

        if (signupAs > 0 && signupAs <= 5)
        {
            if (signupAs == 1)
                contactAdmin();
            else if (signupAs == 2)
                contactAdmin();
            else if (signupAs == 3)
                contactAdmin();
            else if (signupAs == 4)
                signupPage("Customer", user, usersCount);
            return "";
        }
    }
}

bool signupPage(string inputRole, string user[][3], int &usersCount)
{

    // cin.ignore();
    string inputUsername;
    string inputPassword;

    printHeader();
    cout << endl;

    SetConsoleTextAttribute(hConsole, 11);
    cout << "\t\tSet your ";
    SetConsoleTextAttribute(hConsole, 10);
    cout << inputRole;
    SetConsoleTextAttribute(hConsole, 11);
    cout << " credientials:";
    cout << endl
         << endl
         << endl;

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\t\t\tSet Username: ";
    cout << "\n\n\t\t\tSet Password: ";
    SetConsoleTextAttribute(hConsole, 15);

    bool condition = true;
    while (condition)
    {
        cursor(1);
        gotoxy(38, 12);
        // cin.ignore();
        getline(cin, inputUsername);
        if (!validation(inputUsername, "noSpace") || validation(inputUsername, "null"))
        {
            gotoxy(38, 12);
            cursor(0);
            SetConsoleTextAttribute(hConsole, 12);
            if (validation(inputUsername, "null"))
                cout << "Please Enter some name                  ";
            else
                cout << "Username can't contain Space           ";
            SetConsoleTextAttribute(hConsole, 15);
            getch();
            gotoxy(38, 12);
            cout << "                                       ";
            gotoxy(38, 12);

            cursor(1);
        }
        else
            condition = false;
    }

    condition = true;

    while (condition)
    {
        cursor(1);
        gotoxy(38, 14);
        getline(cin, inputPassword);
        if (!validation(inputPassword, "alphaNumeric") || !validation(inputUsername, "noComma"))
        {
            gotoxy(38, 14);
            cursor(0);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Password must contains letters and digits           ";
            SetConsoleTextAttribute(hConsole, 15);
            getch();
            gotoxy(38, 14);
            cout << "                                                    ";
            gotoxy(38, 14);

            cursor(1);
        }
        else
            condition = false;
    }
    cursor(0);

    int i = 0;
    while (user[i][0] != "")
    {
        i++;
    }

    user[i][0] = inputUsername;
    user[i][1] = inputPassword;
    user[i][2] = inputRole;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n\n\t\t\t\t\tAccount Created Successfully\n\t\t\t\t\t----------------------------\n";
    usersCount++;
    storeUsersData(user, usersCount);
    getch();
    SetConsoleTextAttribute(hConsole, 15);

    return 1;
}

string sudoSignupAs(string user[][3], int &usersCount)
{
    printHeader();

    int arrowLocation = 1, input;
    int signupAs = 0;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\t\tSet up as:\n\t\t==========";
    cout << endl
         << endl;

    printArrow(11);

    SetConsoleTextAttribute(hConsole, 12);
    cout << "\t1. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Admin";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t2. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Manager";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t3. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Employee";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t4. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Customer";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t5. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Go Back";

    while (true)
    {
        input = getch();

        if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5')
            signupAs = input - '0';

        else if (input == 13)
        {
            signupAs = arrowLocation;
        }

        else if (input == 224)
        {
            arrowLocation = moveArrow(input, arrowLocation, 11, 5);
        }

        if (signupAs > 0 && signupAs <= 5)
        {
            if (signupAs == 1)
                signupPage("Admin", user, usersCount);
            else if (signupAs == 2)
                signupPage("Manager", user, usersCount);
            else if (signupAs == 3)
                signupPage("Employee", user, usersCount);
            else if (signupAs == 4)
                signupPage("Customer", user, usersCount);
            return "";
        }
    }
}

bool sudoSignupPage(string inputRole, string user[][3], int &usersCount)
{

    cin.ignore();
    string inputUsername;
    string inputPassword;

    printHeader();
    cout << endl;

    SetConsoleTextAttribute(hConsole, 11);
    cout << "\t\tSet your ";
    SetConsoleTextAttribute(hConsole, 10);
    cout << inputRole;
    SetConsoleTextAttribute(hConsole, 11);
    cout << " credientials:";
    cout << endl
         << endl
         << endl;

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\t\t\tSet Username: ";
    cout << "\n\n\t\t\tSet Password: ";
    SetConsoleTextAttribute(hConsole, 15);

    bool condition = true;
    while (condition)
    {
        cursor(1);
        gotoxy(38, 12);
        // cin.ignore();
        getline(cin, inputUsername);
        if (!validation(inputUsername, "noSpace") || validation(inputUsername, "null"))
        {
            gotoxy(38, 12);
            cursor(0);
            SetConsoleTextAttribute(hConsole, 12);
            if (validation(inputUsername, "null"))
                cout << "Please Enter some name                  ";
            else
                cout << "Username can't contain Space           ";
            SetConsoleTextAttribute(hConsole, 15);
            getch();
            gotoxy(38, 12);
            cout << "                                       ";
            gotoxy(38, 12);

            cursor(1);
        }
        else
            condition = false;
    }

    condition = true;

    while (condition)
    {
        cursor(1);
        gotoxy(38, 14);
        getline(cin, inputPassword);
        if (!validation(inputPassword, "alphaNumeric") || !validation(inputUsername, "noComma"))
        {
            gotoxy(38, 14);
            cursor(0);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Password must contains letters and digits           ";
            SetConsoleTextAttribute(hConsole, 15);
            getch();
            gotoxy(38, 14);
            cout << "                                                    ";
            gotoxy(38, 14);

            cursor(1);
        }
        else
            condition = false;
    }
    cursor(0);

    int i = 0;
    while (user[i][0] != "")
    {
        i++;
    }

    user[i][0] = inputUsername;
    user[i][1] = inputPassword;
    user[i][2] = inputRole;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n\n\t\t\t\t\tAccount Created Successfully\n\t\t\t\t\t----------------------------\n";
    usersCount++;
    storeUsersData(user, usersCount);
    getch();
    SetConsoleTextAttribute(hConsole, 15);

    return 1;
}

//                                                        <------(  Users Pages  )------>

int adminPage()
{
    // cout << "\t1. Settings\n\t2. Database\n\t3. Manage Staff\n\t4. Budget and Sales\n\t5. Stocks\n\t6. Salaries\n\t7. Add Announcement\n\n\tSelect any option...";
    printHeader();

    int arrowLocation = 1, input;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\t\tHi Admin:    (" << currentUser << ")" << "\n\t\t=========";
    cout << endl
         << endl;

    printArrow(11);

    SetConsoleTextAttribute(hConsole, 12);
    cout << "\t1. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "View Users";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t2. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Manage Stocks";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t3. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Make Announcements";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t4. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Set up new user";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t5. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Stock Worth";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t6. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Log out";

    while (true)
    {
        input = getch();

        if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6')
            return input - '0';

        else if (input == 13)
        {
            return arrowLocation;
        }

        else if (input == 224)
        {
            arrowLocation = moveArrow(input, arrowLocation, 11, 6);
        }
    }
}

int customerPage()
{
    // cout << "\t1. View Laptops Gallery\n\t2. View Laptops with Categories\n\t3. View Accessories\n\t4. Your Cart\n\t5. Your Orders\n\t6. Your Quires\n\t7. Add a Comment\n\n\tSelect any option...";
    printHeader();

    int arrowLocation = 1, input;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\t\tWelcome back to Store    (" << currentUser << ")" << "\n\t\t=====================";
    cout << endl
         << endl;

    printArrow(11);

    SetConsoleTextAttribute(hConsole, 12);
    cout << "\t1. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "View Laptops Gallery";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t2. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Search Laptops";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t3. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Place Order";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t4. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Your Orders";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t5. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Log out";

    while (true)
    {
        input = getch();

        if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5')
            return input - '0';

        else if (input == 13)
        {
            return arrowLocation;
        }

        else if (input == 224)
        {
            arrowLocation = moveArrow(input, arrowLocation, 11, 5);
        }
    }
}

int managerPage()
{
    // cout << "\t1. Employees\n\t2. View Laptop Stock\n\t3. Manage Laptop Stock\n\t4. Manage Accessories Stock\n\t5. Manage Prices\n\t6. View Sales\n\t7. Communication\n\n\tSelect any option...";
    printHeader();

    int arrowLocation = 1, input;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\t\tWelcome back to Store    (" << currentUser << ")" << "\n\t\t=====================";
    cout << endl
         << endl;

    printArrow(11);

    SetConsoleTextAttribute(hConsole, 12);
    cout << "\t1. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Manage Employees";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t2. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Manage Laptop Stocks";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t3. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "View Announcements";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t4. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Make Announcement";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t5. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Stock Worth";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t6. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Log out";

    while (true)
    {
        input = getch();

        if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6')
            return input - '0';

        else if (input == 13)
        {
            return arrowLocation;
        }

        else if (input == 224)
        {
            arrowLocation = moveArrow(input, arrowLocation, 11, 6);
        }
    }
}

int employeePage()
{
    // cout << "\t1. Add Laptop Stock\n\t2. Add Accessories Stock\n\t3. Delete Stock\n\t4. View Announcements\n\t5. Message\n\t6. Manage Orders\n\t7. Salary Status\n\n\tSelect any option...";
    printHeader();

    int arrowLocation = 1, input;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\t\tWelcome back to Store    (" << currentUser << ")" << "\n\t\t=====================";
    cout << endl
         << endl;

    printArrow(11);

    SetConsoleTextAttribute(hConsole, 12);
    cout << "\t1. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Add Laptop Stock";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t2. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Manage Orders";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t3. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "View Announcements";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t4. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Customer Gallery";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\t5. ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Log out";

    while (true)
    {
        input = getch();

        if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5')
            return input - '0';

        else if (input == 13)
        {
            return arrowLocation;
        }

        else if (input == 224)
        {
            arrowLocation = moveArrow(input, arrowLocation, 11, 5);
        }
    }
}

//                                                       <------(  Laptops Stock  )------>

void laptopStockMenu(string laptop[][10], int &laptopCount)
{
    while (true)
    {
        printHeader();

        int arrowLocation = 1, input;

        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tManage Laptop Stocks:\n\t\t====================";
        cout << endl
             << endl;

        printArrow(11);

        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t1. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Add Laptop";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t2. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Remove Laptop";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t3. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Edit Laptop Stock";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t4. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Display Available Laptops";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t5. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Go Back";

        while (true)
        {
            input = getch();

            if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5')
                break;

            else if (input == 13)
            {
                input = arrowLocation + '0';
                break;
            }

            else if (input == 224)
            {
                arrowLocation = moveArrow(input, arrowLocation, 11, 5);
            }
        }

        if (input == '1')
            addLaptop(laptop, laptopCount);
        else if (input == '2')
            removeLaptop(laptop, laptopCount);
        else if (input == '3')
            updateLaptop(laptop, laptopCount);
        else if (input == '4')
            displayLaptopsStock(laptop, laptopCount);
        else if (input == '5')
            break;
    }
}

void addLaptop(string laptop[][10], int &laptopCount)
{
    printHeader();

    SetConsoleTextAttribute(hConsole, 11);
    cout << "\t\tEnter New Laptop Details:\n\t\t-------------------------";
    cout << endl
         << endl;

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\t\t\tManufacturer: ";
    cout << "\n\n\t\t\t      Series: ";
    cout << "\n\n\t\t\t       Model: ";
    cout << "\n\n\t\t\t   Body Size: ";
    cout << "\n\n\t\t\t         CPU: ";
    cout << "\n\n\t\t\t    RAM \033[0m(GB): ";
    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n\n\t\t\tStorage \033[0m(GB): ";
    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n\n\t\t\t       Price: \033[0m$";
    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n\n\t\t\t    Quantity: ";
    SetConsoleTextAttribute(hConsole, 15);

    int y = 11;
    cursor(1);
    cin.ignore();
    for (int i = 0; i < 9; i++)
    {
        gotoxy(39, y);
        getline(cin, laptop[laptopCount][i]);

        // validations
        if ((i == 0 || i == 1) && !validation(laptop[laptopCount][i], "textonly") || validation(laptop[laptopCount][i], "null"))
        {
            gotoxy(39, y);
            cursor(0);
            SetConsoleTextAttribute(hConsole, 12);
            // cout << "Invalid Input";

            if (validation(laptop[laptopCount][i], "null"))
                cout << "Please Input                  ";
            else
                cout << "Invalid Input           ";

            SetConsoleTextAttribute(hConsole, 15);
            getch();
            gotoxy(39, y);
            cout << "             ";
            gotoxy(39, y);

            cursor(1);
            i--;
            y -= 2;
        }

        else if ((i == 3 || i == 5 || i == 6 || i == 7 || i == 8) && !validation(laptop[laptopCount][i], "numberonly"))
        {
            gotoxy(39, y);
            cursor(0);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Invalid Input";
            SetConsoleTextAttribute(hConsole, 15);
            getch();
            gotoxy(39, y);
            cout << "                            ";
            gotoxy(39, y);

            cursor(1);
            i--;
            y -= 2;
        }

        y += 2;
    }

    laptopCount++;
    storeLaptopsData(laptop, laptopCount);
    Sleep(500);
    cursor(0);

    printHeader();

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\t\t\t\t\t\tLaptop Added\n\t\t\t\t\t\t------------\n";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "\n\n\t\tPress any key to continue.....";
    getch();
}

void removeLaptop(string laptop[][10], int &laptopCount)
{

    if (laptopCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Data Found\n\t\t\t\t\t\t-------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tPlease add Laptop Stock.\n\n\t\tPress any key to continue...";

        getch();
        return;
    }
    while (true)
    {
        printHeader();

        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\tEnter Laptop to Remove:\n\t\t----------------------";
        cout << endl
             << endl
             << endl;

        SetConsoleTextAttribute(hConsole, 14);
        cout << "\t\t\tManufacturer: ";
        cout << "\n\n\t\t\t      Series: ";
        cout << "\n\n\t\t\t       Model: ";
        SetConsoleTextAttribute(hConsole, 15);

        cursor(1);
        string manufacturer, series, model;
        gotoxy(39, 12);
        getline(cin, manufacturer);
        gotoxy(39, 14);
        getline(cin, series);
        gotoxy(39, 16);
        getline(cin, model);
        cursor(0);

        int index = checkLaptop(manufacturer, series, model, laptop, laptopCount);

        if (index == -1)
        {
            printHeader();
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t\t\t\t\t\tLaptop Not Found\n\t\t\t\t\t\t----------------";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "\n\n\t\tEnter Correct Laptop Details.\n\n\t\tPress any key to continue...";

            getch();

            printHeader();
            int arrowLocation = 1, input;
            int option = 0;

            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t\tChoose any option:\n\t\t=================";
            cout << endl
                 << endl;

            printArrow(11);

            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t1. ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "Try Again";
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n\n\t2. ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "Go Back";

            while (true)
            {
                input = getch();

                if (input == '1' || input == '2')
                    option = input - '0';

                else if (input == 13)
                {
                    option = arrowLocation;
                }

                else if (input == 224)
                {
                    arrowLocation = moveArrow(input, arrowLocation, 11, 2);
                }

                if (option > 0 && option <= 2)
                {
                    if (option == 1)
                        break;
                    if (option == 2)
                        return;
                }
            }
        }

        else
        {
            for (int i = index; i < laptopCount; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    laptop[i][j] = laptop[i + 1][j];
                }
            }

            laptopCount--;
            storeLaptopsData(laptop, laptopCount);

            Sleep(500);
            printHeader();

            SetConsoleTextAttribute(hConsole, 10);
            cout << "\t\t\t\t\t\tLaptop Removed\n\t\t\t\t\t\t--------------\n";
            Sleep(500);
            SetConsoleTextAttribute(hConsole, 15);
            cout << "\n\n\t\tPress any key to continue.....";
            return;
        }
    }
}

void updateLaptop(string laptop[][10], int &laptopCount)
{
    if (laptopCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Data Found\n\t\t\t\t\t\t-------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tPlease add Laptop Stock.\n\n\t\tPress any key to continue...";
        getch();
        return;
    }

    while (true)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tSearch Laptop to update stock:\n\t\t-----------------------------";
        cout << endl
             << endl
             << endl;

        SetConsoleTextAttribute(hConsole, 14);
        cout << "\t\t\tManufacturer: ";
        cout << "\n\n\t\t\t      Series: ";
        cout << "\n\n\t\t\t       Model: ";
        SetConsoleTextAttribute(hConsole, 15);

        // cin.ignore();
        string manufacturer, series, model;
        cursor(1);
        gotoxy(39, 12);
        gotoxy(39, 12);
        getline(cin, manufacturer);
        gotoxy(39, 14);
        getline(cin, series);
        gotoxy(39, 16);
        getline(cin, model);
        Sleep(300);
        cursor(0);

        int index = checkLaptop(manufacturer, series, model, laptop, laptopCount);

        if (index == -1)
        {
            printHeader();
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n\t\t\t\t\t\tLaptop Not Found\n\t\t\t\t\t\t---------------";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "\n\n\t\tEnter Correct Laptop Details.\n\n\t\tPress any key to continue...";

            getch();

            printHeader();
            int arrowLocation = 1, input;
            int option = 0;

            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t\tChoose any option:\n\t\t=================";
            cout << endl
                 << endl;

            printArrow(11);

            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t1. ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "Try Again";
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n\n\t2. ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "Go Back";

            while (true)
            {
                input = getch();

                if (input == '1' || input == '2')
                    option = input - '0';

                else if (input == 13)
                {
                    option = arrowLocation;
                }

                else if (input == 224)
                {
                    arrowLocation = moveArrow(input, arrowLocation, 11, 2);
                }

                if (option > 0 && option <= 2)
                {
                    if (option == 1)
                        break;
                    if (option == 2)
                        return;
                }
            }
        }

        else
        {
            cursor(1);
            SetConsoleTextAttribute(hConsole, 11);
            cout << "\n\n\t\tEnter new data:\n\t\t---------------";

            SetConsoleTextAttribute(hConsole, 14);
            cout << "\n\n\t\t\t   New Price: ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "$";
            SetConsoleTextAttribute(hConsole, 14);
            cout << "\n\n\t\t\t   New Stock: ";

            SetConsoleTextAttribute(hConsole, 15);

            gotoxy(39, 22);
            getline(cin, laptop[index][7]);
            gotoxy(39, 24);
            getline(cin, laptop[index][8]);

            storeLaptopsData(laptop, laptopCount);

            Sleep(500);
            cursor(0);
            printHeader();

            SetConsoleTextAttribute(hConsole, 10);
            cout << "\t\t\t\t\t\tStock Updated\n\t\t\t\t\t\t-------------\n";
            Sleep(500);
            SetConsoleTextAttribute(hConsole, 15);
            cout << "\n\n\t\tPress any key to continue.....";
            getch();
            return;
        }
    }
}

void displayLaptops(string laptop[][10], int &laptopCount)
{
    if (laptopCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Laptops Available\n\t\t\t\t\t\t--------------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tWait for new stock to come.\n\n\t\tPress any key to continue...";
    }
    else
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tAvailable Laptops:\n\t\t-----------------";
        cout << endl
             << endl;

        SetConsoleTextAttribute(hConsole, 10);
        cout << "  " << setw(12) << left << "SrNo." << setw(30) << left << "Model" << setw(12) << left << "Price($)" << setw(10) << left << "Size" << setw(15) << left << "CPU" << setw(10) << left << "RAM" << setw(15) << left << "Storage" << endl
             << endl;
        SetConsoleTextAttribute(hConsole, 15);
        string name;
        for (int x = 0; x < laptopCount; x++)
        {
            name = laptop[x][0] + "  " + laptop[x][1] + "  " + laptop[x][2];
            cout << "  " << setw(12) << left << x + 1 << setw(30) << left << name << setw(12) << left << laptop[x][7] << setw(10) << left << laptop[x][3] << setw(15) << left << laptop[x][4] << setw(10) << left << laptop[x][5] << setw(15) << left << laptop[x][6] << endl
                 << endl;
        }
        cout << endl;
        Sleep(1000);
        cout << "\n\t\t \033[2mPress any key to continue...";
    }

    getch();
}

void displayLaptopsStock(string laptop[][10], int &laptopCount)
{

    if (laptopCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Data Found\n\t\t\t\t\t\t-------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tPlease add Laptop Stock.\n\n\t\tPress any key to continue...";
    }
    else
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tLaptops Stock:\n\t\t-------------";
        cout << endl
             << endl;

        SetConsoleTextAttribute(hConsole, 10);
        cout << "  " << setw(10) << left << "SrNo." << setw(30) << left << "Name" << setw(15) << left << "Price ($)" << setw(10) << left << "Stock" << endl
             << endl;
        SetConsoleTextAttribute(hConsole, 15);
        string name;
        for (int x = 0; x < laptopCount; x++)
        {
            name = laptop[x][0] + "  " + laptop[x][1] + "  " + laptop[x][2];
            cout << "  " << setw(10) << left << x + 1 << setw(30) << left << name << setw(15) << left << laptop[x][7] << setw(10) << left << laptop[x][8] << endl
                 << endl;
        }
        cout << endl;
        Sleep(1000);
        cout << "\n\t\t \033[2mPress any key to continue...";
    }

    getch();
}

void displayLaptopsCategories(string laptop[][10], int &laptopCount)
{
    if (laptopCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Laptops Available\n\t\t\t\t\t\t--------------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tWait for new stock to come.\n\n\t\tPress any key to continue...";
    }
    else
    {
        while (true)
        {
            printHeader();
            SetConsoleTextAttribute(hConsole, 11);
            cout << "\t\tSelect Manufacturer to Display:\n\t\t------------------------------";
            cout << endl
                 << endl
                 << endl;

            SetConsoleTextAttribute(hConsole, 14);
            cout << "\t\t\tManufacturer: ";
            SetConsoleTextAttribute(hConsole, 15);

            // cin.ignore();
            string manufacturer;
            cursor(1);
            gotoxy(39, 12);
            gotoxy(39, 12);
            getline(cin, manufacturer);
            Sleep(300);
            cursor(0);

            int index = checkLaptopManu(manufacturer, laptop, laptopCount);

            if (index == -1)
            {
                printHeader();
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\n\t\t\t\t\t\tLaptop Not Found\n\t\t\t\t\t\t---------------";
                SetConsoleTextAttribute(hConsole, 15);
                cout << "\n\n\t\tEnter Correct Laptop Details.\n\n\t\tPress any key to continue...";

                getch();

                printHeader();
                int arrowLocation = 1, input;
                int option = 0;

                SetConsoleTextAttribute(hConsole, 12);
                cout << "\t\tChoose any option:\n\t\t=================";
                cout << endl
                     << endl;

                printArrow(11);

                SetConsoleTextAttribute(hConsole, 12);
                cout << "\t1. ";
                SetConsoleTextAttribute(hConsole, 15);
                cout << "Try Again";
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\n\n\t2. ";
                SetConsoleTextAttribute(hConsole, 15);
                cout << "Go Back";

                while (true)
                {
                    input = getch();

                    if (input == '1' || input == '2')
                        option = input - '0';

                    else if (input == 13)
                    {
                        option = arrowLocation;
                    }

                    else if (input == 224)
                    {
                        arrowLocation = moveArrow(input, arrowLocation, 11, 2);
                    }

                    if (option > 0 && option <= 2)
                    {
                        if (option == 1)
                            break;
                        if (option == 2)
                            return;
                    }
                }
            }

            else
            {
                printHeader();
                SetConsoleTextAttribute(hConsole, 11);
                cout << "\t\tAvailable Laptops:\n\t\t-----------------";
                cout << endl
                     << endl;

                SetConsoleTextAttribute(hConsole, 10);
                cout << "  " << setw(12) << left << "SrNo." << setw(30) << left << "Model" << setw(12) << left << "Price($)" << setw(10) << left << "Size" << setw(15) << left << "CPU" << setw(10) << left << "RAM" << setw(15) << left << "Storage" << endl
                     << endl;
                SetConsoleTextAttribute(hConsole, 15);
                string name;
                int index =1;
                for (int x = 0; x < laptopCount; x++)
                {
                    if(laptop[x][0]==manufacturer)
                    {
                    name = laptop[x][0] + "  " + laptop[x][1] + "  " + laptop[x][2];
                    cout << "  " << setw(12) << left << index << setw(30) << left << name << setw(12) << left << laptop[x][7] << setw(10) << left << laptop[x][3] << setw(15) << left << laptop[x][4] << setw(10) << left << laptop[x][5] << setw(15) << left << laptop[x][6] << endl
                         << endl;
                    index++;
                    }
                }
                cout << endl;
                Sleep(1000);
                cout << "\n\t\t \033[2mPress any key to continue...";
                getch();
                return;
            }
        }
    }
}

int checkLaptop(string manufacturer, string series, string model, string laptop[][10], int &laptopCount)
{
    for (int i = 0; i < laptopCount; i++)
    {
        if (laptop[i][0] == manufacturer && laptop[i][1] == series && laptop[i][2] == model)
            return i;
    }
    return -1;
}

int checkLaptopManu(string manufacturer, string laptop[][10], int &laptopCount)
{
    for (int i = 0; i < laptopCount; i++)
    {
        if (laptop[i][0] == manufacturer)
            return i;
    }
    return -1;
}

//                                                    <------(  Additinal Features  )------>

void makeAnnouncement(string announcement[5], int &announcementCount)
{
    printHeader();

    SetConsoleTextAttribute(hConsole, 11);
    cout << "\t\tMake a new Announcement:\n\t\t------------------------";
    cout << endl
         << endl;

    SetConsoleTextAttribute(hConsole, 14);
    Sleep(500);
    cout << "\tStart Typing:\n\n\t\t";
    Sleep(200);
    SetConsoleTextAttribute(hConsole, 15);
    cin.ignore();

    cursor(1);
    getline(cin, announcement[announcementCount]);
    announcementCount++;
    storeAnnouncementsData(announcement, announcementCount);

    Sleep(500);
    cursor(0);

    printHeader();

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\t\t\t\t\t\tAnnouncement Added\n\t\t\t\t\t\t------------------\n";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "\n\n\t\tPress any key to continue.....";
    getch();
}

void viewAnnouncements(string announcement[5], int &announcementCount)
{
    printHeader();
    if (announcementCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Announcement Found\n\t\t\t\t\t\t---------------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tCurrently, there's no Announcement\n\n\t\tPress any key to continue...";
    }

    else
    {
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tAnnouncements:\n\t\t--------------\n";
        SetConsoleTextAttribute(hConsole, 15);

        for (int i = 0; i < announcementCount; i++)
        {
            SetConsoleTextAttribute(hConsole, 14);
            cout << "\t\t\t\t\t\t( " << i + 1 << " )";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "\n\n\t\t\t" << announcement[i] << endl
                 << endl;
        }
        cout << endl
             << endl;
        Sleep(1000);
        cout << "\n\t\t \033[2mPress any key to close...";
    }
    getch();
}

void placeOrder(string laptop[][10], string order[][4], int &laptopCount, int &ordersCount)
{
    int quantity = 0;

    if (laptopCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Laptop Found\n\t\t\t\t\t\t---------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tPlease wait for new stock.\n\n\t\tPress any key to continue...";

        getch();
        return;
    }

    cin.ignore();
    printHeader();
    SetConsoleTextAttribute(hConsole, 13);
    cout << "\t\tEnter Laptop to Purchase:\n\t\t-------------------------";
    cout << endl
         << endl
         << endl;

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\t\t\tManufacturer: ";
    cout << "\n\n\t\t\t      Series: ";
    cout << "\n\n\t\t\t       Model: ";
    cout << "\n\n\t\t\t    Quantity:";
    SetConsoleTextAttribute(hConsole, 15);

    cursor(1);
    string manufacturer, series, model;
    gotoxy(39, 12);
    getline(cin, manufacturer);
    gotoxy(39, 14);
    getline(cin, series);
    gotoxy(39, 16);
    getline(cin, model);
    gotoxy(39, 18);
    cin >> quantity;
    cin.ignore();
    cursor(0);

    int index = checkLaptop(manufacturer, series, model, laptop, laptopCount);

    if (index == -1)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tLaptop Not Found\n\t\t\t\t\t\t----------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tEnter Correct Laptop Details.\n\n\t\tPress any key to continue...";

        getch();

        printHeader();
        int arrowLocation = 1, input;
        int option = 0;

        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\tChoose any option:\n\t\t=================";
        cout << endl
             << endl;

        printArrow(11);

        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t1. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Try Again";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n\n\t2. ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Go Back";

        while (true)
        {
            input = getch();

            if (input == '1' || input == '2')
                option = input - '0';

            else if (input == 13)
            {
                option = arrowLocation;
            }

            else if (input == 224)
            {
                arrowLocation = moveArrow(input, arrowLocation, 11, 2);
            }

            if (option > 0 && option <= 2)
            {
                if (option == 1)
                    break;
                else if (option == 2)
                    return;
            }
        }
    }

    else
    {
        order[ordersCount][0] = currentUser;
        order[ordersCount][1] = laptop[index][0] + " " + laptop[index][1] + " " + laptop[index][2];
        order[ordersCount][2] = laptop[index][7];
        order[ordersCount][3] = to_string(quantity);
        ordersCount++;
        storeOrdersData(order, ordersCount);

        Sleep(500);
        printHeader();

        SetConsoleTextAttribute(hConsole, 10);
        cout << "\t\t\t\t\t\tLaptop Added to Cart\n\t\t\t\t\t\t--------------------\n";
        Sleep(500);
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tPress any key to continue.....";
    }

    getch();
}

void yourOrders(string laptop[][10], string order[][4], int &laptopCount, int &ordersCount)
{

    if (ordersCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Orders Found\n\t\t\t\t\t\t---------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tPlease Place an order.\n\n\t\tPress any key to continue...";
    }
    else
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tYour Orders:\n\t\t-------------";
        cout << endl
             << endl;

        SetConsoleTextAttribute(hConsole, 10);
        cout << "  " << setw(10) << left << "SrNo." << setw(30) << left << "Model" << setw(15) << left << "Price ($)" << setw(10) << left << "Quantity" << endl
             << endl;
        SetConsoleTextAttribute(hConsole, 15);
        int idx = 1;
        for (int x = 0; x < ordersCount; x++)
        {
            if (order[x][0] == currentUser)
            {
                cout << "  " << setw(10) << left << idx << setw(30) << left << order[x][1] << setw(15) << left << order[x][2] << setw(10) << left << order[x][3] << endl
                     << endl;
                idx++;
            }
        }
        cout << endl;
        Sleep(1000);
        cout << "\n\t\t \033[2mPress any key to continue...";
    }

    getch();
}

void orders(string laptop[][10], string order[][4], int &laptopCount, int &ordersCount)
{

    if (ordersCount == 0)
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\tNo Orders Found\n\t\t\t\t\t\t---------------";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "\n\n\t\tWait for customers to place order.\n\n\t\tPress any key to continue...";
    }
    else
    {
        printHeader();
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\tOrders:\n\t\t-------";
        cout << endl
             << endl;

        SetConsoleTextAttribute(hConsole, 10);
        cout << "  " << setw(10) << left << "SrNo." << setw(30) << left << "Customer:" << setw(30) << left << "Model" << setw(15) << left << "Price ($)" << setw(10) << left << "Quantity" << endl
             << endl;
        SetConsoleTextAttribute(hConsole, 15);
        for (int x = 0; x < ordersCount; x++)
        {
            cout << "  " << setw(10) << left << x + 1 << setw(30) << left << order[x][0] << setw(30) << left << order[x][1] << setw(15) << left << order[x][2] << setw(10) << left << order[x][3] << endl
                 << endl;
        }
        cout << endl;
        Sleep(1000);
        cout << "\n\t\t \033[2mPress any key to continue...";
    }

    getch();
}

void stockWorth(string laptop[][10], int &laptopCount)
{
    printHeader();

    int totalStockWorth = 0;

    for (int i = 0; i < laptopCount; i++)
    {
        totalStockWorth = totalStockWorth + (stoi(laptop[i][7]) * stoi(laptop[i][8]));
    }

    cout << "\n\n\t\tThe total stock worth is: ";
    SetConsoleTextAttribute(hConsole, 10);
    cout << "$" << totalStockWorth;
    SetConsoleTextAttribute(hConsole, 15);

    cout << endl;
    Sleep(1000);
    cout << "\n\t\t \033[2mPress any key to continue...";
    getch();
}

//                                                     <------(  Constant Functins  )------>

bool validation(const string &str, string type)
{
    if (type == "null" || type == "Null")
    {
        if (str.empty())
            return true;
        else
            return false;
    }
    else if (type == "numberonly" || type == "numberOnly" || type == "NumberOnly")
    {
        for (char c : str)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }
    else if (type == "textonly" || type == "textOnly" || type == "TextOnly")
    {
        for (char c : str)
        {
            if (!isalpha(c))
            {
                return false;
            }
        }
        return true;
    }
    else if (type == "alphanumeric" || type == "alphaNumeric" || type == "AlphaNumeric")
    {
        bool hasAlpha = false;
        bool hasDigit = false;

        for (char c : str)
        {
            if (isalpha(c))
            {
                hasAlpha = true;
            }
            if (isdigit(c))
            {
                hasDigit = true;
            }

            if (hasAlpha && hasDigit)
            {
                return true;
            }
        }

        return false;
    }
    else if (type == "nospace" || type == "noSpace" || type == "NoSpace")
    {
        for (char c : str)
        {
            if (c == ' ')
            {
                return false;
            }
        }
        return true;
    }
    else if (type == "noComma" || type == "nocomma" || type == "NoComma")
    {
        for (char c : str)
        {
            if (c == ',')
            {
                return false;
            }
        }
        return true;
    }
    else
        cout << "Validation Erroe";
}

void displayUsers(string user[][3], int &usersCount)
{

    printHeader();
    SetConsoleTextAttribute(hConsole, 11);
    cout << "\t\tUsers of Software:\n\t\t-----------------";
    cout << endl
         << endl;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "  " << setw(10) << left << "SrNo." << setw(30) << left << "Username" << setw(15) << left << "Password" << setw(10) << left << "Role" << endl
         << endl;
    SetConsoleTextAttribute(hConsole, 15);
    string name;
    for (int x = 0; x < usersCount; x++)
    {
        cout << "  " << setw(10) << left << x + 1 << setw(30) << left << user[x][0] << setw(15) << left << user[x][1] << setw(10) << left << user[x][2] << endl
             << endl;
    }
    cout << endl;
    Sleep(1000);
    cout << "\n\t\t \033[2mPress any key to continue...";

    getch();
}

void displayEmployees(string user[][3], int &usersCount)
{

    printHeader();
    SetConsoleTextAttribute(hConsole, 11);
    cout << "\t\tEmployees of Store:\n\t\t--------------------";
    cout << endl
         << endl;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "  " << setw(10) << left << "SrNo." << setw(30) << left << "Username" << setw(15) << left << "Password" << setw(10) << left << "Role" << endl
         << endl;
    SetConsoleTextAttribute(hConsole, 15);
    string name;
    int idx = 1;
    for (int x = 0; x < usersCount; x++)
    {
        if (user[x][2] == "Employee")
        {
            cout << "  " << setw(10) << left << idx + 1 << setw(30) << left << user[x][0] << setw(15) << left << "******" << setw(10) << left << user[x][2] << endl
                 << endl;
            idx++;
        }
    }

    if (idx == 1)
        cout << "\t\t\tNo Employee Found.\n";

    cout << endl;
    Sleep(1000);
    cout << "\n\t\t \033[2mPress any key to continue...";

    getch();
}

int moveArrow(int input, int arrowLocation, int top, int options)
{
    input = getch();
    int bottom = top + (options * 2) - 2;

    if (input == 72) // up
    {
        if (arrowLocation > 1)
        {
            arrowLocation--;
            eraseArrow();
            printArrow(arrowy - 2);
        }
        else
        {
            arrowLocation = options;
            eraseArrow();
            printArrow(bottom);
        }
    }

    else if (input == 80)
    {
        if (arrowLocation < options)
        {
            arrowLocation++;
            eraseArrow();
            printArrow(arrowy + 2);
        }
        else
        {
            arrowLocation = 1;
            eraseArrow();
            printArrow(top);
        }
    }

    return arrowLocation;
}

void printArrow(int y)
{

    arrowy = y;
    SetConsoleTextAttribute(hConsole, 10);
    gotoxy(3, arrowy);
    cout << "-->\r";
    SetConsoleTextAttribute(hConsole, 15);
}

void eraseArrow()
{
    SetConsoleTextAttribute(hConsole, 10);
    gotoxy(3, arrowy);
    cout << "   ";
    SetConsoleTextAttribute(hConsole, 15);
}

void printHeader()
{
    system("cls");
    int a = 14, b = 12, c = 14;
    SetConsoleTextAttribute(hConsole, a);
    cout << "                     _             ";
    SetConsoleTextAttribute(hConsole, b);
    cout << "__        __                   ";
    SetConsoleTextAttribute(hConsole, c);
    cout << "____  _";
    cout << endl;
    SetConsoleTextAttribute(hConsole, a);
    cout << "                    | |    __ _ _ _";
    SetConsoleTextAttribute(hConsole, b);
    cout << "\\ \\      / /_ _ _ __ ___      ";
    SetConsoleTextAttribute(hConsole, c);
    cout << "/ ___|| |_ ___  _ __ ___";
    cout << endl;
    SetConsoleTextAttribute(hConsole, a);
    cout << "                    | |   / _` | '_ ";
    SetConsoleTextAttribute(hConsole, b);
    cout << "\\ \\ /\\ / / _` | '__/ _ \\     ";
    SetConsoleTextAttribute(hConsole, c);
    cout << "\\___ \\| __/ _ \\| '__/ _ \\";
    cout << endl;
    SetConsoleTextAttribute(hConsole, a);
    cout << "                    | |__| (_| | |_) ";
    SetConsoleTextAttribute(hConsole, b);
    cout << "\\ V  V / (_| | | |  __/      ";
    SetConsoleTextAttribute(hConsole, c);
    cout << "___) | || (_) | | |  __/";
    cout << endl;
    SetConsoleTextAttribute(hConsole, a);
    cout << "                    |_____\\__,_| .__/ ";
    SetConsoleTextAttribute(hConsole, b);
    cout << "\\_/\\_/ \\__,_|_|  \\___|     ";
    SetConsoleTextAttribute(hConsole, c);
    cout << "|____/ \\__\\___/|_|  \\___|";
    cout << endl;
    SetConsoleTextAttribute(hConsole, a);
    cout << "                               |_|";
    cout << endl
         << endl
         << endl;
    SetConsoleTextAttribute(hConsole, 15);
    Sleep(200);

    // cout << R"(
    //                      _             __        __                   ____  _
    //                     | |    __ _ _ _\ \      / /_ _ _ __ ___      / ___|| |_ ___  _ __ ___
    //                     | |   / _` | '_ \ \ /\ / / _` | '__/ _ \     \___ \| __/ _ \| '__/ _ \
    //                     | |__| (_| | |_) \ V  V / (_| | | |  __/      ___) | || (_) | | |  __/
    //                     |_____\__,_| .__/ \_/\_/ \__,_|_|  \___|     |____/ \__\___/|_|  \___|
    //                                |_|
    // )";
}

void welcomeScreen()
{
    printHeader();

    cout << "\t\t\t\t\tWelcome to the \033[1mLapWare Store\033[0m\n\t\t\t\t\t<==========================>\n\n\t\t\t\t\033[3;92m      .Where Quality meets Performance.\033[0m\n";

    char solidBlock = 219;  // █
    char shadedBlock = 177; // ▒

    Sleep(1000);
    cout << "\n\n\n\t\t\tLoading...\n\n\t\t\t\t   \033[34m";
    Sleep(500);
    for (int i = 1; i <= 40; i++)
        cout << shadedBlock;
    cout << "\r\t\t\t\t   \033[94m";
    Sleep(1000);
    for (int i = 1; i <= 40; i++)
    {
        cout << solidBlock;
        Sleep(100);
        if (i == 15)
            Sleep(800);
        if (i == 30)
            Sleep(1300);
    }
    Sleep(700);
}

void contactAdmin()
{
    printHeader();
    cout << "\n\n\n\t\t\tContact Admin to get an account.";
    cout << endl;
    Sleep(1000);
    cout << "\n\t\t \033[2mPress any key to continue...";
    getch();
}

void dummyData(string user[][3], string laptop[][10], int &usersCount, int &laptopCount)
{
    user[0][0] = "admin";
    user[0][1] = "admin";
    user[0][2] = "Admin";
    usersCount++;

    // laptop[0][0] = "Dell";
    // laptop[0][1] = "XPS";
    // laptop[0][2] = "9550";
    // laptop[0][3] = "15";
    // laptop[0][4] = "i7 6th";
    // laptop[0][5] = "16";
    // laptop[0][6] = "512";
    // laptop[0][7] = "500";
    // laptop[0][8] = "5";
    // laptopCount++;
}

void comingSoon()
{
    printHeader();

    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n\n\t\t\t\t\t\tComing Soon\n\t\t\t\t\t\t-----------";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "\n\n\t\tThis Feature is Coming Soon.\n\n\t\tPress any key to continue...";
    getch();
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void cursor(bool state)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    if (state == true)
    {
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = true; // Set the cursor visibility to false
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }
    else
    {
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = false; // Set the cursor visibility to false
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }
}