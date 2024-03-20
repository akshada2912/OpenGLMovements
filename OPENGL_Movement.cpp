#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <glm/glm.hpp> 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

//g++ 2022101010.cpp -o 2022101010 -lGL -lGLU -lglut          ./2022101010 <sides>

int argc;
char** argv;
float cameraX = 2.0f, cameraY = 1.0f, cameraZ = 2.0f;
float cameraXangle = 0.0f, cameraYangle = 0.0f;
bool moveForward = false, moveBackward = false, moveLeft = false, moveRight = false, moveUp = false, moveDown = false;
bool moveForward2 = false, moveBackward2 = false, moveLeft2 = false, moveRight2 = false, moveUp2 = false, moveDown2 = false;
bool togglepyr=false, toggleprism=true;
float xcenter=0.f, ycenter=0.f, zcenter=0.f;

float trans1[3] = {0.0f, 0.0f, 0.0f};

float rotateX = 0.0f;
float rotateY = 0.0f;
float rotateZ = 0.0f;

float Rstart = 250.0f / 255.0f;
float Gstart = 182.0f / 255.0f;
float Bstart = 227.0f / 255.0f;

float Rend = 255.0f / 255.0f;
float Gend = 0.0f / 255.0f;
float Bend = 170.0f / 255.0f;

struct quad{
    float x1;
    float x2;
    float x3;
    float x4;
    float y1;
    float y2;
    float y3;
    float y4;
    float z1;
    float z2;
    float z3;
    float z4;
    float a1;
    float a2;
    float a3;
    float a4;
};

void drawPyramid(int sides, float radius, float height) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < sides; ++i) {
        float x1 = xcenter + radius * cos(i * 2 * M_PI / sides);
        float y1 = ycenter + radius * sin(i * 2 * M_PI / sides);
        float x2 = xcenter + radius * cos((i + 1) * 2 * M_PI / sides);
        float y2 = ycenter + radius * sin((i + 1) * 2 * M_PI / sides);

        //normal
        float normalX = (y1 - y2);
        float normalY = (x2 - x1);
        float normalLength = sqrt(normalX * normalX + normalY * normalY);
        normalX /= normalLength;
        normalY /= normalLength;
        float t = static_cast<float>(i) / sides;
        float r = Rstart + (Rend - Rstart) * t;
        float g = Gstart + (Gend - Gstart) * t;
        float b = Bstart + (Bend - Bstart) * t;

        glColor3f(r, g, b);

        struct quad Quad;
        Quad.x1=x1;
        Quad.y1=y1;
        Quad.z1=zcenter+height/2;

        Quad.x2=x2;
        Quad.y2=y2;
        Quad.z2=zcenter+height/2;

        Quad.x3=xcenter;
        Quad.y3=ycenter;
        Quad.z3=zcenter-height/2;

        glVertex3f(Quad.x1,Quad.y1,Quad.z1);
        glVertex3f(Quad.x2,Quad.y2,Quad.z2);
        glVertex3f(Quad.x3,Quad.y3,Quad.z3);

        glNormal3f(normalX, normalY, 0.0f);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.5f); 
    glBegin(GL_POLYGON);
    //glVertex3f(xcenter + 0.0f, ycenter + 0.0f, zcenter - height / 2);  // Base=
    for (int i = 0; i <= sides; ++i) {
        float angle = i * 2 * M_PI / sides;
        glVertex3f(xcenter + radius * cos(angle), ycenter + radius * sin(angle), zcenter + height / 2);
    }
    glEnd();
}



void drawPrism(int sides, float radius, float height) {
    // Draw sides of prism
    for (int i = 0; i < sides; ++i) {

        float r = Rstart + (Rend - Rstart) * (static_cast<float>(i) / (sides - 1));
        float g = Gstart + (Gend - Gstart) * (static_cast<float>(i) / (sides - 1));
        float b = Bstart + (Bend - Bstart) * (static_cast<float>(i) / (sides - 1));

        glColor3f(r, g, b);

        glBegin(GL_QUADS);

        struct quad Quad;

        Quad.x1=xcenter+radius*cos(i * 2 * M_PI / sides);
        Quad.y1=ycenter+radius*sin(i * 2 * M_PI / sides);
        Quad.z1=zcenter-0.5f;
        Quad.x2=xcenter+radius*cos((i + 1) * 2 * M_PI / sides);
        Quad.y2=ycenter+radius*sin((i + 1) * 2 * M_PI / sides);
        Quad.z2=zcenter-0.5f;
        Quad.x3=xcenter+radius*cos((i + 1) * 2 * M_PI / sides);
        Quad.y3=ycenter+radius*sin((i + 1) * 2 * M_PI / sides);
        Quad.z3=zcenter+0.5f;
        Quad.x4=xcenter+radius*cos(i * 2 * M_PI / sides);
        Quad.y4=ycenter+radius*sin(i * 2 * M_PI / sides);
        Quad.z4=zcenter+0.5f;


        glVertex3f(Quad.x1,Quad.y1,Quad.z1);
        glVertex3f(Quad.x2,Quad.y2,Quad.z2);
        glVertex3f(Quad.x3,Quad.y3,Quad.z3);
        glVertex3f(Quad.x4,Quad.y4,Quad.z4);
        glEnd();
    }

    // Render top face
    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; ++i) {
        float angle = i * 2 * M_PI / sides;

        struct quad Quad;
        Quad.x1=xcenter+radius*cos(angle);
        Quad.y1=ycenter+radius*sin(angle);
        Quad.z1=zcenter+0.5f;

        glVertex3f(Quad.x1,Quad.y1,Quad.z1);
    }
    glEnd();

    // Render bottom base
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.5f); 
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; ++i) {
        float angle = i * 2 * M_PI / sides;

        struct quad Quad;

        Quad.x1=xcenter+radius*cos(angle);
        Quad.y1=ycenter+radius*sin(angle);
        Quad.z1=zcenter-0.5f;

        glVertex3f(Quad.x1,Quad.y1,Quad.z1);

    }
    glEnd();
    glPopMatrix();

   // glPopMatrix();


}


void rotatePrism(char axis) {
    const float rotationSpeed = 1.0f; // Adjust as needed

    switch (axis) {
        case 'X':
            rotateX += rotationSpeed;
            break;
        case 'Y':
            rotateY += rotationSpeed;
            break;
        case 'Z':
        rotateZ += rotationSpeed;
            break;
        case 'A':
            rotateX -= rotationSpeed;
            break;
        case 'B':
            rotateY -= rotationSpeed;
            break;
        case 'C':
            rotateZ -= rotationSpeed;
            break;
        default:
            break;
    }
}


void updateCamera() {
    // Calculate camera direction
    float dirX = cos(cameraYangle) * cos(cameraXangle);
    float dirY = sin(cameraYangle) * cos(cameraXangle);
    float dirZ = sin(cameraXangle);

    float mag=(cameraX*cameraX + cameraY*cameraY + cameraZ*cameraZ);
    mag=sqrt(mag);

    // Update camera position based on movement flags
    const float speed = 0.1f;
    if (moveBackward) {
        cameraX += cameraX * speed/mag;
        cameraY += cameraY * speed/mag;
        cameraZ += cameraZ * speed/mag;

        //cameraZ+=speed;
    glutPostRedisplay();
    }
    if (moveForward) {

       // cameraZ-=speed;
        cameraX -= cameraX * speed/mag;
        cameraY -= cameraY * speed/mag;
        cameraZ -= cameraZ * speed/mag;
    glutPostRedisplay();
    }
    if (moveRight) {
       // printf("*%f %f %f\n",cameraX,cameraY,cameraZ);
    //rotatePrism('Z');

   cameraX+=speed;

    // glm::vec3 cameraDirection =(glm::vec3(xcenter - cameraX, ycenter - cameraY, zcenter - cameraZ));
    // glm::vec3 cameraLeft = (glm::cross(cameraDirection, glm::vec3(0,1, 0)));
    // cameraX += cameraLeft.x * speed/mag;
    // cameraY += cameraLeft.y * speed/mag;
    // cameraZ += cameraLeft.z * speed/mag;



    glutPostRedisplay();
    // Request redrawing
    }
    if (moveLeft) {
        cameraX-=speed;
//    glm::vec3 cameraDirection =(glm::vec3(xcenter - cameraX, ycenter - cameraY, zcenter - cameraZ));
//     glm::vec3 cameraLeft = (glm::cross(cameraDirection, glm::vec3(0,1, 0)));
//     cameraX -= cameraLeft.x * speed/mag;
//     cameraY -= cameraLeft.y * speed/mag;
//     cameraZ -= cameraLeft.z * speed/mag;

    glutPostRedisplay();
    }
    if (moveUp) {
        cameraY+=speed;
        //printf("hi");
        //rotatePrism('X');
        // cameraZ += speed;
    //     glm::vec3 cameraDirection = (glm::vec3(xcenter - cameraX, ycenter - cameraY, zcenter - cameraZ));
    //     printf("%f %f %f\n",cameraDirection.x,cameraDirection.y,cameraDirection.z);
    // // // Calculate the "left" direction perpendicular to the camera's line of sight and the up direction
    // glm::vec3 cameraLeft = (glm::cross(cameraDirection, glm::vec3(1, 1,1)));
    // cameraX -= cameraLeft.x * speed/mag;
    // cameraY -= cameraLeft.y * speed/mag;
    // cameraZ -= cameraLeft.z * speed/mag;
glutPostRedisplay();
    }
    if (moveDown) {
        cameraY-=speed;
        //rotatePrism('A');
        // cameraZ -= speed;
    //     glm::vec3 cameraDirection = glm::normalize(glm::vec3(xcenter - cameraX, ycenter - cameraY, zcenter - cameraZ));\

    // // Calculate the "left" direction perpendicular to the camera's line of sight and the up direction
    // glm::vec3 cameraLeft = (glm::cross(cameraDirection, glm::vec3(1, 0, 0)));
    // cameraX += cameraLeft.x * speed/mag;
    // cameraY += cameraLeft.y * speed/mag;
    // cameraZ += cameraLeft.z * speed/mag;
     glutPostRedisplay();

    }
    if(moveUp2)
    {
        trans1[1]+=0.01f;
        glutPostRedisplay();
    }
    if(moveDown2)
    {
        trans1[1]-=0.01f;
        glutPostRedisplay();
    }
    if(moveLeft2)
    {
        trans1[0]-=0.01f;
        glutPostRedisplay();
    }
    if(moveRight2)
    {
        trans1[0]+=0.01f;
        glutPostRedisplay();
    }
    if(moveForward2)
    {
        trans1[2]+=0.01f;
        glutPostRedisplay();
    }
    if(moveBackward2)
    {
        trans1[2]-=0.01f;
        glutPostRedisplay();
    }

    if(toggleprism)
    {
        
    }
    if(togglepyr)
    {

    }
}




void keyboard(unsigned char key, int x, int y) {
    if(key=='w' || key=='W')
    {
        moveForward=true;
    }
    else if(key=='s' || key=='S')
    {
        moveBackward=true;
    }
    else if(key=='a' || key=='A')
    {
        moveLeft=true;
    }
    else if(key=='d' || key=='D')
    {
        moveRight=true;
    }
    else if(key=='q' || key=='Q')
    {
        moveUp=true;
    }
    else if(key=='e' || key=='E')
    {
        moveDown=true;
    }
    else if(key=='u' || key=='U')
    {
        moveUp2=true;
    }
    else if(key=='o' || key=='O')
    {
        moveDown2=true;
    }
    else if(key=='l' || key=='L')
    {
        moveLeft2=true;
    }
    else if(key=='i' || key=='I')
    {
        moveRight2=true;
    }
    else if(key=='z' || key=='Z')
    {
        moveForward2=true;
    }
    else if(key=='y' || key=='Y')
    {
        moveBackward2=true;
    }
    else if(key=='t' || key=='T')
    {
            if(toggleprism)
            {
                togglepyr=true;
                toggleprism=false;
            }
            else if(togglepyr)
            {
                togglepyr=false;
                toggleprism=true;
            }
            glutPostRedisplay();
    }
    else if(key=='r' || key=='R')
    {
        rotatePrism('X');
        glutPostRedisplay();
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    if(key=='w' || key=='W')
    {
        moveForward=false;
    }
    else if(key=='s' || key=='S')
    {
        moveBackward=false;
    }
    else if(key=='a' || key=='A')
    {
        moveLeft=false;
    }
    else if(key=='d' || key=='D')
    {
        moveRight=false;
    }
    else if(key=='q' || key=='Q')
    {
        moveUp=false;
    }
    else if(key=='e' || key=='E')
    {
        moveDown=false;
    }
    else if(key=='u' || key=='U')
    {
        moveUp2=false;
    }
    else if(key=='o' || key=='O')
    {
        moveDown2=false;
    }
    else if(key=='l' || key=='L')
    {
        moveLeft2=false;
    }
    else if(key=='i' || key=='I')
    {
        moveRight2=false;
    }
    else if(key=='z' || key=='Z')
    {
        moveForward2=false;
    }
    else if(key=='y' || key=='Y')
    {
        moveBackward2=false;
    }
    else if(key=='r' || key=='R')
    {
        rotatePrism('X');
        glutPostRedisplay();
    }
}




void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
   glLoadIdentity(); 
    //glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
   //glOrtho(-1, 1, -1, 1, -1, 1);
    glTranslatef(trans1[0],trans1[1],trans1[2]);
    //gluLookAt(5, 5, 5, 0, 0, 0, 0, 0, 1); // Set up the camera
     //gluLookAt(2, 2, 2, 0, 0, 0, 0, 0, 1);
    // gluLookAt(cameraX, cameraY, cameraZ, xcenter, ycenter, zcenter, 0, 1, 0);
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);
    
    
    int sides = 3;
    if (::argc > 1) {
        sides = atoi(::argv[1]);
    }
    // printf("%d %d",toggleprism,togglepyr);
    if(toggleprism)
    drawPrism(sides, 1.0f, 2.0f); // Drawprism
    else if(togglepyr)
    drawPyramid(sides, 1.0f, 2.0f); // Drawprism

    // glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
}


void update(int value) {
    updateCamera();
    glutTimerFunc(16, update, 0);
}


int main(int _argc, char** _argv) {
    ::argc = _argc;
    ::argv = _argv;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Prism");

    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 


    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)500 / 500, 1.0f, 100.0f);
    
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    

    return 0;
}
