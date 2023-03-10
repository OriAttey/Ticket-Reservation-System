#include <iostream>
#include <fstream>
#include <cctype>
#include<iomanip>
#include <string>
#include <sstream>

using namespace std;

//functions prototype
bool inputValidation(string input);
void displayAuditorium();
void reserveSeats(string row, string seat, string adult_num, string senior_num, string child_num);
bool checkAvailability(string row, string seat, int total_quantity);
void displayReport();
string bestAvailable(string row, int totalQuantity);

int main()
{
    string item, infile;
    string row, seat_letter, adult_num, senior_num, child_num, input;
    int total_quantity = 0;
    bool isValid = true;

    // user Interface and Input
    cout << "\t MENU" << endl << " 1. Reserve Seats \n 2. Exit " << endl;
    do
    {
        //prompt the user for a selection
        cout << " \n Option: ";
        cin >> input;
    } while (input.compare("1") != 0 && input.compare("2") != 0);

    if (input.compare("2") == 0)
        exit(0);

    do {
        displayAuditorium();

        do {
               cout << "\nPlease enter reservation information: \n" << endl << "Row Number: ";
               cin >> row;
               cout << "Starting Seat Number: ";
               cin >> seat_letter;
               cout << "Number of Adult Tickets: ";
               cin >> adult_num;
               cout << "Number of Child Tickets: ";
               cin >> child_num;
               cout << "Number of Senior Tickets: ";
               cin >> senior_num;
               cout <<endl;

            isValid = inputValidation(row + "," + seat_letter + "," + adult_num + "," + child_num + "," + senior_num);

            if (!isValid) {
                cout << "\nInvalid Input! \n";
            }
        } while (!isValid);

        total_quantity = stoi(adult_num) + stoi(child_num) + stoi(senior_num);

        if (checkAvailability(row, seat_letter, total_quantity)) {
            reserveSeats(row, seat_letter, adult_num, senior_num, child_num);
            cout << "Seats reserved successfully! Have fun!\n" << endl;
            displayReport();
        }
        else {
            seat_letter = bestAvailable(row, total_quantity);

            //no alternative seating available
            if (seat_letter.compare("-1") == 0) {
                cout << "Sorry, seats are unavailable and no alternative seating can be found on the same row." << endl;
            }
            else {
                do {
                     cout << "Seats unavailable.\nNext best available seat on the requested row are from seat number: " << seat_letter << endl;
                     cout << "Would you like to reserve the next best seats? (Y/N) ";
                     cin >> input;
                } while (input.compare("Y") != 0 && input.compare("N") != 0 && input.compare("y") != 0 && input.compare("n") != 0);

                if (input.compare("Y") == 0 || input.compare("y") == 0) {
                    reserveSeats(row, seat_letter, adult_num, senior_num, child_num);
                     cout << "\nSeats reserved successfully! Have fun!\n" << endl;
                    displayReport();
                }
            }
        }

         cout << "\n\t MENU" << endl;
        // user Interface and Input
         cout << "\n1. Reserve Seats \n2. Exit " << endl;
        do
        {
            //prompt the user for a selection
            cout << " \n Please enter a number to reserve a seat or exit the program : ";
            cin >> input;
        } while (input.compare("1") != 0 && input.compare("2") != 0);

         cout << "\n";
    } while (input.compare("2") != 0);

    return 0;
}



bool isNumber(const string& s)
{
    for (unsigned int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

int totalColumns() {
    fstream inputFile;
    inputFile.open("A1.txt", ios::in);
    bool firstRow = true;
    char ch;
    int total_columns = 0;

    //reading the first row once to find out the total number of columns
    do {
        inputFile >> noskipws >> ch;
        if (ch == '\n' || ch == '\0' || ch == '\r') {
            firstRow = false;
        }
        else if (ch == '.' || ch == 'A' || ch == 'C' || ch == 'S') {
            total_columns++;
        }
        else {
               cout << "\nInput File not Valid! \n";

               cin.get();
            exit(0);
        }
    } while (firstRow);
    inputFile.close();
    return total_columns;
}

int totalRows() {
    fstream inputFile;
    inputFile.open("A1.txt", ios::in);
    int total_rows = 0;
    string item;

    while (!inputFile.eof()) {
        getline(inputFile, item);
        total_rows++;
    }

    if (total_rows == 0) {
        cout << "\nInput File not Valid! \n";
        cout << "Press Any key to Exit";
        cin.get();
        exit(0);
    }
    inputFile.close();
    return total_rows;
}



void displayAuditorium()
{
    fstream inputFile;
    inputFile.open("A1.txt", ios::in);
    string line;
    int total_columns = totalColumns();
    // char ch;
    int rows = 0;
      cout << setw(25) << "Auditorium \n" << endl;
      cout << setw(9);

    //print the column headers
    for (char i = 'A'; i < 'A' + total_columns; i++) {
        cout << i;
    }

    cout << endl;

    //resetting the file pointer to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    //reading the file again and printing row by row
    while (!inputFile.eof())
    {
        rows++;
        cout << setw(5) << rows << "   ";
        getline(inputFile, line);

        for (int i = 0; i < total_columns; i++)
        {
            if (line[i] == 'A' || line[i] == 'C' || line[i] == 'S') {
                line[i] = '#';
            }
            cout << line[i];
        }
        cout << endl;
    }
    inputFile.close();
}

bool inputValidation(string input) {
    stringstream ss(input);
    string token;
    int total_rows = totalRows(), total_columns = totalColumns();
    int i = 0, tempInput;

    while (getline(ss, token, ','))
    {
        //validating row
        if (i == 0) {
            if (isNumber(token)) {
                tempInput = stoi(token);
                if (tempInput < 1 || tempInput > total_rows) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        //validating seat letter
        else if (i == 1) {
            bool isValid = false;
            for (char j = 'a'; j < 'a' + total_columns; j++) {
                string s1(1, toupper(j));
                string s2(1, j);
                if (token.compare(s1) == 0 || token.compare(s2) == 0) {
                    isValid = true;
                    break;
                }
            }
            if (!isValid) {
                return false;
            }
        }
        //validating tickets
        else if (i == 2 || i == 3 || i == 4) {
            if (isNumber(token)) {
                tempInput = stoi(token);
                if (tempInput < 0 || tempInput > total_columns) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
        i++;
    }
    return true;
}

// function to track the availability of seats
bool checkAvailability(string row, string seat, int total_quantity)
{
    fstream inputFile;
    string line;
    inputFile.open("A1.txt", ios::in);

    char ch;
    int total_columns = totalColumns();


    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    char seat_letter = seat[0];

    int temp = toupper(seat_letter);

    inputFile.seekp((stoi(row) - 1)*total_columns + temp - 65);

    for (int i = 0; i < total_quantity; i++)
    {
        inputFile.get(ch);

        if (ch != '.') {
            return false;
        }
    }
    inputFile.close();
    return true;
}

// function to get the best available seat
string bestAvailable(string row, int total_quantity)
{
    fstream inputFile;
    string line, seat_letter = "A";
    inputFile.open("A1.txt", ios::in);
    double pos = inputFile.tellp();
    char ch;
    bool allEmpty = true;
    int shortest_distance = 27;
    int new_distance = 0;
    int total_columns = totalColumns();

    getline(inputFile, line);
    //resetting the file pointer to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    //checking row for empty seats
    for (int i = 0; i < total_columns - total_quantity + 1; i++)
    {
        //moving pointer to position
        inputFile.seekp(pos + ((stoi(row) - 1)*total_columns + i));

        for (int j = i; j < i+total_quantity; j++) {
            inputFile.get(ch);

            if (ch != '.') {
                allEmpty = false;
                i = j;
                break;
            }
        }

        if (allEmpty)
            {
            new_distance = i + (total_quantity - 1) / 2 - (total_columns + 1) / 2;
            if (new_distance < shortest_distance)
             {
                shortest_distance = new_distance;
                seat_letter = (char)(i + 65);
            }
         }
        allEmpty = true;
    }

    //for unavaialable seats found
    if (shortest_distance == 27)
      {
        return "-1";
    }

    inputFile.close();
    return seat_letter;
}

// function to allow user to reserve a seat
void reserveSeats(string row, string seat, string adult_num, string senior_num, string child_num)
{
    fstream inputFile;
    string line;
    inputFile.open("A1.txt");
    long pos;


    //resetting the file pointer to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, ios::beg);
    pos = inputFile.tellp();

    char seat_letter = seat[0];

    int temp = toupper(seat_letter);

    inputFile.seekp(pos + ((stoi(row) - 1)*totalColumns() + temp - 65));


    for (int i = 0; i < stoi(adult_num); i++)
    {
        inputFile.write("A",1);
        pos++;
    }

    for (int i = 0; i < stoi(child_num); i++)
    {
        inputFile.write("C", 1);
        pos++;
    }

    for (int i = 0; i < stoi(senior_num); i++)
    {
        inputFile.write("S", 1);
        pos++;
    }

    inputFile.close();
}

// dispzlay function to display all the total from the ticket selling
void displayReport()
{
    fstream inputFile;
    string line;
    int total_seats = 0, total_sold = 0, adult_sold = 0, child_sold = 0, senior_sold = 0;
    double total_sales = 0;
	int total_columns = totalColumns();

    inputFile.open("A1.txt", ios::in);

    while (!inputFile.eof()) {
        getline(inputFile, line);

        for (int i = 0; i < total_columns; i++) {
            if (line[i] == 'A') {
                adult_sold++;
            }
            if (line[i] == 'C') {
                child_sold++;
            }
            if (line[i] == 'S') {
                senior_sold++;
            }
            if (line[i] == '.') {
                total_seats++;
            }
        }
    }

    total_seats += child_sold + adult_sold + senior_sold;
    total_sold = child_sold + adult_sold + senior_sold;
    total_sales = child_sold*5 + adult_sold*10 + senior_sold*7.5;

    cout << setw(20) << "REPORT\n" <<endl;
    cout << setw(20) << left << "Total Seats in Auditorium: " << setw(10) << right << total_seats << endl;
    cout << setw(20) << left << "Total Tickets Sold: " << setw(10) << right << total_sold << endl;
    cout << setw(20) << left << "Adult Tickets Sold: " << setw(10) << right << adult_sold << endl;
    cout << setw(20) << left << "Child Tickets Sold: " << setw(10) << right << child_sold << endl;
    cout << setw(20) << left << "Senior Tickets Sold: " << setw(10) << right << senior_sold << endl;

    stringstream stream;
    stream << fixed << setprecision(2) << total_sales;
    string s = stream.str();
    cout << setw(30) << left << "Total Tickets Sold: " << setw(10) << right << "$ " + s << endl;

    inputFile.close();
}



