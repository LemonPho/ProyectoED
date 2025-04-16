#pragma once

#include <iostream>
#include "connection-list.h"

class Node; //If we include node.h, node.h will include graph.h which will then include node.h, infinite.

class Graph {
private:
    Node* m_Header;
public:
    Graph();

    void AddNode();
    void EditNode();
    void DeleteNode();

    Node* GetNodeFromString(const std::string& nodeName);
    Node* GetNodeFromIndex(const int index);

    // makes an array of connections of the shortest path between two nodes
    ConnectionList FindShortestPath(Node* originNode, Node* destinationNode);

    void PrintGraph(); //show full graph with connections
    void PrintList(); //show just list of buildings
    void PrintListIndex(); //print list with index

    int NodeCount();

    ~Graph();
};
