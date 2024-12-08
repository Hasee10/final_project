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

class Graph 
{
  private:
    Node_graphs** arr;//array of adjacency lists of graph representation
    int num;//number of nodes added to the graph.
    int green_times[26];//array to store green light timings for traffic signals
    int nodes;//maximum number of nodes in the graph.
    char arr_labels[26];//array that maps node indices to their corresponding labels
    bool block_road_arr[26][26];//array to store blocked road status between intersections.
    int veh_arr[26][26];//vehicle count for congestion monitoring

  public:

    Graph(int n) 
    {
      nodes = n;
      char chr = '\0';
      arr = new Node_graphs*[nodes];
      for (int i = 0; i < nodes; i++) 
      {
        arr[i] = nullptr;
        green_times[i] = 30;//default set to 30
        for (int j = 0; j < nodes; j++) 
        {
           block_road_arr[i][j] = false;// all roads are intialised as unblocked
           veh_arr[i][j] = 0;
        }
      }
      num = 0;//total number of nodes to be added in the graph are intialized
      for (int i = 0; i < 26; i++) 
      {
         arr_labels[i] = chr;
      }
    }