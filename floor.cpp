#include <GL/glut.h>
#include <glm/glm.hpp>
#include <SDL/SDL.h>

#include <unistd.h>

using namespace std;

int window;

#define TEXTURE_SKY_TOP 0
#define TEXTURE_SKY_FRONT 1
#define TEXTURE_SKY_LEFT 2
#define TEXTURE_SKY_RIGHT 3
#define TEXTURE_SKY_BACK 4
#define TEXTURE_COUNT 5
GLuint  textures[TEXTURE_COUNT];
const char *szTextureFiles[TEXTURE_COUNT] = {"sky_top.bmp", "sky_front.bmp", "sky_left.bmp", "sky_right.bmp", "sky_back.bmp"};

glm::vec3 cameraPos   = glm::vec3(0.0f, 2.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
float yaw   =  -90.0f;
float pitch =  0.0f;
float lastX =  1920.0 / 2;
float lastY =  1080.0 / 2;

void MyInit(){
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_DECAL);
	
	glGenTextures(TEXTURE_COUNT, textures);
    SDL_Surface *TextureImage;
    
    for(int i = 0; i < TEXTURE_COUNT; i++){

        glBindTexture(GL_TEXTURE_2D, textures[i]);
		TextureImage = SDL_LoadBMP(szTextureFiles[i]);
		
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->w, TextureImage->h, GL_BGR, GL_UNSIGNED_BYTE, TextureImage->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        SDL_FreeSurface(TextureImage);
    }
	
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);
   
	glEnable(GL_CULL_FACE);
	
  
    glEnable(GL_LIGHTING);  
  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    glEnable(GL_COLOR_MATERIAL);  

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  

    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 2000);
    glMatrixMode(GL_MODELVIEW);

    glutWarpPointer(1920.0 / 2.0, 1080.0 / 2.0);

}

void RenderScene(){
    GLUquadricObj *pObj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glCullFace(GL_BACK);
	glFrontFace(GL_CW);  
	
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SKY_TOP]);
    glBegin(GL_QUADS);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1000.0f, 1000.0f, -1000.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f, 1000.0f, -1000.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f, 1000.0f, 1000.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1000.0f, 1000.0f, 1000.0f);
			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SKY_BACK]);
glBegin(GL_QUADS);
glTexCoord2f(1.0f, 0.0f);
		
		
		glVertex3f(1000.0f, 1000.0f, 1000.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1000.0f, 1000.0f, 1000.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1000.0f, -1000.0f, 1000.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1000.0f, -1000.0f, 1000.0f);
			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SKY_FRONT]);
	glBegin(GL_QUADS);	
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1000.0f, -1000.0f, -1000.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f, -1000.0f, -1000.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f, 1000.0f, -1000.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1000.0f, 1000.0f, -1000.0f);
			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SKY_RIGHT]);
glBegin(GL_QUADS);
glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f, 1000.0f, 1000.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1000.0f, 1000.0f, -1000.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1000.0f, -1000.0f, -1000.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f, -1000.0f, 1000.0f);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SKY_LEFT]);
			
glBegin(GL_QUADS);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1000.0f, 1000.0f, -1000.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1000.0f, 1000.0f, 1000.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1000.0f, -1000.0f, 1000.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1000.0f, -1000.0f, -1000.0f);
	glEnd();
    
    //glCullFace(GL_FRONT);
	//glFrontFace(GL_CW); 
	
    glm::vec3 f = cameraPos + cameraFront;
    
    glLoadIdentity();
    gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, f.x, f.y, f.z, cameraUp.x, cameraUp.y, cameraUp.z);
    
    glBegin(GL_QUADS);
        int i = 0;
        for (GLint x = -50; x < 50; ++x) {
            for (GLint y = -50; y < 50; ++y) {
                if(((x + y) % 2) == 0){
                    glColor3f(0.3, 0.7, 1.0);
                }else {
                    glColor3f(1.0, 1.0, 1.0);
                }

                glVertex3f(    x, 0.0,    y);
                glVertex3f(    x, 0.0,   (y+1));
                glVertex3f((x+1), 0.0,   (y+1));
                glVertex3f((x+1), 0.0,    y);
            }
        }
        
    glEnd();

    glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f);

        pObj = gluNewQuadric();  
        gluQuadricNormals(pObj, GLU_SMOOTH);  

        glColor3f(1.0f, 1.0f, 1.0f);  

        // head
        glPushMatrix();
            glTranslatef(0.0f, 1.0f, 0.0f);
            gluSphere(pObj, 0.24f, 26, 13);
        glPopMatrix();

        // body
        glPushMatrix();
            glTranslatef(0.0f, 0.5f, 0.0f);
            gluSphere(pObj, 0.35f, 26, 13);
        glPopMatrix();

        // body
        glPushMatrix();
            glTranslatef(0.0f, -0.2f, 0.0f);
            gluSphere(pObj, 0.5f, 26, 13);
        glPopMatrix();

        // Nose
        glColor3f(1.0f, 0.4f, 0.51f);  
        glPushMatrix();
            glTranslatef(0.0f, 1.0f, 0.2f);
            gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);  
        glPopMatrix();

        // eyes
        glColor3f(0.0f, 0.0f, 0.0f); 
        glPushMatrix();
            glTranslatef(-0.1f, 1.1f, 0.2f);
            gluSphere(pObj, 0.03f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.1f, 1.1f, 0.2f);
            gluSphere(pObj, 0.03f, 26, 13);
        glPopMatrix();

        // hat
        glPushMatrix();
            glTranslatef(0.0f, 1.3f, 0.0f);
            glRotatef(90, 1, 0, 0);
            gluCylinder(pObj, 0.3f, 0.3f, 0.1f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, 1.3f, 0.0f);
            glRotatef(-90, 1, 0, 0);
            gluDisk(pObj, 0.0f, 0.3f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, 1.2f, 0.0f);
            glRotatef(90, 1, 0, 0);
            gluDisk(pObj, 0.0f, 0.3f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, 1.8f, 0.0f);
            glRotatef(90, 1, 0, 0);
            gluCylinder(pObj, 0.18f, 0.18f, 0.5f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, 1.8f, 0.0f);
            glRotatef(-90, 1, 0, 0);
            gluDisk(pObj, 0.0f, 0.18f, 26, 13);
        glPopMatrix();

        // arms
        glPushMatrix();
            glTranslatef(-0.8f, 1.3f, 0.0f);
            glRotatef(90, 0, 1, 0);
            glRotatef(45, 1, 0, 0);
            gluCylinder(pObj, 0.01f, 0.01f, 0.8f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.28f, 0.68f, 0.0f);
            glRotatef(90, 0, 1, 0);
            glRotatef(-45, 1, 0, 0);
            gluCylinder(pObj, 0.01f, 0.01f, 0.8f, 26, 13);
        glPopMatrix();

    glPopMatrix();  

    glutSwapBuffers();
}

void MotionFunc(int x, int y){

    float xpos = static_cast<float>(x);
    float ypos = static_cast<float>(y);

    float sensitivity = 0.3f; 

    if(xpos == 0){
        yaw   -= 1 + sensitivity;
        firstMouse = true;

    }else if(xpos == 1919){
        yaw   += 1 + sensitivity;
        firstMouse = true;

    }else if(ypos == 0){
        pitch += 1 + sensitivity;
        firstMouse = true;

    }else if(ypos == 1079){
        pitch -= 1 + sensitivity;
        firstMouse = true;

    }else {
        if(firstMouse){
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;
    }
    
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    
    //glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y){
     const float cameraSpeed = 0.1f;

     if(key == 27){
     	glutDestroyWindow(1);
     }

     if(key == 'w'){
         cameraPos += cameraSpeed * cameraFront;   
     }

     if(key == 's'){
         cameraPos -= cameraSpeed * cameraFront;   
     }

     if(key == 'a'){
         cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
     }
    
     if(key == 'd'){
         cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
     }
    
     //glutPostRedisplay();
}

int main(int argc, char **argv){
        
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize(666, 666);   
    glutCreateWindow("Floor");
    glutFullScreen();
    
    glutKeyboardFunc(KeyboardFunc);
    glutPassiveMotionFunc(MotionFunc);
    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);

    MyInit();
    glutMainLoop();

    return 0;
}
