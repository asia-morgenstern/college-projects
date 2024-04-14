/* Project 2
 *
 * Elizabeth Walters, Asia Morgenstern
 * 2 April 2024
 * Due 9 April 2024
 */

#include <GL/glut.h>

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;
int width = WIDTH;
int height = HEIGHT;

const int DEF_BOUND = 0;
const int DEF_OBJ = 1;
const int START_MOVE = 2;

int prevState = -1;
int state = DEF_BOUND;

class Point {
    public:
        float x;
        float y;

    public:
        Point(float px, float py) {
            x = px;
            y = py;
        }
};

list <Point> bPoints;
list <Point> oPoints;
list<Point>::iterator it;
list<Point>::iterator it2;

float bxmin, bxmax;
float bymin, bymax;
float oxmin, oxmax;
float oymin, oymax;

double matrix[16];

const double PI = 4.0*atan(1.0);

bool rotateYN = false;
bool translateYN = false;

float theta = 0.0;
float dtheta = 1.0;
float incTheta = 1.0;

float z = 1.0;

float translate = 0.5;
float dTranslate = 1.0;
float incTranslate = 1.0;
const float minTranslate = 0.0;
const float maxTranslate = 50.0;

float intersectX = 0.0;
float intersectY = 0.0;
float cx = 0.0;
float cy = 0.0;

void drawObjects() {
    glPointSize(5.0);

    if (state == DEF_OBJ && prevState != DEF_OBJ) {
        glBegin(GL_LINE_LOOP);
            glColor3f(0.0, 1.0, 0.0);
            for (it2 = bPoints.begin(); it2 != bPoints.end(); ++it2) {
                glVertex2f(it2->x, it2->y);
            }
        glEnd();

        glBegin(GL_LINE_STRIP);
            glColor3f(1.0, 0.0, 0.0);
            for (it = oPoints.begin(); it != oPoints.end(); ++it) {
                glVertex2f(it->x, it->y);
            }
        glEnd();
    } else if (state == DEF_BOUND && prevState != DEF_BOUND) {
        glBegin(GL_LINE_LOOP);
            glColor3f(1.0, 0.0, 0.0);
            for (it = oPoints.begin(); it != oPoints.end(); ++it) {
                glVertex2f(it->x, it->y);
            }
        glEnd();

        glBegin(GL_LINE_STRIP);
            glColor3f(0.0, 1.0, 0.0);
            for (it2 = bPoints.begin(); it2 != bPoints.end(); ++it2) {
                glVertex2f(it2->x, it2->y);
            }
        glEnd();
    } else if (state == START_MOVE || (!bPoints.empty() && !oPoints.empty())) {
        glBegin(GL_LINE_LOOP);
            glColor3f(1.0, 0.0, 0.0);
            for (it = oPoints.begin(); it != oPoints.end(); ++it) {
                glVertex2f(it->x, it->y);
            }
        glEnd();

        glBegin(GL_LINE_LOOP);
            glColor3f(0.0, 1.0, 0.0);
            for (it2 = bPoints.begin(); it2 != bPoints.end(); ++it2) {
                glVertex2f(it2->x, it2->y);
            }
        glEnd();
    }
    glFlush();
}

void findCentroid() {
    float avgx = 0;
    float avgy = 0;

    for (it = oPoints.begin(); it != oPoints.end(); ++it) {
        // get sum of x and y values of the object's points to calculate the average to get the center of the shape

        avgx += it->x;
        avgy += it->y;
    }

    avgx /= oPoints.size();
    avgy /= oPoints.size();

    cx = avgx;
    cy = avgy;
}

void updateObjectPositions() {
    glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

    int i = 0;
    for (it = oPoints.begin(); it != oPoints.end(); ++it) {
        float thisx = it->x;
        float thisy = it->y;

        float newX = matrix[0]*thisx + matrix[4]*thisy + matrix[12];
        float newY = matrix[1]*thisx + matrix[5]*thisy + matrix[13];

        it->x = newX;
        it->y = newY;

        if (i == 0){
            oxmin = oxmax = newX;
            oymin = oymax = newY;
        } else {
            if (newX < oxmin) {
                oxmin = newX;
            }
            if (newX > oxmax) {
                oxmax = newX;
            }
            if (newY < oymin) {
                oymin = newY;
            }
            if (newY > oymax) {
                oymax = newY;
            }
        }

        i++;
    }
}

void reflectObject(Point A, Point B, Point C, Point D) {
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// object

    float ax = D.x - C.x;
    float ay = D.y - C.y;

    // boundary

    float bx = B.x - A.x;
    float by = B.y - A.y;

    // normal to boundary

    float nx = ay;
    float ny = -ax;

    // normalize normal vector

    float nmag = sqrt(nx*nx + ny*ny);

    nx /= nmag;
    ny /= nmag;

    // find reflection vector r = a - 2 (a \dot n) n

    float an = ax*nx + ay*ny;           // calculate a \dot n

    float rx = ax - 2*an*nx;
    float ry = ay - 2*an*ny;

    // calculate rotation angle phi between normal and a vector

    float amag = sqrt(ax*ax + ay*ay);   // normalize vec(a)

    ax /= amag;
    ay /= amag;

    an = ax*nx + ay*ny;

    float phi = acos(an);               // use a \dot n = |a| |n| cos \phi
    phi *= 180.0/PI;

    // determine if normal is +z or -z (by the RHR) a \cross b

    float nz = ax*by - ay*bx;
    if (nz > 0) {
        z *= -1;
    }

    if (phi == 0 || isnan(phi)) {
        glTranslatef(z*translate, z*translate, 0.0);
    } else {
        glTranslatef(intersectX, intersectY, 0.0);
        glRotatef(-phi, 0.0, 0.0, z);
        glTranslatef(-intersectX, -intersectY, 0.0);

        glTranslatef(rx, ry, 0.0);
    }

    updateObjectPositions();

    glutPostRedisplay();
}

void reflectObject2(Point A, Point B, Point C, Point D) {
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    float bx = B.x - A.x;
    float by = B.y - A.y;

    float dx = D.x - C.x;
    float dy = D.y - C.y;

    float bmag = sqrt(bx*bx + by*by);
    float dmag = sqrt(dx*dx + dy*dy);

    // normalize vec(b) and vec(d)

    bx /= bmag;
    by /= bmag;

    dx /= dmag;
    dy /= dmag;

    float bd = bx*dx + by*dy;

    float phi = acos(bd);
    phi *= 180.0/PI;

    // determine if normal is +z or -z (by the RHR)

    float nz = bx*dy - by*dx;

    if (nz > 0) {
        z *= -1;
    } else {
        z *= 1;
    }

    if (phi == 0 || isnan(phi)) {
        glTranslatef(z*translate, z*translate, 0.0);
    } else {
        glTranslatef(intersectX, intersectY, 0.0);
        glRotatef(180 + 2*phi, 0.0, 0.0, z);
        glTranslatef(-intersectX, -intersectY, 0.0);
    }

    updateObjectPositions();

    glutPostRedisplay();
}

bool intersect(Point A, Point B, Point C, Point D) {
    float bx = B.x - A.x;
    float by = B.y - A.y;

    float dx = D.x - C.x;
    float dy = D.y - C.y;

    float cx = C.x - A.x;
    float cy = C.y - A.y;

    float bperpx = -by;
    float bperpy = bx;

    float dperpx = -dy;
    float dperpy = dx;

    float bdperp = bx*dperpx + by*dperpy;

    float cdperp = cx*dperpx + cy*dperpy;
    float cbperp = cx*bperpx + cy*bperpy;

    if (bdperp != 0) {
        // segments may intersect

        float t = cdperp/bdperp;
        float u = cbperp/bdperp;

        bool intersects = (t <= 1 && u <= 1 && t >= 0 && u >= 0);

        if (intersects) {
            intersectX = A.x + bx*t;
            intersectY = A.y + by*t;
        }

        return intersects;
    } else if ((C.x >= A.x && C.x <= B.x) || (C.x >= B.x && C.x <= A.x)     // C between A & B
            || (D.x >= A.x && D.x <= B.x) || (D.x >= B.x && D.x <= A.x)     // D between A & B
            || (A.x >= C.x && A.x <= D.x) || (A.x >= D.x && A.x <= C.x)     // A between C & D
            || (B.x >= C.x && B.x <= D.x) || (B.x >= D.x && B.x <= C.x)) {  // B between C & D
                //segments may be collinear ^
                // check if x vals overlap ^^

        // check if C lies on line AB

        float tx = cx/bx;
        float ty = cy/by;

        return (tx == ty);
    } else {
        return false;
    }
}

bool isInside() {
    int i = 0;
    int j;

    for (it2 = bPoints.begin(); it2 != bPoints.end() && i < bPoints.size() - 1; ++it2) {
        Point A = *it2;
        Point B = *(++it2);
        --it2;

        j = 0;
        for (it = oPoints.begin(); it != oPoints.end() && j < oPoints.size() - 1; ++it) {
            Point C = *it;
            Point D = *(++it);
            --it;

            bool isOutside = false;

            float adjust = oxmax - oxmin;
            if (oymax - oymin > adjust) {
                adjust = oymax - oymin;
            }

            if (oxmin < bxmin) {        // object is left of boundary
                glTranslatef(adjust, 0.0, 0.0);
                isOutside = true;
            }
            if (oxmax > bxmax) {        // object is right of boundary
                glTranslatef(-adjust, 0.0, 0.0);
                isOutside = true;
            }
            if (oymin < bymin) {        // object is below boundary
                glTranslatef(0.0, adjust, 0.0);
                isOutside = true;
            }
            if (oymax > bymax) {        // object is above boundary
                glTranslatef(0.0, -adjust, 0.0);
                isOutside = true;
            }
            if (isOutside) {
                updateObjectPositions();
                return false;
            }

            if (intersect(A, B, C, D)) {
                reflectObject(A, B, C, D);
                return false;
            }
            j++;
        }
        i++;
    }

    return true;
}

void menu(int val) {
    prevState = state;

    switch(val) {
        case 0:
            state = DEF_BOUND;
            rotateYN = translateYN = false;
            bPoints.clear();
            break;
        case 1:
            state = DEF_OBJ;
            rotateYN = translateYN = false;
            oPoints.clear();
            break;
        case 2:
            if (!oPoints.empty() && !bPoints.empty()) {
                state = START_MOVE;
                rotateYN = translateYN = true;
            }
            break;
    }
    glutPostRedisplay();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    glutCreateMenu(menu);
    glutAddMenuEntry("Define Boundary", 0);
    glutAddMenuEntry("Define Object", 1);
    glutAddMenuEntry("Start Movement", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    drawObjects();

    if (translateYN) {
        glTranslatef(z*translate, z*translate, 0.0);
    }

    if (rotateYN) {
        findCentroid();

        glTranslatef(cx, cy, 0.0);
        glRotatef(theta, 0.0, 0.0, z);
        glTranslatef(-cx, -cy, 0.0);
    }

    if (translateYN || rotateYN) {
        updateObjectPositions();

        isInside();
    }

    Sleep(450);

    glutPostRedisplay();
}

void idle() {
    if (translateYN) {
        translate += dTranslate;
    }
    if (rotateYN) {
        theta += dtheta;
        if (theta > 360.0) {
            theta -= 360.0;
        }
    }
    glutPostRedisplay();
}

void myMouse(int button, int buttonState, int mx, int my) {
    my = height - my;
    if (button == GLUT_LEFT_BUTTON && buttonState == GLUT_DOWN) {
        if (state == DEF_BOUND) {
            bPoints.push_back(Point(mx, my));

            if (bPoints.size() == 1){
                bxmin = bxmax = mx;
                bymin = bymax = my;
            } else {
                if (mx < bxmin) {
                    bxmin = mx;
                }
                if (mx > bxmax) {
                    bxmax = mx;
                }
                if (my < bymin) {
                    bymin = my;
                }
                if (my > bymax) {
                    bymax = my;
                }
            }
        } else if (state == DEF_OBJ) {
            oPoints.push_back(Point(mx, my));

            if (oPoints.size() == 1){
                oxmin = oxmax = mx;
                oymin = oymax = my;
            } else {
                if (mx < oxmin) {
                    oxmin = mx;
                }
                if (mx > oxmax) {
                    oxmax = mx;
                }
                if (my < oymin) {
                    oymin = my;
                }
                if (my > oymax) {
                    oymax = my;
                }
            }
        }
    }
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(0);
            break;
        case 'r':
            rotateYN = !rotateYN;
            break;
        case 't':
            translateYN = !translateYN;
            break;
    }
}

void mySpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP && translate > minTranslate) {
        dTranslate -= incTranslate;
    } else if (key == GLUT_KEY_DOWN && translate < maxTranslate) {
        dTranslate += incTranslate;
    } else if (key == GLUT_KEY_LEFT) {
        dtheta -= incTheta;
        if (dtheta < 0.0) {
            dtheta += 360.0;
        }
    } else if (key == GLUT_KEY_RIGHT) {
        dtheta += incTheta;
        if (dtheta > 360.0) {
            dtheta -= 360.0;
        }
    }
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
    glutCreateWindow("Project 2");

    glutIdleFunc(idle);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);

    myInit();
    glutMainLoop();

    return EXIT_SUCCESS;
}
