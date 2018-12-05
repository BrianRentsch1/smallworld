#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
#include <stdio.h>
#include <queue>

using namespace std;

Graph::Graph()
{
    
}

//Initialize new graph
int Graph::initializeGraph(Graph *g, int m)
{
    srand(time(NULL));  //Set random seed for all graph operations based on time
    g->num_nodes = 0;   //Initialize number of nodes in graph to 0
    g->num_edges = 0;   //Initialize number of edges in graph to 0
    g->incomplete_nodes = 0;    //Track incomplete nodes
    if((4*m)/3 > MAX_NODES)   //If M is too large, return with error
    {        
        return 1;
    }
    g->m = m;   //Set M value of graph
    
    for(int i = 0; i < MAX_NODES; i++) //For all nodes, set random degree and initialize place in adjecency list as null
    {
        g->node_edges[i] = 0;   //Currently no edges in graph, so each node has 0 edges
        g->node_degree[i] = rand() % (((4*g->m)/3) - ((2*g->m)/3) + 1) + ((2*g->m)/3);  //generate random degree between 2/3m and and 4/3m for each node
        g->edges[i] = new node(i);  //Fill adjacency list with new nodes, with each node having an ID equal to their index in the array
        num_nodes++;           //Increment number of nodes in graph
    }
    return 0;
}

//Insert an edge into the graph
void Graph::insertEdge(Graph *g, int x, int y, bool duplicate)
{
    node *p = new node(y);  //Allocate new node
    p->next = g->edges[x]->next;  //Append list to end of new node
    g->edges[x]->next = p;  //Insert new node at head of list
    g->node_edges[x] += 1;  //Node x has one more edge 
    if(duplicate == false)  //Since our edges are undirected, we need to insert 2 edges every time we call insertEdge
    {
        insertEdge(g,y,x,true);  //This is undirected graph, so insert an edge in y's list    
    }
    g->num_edges += 1;   //Increment number of edges in graph 
}

//Populate the graph with edges. This function manages the random number generation of which edges to add, and makes sure no duplicate or invalid edges are inserted.
void Graph::populateGraph(Graph *g, int m)
{
    int y;
    int invalid_graph;
    
    invalid_graph = initializeGraph(g, m);   //Initialize graph

    if(invalid_graph == 1) //Make sure the M value chosen is realistic
    {
        cout << "Error:\tCould not populate graph.\n\tPlease select an M value such that 4m/3 is less than or equal to " << MAX_NODES << ".\n";
        cout << "\tCurrently, M = " << m << " and 4m/3 = " << (4*m)/3 << endl;
        return;
    }    

    cout << "\n\t*POPULATING GRAPH*" << endl;   //Display status of program
    
    graph_populated = 1;  //Indicate graph is being populated
    
    for(int i = 0; i < MAX_NODES; i++)  //For each node...
    {
        node *p = g->edges[i];  //temporary node pointer
        
        bool exhausted = false;  //Keep track if we have exhausted possible new edges to add
        int loop_counter = 0;   //Value to prevent infinite looping if no suitable new edge can be found

        for(int j = 0; g->node_edges[i] < g->node_degree[i]; j++) //Keep adding edges until the number of edges for node[i] == the degree of node[i]
        {
            bool edge_exists; //Indicate if we have found a duplicate edge
            do
            {
                p = g->edges[i]; //Point p to the top of the current node's linked list

                y = rand() % MAX_NODES;  //Generate a random node to make an edge with                

                //Traverse linked list of our current node to find if edge (x,y) already exists                
                while(p != nullptr)
                {
                    if(node_edges[y] == 0) //If there are no edges connected to this node...
                    {                        
                        edge_exists = false; //Currently no edges connected to this node -- OK to insert any edge (besides (x, x))  
                    }
                    else if(p->id == y)   //If a node (x, y) already exists... 
                    {
                        edge_exists = true;  //Edge will be a duplicate -- don't insert it and stop traversing this node's linked list
                        break;
                    }
                    else  //Otherwise, the edge (x, y) doesn't exist, and can be inserted
                    {
                        edge_exists = false;  //Edge will not be a duplicate -- OK to insert
                    }
                    
                    p = p->next;  //Advance along list
                }
                
                if(loop_counter > 100000)  //Assume after 100000 loops, we've exhausted all possible y values, so break from loop to prevent infinite looping
                {
                    exhausted = true;
                    break;
                }
                
                loop_counter++;

            } while(y == i || node_edges[y] == node_degree[y] || edge_exists);  //Repeatedly pick a new y value if node y already has its full degree of edges or if (x,y) is an edge that already exits

            if(exhausted == false)  //If this node did not exhaust all possible y values, we insert an edge
            {
                insertEdge(g,i,y,false);
            }
            else  //Otherwise, we break and proceed to the next node, as no other edges can be added to this node. This results in an "incomplete node"
            {
                break;
            }
        }
    }    
}

//Print out entire contents of graph
void Graph::printGraph(Graph *g)
{
    if(graph_populated == 0)  //Handle being called when graph has yet to be populated
    {
        cout << "\nError:\tCould not print graph.\n\tPlease populate a graph with a valid M value first." << endl;
        return;
    }
    
    node *p;   //temporary pointer

    for(int i = 0; i < g->num_nodes; i++)  //For all nodes in the graph...
    {
        int first = 1;  //Keep track of whether or not this is the head of the current linked list, for special formatting
        
        printf("%d: ", i);  //Print current node whose edges we are about to list
        p = g->edges[i];
        
        while (p != NULL)
        {
            if(first == 1)  //Skip first entry in list (which is the current node itself)
            {
                p = p->next;
                first = !first;
            }
            
            if(p != NULL)
            {
                printf(" %d", p->id);   //Print edge
                p = p->next;       //Advance to next edge
            }            
        }
        if(g->node_degree[i] != g->node_edges[i])  //Detect an incomplete node
        {
            printf(" // expected edges: %d actual edges: %d\n", g->node_degree[i], g->node_edges[i]);
            g->incomplete_nodes += 1;
        }
        else cout << endl;
    }
    //Print out stats about the graph
    cout <<endl<< "Total nodes: " << g->num_nodes << endl;
    cout << "Total edges: " << g->num_edges << endl;
    cout << "Total nodes left incomplete: " << g->incomplete_nodes << endl;
}

//Don't print out the entire graph, just print out stats
void Graph::simplePrint(Graph *g)
{
    if(graph_populated == 0)  //Handle being called when graph has yet to be populated
    {
        cout << "Error:\tCould not print graph.\n\tPlease populate a graph with a valid M value first." << endl;
        return;
    }
    
    for(int i = 0; i < g->num_nodes; i++)  //For all nodes in the graph...
    {        
        if(g->node_degree[i] != g->node_edges[i])  //Detect incomplete nodes
        {
            g->incomplete_nodes += 1;
        }
    }
    //Print stats
    cout <<endl<< "Total nodes: " << g->num_nodes << endl;
    cout << "Total edges: " << g->num_edges << endl;
    cout << "Total nodes left incomplete: " << g->incomplete_nodes << endl;
}

//Estimate the diameter of the graph, with a user-specified number of samples to take
int Graph::estimateDiameter(Graph *g, int samples)
{
    if(g->graph_populated == 0)   //Handle being called when graph isn't populated
    {
        cout << "\nError:\tCould not estimate diameter.\n";
        return -1;
    }
    
    int bfs_result;
    int s; int d;
    int diameter = 0;
    int greatest_s = 0;
    int greatest_d = 0;

    cout << "\n\t*DIAMETER CALCULATION STARTED*\n\n";
    
    //Run BFS a certain number of times and take the largest result as the likely diameter of the graph
    for(int i = 0; i < samples; i++)  
    {
        s = rand()%MAX_NODES;   //Generate random start and destination nodes
        d = rand()%MAX_NODES;   
        
        bfs_result = g->bfs(g, s, d);  //Run BFS

        if(bfs_result > diameter)   //Is our new result a new maximum diameter?
        {
            diameter = bfs_result;  //Update diameter
            greatest_s = s;         //Keep track of which nodes form the longest shortest path
            greatest_d = d;
        }
    }
    
    cout << "Diameters calculated: " << samples << endl;
    cout << "Max diameter: " << diameter << endl;

    return diameter;
}

//Estimate diameter with default number of samples
int Graph::estimateDiameter(Graph *g)
{
    return g->estimateDiameter(g, BFS_SAMPLES); //BFS_SAMPLES defined in Graph.h
}

//Breadth-first search function. This function traverses all nodes in the graph from a given starting node and determines if the graph is connected.
int Graph::bfs(Graph *g, int start)
{
    if(start >= MAX_NODES || start < 0)  //Handle incorrect starting node
    {
        cout << "\nError:\tBFS could not be performed.\n\tInvalid start node.\n\n";
        return -1;  //Error
    }
    
    node *s = g->edges[start];
    
    bool visited[MAX_NODES];  //Keep track of which nodes have been visited
    for(int i = 0; i < MAX_NODES; i++) //Initialize all entries of visited to false
    {
        visited[i] = false;
    }
    int nodes_traversed = 0;  //Count how many nodes we have traversed (to determine if graph is connected or not)
    
    node *curr_node;  //current node
    node *curr_neighbor;  //Current neighbor of current node
    int id;           //ID of current neighbor
              
    queue <node* > q;   //Queue to process nodes
    q.push(s);          //Push starting node to queue
    visited[s->id] = true;        //Indicate starting node has been visited
    
    while(!q.empty())
    {
        curr_node = q.front();  //Get front of queue        
        q.pop();                //Pop from queue, indicating the node has been traversed
        nodes_traversed++;      //Keep track of how many nodes have been poppped
        curr_neighbor = g->edges[curr_node->id]->next;  //curr_neighbor = first edge of curr_node
        
        while(curr_neighbor != nullptr)  //For all neighbors of our current node
        {
            id = curr_neighbor->id;   //Get node ID
            if(visited[id] == false)  //If neighbor hasn't been visited...
            {
                q.push(curr_neighbor);  //push it to queue
                visited[id] = true;   //mark as visited
            }
            curr_neighbor = curr_neighbor->next;  //advance along list
        }
    }
    if(nodes_traversed == g->num_nodes)  //If we have traversed all nodes in the graph
    {
        return 1;   //We've popped all nodes from our graph, so all nodes have been traversed: e.g. graph is connected
    }
    else
    {
        return 0;  //Graph is not connected    
    }
}

//BFS algorithm for finding the shortest path between two specified nodes. Used for determining the diameter of the graph.
int Graph::bfs(Graph *g, int start, int destination)
{
    if(start >= MAX_NODES || start < 0 || destination >= MAX_NODES || destination < 0) //Handle incorrect nodes
    {
        cout << "\nError:\tBFS could not be performed.\n\tInvalid start or destination node.\n\n";
        return -2;  //Error
    }
    node *s = g->edges[start];
    node *dst = g->edges[destination];
    
    if(s->id == dst->id)  
    {    
        return 0;  //start and destination are the same
    }

    bool visited[MAX_NODES];  //Keep track of which nodes have been visited
    for(int i = 0; i < MAX_NODES; i++) //Initialize all entries of visited to false
    {
        visited[i] = false;
    }
    
    node *parent[MAX_NODES];  //Keep track of parent nodes for backtracking later
    node *curr_node;  //current node
    node *curr_neighbor; //current neighbor of current node
    int id;   //ID of current neighbor
          
    
    queue <node* > q;  //Queue for processing nodes
    q.push(s);    //Push start to queue
    
    while(!q.empty())
    {
        curr_node = q.front();  //Get first item in queue
        if(curr_node->id == dst->id)  //If we have found our destination...
        {
            return backtrack(g,parent,s,dst);  //...Find the shortest path from start to dst
        }
        q.pop(); 
        visited[curr_node->id] = true;  //current node has been processed
        curr_neighbor = g->edges[curr_node->id]->next;  //curr_neighbor = first edge of curr_node
        
        while(curr_neighbor != nullptr)
        {
            id = curr_neighbor->id;
            if(visited[id] == false)  //If neighbor hasn't been visited...
            {
                q.push(curr_neighbor);  //push it to queue
                visited[id] = true;   //mark as visited
                parent[id] = curr_node;            //record parent    
            }
            curr_neighbor = curr_neighbor->next;  //advance along list
        }
    }
    return -1;  //DST not found in graph containing s    
}

//Backtrack through parent array and determine shortest path between s and dst
int Graph::backtrack(Graph *g, node *parents[MAX_NODES], node *s, node *dst)
{
    node *p = dst; //temp node pointer
    int distance = 0;
    
    while(p->id != s->id)
    {
        distance++;  //Increment path length
        p = parents[p->id];  //go back one edge
    }
    return distance;
}

//Determine if the graph is connected by calling BFS
bool Graph::connected(Graph *g)
{
    if(graph_populated == 0)  //Handle being called when graph isn't populated
    {
        cout << "\nError:\tCould not determine if graph is connected. Graph has not been populated.\n";
        return false;
    }

    cout << "\n\t*CHECKING CONNECTEDNESS*\n\n";  //Print status to console
     
    int s = rand() % MAX_NODES;  //Generate a random starting node
    int result = g->bfs(g,s);   //Run BFS

    if(result == 1)   //Handle result
    {
        return true;
    }
    else if(result == 0)
    {
        return false;
    }
    else
    {
        cout << "\nError:\tConnectedness of graph could not be determined; Invalid call to BFS.\n";
        return false;
    }
}
