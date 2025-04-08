#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <vector>
#include <cmath>


const float PI = 3.14159265359f;


void drawCube(float size) {
    float half = size / 2.0f;
    glBegin(GL_QUADS);

    
    glColor3f(1.0f, 0.0f, 0.0f); // Красный
    glVertex3f(-half, -half, half);
    glVertex3f(half, -half, half);
    glVertex3f(half, half, half);
    glVertex3f(-half, half, half);

    
    glColor3f(0.0f, 1.0f, 0.0f); // Зеленый
    glVertex3f(-half, -half, -half);
    glVertex3f(-half, half, -half);
    glVertex3f(half, half, -half);
    glVertex3f(half, -half, -half);

    
    glColor3f(0.0f, 0.0f, 1.0f); // Синий
    glVertex3f(-half, half, -half);
    glVertex3f(-half, half, half);
    glVertex3f(half, half, half);
    glVertex3f(half, half, -half);

    
    glColor3f(1.0f, 1.0f, 0.0f); // Желтый
    glVertex3f(-half, -half, -half);
    glVertex3f(half, -half, -half);
    glVertex3f(half, -half, half);
    glVertex3f(-half, -half, half);

    
    glColor3f(1.0f, 0.0f, 1.0f); // Фиолетовый
    glVertex3f(half, -half, -half);
    glVertex3f(half, half, -half);
    glVertex3f(half, half, half);
    glVertex3f(half, -half, half);

    
    glColor3f(0.0f, 1.0f, 1.0f); // Голубой
    glVertex3f(-half, -half, -half);
    glVertex3f(-half, -half, half);
    glVertex3f(-half, half, half);
    glVertex3f(-half, half, -half);

    glEnd();
}


void drawPyramid(float baseSize, float height) {
    float half = baseSize / 2.0f;
    glBegin(GL_TRIANGLES);

    
    glColor3f(1.0f, 0.5f, 0.0f); // Оранжевый
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(-half, 0.0f, half);
    glVertex3f(half, 0.0f, half);

    
    glColor3f(0.5f, 0.0f, 1.0f); // Фиолетовый
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(half, 0.0f, half);
    glVertex3f(half, 0.0f, -half);

    
    glColor3f(0.0f, 1.0f, 0.5f); // Мятный
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(half, 0.0f, -half);
    glVertex3f(-half, 0.0f, -half);

    
    glColor3f(1.0f, 0.0f, 0.5f); // Розовый
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(-half, 0.0f, -half);
    glVertex3f(-half, 0.0f, half);

    glEnd();

    
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f); // Серый
    glVertex3f(-half, 0.0f, half);
    glVertex3f(half, 0.0f, half);
    glVertex3f(half, 0.0f, -half);
    glVertex3f(-half, 0.0f, -half);
    glEnd();
}


void drawCylinder(float radius, float height, int segments) {
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        glColor3f((float)i / segments, 1.0f - (float)i / segments, 0.5f); // Градиент
        glVertex3f(x, 0.0f, z);
        glVertex3f(x, height, z);
    }
    glEnd();

    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5f, 0.5f, 1.0f); // Светло-синий
    glVertex3f(0.0f, height, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, height, z);
    }
    glEnd();

    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5f, 0.5f, 0.5f); // Серый
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
}


void drawSphere(float radius, int segments, int rings) {
    for (int i = 0; i <= rings; ++i) {
        float lat0 = PI * (-0.5f + (float)(i - 1) / rings);
        float z0 = radius * sin(lat0);
        float zr0 = radius * cos(lat0);

        float lat1 = PI * (-0.5f + (float)i / rings);
        float z1 = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= segments; ++j) {
            float lng = 2.0f * PI * (float)(j - 1) / segments;
            float x = cos(lng);
            float y = sin(lng);

            glColor3f(1.0f, 1.0f, 0.0f); // Желтый
            glVertex3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

int main() {
    sf::Window window(sf::VideoMode(800, 600), "3D Scene with OpenGL", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(4.0, 4.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        
        glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 0.0f);
        drawCube(2.0f);
        glPopMatrix();

        
        glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f);
        drawPyramid(2.0f, 3.0f);
        glPopMatrix();

        
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -3.0f);
        drawCylinder(1.0f, 3.0f, 30);
        glPopMatrix();

        
        glPushMatrix();
        glTranslatef(-3.0f, 3.0f, 3.0f);
        drawSphere(0.5f, 20, 20);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3.0f, 3.0f, 3.0f);
        drawSphere(0.5f, 20, 20);
        glPopMatrix();

        window.display();
    }

    return 0;
}