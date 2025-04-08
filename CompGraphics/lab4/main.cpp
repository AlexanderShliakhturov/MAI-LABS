#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <iostream>

float specularIntensity = 1.0f;
float specularPower = 32.0f;
float lightPosition[3] = { 1.0f, 1.0f, 1.0f };

void handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        specularIntensity += 0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        specularIntensity = std::max(0.0f, specularIntensity - 0.1f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        specularPower = std::max(1.0f, specularPower - 1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        specularPower += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        lightPosition[1] += 0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        lightPosition[1] -= 0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        lightPosition[0] -= 0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        lightPosition[0] += 0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        lightPosition[2] -= 0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        lightPosition[2] += 0.1f;
    }
}

void drawPyramid() {
    glBegin(GL_TRIANGLES);

    // Передняя грань
    glNormal3f(0.0f, 0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Правая грань
    glNormal3f(1.0f, 0.5f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Задняя грань
    glNormal3f(0.0f, 0.5f, -1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Левая грань
    glNormal3f(-1.0f, 0.5f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    // Основание
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();
}

int main() {
    sf::Window window(sf::VideoMode(800, 600), "3D Pyramid with Specular Lighting", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        handleInput();

        GLfloat lightPos[] = { lightPosition[0], lightPosition[1], lightPosition[2], 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

        GLfloat specular[] = { specularIntensity, specularIntensity, specularIntensity, 1.0f };
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, specularPower);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(0.0, 2.0, 5.0,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);

        drawPyramid();

        window.display();
    }

    return 0;
}
