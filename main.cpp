/*
|================================|
|Muhammad Haseeb Arshad  23i-2578|
|Talha Zaheer            23i-2609| 
|Ali Waseem              23i-2630|
|================================|

        ---> DS-A Semester Project <---
 ---> Smart Traffic Management System Simulator <---

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Node_graphs 
{
  public:
    int id;
    int weight;
    Node_graphs* next;

    Node_graphs(int nodeId, int edgeWeight = 0) 
    {
        id = nodeId;
        weight = edgeWeight;
        next = nullptr;
    }
};