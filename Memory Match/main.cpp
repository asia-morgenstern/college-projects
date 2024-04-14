/* project 1
 *
 * Elizabeth Walters, Asia Morgenstern
 * 9 February 2024
 * Due 15 February 2024
 */

#include <GL/glut.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;
int width = WIDTH;
int height = HEIGHT;

const int startX = 50;
const int startY = 450;
const int x = 75;
const int y = 75;
const int dx = 25;
const int dy = 25;

const int triangle1 = 0;
const int triangle2 = 1;
const int square1 = 2;
const int square2 = 3;
const int triangle3 = 4;
const int triangle4 = 5;
const int diamond1 = 6;
const int diamond2 = 7;

int countShapes[8];

const int shapeOffset = 5;

class Card {
    public:
        int x1, y1;
        int x2, y2;
        int image;
        bool isFlipped;
        bool isRemoved;
};

Card cardArray[16];
int card1 = -1;
int card2 = -1;
int currWidth1 = x;
int currWidth2 = x;
int numMoves = 0;

bool animate = false;
float increment = 2.0;
const int minWidth = 1;

void drawCard(int i, float r, float g, float b, int width) {
    glColor3f(1.0, 1.0, 1.0);
    glRecti(cardArray[i].x1, cardArray[i].y1, cardArray[i].x2, cardArray[i].y2);
    glFlush();

    glColor3f(r, g, b);
    glRecti(cardArray[i].x1, cardArray[i].y1, cardArray[i].x1 + width, cardArray[i].y2);
    glFlush();
}

void drawCard(int i, float r, float g, float b) {
    glColor3f(r, g, b);
    glRecti(cardArray[i].x1, cardArray[i].y1, cardArray[i].x2, cardArray[i].y2);
    glFlush();
}

void drawShape(int i) {
    int x1 = cardArray[i].x1 + shapeOffset;
    int y1 = cardArray[i].y1 - shapeOffset;
    int x2;
    int y2 = cardArray[i].y2 + shapeOffset;

    if (i == card1 && currWidth1 <= 3*shapeOffset) {
        x2 = cardArray[i].x1 + currWidth1/3;
    } else if (i == card1) {
        x2 = cardArray[i].x1 + currWidth1 - shapeOffset;
    } else if (i == card2 && currWidth2 <= 3*shapeOffset) {
        x2 = cardArray[i].x1 + currWidth2/3;
    } else {
        x2 = cardArray[i].x1 + currWidth2 - shapeOffset;
    }

    int midpointx = (x1 + x2)/2;
    int midpointy = (y1 + y2)/2;

    switch (cardArray[i].image) {
    case triangle1:
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
            glVertex2i(midpointx, y1);
        glEnd();
        break;
    case triangle2:
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(midpointx, y2);
        glEnd();
        break;
    case triangle3:
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
            glVertex2i(midpointx, y1);
        glEnd();
        break;
    case triangle4:
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(midpointx, y2);
        glEnd();
        break;
    case square1:
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y2);
            glVertex2i(x1, y2);
        glEnd();
        break;
    case square2:
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y2);
            glVertex2i(x1, y2);
        glEnd();
        break;
    case diamond1:
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
            glVertex2i(midpointx, y1);
            glVertex2i(x2, midpointy);
            glVertex2i(midpointx, y2);
            glVertex2i(x1, midpointy);
        glEnd();
        break;
    case diamond2:
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
            glVertex2i(midpointx, y1);
            glVertex2i(x2, midpointy);
            glVertex2i(midpointx, y2);
            glVertex2i(x1, midpointy);
        glEnd();
        break;
    }
    glFlush();
}

bool checkMatch() {
    return (cardArray[card1].image == cardArray[card2].image);
}

void removeCards() {
    glColor3f(1.0, 1.0, 1.0);
    glRecti(cardArray[card1].x1, cardArray[card1].y1, cardArray[card1].x2, cardArray[card1].y2);
    glRecti(cardArray[card2].x1, cardArray[card2].y1, cardArray[card2].x2, cardArray[card2].y2);

    cardArray[card1].isRemoved = true;
    cardArray[card2].isRemoved = true;
}

void flipCard(int i) {
    animate = true;
    if (!cardArray[i].isFlipped) {
        float r, g, b;
        r = b = 0.0;
        g = 1.0;
        drawCard(i, r, g, b);
    } else {
        drawShape(i);
    }
}

void newGame() {
    numMoves = 0;

    for (int i = 0; i < 8; i++) {
        countShapes[i] = 0;
    }

    for (int i = 0; i < 16; i++) {
        int imgNum = rand()%8;
        while (countShapes[imgNum] >= 2) {
            imgNum = rand()%8;
        }
        countShapes[imgNum]++;

        cardArray[i].image = imgNum;
        cardArray[i].isFlipped = cardArray[i].isRemoved = false;
    }
    glutPostRedisplay();
}

void resetAnimationSpeed() {
    increment = 2.0;
}

void slowAnimation() {
    if (increment == 0) {
        resetAnimationSpeed();
    } else {
        increment -= 0.5;
    }
}

void gameMenu(int val) {
    switch(val) {
    case 0: exit(0); break;
    case 1: newGame(); break;
    case 2: slowAnimation(); break;
    case 3: resetAnimationSpeed(); break;
    }
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    glutCreateMenu(gameMenu);
    glutAddMenuEntry("Quit", 0);
    glutAddMenuEntry("New Game", 1);
    glutAddMenuEntry("Slow Down Animation", 2);
    glutAddMenuEntry("Reset Animation Speed", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Card c;
            c.x1 = startX + (dx + x)*j;
            c.y1 = startY - (dy + y)*i;
            c.x2 = startX + (dx + x)*j + x;
            c.y2 = startY - (dy + y)*i - y;

            int imgNum = rand()%8;
            while (countShapes[imgNum] >= 2) {
                imgNum = rand()%8;
            }
            countShapes[imgNum]++;

            c.image = imgNum;
            c.isFlipped = c.isRemoved = false;

            cardArray[k++] = c;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(10.0);

    float r, g, b;
    r = b = 0.0;
    g = 1.0;

    for (int i = 0; i < 16; i++) {
        if (!cardArray[i].isRemoved) {
            drawCard(i, r, g, b);
        }
        if (i == card1 || i == card2) {
            drawShape(i);
        }
    }

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(startX, y/2);
    string txt = "Number of Moves:  ";
    stringstream ss;
    ss << numMoves;
    string moves = ss.str();
    string s = txt + moves;
    for (int i = 0; i < s.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
    glFlush();
}

void idle() {
    if (animate) {
        if (!cardArray[card1].isFlipped && !cardArray[card2].isFlipped) {
            while (currWidth2 > minWidth) {
                currWidth1 -= increment;
                currWidth2 -= increment;
                drawCard(card1, 0.0, 1.0, 0.0, currWidth1);
                drawShape(card1);
                drawCard(card2, 0.0, 1.0, 0.0, currWidth2);
                drawShape(card2);
                Sleep(10);
            }
            while (currWidth1 < x) {
                currWidth1 += increment;
                currWidth2 += increment;
                drawCard(card1, 0.0, 1.0, 0.0, currWidth1);
                drawCard(card2, 0.0, 1.0, 0.0, currWidth2);
                Sleep(10);
            }
            animate = false;
            currWidth1 = x;
            currWidth2 = x;

            card1 = card2 = -1;
        } else if (card2 != -1) {
            while (currWidth2 > minWidth) {
                currWidth2 -= increment;
                drawCard(card2, 0.0, 1.0, 0.0, currWidth2);
                Sleep(10);
            }
            while (currWidth2 < x) {
                currWidth2 += increment;
                drawCard(card2, 0.0, 1.0, 0.0, currWidth2);
                drawShape(card2);
                Sleep(10);
            }
            animate = false;
            currWidth2 = x;
        } else if (card1 != -1) {
            while (currWidth1 > minWidth) {
                currWidth1 -= increment;
                drawCard(card1, 0.0, 1.0, 0.0, currWidth1);
                Sleep(10);
            }
            while (currWidth1 < x) {
                currWidth1 += increment;
                drawCard(card1, 0.0, 1.0, 0.0, currWidth1);
                drawShape(card1);
                Sleep(10);
            }
            animate = false;
            currWidth1 = x;
        }
    }
}

void myMouse(int button, int buttonState, int mx, int my) {
    my = height - my;
    if (button == GLUT_LEFT_BUTTON && buttonState == GLUT_DOWN) {
        int wx = x + dx;
        int wy = y + dy;

        int row = -1;
        int col = -1;

        if (mx < wx + startX) {
            col = 0;
        } else if (mx < 2*wx + startX) {
            col = 1;
        } else if (mx < 3*wx + startX) {
            col = 2;
        } else if (mx < 4*wx + startX) {
            col = 3;
        }

        if (my < startY - 3*wy) {
            row = 3;
        } else if (my < startY - 2*wy) {
            row = 2;
        } else if (my < startY - wy) {
            row = 1;
        } else if (my < startY) {
            row = 0;
        }

        int i = 4*row + col;

        Card card = cardArray[i];

        if (row > -1 && col > -1 && mx > card.x1 && mx < card.x2 && my < card.y1 && my > card.y2 && !card.isRemoved) {
            if (card1 == -1) {
                card1 = i;
                cardArray[card1].isFlipped = true;
                flipCard(card1);
            } else if (i != card1) {
                card2 = i;
                cardArray[card2].isFlipped = true;
                flipCard(card2);

                idle();
                Sleep(300);

                numMoves++;

                if (checkMatch()) {
                    Sleep(300);
                    removeCards();

                    card1 = card2 = -1;
                } else {
                    Sleep(300);
                    cardArray[card1].isFlipped = false;
                    cardArray[card2].isFlipped = false;

                    flipCard(card1);
                    flipCard(card2);
                }
            }
        }
    }
}

void myReshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Project 1");

    glutMouseFunc(myMouse);
    glutIdleFunc(idle);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);

    myInit();
    glutMainLoop();

    return EXIT_SUCCESS;
}
