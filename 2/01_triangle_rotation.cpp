#include <math.h>
#include <GLUT/glut.h> // ライブラリ用ヘッダファイルの読み込み

int rotateAngle; // 回転角度を記録しておく変数

// 表示部分をこの関数で記入
void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // 消去色指定
	glClear(GL_COLOR_BUFFER_BIT);	  // 画面と奥行き情報を初期化

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(rotateAngle, 0, 0, 1);

	glColor3d(1.0, 0.0, 0.0); // 色指定(R,G,B)で0～1まで
	glBegin(GL_TRIANGLES);
	glVertex3d(0, 0, 0);
	glVertex3d(0.5, 0, 0);
	glVertex3d(0.5, 0.5, 0);
	glEnd();

	glutSwapBuffers(); // バッファの入れ替え
}

// 一定時間ごとに呼び出される関数
void timer(int value)
{
	rotateAngle++; // 回転角度の更新

	glutPostRedisplay();		 // 再描画命令
	glutTimerFunc(10, timer, 0); // 100ミリ秒後に自身を実行する
}

// メインプログラム
int main(int argc, char *argv[])
{
	glutInit(&argc, argv); // ライブラリの初期化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(400, 400); // ウィンドウサイズを指定
	glutCreateWindow(argv[0]);	  // ウィンドウを作成
	glutDisplayFunc(display);	  // 表示関数を指定

	glutTimerFunc(100, timer, 0); // 100ミリ秒後に実行する関数の指定

	rotateAngle = 0; // 変数の初期値の設定

	glutMainLoop(); // イベント待ち
	return 0;
}
