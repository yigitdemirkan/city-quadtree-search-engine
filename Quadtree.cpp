#include "Quadtree.h"

//Default constructor
Quadtree :: Quadtree(){
    root = nullptr;
}

//Destructor
Quadtree :: ~Quadtree(){
    deletion(root);
}

//Deleting all dynamically allocated memory, this private function is used in destructor
void Quadtree :: deletion(Node*n){
    if (n != nullptr){
        deletion(n->NE);
        deletion(n->NW);
        deletion(n->SE);
        deletion(n->SW);
        delete n;
    }
}

//This public function calls the private insert function to insert new element to quadtree
void Quadtree :: insert(string cname, int x, int y){
    root = insert(root,cname, x,y);
}

//This private function inserts a new element to quadtree
Node* Quadtree :: insert(Node*n, string name, int x, int y){
    if (n == nullptr){ //if there are no elements in quadtree
        return new Node(name,x,y);
    }

    //Deciding for the direction
    if (x >= n->x && y>= n ->y){
        n->NE = insert(n->NE,name,x,y);
    }
    else if (x >= n->x && y < n->y){
        n->SE = insert(n->SE,name,x,y);
    }
    else if (x < n->x && y>= n ->y){
        n->NW = insert(n->NW,name,x,y);
    }
    else{
        n->SW = insert(n->SW,name,x,y);
    }
    return n;
}

//This public function calls the private prettyPrint with private field data root
void Quadtree :: prettyPrint(){
    prettyPrint(root);
}

//This private function prints the whole quadtree in a specific order.
void Quadtree :: prettyPrint(Node*n){
    if (n != nullptr){
        cout << n->cityName << endl;
        prettyPrint(n->SE);
        prettyPrint(n->SW);
        prettyPrint(n->NE);
        prettyPrint(n->NW);
    }
}

/*
This public function calls the private search function with private data field root.
If decider is entered as 0, it returns the found vector, if decider entered as 1, it returns the all visited cities.
 */
vector<Node*> Quadtree :: search(int x, int y, int r, int decider){
    vector <Node*> found,visited;
    search(root,x,y,r,found,visited);
    if (decider == 0){
        return found;
    }
    else{
        return visited;
    }
}

//This private function calculates the distance between two points
double Quadtree :: calculateDistance(int x1, int x2, int y1, int y2){
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

//This private function traverses the quadtree recursively and returns the cities in distance and all visited cities
void Quadtree :: search (Node*n,int x, int y, int r, vector<Node*> & found,vector<Node*> & visited ){
    if (n == nullptr){
        return;
    }

    if (calculateDistance(n->x,x,n->y,y) <= r){ //If the city in distance
        found.push_back(n);
        visited.push_back(n);
    }
    else{
        visited.push_back(n);
    }

    if (x-r >= n->x){
        if (n-> y > y+r){ //Region 1
            search(n->SE,x,y,r,found,visited);
        }
        else if (n-> y <= y-r){ //Region 6
            search(n->NE,x,y,r,found,visited);
        }
        else{ //Region 4
            search(n->SE,x,y,r,found,visited);
            search(n->NE,x,y,r,found,visited);
        }
    }
    else if (x+r < n->x){
        if (n->y > y+r){ //Region 3
            search(n->SW,x,y,r,found,visited);
        }
        else if (n->y <= y-r){ //Region 8
            search(n->NW,x,y,r,found,visited);
        }
        else{ //Region 5
            search(n->SW,x,y,r,found,visited);
            search(n->NW,x,y,r,found,visited);
        }
    }
    else{
        if (n->y > y+r){ //Region 2
            search(n->SE,x,y,r,found,visited);
            search(n->SW,x,y,r,found,visited);
        }
        else if(n->y <= y-r){ //Region 7
            search(n->NE,x,y,r,found,visited);
            search(n->NW,x,y,r,found,visited);
        }
        else{
            if(calculateDistance(n->x,x,n->y,y) <= r){//Region 13
                search(n->SE,x,y,r,found,visited);
                search(n->SW,x,y,r,found,visited);
                search(n->NE,x,y,r,found,visited);
                search(n->NW,x,y,r,found,visited);
            }
            else{
                if (n->x < x){
                    if (n->y > y){ //Region 9
                        search(n->SE,x,y,r,found,visited);
                        search(n->SW,x,y,r,found,visited);
                        search(n->NE,x,y,r,found,visited);
                    }
                    else{ //Region 11
                        search(n->SE,x,y,r,found,visited);
                        search(n->NE,x,y,r,found,visited);
                        search(n->NW,x,y,r,found,visited);
                    }
                }
                else{
                    if(n->y > y){//Region 10
                        search(n->SE,x,y,r,found,visited);
                        search(n->SW,x,y,r,found,visited);
                        search(n->NW,x,y,r,found,visited);
                    }
                    else{ //Region 12
                        search(n->SW,x,y,r,found,visited);
                        search(n->NE,x,y,r,found,visited);
                        search(n->NW,x,y,r,found,visited);
                    }
                }
            }

        }
    }

}
