#define NOMINMAX // Windows ��� min/max �̃}�N���𖳌������邽�߂̂��܂��Ȃ�
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include <algorithm>
#include <vector>

// 3�����x�N�g��
class Vector3d
{
public:
	double x, y, z;
	Vector3d() { x = y = z = 0; }
	Vector3d(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	void set(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	// ������1�ɐ��K������
	void normalize()
	{
		double len = length();
		x /= len;
		y /= len;
		z /= len;
	}

	// ������Ԃ�
	double length() { return sqrt(x * x + y * y + z * z); }

	// s�{����
	void scale(const double s)
	{
		x *= s;
		y *= s;
		z *= s;
	}

	// ���Z�̒�`
	Vector3d operator+(Vector3d v) { return Vector3d(x + v.x, y + v.y, z + v.z); }

	// ���Z�̒�`
	Vector3d operator-(Vector3d v) { return Vector3d(x - v.x, y - v.y, z - v.z); }

	// ���ς̒�`
	double operator*(Vector3d v) { return x * v.x + y * v.y + z * v.z; }

	// �O�ς̒�`
	Vector3d operator%(Vector3d v) { return Vector3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

	// ������Z�̒�`
	Vector3d &operator=(const Vector3d &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return (*this);
	}

	// ���Z����̒�`
	Vector3d &operator+=(const Vector3d &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	// ���Z����̒�`
	Vector3d &operator-=(const Vector3d &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}

	// �l���o�͂���
	void print() { printf("Vector3d(%f %f %f)\n", x, y, z); }
};
// �}�C�i�X�̕����̕t�����x�N�g����������悤�ɂ��邽�߂̒�` ��Fb=(-a); �̂悤�ɋL�q�ł���
Vector3d operator-(const Vector3d &v) { return (Vector3d(-v.x, -v.y, -v.z)); }

// �x�N�g���Ǝ����̐ς�������悤�ɂ��邽�߂̒�` ��F c=5*a+2*b; c=b*3; �̂悤�ɋL�q�ł���
Vector3d operator*(const double &k, const Vector3d &v) { return (Vector3d(k * v.x, k * v.y, k * v.z)); }
Vector3d operator*(const Vector3d &v, const double &k) { return (Vector3d(v.x * k, v.y * k, v.z * k)); }

// �x�N�g���������Ŋ��鑀���������悤�ɂ��邽�߂̒�` ��F c=a/2.3; �̂悤�ɋL�q�ł���
Vector3d operator/(const Vector3d &v, const double &k) { return (Vector3d(v.x / k, v.y / k, v.z / k)); }

// ���_
class Point
{
public:
	Vector3d f;	 // ���_�ɓ����͂̃x�N�g��
	Vector3d v;	 // ���x�x�N�g��
	Vector3d p;	 // �ʒu
	bool bFixed; // true: �Œ肳��Ă��� false:�Œ肳��Ă��Ȃ�
};

// �o�l
class Spring
{
public:
	Point *p0;		   // ���_
	Point *p1;		   // ���_
	double restLength; // ���R��

	double length()
	{
		return (p0->p - p1->p).length();
	}

	Spring(Point *_p0, Point *_p1)
	{
		p0 = _p0;
		p1 = _p1;
		restLength = length();
	}
};

#define POINT_NUM 20

// �z�̒�`
class Cloth
{
public:
	Point points[POINT_NUM][POINT_NUM];
	std::vector<Spring *> springs;

	Cloth()
	{
		// ���_�̒�`
		for (int y = 0; y < POINT_NUM; y++)
		{
			for (int x = 0; x < POINT_NUM; x++)
			{
				points[x][y].bFixed = false;
				points[x][y].p.set(x - POINT_NUM / 2, POINT_NUM / 2, -y);
			}
		}

		// �o�l�̐ݒ�
		for (int y = 0; y < POINT_NUM; y++)
		{
			for (int x = 0; x < POINT_NUM; x++)
			{
				// �������̃o�l
				if (x < POINT_NUM - 1)
				{
					springs.push_back(new Spring(&points[x][y], &points[x + 1][y]));
				}

				// �c�����̃o�l
				if (y < POINT_NUM - 1)
				{
					springs.push_back(new Spring(&points[x][y], &points[x][y + 1]));
				}

				// �E�������̃o�l
				if (x < POINT_NUM - 1 && y < POINT_NUM - 1)
				{
					springs.push_back(new Spring(&points[x][y], &points[x + 1][y + 1]));
				}

				// ���������̃o�l
				if (x > 0 && y < POINT_NUM - 1)
				{
					springs.push_back(new Spring(&points[x][y], &points[x - 1][y + 1]));
				}
			}
		}

		// �Œ�_�̎w��
		points[0][0].bFixed = true;
		points[POINT_NUM - 1][0].bFixed = true;
	}
};

Cloth *cloth;
double rotateAngleH_deg; // ��ʐ��������̉�]�p�x
double rotateAngleV_deg; // �c�����̉�]�p�x
int preMousePositionX;	 // �}�E�X�J�[�\���̈ʒu���L�����Ă����ϐ�
int preMousePositionY;	 // �}�E�X�J�[�\���̈ʒu���L�����Ă����ϐ�
bool bRunning;			 // �A�j���[�V�����̎��s/��~��؂�ւ���t���O

double Ks = 8;					// �o�l�萔
double Mass = 30;				// ���_�̎���
double dT = 1;					// ���ԍ��ݕ�
double Dr = 0.1;				// ���x�ɔ�Ⴕ�āA�t�����ɂ͂��炭��R�W��
Vector3d gravity(0, -0.002, 0); // �d��(y�������̕��̌����ɓ���)

void drawCloth(void)
{

	// �o�l��`��
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < cloth->springs.size(); i++)
	{
		glVertex3d(cloth->springs[i]->p0->p.x, cloth->springs[i]->p0->p.y, cloth->springs[i]->p0->p.z);
		glVertex3d(cloth->springs[i]->p1->p.x, cloth->springs[i]->p1->p.y, cloth->springs[i]->p1->p.z);
	}
	glEnd();

	// ���_��`��
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	for (int y = 0; y < POINT_NUM; y++)
	{
		for (int x = 0; x < POINT_NUM; x++)
		{
			glVertex3d(cloth->points[x][y].p.x, cloth->points[x][y].p.y, cloth->points[x][y].p.z);
		}
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glTranslated(0, 0.0, -50);

	glRotated(rotateAngleV_deg, 1.0, 0.0, 0.0);
	glRotated(rotateAngleH_deg, 0.0, 1.0, 0.0);

	drawCloth();

	glFlush();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{

	if (key == '\033' || key == 'q')
	{
		exit(0);
	} // ESC �܂��� q �ŏI��
	if (key == 'a')
	{
		bRunning = !bRunning;
	} // a �ŃA�j���[�V�����̃I���I�t
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		preMousePositionX = x;
		preMousePositionY = y;
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		preMousePositionX = x;
		preMousePositionY = y;
		break;
	default:
		break;
	}
}

// �z�̌`��̍X�V
void updateCloth(void)
{
	for (int y = 0; y < POINT_NUM; y++)
	{
		for (int x = 0; x < POINT_NUM; x++)
		{
			cloth->points[x][y].f.set(0, 0, 0); //������
		}
	}

	// 1. ���_�ɓ����͂����߂�
	for (int i = 0; i < cloth->springs.size(); i++)
	{
		// cloth�I�u�W�F�N�g�� i �Ԗڂ̃o�l���擾
		Spring *spring = cloth->springs[i];

		// �o�l�̎��R���i�ƁA���݂̒����̍��������߂�
		double d = spring->length() - spring->restLength;

		// �o�l�̎��ɓ��Ă͂߂Čv�Z
		Vector3d e = (spring->p1->p - spring->p0->p);
		e.normalize();
		Vector3d Fs = e * d * Ks;

		// ���[�̎��_�ɑ΂��āA�̓x�N�g�������Z����
		spring->p0->f += Fs;
		spring->p1->f -= Fs;
	}

	for (int y = 0; y < POINT_NUM; y++)
	{
		for (int x = 0; x < POINT_NUM; x++)
		{
			// �d�́A��C��R�ɂ��͂����Z����
			Point *p = &(cloth->points[x][y]);
			p->f += gravity * Mass - p->v * Dr;
		}
	}

	for (int y = 0; y < POINT_NUM; y++)
	{
		for (int x = 0; x < POINT_NUM; x++)
		{
			Point *p = &(cloth->points[x][y]);
			// 2. ���_�̉����x�����߂�
			// 3. ���_�̑��x�����߂�
			p->v += p->f * (dT / Mass);
			// 4. ���_�̈ʒu���X�V����
			if (!p->bFixed) //�Œ肳��Ă��Ȃ�point�����ψʂ�����
			{
				p->p += p->v * dT;
			}
		}
	}
}

void motion(int x, int y)
{
	int diffX = x - preMousePositionX;
	int diffY = y - preMousePositionY;

	rotateAngleH_deg += diffX * 0.1;
	rotateAngleV_deg += diffY * 0.1;

	preMousePositionX = x;
	preMousePositionY = y;
	glutPostRedisplay();
}

// ��莞�Ԃ��ƂɎ��s�����
void timer(int value)
{
	if (bRunning)
	{
		updateCloth();
		glutPostRedisplay();
	}

	glutTimerFunc(10, timer, 0);
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[])
{

	bRunning = true;
	cloth = new Cloth();

	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(10, timer, 0);

	init();
	glutMainLoop();
	return 0;
}