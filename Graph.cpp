#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
using namespace std;

Graph::Graph()
{
    
}

//Initialize new graph
void Graph::initializeGraph(Graph *g, int m)
{
    srand(time(NULL));
    g->num_nodes = 100000;
    g->num_edges = 0;
    g->m = m;
    
    for(int i = 0; i < MAX_NODES; i++) //For all nodes, set random degree and initialize place in adjecency list as null
    {
        g->node_edges[i] = 0;   //Currently no edges in graph
        g->node_degrees[i] = rand() % ((2*g->m)/3) + ((2*g->m)/3);  //generate random degree between 2/3m and and 4/3m for each node
        g->edges[i] = new node(i);
    }
}

//Insert an edge into the graph
void Graph::insertEdge(Graph *g, int x, int y, bool duplicate)
{
    node *p = new node(y);  //Allocate new node
    p->next = g->edges[x]->next;  //Append list to end of new node
    g->edges[x]->next = p;  //Insert new node at head of list
    g->node_edges[x] += 1;  //Node x has one more edge 
    if(duplicate == false)
    {
        insertEdge(g,y,x,true); //This is undirected graph, so insert an edge in y's list    
    }
    else g->num_edges += 1;    
}

void Graph::populateGraph(Graph *g, int m)
{
    int y;
    
    initializeGraph(g, m);
    srand(time(NULL));
       
    for(int i = 0; i < MAX_NODES; i++)  //For each node...
    {
        for(int j = 0; g->node_edges[i] < g->node_degrees[i]; j++) //Keep adding edges until the number of edges for node[i] == the degree of node[i]
        {
            int inserted_nodes[g->node_degrees[i]];  //Make an array of all nodes added to current index of adjecency list
            bool in_list;
            do
            {
                y = rand() % MAX_NODES;  //Generate a random node to make an edge with
                for(int k = 0; k < g->node_degrees[i];k++)
                {
                    if(inserted_nodes[k] == y)
                        in_list = true;
                }
            } while(y == i && !in_list);
            insertEdge(g,i,y,false);
        }        
    }    
}

void Graph::printGraph(Graph *g)
{
    node *p;

    for(int i = 0; i < g->num_nodes; i++)
    {
        int first = 1;
        printf("%d: ", i);
        p = g->edges[i];        
        
        while (p != NULL)
        {
            if(first == 1)
            {
                p = p->next;
                first = !first;
            }         
            printf(" %d", p->id);                        
            p = p->next;        
        }
        printf("\n");
    }
}
