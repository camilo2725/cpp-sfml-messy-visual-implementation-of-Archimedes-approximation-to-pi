/******************************************************************************
                                    PI
*******************************************************************************/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits.h>
#include <sstream>
#include <SFML/Graphics.hpp>
//#include <unistd.h>

// g++ ArchimedesMethodVisualized.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app
using namespace std;

#define PI 3.14159265358979323846264338327950288419716939937510 // Using a different pi from M_PI, don't ask me why
#define cAng 360.00 // A full angle
#define MULT 100 // so it can be seen in the window
#define maxval 12345

int main(){
    int x = 3, n = 3; // x is the biggest regular polygon, n is the current polygon
    float l, a, r = 1, ap, Ar, Pe; // l = length size, a = theta, r = the radius, ap = the apothem, Ar = the area and Pe the perimeter (yes this is useless)
    /*cout << fixed << setprecision(50);
    cout << "Insert polygon limit: "; // If we were using <iostream>:
    cin >> x;
    if(!cin.good()){
        x = INT_MAX;
    }if(x < 3){
        x = 3;
    }*/
    sf::RenderWindow window(sf::VideoMode(1000,600),"Archimedes' method for finding pi"); // create window
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.clear();

    // Center coordinates and font:
    const float cx = window.getSize().x/2;
    const float cy = window.getSize().y/2;
    sf::Font font;
    if(!font.loadFromFile("fonts/terminus/TerminusTTF-4.49.2.ttf")){};
    bool menuCheck = false;
    while(window.isOpen()){ // open window
    sf::Event event;
    while(window.pollEvent(event)){ // Close window if the ESC key is pressed:
        if(event.type==sf::Event::Closed) window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        while(menuCheck == false){
            window.clear();
            sf::Text MenuText;
            MenuText.setFont(font);
            stringstream menuString;
            menuString << "Choose the limit (right and left keys to change the unity, up and down to change by a factor of 10): ";
            MenuText.setString(menuString.str());
            MenuText.setCharacterSize(24);
            MenuText.setFillColor(sf::Color::White);
            MenuText.setOrigin(MenuText.getLocalBounds().width/2,MenuText.getLocalBounds().height/2);
            MenuText.setPosition(cx,cy-180);
            sf::Text xText;
            xText.setFont(font);
            xText.setString(to_string(x));
            xText.setCharacterSize(32);
            xText.setFillColor(sf::Color::White);
            xText.setOrigin(xText.getLocalBounds().width/2,xText.getLocalBounds().height/2);
            xText.setPosition(cx,cy);
            int tempX = x;
            sf::Time miliDelay = sf::milliseconds(10);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                tempX=tempX-1;
                miliDelay = sf::milliseconds(150);
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                tempX=tempX+1;;
                miliDelay = sf::milliseconds(150);
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                tempX=tempX*10;
                miliDelay = sf::milliseconds(150);
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                tempX=tempX/10;
                miliDelay = sf::milliseconds(150);
            }
            if(tempX >= 3 && tempX <= maxval){
                x = tempX;
                sf::sleep(miliDelay);
            }
            window.draw(MenuText);
            window.draw(xText);
            window.display();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                menuCheck = true;
            }
        }
        window.clear();
        //menuCheck = false;

    while(n <= x){ // don't ask me why not For
        if(event.type==sf::Event::Closed) window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        a = cAng/n;
        a = a/2;
        a = a*PI/180; // Transforming to radians
        //cout << a << "\n";
        l = sin(a);
        l = l*2;
        //cout << l << "\n";
        Pe = n*l;
        //cout << Pe << "\n";
        ap = cos(a);
        //cout << ap << "\n";
        Ar = Pe*ap/2;
        //cout << Ar << "\n";
        /*cout << n << "gon pi = " << Ar << ";\n"; // if we were using <iostream>
        */
        //Shapes:
        sf::Vertex apothem[]={
            sf::Vertex(sf::Vector2f(cx,cy)),
            sf::Vertex(sf::Vector2f(cx,cy+(ap*MULT)))
        };
        sf::Vertex radius[]={
            sf::Vertex(sf::Vector2f(cx,cy),sf::Color::Red),
            sf::Vertex(sf::Vector2f(cx+(l/2*MULT),cy+(ap*MULT)),sf::Color::Red)
        };

        sf::CircleShape polygon(r*MULT,n);
        polygon.setFillColor(sf::Color::Transparent);
        polygon.setOutlineThickness(1);
        polygon.setOutlineColor(sf::Color::White);
        polygon.setOrigin(polygon.getRadius(),polygon.getRadius());
        if(n%2==0){
            polygon.rotate(360/n/2);
        }
        polygon.setPosition(cx,cy);
        sf::CircleShape circle(r*MULT);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(1);
        circle.setOutlineColor(sf::Color::Red);
        circle.setOrigin(polygon.getRadius(),polygon.getRadius());
        circle.setPosition(cx,cy);

        #define textsize 24
        sf::Text nOfSizes;
        nOfSizes.setFont(font);
        nOfSizes.setString("Number of sizes: " + to_string(n));
        nOfSizes.setCharacterSize(textsize);
        nOfSizes.setFillColor(sf::Color::White);
        nOfSizes.setOrigin(nOfSizes.getLocalBounds().width/2,nOfSizes.getLocalBounds().height/2);
        nOfSizes.setPosition(cx,cy-130);
        sf::Text sRadius;
        sRadius.setFont(font);
        stringstream rString;
        rString << "Radius: " << setprecision(0) << fixed << r;
        sRadius.setString(rString.str());
        sRadius.setCharacterSize(textsize);
        sRadius.setFillColor(sf::Color::Red);
        sRadius.setPosition(cx+80,cy+60);
        sf::Text apothemText;
        apothemText.setFont(font);
        stringstream apString;
        apString << "Apothem: " << setprecision(10) << fixed << ap;
        apothemText.setString(apString.str());
        apothemText.setCharacterSize(textsize);
        apothemText.setFillColor(sf::Color::White);
        apothemText.setOrigin(apothemText.getLocalBounds().width/2,apothemText.getLocalBounds().height/2);
        apothemText.setPosition(cx,cy+115);
        sf::Text length;
        length.setFont(font);
        stringstream lString;
        lString << "Side length: " << setprecision(10) << fixed << l;
        length.setString(lString.str());
        length.setCharacterSize(textsize);
        length.setFillColor(sf::Color::White);
        length.setOrigin(length.getLocalBounds().width/2,length.getLocalBounds().height/2);
        length.setPosition(cx,cy+125+apothemText.getLocalBounds().height/2);
        sf::Text CircleArea;
        CircleArea.setFont(font);
        stringstream piString;
        piString << "Circle's area (actual pi): " << setprecision(30) << fixed << PI;
        CircleArea.setString(piString.str());
        CircleArea.setCharacterSize(textsize);
        CircleArea.setFillColor(sf::Color::White);
        CircleArea.setOrigin(CircleArea.getLocalBounds().width/2,CircleArea.getLocalBounds().height/2);
        CircleArea.setPosition(cx,cy+180);
        sf::Text pArea;
        pArea.setFont(font);
        stringstream polyString;
        polyString << "Polygon's area (estimated pi): " << setprecision(30) << fixed << Ar;
        pArea.setString(polyString.str());
        pArea.setCharacterSize(textsize);
        pArea.setFillColor(sf::Color::White);
        pArea.setOrigin(pArea.getLocalBounds().width/2,pArea.getLocalBounds().height/2);
        pArea.setPosition(cx,cy+190+CircleArea.getLocalBounds().height/2);

        window.clear();
        window.draw(nOfSizes);
        window.draw(radius,2,sf::Lines);
        window.draw(circle);
        window.draw(sRadius);
        window.draw(apothem,2,sf::Lines);
        window.draw(polygon);
        window.draw(length);
        window.draw(apothemText);
        window.draw(CircleArea);
        window.draw(pArea);
        window.display();
        n++;
        if(x == INT_MAX){
            if(Ar == PI){
                x = n-1;
            }
        }
        sf::Time microDelay = sf::microseconds(1000000/n);
        //cout<<microDelay.asMicroseconds()<<endl;
        sf::sleep(microDelay);
        //sf::sleep(sf::microseconds(1));
        if(n >= x){
            int comp = 0; // Messy way of comparing both numbers:
    double ppi = PI*100, pAr = Ar*100;
    //cout << ppi << " " << pAr << ";\n";
    bool uneq = false;
    while(uneq == false){
        int ipi = ppi;
        int pidigit = ipi/100;
        int iAr = pAr;
        int Ardigit = iAr/100;
        /*cout << ipi << " " << iAr << ";\n";
        cout << pidigit << " " << Ardigit << ";\n";*/
        ppi = ppi - pidigit*100;
        pAr = pAr - Ardigit*100;
        //cout << ppi << " " << pAr << ";\n";
        if(pidigit == Ardigit){
            comp++;
        }else{
            uneq = true;
        }
        //cout << comp << " " << uneq << ";\n";
        ppi = ppi*10;
        pAr = pAr*10;
        //cout << ppi << " " << pAr << ";\n";
    }
    /*cout << "Precision: " << comp << " digits;\n";
    cout << "Subtraction: " << PI-Ar << ";\n";*/
    sf::Text precision;
    precision.setFont(font);
    precision.setString("Precision: " + to_string(comp) + " digits");
    precision.setCharacterSize(24);
    precision.setFillColor(sf::Color::White);
    precision.setOrigin(precision.getLocalBounds().width/2,precision.getLocalBounds().height/2);
    precision.setPosition(cx,cy+240);
    sf::Text subtraction;
    subtraction.setFont(font);
    stringstream subtString;
    subtString << "Subtraction: " << setprecision(30) << fixed << PI-Ar;
    subtraction.setString(subtString.str());
    subtraction.setCharacterSize(24);
    subtraction.setFillColor(sf::Color::White);
    subtraction.setOrigin(subtraction.getLocalBounds().width/2,subtraction.getLocalBounds().height/2);
    subtraction.setPosition(cx,cy+250+precision.getLocalBounds().height/2);
    window.draw(precision);
    window.draw(subtraction);
    window.display();
        }
    }
    /*cout << "∞gon pi = " << PI << ";\n";*/
    }
    }
    return 0;
}