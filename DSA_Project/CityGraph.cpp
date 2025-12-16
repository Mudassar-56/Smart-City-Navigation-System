#include "CityGraph.h"
#include <cmath>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

vector<string> cities;
vector<int> xCoord, yCoord;
vector<vector<int>> adjMatrix;

// ================= UTILITY FUNCTIONS =================
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int getCityIndex(string name) {
    name = toLower(name);
    for (int i = 0; i < cities.size(); i++)
        if (toLower(cities[i]) == name)
            return i;
    return -1;
}

int calculateDistance(int i, int j) {
    int dx = xCoord[j] - xCoord[i];
    int dy = yCoord[j] - yCoord[i];
    return round(sqrt(dx * dx + dy * dy));
}

// ================= GRAPH FUNCTIONS =================
void addCity() {
    string name;
    int x, y;

    cout << "\nEnter city name: ";
    cin >> name;

    if (getCityIndex(name) != -1) {
        cout << "City already exists!\n";
        return;
    }

    cout << "Enter X coordinate: ";
    if (!(cin >> x)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input!\n"; return; }
    cout << "Enter Y coordinate: ";
    if (!(cin >> y)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input!\n"; return; }

    cities.push_back(name);
    xCoord.push_back(x);
    yCoord.push_back(y);

    int n = cities.size();
    adjMatrix.resize(n);
    for (int i = 0; i < n; i++)
        adjMatrix[i].resize(n, 0);

    cout << "City added successfully.\n";
}

void connectCities() {
    string c1, c2;
    cout << "\nEnter first city: ";
    cin >> c1;
    cout << "Enter second city: ";
    cin >> c2;

    int i = getCityIndex(c1);
    int j = getCityIndex(c2);

    if (i == -1 || j == -1) {
        cout << "City not found.\n";
        return;
    }

    int distance = calculateDistance(i, j);
    adjMatrix[i][j] = distance;
    adjMatrix[j][i] = distance;

    cout << "Cities connected. Distance = " << distance << " km\n";
}

void listCities() {
    if (cities.empty()) {
        cout << "\nNo cities available.\n";
        return;
    }

    cout << "\n LIST OF CITIES\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < cities.size(); i++) {
        cout << i << ". " << cities[i] << " (" << xCoord[i] << "," << yCoord[i] << ")\n";
    }
}

void displayCityMap() {
    if (cities.empty()) {
        cout << "No cities available.\n";
        return;
    }

    cout << "\nAdjacency Matrix (City Map):\n\n";
    cout << setw(12) << " ";
    for (string c : cities)
        cout << setw(12) << c.substr(0, 10);
    cout << endl;

    for (int i = 0; i < cities.size(); i++) {
        cout << setw(12) << cities[i].substr(0, 10);
        for (int j = 0; j < cities.size(); j++)
            cout << setw(12) << adjMatrix[i][j];
        cout << endl;
    }
}

void displayAsciiMap() {
    cout << "\nASCII CITY MAP (Conceptual View)\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < cities.size(); i++) {
        cout << cities[i] << " --> (" << xCoord[i] << "," << yCoord[i] << ")\n";
    }
}

void shortestPath() {
    string src, dest;
    cout << "\nEnter source city: ";
    cin >> src;
    cout << "Enter destination city: ";
    cin >> dest;

    int s = getCityIndex(src);
    int d = getCityIndex(dest);

    if (s == -1 || d == -1) {
        cout << "Invalid city name.\n";
        return;
    }

    int n = cities.size();
    vector<int> dist(n, INF), visited(n, 0), parent(n, -1);
    dist[s] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1, minDist = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < n; v++)
            if (!visited[v] && adjMatrix[u][v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
            }
    }

    if (dist[d] == INF) {
        cout << "No path exists between " << src << " and " << dest << ".\n";
        return;
    }

    cout << "\nShortest Distance: " << dist[d] << " km\nPath: ";
    vector<int> path;
    for (int v = d; v != -1; v = parent[v])
        path.push_back(v);

    for (int i = path.size() - 1; i >= 0; i--) {
        cout << cities[path[i]];
        if (i) cout << " -> ";
    }
    cout << endl;
}

void bfsTraversal() {
    string startCity;
    cout << "\nEnter starting city: ";
    cin >> startCity;

    int start = getCityIndex(startCity);
    if (start == -1) {
        cout << "City not found.\n";
        return;
    }

    int n = cities.size();
    vector<int> visited(n, 0), queue;
    visited[start] = 1;
    queue.push_back(start);

    cout << "\nReachable Cities from " << startCity << ":\n";

    for (int i = 0; i < queue.size(); i++) {
        int u = queue[i];
        cout << cities[u] << " ";

        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] && !visited[v]) {
                visited[v] = 1;
                queue.push_back(v);
            }
        }
    }
    cout << endl;
}

void exportGraphToFile() {
    if (cities.empty()) {
        cout << "No cities to export.\n";
        return;
    }

    ofstream file("graph.txt");
    if (!file) {
        cout << "Error creating file.\n";
        return;
    }

    int n = cities.size();
    file << n << endl;

    for (int i = 0; i < n; i++)
        file << cities[i] << " " << xCoord[i] << " " << yCoord[i] << endl;

    int edgeCount = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (adjMatrix[i][j] != 0)
                edgeCount++;

    file << edgeCount << endl;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (adjMatrix[i][j] != 0)
                file << cities[i] << " " << cities[j] << " " << adjMatrix[i][j] << endl;

    file.close();
    cout << "Graph exported successfully to graph.txt\n";
}
