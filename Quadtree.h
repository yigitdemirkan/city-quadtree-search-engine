#ifndef CS300HW2_QUADTREE_H
#define CS300HW2_QUADTREE_H
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Node{
    string cityName;
    int x,y;
    Node * NW;
    Node * NE;
    Node * SW;
    Node * SE;
    Node(string c, int X, int Y):
            cityName(c),x(X),y(Y),NW(nullptr),NE(nullptr),SW(nullptr),SE(nullptr){}
};

class Quadtree {
public:
    Quadtree();
    Quadtree(int x, int y):x_boundary(x),y_boundary(y),root(nullptr){};
    void insert(string cname, int x, int y);
    void prettyPrint();
    vector<Node*> search(int x, int y, int r, int decider);
    ~Quadtree();

private:
    int x_boundary;
    int y_boundary;
    Node*root;
    Node*insert(Node*n, string name, int x, int y);
    void prettyPrint(Node*n);
    void deletion(Node*n);
    void search(Node*n,int x, int y, int r, vector<Node*> & found, vector<Node*> & visited);
    double calculateDistance(int x1, int x2, int y1, int y2);
};


#endif //CS300HW2_QUADTREE_H
