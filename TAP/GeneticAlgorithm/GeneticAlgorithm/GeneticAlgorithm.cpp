#include <iostream>
#include <algorithm>
#include <vector>
#include "Evolution.h"

using namespace std;


int main()
{
    Evolution evolution(20, pair<int, int>(-1, 2), 6, 0.25, 0.01, 50);

    evolution.PrintPopulation();

    return 0;
}