#include "node.h"
#define MAX_NODES 100000  //Our graph will represent a population of 100000
#define BFS_SAMPLES 100   //Default number of times BFS will be run to determine diameter of graph
using namespace std;

class Graph
{
public:
    node *edges[MAX_NODES];        //All nodes of our graph
    int node_degree[MAX_NODES];   //Degree of each node in our graph
    int m;                         //Average degree of graph
    int node_edges[MAX_NODES];     //How many edges are connected to each node
    int num_nodes;                 //Total nodes in graph
    int num_edges;                 //Total edges in graph
    int incomplete_nodes;          //If any, how many nodes were left incomplete?
    int graph_populated;           //Indicates when the graph has been successfully populated
    
    Graph();
    void populateGraph(Graph *g, int m);    //Insert random edges into graph   
    void printGraph(Graph *g);              //Print entire contents of graph as well as stats
    void simplePrint(Graph *g);             //Don't print graph contents, just print stats
    int estimateDiameter(Graph *g, int samples);  //Run BFS for <samples> number of times and take highest result
    int estimateDiameter(Graph *g);  //Run BFS for a default number of times and take highest result
    bool connected(Graph *g);       //Run BFS once to determine if graph is connected
    
private:
    int initializeGraph(Graph *g, int m);   //Initialize graph
    void insertEdge(Graph *g, int x, int y, bool duplicate); //Insert edge between nodes x and y
    int backtrack(Graph *g, node *parents[MAX_NODES], node *s, node *dst);  //backtrack and find shortest distance
    int bfs(Graph *g, int start);  //Find paths from s to all nodes. Can use to determine if graph is connected.
    int bfs(Graph *g, int start, int destination);  //Find shortest path from node s to node dst   
};
