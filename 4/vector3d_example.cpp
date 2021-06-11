#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <GLUT/glut.h>

using namespace std;

// 3次元ベクトルを扱うためのクラス
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

	// 長さを1に正規化する
	void normalize()
	{
		double len = length();
		x /= len;
		y /= len;
		z /= len;
	}

	// 長さを返す
	double length() { return sqrt(x * x + y * y + z * z); }

	// s倍する
	void scale(const double s)
	{
		x *= s;
		y *= s;
		z *= s;
	}

	// 加算の定義
	Vector3d operator+(Vector3d v) { return Vector3d(x + v.x, y + v.y, z + v.z); }

	// 減算の定義
	// ★加算の定義を参考に、減算のコードを記述してみる
	Vector3d operator-(Vector3d v) { return Vector3d(x - v.x, y - v.y, z - v.z); }

	// 内積の定義
	double operator*(Vector3d v) { return x * v.x + y * v.y + z * v.z; }

	// 外積の定義
	Vector3d operator%(Vector3d v) { return Vector3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

	// 代入演算の定義
	Vector3d &operator=(const Vector3d &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return (*this);
	}

	// 加算代入の定義
	Vector3d &operator+=(const Vector3d &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	// 減算代入の定義
	// ★加算代入の定義を参考に、減算代入のコードを記述してみる
	Vector3d &operator-=(const Vector3d &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}

	// 値を出力する
	void print() { printf("Vector3d(%f %f %f)\n", x, y, z); }
};

// マイナスの符号の付いたベクトルを扱えるようにするための定義 例：b=(-a); のように記述できる
Vector3d operator-(const Vector3d &v) { return (Vector3d(-v.x, -v.y, -v.z)); }

// ベクトルと実数の積を扱えるようにするための定義 例： c=5*a+2*b; c=b*3; のように記述できる
Vector3d operator*(const double &k, const Vector3d &v) { return (Vector3d(k * v.x, k * v.y, k * v.z)); }
Vector3d operator*(const Vector3d &v, const double &k) { return (Vector3d(v.x * k, v.y * k, v.z * k)); }

// ベクトルを実数で割る操作を扱えるようにするための定義 例： c=a/2.3; のように記述できる
Vector3d operator/(const Vector3d &v, const double &k) { return (Vector3d(v.x / k, v.y / k, v.z / k)); }

int main(int argc, char **argv)
{
	// 定義
	Vector3d a(2, 3, 4);
	Vector3d b(3, 5, -2);
	Vector3d c(2, -1, 1);

	// (a)
	Vector3d AnsV = a - b;
	AnsV.print();

	// (b)
	a.scale(3);
	b.scale(-2);
	AnsV = a + b;
	AnsV.print();
	// aとbを元の値に戻す
	a.set(2, 3, 4);
	b.set(3, 5, -2);

	// (c)
	double Ans = a * b;
	printf("%f\n", Ans);

	// (d)
	AnsV = a % b;
	AnsV.normalize();
	AnsV.print();

	// (e)
	b.scale(2);
	Vector3d temp = a + b;
	AnsV = temp % c;
	AnsV.print();

	// Visual Studio でコンソールがすぐに閉じないようにするためには次のコメントアウトをはずす
	//system("pause");
	return 0;
}
