#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits.h>
#include <sstream>
#include <SFML/Graphics.hpp>
// g++ GoLv1.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app
using namespace std;
using namespace sf;

#define MapWidth 320/pixelSide
#define MapHeight 320/pixelSide
#define pixelSide 10
int cellMap[MapWidth][MapHeight];
int nextCellMap[MapWidth][MapHeight];

#define BLACK Color::Black
#define WHITE Color::White
#define GRAY Color(153, 153, 153)
#define ticMiliseconds 100
bool Play = false;

void init();
void findNextCell();
void setNextCell();

int main(){
    /* Window and font: */
    RenderWindow window(VideoMode(320, 320), "Game of Life");
    window.setVerticalSyncEnabled(true);
    Font terminus;
    if(!terminus.loadFromFile("fonts/terminus/TerminusTTF-4.49.2.ttf")){cout<<"Error: text font not found!";};
    init();

    while(window.isOpen()){
        /* Events: */
        Event event;
        window.clear(BLACK);
        while(window.pollEvent(event)){
            switch(event.type){
                case Event::Closed:
                window.close();
                break;

                case Event::KeyPressed:
                switch(event.key.code){
                    case Keyboard::Escape:
                    window.close();
                    break;

                    case Keyboard::P:
                    Play = !Play;
                    break;

                    case Keyboard::R:
                    init();
                    break;
                }
                break;

                case Event::MouseButtonPressed:
                if (Play == false && event.mouseButton.button == Mouse::Left){
                    int j = double(event.mouseButton.x)/pixelSide;
                    int i = double(event.mouseButton.y)/pixelSide;
                    if (j >= 0 && j < MapWidth && i >= 0 && i < MapHeight){
                        if(cellMap[i][j] == 0){ cellMap[i][j] = 1; }else{ cellMap[i][j] = 0; };
                    }
                }
                break;
            }
        }

        /* Coloring cells: */
        for(int i = 0; i < MapHeight; i++){
            for(int j = 0; j < MapWidth; j++){
                RectangleShape cell;
                cell.setPosition(j*pixelSide,i*pixelSide);
                cell.setSize(Vector2f(pixelSide, pixelSide));
                cell.setOutlineThickness(1);
                cell.setOutlineColor(GRAY);
                if(Play == true){
                    findNextCell();
                    cellMap[j][i] == nextCellMap[j][i];
                }else{
                    setNextCell();
                }

                if(cellMap[i][j] == 1){
                    cell.setFillColor(WHITE);
                }else{
                    cell.setFillColor(BLACK);
                }

                window.draw(cell);
            }
        }

        /*if(Play == true){
            for(int i = 0; i < MapHeight; i++){
                for(int j = 0; j < MapWidth; j++){
                    cellMap[i][j] = findNextCell(j, i);
                }
            }
        };*/
        window.display();
        sleep(milliseconds(ticMiliseconds));
    }

}

void init(){
    for(int i = 0; i < MapHeight; i++){
        for(int j = 0; j < MapWidth; j++){
            cellMap[i][j] = 0;
        }
    }
}

void setNextCell(){
    for(int i = 0; i < MapHeight; i++){
        for(int j = 0; j < MapWidth; j++){
            nextCellMap[j][i] = cellMap[j][i];
        }
    }
}

void findNextCell(){
    int neighborSum = 0, neighborCheck = 1;

    for(int y = 0; y < MapHeight; y++){
    for(int x = 0; x < MapWidth; x++){
    if(y > 0){
        if(nextCellMap[y-1][x] == neighborCheck) neighborSum++;
    }if(y < MapHeight-1){
        if(nextCellMap[y+1][x] == neighborCheck) neighborSum++;
    }

    if(x > 0){
        if(nextCellMap[y][x-1] == neighborCheck) neighborSum++;
    }if(x < MapWidth-1){
        if(nextCellMap[y][x+1] == neighborCheck) neighborSum++;
    }

    if(y > 0 && x > 0){
        if(nextCellMap[y-1][x-1] == neighborCheck) neighborSum++;
    }if(y < MapHeight-1 && x < MapWidth-1){
        if(nextCellMap[y+1][x+1] == neighborCheck) neighborSum++;
    }

    if(y > 0 && x < MapWidth-1){
        if(nextCellMap[y-1][x+1] == neighborCheck) neighborSum++;
    }if(y < MapHeight-1 && x > 0){
        if(nextCellMap[y+1][x-1] == neighborCheck) neighborSum++;
    }

    int nextCell = 0;
    if(nextCellMap[y][x] == 1){
        cout<<x<<" "<<y<<": "<<nextCellMap[y][x]<<", "<<neighborSum;
        if(neighborSum == 2 || neighborSum == 3){
            nextCell = 1;
        }
        cout<<" = "<<nextCell<<"\n";
    }else{
        if(neighborSum == 3){
            nextCell = 1;
        }
    }

    nextCellMap[y][x] = nextCell;
    }
    }
}