/*
 * CHAPTER 13, PROJECT 15
 * CS 151
 * Tu 5:30-9:20 with Porto
 * Programmer: Jay Montoya
 *
 * PROBLEM STATEMENT:
 *     Write a program that uses a structure to store the following
 *     inventory information in a file:
 *          Item description
 *          Quantity on hand
 *          Wholesale cost
 *          Retail cost
 *          Date added to inventory
 *
 *     The program should have a menu that allows the user to perform
 *     the following tasks:
 *          Add new records to the file
 *          Display any record in the file
 *          Change any record in the file
 *
 *
 *
 */
#include <iostream>
#include <fstream>
using namespace std;


// a struct to read and write
struct Item
{
    char description[100];
    int quantity;
    double wholesaleCost;
    double retailCost;
    char dateAdded[11];
};

int main() {


    string fileName;
    int choice, numRecords, targetRecord;

    // load up some pre-installed database values
    cout << "loading database..." << endl;
    struct Item loadThis1 = {"Toaster", 3, 19.99, 29.99, "05/20/2019"};
    struct Item loadThis2 = {"Lamp", 12, 24.99, 29.99, "05/20/2019"};
    struct Item loadThis3 = {"Backpack", 15, 19.99, 39.99, "05/20/2019"};
    numRecords = 3;


    // create the file stream
    fstream inventory("database.dat", ios::in | ios::out | ios::binary);
    if (!inventory) { cout << "Error bootstrapping database!" << endl; return 0; }

    inventory.write(reinterpret_cast<char *>(&loadThis1), sizeof(loadThis1));
    inventory.write(reinterpret_cast<char *>(&loadThis2), sizeof(loadThis2));
    inventory.write(reinterpret_cast<char *>(&loadThis3), sizeof(loadThis3));
    inventory.flush();

    cout << "Welcome to the demo of project 15!" << endl;
    cout << "Connecting to the database..." << endl;

    do {

        struct Item record;

        cout << "\n\n\tMAIN MENU Please select an option below:" << endl;
        cout << "\t\t1) Add a new record to the file" << endl;
        cout << "\t\t2) Display a particular record" << endl;
        cout << "\t\t3) Display all records" << endl;
        cout << "\t\t4) Change a particular record" << endl;
        cout << "\t\t\tYOUR SELECTION (-1 to exit): ";

        // user input
        cin >> choice;

        // switch statement
        switch (choice) {
            case 1:
                cout << "\n\nEnter a brief description of the object: ";
                cin.ignore();
                cin.getline(record.description, 100);
                cout << "Enter the quanity in stock: ";
                cin >> record.quantity;
                cout << "Enter the wholesale cost: ";
                cin >> record.wholesaleCost;
                cout << "Enter the retail cost: ";
                cin >> record.retailCost;
                cout << "What is todays date? (dd/mm/yyyy): ";
                cin.ignore();
                cin.getline(record.dateAdded, 11);

                // write the record
                cout << "\t\tWriting record..." << endl;

                // Move to the right place in the file and write the record
                inventory.seekp(numRecords * sizeof(record), ios::beg);
                inventory.write(reinterpret_cast<char *>(&record), sizeof(record));
                inventory.flush();
                cout << "\t\tRecord written successfully!" << endl;
                numRecords++;
                break;
            case 2:
                cout << "\n\nWhich record number would you like to view?:";
                cin >> targetRecord;

                // seek to that record
                inventory.seekg((targetRecord -1) * sizeof(record), ios::beg);

                // read the record
                inventory.read(reinterpret_cast<char *>(&record), sizeof(record));

                // display the record contents
                cout << "\n\t\tDESCRIPTION: " << record.description << endl;
                cout << "\t\tQUANTITY: " << record.quantity << endl;
                cout << "\t\tWHOLESALE PRICE: " << record.wholesaleCost << endl;
                cout << "\t\tRETAIL PRICE: " << record.retailCost << endl;
                cout << "\t\tDATE ADDED: " << record.dateAdded << endl;
                break;
            case 3:
                // seek to the beginning
                inventory.seekg(0, ios::beg);

                while (!inventory.eof()) {
                    // read the record
                    inventory.read(reinterpret_cast<char *>(&record), sizeof(record));

                    if (inventory.eof()) {
                        break;
                    }

                    // display the record contents
                    cout << "\n\t\tDESCRIPTION: " << record.description << endl;
                    cout << "\t\tQUANTITY: " << record.quantity << endl;
                    cout << "\t\tWHOLESALE PRICE: " << record.wholesaleCost << endl;
                    cout << "\t\tRETAIL PRICE: " << record.retailCost << endl;
                    cout << "\t\tDATE ADDED: " << record.dateAdded << endl;
                }

                inventory.clear();
                break;
            case 4:
                cout << "\n\nWhich record number would you like to edit?:";
                cin >> targetRecord;

                // seek to that record
                inventory.seekg((targetRecord-1) * sizeof(record), ios::beg);

                // read the record
                inventory.read(reinterpret_cast<char *>(&record), sizeof(record));

                // edit the parts
                cout << "\n\t\tEnter the updated description: ";
                cin.ignore();
                cin.getline(record.description, 100);
                cout << "\t\tEnter the updated quantity: ";
                cin >> record.quantity;
                cout << "\t\tEnter the updated wholesale price: ";
                cin >> record.wholesaleCost;
                cout << "\t\tEnter the updated retail price: ";
                cin >> record.retailCost;
                cout << "\t\tWhat is today's date?: ";
                cin.ignore();
                cin.getline(record.dateAdded, 11);

                // move to the right record
                inventory.seekp((targetRecord-1) * sizeof(record), ios::beg);
                inventory.write(reinterpret_cast<char *>(&record), sizeof(record));
                inventory.flush();
                break;
        }
    } while (choice != -1);

    cout << "This concludes the demo!" << endl;

    inventory.close();
    return 0;
}