#include <math.h>
#include <GLUT/glut.h> // ライブラリ用ヘッダファイルの読み込み

int inflateX;
int inflateY;

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); //消去色
    glClear(GL_COLOR_BUFFER_BIT);     //画面と奥行き情報を初期化

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glColor3d(1.0, 0.0, 0.0);
    glTranslated(-0.5, 0.0, 0);
    glScaled(inflateX * 0.01, inflateY * 0.01, 1.0);
    glCallList(1);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.0, 1.0, 0.0);
    glTranslated(0.5, 0.0, 0);
    glScaled(inflateX * 0.01, inflateY * 0.01, 1.0);
    glCallList(1);
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value)
{
    if (inflateX <= 50)
    {
        inflateX++;
    }
    if (inflateY <= 100)
    {
        inflateY++;
    }

    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

void buildDisplayList()
{
    glNewList(1, GL_COMPILE);
    glBegin(GL_QUADS);
    glVertex2d(-1.0, 1.0);
    glVertex2d(-1.0, -1.0);
    glVertex2d(1.0, -1.0);
    glVertex2d(1.0, 1.0);
    glEnd();
    glEndList();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); //ライブラリの初期化
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutInitWindowSize(400, 400);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);

    glutTimerFunc(100, timer, 0);

    buildDisplayList();

    inflateX = 1;
    inflateY = 1;

    glutMainLoop();
    return 0;
}