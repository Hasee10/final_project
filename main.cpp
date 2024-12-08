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

        void upd_veh(char from, char to, int cou)//here the vehicle count for a road are updated 
    {
      int s_1 = 0;
      int s_2 = 0;
      
      s_1 = node_id(from);
      s_2 = node_id(to);
      
      if (s_1 == -1) 
      {
        cout << "INVALID ROAD" << endl;
        return;
      }
      if (s_2 == -1)
      {
        cout << "INVALID ROAD" << endl;
        return;
      }
      veh_arr[s_1][s_2] += cou;
    }

    void disp_conges() 
    {
      cout << "------ Congestion Status ------" << endl;
      bool c = false;
      for (int i = 0; i < num; i++) 
      {
        for (int j = 0; j < num; j++) 
        {
          if (veh_arr[i][j] > 0) 
          {
            c = true;
            cout << arr_labels[i]; 
            cout << " to ";
            cout << arr_labels[j];
            cout << " -> Vehicles: ";
            cout << veh_arr[i][j];
            cout << endl;            
          }
        }
      }

      if (c)
      {
        cout << "";
      }
      
      else
      {
        cout << "--> No congestion detected <--";
        cout << endl;
      }
    }
