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

    void gree_ligh_disp()//green light durations for all intersections are displayed here 
    {
      cout << "------Traffic Signal Status------";
      cout << endl;
      for (int i = 0; i < num; i++) 
      {
        cout << "Intersection ";
        cout << arr_labels[i];
        cout << " Green Time : ";
        cout << green_times[i];
        cout << " s";
        cout << endl;
      }
    }
    
    void find_paths(char a, char b)//Finds all paths between two nodes using DFS. 
    {
      bool arr_flag[26] = {false};
      string path = "";
      int t_w = 0;
      int p_c = 0;
      int st = 0;
      int en = 0;
      
      st = node_id(a);
      en = node_id(b);

      cout << "All possible paths from";
      cout << endl;
      cout << a;
      cout << " to ";
      cout << b;
      cout << " are";
      cout << endl;
      find_path_help(st, en, arr_flag, path, t_w, p_c);

      if (p_c == 0) 
      {
        cout << "No paths exist between ";
        cout << a;
        cout << " and ";
        cout << b;
        cout << endl;
      }
    }

    void find_path_help(int c, int end, bool arr_flag[], string path, int t_w, int& p_c)//helper to find paths between two nodes. 
    {
      arr_flag[c] = true;
      path = path + arr_labels[c];
      path = path + " ";

      if (c != end) 
      {
        cout << "";
      }
      
      else
      {
        cout << "Path ";
        cout << ++p_c;
        cout << ": ";
        cout << path;
        cout << "| ";
        cout << "Total Weight: ";
        cout << t_w;
        cout << endl;
        arr_flag[c] = false;
        return;
      }

      Node_graphs* temp = arr[c];
      while (temp != nullptr) 
      {
        if (!arr_flag[temp->id]) 
        {
          find_path_help(temp->id, end, arr_flag, path, t_w + temp->weight, p_c);
        }
        temp = temp->next;
      }
      arr_flag[c] = false;
    }
    
    void read_csv(const string& filename)//graph edged fro the csv file are read here 
    {
      ifstream file(filename);
      if (!file.is_open()) 
      {
        cout << "Failed to open file." << endl;
        return;
      }

      string line;
      getline(file, line);//header line is skipped here
      while (getline(file, line)) 
      {
        stringstream ss(line);
        char from, to;
        int weight;

        ss >> from;
        ss.ignore();
        ss >> to;
        ss.ignore();
        ss >> weight;

        int s_1 = node_id(from);
        int s_2 = node_id(to);
        if (s_1 != -1 && s_2 != -1) 
        {
           edge_inclusion(s_1, s_2, weight);
        }
      }
      file.close();
    }    
};


int main() 
{
    int choi = 0;
    int nu_1 = 8;
    int t_ns = 26;
    Graph graph(t_ns);

    string roadFilename = "road_network.csv";
    graph.read_csv(roadFilename);

    string signalFilename = "traffic_signals.csv";
    graph.traffc_signal_csv(signalFilename);

    string roadClosuresFilename = "road_closures.csv";
    graph.block_roads_csv(roadClosuresFilename);

    char start;
    char end;
    while (choi != nu_1) 
    {
        cout << "======================================";
        cout << endl;
        cout << "----- Simulation -----";
        cout << endl;
        cout << "1. Display City Traffic Network";
        cout << endl;
        cout << "2. Display Traffic Signal Status";             
        cout << endl;
        cout << "3. Display Congestion Status";    
        cout << endl;
        cout << "4. Display Blocked Roads";
        cout << endl;
        cout << "5. Handle Emergency Routing";
        cout << endl;
        cout << "6. Block Road due to Accident";
        cout << endl;
        cout << "7. Simulate Vehicle Routing";
        cout << endl;
        cout << "8. Exit";
        cout << endl;
        cout << "======================================";
        cout << endl;
        cout << endl;
        
        cout << "Enter your CHOICE --> ";
        cin >> choi;

        switch (choi) 
        {
            case 1:
                cout << endl;
                cout << endl;
                graph.graph_disp();
                cout << endl;
                cout << endl;
                break;

            case 2:
                cout << endl;
                graph.gree_ligh_disp();
                cout << endl;
                cout << endl;
                break;
            
            case 3:
                cout << endl;
                graph.disp_conges();
                cout << endl;
                cout << endl;
                break;

            case 4:
                cout << endl;
                graph.displayblock_road_arr();
                cout << endl;
                cout << endl;
                break;

            case 5:
                cout << endl;
                cout << "Enter start and end intersections for emergency vehicle --> ";
                cin >> start;
                cin >> end;            
                graph.djik_sea(start, end);
                cout << endl;
                cout << endl;
                break;

            case 6:
                cout << endl;
                cout << "Enter road to block (start, end) --> ";                                
                cin >> start;                                                
                cin >> end;                     
                graph.road_blocked(start, end);
                cout << endl;
                cout << endl;
                break;

            case 7:
                cout << endl;     
                cout << "Simulating vehicle routing...";
                cout << endl;     

                cout << "Enter starting intersection: ";
                cin >> start;

                cout << "Enter ending intersection: ";
                cin >> end;     

                graph.find_paths(start, end);
                cout << endl;
                cout << endl;
                break;

            case 8:
                cout << "Exiting Simulation...";
                cout << endl;                     
                break;

            default:
                cout << endl;     
                cout << "-->Enter a number between 1 and 8 ONLY<--";
                cout << endl;                     
                break;
        }
    }
    return 0;
}