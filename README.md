#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <string>


// Window dimensions
int screenWidth = 900;
int screenHeight = 700;

// Paddle properties
float paddleWidth = 200.0f;
float paddleHeight = 15.0f;
float paddleSpeed = 5.0f;
float paddleX = screenWidth / 2 - paddleWidth / 2;
float paddleY = 20.0f;

// Ball properties
float ballRadius = 12.0f;
float ballSpeedX = 3.0f;
float ballSpeedY = 3.0f;
float ballX = screenWidth / 2;
float ballY = screenHeight / 2;

// Score
int score = 0;

// Function to handle window resizing
void reshape(int w, int h) {
    screenWidth = w;
    screenHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

// Function to draw the paddle
void drawPaddle() {
    glColor3f(0,1,0.7); // cyan color for paddle
    glBegin(GL_QUADS);
    glVertex2f(paddleX, paddleY);
    glVertex2f(paddleX + paddleWidth, paddleY);
    glVertex2f(paddleX + paddleWidth, paddleY + paddleHeight);
    glVertex2f(paddleX, paddleY + paddleHeight);
    glEnd();
}

// Function to draw the ball
void drawBall() {
    glColor3f(0.7,1,0); // Green color for ball
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159 / 180;
        glVertex2f(ballX + cos(rad) * ballRadius, ballY + sin(rad) * ballRadius);
    }
    glEnd();
}

// Function to handle keyboard input  using call-back function
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Escape key
            exit(0);
            break;
    }
}

// Function to update game state
void update(int value) {
    // Move paddle
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Left arrow key
        paddleX -= paddleSpeed;
        if (paddleX < 0) paddleX = 0;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Right arrow key
        paddleX += paddleSpeed;
        if (paddleX + paddleWidth > screenWidth) paddleX = screenWidth - paddleWidth;
    }

    // Move ball
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Ball collision with walls
    if (ballX + ballRadius >= screenWidth || ballX - ballRadius <= 0) {
        ballSpeedX = -ballSpeedX;
    }
    if (ballY + ballRadius >= screenHeight) {
        ballSpeedY = -ballSpeedY;
    }

    // Ball collision with paddle
    if (ballY - ballRadius <= paddleY + paddleHeight && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
        ballSpeedY = -ballSpeedY;
        score++; // Increment score when ball hits the paddle
    }

    // Ball out of bounds
    if (ballY - ballRadius <= 0) {
        std::cout << "Game Over! Score: " << score << std::endl;
        exit(0);
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Function to render the scene
void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw paddle and ball
    drawPaddle();
    drawBall();

    // Draw score on the screen
    glColor3f(1.0, 1.0, 1.0); 
    glRasterPos2f(10, 10);
    std::string scoreStr = " Bro your Score: " + std::to_string(score);
    for (char c : scoreStr) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Paddle-Bounce Game");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboard);
    glClearColor(0.50, 0.0, 1.0, 1.0);

    glutMainLoop();
    return 0;
}
