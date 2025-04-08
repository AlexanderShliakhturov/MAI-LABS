#include <GLFW/glfw3.h>
#include <cmath>
#include <algorithm>
#include <iostream>

void drawCirclePoints(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
}

void bresenhamCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        drawCirclePoints(xc, yc, x, y);
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int radius = 50;
int centerX = 400, centerY = 300;
bool pulsate = true;
float pulseSpeed = 10.0f;
float pulseDelta = 0;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) radius += 1;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) radius -= 1;
    radius = std::max(1, radius);
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) pulsate = !pulsate;
}

void draw(GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); 

    glBegin(GL_POINTS);

    int dynamicRadius = radius + static_cast<int>(pulseDelta);
    bresenhamCircle(centerX, centerY, std::max(1, dynamicRadius));

    glEnd();
    glfwSwapBuffers(window);
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow *window = glfwCreateWindow(800, 600, "Bresenham Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, 800, 0, 600, -1, 1); 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        if (pulsate) pulseDelta = sin(glfwGetTime() * pulseSpeed) * 20;

        draw(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}