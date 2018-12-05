/**************************
CSC 335 Project 2
Brian Rentsch, Matt Kilcher
Fall 2018
***************************/

#include "node.h"
using namespace std;

node::node(int node_id)
{
    id = node_id;  //Set ID of node
    next = nullptr;  //Set next to NULL
}
