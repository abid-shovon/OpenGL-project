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

// Game state
bool gameStarted = false;
bool gamePaused = false;
bool gameEnded = false;

// Function declarations
void reshape(int w, int h);
void drawPaddle();
void drawBall();
void keyboard(unsigned char key, int x, int y);
void update(int value);
void render();
void startGame();
void pauseGame();
void exitGame();
void restartGame();
void drawText(const std::string& text, float x, float y);
void drawStartScreen();
void drawEndScreen();

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

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Escape key
            if (gameEnded)
                exit(0);
            else
                exitGame();
            break;
        case ' ': // Space key
            if (!gameStarted && !gameEnded)
                startGame();
            break;
        case 'p':
        case 'P': // Pause key
            if (gameStarted && !gameEnded)
                pauseGame();
            break;
        case 'r':
        case 'R': // Restart key
            if (gameEnded)
                restartGame();
            break;
    }
}

// Function to update game state
void update(int value) {
    if (gameStarted && !gamePaused && !gameEnded) {
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
        if (ballY + ballRadius >= screenHeight || ballY - ballRadius <= 0) {
            ballSpeedY = -ballSpeedY;
        }

        // Ball collision with paddle
        if (ballY - ballRadius <= paddleY + paddleHeight && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
            ballSpeedY = -ballSpeedY;
            score++; // Increment score when ball hits the paddle
        }

        // Ball out of bounds
        if (ballY - ballRadius <= 0) {
            gameEnded = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Function to render the scene
void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (!gameStarted) {
        drawStartScreen();
    } else if (gameEnded) {
        drawEndScreen();
    } else {
        // Draw paddle and ball
        drawPaddle();
        drawBall();

        // Draw score on the screen
        glColor3f(1.0, 1.0, 1.0); 
        glRasterPos2f(10, 10);
        std::string scoreStr = "Score: " + std::to_string(score);
        for (char c : scoreStr) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
    }

    glutSwapBuffers();
}

// Function to draw text on the screen
void drawText(const std::string& text, float x, float y) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

// Function to draw the start screen
void drawStartScreen() {
    glColor3f(1.0, 1.0, 1.0); // White color for text

    // Draw start game option
    drawText("Press SPACEBAR to Start", screenWidth / 2 - 150, screenHeight / 2);

    // Draw exit game option
    drawText("Press ESC to Exit", screenWidth / 2 - 100, screenHeight / 2 - 50);
}

// Function to draw the end screen
void drawEndScreen() {
    glColor3f(1.0, 1.0, 1.0); // White color for text

    // Draw end game message
    drawText("Game Over! Your Score: " + std::to_string(score), screenWidth / 2 - 140, screenHeight / 2);

    // Draw restart game option
    drawText("Press R to Restart", screenWidth / 2 - 100, screenHeight / 2 - 50);

    // Draw exit game option
    drawText("Press ESC to Exit", screenWidth / 2 - 100, screenHeight / 2 - 100);
}

// Function to start the game
void startGame() {
    gameStarted = true;
}

// Function to pause the game
void pauseGame() {
    gamePaused = !gamePaused;
}

// Function to restart the game
void restartGame() {
    gameStarted = true;
    gamePaused = false;
    gameEnded = false;
    score = 0;
    ballX = screenWidth / 2;
    ballY = screenHeight - ballRadius; // Reset ball position to the top
    ballSpeedY = -ballSpeedY; // Make ball move upwards
    paddleX = screenWidth / 2 - paddleWidth / 2;
}

// Function to exit the game
void exitGame() {
    std::cout << "Game Over! Your Score: " << score << std::endl;
    exit(0);
}

// Function to handle mouse input
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!gameStarted) {
            startGame();
        }
    }
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
    glutMouseFunc(mouse);
    glClearColor(0.50, 0.0, 1.0, 1.0);

    glutMainLoop();
    return 0;
}
