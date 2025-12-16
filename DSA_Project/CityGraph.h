#ifndef CITYGRAPH_H
#define CITYGRAPH_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define INF 9999

// ================= GLOBAL DATA =================
extern vector<string> cities;
extern vector<int> xCoord, yCoord;
extern vector<vector<int>> adjMatrix;

// ================= FUNCTION DECLARATIONS =================
int calculateDistance(int i, int j);
int getCityIndex(string name);
string toLower(string s);

void addCity();
void connectCities();
void listCities();
void displayCityMap();
void displayAsciiMap();

void shortestPath();
void bfsTraversal();
void exportGraphToFile();

#endif
