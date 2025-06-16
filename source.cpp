#include <iostream>
#include <string>
#include "Quadtree.h"
#include <fstream>
#include <sstream>
using namespace std;

//This function prints the found and visited cities for each query
void printResult(const vector<Node*> & found,const vector <Node*> & visited){
    int fsize = found.size();
    if (fsize == 0){ //If there are no cities in r distance
        cout << "<None>" << endl;
    }
    if (fsize == 1){ //If there is only one city, no comma needed at the end.
        cout << found[0]->cityName << endl;
    }
    else{
        for (int i = 0; i < fsize ; i++){
            if (i == fsize-1){ //If it is the last city, no comma needed.
                cout << found[i]->cityName <<endl;
            }
            else{
                cout << found[i]->cityName << ", ";
            }
        }
    }
    int vsize = visited.size();
    for (int t = 0; t < vsize ; t++){
        if (t == vsize-1){ //If it is the last city, no comma needed.
            cout << visited[t]->cityName <<endl;
        }
        else{
            cout << visited[t]->cityName << ", ";
        }
    }
}

int main() {

    ifstream cities("cities.txt");
    string line, name;
    int x,y;
    if(getline(cities,line)){ //proceeding the cities file
        istringstream iss(line);
        iss >> x >> y;
    }
    Quadtree my_quad(x,y); //quadtree is created, first line indicates the boundaries, so it is taken separately.
    while (getline(cities,line)){ //getting the rest of the lines
        istringstream iss(line);
        iss >> name >> x >> y;
        my_quad.insert(name,x,y);
    }
    cities.close();
    my_quad.prettyPrint(); //printing the quadtree
    cout << endl;

    ifstream query("queries.txt"); //proceeding queries file
    string line2;
    int x1,y1,r;
    char comma;
    bool first = true;
    while (getline(query, line2)){
        istringstream iss(line2);
         if (iss >> x1 >> comma >> y1 >> comma >> r) {
             vector<Node *> found = my_quad.search(x1, y1, r,0); //search function returns the cities in distance with decider '0'
             vector<Node *> visited = my_quad.search(x1, y1, r,1); //search function returns the all cities visited with decider '1'
             if (!first) {
                 cout << endl;
             }
             printResult(found, visited);
             first = false;
         }
    }
    query.close();
    return 0;
}
