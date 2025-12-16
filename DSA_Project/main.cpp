#include "CityGraph.h"
#include "Admin.h"
#include "User.h"
#include <limits>

int main() {
    int role;

    do {
        cout << "\n========================================\n";
        cout << "      SMART CITY NAVIGATION SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Admin Login\n";
        cout << "2. User\n";
        cout << "3. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Select option: ";
        if (!(cin >> role)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (role) {
            case 1: adminLogin(); break;
            case 2: userMenu(); break;
            case 3: cout << "\nProgram terminated successfully.\n"; break;
            default: cout << "\nInvalid option!\n";
        }
    } while (role != 3);

    return 0;
}
