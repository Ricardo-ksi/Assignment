#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<cctype>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<fstream>

#include <thread>
#include <chrono>

using namespace std;

int countUser = 0;

int displayUsermenu();

void displayone(int count, string request);
void addrecord();
void updaterecord();
void deleterecord();
void displayrecord();

int Getage();
char Getgender();
string Getphone();
string Getemail();
string randomid();
int selectUser();

int sureint(string b);
int sureint(int limit, string b);
int surechoice();

void savedata();
void loaddata();

void searchrecord();
int searchuser(int choice);



void restaurantlogo() {
    cout << "  =================================" << endl;
    cout << "  =  RESTAURANT ORDERING SYSTEM   =" << endl;
    cout << "  =      MEOW MEOW RESTAURANT     =" << endl;
    cout << "  =================================" << endl;
}


struct userrecord {
    string username = "";
    char gender = ' ';
    int age = 0;
    string phone = "";
    string email = "";
    string address = "";
    string userid = "";
};
userrecord u[100];
//2
const int MAX_FOOD = 999;			//delcare that maximum food item is 999
const string MENU = "menu.txt";		//this is declare to save to a .txt file txt file is bacisly a place where text get store

struct menu {
    string id = "";
    string name = "";
    string type = "";
    double price = 0.0;
    bool isAvailable = true;
};

menu menulist[MAX_FOOD];
int foodcount = 0;

void displayServiceMenu();								//all is use to dedicate a space for it function
void addfood();			//to add food items
void updatefood();		//to update food example update price 
void deletefood();		//to deleted food items
void searchfood();		//search food items 
void displayAllfood();	//display all register food

void loadFood();				//load memory
void saveFood();					//save memory
int findFoodbyId(string id);		//find food by id
string toUpperString(string str);	//to change the lowercase character to upper case character

//student c
const int MAX_CUSTOMER = 100;
const int MAX_ORDER = 1000;
const int MAX_ITEM_PER_ORDER = 50;

struct Order {
    string customerID;
    int orderID = 0;
    int itemID[MAX_ITEM_PER_ORDER] = {};
    int quantity[MAX_ITEM_PER_ORDER] = {};
    int itemCount = 0;
    double totalAmount = 0.0;
    bool active = true;
    bool paid = false;
};

Order order[MAX_CUSTOMER][MAX_ORDER];
int orderCount[MAX_CUSTOMER] = { 0 };

void createOrder(int, string);
void cancelOrder(int);
void modifyOrder(int);
void searchOrder(int);
void displayOrderSummary(int);
void makePayment(int);

void saveOrders();
void loadOrders();
// end of student c

const int MAX_RECORDS = 100;

void initializeDefaultMenu();

//4
void userModule();
void serviceManagement();
void transactionModule(userrecord u[]);
void reportingModule();
void findUserReport(userrecord uList[], int userCount, Order order[][MAX_ORDER], int orderCount[]);
void generateSummary(Order order[][MAX_ORDER], int orderCount[], int maxCustomer);
void calculateStatistic(Order order[][MAX_ORDER], int orderCount[], int maxCustomer, int maxFood);
void sortRecords(Order order[MAX_CUSTOMER][MAX_ORDER], int orderCount[], int maxCustomer);
int choice;
int findUserIndex(int targetId, int idArray[], int size);
void displayUserReport(int index);
int idArray[6] = { 1001, 1002, 1003 };
int currentSize = 3;


int main() {

    initializeDefaultMenu();
    do {
        loaddata();
        loadFood();
        loadOrders();
        cout << "==================================================" << endl;
        cout << "||          RESTAURANT ORDERING SYSTEM          ||" << endl;
        cout << "==================================================" << endl << endl;
        cout << "1. User Management Module" << endl;
        cout << "2. Item Management" << endl;
        cout << "3. Ordering and Transaction Module" << endl;
        cout << "4. Reporting Module" << endl;
        cout << "5. Exit" << endl;
        cout << "==========================================" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            userModule();
            break;
        case 2:
            system("cls");
            serviceManagement();
            break;
        case 3:
            system("cls");
            transactionModule(u);
            break;
        case 4:
            system("cls");
            reportingModule();
            break;
        case 5:
            system("cls");
            cout << "\n\n******************  Exiting......  ******************\n\n";
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            cout << "\n\n*********************************************************************" << endl;
            cout << "****  Thank you for using the Restaurant Ordering System! (^o^)  ****\a" << endl;
            cout << "*********************************************************************\n\n";
            break;
        default:
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "Invalid! Please enter a number between 1 and 5." << endl;
        }
    } while (choice != 5);

    return 0;
}

void userModule() {
    srand((unsigned)time(0));
    loaddata();
    int runusermenu = 0;
    while (runusermenu == 0) {
        int usermenu = displayUsermenu();
        runusermenu = 1;

        switch (usermenu) {

        case 1:

            addrecord();
            runusermenu = 0;
            break;
        case 2:
            updaterecord();
            runusermenu = 0;
            break;
        case 3:
            deleterecord();
            runusermenu = 0;
            break;
        case 4:
            searchrecord();
            runusermenu = 0;
            break;
        case 5:
            displayrecord();
            runusermenu = 0;
            system("cls");

            break;
        case 6:
            break;
        default:cout << "wrong number please enter a valid number" << endl << "-----------------------------------" << endl;
            runusermenu = 0; break;

        }
    }

}

int displayUsermenu() {
    int action;
    string request = "please enter a number (1 - 6)";
    restaurantlogo();
    cout << "User module" << endl
        << "1.Add User" << endl
        << "2.Update User" << endl
        << "3.Delete Record" << endl
        << "4.Search Record" << endl
        << "5.Display all Record" << endl
        << "6.exit" << endl
        << request << endl;
    action = sureint(6, request);
    system("cls");
    return action;
}
void displayone(int count, string request) {
    cout << "------------------------------" << endl;
    cout << request << endl;
    cout << "Username:" << u[count].username << endl;
    cout << "UserId:" << u[count].userid << endl;
    cout << "Gender:" << u[count].gender << endl;
    cout << "Age:" << u[count].age << endl;
    cout << "Phone number:" << u[count].phone << endl;
    cout << "Email:" << u[count].email << endl;
    cout << "Home Address:" << u[count].address << endl;
    cout << "------------------------------" << endl;
}
void addrecord() {
    string action = "Successful Add User";
    cout << "Add User" << endl;
    cout << "Name:";
    getline(cin, u[countUser].username);
    u[countUser].gender = Getgender();
    u[countUser].age = Getage();
    u[countUser].phone = Getphone();
    u[countUser].email = Getemail();
    cout << "Home Address:";
    getline(cin, u[countUser].address);
    u[countUser].userid = randomid();

    system("cls");
    displayone(countUser, action);
    cout << "(notice)  Your User id is:" << u[countUser].userid << endl;
    countUser++;
    savedata();
}
void updaterecord() {
    if (countUser == 0) {
        cout << "No users available.\n";
        return;
    }
    int j = selectUser();
    string action1 = "Original information";
    string action2 = "Successful Update User";
    cout << "Update User" << endl;
    system("cls");
    displayone(j, action1);

    char confirm;
    cout << "Do you want to update this user? (Y/N): ";
    cin >> confirm;
    cin.ignore(10000, '\n');

    if (toupper(confirm) != 'Y') {
        cout << "\nUpdate cancelled. Returning to menu...\n";
        return;
    }

    cout << "Name:";
    getline(cin, u[j].username);
    u[j].gender = Getgender();
    u[j].age = Getage();
    u[j].phone = Getphone();
    u[j].email = Getemail();
    cout << "Home Address:";
    getline(cin, u[j].address);

    savedata();

    system("cls");
    displayone(j, action2);
}
void deleterecord() {
    if (countUser == 0) {
        cout << "No users available.\n";
        return;
    }
    int j = selectUser();
    string save = u[j].username;
    string suredelete = "";
    do {
        cout << "Do you sure want to delete user:" << save << endl
            << "(enter 0 for back \"sure\"for delete)" << endl;

        cin >> suredelete;
    } while (!(suredelete == "sure" || suredelete == "0"));

    if (suredelete == "sure") {
        for (int k = j; k < countUser - 1; k++) {
            u[k] = u[k + 1];
        }
        countUser--;
        savedata();
        system("cls");
        cout << "------------------------------" << endl;
        cout << "successful delete user:" << save << endl;
        cout << "------------------------------";
    }
}
void displayrecord() {
    ifstream infile("userData.txt");
    if (!infile.is_open()) {
        cout << "No records to display." << endl;
        return;
    }

    int count;
    infile >> count;
    infile.ignore(10000, '\n');

    if (count == 0) {
        cout << "No records to display." << endl;
        infile.close();
        return;
    }
    string ignore;
    int choice;
    string userinfo[100][5]; //0 is name 1 is phone 2 is email 3 is address 4 is userid
    int name = 0;
    int phone = 1;
    int email = 2;
    int address = 3;
    int id = 4;
    int age[100];
    char gender[100];
    int shownNumber = 0;
    string request = "please enter a number1-6";


    for (int k = 0; k < count; k++) {
        getline(infile, userinfo[shownNumber][name]);

        string genderline;
        getline(infile, genderline);
        gender[shownNumber] = genderline.empty() ? '\0' : genderline[0];

        string ageline;
        getline(infile, ageline);
        age[shownNumber] = ageline.empty() ? 0 : stoi(ageline);
        getline(infile, userinfo[shownNumber][phone]);
        getline(infile, userinfo[shownNumber][email]);
        getline(infile, userinfo[shownNumber][address]);
        getline(infile, userinfo[shownNumber][id]);

        shownNumber++;
    }
    infile.close();
    cout << "Display User" << endl
        << "1.Default:" << endl
        << "2.By Name:" << endl
        << "3.By User id:" << endl
        << "4.By Gender:" << endl
        << "5.By Age:" << endl
        << "6.Back" << endl
        << request << endl;
    choice = sureint(6, request);
    system("cls");

    switch (choice) {
    case 1: for (int z = 0;z < shownNumber;z++) {
        cout << "User Record:" << endl;
        cout << z + 1 << ". ";
        cout << "UserID:" << userinfo[z][id] << endl;
        cout << "Username:" << userinfo[z][name] << endl;
        cout << "Gender:" << gender[z] << endl;
        cout << "Age:" << age[z] << endl;
        cout << "Phone Number:" << userinfo[z][phone] << endl;
        cout << "Email:" << userinfo[z][email] << endl;
        cout << "Home Address:" << userinfo[z][address] << endl;
        cout << "------------------------------" << endl;
    }
          break;

    case 2: for (int z = 0;z < shownNumber;z++) {
        string minvalue = userinfo[z][name];
        int min = z;
        for (int j = z + 1;j < shownNumber;j++) {
            if (userinfo[j][name] < minvalue) {
                min = j;
                minvalue = userinfo[j][name];
            }
        }
        string savename = userinfo[z][name];
        userinfo[z][name] = userinfo[min][name];
        userinfo[min][name] = savename;


        cout << "User Record:" << endl;
        cout << z + 1 << ". ";
        cout << "Username:" << userinfo[z][name] << endl;

    }
          break;
    case 3:   for (int z = 0;z < shownNumber;z++) {
        string minvalue = userinfo[z][id];
        int min = z;
        for (int j = z + 1;j < shownNumber;j++) {
            if (userinfo[j][id] < minvalue) {
                min = j;
                minvalue = userinfo[j][id];
            }
        }
        string saveid = userinfo[z][id];
        userinfo[z][id] = userinfo[min][id];
        userinfo[min][id] = saveid;

        string savename = userinfo[z][name];
        userinfo[z][name] = userinfo[min][name];
        userinfo[min][name] = savename;


        cout << "User Record:" << endl;
        cout << z + 1 << ". ";
        cout << "Username:" << userinfo[z][name] << endl;
        cout << "UserID:" << userinfo[z][id] << endl;
    }
          break;
    case 4: for (int z = 0;z < shownNumber;z++) {
        char minvalue = gender[z];
        int min = z;
        for (int j = z + 1;j < shownNumber;j++) {
            if (gender[j] < minvalue) {
                min = j;
                minvalue = gender[j];
            }
        }
        char savegender = gender[z];
        gender[z] = gender[min];
        gender[min] = savegender;

        string savename = userinfo[z][name];
        userinfo[z][name] = userinfo[min][name];
        userinfo[min][name] = savename;


        cout << "User Record:" << endl;
        cout << z + 1 << ". ";
        cout << "Username:" << userinfo[z][name] << endl;
        cout << "Gender:" << gender[z] << endl;
    }
          break;
    case 5: for (int z = 0;z < shownNumber;z++) {
        int minvalue = age[z];
        int min = z;
        for (int j = z + 1;j < shownNumber;j++) {
            if (age[j] < minvalue) {
                min = j;
                minvalue = age[j];
            }
        }
        int saveage = age[z];
        age[z] = age[min];
        age[min] = saveage;

        string savename = userinfo[z][name];
        userinfo[z][name] = userinfo[min][name];
        userinfo[min][name] = savename;


        cout << "User Record:" << endl;
        cout << z + 1 << ". ";
        cout << "Username:" << userinfo[z][name] << endl;
        cout << "Age:" << age[z] << endl;
    }
          break;
    case 6: break;

    }
    cout << "enter any key back to menu:";
    cin >> ignore;

}//function


int Getage() {
    int age;
    string request = "Age:";
    cout << request;
    age = sureint(request);
    return age;
}
char Getgender() {
    char gender;
    string request = "Gender(m for male f for female):";
    do {
        cout << request;
        cin >> gender;
        cin.ignore(10000, '\n');
        gender = tolower(gender);
        if (!(gender == 'm' || gender == 'f')) {
            cout << "Wrong gender please enter m or f" << endl;
        }
    } while ((!(gender == 'm' || gender == 'f')));
    return gender;
}
string Getphone() {
    string phone;
    int run = 0;
    do {
        run = 1;
        cout << "Phone number:";
        getline(cin, phone);

        if (phone.size() < 7) {
            cout << "invalid input format(012-3456789)" << endl;
            run = 0;
        }
        else {
            for (int j = 0; j < phone.size(); j++) {
                if (!(isdigit(phone.at(j)) || phone.at(j) == '-')) {
                    cout << "invalid input format(012-3456789)" << endl;
                    run = 0;
                }
            }
        }
    } while (run == 0);
    return phone;
}


string Getemail() {
    string email;
    int count;
    do {
        count = 0;
        cout << "Email:";
        getline(cin, email);
        for (int a = 0;a < email.size();a++) {
            if (email.at(a) == '@') {
                count++;
            }
        }
        if (!(count == 1)) {
            cout << "Wrong email   Example(abc@gmail.com)" << endl;
        }
    } while (!(count == 1));
    return email;
}
string randomid() {
    string id = "M";
    int num;
    bool duplicate;
    do {
        id = "M";
        duplicate = false;
        num = rand() % 10000;
        id += to_string(num);

        for (int k = 0; k < countUser; k++) {
            if (u[k].userid == id) {
                duplicate = true;
                break;
            }
        }
    } while (duplicate);
    return id;
}
int selectUser() {
    int choice;
    for (int count = 0; count < countUser; count++) {
        cout << count + 1 << ". ";
        cout << u[count].username << endl;
    }
    cout << "which user(enter 1-" << countUser << "):\n";
    choice = surechoice();
    return choice;
}

int sureint(string request) {
    int result = 0;
    string position = "run";
    do {
        cin >> result;
        int wrongmessage = 0;
        if (cin.fail()) {
            cout << "wrong number please enter more than 0" << endl << request;
            cin.clear();
            cin.ignore(10000, '\n');
            wrongmessage = 1;
        }
        else {
            cin.ignore(10000, '\n');
        }
        if (result >= 1) { position = "stop"; }
        if (position == "run" && wrongmessage == 0) {
            cout << "wrong number please enter more than 0" << endl << request;
        }
    } while (!(position == "stop"));
    return result;
}
int sureint(int limit, string request) {
    int result = 0;
    string position = "run";
    do {
        cin >> result;
        int wrongmessage = 0;
        if (cin.fail()) {
            cout << "wrong number please enter more than 0" << endl << request;
            cin.clear();
            cin.ignore(10000, '\n');
            wrongmessage = 1;
        }
        else {
            cin.ignore(10000, '\n');
        }
        if (result >= 1 && result <= limit) { position = "stop"; }
        if (position == "run" && wrongmessage == 0) {
            cout << "wrong nunber please enter more than 0" << endl << request;
        }
    } while (!(position == "stop"));
    return result;
}
int surechoice() {
    string position = "run";
    int choice;
    do {
        cin >> choice;
        if (cin.fail()) {
            cout << "wrong number please enter more than 0" << endl << "user:";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else {
            cin.ignore(10000, '\n');
            choice -= 1;
            if (choice < 0 || choice >= countUser) {
                cout << "wrong number please enter more than 0 " << endl << "user:";
            }
            else { position = "stop"; }
        }
    } while (!(position == "stop"));
    return choice;
}

void savedata() {
    ofstream outfile("userData.txt");
    outfile << countUser << endl;
    for (int k = 0; k < countUser; k++) {
        outfile << u[k].username << endl;
        outfile << u[k].gender << endl;
        outfile << u[k].age << endl;
        outfile << u[k].phone << endl;
        outfile << u[k].email << endl;
        outfile << u[k].address << endl;
        outfile << u[k].userid << endl;
    }
    outfile.close();
}

void loaddata() {
    ifstream infile("userData.txt");
    if (!infile.is_open()) { return; }
    infile >> countUser;
    infile.ignore(10000, '\n');
    for (int k = 0; k < countUser; k++) {
        string genderline;
        string ageline;

        getline(infile, u[k].username);

        getline(infile, genderline);
        u[k].gender = genderline[0];

        getline(infile, ageline);
        u[k].age = stoi(ageline);

        getline(infile, u[k].phone);
        getline(infile, u[k].email);
        getline(infile, u[k].address);
        getline(infile, u[k].userid);
    }
    infile.close();
}

void searchrecord() {
    string ignore;
    string request = "please enter a number1-7： ";
    loaddata();
    cout << "Search User" << endl
        << "1.By User ID:" << endl
        << "2.By Name:" << endl
        << "3.By Gender:" << endl
        << "4.By Age:" << endl
        << "5.By Email:" << endl
        << "6.By phone Number:" << endl
        << "7.Back" << endl
        << request << endl;
    choice = sureint(7, request);
    system("cls");
    searchuser(choice);
    cout << "enter any key back to menu:";
    cin >> ignore;
    system("cls");
}

int searchuser(int choice) {
    string search;
    char searchgender;
    int searchage;
    bool found = false;
    int shownNumber = 0;
    if (choice == 1) {
        cout << "UserID: ";
        getline(cin, search);
        for (int k = 0; k < countUser; k++) {
            if (u[k].username.empty()) continue;

            if (u[k].userid.find(search) != string::npos) {
                found = true;
                shownNumber++;
                displayone(k, to_string(shownNumber));
            }
        }
    }
    if (choice == 2) {
        cout << "Name: ";
        getline(cin, search);
        for (int k = 0; k < countUser; k++) {
            if (u[k].username.empty()) continue;

            if (u[k].username.find(search) != string::npos) {
                found = true;
                shownNumber++;
                displayone(k, to_string(shownNumber));
            }
        }
    }
    if (choice == 3) {
        cout << "Gender: ";
        searchgender = Getgender();
        for (int k = 0; k < countUser; k++) {
            if (u[k].username.empty()) continue;

            if (searchgender == u[k].gender) {
                found = true;
                shownNumber++;
                displayone(k, to_string(shownNumber));
            }
        }
    }
    if (choice == 4) {
        cout << "Age: ";
        searchage = Getage();
        for (int k = 0; k < countUser; k++) {
            if (u[k].username.empty()) continue;

            if (searchage == u[k].age) {
                found = true;
                shownNumber++;
                displayone(k, to_string(shownNumber));
            }
        }
    }
    if (choice == 5) {
        cout << "Email: ";
        getline(cin, search);
        for (int k = 0; k < countUser; k++) {
            if (u[k].username.empty()) continue;

            if (u[k].email.find(search) != string::npos) {
                found = true;
                shownNumber++;
                displayone(k, to_string(shownNumber));
            }
        }
    }
    if (choice == 6) {
        cout << "Phone Number: ";
        getline(cin, search);
        for (int k = 0; k < countUser; k++) {
            if (u[k].username.empty()) continue;

            if (u[k].phone.find(search) != string::npos) {
                found = true;
                shownNumber++;
                displayone(k, to_string(shownNumber));
            }
        }
    }
    if (choice == 7) { found = true; }
    if (!found) {
        cout << "No matching user found." << endl;
    }
    cout << "------------------------------" << endl;
    return 0;
}










void serviceManagement() {
    loadFood();

    int choice = 0;
    do {
        displayServiceMenu();
        cout << "Please enter your choice (1-6) : ";

        while (!(cin >> choice) || choice < 1 || choice>6) {
            cout << "You have enter an invalid choice ! Please enter a digit between 1 to 6 : ";
            cin.clear();				//use to reset the cin>>choice 
            cin.ignore(1000, '\n');		//clear the cin>>choice if invalid input is enter

        }
        cin.ignore(1000, '\n');			//the 1000 mean that ignore 1000 character while \n will ignore new line 

        switch (choice) {
        case 1:
            addfood();
            break;
        case 2:
            updatefood();
            break;
        case 3:
            deletefood();
            break;
        case 4:
            searchfood();
            break;
        case 5:
            displayAllfood();
            break;
        case 6:
            saveFood();
            cout << "\nReturning to Main Menu......\n";
            break;

        }
    } while (choice != 6);
}

string toUpperString(string str) {
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

//The search function 
int findFoodbyId(string id) {
    string searchID = toUpperString(id);
    for (int i = 0;i < foodcount;i++) {
        if (toUpperString(menulist[i].id) == searchID) {
            return i;
        }
    }
    return -1;
}

void displayServiceMenu() {								//display what the user will see first
    cout << "\n===============----------===============\n";
    cout << "                Service Menu ";
    cout << "\n===============----------===============\n";
    cout << "1) Add new food items " << endl;
    cout << "2) Update existing food items " << endl;
    cout << "3) Delete food items " << endl;
    cout << "4) Search for any food " << endl;
    cout << "5) Display all menu items " << endl;
    cout << "6) Return to main menu " << endl;
    cout << "===============----------===============\n";

}

//The function of adding food

void addfood() {										//head to the add food function
    if (foodcount >= MAX_FOOD) {						//if food count reach 999 display this
        cout << "\n Unable to add more food! The food menu is full. Please contact the administrator to increase the food count.\n";
        return;
    }

    menu newitem;										//the function to enter new item into the menu
    cout << "\n----------ADD NEW MENU FOODS----------\n";

    //use to validate not same food ID
    while (true) {										//if true display this ensure that id is valid
        cout << "Enter food ID (EXAMPLE : F001) : ";
        getline(cin, newitem.id);

        if (newitem.id.empty()) {						//if false display this
            cout << "Food ID cannot be entered! Please ensure that you are entering a valid food ID";
            continue;
        }

        newitem.id = toUpperString(newitem.id);

        if (findFoodbyId(newitem.id) != -1) {			//if already have display this
            cout << "Invalid ID name " << newitem.id << "already exist! Please enter a new food ID" << endl;
            continue;
        }
        break;
    }
    while (true) {										//if previous is true then display this. valid food name
        cout << "Enter food name : ";
        getline(cin, newitem.name);

        if (newitem.name.empty()) {						//if false display this
            cout << "Invalid food name! Food name cannot be blank \n";
            continue;
        }
        bool namehave = false;
        for (int i = 0; i < foodcount;i++) {
            if (toUpperString(menulist[i].name) == toUpperString(newitem.name)) {
                namehave = true;
                break;
            }
        }
        if (namehave) {
            cout << "The menu already contain this dish. Please enter new dish name or add some modification.";
            continue;
        }
        break;

    }

    while (true) {										//if previous is true then display this.valid food types
        cout << "Enter the type of the food (Example: Main dish,drinks or dessert) : ";
        getline(cin, newitem.type);

        if (newitem.type.empty()) {						//if false display this
            cout << "Invalid input\n";
        }
        else {
            break;
        }
    }
    while (true) {										//if previous is true then display this. valid price for food
        cout << "Enter the price of the food (RM) : ";
        if (cin >> newitem.price && newitem.price >= 0) {
            cin.ignore(1000, '\n');
            break;
        }
        else {											//if flase display this
            cout << "Invalid input. Please enter again";
            cin.clear();
            cin.ignore(100, '\n');
        }
    }
    char availchoice;									//if previous is true the display this. want to put this food into the memory menu
    cout << "Is this food available now?? (Y/N) : ";
    cin >> availchoice;
    cin.ignore(100, '\n');
    newitem.isAvailable = (toupper(availchoice) == 'Y');  //ensure the the y will become Y

    menulist[foodcount] = newitem;						//add food to the memory
    foodcount++;

    saveFood();
    cout << "\n Food have now been added to the menu!\n";
    cout << "*******************\n";

}

//update food 
void updatefood() {										//head to the update food function
    cout << "\n-----UPDATE MENU FOOD------\n";			//if no food is in menu display this
    if (foodcount == 0) {
        cout << "Please add food to the menu to update the food.\n";
        return;
    }
    string upid;										//chaneg food ID
    cout << "Please enter the food ID you would like to update : ";
    getline(cin, upid);

    int index = findFoodbyId(upid);						//to find exsiting id to change
    if (index == -1) {
        cout << "Invalid food ID" << upid << " food id not found. Please ensure that you have enter a valid food ID.\n";
        return;
    }

    cout << "Food ID have been found : \n";				//food id found, food id change 
    cout << "ID : " << menulist[index].id << " |Name : " << menulist[index].name
        << "| Price : RM" << fixed << setprecision(2) << menulist[index].price << endl;
    cout << "\n Please enter the updated information. Leave blank to not update food details.\n";

    string nname;										//save new name
    cout << "The new name is [" << menulist[index].name << "]: ";
    getline(cin, nname);
    if (!nname.empty()) {
        menulist[index].name = nname;

    }

    string ntype;										//save new type
    cout << "The new type of food is [" << menulist[index].type << "]: ";
    getline(cin, ntype);
    if (!ntype.empty()) {
        menulist[index].type = ntype;

    }

    string pstr;										//save new price
    cout << "The new price is [" << menulist[index].price << "]: ";
    getline(cin, pstr);
    if (!pstr.empty()) {
        try {											//Try is use to ensure the console does not crash by runtime error.Run time error will be the example below (RM).
            double nprice = stod(pstr);					//stod is use to convert string and floating point into double
            if (nprice >= 0) {							// if admin type RM, rm will be ignore and only the value will be store
                menulist[index].price = nprice;
            }
            else {
                cout << "Invalid input. Please ensure that you have entered a valid price\n"
                    << endl << "The food price will remain unchange";
            }
        }
        catch (...) {								//If the try fail,catch will continue the code to ensure the code does not get into runtime erros
            cout << "Invalid input. Please ensure that you have entered a valid price.\n"
                << endl << "The food price will remain unchange";

        }
    }

    char availfood;									//is the new food available
    cout << "Is the updated food available? (Y/N) : ";
    cin >> availfood;
    cin.ignore(1000, '\n');
    menulist[index].isAvailable = (toupper(availfood) == 'Y');

    saveFood();									//All the updated information will be save into the memory
    cout << "\n The food have been updated. Thank you for your hardwork.\n";
}

//Delete food											//function to delete food
void deletefood() {
    cout << "\n-----DELETING FOOD ITEMS-----\n";
    if (foodcount == 0) {								//if admin have not enter food display this
        cout << "There is no available food to delete. Please add some food to use this function.\n";
        return;
    }
    string targetid;									//find the food ID to delete
    cout << "Please enter the food ID to delete : ";
    getline(cin, targetid);

    int index = findFoodbyId(targetid);					//invalid input display this
    if (index == -1) {
        cout << "Unable to find food ID" << targetid << endl;
        cout << "\n*****************";
        return;
    }
    char confirm;										//if valid then display confirmation
    cout << "Are you sure you would like to delete : " << menulist[index].name << "? (Y/N)";
    cin >> confirm;
    cin.ignore(1000, '\n');

    if (toupper(confirm) == 'Y') {						//change the y to Y
        for (int i = index;i < foodcount;i++) {
            menulist[i] = menulist[i + 1];				//increase food item in menu memory
        }foodcount--;									//decrease the maximum food count
        saveFood();									//save to memory
        cout << "The following food have been deleted";

    }
    else {												//if other alphabet or n is input then display this
        cout << "The deletion have been cancel";
    }

}

//search food

void searchfood() {										//function for searching food
    cout << "\n-----SEARCH MENU FOOD-----\n";
    if (foodcount == 0) {								//if no food added then display this
        cout << "Menu is currently empty. Please enter food to search for food.";
        return;
    }

    string fname;										//fname is find name
    cout << "Enter food ID or food name to search for food : ";
    getline(cin, fname);

    string upperfname = toUpperString(fname);			//change all upper fname to uppercase
    bool found = false;
    //display the found food
    cout << "\n====================================================================================\n";
    cout << left << setw(10) << "Food ID";
    cout << left << setw(25) << "Name";
    cout << left << setw(15) << "Type";
    cout << left << setw(12) << "Price (RM) ";
    cout << left << setw(10) << "status";
    cout << "\n====================================================================================\n";

    for (int i = 0;i < foodcount;i++) {					//this loop is to loop through the entire function inside 1 by one
        string upperid = toUpperString(menulist[i].id);			//change the id inside the menu to upper 
        string uppername = toUpperString(menulist[i].name);		//same for food name

        if (upperid.find(upperfname) != string::npos || uppername.find(upperfname) != string::npos) {				//npos mean no position. npos detect string in this case.If user enter a type of string 
            cout << left << setw(10) << menulist[i].id																//for example no_pain,the entire for loop will loop until it find that string,if no string is found 
                << left << setw(25) << menulist[i].name																//inside the index or menulist[i].name it will return back the following statment    
                << left << setw(15) << menulist[i].type																//npos is use when an invalid input is inputed into the code within a string.
                << fixed << setprecision(2) << setw(12) << menulist[i].price
                << (menulist[i].isAvailable ? "Available" : "Sold out") << endl;										//the ? and : is use to output true or false statment. Example if i>5 ? "true" : "false".If the condition is true it will print the left handside in this case it will print (true)
            found = true;
        }

    }
    if (!found) {										//if unable to find food display this
        cout << "Unable to find food matching " << fname << "\n";

    }
    cout << "\n======================================================================================\n";

}

//Display all food item that is available at menu

void displayAllfood() {																					//function to display food
    cout << "\n-----RESTAURANT MENU-----\n";															//when food count=0 display this
    if (foodcount == 0) {
        cout << "Menu does not contain any items. Please add item to display food.";
        return;
    }

    cout << "\n====================================================================================\n";	//food count not equal to 0 display this
    cout << left << setw(5) << "No."
        << setw(10) << "ID"
        << setw(25) << "Name"
        << setw(15) << "Type"
        << setw(12) << "Price (RM)"
        << setw(10) << "Status" << endl;
    cout << "\n====================================================================================\n";

    for (int i = 0;i < foodcount;i++) {																	//displaying all food mean that we start from array 0
        cout << left << setw(5) << (i + 1)																//thus i=0 and after display a food i is increase thus display next food
            << setw(10) << menulist[i].id
            << setw(25) << menulist[i].name
            << setw(15) << menulist[i].type
            << fixed << setprecision(2) << setw(12) << menulist[i].price
            << (menulist[i].isAvailable ? "Available" : "Sold out") << endl;
    }
    cout << "\n====================================================================================\n";
    cout << "Total food : " << foodcount << endl;

}

//Save data(food) to File
void saveFood() {																						//function of saving food to file
    ofstream outfile(MENU);																				//ofstream is use to open a file for saving data, it serve as a memory space where the code is save
    if (!outfile) {
        cout << "Unable to save data to file. Please ensure that you have enter valid input.\n";
        return;
    }
    for (int i = 0;i < foodcount;i++) {																	//save food to file 
        outfile << menulist[i].id << "|"																//after a food is save i++ to enable for the next food to be save
            << menulist[i].name << "|"
            << menulist[i].type << "|"
            << menulist[i].price << "|"
            << menulist[i].isAvailable << "\n";

    }
    outfile.close();																					//close the file
}

//load data from file
void loadFood() {																					//function of laoding memory in the file
    ifstream infile(MENU);
    if (!infile) {																						//if it is not in file then return
        return;
    }
    foodcount = 0;																						//starting with food count 0
    string food;
    while (getline(infile, food) && foodcount < MAX_FOOD) {												//this function to start reading the file one line at a time until end of array or MAX_FOOD
        if (food.empty())continue;																		//this is use to skip any blank line from the file

        size_t p1 = food.find('|');																		//size_t is a data type that is use to represent the size of anything in cpp,size can only store positive integer
        size_t p2 = food.find('|', p1 + 1);																//size_t is use for array or structure
        size_t p3 = food.find('|', p2 + 1);																//find is use for linear search 
        size_t p4 = food.find('|', p3 + 1);

        if (p1 != string::npos && p2 != string::npos && p3 != string::npos && p4 != string::npos) {		//this is use to check that all 4 condition is found in the file
            menulist[foodcount].id = food.substr(0, p1);												//How substr work use to know what to copy base on the starting character and ending character
            menulist[foodcount].name = food.substr(p1 + 1, p2 - p1 - 1);								//It first start by changing all the data type like string, int, double in to a character (char)
            menulist[foodcount].type = food.substr(p2 + 1, p3 - p2 - 1);								//Each char will take up a single place inside an index.
            menulist[foodcount].price = stod(food.substr(p3 + 1, p4 - p3 - 1));							//go to line 505
            menulist[foodcount].isAvailable = (stoi(food.substr(p4 + 1)) == 1);							//stod convert string to double, stoi convert string to integer          converting the isAvailable form string to integer, so that if isAvailable is label with available it will convert the string isAvailable to int isAvaible. mean that if isAvailbe is available then 1==1.
            foodcount++;																				//substr is use to cut a portion of a string and display the cuted string or substring into a brand new string

        }
    }
    infile.close();																						//close file
}


//Student C System
void transactionModule(userrecord u[]) {

    int choice;
    loaddata();       //load student a data
    loadFood();   //load student b data
    loadOrders();

    string currentCustomerID;
    int customerIndex = -1;
    system("cls");
    cout << "Enter your customer ID (Type R to return): ";
    cin >> currentCustomerID;

    if (currentCustomerID == "R") {
        system("cls");
        return;
    }

    for (int idx = 0; idx < MAX_CUSTOMER; idx++) {
        if (u[idx].userid == currentCustomerID) {
            customerIndex = idx;
            break;
        }
    }

    while (cin.fail() || customerIndex == -1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter correct customer ID: \a";
        cin >> currentCustomerID;

        if (currentCustomerID == "R") {
            system("cls");
            return;
        }

        for (int idx = 0; idx < MAX_CUSTOMER; idx++) {
            if (u[idx].userid == currentCustomerID) {
                customerIndex = idx;
                break;
            }
        }
    }
    cout << "Valid customer ID!!";
    this_thread::sleep_for(chrono::seconds(2));
    system("cls");

    do {
        system("cls");
        cout << "\n----------------------------------------------" << endl;
        cout << "-----** Restaurant Ordering System **-----" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Current Customer ID : " << currentCustomerID << endl;
        cout << "----------------------------------------------" << endl;
        cout << "---       1) Create Order                  ---" << endl;
        cout << "---       2) Cancel Order                  ---" << endl;
        cout << "---       3) Modify Order                  ---" << endl;
        cout << "---       4) Search Order                  ---" << endl;
        cout << "---       5) Display Order Summary         ---" << endl;
        cout << "---       6) Make Payment                  ---" << endl;
        cout << "---       7) Exit                          ---" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "\nChoose an Option (1-7): ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            createOrder(customerIndex, currentCustomerID);
            break;
        case 2:
            cancelOrder(customerIndex);
            break;
        case 3:
            modifyOrder(customerIndex);
            break;
        case 4:
            searchOrder(customerIndex);
            break;
        case 5:
            displayOrderSummary(customerIndex);
            break;
        case 6:
            makePayment(customerIndex);
            break;
        case 7:
            saveOrders();
            system("cls");
            cout << "\nReturning to Main Menu..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            break;
        default:
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "\n =============================================" << endl;
            cout << "||  Invalid option. Please try again. (>_<)  ||\a" << endl;
            cout << " ============================================= \n\n";
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    } while (choice != 7);
}

void createOrder(int customerIndex, string currentCustomerID) {
    if (orderCount[customerIndex] >= MAX_ORDER) {
        cout << "\n###############################################\n";
        cout << "## Maximum 1000 orders reached for customer. ##\n\a";
        cout << "###############################################\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    Order newOrder{};
    newOrder.customerID = currentCustomerID;
    newOrder.orderID = orderCount[customerIndex] + 1;

    cout << "\n  =================================  \n";
    cout << "  ===       Create Order       ===  ";
    cout << "\n  =================================  \n";
    cout << "\nCustomer ID : " << newOrder.customerID << endl;
    cout << "Order ID : " << newOrder.orderID << endl;

    newOrder.itemCount = 0;
    newOrder.totalAmount = 0;
    newOrder.active = true;
    newOrder.paid = false;

    char more;
    do {
        cout << "\n";
        displayAllfood();

        int itemID;
        int quantity;

        cout << "\nEnter Item ID (Enter 1 for F001)(Enter -999 for exit) : ";
        cin >> itemID;

        if (itemID == -999) {
            return;
        }

        string searchID;
        if (itemID < 10)
            searchID = "F00" + to_string(itemID);
        else if (itemID < 100)
            searchID = "F0" + to_string(itemID);
        else
            searchID = "F" + to_string(itemID);

        int menuPosition = -1;

        for (int i = 0; i < foodcount; i++) {
            if (menulist[i].id == searchID) {
                menuPosition = i;
                break;
            }
        }

        while (menuPosition == -1) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid Item ID.\n\a";
                cout << "Please enter Item ID again (Enter -999 for exit) : ";
                cin >> itemID;
                if (itemID == -999) {
                    return;
                }
            }
            else {
                cout << "Invalid Item ID.\n\a";
                cout << "Please enter Item ID again(Enter -999 for exit) : : ";
                cin >> itemID;
                if (itemID == -999) {
                    return;
                }
            }

            if (itemID < 10)
                searchID = "F00" + to_string(itemID);
            else if (itemID < 100)
                searchID = "F0" + to_string(itemID);
            else
                searchID = "F" + to_string(itemID);

            menuPosition = -1;

            for (int i = 0; i < foodcount; i++) {
                if (menulist[i].id == searchID) {
                    menuPosition = i;
                    break;
                }
            }
        }

        cout << "Enter quantity : ";
        cin >> quantity;
        int error = -999;
        while (error == -999) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input.\n\a";
                cout << "Please enter quantity again : ";
                cin >> quantity;
            }
            else if (quantity <= 0) {
                cout << "Quantity must be greater than 0.\n\a";
                cout << "Please enter quantity again : ";
                cin >> quantity;
            }
            else {
                error = -888;
            }
        }

        newOrder.itemID[newOrder.itemCount] = itemID;
        newOrder.quantity[newOrder.itemCount] = quantity;
        newOrder.totalAmount = newOrder.totalAmount + menulist[menuPosition].price * quantity;
        newOrder.itemCount++;

        cout << "\nItem added successfully.\n\a";
        this_thread::sleep_for(chrono::seconds(1));

        if (newOrder.itemCount >= MAX_ITEM_PER_ORDER) {
            cout << "\n########################################\n";
            cout << "## Maximum 50 different items reached. ##\n";
            cout << "########################################\n";
            this_thread::sleep_for(chrono::seconds(2));
            more = 'N';
            cin.ignore(1000, '\n');
        }
        else {
            cout << "\nAdd another item? (Y/N) : ";
            cin.ignore(1000, '\n');
            cin.get(more);
            more = toupper(more);
            cin.ignore(1000, '\n');

            while (more != 'Y' && more != 'N') {
                cout << "Invalid answer! Please try again.\n\a";
                cout << "Add another item? (Y/N) : ";
                cin.get(more);
                more = toupper(more);
                cin.ignore(1000, '\n');
            }
        }
    } while (more == 'Y');

    order[customerIndex][orderCount[customerIndex]] = newOrder;
    orderCount[customerIndex]++;

    saveOrders();

    system("cls");
    cout << "\n================================\n";
    cout << "== Order Created Successfully ==\n";
    cout << "================================\n";
    cout << "\nCustomer ID : " << newOrder.customerID << endl;
    cout << "Order ID : " << newOrder.orderID << endl;
    cout << "\nItems:\n";

    for (int i = 0;i < newOrder.itemCount;i++) {
        for (int j = 0; j < foodcount; j++) {

            string targetID;
            int idNum = newOrder.itemID[i];
            if (idNum < 10)
                targetID = "F00" + to_string(idNum);
            else if (idNum < 100)
                targetID = "F0" + to_string(idNum);
            else
                targetID = "F" + to_string(idNum);

            if (menulist[j].id == targetID) {
                cout << "  " << menulist[j].name << " x " << newOrder.quantity[i] << " = RM "
                    << fixed << setprecision(2) << menulist[j].price * newOrder.quantity[i] << endl;
                break;
            }
        }

    }

    cout << "\nTotal Amount : RM " << fixed << setprecision(2) << newOrder.totalAmount << endl;
    cout << "\nOrder saved successfully.\n";
    cout << "\nType any character to exit.";
    cin.get();
}

void cancelOrder(int customerIndex) {
    cout << "\n  =================================  \n";
    cout << "  ===       Cancel Order       ===  ";
    cout << "\n  =================================  \n";

    if (orderCount[customerIndex] == 0) {
        cout << "\n\n    ############################\n";
        cout << "    ##  No orders available.  ##\n\a";
        cout << "    ############################\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    int orderID;
    int position = -1;

    do {
        cout << "\nEnter Order ID";
        cout << " (Type -999 to return): ";
        cin >> orderID;

        if (orderID == -999) {
            return;
        }

        for (int i = 0;i < orderCount[customerIndex];i++) {
            if (order[customerIndex][i].orderID == orderID && order[customerIndex][i].active == true) {
                position = i;
                break;
            }
        }

        if (position == -1) {
            cout << "\n\n    ##########################";
            cout << "\n    ##   Order not found!   ##\n\a";
            cout << "    ##########################\n";
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            this_thread::sleep_for(chrono::seconds(2));
        }
    } while (position == -1);


    cout << "\nOrder found!\n\n\a";
    this_thread::sleep_for(chrono::seconds(1));
    cin.ignore(1000, '\n');

    cout << "------------------------------------------------------------------------------------------";
    cout << "\n\tCustomer ID : " << order[customerIndex][position].customerID << endl;
    cout << "\tOrder ID : " << order[customerIndex][position].orderID << endl;
    cout << "\n\tItems:\n";

    for (int i = 0;i < order[customerIndex][position].itemCount;i++) {
        for (int j = 0; j < foodcount; j++) {
            string targetID;
            int idNum = order[customerIndex][position].itemID[i];
            if (idNum < 10)
                targetID = "F00" + to_string(idNum);
            else if (idNum < 100)
                targetID = "F0" + to_string(idNum);
            else
                targetID = "F" + to_string(idNum);

            if (menulist[j].id == targetID) {
                cout << "\t  " << menulist[j].name << " x " << order[customerIndex][position].quantity[i] << endl;
                break;
            }
        }
    }

    cout << "\n\tTotal Amount : RM " << fixed << setprecision(2) << order[customerIndex][position].totalAmount << endl;
    cout << "\tPayment Status : ";
    if (order[customerIndex][position].paid) {
        cout << "Paid\n";
    }
    else {
        cout << "Not Paid\n";
    }

    cout << "------------------------------------------------------------------------------------------\n";
    char confirm;
    cout << "\nAre you sure you want to cancel this order? (Y/N) : ";
    cin.get(confirm);
    confirm = toupper(confirm);
    cin.ignore(1000, '\n');

    while (confirm != 'Y' && confirm != 'N') {
        cout << "Invalid answer! Please try again.\n\a";
        cout << "Are you sure you want to cancel this order? (Y/N) : ";
        cin.get(confirm);
        confirm = toupper(confirm);
        cin.ignore(1000, '\n');
    }

    if (confirm == 'Y') {
        order[customerIndex][position].active = false;
        if (order[customerIndex][position].paid == true) {
            cout << "\n\nThe amount of RM" << order[customerIndex][position].totalAmount << " has been refund successfully! \a";
            this_thread::sleep_for(chrono::seconds(1));
            order[customerIndex][position].paid = false;
        }
        saveOrders();
        cout << "\n\n  #####################################\n";
        cout << "  ##  Order cancelled successfully.  ##\n\a";
        cout << "  #####################################\n";
    }
    else {
        cout << "\n\n    ################################";
        cout << "\n    ##  Order was not cancelled.  ##\n\a";
        cout << "    ################################\n";
    }
    this_thread::sleep_for(chrono::seconds(2));
}

void modifyOrder(int customerIndex) {
    cout << "\n====================================\n";
    cout << "==          Modify Order          ==\n";
    cout << "====================================\n";

    if (orderCount[customerIndex] == 0) {
        cout << "\n\n    ############################\n";
        cout << "    ##  No orders available.  ##\n\a";
        cout << "    ############################\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    char again = 'Y';
    do {
        int orderID;
        int position = -1;

        do {
            cout << "\nEnter Order ID (Type -999 to return): ";
            cin >> orderID;

            if (orderID == -999) {
                return;
            }

            for (int i = 0;i < orderCount[customerIndex];i++) {
                if (order[customerIndex][i].orderID == orderID && order[customerIndex][i].active == true) {
                    position = i;
                    break;
                }
            }

            if (position == -1) {
                cout << "\n\n    ##########################";
                cout << "\n    ##   Order not found!   ##\n\a";
                cout << "    ##########################\n";
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                this_thread::sleep_for(chrono::seconds(2));
            }
        } while (position == -1);


        cout << "\nOrder found!\n\n\a";
        this_thread::sleep_for(chrono::seconds(1));
        cin.ignore(1000, '\n');

        cout << "\n----------------------------------\n";
        cout << "   1. Modify Item Quantity\n";
        cout << "   2. Add Item\n";
        cout << "   3. Remove Item\n";
        cout << "----------------------------------\n";

        int choice;
        cout << "\nEnter choice: ";
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid choice.\n\n\a";
            cout << "Please enter choice again (1-3): ";
            cin >> choice;
        }
        if (choice == 1) {
            if (order[customerIndex][position].itemCount == 0) {
                cout << "\n\n*****************************\n";
                cout << "   No items in this order.\n";
                cout << "*****************************\n\n";
                this_thread::sleep_for(chrono::seconds(2));
                return;
            }

            cout << "\n\nItems in order:\n";
            for (int i = 0;i < order[customerIndex][position].itemCount;i++) {
                for (int j = 0; j < foodcount; j++) {
                    string targetID;
                    int idNum = order[customerIndex][position].itemID[i];
                    if (idNum < 10)
                        targetID = "F00" + to_string(idNum);
                    else if (idNum < 100)
                        targetID = "F0" + to_string(idNum);
                    else
                        targetID = "F" + to_string(idNum);

                    if (menulist[j].id == targetID) {
                        cout << i + 1 << ". " << menulist[j].name << "  ||  Quantity: "
                            << order[customerIndex][position].quantity[i] << endl;
                        break;
                    }
                }
            }

            cout << "\nPayment Status : ";
            if (order[customerIndex][position].paid) {
                cout << "Paid\n";
            }
            else {
                cout << "Not Paid\n";
            }

            int itemNumber;
            cout << "\n\nEnter item number: ";
            cin >> itemNumber;

            while (cin.fail() || itemNumber < 1 || itemNumber > order[customerIndex][position].itemCount) {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid item number.\n\a";
                cout << "Please enter item number again: ";
                cin >> itemNumber;
            }

            int newQuantity;
            cout << "Enter new quantity: ";
            cin >> newQuantity;
            int error = -999;

            while (error == -999) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "Invalid input.\n\a";
                    cout << "Please enter quantity again : ";
                    cin >> newQuantity;
                }
                else if (newQuantity <= 0) {
                    cout << "Quantity must be greater than 0.\n\a";
                    cout << "Please enter quantity again : ";
                    cin >> newQuantity;
                }
                else {
                    error = -888;
                }
            }

            if (order[customerIndex][position].paid == true) {
                cout << "\n\nThe amount of RM" << order[customerIndex][position].totalAmount << " has been refund successfully! \a";
                cout << "\nPlease make payment again after it. ";
                this_thread::sleep_for(chrono::seconds(2));
                order[customerIndex][position].paid = false;
            }

            order[customerIndex][position].quantity[itemNumber - 1] = newQuantity;
            order[customerIndex][position].totalAmount = 0;

            for (int i = 0;i < order[customerIndex][position].itemCount;i++) {
                for (int j = 0; j < foodcount; j++) {
                    string targetID;
                    int idNum = order[customerIndex][position].itemID[i];
                    if (idNum < 10)
                        targetID = "F00" + to_string(idNum);
                    else if (idNum < 100)
                        targetID = "F0" + to_string(idNum);
                    else
                        targetID = "F" + to_string(idNum);

                    if (menulist[j].id == targetID) {
                        order[customerIndex][position].totalAmount += menulist[j].price * order[customerIndex][position].quantity[i];
                        break;
                    }
                }
            }

            saveOrders();
            cout << "\n\n  ######################################\n";
            cout << "  ##  Quantity updated successfully.  ##\n\a";
            cout << "  ######################################\n";
        }

        else if (choice == 2) {
            if (order[customerIndex][position].itemCount >= MAX_ITEM_PER_ORDER) {
                cout << "\n\n  ########################################\n";
                cout << "  ## Maximum 50 different items reached. ##\n";
                cout << "  ########################################\n";
                this_thread::sleep_for(chrono::seconds(2));
                return;
            }

            cout << "\n\nItems in order:\n";
            for (int i = 0;i < order[customerIndex][position].itemCount;i++) {
                for (int j = 0; j < foodcount; j++) {
                    string targetID;
                    int idNum = order[customerIndex][position].itemID[i];
                    if (idNum < 10)
                        targetID = "F00" + to_string(idNum);
                    else if (idNum < 100)
                        targetID = "F0" + to_string(idNum);
                    else
                        targetID = "F" + to_string(idNum);

                    if (menulist[j].id == targetID) {
                        cout << i + 1 << ". " << menulist[j].name << "  ||  Quantity: "
                            << order[customerIndex][position].quantity[i] << endl;
                        break;
                    }
                }
            }

            cout << "\nPayment Status : ";
            if (order[customerIndex][position].paid) {
                cout << "Paid\n\n";
            }
            else {
                cout << "Not Paid\n\n";
            }

            this_thread::sleep_for(chrono::seconds(2));
            displayAllfood();

            int itemID;
            int quantity;
            cout << "\nEnter Item ID (Enter 1 for F001): ";
            cin >> itemID;

            int menuPosition = -1;

            for (int i = 0; i < foodcount; i++) {
                string targetID;
                if (itemID < 10)
                    targetID = "F00" + to_string(itemID);
                else if (itemID < 100)
                    targetID = "F0" + to_string(itemID);
                else
                    targetID = "F" + to_string(itemID);

                if (menulist[i].id == targetID) {
                    menuPosition = i;
                    break;
                }
            }

            while (menuPosition == -1) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "Invalid Item ID.\n\a";
                    cout << "Please enter Item ID again : ";
                    cin >> itemID;
                }
                else {
                    cout << "Invalid Item ID.\n\a";
                    cout << "Please enter Item ID again : ";
                    cin >> itemID;
                }
                menuPosition = -1;

                for (int i = 0; i < foodcount; i++) {
                    string targetID;
                    if (itemID < 10)
                        targetID = "F00" + to_string(itemID);
                    else if (itemID < 100)
                        targetID = "F0" + to_string(itemID);
                    else
                        targetID = "F" + to_string(itemID);

                    if (menulist[i].id == targetID) {
                        menuPosition = i;
                        break;
                    }
                }
            }

            cout << "Enter quantity : ";
            cin >> quantity;
            int error = -999;

            while (error == -999) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "Invalid input.\n\a";
                    cout << "Please enter quantity again : ";
                    cin >> quantity;
                }
                else if (quantity <= 0) {
                    cout << "Quantity must be greater than 0.\n\a";
                    cout << "Please enter quantity again : ";
                    cin >> quantity;
                }
                else {
                    error = -888;
                }
            }

            order[customerIndex][position].itemID[order[customerIndex][position].itemCount] = itemID;
            order[customerIndex][position].quantity[order[customerIndex][position].itemCount] = quantity;
            order[customerIndex][position].itemCount++;

            if (order[customerIndex][position].paid == true) {
                cout << "\n\nThe amount of RM" << order[customerIndex][position].totalAmount << " has been refund successfully! \a";
                cout << "\nPlease make payment again after it. ";
                this_thread::sleep_for(chrono::seconds(2));
                order[customerIndex][position].paid = false;
            }

            order[customerIndex][position].totalAmount += menulist[menuPosition].price * quantity;
            saveOrders();
            cout << "\n\n  ################################\n";
            cout << "  ##  Item added successfully.  ##\n\a";
            cout << "  ################################\n";
        }

        else if (choice == 3) {
            if (order[customerIndex][position].itemCount == 0) {
                cout << "\n\n***************************\n";
                cout << "   No items in this order.\n";
                cout << "*****************************\n\n";
                this_thread::sleep_for(chrono::seconds(2));
                return;
            }

            cout << "\n\nItems in order:\n";
            for (int i = 0; i < order[customerIndex][position].itemCount; i++) {
                for (int j = 0; j < foodcount; j++) {
                    string targetID;
                    int idNum = order[customerIndex][position].itemID[i];
                    if (idNum < 10)
                        targetID = "F00" + to_string(idNum);
                    else if (idNum < 100)
                        targetID = "F0" + to_string(idNum);
                    else
                        targetID = "F" + to_string(idNum);

                    if (menulist[j].id == targetID) {
                        cout << i + 1 << ". " << menulist[j].name << "  ||  Quantity: "
                            << order[customerIndex][position].quantity[i] << endl;
                        break;
                    }
                }
            }

            cout << "\nPayment Status : ";
            if (order[customerIndex][position].paid) {
                cout << "Paid\n";
            }
            else {
                cout << "Not Paid\n";
            }

            int itemNumber;
            cout << "\n\nEnter item number to remove: ";
            cin >> itemNumber;

            while (cin.fail() || itemNumber < 1 || itemNumber > order[customerIndex][position].itemCount) {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid item number.\n\a";
                cout << "Please enter item number again: ";
                cin >> itemNumber;
            }

            int removePosition = itemNumber - 1;

            for (int i = removePosition;i < order[customerIndex][position].itemCount - 1;i++) {
                order[customerIndex][position].itemID[i] = order[customerIndex][position].itemID[i + 1];
                order[customerIndex][position].quantity[i] = order[customerIndex][position].quantity[i + 1];
            }

            order[customerIndex][position].itemCount--;

            if (order[customerIndex][position].paid == true) {
                cout << "\n\nThe amount of RM" << order[customerIndex][position].totalAmount << " has been refund successfully! \a";
                cout << "\nPlease make payment again after it. ";
                this_thread::sleep_for(chrono::seconds(2));
                order[customerIndex][position].paid = false;
            }

            order[customerIndex][position].totalAmount = 0;

            for (int i = 0; i < order[customerIndex][position].itemCount; i++) {
                for (int j = 0; j < foodcount; j++) {
                    string targetID;
                    int idNum = order[customerIndex][position].itemID[i];
                    if (idNum < 10)
                        targetID = "F00" + to_string(idNum);
                    else if (idNum < 100)
                        targetID = "F0" + to_string(idNum);
                    else
                        targetID = "F" + to_string(idNum);

                    if (menulist[j].id == targetID) {
                        order[customerIndex][position].totalAmount += menulist[j].price * order[customerIndex][position].quantity[i];
                        break;
                    }
                }
            }
            saveOrders();
            cout << "\n\n  ##################################\n";
            cout << "  ##  Item removed successfully.  ##\n\a";
            cout << "  ##################################\n";
        }
        this_thread::sleep_for(chrono::seconds(2));
        cout << "\nDo you want to continue modify other order? (Y/N) : ";
        cin.ignore(1000, '\n');
        cin.get(again);
        again = toupper(again);
        cin.ignore(1000, '\n');

        while (again != 'Y' && again != 'N') {
            cout << "Invalid answer! Please try again.\n\a";
            cout << "Do you want to continue modify other order? (Y/N) : ";
            cin.get(again);
            again = toupper(again);
            cin.ignore(1000, '\n');
        }
    } while (again == 'Y');
}

void searchOrder(int customerIndex) {
    cout << "\n====================================\n";
    cout << "==           Search Order         ==\n";
    cout << "====================================\n";

    if (orderCount[customerIndex] == 0) {
        cout << "\n\n    ############################\n";
        cout << "    ##  No orders available.  ##\n\a";
        cout << "    ############################\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    int orderID;
    int position = -1;

    do {
        cout << "\nEnter Order ID";
        cout << " (Type -999 to return): ";
        cin >> orderID;

        if (orderID == -999) {
            return;
        }

        for (int i = 0;i < orderCount[customerIndex];i++) {
            if (order[customerIndex][i].orderID == orderID && order[customerIndex][i].active == true) {
                position = i;
                break;
            }
        }

        if (position == -1) {
            cout << "\n\n    ##########################";
            cout << "\n    ##   Order not found!   ##\n\a";
            cout << "    ##########################\n";
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            this_thread::sleep_for(chrono::seconds(2));
        }
    } while (position == -1);

    cout << "\n\n====================================\n";
    cout << "             Order Found !!!\n";
    cout << "====================================\n";

    cout << "\nCustomer ID : " << order[customerIndex][position].customerID << endl;
    cout << "Order ID : " << order[customerIndex][position].orderID << endl;
    cout << "\nItems:\n";
    for (int i = 0; i < order[customerIndex][position].itemCount; i++) {
        for (int j = 0; j < foodcount; j++) {
            string targetID;
            int idNum = order[customerIndex][position].itemID[i];
            if (idNum < 10)
                targetID = "F00" + to_string(idNum);
            else if (idNum < 100)
                targetID = "F0" + to_string(idNum);
            else
                targetID = "F" + to_string(idNum);

            if (menulist[j].id == targetID) {
                cout << "  " << menulist[j].name << " x " << order[customerIndex][position].quantity[i] << " = RM "
                    << fixed << setprecision(2) << menulist[j].price * order[customerIndex][position].quantity[i] << endl;
                break;
            }
        }
    }
    cout << "\nTotal Amount : RM " << fixed << setprecision(2) << order[customerIndex][position].totalAmount << endl;
    cout << "Payment Status : ";

    if (order[customerIndex][position].paid) {
        cout << "Paid\n";
    }
    else {
        cout << "Not Paid\n";
    }
    cout << "\n\nType any character to exit.";
    cin.get();
    cin.ignore(1000, '\n');
}

void displayOrderSummary(int customerIndex) {
    cout << "\n====================================\n";
    cout << "==        Order Summary           ==\n";
    cout << "====================================\n";

    if (orderCount[customerIndex] == 0) {
        cout << "\n\n    ############################\n";
        cout << "    ##  No orders available.  ##\n\a";
        cout << "    ############################\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    bool found = false;

    for (int i = 0;i < orderCount[customerIndex];i++) {
        if (order[customerIndex][i].active == true) {
            found = true;
            cout << "\n\n------------------------------------\n";
            cout << "Customer ID : " << order[customerIndex][i].customerID << endl;
            cout << "Order ID : " << order[customerIndex][i].orderID << endl;
            cout << "Items:\n";

            for (int j = 0; j < order[customerIndex][i].itemCount; j++) {
                for (int k = 0; k < foodcount; k++) {
                    string targetID;
                    int idNum = order[customerIndex][i].itemID[j];
                    if (idNum < 10)
                        targetID = "F00" + to_string(idNum);
                    else if (idNum < 100)
                        targetID = "F0" + to_string(idNum);
                    else
                        targetID = "F" + to_string(idNum);

                    if (menulist[k].id == targetID) {
                        cout << "  " << menulist[k].name << " x " << order[customerIndex][i].quantity[j] << " = RM "
                            << fixed << setprecision(2) << menulist[k].price * order[customerIndex][i].quantity[j] << endl;
                        break;
                    }
                }
            }
            cout << "Total Amount : RM " << fixed << setprecision(2) << order[customerIndex][i].totalAmount << endl;
            cout << "Payment Status : ";
            if (order[customerIndex][i].paid) {
                cout << "Paid\n";
            }
            else {
                cout << "Not Paid\n";
            }
        }
    }


    if (!found) {
        cout << "\n\n    #####################################\n";
        cout << "    ##  No active orders available !!  ##\n\a";
        cout << "    #####################################\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    cout << "\n====================================\n";
    cout << "\n\nType any character to exit.";
    cin.get();
    cin.ignore(1000, '\n');
}

void makePayment(int customerIndex) {
    cout << "\n====================================\n";
    cout << "==         Make Payment           ==\n";
    cout << "====================================\n";

    if (orderCount[customerIndex] == 0) {
        cout << "\n\n    ############################\n";
        cout << "    ##  No orders available.  ##\n\a";
        cout << "    ############################\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    int orderID;
    int position = -1;
    do {
        cout << "\nEnter Order ID";
        cout << " (Type -999 to return): ";
        cin >> orderID;

        if (orderID == -999) {
            return;
        }

        for (int i = 0;i < orderCount[customerIndex];i++) {
            if (order[customerIndex][i].orderID == orderID && order[customerIndex][i].active == true) {
                position = i;
                break;
            }
        }

        if (position == -1) {
            cout << "\n\n    ##########################";
            cout << "\n    ##   Order not found!   ##\n\a";
            cout << "    ##########################\n";
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            this_thread::sleep_for(chrono::seconds(2));
        }
    } while (position == -1);


    if (order[customerIndex][position].paid) {
        cout << "\n\n\n**---*---*=============*---*---**";
        cout << "\n**  This order has already been paid.  **\n\a";
        cout << "\n**---*---*=============*---*---**\a\a";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }
    cout << "\nCustomer ID : " << order[customerIndex][position].customerID << endl;
    cout << "Order ID : " << order[customerIndex][position].orderID << endl;
    cout << "\nItems:\n";
    for (int i = 0; i < order[customerIndex][position].itemCount; i++) {
        for (int j = 0; j < foodcount; j++) {
            string targetID;
            int idNum = order[customerIndex][position].itemID[i];
            if (idNum < 10)
                targetID = "F00" + to_string(idNum);
            else if (idNum < 100)
                targetID = "F0" + to_string(idNum);
            else
                targetID = "F" + to_string(idNum);

            if (menulist[j].id == targetID) {
                cout << "  " << menulist[j].name << " x " << order[customerIndex][position].quantity[i] << " = RM "
                    << fixed << setprecision(2) << menulist[j].price * order[customerIndex][position].quantity[i] << endl;
                break;
            }
        }
    }

    cout << "\nTotal Amount : RM " << fixed << setprecision(2) << order[customerIndex][position].totalAmount << endl;
    cout << "\n\nPayment Method\n";
    cout << "=================================\n";
    cout << "\t1. Cash\n";
    cout << "\t2. Card\n";
    cout << "\t3. E-Wallet\n";
    cout << "=================================\n";

    int method;
    cout << "\nEnter payment method : ";
    cin >> method;

    while (cin.fail() || method < 1 || method > 3) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid choice.\n\a";
        cout << "Please enter payment method again (1-3): ";
        cin >> method;
    }
    if (method == 1) {
        double amount;
        do {
            cout << "\nEnter cash amount : RM ";
            cin >> amount;

            if (cin.fail() || amount < 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input.Please enter again. \n\a";
            }
            else if (amount < order[customerIndex][position].totalAmount) {
                cout << "Insufficient amount.Please enter again. \n\a";
            }

        } while (cin.fail() || amount < order[customerIndex][position].totalAmount);

        double change = amount - order[customerIndex][position].totalAmount;
        cout << "\n\aChange : RM " << fixed << setprecision(2) << change << endl;
        this_thread::sleep_for(chrono::seconds(1));

        order[customerIndex][position].paid = true;
        cout << "\n\n*****************************";
        cout << "\n**   Payment successful.   **\n\a";
        cout << "*****************************\n\n";
    }

    else if (method == 2) {
        order[customerIndex][position].paid = true;
        cout << "\n\n**********************************";
        cout << "\n**   Card payment successful.   **\n\a";
        cout << "**********************************\n\n";
    }
    else if (method == 3) {
        order[customerIndex][position].paid = true;
        cout << "\n\n**************************************";
        cout << "\n**   E-Wallet payment successful.   **\n\a";
        cout << "**************************************\n\n";
    }

    saveOrders();
    this_thread::sleep_for(chrono::seconds(2));
}

void saveOrders() {
    ofstream writefile("orders.txt");

    if (!writefile) {
        return;
    }

    for (int i = 0; i < MAX_CUSTOMER; i++) {
        writefile << orderCount[i] << endl;

        for (int j = 0; j < orderCount[i]; j++) {
            writefile << order[i][j].customerID << endl;
            writefile << order[i][j].orderID << endl;
            writefile << order[i][j].itemCount << endl;

            for (int k = 0; k < MAX_ITEM_PER_ORDER; k++) {
                writefile << order[i][j].itemID[k] << " ";
            }
            writefile << endl;

            for (int k = 0; k < MAX_ITEM_PER_ORDER; k++) {
                writefile << order[i][j].quantity[k] << " ";
            }
            writefile << endl;

            writefile << order[i][j].totalAmount << endl;
            writefile << order[i][j].active << endl;
            writefile << order[i][j].paid << endl;
        }
    }

    writefile.close();
}


void loadOrders() {
    ifstream readfile("orders.txt");

    if (!readfile) {
        return;
    }

    int i = 0;

    while (!readfile.eof() && i < MAX_CUSTOMER) {
        readfile >> orderCount[i];

        if (readfile.eof()) {
            break;
        }

        for (int j = 0; j < orderCount[i] && j < MAX_ORDER; j++) {

            readfile >> order[i][j].customerID;
            readfile >> order[i][j].orderID;
            readfile >> order[i][j].itemCount;

            for (int k = 0; k < MAX_ITEM_PER_ORDER; k++) {
                readfile >> order[i][j].itemID[k];
            }

            for (int k = 0; k < MAX_ITEM_PER_ORDER; k++) {
                readfile >> order[i][j].quantity[k];
            }

            readfile >> order[i][j].totalAmount;
            readfile >> order[i][j].active;
            readfile >> order[i][j].paid;
        }

        i++;
    }

    readfile.close();
}

//student D system
void reportingModule() {
    int reportChoice;
    do {
        cout << "\n==========================================" << endl;
        cout << "         REPORTING MODULE SUBMENU         " << endl;
        cout << "==========================================" << endl;
        cout << "1. Search User Report by ID" << endl;
        cout << "2. Generate Summary Report" << endl;
        cout << "3. Calculate Statistics (Popular Item)" << endl;
        cout << "4. Sort Records (by Sales Amount)" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "==========================================" << endl;
        cout << "Enter choice (1-5): ";


        while (!(cin >> reportChoice)) {
            cout << "[Error] Please enter a valid number (1-5): ";
            cin.clear();
            cin.ignore(100, '\n');
        }

        switch (reportChoice) {
        case 1:
            findUserReport(u, countUser, order, orderCount);
            break;
        case 2:
            generateSummary(order, orderCount, MAX_CUSTOMER);
            break;
        case 3:
            calculateStatistic(order, orderCount, MAX_CUSTOMER, MAX_FOOD);
            break;
        case 4:
            sortRecords(order, orderCount, MAX_CUSTOMER);
            break;
        case 5: cout << "\nReturning to Main Menu..." << endl; break;
        default: cout << "[Invalid] Please enter a number between 1 and 5." << endl;
        }
    } while (reportChoice != 5);
}



int findUserIndex(int targetId, Order arr[], int size);
void displayUserReport(int index);

string itemIDToString(int idNum) {
    if (idNum < 10)
        return "F00" + to_string(idNum);
    else if (idNum < 100)
        return "F0" + to_string(idNum);
    else
        return "F" + to_string(idNum);
}

// =====================================================

// =====================================================
void findUserReport(userrecord uList[], int userCount, Order order[][MAX_ORDER], int orderCount[]) {
    string targetUserID;
    cout << "\n==========================================" << endl;
    cout << "         SEARCH USER REPORT BY USER ID     " << endl;
    cout << "==========================================" << endl;

    do {
        cout << "Enter User ID (e.g., M1234): ";
        cin >> targetUserID;
        if (targetUserID.empty()) {
            cout << "[Error] User ID cannot be empty. Please try again.\n";
        }
    } while (targetUserID.empty());

    int customerIndex = -1;
    for (int idx = 0; idx < userCount; idx++) {
        if (uList[idx].userid == targetUserID) {
            customerIndex = idx;
            break;
        }
    }

    if (customerIndex == -1) {
        cout << "\n[Notice] User ID '" << targetUserID << "' not found in the system.\n";
        return;
    }

    bool found = false;
    int orderCountTotal = 0;

    for (int o = 0; o < orderCount[customerIndex]; o++) {
        if (order[customerIndex][o].active) {
            if (!found) {
                cout << "\n==========================================" << endl;
                cout << "         USER ORDER REPORT                " << endl;
                cout << "==========================================" << endl;
                cout << "User ID    : " << targetUserID << endl;
                cout << "Username   : " << uList[customerIndex].username << endl;
                cout << "==========================================" << endl;
                found = true;
            }

            orderCountTotal++;
            cout << "\n--- Order #" << orderCountTotal << " ---" << endl;
            cout << left << setw(20) << "Order ID" << ": " << order[customerIndex][o].orderID << endl;
            cout << left << setw(20) << "Total Amount" << ": RM " << fixed << setprecision(2) << order[customerIndex][o].totalAmount << endl;
            cout << left << setw(20) << "Payment Status" << ": " << (order[customerIndex][o].paid ? "Paid" : "Not Paid") << endl;
            cout << left << setw(20) << "Items" << ":" << endl;

            for (int itemIdx = 0; itemIdx < order[customerIndex][o].itemCount; itemIdx++) {
                string idStr = itemIDToString(order[customerIndex][o].itemID[itemIdx]);
                int menuIdx = findFoodbyId(idStr);
                if (menuIdx != -1) {
                    cout << "    " << menulist[menuIdx].name << " x " << order[customerIndex][o].quantity[itemIdx]
                        << " = RM " << fixed << setprecision(2)
                        << menulist[menuIdx].price * order[customerIndex][o].quantity[itemIdx] << endl;
                }
                else {
                    cout << "    [Unknown Item ID: " << idStr << "]" << endl;
                }
            }
            cout << "------------------------------------------" << endl;
        }
    }

    if (!found) {
        cout << "\n[Notice] No active orders found for User ID '" << targetUserID << "'.\n";
    }
    else {
        cout << "\n==========================================" << endl;
        cout << "Total Orders Found : " << orderCountTotal << endl;
        cout << "==========================================" << endl;
    }
}

// =====================================================

// =====================================================
void generateSummary(Order order[][MAX_ORDER], int orderCount[], int maxCustomer) {
    int totalOrders = 0;
    double totalRevenue = 0.0;
    for (int c = 0; c < maxCustomer; c++) {
        for (int o = 0; o < orderCount[c]; o++) {
            if (order[c][o].active) {
                totalOrders++;
                totalRevenue += order[c][o].totalAmount;
            }
        }
    }


    if (totalOrders == 0) {
        cout << "\n[Notice] No active orders found. Cannot generate summary.\n";
        return;
    }

    double average = totalRevenue / totalOrders;


    cout << "\n==========================================" << endl;
    cout << "         RESTAURANT SALES SUMMARY         " << endl;
    cout << "==========================================" << endl;
    cout << fixed << setprecision(2);
    cout << left << setw(25) << "Total Active Orders" << ": " << totalOrders << endl;
    cout << left << setw(25) << "Total Revenue" << ": RM " << totalRevenue << endl;
    cout << left << setw(25) << "Average Order Value" << ": RM " << average << endl;
    cout << "==========================================" << endl;


    ofstream outFile("SalesReport.txt");
    if (outFile) {
        outFile << "==========================================" << endl;
        outFile << "         RESTAURANT SALES SUMMARY         " << endl;
        outFile << "==========================================" << endl;
        outFile << fixed << setprecision(2);
        outFile << left << setw(25) << "Total Active Orders" << ": " << totalOrders << "\n";
        outFile << left << setw(25) << "Total Revenue" << ": RM " << totalRevenue << "\n";
        outFile << left << setw(25) << "Average Order Value" << ": RM " << average << "\n";
        outFile << "==========================================" << endl;
        outFile.close();
        cout << "[Bonus] Summary report saved to 'SalesReport.txt'!" << endl;
    }
    else {
        cout << "[Error] Failed to open 'SalesReport.txt' for writing." << endl;
    }
}


void calculateStatistic(Order order[][MAX_ORDER], int orderCount[], int maxCustomer, int maxFood) {

    bool hasOrder = false;
    for (int c = 0; c < maxCustomer; c++) {
        if (orderCount[c] > 0) {
            hasOrder = true;
            break;
        }
    }
    if (!hasOrder) {
        cout << "\n[Notice] No orders available for statistics.\n";
        return;
    }


    struct StatItem {
        string name;
        int totalQty;
    };

    StatItem* stats = new StatItem[maxFood]();
    int statCount = 0;


    for (int c = 0; c < maxCustomer; c++) {
        for (int o = 0; o < orderCount[c]; o++) {
            if (!order[c][o].active) continue;

            for (int itemIdx = 0; itemIdx < order[c][o].itemCount; itemIdx++) {
                string idStr = itemIDToString(order[c][o].itemID[itemIdx]);
                int menuIdx = findFoodbyId(idStr);

                if (menuIdx == -1) continue;

                string itemName = menulist[menuIdx].name;
                int qty = order[c][o].quantity[itemIdx];

                bool found = false;
                for (int j = 0; j < statCount; j++) {
                    if (stats[j].name == itemName) {
                        stats[j].totalQty += qty;
                        found = true;
                        break;
                    }
                }

                if (!found && statCount < maxFood) {
                    stats[statCount].name = itemName;
                    stats[statCount].totalQty = qty;
                    statCount++;
                }
            }
        }
    }

    if (statCount == 0) {
        cout << "\n[Notice] No items found in orders.\n";
        delete[] stats;
        return;
    }

    int maxIdx = 0;
    int totalQtyAll = 0;
    for (int i = 0; i < statCount; i++) {
        totalQtyAll += stats[i].totalQty;
        if (stats[i].totalQty > stats[maxIdx].totalQty) {
            maxIdx = i;
        }
    }

    double percentage = (totalQtyAll > 0) ? (static_cast<double>(stats[maxIdx].totalQty) / totalQtyAll) * 100.0 : 0.0;

    cout << "\n==========================================" << endl;
    cout << "         POPULAR ITEM STATISTICS          " << endl;
    cout << "==========================================" << endl;
    cout << left << setw(22) << "Most Popular Item" << ": " << stats[maxIdx].name << endl;
    cout << left << setw(22) << "Total Quantity Sold" << ": " << stats[maxIdx].totalQty << " units" << endl;
    cout << fixed << setprecision(2);
    cout << left << setw(22) << "Popularity Rate" << ": " << percentage << "%" << endl;
    cout << "==========================================" << endl;

    delete[] stats;
}

void sortRecords(Order order[MAX_CUSTOMER][MAX_ORDER], int orderCount[], int maxCustomer) {
    struct OrderRecord {
        string customerID;
        int orderID;
        double amount;
    };

    const int MAX_RECORDS = 1000;
    OrderRecord records[MAX_RECORDS] = {};
    int recordCount = 0;

    for (int c = 0; c < maxCustomer; c++) {
        for (int o = 0; o < orderCount[c]; o++) {
            if (order[c][o].active && recordCount < MAX_RECORDS) {
                records[recordCount].customerID = order[c][o].customerID;
                records[recordCount].orderID = order[c][o].orderID;
                records[recordCount].amount = order[c][o].totalAmount;
                recordCount++;
            }
        }
    }


    if (recordCount <= 1) {
        cout << "\n[Notice] Not enough active orders to sort (need at least 2).\n";
        return;
    }


    for (int i = 0; i < recordCount - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < recordCount - i - 1; j++) {
            if (records[j].amount < records[j + 1].amount) {
                OrderRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    cout << "\n==============================================" << endl;
    cout << "     ORDERS SORTED BY AMOUNT (HIGH->LOW)      " << endl;
    cout << "==============================================" << endl;
    cout << left << setw(18) << "Customer ID"
        << setw(15) << "Order ID"
        << "Amount" << endl;
    cout << "----------------------------------------------" << endl;
    cout << fixed << setprecision(2);

    for (int i = 0; i < recordCount; i++) {
        cout << left << setw(18) << records[i].customerID
            << setw(15) << records[i].orderID
            << "RM " << records[i].amount << endl;
    }
    cout << "==============================================" << endl;
    cout << "[Success] " << recordCount << " active records successfully sorted." << endl;
}


void initializeDefaultMenu() {
    if (foodcount > 0) return;

    menulist[0] = { "F001", "Chicken Burger", "Main", 8.50, true };
    menulist[1] = { "F002", "Beef Burger", "Main", 10.00, true };
    menulist[2] = { "F003", "French Fries", "Side", 5.00, true };
    menulist[3] = { "F004", "Chicken Rice", "Main", 9.50, true };
    menulist[4] = { "F005", "Fried Rice", "Main", 7.50, true };
    menulist[5] = { "F006", "Spaghetti", "Main", 8.00, true };
    menulist[6] = { "F007", "Chicken Chop", "Main", 12.00, true };
    menulist[7] = { "F008", "Fish and Chips", "Main", 13.00, true };
    menulist[8] = { "F009", "Iced Tea", "Drink", 3.00, true };
    menulist[9] = { "F010", "Orange Juice", "Drink", 4.00, true };

    foodcount = 10;
}




