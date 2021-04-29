#include <GLUT/glut.h> // ライブラリ用ヘッダファイルの読み込み

// 表示部分をこの関数で記入
void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // 消去色指定
    glClear(GL_COLOR_BUFFER_BIT);     // 画面消去

    glColor3d(0.0, 0.0, 0.0); // 色指定(R,G,B)で0～1まで
    glBegin(GL_QUADS);
    int slice = 100; //平面を均等に分割する数（1以上）
    for (int i = 0; i <= (slice * 2) - 1; i++)
    {
        for (int j = 0; j <= (slice * 2) - 1; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                glVertex2d(-1.0 + (2.0 / (slice * 2) * i), 1.0 - (2.0 / (slice * 2) * j));
                glVertex2d(-1.0 + (2.0 / (slice * 2) * i), 1.0 - (2.0 / (slice * 2) * (j + 1)));
                glVertex2d(-1.0 + ((2.0 / (slice * 2)) * (i + 1)), 1.0 - (2.0 / (slice * 2) * (j + 1)));
                glVertex2d(-1.0 + ((2.0 / (slice * 2)) * (i + 1)), 1.0 - (2.0 / (slice * 2) * j));
            }
            else if (i % 2 == 1 && j % 2 == 1)
            {
                glVertex2d(-1.0 + (2.0 / (slice * 2) * i), 1.0 - (2.0 / (slice * 2) * j));
                glVertex2d(-1.0 + (2.0 / (slice * 2) * i), 1.0 - (2.0 / (slice * 2) * (j + 1)));
                glVertex2d(-1.0 + ((2.0 / (slice * 2)) * (i + 1)), 1.0 - (2.0 / (slice * 2) * (j + 1)));
                glVertex2d(-1.0 + ((2.0 / (slice * 2)) * (i + 1)), 1.0 - (2.0 / (slice * 2) * j));
            }
        }
    }
    glEnd();

    glFlush(); // 画面出力
}

// メインプログラム
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);        // ライブラリの初期化
    glutInitWindowSize(800, 800); // ウィンドウサイズを指定
    glutCreateWindow(argv[0]);    // ウィンドウを作成
    glutDisplayFunc(display);     // 表示関数を指定
    glutMainLoop();               // イベント待ち
    return 0;
}