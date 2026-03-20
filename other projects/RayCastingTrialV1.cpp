/* Libraries: */
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits.h>
#include <sstream>
#include <SFML/Graphics.hpp>
// g++ RayCastingTrialV1.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app
using namespace std;
using namespace sf;

/* Functions: */
void init(float cx,float cy);
float angleAdjust(float angle);
float dtoR(float angle);
float rotatePointx(float pointx, float pointy, float angle);
float rotatePointy(float pointx, float pointy, float angle);
RectangleShape Draw2dMap(int x, int y);
int checkTileValue(int x, int y);

/* Global constants: */
const int MapWidth2d = 8;
const int MapHeight2d = 8;
const int squareSide = 32;
const float cubeHeight = 32;
#define SPACE_BETWEEN_MAPS 32 // Space between the 2d and 3d maps
const int Width3d = 320;
const int Height3d = 200;

/* Global variables: */
float ppx, ppy; // Player position x and y
float pvx, pvy; // Player velocity in x and y
float pangle = 0; // Player's direction angle
float pvr; // Player's rotation velocity
float pHeight = cubeHeight/2; // Player's height
float pFOV = 60; // The field of view

int map1[MapWidth2d][MapHeight2d]={ // Map:
{1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,1},
{1,0,1,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,1},
{1,0,1,1,0,1,0,1},
{1,0,0,0,0,1,0,1},
{1,1,1,1,1,1,0,1},
};

/* Main loop: */
int main(){
    /* Create and configure window: */
    RenderWindow window(VideoMode(MapWidth2d*squareSide+SPACE_BETWEEN_MAPS+Width3d,MapHeight2d*squareSide+(Height3d-MapHeight2d)),"Ray Casting attempt");
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true); // Get map's center:
    const float xMapLimit2d = MapWidth2d*squareSide;
    const float yMapLimit2d = MapHeight2d*squareSide;
    const float cx2d = xMapLimit2d/2;
    const float cy2d = yMapLimit2d/2; // Get font:
    Font terminus;
    if(!terminus.loadFromFile("fonts/terminus/TerminusTTF-4.49.2.ttf")){cout<<"Error: text font not found!";};
    init(cx2d,cy2d); // Initializing everything

    /* Shapes and variables: */
    // Player:
    #define PLAYER_RADIUS 8
    CircleShape player(PLAYER_RADIUS);
    player.setFillColor(Color::Yellow);
    player.setOrigin(PLAYER_RADIUS,PLAYER_RADIUS);
    player.setPosition(ppx,ppy);
    RectangleShape playerPointer(Vector2f(PLAYER_RADIUS+PLAYER_RADIUS/2,1));
    playerPointer.setFillColor(Color::Yellow);
    playerPointer.setOrigin(0,1);
    playerPointer.setPosition(ppx,ppy);

    // 3d renderization calculations:
    const float cx3d = Width3d/2;
    const float cy3d = Height3d/2;
    float distp = cx3d/tan(dtoR(pFOV/2)); // Distance from the player to the "plane"

    // Keys:
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;

    /* Opening window: */
    while(window.isOpen()){
        /* Getting the events: */
        Event event;
        while(window.pollEvent(event)){ // Closing window:
            if(event.type==Event::Closed) window.close();
            if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

            /* Moving player: */
            if (event.type==Event::KeyPressed){
                switch (event.key.code){
                case  Keyboard::Escape: window.close(); break;
                case Keyboard::W:
                case Keyboard::Up: upFlag=true; break;
                case Keyboard::S:
                case Keyboard::Down: downFlag=true; break;
                case Keyboard::A:
                case Keyboard::Left: leftFlag=true; break;
                case Keyboard::D:
                case Keyboard::Right: rightFlag=true; break;
                default: break;
                }
            }if (event.type == sf::Event::KeyReleased){
                switch(event.key.code){
                case Keyboard::W:
                case Keyboard::Up: upFlag=false; break;
                case Keyboard::S:
                case Keyboard::Down: downFlag=false; break;
                case Keyboard::A:
                case Keyboard::Left: leftFlag=false; break;
                case Keyboard::D:
                case Keyboard::Right: rightFlag=false; break;
                default: break;
                }
            }
        }

        // Moving
        pangle = angleAdjust(pangle);
        float pangleRad = dtoR(pangle);
        playerPointer.setRotation(-pangle);
        float radiusSignX,radiusSignY;
        if(pangle > 90 && pangle <= 270){
            radiusSignX = PLAYER_RADIUS*-1;
        }else{
            radiusSignX = PLAYER_RADIUS;
        }if(pangle > 180 && pangle <= 360){
            radiusSignY = PLAYER_RADIUS*-1;
        }else{
            radiusSignY = PLAYER_RADIUS;
        }
        if(leftFlag){/*player.move(-pvx,0);*/ pangle=pangle+pvr;};
        if(rightFlag){/*player.move(pvx,0);*/ pangle=pangle-pvr;};
        if(upFlag){
            if(player.getPosition().x+PLAYER_RADIUS+pvx*cos(pangleRad) < xMapLimit2d && player.getPosition().y-pvy*sin(pangleRad)+PLAYER_RADIUS < yMapLimit2d && player.getPosition().x-PLAYER_RADIUS+pvx*cos(pangleRad) > 0 && player.getPosition().y-pvy*sin(pangleRad)-PLAYER_RADIUS > 0){
                int tileposy = (player.getPosition().y-radiusSignY-pvy*sin(pangleRad))/squareSide;
                int tileposx = (player.getPosition().x+radiusSignX+pvx*cos(pangleRad))/squareSide;
                int tilev = checkTileValue(tileposx,tileposy);
                RectangleShape tile = Draw2dMap(tileposx,tileposy);
                if(tilev > 0 && tile.getGlobalBounds().contains(player.getPosition().x+radiusSignX+pvx*cos(pangleRad),player.getPosition().y-radiusSignY-pvy*sin(pangleRad))){
                    cout<<"Collision!!!\n";
                }else{
                    player.move(pvx*cos(pangleRad),-pvy*sin(pangleRad)); playerPointer.move(pvx*cos(pangleRad),-pvy*sin(pangleRad));
                }
            }
        };
        if(downFlag){
            if(player.getPosition().x+PLAYER_RADIUS-pvx*cos(pangleRad) < xMapLimit2d && player.getPosition().y+pvy*sin(pangleRad)+PLAYER_RADIUS < yMapLimit2d && player.getPosition().x-PLAYER_RADIUS-pvx*cos(pangleRad) > 0 && player.getPosition().y+pvy*sin(pangleRad)-PLAYER_RADIUS > 0){
                int tileposy = (player.getPosition().y+radiusSignY+pvy*sin(pangleRad))/squareSide;
                int tileposx = (player.getPosition().x-radiusSignX-pvx*cos(pangleRad))/squareSide;
                int tilev = checkTileValue(tileposx,tileposy);
                RectangleShape tile = Draw2dMap(tileposx,tileposy);
                if(tilev > 0 && tile.getGlobalBounds().contains(player.getPosition().x-radiusSignX-pvx*cos(pangleRad),player.getPosition().y+radiusSignY+pvy*sin(pangleRad))){
                    cout<<"Collision!!!\n";
                }else{
                    player.move(-pvx*cos(pangleRad),pvy*sin(pangleRad)); playerPointer.move(-pvx*cos(pangleRad),pvy*sin(pangleRad));
                }
            }
        };

        // DDA:
        float sideDistX, sideDistY;
        int tileposx = (player.getPosition().x)/squareSide;
        int tileposy = (player.getPosition().y)/squareSide;
        cout<<tileposx<<","<<tileposy<<endl;

        /* Draw: */
        window.clear();
        for(int i = 0; i < MapHeight2d; i++){
            for(int j = 0; j < MapWidth2d; j++){
                RectangleShape tile = Draw2dMap(i,j);
                window.draw(tile);
            }
        }
        // The ray casting:
        
        window.draw(playerPointer);
        window.draw(player);
        window.display();
    }
    return 0;
}

/* Initialization function: */
void init(float cx2d, float cy2d){
    ppx = cx2d;
    ppy = cy2d;
    pvx = 2;
    pvy = 2;
    pangle = 90;
    pvr = 3;
    pHeight = cubeHeight/2;
    pFOV = 60;
}

/* Adjust negative angles: */
float angleAdjust(float angle){
    //cout<<"Angle fixed: "<<angle;
    if(angle < 0){
        angle = angle*-1;
        angle = 360-angle;
    }if(angle > 360){
        angle = angle-360;
        angleAdjust(angle);
    }
    //cout<<"° -> "<<angle<<"°;\n";
    return angle;
}

/* Converting angle to radian: */
float dtoR(float angle){
    //cout<<"Angle converted: "<<angle;
    angle=angle*M_PI/180;
    //cout<<"° -> "<<angle<<"RAD;\n";
    return angle;
}

/* Rotating any x and y: */
float rotatePointx(float pointx, float pointy, float angle){
    angle = dtoR(angle);
    pointx = pointx*cos(angle) + pointy*sin(angle);
    return pointx;
}

float rotatePointy(float pointx, float pointy, float angle){
    angle = dtoR(angle);
    pointy = pointx*sin(angle) + pointy*cos(angle);
    return pointy;
}

/* Structure for the differente blocks when drawing the 2d map: */
struct tile{
    int outlineThick = 1;
    Vector2f tileSize = Vector2f(squareSide,squareSide);
    float tilePosx;
    float tilePosy;
    Color tileColor;
    Color outlineColor = Color::Black;
};
/* Function to return the blocks to be drawn */
RectangleShape Draw2dMap(int x, int y){
    tile currentTile;
    RectangleShape tile(currentTile.tileSize);
    tile.setOutlineThickness(currentTile.outlineThick);
    tile.setOutlineColor(currentTile.outlineColor);
    currentTile.tilePosx = squareSide*x;
    currentTile.tilePosy = squareSide*y;
    if(map1[y][x]>0){
        currentTile.tileColor = Color::White;
    }else{
        currentTile.tileColor = Color::Black;
    }
    tile.setPosition(currentTile.tilePosx,currentTile.tilePosy);
    tile.setFillColor(currentTile.tileColor);
    return tile;
}

/* Check desired tile's value */
int checkTileValue(int x, int y){
    return map1[y][x];
}