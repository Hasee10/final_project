# Smart Traffic Management System Simulator
Introduction
The Smart Traffic Management System Simulator is a C++ program designed to simulate traffic flow management in a city with multiple intersections. It uses a graph data structure to represent the traffic network and handles congestion, traffic signal timings, road closures, and rerouting. This program reads data from CSV files to update traffic signal timings and road blockage statuses.

The system allows you to:

- Manage traffic signal timings.
- Block roads when needed.
- Monitor traffic congestion and reroute vehicles.
- Visualize the city’s traffic network and status.
- Prerequisites
- Before running the program, ensure that you have the following installed on your system:

- C++ Compiler: I have a C++ compiler on ubuntu, but I normally use VScode
- CSV Files: You need the CSV files for traffic signal timings and road closure statuses. These files will be read by the program to update the traffic system.

SmartTrafficSimulator/
├── README.md                   // This file
├── main.cpp                     // Main C++ source file
├── traffic_signals.csv           // CSV file for traffic signal timings
├── road_closures.csv             // CSV file for road closures
