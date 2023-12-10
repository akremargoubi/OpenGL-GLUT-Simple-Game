#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>


/*camera globals*/
double camX = 70; double camY = 70; double camZ = 70;
bool skycam = false;
static int slices = 32; static int stacks = 32;
double trackLength = 3000;
double cameraDistance  = 70; double cameraHeight  = 40;
double ps = 5;
double tx = 0; double ty = 0; double tz = 0;

/*PLAYER COLOR AND EMOTION*/
char emotion = 'i';  double cR = 0.5; double cG = 0.5; double cB = 0.5;

/*PLAYER MOVEMENTS*/
double playerX = -0; double playerZ = 0; double playerXSpeed = 0.45; double playerZSpeed = 0.3;
double playerAngle = -90;
bool isMovingForward = false; bool isMovingBackward = false; bool isMovingLeft = false; bool isMovingRight = false;
bool isRotatingLeft = false; bool isRotatingRight = false;

/*GAME  SETTING*/
bool playing = false;
char* lobbyText = "PLAY >"; //"YOU WON / YOU LOST";

/*GAMEPLAY*/
int collisionTimes = 0;
double TIME = 0;
double REMAINING_TIME = 0;
double REQUIRED_TIME = 60;

/* GLUT callback Handlers */
void axis(){
    glTranslated(0,0,50);
    glPushMatrix(); glColor3d(1,0,0); glScaled(50,1,1); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glColor3d(0,1,0); glScaled(1,50,1); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glColor3d(0,0,1); glScaled(1,1,50); glutSolidCube(1); glPopMatrix();
    }


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar,ar,-1.0,1.0,2.0,1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


// Normal Mvt MovePlayer function
void MovePlayer(){
    if(isMovingForward && playerX > -2550 ){
        playerX -= playerXSpeed;
        if ( !(isMovingLeft) || !(isMovingRight)){playerAngle = -90;} // rotate forwards
    }
    if(isMovingBackward && playerX <= 0){
        playerX += playerXSpeed;
        if ( !(isMovingLeft) || !(isMovingRight)){playerAngle = 90;} // rotate backwards
    }
    if(isMovingLeft && (playerZ < 72) ){
        playerZ += playerZSpeed;
        if(playerAngle < -45){ playerAngle += 0.5;} // rotate when moving left
    }
    if(isMovingRight && (playerZ > -72) ){
        playerZ -= playerZSpeed;
        if(playerAngle > -135){ playerAngle -= 0.5;} // rotate when moving right
    }
    if(isRotatingLeft && (playerAngle < -45)){
        playerAngle += 1;
    }
    if(isRotatingRight && (playerAngle > -135) ){
        playerAngle -= 1;
    }

    glutPostRedisplay();
}


///////////////////////RABBIT PLAYER start
//////////////////////////////////////////

void renderLeftArm(){
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(-1,-1.37,0); glScaled(0.24,0.57,0.315); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(-0.98,-1.9,0); glScaled(0.2,0.5,0.2); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0.6,0.6,0.6); glTranslated(-0.9,-2.4,0); glScaled(0.16,0.18,0.15); glutSolidSphere(1,slices,stacks); glPopMatrix();
}
void renderRightArm(){
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(1,-1.37,0); glScaled(0.24,0.57,0.315); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(0.98,-1.9,0); glScaled(0.2,0.5,0.2); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0.6,0.6,0.6); glTranslated(0.9,-2.4,0); glScaled(0.16,0.18,0.15); glutSolidSphere(1,slices,stacks); glPopMatrix();
}
void renderLeftLeg(){
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(-0.44,-3.34,0); glRotated(-20,0,0,0); glScaled(0.35,1.2,0.35); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(-0.44,-4.35,0.1); glScaled(0.28,0.19,0.38); glutSolidSphere(1,slices,stacks); glPopMatrix();
}
void renderRightLeg(){
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(0.44,-3.34,0); glRotated(20,0,0,0); glScaled(0.35,1.2,0.35); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(0.44,-4.35,0.1); glScaled(0.28,0.19,0.38); glutSolidSphere(1,slices,stacks); glPopMatrix();
}
void renderHead(){
    //Head
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(0,0.5,0); glScaled(0.8,0.8,0.5); glutSolidSphere(1,slices,stacks); glPopMatrix();
    //Cheeks
    glPushMatrix(); glColor3d(0.8,0.8,0.8); glTranslated(0,0,0); glScaled(1,0.55,0.55); glutSolidSphere(1,slices,stacks); glPopMatrix();
    //eyes
    glPushMatrix(); glColor3d(1,1,1); glTranslated(0.3,0.5,0.5); glScaled(0.2,0.25,0.01); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0,0.5,1); glTranslated(0.3,0.42,0.5); glScaled(0.15,0.15,0.02); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0,0,0); glTranslated(0.3,0.4,0.55); glScaled(0.06,0.06,0.02); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(1,1,1); glTranslated(-0.3,0.5,0.5); glScaled(0.2,0.25,0.01); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0,0.5,1); glTranslated(-0.3,0.42,0.5); glScaled(0.15,0.15,0.02); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0,0,0); glTranslated(-0.3,0.4,0.55); glScaled(0.06,0.06,0.02); glutSolidSphere(1,slices,stacks); glPopMatrix();
    //ears
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(0.55,1.5,0); glRotated(-15,0,0,1); glScaled(0.2,1,0.02); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0.8,0.4,0.7); glTranslated(0.55,1.5,0.009); glRotated(-15,0,0,1); glScaled(0.15,0.8,0.02); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(-0.55,1.5,0); glRotated(15,0,0,1); glScaled(0.2,1,0.02); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0.8,0.4,0.7); glTranslated(-0.55,1.5,0.009); glRotated(15,0,0,1); glScaled(0.15,0.8,0.02); glutSolidSphere(1,slices,stacks); glPopMatrix();
    //nose
    glPushMatrix(); glColor3d(0.8,0.4,0.7); glTranslated(0,0.24,0.45); glScaled(0.11,0.11,0.11); glutSolidSphere(1,slices,stacks); glPopMatrix();
    //staches
    glPushMatrix(); glColor3d(0.2,0.2,0.2); glTranslated(0.75,0.06,0.4); glRotated(-15,0,0,1); glScaled(0.5,0.01,0.01); glutSolidSphere(1,slices,stacks); glPopMatrix(); //L
    glPushMatrix(); glColor3d(0.2,0.2,0.2); glTranslated(0.9,-0.06,0.44); glRotated(-15,0,0,1); glScaled(0.5,0.01,0.01); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0.2,0.2,0.2); glTranslated(0.94,-0.17,0.43); glRotated(-15,0,0,1); glScaled(0.5,0.01,0.01); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0.2,0.2,0.2); glTranslated(-0.75,0.06,0.4); glRotated(15,0,0,1); glScaled(0.5,0.01,0.01); glutSolidSphere(1,slices,stacks); glPopMatrix(); //R
    glPushMatrix(); glColor3d(0.2,0.2,0.2); glTranslated(-0.9,-0.06,0.44); glRotated(15,0,0,1); glScaled(0.5,0.01,0.01); glutSolidSphere(1,slices,stacks); glPopMatrix();
    glPushMatrix(); glColor3d(0.2,0.2,0.2); glTranslated(-0.94,-0.17,0.43); glRotated(15,0,0,1); glScaled(0.5,0.01,0.01); glutSolidSphere(1,slices,stacks); glPopMatrix();
    //mouth
    if(emotion == 's'){
        glPushMatrix(); glColor3d(1,0.1,0.6); glTranslated(0,0,0.46); glRotated(-10,1,0,0); glScaled(0.5,0.25,0.05); glutSolidSphere(1,slices,stacks); glPopMatrix();
    }else if(emotion == 't'){
        glPushMatrix(); glColor3d(1,0.1,0.6); glTranslated(0,-0.07,0.44); glRotated(20,1,0,0); glScaled(0.5,0.25,0.05); glutSolidSphere(1,slices,stacks); glPopMatrix();
    }else{
        glPushMatrix(); glColor3d(1,0.1,0.6); glTranslated(0,0,0.5); glRotated(0,0,0,0); glScaled(0.25,0.025,0.1); glutSolidSphere(1,slices,stacks); glPopMatrix();
        glPushMatrix(); glColor3d(1,1,1); glTranslated(-0.055,-0.05,0.5); glScaled(0.1,0.1,0.1); glutSolidCube(1); glPopMatrix();
        glPushMatrix(); glColor3d(1,1,1); glTranslated(0.055,-0.05,0.5); glScaled(0.1,0.1,0.1); glutSolidCube(1); glPopMatrix();
    }
}

void renderRabbit(double t){

    if (isMovingForward || isMovingBackward){
            glPushMatrix(); glTranslated(0,0.1*sin(t/10),0); renderHead(); glPopMatrix();
    } else {
        glPushMatrix(); glTranslated(0,0.01*sin(t/10),0); renderHead(); glPopMatrix();
    }
    //shoulders
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(0,-0.96,0); glScaled(1.2,0.38,0.42); glutSolidSphere(1,slices,stacks); glPopMatrix();
    //stomach
    glPushMatrix(); glColor3d(cR,cG,cB); glTranslated(0,-1.89,0); glScaled(0.79,1.54,0.66); glutSolidSphere(1,slices,stacks); glPopMatrix();
    //INNER
    glPushMatrix(); glColor3d(0.8,0.8,0.8); glTranslated(0,-1.93,0.09); glScaled(0.72,1.2,0.65); glutSolidSphere(1,slices,stacks); glPopMatrix();
    if (isMovingForward || isMovingBackward){
        //Legs
        glPushMatrix(); glRotated(10*sin(t/8),1,0,0); renderLeftLeg(); glPopMatrix();
        glPushMatrix(); glRotated(10*-sin(t/8),1,0,0); renderRightLeg(); glPopMatrix();
        //arms
        glPushMatrix(); glRotated(10*-sin(t/8),1,0,0); renderLeftArm(); glPopMatrix();
        glPushMatrix(); glRotated(10*sin(t/8),1,0,0); renderRightArm(); glPopMatrix();
    }else{
        renderLeftLeg(); renderRightLeg();renderLeftArm(); renderRightArm();
    }
    glPushMatrix(); glColor3d(0.8,0.8,0.8); glTranslated(0,-2.5,-0.75); glScaled(0.2,0.2,0.2); glutSolidSphere(1,slices,stacks); glPopMatrix();

}



void renderTree(double angle){
    glPushMatrix();
    glRotated(angle,0,1,0);
    glColor3d(0.545,0.376,0.075);
    glPushMatrix(); glTranslatef(0,0,0); glRotated(90,1,0,0); gluCylinder(gluNewQuadric(),0.2,0.2,4,4,4); glPopMatrix(); //stem
    glPushMatrix(); glColor3d(0.133, 0.545, 0.133); glTranslatef(0,0.6,-1.5); glutSolidSphere(1,8,8); glPopMatrix(); //bush1
    glPushMatrix(); glColor3d(0.000, 0.502, 0.000); glTranslatef(0,1.7,0); glutSolidSphere(1.75,8,8); glPopMatrix(); //bush2
    glPushMatrix(); glColor3d(0.180, 0.545, 0.341); glTranslatef(0,0.6,1.5); glutSolidSphere(1.5,8,8); glPopMatrix(); //bush3
    glPopMatrix();
}


void renderTerrain(){
    glPushMatrix(); glColor3d(0.3,0.4,0.4); glTranslated(-trackLength/2,0,0); glScaled(3500,0.1,500); glutSolidCube(1); glPopMatrix();


    glPushMatrix();
        for(int i = 0; i < 25; i++){
            glPushMatrix();
             glTranslated(-i*120,27,90); glScaled(7,7,7); renderTree(30); glPopMatrix();
            glPushMatrix(); glTranslated(-i*120,27,160); glScaled(7,7,7); renderTree(30); glPopMatrix();
            glPushMatrix(); glTranslated(-i*120,27,-90); glScaled(7,7,7); renderTree(30); glPopMatrix();
            glPushMatrix(); glTranslated(-i*120,27,-160); glScaled(7,7,7); renderTree(30); glPopMatrix();
        }
    glPopMatrix();

}


void renderTrack(){

    glPushMatrix(); glColor3d(0.815,0.388,0.274); glTranslated(-trackLength/2,0.1,0); glScaled(trackLength,0.1,150); glutSolidCube(1); glPopMatrix(); //orange
    glPushMatrix(); glColor3d(1,1,1); glTranslated(-trackLength/2,0.1,-20); glScaled(trackLength,0.2,5); glutSolidCube(1); glPopMatrix(); //stripes
    glPushMatrix(); glColor3d(1,1,1); glTranslated(-trackLength/2,0.1,20); glScaled(trackLength,0.2,5); glutSolidCube(1); glPopMatrix();

    glPushMatrix(); glColor3d(0.6,0.2,1); glTranslated(-trackLength/2,0,77); glScaled(trackLength,10,5); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glColor3d(0.6,0.2,1); glTranslated(-trackLength/2,0,-77); glScaled(trackLength,10,5); glutSolidCube(1); glPopMatrix();
    //torus start
    glPushMatrix(); glColor3d(0.6,0.2,1); glTranslated(0,0,0); glRotated(90,0,1,0); glScaled(1,1,1); glutSolidTorus(5,75,64,64); glPopMatrix();
    glPushMatrix(); glColor3d(0.9,0.1,0.6); glTranslated(-500,0,0); glRotated(90,0,1,0); glScaled(1,1,1); glutSolidTorus(5,75,64,64); glPopMatrix();
    glPushMatrix(); glColor3d(0.9,0.2,0.9); glTranslated(-1000,0,0); glRotated(90,0,1,0); glScaled(1,1,1); glutSolidTorus(5,75,64,64); glPopMatrix();
    glPushMatrix(); glColor3d(0.9,1,0.3); glTranslated(-1500,0,0); glRotated(90,0,1,0); glScaled(1,1,1); glutSolidTorus(5,75,64,64); glPopMatrix();
    glPushMatrix(); glColor3d(0.9,0.5,0); glTranslated(-2000,0,0); glRotated(90,0,1,0); glScaled(1,1,1); glutSolidTorus(5,75,64,64); glPopMatrix();
    glPushMatrix(); glColor3d(0.4,0.5,1); glTranslated(-2500,0,0); glRotated(90,0,1,0); glScaled(1,1,1); glutSolidTorus(5,75,64,64); glPopMatrix();
}

 void renderRockObstacle(double x = 0, double z = 0){
    glPushMatrix(); glColor3d(0.4,0.5,0.5); glTranslated(x,2,z);glutSolidSphere(22,4,4); glPopMatrix();
 }

const int numberOfObstacles = 20;
float obstaclePositions[numberOfObstacles][2] = {
                                {-250,-45},{-250,45},
                                {-500,0},{-500,45},
                                {-750,0},{-750,-45},
                                {-1000,-45},{-1000,45},
                                {-1250,0},{-1250,45},
                                {-1500,0},{-1500,-45},
                                {-1750,-45},{-1750,45},
                                {-2000,0},{-2000,45},
                                {-2250,0},{-2250,-45},
                                {-2500,-45},{-2500,45},
        };

void renderObstacles(){
    for(int i = 0; i<=numberOfObstacles; i++){
        renderRockObstacle(obstaclePositions[i][0],obstaclePositions[i][1]);
    }
}

bool checkCollision(double plx,double ply,double obx,double oby){
    if( (plx < -225 && plx > -275) && (ply>18.5 || ply < -18.5) || //1
        (plx < -475 && plx > -525) && (ply>-25) ||                 //2
        (plx < -725 && plx > -775) && (ply<25)  ||                 //3
        (plx < -975 && plx > -1025) && (ply>18.5 || ply < -18.5) ||//4
        (plx < -1225 && plx > -1275) && (ply>-25) ||               //5
        (plx < -1475 && plx > -1525) && (ply<25)  ||               //6
        (plx < -1725 && plx > -1775) && (ply>18.5 || ply < -18.5) || //7
        (plx < -1975 && plx > -2025) && (ply>-25) ||                //8
        (plx < -2225 && plx > -2275) && (ply<25)  ||                 //9
        (plx < -2475 && plx > -2525) && (ply>18.5 || ply < -18.5) //10
        ){
        return true;
    }
    return false;
}

void onCollide(){
    if(checkCollision(playerX,playerZ,0,0)){
        collisionTimes += 1;
        playerX += 50; //playerZ = 0;
        printf("collided %i Times \n",collisionTimes);
    }
    if(collisionTimes >= 3){
           collisionTimes = 0;
           playerX = 0;
           playerZ = 0;
           playing = false;
           emotion = 't';
           printf("you lost !");
           lobbyText = "YOU LOST";
    }
}


void displayLobbyText(char* text , float x , float y , float z){
    glPushMatrix();
        glRasterPos3f(x,y,z);
        while (*text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
            text++;
        }
    glPopMatrix();
}

void displayPlayText(char* text , float x , float y , float z){
    glPushMatrix();
    glColor3d(1.0, 1.0, 1.0);
    glRasterPos3f(x,y,z);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *text);
        text++;
    }

    glPopMatrix();
}

void resetGame(){
    playerX = 0;
    playerZ = 0;
    playerAngle = -90;
    TIME = 0;
    REMAINING_TIME = 0;
}




static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; //t = seconds
    const double a = t*90.0;

    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    if(playing){ // START GAME
        TIME += 1; //start timer
        REMAINING_TIME = REQUIRED_TIME - TIME/100;

        if (REMAINING_TIME < 0){ resetGame(); emotion = 't'; lobbyText = "YOU LOST"; playing = false;}

        if  (skycam){
            gluLookAt(camX,camY,camZ,playerX,20,0,0,1,0);
        }else{
            gluLookAt(cameraDistance+playerX,cameraHeight,0,playerX,20,0,0,1,0);
        }


        char tit1 [100];
        snprintf(tit1,sizeof(tit1),"Remaining Time : %.0f s",REMAINING_TIME);
        displayPlayText(tit1,playerX,52+ty,45+tz);

        char tit2 [100];
        snprintf(tit2,sizeof(tit2),"Remaining Life Count : %.0i",3 - collisionTimes);
        displayPlayText(tit2,playerX,50+ty,46+tz);


        glPushMatrix();
            if(playerX < -2500){
                printf("you won !");
                resetGame(); playing = false; emotion = 's'; lobbyText = "YOU WON !";
            }
            onCollide();
            MovePlayer(); glTranslated(playerX,15,playerZ); glRotated(playerAngle,0,1,0); glScaled(3,3,3); renderRabbit(a);
        glPopMatrix();

        renderTerrain();

        renderTrack();

        renderObstacles();

        //axis();


    }else{ // PAUSED GAME
        gluLookAt(40+playerX,15,0,playerX,20,0,0,1,0);

        displayLobbyText("PRESS [ S ] TO START THE GAME",0,30,15);
        displayLobbyText("Use ARROW KEYS to move the player",0,28,15);
        displayLobbyText("PRESS [ R ] [ G ] [ B ] [ N ] to Change the player color",0,26,15);
        displayLobbyText("PRESS [ I ] [ T ] [ K ] to Change the player emotions",0,24,15);

        displayLobbyText(lobbyText,0,20,15);


        glPushMatrix(); glTranslated(playerX,15,playerZ); glRotated(a*1.2,0,1,0); glScaled(3,3,3); renderRabbit(a); glPopMatrix();


    }

    glPopMatrix();

    glutSwapBuffers();
}



void mouseButtons(int button , int state , int x , int y){
    switch(button){
        case GLUT_RIGHT_BUTTON :
             if (state == GLUT_DOWN){isRotatingRight = true;}else{isRotatingRight = false;}
        break;
        case GLUT_LEFT_BUTTON :
             if (state == GLUT_DOWN){isRotatingLeft = true;}else{isRotatingLeft = false;}
        break;
    }

}

void arrowKeysPressed(int key , int x , int y){
    switch(key){
        case GLUT_KEY_UP : isMovingForward = true; break;
        case GLUT_KEY_DOWN : isMovingBackward = true; break;
        case GLUT_KEY_RIGHT : isMovingRight = true; break;
        case GLUT_KEY_LEFT : isMovingLeft = true; break;
    }


}

void arrowKeysReleased(int key , int x , int y){
    switch(key){
        case GLUT_KEY_UP : isMovingForward = false; break;
        case GLUT_KEY_DOWN : isMovingBackward = false; break;
        case GLUT_KEY_RIGHT : isMovingRight = false; break;
        case GLUT_KEY_LEFT : isMovingLeft = false; break;


    }
}

void key(unsigned char key , int a , int b){
    switch(key){
        case 'n' : cR = 0.5; cG = 0.5; cB = 0.5; break;
        case 'r' : cR = 1.0; cG = 0.2; cB = 0.2; break;
        case 'g' : cR = 0.5; cG = 1.0; cB = 0.5; break;
        case 'b' : cR = 0.2; cG = 0.2; cB = 1.0; break;

        case 'i' : emotion = 'i'; break;
        case 't' : emotion = 't'; break;
        case 'k' : emotion = 's'; break;


        case 's' : playing = true; break;
        case 'p' : playing = false; break;


        case '-' : skycam = false; break; case '+' : skycam = true; break;
        case '6' : camX++; break; case '4' : camX--; break;
        case '8' : camY++; break; case '5' : camY--; break;
        case '9' : camZ++; break; case '7' : camZ--; break;



    }
    printf("tx : %.3f , ty : %.3f ,tz : %.3f\n",tx,ty,tz);
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1280,720);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    //glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseButtons);
    glutSpecialFunc(arrowKeysPressed);
    glutSpecialUpFunc(arrowKeysReleased);
    glutIdleFunc(idle);
gluLookAt(camX,camY,camZ,playerX,20,0,0,1,0);
    glClearColor(0.1,0.6,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
