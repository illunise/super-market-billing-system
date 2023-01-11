/*
    Creator :- Manish Kushwaha (@illunise)
    Created At :- 11 Jan, 2023
    -------- Social Media Links ----------
    GitHub :- https://github.com/illunise
    Linkedin :- https://www.linkedin.com/in/illunise
    Instagram :- https://www.instagram.com/illunise
    Project Link :- https://github.com/illunise/super-market-billing-system
    
*/



#include <iostream>
#include <unistd.h>
// #include <windows.h> //Enable it for windows
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

// Function Definition
void welcomeMsg();
void clearScr();
void endScr();

class ShoppingMall
{
};

// Administrator Class with ShoppingMall Class inherit with public
class Administrator : public ShoppingMall
{

public:
    void adminWelcomeMsg()
    {
        clearScr();
        // Welcome Screen Menu for Admin
        cout << "-----------------------------------" << endl;
        cout << "    Login Successful As Admin\t" << endl;
        cout << "-----------------------------------" << endl;
        cout << "|       1. Add The Product           |" << endl;
        cout << "|       2. Modify The Product        |" << endl;
        cout << "|       3. Delete The Product        |" << endl;
        cout << "|       4. Back To Main Menu         |" << endl;
        cout << "|       5. Exit                      |" << endl;
        cout << "-----------------------------------" << endl;

        int aOption;
        cout << "Enter Your Option : ";
        cin >> aOption;

        switch (aOption)
        {
        case 1:
            // if entered option is 1 then execute the addProduct function
            addProduct();
            break;
        case 2:
            // if entered option is 2 then execute the modifyProduct function
            modifyProduct();
            break;
        case 3:
            // if entered option is 3 then execute the deleteProduct function
            deleteProduct();
            break;
        case 4:
            // if entered option is 4 then back to the main menu
            ::welcomeMsg();
            break;
        case 5:
            // if entered option is 5 then show them the credit screen and exit from program
            endScr();
            exit(0);
            break;
        default:
            // if entered option is other than above options then back to the back to the start of this function
            cout << "Enter Proper Options" << endl;
            welcomeMsg();
            break;
        }
    }

    // will add the product in the database
    void addProduct()
    {
        clearScr();

        try
        {
            string pName, pID, pPrice, pQty, pDis;
            cout << "Adding Product..." << endl;

            cout << "Enter Product ID : ";
            cin >> pID;

            cout << "Enter Product Name : ";
            cin >> pName;

            cout << "Enter Product Price : ";
            cin >> pPrice;

            cout << "Enter Product Quantity : ";
            cin >> pQty;

            cout << "Enter Product Discount(%) : ";
            cin >> pDis;

            ofstream database;
            database.open("database.txt", ios::out | ios::app); // open the file in write and append mode

            if (!database.is_open())
            {
                cerr << "Error opening file" << endl;
            }
            // add the variables to the
            database << " " << pID << " " << pName << " " << pPrice << " " << pQty << " " << pDis << endl;

            // close the file
            database.close();

            cout << "Product Added Succesdully" << endl;

            string inputInvalid;
            cout << "Enter Any Number to Continue : ";
            cin >> inputInvalid;

            adminWelcomeMsg();
        }
        catch (const invalid_argument &e)
        {
            cerr << e.what() << endl;
            cout << "We will redirect to the main menu in 3 seconds." << endl;
            sleep(3); // sleep for 3 seconds
            adminWelcomeMsg();
        }
    }

    // will modify the product in the database
    void modifyProduct()
    {
        string modifyID, prID, prQty, prDis, prName, prPrice;
        ifstream readFile("database.txt");
        ofstream modifyFile("database1.txt");

        cout << "Enter Product ID to Modify : ";
        cin >> modifyID;

        if (!readFile.is_open())
        {
            cerr << "Error opening file" << endl;
        }

        int isAvailable = 0;

        while (readFile >> prID >> prName >> prPrice >> prQty >> prDis)
        {

            // Check if the ID of the record matches the ID we are looking for
            // if available then ask the user about new data and replace it
            // if not available then add the data as it is to the database1.txt file
            if (modifyID == prID)
            {
                isAvailable = 1;
                string newID, newName, newPrice, newQty, newDis;
                cout << "Enter New Product ID : ";
                cin >> newID;
                cout << "Enter New Product Name : ";
                cin >> newName;
                cout << "Enter New Product Price : ";
                cin >> newPrice;
                cout << "Enter New Product Quantity : ";
                cin >> newQty;
                cout << "Enter New Discount(%) : ";
                cin >> newDis;

                modifyFile << newID << " " << newName << " " << newPrice << " " << newQty << " " << newDis << endl;
            }
            else
            {
                modifyFile << prID << " " << prName << " " << prPrice << " " << prQty << " " << prDis << endl;
            }
        }

        readFile.close();
        modifyFile.close();

        fstream srcFile, dstFile;

        srcFile.open("database1.txt", ios::in);
        dstFile.open("database.txt", ios::out);

        // copy the content from database1.txt file and
        // paste it to database.txt file
        dstFile << srcFile.rdbuf();

        srcFile.close();
        dstFile.close();

        // after loop is entered product id is available then change it to file
        // adn execute else statement otherwise execute if statement
        if (isAvailable == 0)
        {
            cout << "Enter Product Id Not Found!" << endl;
        }
        else
        {
            cout << "Entry Modified Successfully :)" << endl;
        }

        cout << "We will redirect to the main menu in 3 seconds." << endl;
        sleep(3); // hold the screen for 3 seconds
        adminWelcomeMsg();
    }

    // will delete the product from the database
    void deleteProduct()
    {

        string modifyID, prID, prQty, prDis, prName, prPrice;
        ifstream readFile("database.txt");
        ofstream modifyFile("database1.txt");

        cout << "Enter Product ID to Modify : ";
        cin >> modifyID;

        if (!readFile.is_open())
        {
            cerr << "Error opening file" << endl;
        }

        int isAvailable = 0;

        while (readFile >> prID >> prName >> prPrice >> prQty >> prDis)
        {

            // Check if the ID of the record matches the ID we are looking for
            // if available then don't add that item into file otherwise add the item
            if (modifyID == prID)
            {
                isAvailable = 1;
            }
            else
            {
                modifyFile << prID << " " << prName << " " << prPrice << " " << prQty << " " << prDis << endl;
            }
        }

        readFile.close();
        modifyFile.close();

        fstream srcFile, dstFile;

        srcFile.open("database1.txt", ios::in);
        dstFile.open("database.txt", ios::out);

        dstFile << srcFile.rdbuf();

        srcFile.close();
        dstFile.close();

        if (isAvailable == 0)
        {
            cout << "Enter Product Id Not Found!" << endl;
        }
        else
        {
            cout << "Entry Modified Successfully :)" << endl;
        }

        cout << "We will redirect to the main menu in 3 seconds." << endl;
        sleep(3);
        adminWelcomeMsg();
    }
};

class Buyer : public ShoppingMall
{

public:
    // will show the list to the customer and execute the receipt
    void buyerWelcomeMsg()
    {
        clearScr();
        string pID, pName, pPrice, pQty, pDis;
        vector<int> arr;
        cout << "------------------------ Menu --------------------" << endl;
        cout << "| PID\t|   Name\tQty\tPrice\tDiscount |" << endl;
        cout << "--------------------------------------------------" << endl;
        fstream menuFile;
        menuFile.open("database.txt", ios::in);

        // Go through the loop and print the items of file
        while (menuFile >> pID >> pName >> pPrice >> pQty >> pDis)
        {
            cout << "| " << pID << "\t|   " << pName << "\t" << pQty << "\t" << pPrice << "\t" << pDis << "%"
                 << "\t |" << endl;
            arr.push_back(stoi(pID));
        }

        cout << "--------------------------------------------------" << endl
             << endl;

        int items = 0;
        vector<string> choices;
        while (true)
        {
            string choice;
            cout << "Enter Product Id : ";
            cin >> choice;

            // if the entered product id is available in file then ask for
            // other choice otherwise execute the else statement
            if (find(arr.begin(), arr.end(), stoi(choice)) != arr.end())
            {
                choices.push_back(choice);

                items += 1;
                string want;
                cout << "Want to add another item? (y/n) : ";
                cin >> want;
                if (want == "y" | want == "Y")
                {
                    continue;
                }
                else
                {
                    cout << "Thanks for Shopping!" << endl;
                    break;
                }
            }
            else
            {
                cout << "Invalid Product ID!" << endl;

                cout << "We will redirect to the main menu in 3 seconds." << endl;
                sleep(3);
                buyerWelcomeMsg();
            }
        }

        if (items != 0)
        {
            clearScr();
            time_t t = time(nullptr);
            tm tm = *localtime(&t);
            int total_Amt = 0;
            int N = 1000;


            cout << " ------------------------------------------------------- " << endl;
            cout << "| \t\t         D-MART   \t\t\t|" << endl;
            cout << "| \t\t      ************\t\t\t|" << endl;
            cout << "| \t\t      Cash Receipt\t\t\t|" << endl;
            cout << "|\t\t\t\t\t\t\t|"<<endl;
            cout << "| Date : " << tm.tm_mday << "/" << tm.tm_mon + 1 << "/" << tm.tm_year + 1900 << "\t\t   Bill No. : " << rand() % N << "\t|" << endl;
            cout << "| Cashier : Manish Kushwaha" << "\t\t\t\t|"<< endl;
            cout << "| ***************************************************** |" << endl;
            cout << "| SrNo\tName\t\tQty\tPrice\tDsct\tTotal\t|" << endl;
            cout << "| ----------------------------------------------------- |" << endl;
            for (int i = 0; i < items; i++)
            {
                ifstream readFile("database.txt");
                ofstream modifyFile("database1.txt");
                string prID, prName, prPrice, prQty, prDis;

                while (readFile >> prID >> prName >> prPrice >> prQty >> prDis)
                {

                    // Check if the ID of the record matches the ID we are looking for
                    if (choices.at(i) == prID)
                    {
                        int discount, total;
                        discount = (stoi(prDis) * stoi(prPrice)) / 100;
                        total = stoi(prPrice) - discount;
                        total_Amt += total;
                        cout << "|   " << i + 1 << "\t" << prName << "\t\t1\t" << prPrice << "\t" << discount << "\t" << total << "\t|" << endl;
                        modifyFile << prID << " " << prName << " " << prPrice << " " << stoi(prQty) - 1 << " " << prDis << endl;
                    }
                    else
                    {
                        modifyFile << prID << " " << prName << " " << prPrice << " " << prQty << " " << prDis << endl;
                    }
                }

                readFile.close();
                modifyFile.close();
            }

            fstream srcFile, dstFile;

            srcFile.open("database1.txt", ios::in);
            dstFile.open("database.txt", ios::out);

            dstFile << srcFile.rdbuf();

            srcFile.close();
            dstFile.close();

            cout << "| ----------------------------------------------------- |" << endl;
            cout << "| \t\t\t\t\tTotal : " << total_Amt << "\t|" << endl;
            cout << "|\t\t\t\t\t\t\t|" << endl;
            cout << "| \t\tThank You Visit Again!\t\t\t|" << endl;

            cout << " ------------------------------------------------------- " << endl;
        }
        else
        {
            cout << "You Haven't Bought Anything!" << endl;
            cout << "We will redirect to the main menu in 3 seconds." << endl;
            sleep(3);
            welcomeMsg();
        }
    }
};

int main()
{

    // execute when the program starts
    welcomeMsg();

    return 0;
}

// Welcome Message to Show When Program Starts
void welcomeMsg()
{

    clearScr();
    cout << "-----------------------------------" << endl;
    cout << "\tWelcome To The D-Mart\t" << endl;
    cout << "-----------------------------------" << endl;
    cout << "|       1. Administrator           |" << endl;
    cout << "|       2. Buyer                   |" << endl;
    cout << "|       3. Exit                    |" << endl;
    cout << "-----------------------------------" << endl;

    int fOption;
    cout << endl
         << "Enter Your Role : ";
    cin >> fOption;

    if (fOption == 1)
    { // Execute When Enter Option is Administrator
        string username, password;
        cout << "Enter Username : ";
        cin >> username;
        cout << "Enter Password : ";
        cin >> password;
        if (username == "admin" && password == "admin")
        {
            Administrator admin;
            admin.adminWelcomeMsg();
        }
        else
        {
            cout << "Wrong Credentials!" << endl;
            cout << "We will redirect to the main menu in 3 seconds." << endl;
            sleep(3);
            welcomeMsg();
        }
    }
    else if (fOption == 2)
    { // Execute When Enter Option is Buyer
        // Your Code
        Buyer buyer;
        buyer.buyerWelcomeMsg();
    }
    else if (fOption == 3)
    { // Execute When Enter Option Exit
        endScr();
        exit(0);
    }
    else
    { // Execute When Enter Option is Invalid
        cout << "Entered Invalid Option!" << endl;
        cout << "We will redirect to the main menu in 3 seconds." << endl;
        sleep(3);
        welcomeMsg();
    }
}

void clearScr()
{
    // Clear the terminal
    system("clear");
}

void endScr()
{
    clearScr();
    cout << "-----------------------------------" << endl;
    cout << "   Thanks For Visiting D-Mart\t" << endl;
    cout << "-----------------------------------" << endl
         << endl;
    cout << "Copyright © 2022 by Manish Kushwaha. All rights reserved." << endl
         << endl;
    cout << "------------Useful Links------------" << endl;
    cout << "GitHub :- https://github.com/illunise" << endl;
    cout << "Linkedin :- https://www.linkedin.com/in/illunise" << endl;
    cout << "Instagram :- https://www.instagram.com/illunise" << endl;
}
