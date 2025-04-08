#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <GL/glu.h>
#include <vector>
#include <iostream>


void multiplyMatrix(float result[4][4], const float mat1[4][4], const float mat2[4][4]) {
    float temp[4][4] = {};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                temp[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    std::copy(&temp[0][0], &temp[0][0] + 16, &result[0][0]);
}

void applyMatrix(const float matrix[4][4]) {
    glMultMatrixf(&matrix[0][0]);
}


void createTranslationMatrix(float tx, float ty, float tz, float matrix[4][4]) {
    std::fill(&matrix[0][0], &matrix[0][0] + 16, 0.0f);
    matrix[0][0] = 1.0f;
    matrix[1][1] = 1.0f;
    matrix[2][2] = 1.0f;
    matrix[3][3] = 1.0f;
    matrix[3][0] = tx;
    matrix[3][1] = ty;
    matrix[3][2] = tz;
}

void createScaleMatrix(float sx, float sy, float sz, float matrix[4][4]) {
    std::fill(&matrix[0][0], &matrix[0][0] + 16, 0.0f);
    matrix[0][0] = sx;
    matrix[1][1] = sy;
    matrix[2][2] = sz;
    matrix[3][3] = 1.0f;
}

void createRotationMatrix(float angle, char axis, float matrix[4][4]) {
    float radians = angle * 3.14159265f / 180.0f;
    std::fill(&matrix[0][0], &matrix[0][0] + 16, 0.0f);
    matrix[3][3] = 1.0f;
    if (axis == 'x') {
        matrix[0][0] = 1.0f;
        matrix[1][1] = std::cos(radians);
        matrix[1][2] = -std::sin(radians);
        matrix[2][1] = std::sin(radians);
        matrix[2][2] = std::cos(radians);
    } else if (axis == 'y') {
        matrix[0][0] = std::cos(radians);
        matrix[0][2] = std::sin(radians);
        matrix[1][1] = 1.0f;
        matrix[2][0] = -std::sin(radians);
        matrix[2][2] = std::cos(radians);
    } else if (axis == 'z') {
        matrix[0][0] = std::cos(radians);
        matrix[0][1] = -std::sin(radians);
        matrix[1][0] = std::sin(radians);
        matrix[1][1] = std::cos(radians);
        matrix[2][2] = 1.0f;
    }
}


void drawCube() {
    glBegin(GL_QUADS);

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Top face
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Bottom face
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Right face
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Left face
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();
}

int main() {
    sf::Window window(sf::VideoMode(800, 600), "3D Cube with Transformations", sf::Style::Default, sf::ContextSettings(24));
    window.setFramerateLimit(60);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 

    float transformationMatrix[4][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                float tempMatrix[4][4];

                if (event.key.code == sf::Keyboard::W) {
                    createTranslationMatrix(0.0f, 0.1f, 0.0f, tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::S) {
                    createTranslationMatrix(0.0f, -0.1f, 0.0f, tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::A) {
                    createTranslationMatrix(-0.1f, 0.0f, 0.0f, tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::D) {
                    createTranslationMatrix(0.1f, 0.0f, 0.0f, tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::Q) {
                    createScaleMatrix(1.1f, 1.1f, 1.1f, tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::E) {
                    createScaleMatrix(0.9f, 0.9f, 0.9f, tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::Left) {
                    createRotationMatrix(5.0f, 'y', tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::Right) {
                    createRotationMatrix(-5.0f, 'y', tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::Up) {
                    createRotationMatrix(5.0f, 'x', tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                } else if (event.key.code == sf::Keyboard::Down) {
                    createRotationMatrix(-5.0f, 'x', tempMatrix);
                    multiplyMatrix(transformationMatrix, transformationMatrix, tempMatrix);
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -8.0f);

        applyMatrix(transformationMatrix);
        drawCube();

        window.display();
    }

    return 0;
}