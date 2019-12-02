#include <iostream>
#include "queue.h"
#include "linearlist.h"

using namespace std;

const int dCol[] = {0, 1, 1, 0, -1, -1};
const int dREven[] = {-1, -1, 0, 1, 0, -1};
const int dROdd[] = {-1, 0, 1, 1, 1, 0};
const int *dRow;
int map[400];
int duck, marvin, phos;

int convertPos(int r, int c){
    int num = 0;
    num = 20 * r + c;
    return num;
}

int getCol(int num){
    int r = num % 20;
    return r;
}

int getRow(int num){
    // ones is used as a temp integer to hold the ones place of the number
    int ones = num % 10;
    int c = (num - ones) / 20;
    return c;
}

int findNeighbors(int pos, Queue<int> &Queue, int &count){
    int nR, nC, tempCol, tempRow;

    tempCol = getCol(pos);
    tempRow = getRow(pos);

    if(tempCol % 2 == 0){
        dRow = dREven;
    }

    else{
        dRow = dROdd;
    }

    for(int i = 0; i<=5; i++){
        int neighbor;

        nR = tempRow + dRow[i];
        nC = tempCol + dCol[i];

        neighbor = convertPos(nR,nC);

        if(map[neighbor] == -1){
            Queue.enqueue(neighbor);
            // cout << "Neighbor enqueued: " << nR << "," << nC << endl;
            map[neighbor] = map[pos] + 1;
        }
    }
    return 0;
}

int createList(int &pos, LinearList<int> &List, int &counter){
    int nR, nC, tempCol, tempRow;

    dRow = nullptr;

    tempCol = getCol(pos);
    tempRow = getRow(pos);

    if(tempCol % 2 == 0){
        dRow = dREven;
    }

    else{
        dRow = dROdd;
    }

    for(int i = 0; i<=5;i++){
        int neighbor = 0;
        nR = tempRow + dRow[i];
        nC = tempCol + dCol[i];

        neighbor = convertPos(nR,nC);

        if(map[neighbor] == map[pos]-1){
            List.insert(counter, map[neighbor]);
            counter +=1;
            pos = neighbor;
            break;
        }
    }
    return 0;
}

LinearList<int> findPath(int &posit, int lava[], int lavaSpaces){

    // Create a queue for the list to be stored
    Queue<int> pathQueue;       // Illudium Phosdex Queue
    LinearList<int> PlayerPath;      // Duck or Marvin's Path/List

    int count = 0;
    int listCount = 0;
    PlayerPath.clear();
    pathQueue.clear();
    pathQueue.enqueue(phos);

    // Assign each location on the map to be -1
    for(int i = 0; i<400; i++){
        map[i] = -1;
    }

    // Assign the locations to the map
    map[phos] = count;
    for(int i = 0; i<lavaSpaces; i++){
        map[lava[i]] = -2;
    }

    while(!pathQueue.isEmpty()){
        int loc = 0;
        loc = pathQueue.dequeue();
        findNeighbors(loc,pathQueue,count);
    }

    if(map[posit] == -1){
        // There is no path to the Phosdex
    }
    else{
        PlayerPath.insert(listCount,map[posit]);
        listCount+=1;
        while(map[posit] != 0){
            createList(posit, PlayerPath, listCount);
        }
    }

    return PlayerPath;
}

void print(int &d) {
    cout << d << endl;
}

int main() {

    int duckX, duckY, marvinX, marvinY, phosX, phosY, last_pos;
    int lavaSpaces = 0;
    LinearList<int> DuckList, MarvinList;
    DuckList.clear();

    // Get the locations needed from the user (Duck, Marvin, Illudium, Lava Blocks)
    cout << "Enter the position of Duck Dodgers: " << endl;
    cin >> duckX >> duckY;
    duck = convertPos(duckX, duckY);

    cout << "Enter the position of Marvin the Martian: " << endl;
    cin >> marvinX >> marvinY;
    marvin = convertPos(marvinX, marvinY);

    cout << "Enter the position of the Illudium Phosdex: " << endl;
    cin >> phosX >> phosY;
    phos = convertPos(phosX, phosY);

    cout << "Enter the amount of Lava blocks: " << endl;
    cin >> lavaSpaces;

    int lava[lavaSpaces];

    for(int i = 0; i < lavaSpaces; i++){
        int lavaX = 0, lavaY = 0;
        cout << "Enter a lava space: " << endl;
        cin >> lavaX >> lavaY;
        lava[i] = convertPos(lavaX,lavaY);
    }

    DuckList = findPath(duck, lava, lavaSpaces);
    cout << "Size of Duck List: " << DuckList.size() - 1 << endl;

    MarvinList = findPath(marvin, lava, lavaSpaces);
    cout << "Size of Marvin List: " << MarvinList.size() - 1 << endl;
    // MarvinList.traverse(print);

    if(DuckList.size() > MarvinList.size()){
        cout << "Marvin the Martian reaches the Illudium Phosdex first." << endl;
        cout << "Trying Gandolf." << endl;
    }
    else if(DuckList.size() < MarvinList.size()){
        cout << "Duck Dodgers reaches the Illudium Phosdex first." << endl;
    }
    else if(DuckList.size() == MarvinList.size()){
        cout << "They will both reach the Illudium Phosdex at the same time." << endl;
        cout << "Trying Gandolf." << endl;
    }
    return 0;
}