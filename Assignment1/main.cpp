#include <SFML/Graphics.hpp>
#include <optional>
#include <fstream>
#include<iostream>
#include<string>
#include <vector>

class Circle
{
    std::string m_name;
    float m_xPos;
    float m_yPos;
    float m_xVelocity;
    float m_yVelocity;
    float m_r;
    float m_g;
    float m_b;
    float m_radius;

    sf::CircleShape shape;
    sf::Font m_font;
    sf::Text m_text;

    public:

    Circle(std::string name, float xPos, float yPos, float xVelocity, float yVelocity, int r, int g, int b, float radius)
        :m_name         (name)
        ,m_xPos         (xPos)
        ,m_yPos         (yPos)
        ,m_xVelocity    (xVelocity)
        ,m_yVelocity    (yVelocity)
        ,m_r            (r)
        ,m_g            (g)
        ,m_b            (b)
        ,m_radius       (radius)
        ,m_font         ()
        ,m_text         (m_font)
    {
        shape.setRadius(m_radius);
        shape.setPosition(sf::Vector2f (m_xPos,m_yPos));
        shape.setFillColor(sf::Color(m_r,m_g,m_b));

        if (!m_font.openFromFile("C:\\Windows\\Fonts\\Calibri.ttf"))
        {
            std::cerr << "Couldn't load font" << std::endl;
            exit(-1);
        }
        
        m_text.setString(m_name);
        m_text.setPosition(sf::Vector2f (m_xPos, m_yPos));
        m_text.setCharacterSize(24);

        std::cout << "Circle Constructor" << std::endl;
    }

    void update(sf::RenderWindow &window)
    {
        sf::Vector2u size = window.getSize();
        auto [width, height] = size;

        m_xPos += m_xVelocity;
        m_yPos += m_yVelocity;

        if (m_xPos + (2*m_radius) > width || m_xPos < 0)
        {
            m_xVelocity *= -1;
            m_xPos += m_xVelocity * 2;
        }
        if (m_yPos + (2*m_radius)> height || m_yPos < 0)
        {
            m_yVelocity *= -1;
            m_yPos += m_yVelocity * 2;
        }

        m_text.setPosition(sf::Vector2f (m_xPos + m_radius/2,m_yPos + m_radius/2));
        shape.setPosition(sf::Vector2f (m_xPos,m_yPos));

        window.draw(shape);
        window.draw(m_text);
    }
};

class Rectangle
{
    std::string m_name;
    float m_xPos;
    float m_yPos;
    float m_xVelocity;
    float m_yVelocity;
    float m_r;
    float m_g;
    float m_b;
    float m_width;
    float m_height;

    sf::RectangleShape shape;
    sf::Font m_font;
    sf::Text m_text;

    public:

    Rectangle(std::string name, float xPos, float yPos, float xVelocity, float yVelocity, int r, int g, int b, float width, float height)
        :m_name         (name)
        ,m_xPos         (xPos)
        ,m_yPos         (yPos)
        ,m_xVelocity    (xVelocity)
        ,m_yVelocity    (yVelocity)
        ,m_r            (r)
        ,m_g            (g)
        ,m_b            (b)
        ,m_width        (width)
        ,m_height       (height)
        ,m_font         ()
        ,m_text         (m_font)
    {
        shape.setSize({m_width, m_height});
        shape.setPosition(sf::Vector2f (m_xPos,m_yPos));
        shape.setFillColor(sf::Color(m_r,m_g,m_b));

        if (!m_font.openFromFile("C:\\Windows\\Fonts\\Calibri.ttf"))
        {
            std::cerr << "Couldn't load font" << std::endl;
            exit(-1);
        }
        
        m_text.setString(m_name);
        m_text.setPosition(sf::Vector2f (m_xPos, m_yPos));
        m_text.setCharacterSize(24);

        std::cout << "Rectangle Constructor" << std::endl;
    }

    void update(sf::RenderWindow &window)
    {
        sf::Vector2u size = window.getSize();
        auto [width, height] = size;

        m_xPos += m_xVelocity;
        m_yPos += m_yVelocity;

        if (m_xPos + m_width > width || m_xPos < 0)
        {
            m_xVelocity *= -1;
            m_xPos += m_xVelocity * 2;
        }
        if (m_yPos + m_height > height || m_yPos < 0)
        {
            m_yVelocity *= -1;
            m_yPos += m_yVelocity * 2;
        }

        m_text.setPosition(sf::Vector2f (m_xPos ,m_yPos));
        shape.setPosition(sf::Vector2f (m_xPos,m_yPos));

        window.draw(shape);
        window.draw(m_text);
        std::cout << m_name << std::endl;
    }
};


int main()
{

    std::ifstream fin("configuration.txt");
    std::string temp;
    fin >> temp;

    unsigned int wWidth;
    unsigned int wHeight;
    fin >> wWidth;
    fin >> wHeight;

    std::string fontPath; 
    int characterSize;
    int fontR;
    int fontG;
    int fontB;

    fin >> temp;
    fin >> fontPath;
    fin >> characterSize;
    fin >> fontR;
    fin >> fontG;
    fin >> fontB;

    std::vector<Circle> circles;
    std::vector<Rectangle> rectangles;

    std::string name;
    float xPos;
    float yPos;
    float xVelocity;
    float yVelocity;
    int r;
    int g;
    int b;
    int radius;
    int width;
    int height;

    while (fin >> temp)
    {
        if (temp == "Circle")
        {
            fin >> name;
            fin >> xPos;
            fin >> yPos;
            fin >> xVelocity;
            fin >> yVelocity;
            fin >> r;
            fin >> g;
            fin >> b;
            fin >> radius;

            circles.push_back(Circle(name, xPos, yPos, xVelocity, yVelocity, r, g, b, radius));

            std::cout << "Circle" << std::endl;
        }
        else if (temp == "Rectangle")
        {
            fin >> name;
            fin >> xPos;
            fin >> yPos;
            fin >> xVelocity;
            fin >> yVelocity;
            fin >> r;
            fin >> g;
            fin >> b;
            fin >> width;
            fin >> height;

            rectangles.push_back(Rectangle(name, xPos, yPos, xVelocity, yVelocity, r, g, b, width, height));

            std::cout << "Rectangle" << std::endl;
        }
        else
        {
            std::cout << "Unknown" << std::endl;
        }
    }

    //Circle circle1("name", 300.0f, 300.0f, 1.0f, 1.0f, 255, 0, 0,50);

    //Rectangle rectangle1("name", 300.0f, 300.0f, -2.0f, -2.0f, 255, 0, 0,50, 50);


    sf::RenderWindow window(
        sf::VideoMode({wWidth, wHeight}),
        "SFML Window"
    );
    //window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        for (Circle &circle: circles)
        {
            circle.update(window);
        }
        for (Rectangle &rectangle: rectangles)
        {
            rectangle.update(window);
        }
        //circle1.update(window);
        //rectangle1.update(window);
        window.display();
    }

    return 0;
}