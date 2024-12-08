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

    void rer_cong() 
    {
      for (int i = 0; i < num; i++) 
      {
        for (int j = 0; j < num; j++) 
        {
          if (veh_arr[i][j] > 3) 
          { 
            veh_arr[i][j] = veh_arr[i][j] - 2;
            cout << "Rerouting traffic from ";
            cout << arr_labels[i];
            cout << " to ";
            cout << arr_labels[j];
            cout << " due to congestion.";
            cout << endl; 
          }
        }
      }
    }

        void traffc_signal_csv(const string& filename)//green light times is updated after the data is read 
    {
      string line;
      int nodeId;
      char intersection;
      int gre_time_in_csv;
      ifstream file(filename);
      getline(file, line);//header line skipped
      while (getline(file, line)) 
      {
        stringstream ss(line);
        ss >> intersection;
        ss.ignore();
        ss >> gre_time_in_csv;//green time read

        nodeId = node_id(intersection);//get the node id to the label
        if (nodeId == -1)
        {
           cout << "";
        }
        
        else
        {
           green_times[nodeId] = gre_time_in_csv;//green time updated
        }
      }
      file.close();
    }

    void block_roads_csv(const string& filename) //road closure data is read and marks roads as blocked
    {
      ifstream file(filename);
      if (!file.is_open()) 
      {
        cout << "FAILED to CSV file";
        cout << endl;
        return;
      }

      string line;
      getline(file, line);//skip header line
      while (getline(file, line)) 
      {
        stringstream ss(line);
        char start, end;
        string status;

        ss >> start;
        ss.ignore();
        ss >> end;  
        ss.ignore();  
        getline(ss, status, ',');//road status is read

        if (status == "Under Repair")
        {
            road_blocked(start, end);
        }

        else if (status == "Blocked") 
        {
            road_blocked(start, end);
        }
      }
      file.close();
    }

      int node_id(char node)//node label is mapped to its index creating a new node if necessary. 
    {
      for (int i = 0; i < num; i++) 
      {
        if (arr_labels[i] == node) 
        {
           return i;
         }
      }
      arr_labels[num] = node;
      arr[num] = new Node_graphs(num);
      return num++;//increment and return the new node index.
    }

    void edge_inclusion(int a, int b, int c)//adds an edge between two nodes with a given weight. 
    {
      if (a >= nodes) 
      {
        cout << "Invalid edge." << endl;
        return;
      }
        
      else if (b >= nodes)
      {
        cout << "Invalid edge." << endl;
        return;
      }        

      Node_graphs* newNode = new Node_graphs(b, c);//creates a new adjacency list node
      newNode->next = arr[a]->next;
      arr[a]->next = newNode;
    }

        void road_blocked(char a, char b)//blocks a road between two nodes in the graph
    {
      int c = 0;
      int d = 0;
        
      c = node_id(a);
      d = node_id(b);
      if (c == -1) 
      {
        cout << "Invalid road to block." << endl;
        return;
      }
        
      if (d == -1)
      {
        cout << "Invalid road to block." << endl;
        return;
      }        
      block_road_arr[c][d] = true;//marks the road as blocked in the array
      cout << "Road from ";
      cout << a;
      cout << " to ";
      cout << b;
      cout << " has been blocked";
      cout << endl;
    }

    bool ro_blo(int from, int to)//checks if a road is blocked between two nodes. 
    {
        return block_road_arr[from][to];
    }

        void displayblock_road_arr()//displays all blocked roads in the graph. 
    {
      cout << "------ Blocked Roads ------";
      cout << endl;
      bool b = false;

      for (int i = 0; i < num; i++) 
      {
        for (int j = 0; j < num; j++) 
        {
          if (block_road_arr[i][j]) 
          {
            cout << arr_labels[i];
            cout << " to ";
            cout << arr_labels[j];
            cout << " is blocked";
            cout << endl;
            b = true;
          }
        }
      }

      if (b) 
      {
        cout << "";  
      }
        
      else
      {
        cout << "No blocked roads.";
        cout << endl;
      }
    }

    void graph_disp() 
    {
      cout << "------ City Traffic Network ------";
      cout << endl;
      for (int i = 0; i < num; i++) 
      {
        cout << arr_labels[i];
        cout << " -> ";
        Node_graphs* temp = arr[i];
        bool f = true;
        while (temp -> next) 
        {
          if (f) 
          {
            cout << "";
          }
          
          else
          {
            cout << ", ";
          }
          cout << "(";
          cout << arr_labels[temp->next->id];
          cout << ", ";
          cout << temp->next->weight;
          cout << ")";
          f = false;
          temp = temp->next;
       }
       cout << endl;
      }
    }

    int get_djik_node(int arr_1[], int arr_2[], bool arr_3[])//finds the next node with the minimum distance in Dijkstra's algorithm. 
    {
      int s_1 = 0;
      int s_2 = 0;
      
      s_1 = 1000000;
      s_2 = -1;

      for (int i = 0; i < num; i++) 
      {
        if (!arr_3[i] && (arr_1[i] + arr_2[i]) < s_1) 
        {
          s_1 = arr_1[i] + arr_2[i];
          s_2 = i;
        }
      }
      return s_2;
    }

    void djik_sea(char start, char end)//dijkstras algorithm is implemented here 
    {
       int arr_dist[26];
       int arr_set[26];
       bool arr_flag[26] = {false};
       int parent_num[26];
       int st = node_id(start);
       int en = node_id(end);
  
       if (st == -1) 
       {
         cout << "Invalid node MARKS";
         cout << endl;
         return;
       }
      
       if (en == -1)
       {
         cout << "Invalid node labels";
         cout << endl;
         return;
       }
  
       for (int i = 0; i < num; i++) 
       {
         arr_dist[i] = 1000000;
         arr_set[i] = 0;//Use 0 arr_set for now or a meaningful value.
         parent_num[i] = -1;
       }
       arr_dist[st] = 0;

       for (int cou = 0; cou < num; cou++) 
       {
         int u = get_djik_node(arr_dist, arr_set, arr_flag);
         if (u == -1)//no node can be reached
         {
           break;
         }
         arr_flag[u] = true;

         if (u == en)
         {
           break;//here if we have reached the target node, break
         }

         Node_graphs* temp = arr[u];//start from the head of the adjacency list
         while (temp != nullptr)//here I traverse through the adjacency list 
         {          
           int v = temp->id;
           int weight = temp->weight;

           if (ro_blo(u, v))//here I skip if the road is blocked 
           {
             temp = temp->next; 
             continue;
           }

           if (!arr_flag[v] && arr_dist[u] != 1000000 && arr_dist[u] + weight < arr_dist[v])//relaxation step 
           {
             arr_dist[v] = arr_dist[u] + weight;
             parent_num[v] = u;
           }
           temp = temp->next;
         }
      }

      if (arr_dist[en] == 1000000) 
      {
        cout << "There is NO existent path between --> ";
        cout << start;
        cout << " <-- and --> ";
        cout << end;
        cout << " <--";
        cout << endl;
        return;
      } 
      
      cout << "Emergency Vehicle is being routed..." << endl;
      cout << "Emergency Vehicle path: ";
      path_print_all(en, parent_num);
    }

    void path_print_all(int node, int parent_num[])//helper function to priny from source to target 
    {
      int nu = -1;
      if (parent_num[node] == nu) 
      {
        cout << arr_labels[node];
        return;
      }
      path_print_all(parent_num[node], parent_num);
      cout << " -> ";
      cout << arr_labels[node];
    }      