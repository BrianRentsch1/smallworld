/**************************
CSC 335 Project 2
Brian Rentsch, Matt Kilcher
Fall 2018
***************************/

using namespace std;

struct node
{
    int id;  //Node has an ID (a number which indicates which node of the graph it is)
    node *next;  //Node has a pointer to next node in adjacency list (neighbor of head of list)

    node(int node_id);  //Constructor
};
