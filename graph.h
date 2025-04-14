#pragma once

#include <iostream>
#include "node.h"

class Node; //If we include node.h, node.h will include nodelist.h which will then include node.h, infinite.

//consider changing name to graph
class Graph {
private:
    Node* m_Header;
public:
    Graph();

    void AddNode(Node* newNode);
    void EditNode(Node* node);
    void RemoveNode(const std::string& nodeName);

    Node* GetNodeFromString(const std::string& nodeName);

    // makes an array of connections of the shortest path between two nodes
    Connection* MakeShortestPath(Node* originNode, Node* destinationNode);

    void PrintGraph(); //show full graph with connections
    void PrintList(); //show just list of buildings

    ~Graph();
};
