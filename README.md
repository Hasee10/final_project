# Smart Traffic Management System Simulator

## Table of Contents
1. [Introduction](#introduction)
2. [Classes](#classes)
   - [Node_graphs](#node_graphs)
   - [Graph](#graph)
3. [Main Function](#main-function)
4. [Detailed Function Descriptions](#detailed-function-descriptions)
   - [Graph Class Methods](#graph-class-methods)
5. [Usage](#usage)
6. [Conclusion](#conclusion)

## Introduction

The Smart Traffic Management System Simulator is a C++ program designed to simulate and manage traffic in a city network. The system uses a graph data structure to represent the city's road network, where intersections are nodes and roads are edges with weights representing travel times. The simulator provides functionalities to manage traffic signals, detect congestion, block roads, and route emergency vehicles efficiently.

## Classes

### Node_graphs

The `Node_graphs` class represents a node in the adjacency list of the graph. Each node has:
- `id`: The identifier of the node.
- `weight`: The weight of the edge connecting this node to another.
- `next`: A pointer to the next node in the adjacency list.

```cpp
class Node_graphs {
  public:
    int id;
    int weight;
    Node_graphs* next;

    Node_graphs(int nodeId, int edgeWeight = 0) {
        id = nodeId;
        weight = edgeWeight;
        next = nullptr;
    }
};
```

### Graph

The `Graph` class represents the city's traffic network using an adjacency list. It includes methods to manage the graph, traffic signals, congestion, and road blocks.

```cpp
class Graph {
  private:
    Node_graphs** arr; // Array of adjacency lists
    int num; // Number of nodes added to the graph
    int green_times[26]; // Array to store green light timings
    int nodes; // Maximum number of nodes in the graph
    char arr_labels[26]; // Array that maps node indices to their corresponding labels
    bool block_road_arr[26][26]; // Array to store blocked road status
    int veh_arr[26][26]; // Vehicle count for congestion monitoring

  public:
    // Constructor and methods...
};
```

## Main Function

The `main` function initializes the graph, reads data from CSV files, and provides a menu-driven interface for the user to interact with the traffic management system.

```cpp
int main() {
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
    while (choi != nu_1) {
        // Display menu and handle user choices
    }
    return 0;
}
```

## Detailed Function Descriptions

### Graph Class Methods

#### Constructor

```cpp
Graph(int n);
```

- **Description**: Initializes the graph with a specified number of nodes.
- **Parameters**:
  - `n`: Maximum number of nodes in the graph.

#### upd_veh

```cpp
void upd_veh(char from, char to, int cou);
```

- **Description**: Updates the vehicle count on a road.
- **Parameters**:
  - `from`: Starting intersection.
  - `to`: Ending intersection.
  - `cou`: Number of vehicles to add.

#### disp_conges

```cpp
void disp_conges();
```

- **Description**: Displays the current congestion status of the roads.

#### rer_cong

```cpp
void rer_cong();
```

- **Description**: Reroutes traffic if congestion is detected.

#### traffc_signal_csv

```cpp
void traffc_signal_csv(const string& filename);
```

- **Description**: Reads and updates traffic signal timings from a CSV file.
- **Parameters**:
  - `filename`: Path to the CSV file.

#### block_roads_csv

```cpp
void block_roads_csv(const string& filename);
```

- **Description**: Reads and updates road closure data from a CSV file.
- **Parameters**:
  - `filename`: Path to the CSV file.

#### node_id

```cpp
int node_id(char node);
```

- **Description**: Maps a node label to its index in the graph.
- **Parameters**:
  - `node`: Node label.
- **Returns**: Index of the node.

#### edge_inclusion

```cpp
void edge_inclusion(int a, int b, int c);
```

- **Description**: Adds an edge between two nodes with a given weight.
- **Parameters**:
  - `a`: Start node.
  - `b`: End node.
  - `c`: Weight of the edge.

#### road_blocked

```cpp
void road_blocked(char a, char b);
```

- **Description**: Blocks a road between two intersections.
- **Parameters**:
  - `a`: Start intersection.
  - `b`: End intersection.

#### ro_blo

```cpp
bool ro_blo(int from, int to);
```

- **Description**: Checks if a road is blocked.
- **Parameters**:
  - `from`: Start node.
  - `to`: End node.
- **Returns**: `true` if the road is blocked, `false` otherwise.

#### displayblock_road_arr

```cpp
void displayblock_road_arr();
```

- **Description**: Displays all blocked roads.

#### graph_disp

```cpp
void graph_disp();
```

- **Description**: Displays the city traffic network.

#### get_djik_node

```cpp
int get_djik_node(int arr_1[], int arr_2[], bool arr_3[]);
```

- **Description**: Finds the next node with the minimum distance in Dijkstra's algorithm.
- **Parameters**:
  - `arr_1[]`: Array of distances.
  - `arr_2[]`: Array of weights.
  - `arr_3[]`: Array of visited nodes.
- **Returns**: Index of the next node.

#### djik_sea

```cpp
void djik_sea(char start, char end);
```

- **Description**: Implements Dijkstra's algorithm to find the shortest path for an emergency vehicle.
- **Parameters**:
  - `start`: Starting intersection.
  - `end`: Ending intersection.

#### path_print_all

```cpp
void path_print_all(int node, int parent_num[]);
```

- **Description**: Prints the path from the source to the target node.
- **Parameters**:
  - `node`: Current node.
  - `parent_num[]`: Array of parent nodes.

#### gree_ligh_disp

```cpp
void gree_ligh_disp();
```

- **Description**: Displays the green light durations for all intersections.

#### find_paths

```cpp
void find_paths(char a, char b);
```

- **Description**: Finds all paths between two intersections using DFS.
- **Parameters**:
  - `a`: Start intersection.
  - `b`: End intersection.

#### find_path_help

```cpp
void find_path_help(int c, int end, bool arr_flag[], string path, int t_w, int& p_c);
```

- **Description**: Helper function to find paths between two nodes.
- **Parameters**:
  - `c`: Current node.
  - `end`: End node.
  - `arr_flag[]`: Array of visited nodes.
  - `path`: Current path.
  - `t_w`: Total weight.
  - `p_c`: Path count.

#### read_csv

```cpp
void read_csv(const string& filename);
```

- **Description**: Reads graph edges from a CSV file.
- **Parameters**:
  - `filename`: Path to the CSV file.

## Usage

1. **Compile the Program**: Use a C++ compiler to compile the `main.cpp` file.
2. **Run the Program**: Execute the compiled program.
3. **Interact with the Menu**: Follow the on-screen instructions to manage the traffic network.

## Conclusion

The Smart Traffic Management System Simulator provides a comprehensive tool for managing and simulating traffic in a city network. It leverages graph algorithms to efficiently route vehicles, manage traffic signals, and handle road closures. The system is designed to be user-friendly, with a menu-driven interface that allows users to interact with various functionalities.
