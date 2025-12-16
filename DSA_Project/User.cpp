#include "User.h"
#include <limits>

void userMenu() {
    int choice;
    do {
        cout << "\n========== USER PANEL ==========\n";
        cout << "1. List All Cities\n";
        cout << "2. Find Shortest Path\n";
        cout << "3. Show Reachable Cities (BFS)\n";
        cout << "4. Display ASCII City Map\n";
        cout << "5. Back\n";
        cout << "-------------------------------\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: listCities(); break;
            case 2: shortestPath(); break;
            case 3: bfsTraversal(); break;
            case 4: displayAsciiMap(); break;
            case 5: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}
