#include <GLUT/glut.h> //ライブラリ読み込み
#include <math.h>

//表示部分
void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //消去色指定
	glClear(GL_COLOR_BUFFER_BIT);	  //画面消去

	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		double x = cos(i * 3.14159 / 180.0);
		double y = sin(i * 3.14159 / 180.0);
		glVertex2d(x, y);
	}
	glEnd();

	glFlush(); //画面出力
}

//メインプログラム
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
