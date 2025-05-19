#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "connection-list.h"

const std::string BUILDINGS_FILE = "buildings.txt";
const std::string CONNECTIONS_FILE = "connections.txt";

class Node; //If we include node.h, node.h will include graph.h which will then include node.h, infinite.

class Graph {
private:
    Node* m_Header;
    std::string m_ErrorMessages;
public:
    Graph();

    void InsertNode(Node* newNode);
    void DeleteNode(int index);

    Node* GetNodeFromString(const std::string& nodeName);
    Node* GetNodeFromIndex(const int index);
    int GetIndexFromNode(Node* node);

    // makes an array of connections of the shortest path between two nodes
    ConnectionList FindShortestPath(Node* originNode, Node* destinationNode);

    void PrintGraph(); //show full graph with connections
    void PrintList(); //show just list of buildings
    void PrintListIndex(); //print list with index

    void PrintErrorMessages(); //Print error messages then delete them

    int NodeCount();

    void ReadFromDisk();
    void WriteToDisk();

    ~Graph();
};
