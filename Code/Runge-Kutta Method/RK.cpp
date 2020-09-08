#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "RK.hpp"

#define M_PI 3.14159265358979323846


const std::vector<long double> cond_osc1 = {0, 1, 0, 0};
const std::vector<long double> cond_osc2 = {2, 0, 0, 0};
const std::vector<long double> cond_osc3 = {3, 0, 0, 0};
const std::vector<long double> cond_lor1 = {1, 0, 0.5, 0};
const std::vector<long double> cond_lor2 = {2.1, 0, 0, 0};
const std::vector<long double> cond_lor3 = {0.03, 1, 0.7, 0};
const std::vector<long double> cond_dpen1 = {1.047, M_PI, 0, 0};
const std::vector<long double> cond_dpen2 = {1, M_PI/2, 0.1, 0};
const std::vector<long double> cond_dpen3 = {0.99, M_PI/4, 0.2, 0};
const std::vector<long double> cond_chua1 = {0.2, 0.3, 0.1, 0};
const std::vector<long double> cond_chua2 = {1, 0.5, 0.8, 0};
const std::vector<long double> cond_chua3 = {0.03, 1, 0.7, 0};
const std::vector<long double> cond_tbpr1 = {1.2, 0, 0, -1.04935750983};
const std::vector<long double> cond_tbpr2 = {0.994, 0, 0, -2.00158510637908252240537862224};
const std::vector<long double> cond_lmb1 = {0.825, 0.835, 0.18, 0};
const std::vector<long double> cond_lmb2 = {0.5, 0.55, 0.1, 0};
const std::vector<long double> cond_lmb3 = {0.3, 0.9, 0.4, 0}; //stale warunki poczatkowe uzyte w pracy

void coordinate_system(sf::RenderWindow& window, std::vector<int> plain, sf::Font font, double scale)//funkcja rysujaca uklad wspolrzednych
{
    sf::Text Axe("", font, 20);
    Axe.setOrigin(Axe.getLocalBounds().width/2, Axe.getLocalBounds().height/2);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(640,10)),
        sf::Vertex(sf::Vector2f(640,790))
    };

    sf::Vertex line2[] =
    {
        sf::Vertex(sf::Vector2f(10,400)),
        sf::Vertex(sf::Vector2f(1270,400))
    };

    window.draw(line,2,sf::Lines);
    window.draw(line2, 2, sf::Lines);

    for(int i = 0; i < 2; ++i)
    {
        switch (plain[i])
        {
        case 0:
            Axe.setString("T");
            break;
        case 1:
            Axe.setString("X");
            break;
        case 2:
            Axe.setString("Y");
            break;
        case 3:
            Axe.setString("Z");
            break;
        case 4:
            Axe.setString("W");
            break;
        }

        switch (i)
        {
        case 0:
            Axe.setPosition( 1250, 420 );
            break;
        case 1:
            Axe.setPosition( 670 , 30 );
            break;
        }

        window.draw(Axe);
    }

    int x_coor = 10;
    int y_coor = 10;
    int x_power = 10;
    int y_power = 10;

    while( (1280)/x_power > 100 )
    {
        x_power+=10;
    }

    x_coor = x_power;
    y_coor = x_power;
    y_power = x_power;

    for(int i = 0; i < (1280/x_power); ++ i)
    {
        sf::Vertex line3[] =
        {
            sf::Vertex(sf::Vector2f(x_coor,395)),
            sf::Vertex(sf::Vector2f(x_coor,405))
        };
        window.draw(line3, 2, sf::Lines);
        x_coor+=x_power;
    }
    for(int i = 0; i < (800/y_power) ; ++i)
    {
        sf::Vertex line4[] =
        {
            sf::Vertex(sf::Vector2f(635, y_coor)),
            sf::Vertex(sf::Vector2f(645, y_coor))
        };
        window.draw(line4, 2, sf::Lines);
        y_coor+=y_power;
    }

    sf::Text scale_text("Scale:", font, 20);
    sf::Text scale_coor_2("", font, 20);

    scale_text.setPosition(sf::Vector2f(900,730));
    scale_coor_2.setPosition(sf::Vector2f(970, 730));

    std::string scale_string = std::to_string(x_power/scale);
    scale_coor_2.setString(scale_string.substr(0, 5));

    window.draw(scale_coor_2);
    window.draw(scale_text);

}

void Menu() //funkcja glowna operujaca na glownym ekranie
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window( sf::VideoMode( 1280, 800 ), "Runge-Kutta Method", sf::Style::None, settings );

    window.setFramerateLimit(60);

    sf::Font font;
    if ( !font.loadFromFile( "menu.ttf" ) )
        std::cout << "Can't find the font file" << std::endl;

    sf::Text exit("Exit (ESC)", font, 20);
    exit.setOrigin(exit.getLocalBounds().width/2, exit.getLocalBounds().height/2);
    exit.setPosition( 1150.0f, 720.0f );

    sf::Text back_1("Back (B)", font, 20);
    back_1.setOrigin(back_1.getLocalBounds().width/2, back_1.getLocalBounds().height/2);
    back_1.setPosition( 1150.0f, 750.0f );

    sf::Text start("Choose one of the equations by clicking number on your keyboard", font, 17);
    start.setPosition(sf::Vector2f(10.0f, 0.0f));

    sf::Text equation_1("1. Harmonic oscillator:\n\nx'(t) = y\ny'(t) = -kx\n\nwith k = 1.\n", font, 17);
    equation_1.setPosition(sf::Vector2f(10.0f, 20.0f));


    sf::Text equation_2("2. Lorenz Attractor:\n\nx'(t) = a(y(t) - x(t))\ny'(t) = bx(t) - y(t) - x(t)z(t)\nz'(t) = x(t)y(t) - cz(t)\n\nwith a = 10, b = 28, c = 8/3.", font, 17);
    equation_2.setPosition(sf::Vector2f(10.0f, 170.0f));


    sf::Text equation_3("3. Double pendulum:\n\nx'(t) = (cz(t) - bcos(y(t)-X(t))w(t))/(ac - b^2cos^2(y2-y1))\ny'(t) = (aw(t) - bcos(y(t)-X(t))z(t))/(ac - b^2cos^2(y2-y1))\nz'(t) = -bsin(y(t) - x(t))x'(t)y'(t) - psin(x(t))\nw'(t) = -bsin(y(t) - x(t))x'(t)y'(t) - qsin(y(t))\n\nwith a=(1/3(m1) + (m2))(l1)^2, b = 1/2(m2)(l1)(l2), c = 1/3(m2)(l2)^2\np = (1/2(m1)+(m2))g(l1), q = (m2)(l2)1/2g,\n m1 = 2, m2 = 0.5, l1 = 1, l2 = 0.6, g = 9.81\n", font, 17);
    equation_3.setPosition(sf::Vector2f(10.0f, 330.0f));


    sf::Text equation_4("4. Chua's equation:\n\nx'(t) = a(y(t) - x(t) - ( bx(t) + ( (c - b)/2 |x(t) + 1| - |x(t) - 1|)\ny'(t) = x(t) - y(t) + z(t)\nz'(t) = dy(t)\n\nwith a = 15, b = -5/7, c = -8/7, d = -25.58.", font, 17);
    equation_4.setPosition(sf::Vector2f(640.0f, 0.0f));


    sf::Text equation_5("5. Three-body Problem:\n\nx'(t) = z(t)\ny'(t) = w(t)\nz'(t) = x(t) + 2y(t) - l(r1)^(-3)(x(t)+ m) - m(r2)^(-3)(x(t) - l)\nw'(t) = y(t) - 2z(t) - ly(t)(r1)^(-3) - my(t)r2^(-3)\n\nwith r1 = ( (x(t) + m)^2 + y(t)^2 )^(1/2),\nr2 = ( (x(t) - l)^2 + y(t)^2 )^(1/2), m = 1/82.45 , l = 1 - m.", font, 17);
    equation_5.setPosition(sf::Vector2f(640.0f, 160.0f));


    sf::Text equation_6("6. Labour market model:\n\nx'(t) = g(x(t)^D - x(t))\ny'(t) = d(x(t)^S - y(t))\n z'(t) = l(x(t) - y(t))\n\nwith x(t)^D = (z(t)/(aD))^(1/(a-1)), x(t)^S = 1/(1+z(t)^(b/(b-1))) and D=1,\n a=0.15, b=-10, d=4, l=4.", font, 17);
    equation_6.setPosition(sf::Vector2f(640.0f, 360.0f));

    sf::Text plain("Choose plain to draw: ", font, 17);
    plain.setPosition(sf::Vector2f(10.0f, 570.0f));

    sf::Text xy(" (1)XY ", font, 17);
    xy.setPosition(sf::Vector2f(10.0f, 590.0f));

    sf::Text xz(" (2)XZ ", font, 17);
    xz.setPosition(sf::Vector2f(70.0f, 590.0f));

    sf::Text xw(" (3)XW ", font, 17);
    xw.setPosition(sf::Vector2f(130.0f, 590.0f));

    sf::Text yz(" (4)YZ ", font, 17);
    yz.setPosition(sf::Vector2f(190.0f, 590.0f));

    sf::Text yw(" (5)YW ", font, 17);
    yw.setPosition(sf::Vector2f(250.0f, 590.0f));

    sf::Text zw(" (6)ZW ", font, 17);
    zw.setPosition(sf::Vector2f(310.0f, 590.0f));

    sf::Text counting("After your choice please wait, calculations may take a while because of precision", font, 20);
    counting.setPosition(sf::Vector2f(10.0f, 750.0f));
    counting.setFillColor(sf::Color::Red);

    bool menu = true;
    int opt = 0;
    bool drawing =false;
    bool equ_choose = true;
    bool plain_bool = false;
    std::vector<int> plain_ch = {0,0};
    RungeKutta equ, equ2, equ3;
    while ( window.isOpen() ) //glowna petla programu i okna
    {
        sf::Event Event;
        while ( window.pollEvent( Event ) ) //petla obslugujaca wszystkie wydarzenia
        {
            switch ( Event.type )
            {
                case sf::Event::Closed: //zamkniecie okna
                    window.close();
                break;
                case sf::Event::Resized:
                    window.setSize(sf::Vector2u( 1280 , 800 ));
                break;
                case sf::Event::KeyPressed:
                {
                    switch(Event.key.code)
                    {
                        case sf::Keyboard::Escape: //przycisk zamkniecia okna
                            window.close();
                        break;
                        case sf::Keyboard::B:
                            equation_1.setFillColor(sf::Color::White);
                            equation_2.setFillColor(sf::Color::White);
                            equation_3.setFillColor(sf::Color::White);
                            equation_4.setFillColor(sf::Color::White);
                            equation_5.setFillColor(sf::Color::White);
                            equation_6.setFillColor(sf::Color::White);
                            xy.setFillColor(sf::Color::White);
                            xz.setFillColor(sf::Color::White);
                            xw.setFillColor(sf::Color::White);
                            yz.setFillColor(sf::Color::White);
                            yw.setFillColor(sf::Color::White);
                            zw.setFillColor(sf::Color::White);
                            opt = 0;
                            plain_ch = {0,0};
                            equ_choose = true;
                            drawing = false;
                            menu = true;
                            plain_bool = false;
                        break;
                        case sf::Keyboard::Num1: //obsluga klawiatury
                            if(equ_choose == true)
                            {
                                opt = 1;
                                equation_1.setFillColor(sf::Color::Red);
                                equ_choose = false;
                            }
                            else
                            {
                                plain_ch = {1,2};
                                xy.setFillColor(sf::Color::Red);
                                plain_bool = true;
                            }
                            break;
                        case sf::Keyboard::Num2:
                            if(equ_choose == true)
                            {
                                opt = 2;
                                equation_2.setFillColor(sf::Color::Red);
                                equ_choose = false;
                            }
                            else
                            {
                                plain_ch = {1,3};
                                xz.setFillColor(sf::Color::Red);
                                plain_bool = true;
                            }
                            break;
                        case sf::Keyboard::Num3:
                            if(equ_choose == true)
                            {
                                opt = 3;
                                equation_3.setFillColor(sf::Color::Red);
                                equ_choose = false;
                            }
                            else
                            {
                                plain_ch = {1,4};
                                xw.setFillColor(sf::Color::Red);
                                plain_bool = true;
                            }
                            break;
                        case sf::Keyboard::Num4:
                            if(equ_choose == true)
                            {
                                opt = 4;
                                equation_4.setFillColor(sf::Color::Red);
                                equ_choose = false;
                            }
                            else
                            {
                                plain_ch = {2,3};
                                yz.setFillColor(sf::Color::Red);
                                plain_bool = true;
                            }
                            break;
                        case sf::Keyboard::Num5:
                            if(equ_choose == true)
                            {
                                opt = 5;
                                equation_5.setFillColor(sf::Color::Red);
                                equ_choose = false;
                            }
                            else
                            {
                                plain_ch = {2,4};
                                yw.setFillColor(sf::Color::Red);
                                plain_bool = true;
                            }
                            break;
                        case sf::Keyboard::Num6:
                            if(equ_choose == true)
                            {
                                opt = 6;
                                equation_6.setFillColor(sf::Color::Red);
                                equ_choose = false;
                            }
                            else
                            {
                                plain_ch = {3,4};
                                zw.setFillColor(sf::Color::Red);
                                plain_bool = true;
                            }
                            break;
                    }
                }
                break;
            }
        }

    window.clear();
    if(menu == true)
    {
        window.draw(start);
        window.draw(exit);
        window.draw(back_1);
        window.draw(equation_1);
        window.draw(equation_2);
        window.draw(equation_3);
        window.draw(equation_4);
        window.draw(equation_5);
        window.draw(equation_6);
        if(equ_choose == false)
        {
            window.draw(plain);
            window.draw(xy);
            window.draw(xz);
            window.draw(xw);
            window.draw(yz);
            window.draw(yw);
            window.draw(zw);
            window.draw(counting);
            if(plain_bool == true)
            {
                menu = false;
                drawing = true;
            }
        }

    }
    else
    {
        if(drawing == true )
        {
            std::vector<long double> conditions_ld;
            window.draw( exit );
            window.draw( back_1 );

            std::vector<long double> resolutions, resolutions2, resolutions3;

                switch(opt) //uzupelnianie warunkow
                {
                case 1:
                    coordinate_system(window, plain_ch, font, 100);
                    equ.fill_conditions(cond_osc1);
                    equ.fill_parameters(0.005, 1, 100);
                    equ2.fill_conditions(cond_osc2);
                    equ2.fill_parameters(0.005, 1, 100);
                    equ3.fill_conditions(cond_osc3);
                    equ3.fill_parameters(0.005, 1, 100);
                    break;
                case 2:
                    coordinate_system(window, plain_ch, font, 7);
                    equ.fill_conditions(cond_lor1);
                    equ.fill_parameters(0.001, 2, 7);
                    equ2.fill_conditions(cond_lor2);
                    equ2.fill_parameters(0.001, 2, 7);
                    equ3.fill_conditions(cond_lor3);
                    equ3.fill_parameters(0.001, 2, 7);
                    break;
                case 3:
                    coordinate_system(window, plain_ch, font, 50);
                    equ.fill_conditions(cond_dpen1);
                    equ.fill_parameters(0.005, 3, 50);
                    equ2.fill_conditions(cond_dpen2);
                    equ2.fill_parameters(0.005, 3, 50);
                    equ3.fill_conditions(cond_dpen3);
                    equ3.fill_parameters(0.005, 3, 50);
                    break;
                case 4:
                    coordinate_system(window, plain_ch, font, 100);
                    equ.fill_conditions(cond_chua1);
                    equ.fill_parameters(0.005, 4, 100);
                    equ2.fill_conditions(cond_chua2);
                    equ2.fill_parameters(0.005, 4, 100);
                    equ3.fill_conditions(cond_chua3);
                    equ3.fill_parameters(0.005, 4, 100);
                    break;
                case 5:
                    coordinate_system(window, plain_ch, font, 150);
                    equ.fill_conditions(cond_tbpr1);
                    equ.fill_parameters(0.001, 5, 150);
                    equ2.fill_conditions(cond_tbpr2);
                    equ2.fill_parameters(0.001, 5, 150);
                    break;
                case 6:
                    coordinate_system(window, plain_ch, font, 350);
                    equ.fill_conditions(cond_lmb1);
                    equ.fill_parameters(0.001, 6, 350);
                    equ2.fill_conditions(cond_lmb2);
                    equ2.fill_parameters(0.001, 6, 350);
                    equ3.fill_conditions(cond_lmb3);
                    equ3.fill_parameters(0.001, 6, 350);
                    break;
                }

                resolutions = equ.make_step();
                resolutions2 = equ2.make_step();

                if(opt != 5)
                    resolutions3 = equ3.make_step();

                for(int i = 0; i < 60000; ++i) //petla rysujaca kolejne linie
                {
                    resolutions = equ.draw(window, resolutions, plain_ch, equ.scale, sf::Color::Magenta);
                    resolutions2 = equ2.draw(window, resolutions2, plain_ch, equ2.scale, sf::Color::Blue);
                    if( opt != 5 )
                        resolutions3 = equ3.draw(window, resolutions3, plain_ch, equ3.scale, sf::Color::Yellow);
                }
        }
    }
    window.display();
    sf::Time time_1 = sf::seconds(1);
    sf::sleep( time_1 );
    }
}

int main()
{
    Menu();
    return 0;
}
