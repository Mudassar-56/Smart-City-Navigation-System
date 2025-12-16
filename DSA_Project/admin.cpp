#include "Admin.h"
#include <limits>

void adminLogin() {
    string password;
    cout << "\nEnter admin password: ";
    cin >> password;

    if (password == ADMIN_PASSWORD) {
        cout << "Access Granted.\n";
        adminMenu();
    } else {
        cout << "Incorrect Password! Access Denied.\n";
    }
}

void adminMenu() {
    int choice;
    do {
        cout << "\n========== ADMIN PANEL ==========\n";
        cout << "1. Add City (with Coordinates)\n";
        cout << "2. Connect Cities (Auto Distance)\n";
        cout << "3. Display Adjacency Matrix\n";
        cout << "4. List All Cities\n";
        cout << "5. Show Reachable Cities (BFS)\n";
        cout << "6. Display ASCII City Map\n";
        cout << "7. Export Graph to File\n";
        cout << "8. Back\n";
        cout << "--------------------------------\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: addCity(); break;
            case 2: connectCities(); break;
            case 3: displayCityMap(); break;
            case 4: listCities(); break;
            case 5: bfsTraversal(); break;
            case 6: displayAsciiMap(); break;
            case 7: exportGraphToFile(); break;
            case 8: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 8);
}
