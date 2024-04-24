/* Project 3
 *
 * Elizabeth Walters, Asia Morgenstern
 * 11 April 2024
 * Due 25 April 2024
 */

#include <GL/glut.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

const float WIDTH = 750;
const float HEIGHT = 500;
float width = WIDTH;
float height = HEIGHT;

// what surface the ball hits

const int PADDLE1 = 1;
const int PADDLE2 = 2;
const int TOP = 3;
const int BOTTOM = 4;

const float border = 10.0;

float p1cy = height/2.0;                // center y position of paddle
float p2cy = height/2.0;
float pHeight = 101.0;

float bx = width/2 - border/2;          // lower LH corner
float by = height/2 - border/2;

int p1Score = 0;
int p2Score = 0;

int nHits = 0;

// paddle movement

float translateP1 = 3.0;
float translateP2 = 3.0;
float dTranslateP = 6.0;

// ball movement

const float PI = 4.0*atan(1.0);

float angle = 0;                      // in radians, relative to x axis
float minAngle = 35.0*PI/180.0;

float translateBx = 5.0;
float translateBy = 5.0;
float dTranslateBx = 2.5;
float dTranslateBy = 2.5;
float incTranslateB = 1.0;
float maxTranslate = 20.0;

float pauseBx, pauseBy, pauseP;

void printScore() {
    glRasterPos2i(width/4, height - 4*border);
    stringstream ss;
    ss << p1Score;
    string moves = ss.str();
    string s = moves;
    for (int i = 0; i < s.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }

    glRasterPos2i(3*width/4, height - 4*border);
    ss.str("");
    ss << p2Score;
    moves = ss.str();
    s = moves;
    for (int i = 0; i < s.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
}

void drawPaddles() {
    glRectf(0, p1cy - pHeight/2.0, border, p1cy + pHeight/2.0);
    glRectf(width - border, p2cy - pHeight/2.0, width, p2cy + pHeight/2.0);

    glFlush();
}

void drawBall() {
    glRectf(bx, by, bx + border, by + border);
    glFlush();
}

void createBoard() {
    glColor3f(1.0, 1.0, 1.0);
	glLineWidth(border);
    glLineStipple(border, 0xAAAA);
    glBegin(GL_LINES);
        glVertex2f(width/2, 0.0);
        glVertex2f(width/2, height);
    glEnd();

    glRecti(0, 0, width, border);
    glRecti(0, height - border, width, height);

    printScore();

    drawPaddles();
    drawBall();

    glFlush();
}

void newRound() {
    p1cy = height/2.0;                // center y position of paddle
    p2cy = height/2.0;

    bx = width/2 - border/2;          // lower LH corner
    by = height/2 - border/2;

    angle = 0;

    nHits = 0;

    printScore();

    drawPaddles();
    drawBall();

    glFlush();
}

void newGame() {
    translateBx = 5.0;
    translateBy = 5.0;
    dTranslateBx = 2.5;
    dTranslateBy = 2.5;
    incTranslateB = 1.0;

    p1Score = 0;
    p2Score = 0;

    newRound();
}

bool hitsPaddle(int state) {
    float bc = by + border/2;

    float pTop, pBottom;
    if (state == PADDLE1) {
        pTop = p1cy + pHeight/2;
        pBottom = p1cy - pHeight/2;
    } else if (state == PADDLE2) {
        pTop = p2cy + pHeight/2;
        pBottom = p2cy - pHeight/2;
    }

    return (bc >= pBottom && bc <= pTop);
}

void updateAngle(int state) {
    float bc = by + border/2;
    float r;

    if (state == PADDLE1) {
        r = 1 - bc/p1cy;

        angle = 2*PI - angle;
        angle *= -r;
    } else if (state == PADDLE2) {
        r = bc/p2cy;

        angle = 2*PI - angle;
        angle *= -r;
    } else if (state == TOP) {
        r = -1;
        angle *= r;
    } else if (state == BOTTOM) {
        r = -1;
        angle *= r;
    }

    while (angle < 0) {
        angle += 2*PI;
    }
    while (angle > 2*PI) {
        angle -= 2*PI;
    }

    if (r != 1 && r != 0) {
        if (angle < minAngle) {                                         // (0, minAngle)
            angle = minAngle;
        } else if (angle >= PI/2 - 15*PI/180.0 && angle <= PI/2) {      // (75, 90)
            angle = PI/2 - 15*PI/180.0;
        } else if (angle > PI/2 && angle <= PI/2 + 15*PI/180.0) {       // (90, 105)
            angle = PI/2 + 15*PI/180.0;
        } else if (angle >= 3*PI/2 - 15*PI/180.0 && angle <= 3*PI/2) {  // (255, 270)
            angle = 3*PI/2 - 15*PI/180.0;
        } else if (angle > 3*PI/2 && angle <= 3*PI/2 + 15*PI/180.0) {   // (270, 285)
            angle = 3*PI/2 + 15*PI/180.0;
        }
    }
}

void reflect() {
    if (bx == border) {                             // hit paddle 1
        if (hitsPaddle(PADDLE1)) {
            updateAngle(PADDLE1);

            translateBx *= -1;
            dTranslateBx *= -1;
            translateBy *= -1;
            dTranslateBy *= -1;
            incTranslateB *= -1;
            nHits++;
        }
    } else if (bx <= -border) {                     // paddle 1 miss
        p2Score++;

        newRound();
    } else if (bx + border == width - border) {     // hit paddle 2
        if (hitsPaddle(PADDLE2)) {
            updateAngle(PADDLE2);

            translateBx *= -1;
            dTranslateBx *= -1;
            translateBy *= -1;
            dTranslateBy *= -1;
            incTranslateB *= -1;
            nHits++;
        }
    } else if (bx >= width) {                       // paddle 2 miss
        p1Score++;

        newRound();
    } else if (by == border) {                      // hits floor
        updateAngle(BOTTOM);
    } else if (by + border >= height - border) {    // hits ceiling
        updateAngle(TOP);
    }

    if (nHits == 4) {
        if (translateBx < maxTranslate) {
            translateBx += dTranslateBx;
        }
        if (translateBy < maxTranslate) {
            translateBy += dTranslateBy;
        }
        nHits = 0;
    }
}

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LINE_STIPPLE);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    createBoard();
}

void idle() {
    if (bx + translateBx*cos(angle) < border && hitsPaddle(PADDLE1)) {   // steps over Paddle1
        float factor = (bx - border)/translateBx;

        bx = border;
        by += factor*translateBy*sin(angle);
    } else if (bx + translateBx*cos(angle) > width - border && hitsPaddle(PADDLE2)) { // steps over Paddle2
        float factor = (width - border - bx)/translateBx;

        bx = width - 2*border;
        by += factor*translateBy*sin(angle);
    } else if (by + translateBy*sin(angle) < border) {                  // steps over floor
        float factor = (by - border)/translateBy;

        bx += factor*translateBx*cos(angle);
        by = border;
    } else if (by + translateBy*sin(angle) > height - border) {        // steps over ceiling
        float factor = (border - by)/translateBy;

        bx += factor*translateBx*cos(angle);
        by = height - 2*border;
    } else {
        bx += translateBx*cos(angle);
        by += translateBy*sin(angle);
    }

    reflect();
    glutPostRedisplay();

    Sleep(25);
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'n':
            newGame();
            break;
        case 'p':
            pauseBx = translateBx;
            pauseBy = translateBy;
            pauseP = dTranslateP;

            translateBx = translateBy = translateP1 = translateP2 = 0;
            break;
        case 'q':
            exit(0);
            break;
        case 'r':
            translateBx = pauseBx;
            translateBy = pauseBy;
            dTranslateP = pauseP;
            break;
        case 's':
            if (p1cy <= height - pHeight/2 - border) {
                p1cy += dTranslateP;
            }
            break;
        case 'x':
            if (p1cy >= pHeight/2 + border) {
                p1cy -= dTranslateP;
            }
            break;
    }
    glutPostRedisplay();
}

void mySpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP && p2cy <= height - pHeight/2 - border) {
        p2cy += dTranslateP;
    } else if (key == GLUT_KEY_DOWN && p2cy >= pHeight/2 + border) {
        p2cy -= dTranslateP;
    }
    glutPostRedisplay();
}

void myReshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Project 3");

    glutIdleFunc(idle);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);

    myInit();
    glutMainLoop();

    return EXIT_SUCCESS;
}
