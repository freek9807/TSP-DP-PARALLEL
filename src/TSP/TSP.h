#ifndef TSP_DEF
#define TSP_DEF

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <tsl/robin_map.h>

using namespace std;

/**
 * Describe a path, how much it cost( cost field) and route (path)
 */
struct Path
{
    double cost = 0;
    vector<int*> path;
};
/**
 * Describe a node on the stack
 */
struct NodeStack{
    int* node;
    double cost;
    vector<int*> ls;
    vector<int*> remaining;
};
/**
 * Describe The TSP Algorithm
 */
class TSP_Class
{
private:
    /**
     * Distance Matrix
     */
    double** adj;
    /**
     * Real starting node
     */
    int* realFirst;
    /**
     * Node from where TSP should start in this instance ( equal to realFist in not parallel implementation)
     */
    int* first;
    /**
     * Stack of value to be evaluated
     */
    stack<NodeStack*> st;
public:
    /**
     * Constructor
     * @param realFirst Real starting node
     * @param first Node from where TSP should start in this instance ( equal to realFist in not parallel implementation)
     * @param cost path cost till now
     * @param adj distance matrix
     * @param S set of values to evaluate
     */
    TSP_Class(int* realFirst,int* first,double cost,double** adj,vector<int*>& S);
    /**
     * Start the algorithm
     * @return Return the best path (cost and route)
     */
    Path* start();
};
#endif