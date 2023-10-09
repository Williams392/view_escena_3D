#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;

float camaraX = -30;
float camaraY = 20;
float camaraZ = 40;

float angulo = 0;

void iniciarVentana(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / (float)h, 1, 200);

}

void inicializarLuces() {

	GLfloat luz_ambiente[] = { 0.35, 0.35, 0.35,1 };
	GLfloat luz_difusa[] = { 0.5, 0.5, 0.5,1 };
	GLfloat luz_especular[] = { 0.3, 0.3, 0.3,1 };

	float posicionLuz[] = { 0,70,60,1 };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void piso() {
	glPushMatrix();
	glTranslated(0, -0.1, 0);
	glBegin(GL_POLYGON);
	glColor3ub(230, 230, 230);
	glVertex3d(-50, 0, -50);
	glVertex3d(50, 0, -50);
	glVertex3d(50, 0, 50);
	glVertex3d(-50, 0, 50);
	glEnd();
	glPopMatrix();
}
void ejes() {
	glPushMatrix();
	glBegin(GL_LINES);

	glColor3ub(230, 0, 0); // Rojo - X
	glVertex3d(0, 0, 0);
	glVertex3d(50, 0, 0);

	glColor3ub(0, 250, 0); // Verde - Y
	glVertex3d(0, 0, 0);
	glVertex3d(0, 50, 0);

	glColor3ub(0, 0, 250); // Azul - Z
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 50);

	glEnd();
	glPopMatrix();
}
void pared() {
	glBegin(GL_QUADS);

	// Pared frontal
	glColor3ub(0, 0, 0);  // Negro
	glVertex3d(-50, 0, -50);
	glVertex3d(50, 0, -50);
	glVertex3d(50, 50, -50);  // Altura de la pared
	glColor3ub(190, 86, 105); // Rojo
	glVertex3d(-50, 50, -50);

	// Pared trasera
	glColor3ub(0, 0, 0);  // Negro
	glVertex3d(-50, 0, 50);
	glVertex3d(50, 0, 50);
	glVertex3d(50, 50, 50);  // Altura de la pared
	glColor3ub(190, 86, 105); // Rojo
	glVertex3d(-50, 50, 50);

	// Pared izquierda
	glColor3ub(0, 0, 0);  // Negro
	glVertex3d(-50, 0, -50);
	glVertex3d(-50, 0, 50);
	glVertex3d(-50, 50, 50);  // Altura de la pared
	glColor3ub(190, 86, 105); // Rojo
	glVertex3d(-50, 50, -50);

	// Pared derecha
	glColor3ub(0, 0, 0);  // Negro
	glVertex3d(50, 0, -50);
	glVertex3d(50, 0, 50);
	glVertex3d(50, 50, 50);  // Altura de la pared
	glColor3ub(190, 86, 105); // Rojo
	glVertex3d(50, 50, -50);

	glEnd();
}



void dibujar() {

	inicializarLuces();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camaraX, camaraY, camaraZ, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	glRotated(angulo, 0, 1, 0);
	piso();
	ejes();
	//pared();
	glPopMatrix();


	glutSwapBuffers();

}

void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(20, timer, 20);
}

void teclado(int tecla, int x, int y) {

	switch (tecla) {
	case 101:
		camaraY += 0.2;
		break;
	case 103:
		camaraY += -0.2;
		break;
	case 100:
		angulo -= 1;
		break;
	case 102:
		angulo += 1;
		break;

	}
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1081, 762);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Plantilla - 3D");
	glutReshapeFunc(iniciarVentana);
	glutDisplayFunc(dibujar);
	glutSpecialFunc(teclado);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;

}