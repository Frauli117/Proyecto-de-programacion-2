#pragma once
#include <sstream> 
#include <vector>
#include <fstream>
#include "RouteList.h"

using namespace std;

class RouteFileManager {
public:
    static void saveRoutesToFile(const string& filename, RouteList& routeList);
    static void loadRoutesFromFile(const string& filename, RouteList& routeList);
};

