#include "node.h"
#define MAX_NODES 100000  //Our graph will represent a population of 100000
using namespace std;

class Graph
{
public:
    node *edges[MAX_NODES];        //All nodes of our graph
    int node_degrees[MAX_NODES];   //Degree of each node in our graph
    int m;                         //Average degree of graph
    int node_edges[MAX_NODES];     //How many edges are connected to each node
    int num_nodes;                 //Total nodes in graph
    int num_edges;                 //Total edges in graph
    
    Graph();
    void initializeGraph(Graph *g, int m);   //Initialize graph
    void populateGraph(Graph *g, int m);
    void insertEdge(Graph *g, int x, int y, bool duplicate); //Insert edge between nodes x and y
    void printGraph(Graph *g);               //Print contents of graph
};
