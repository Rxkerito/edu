#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <windows.h>

using namespace std;

const double PI = 3.141592653;
const double height = 25;
const double width = 25;

struct point {
	double x = 0;
	double y = 0;
};

void polygonf(point *polygon, int n);
bool n_square(int n, point *polygon, double x, double y);
double areaf(point* polygon, int n, point min, point max, int **mass);
bool circle(double a, double b, double r, double x, double y);
double area_circle(double a, double b, double r, point min, point max, int **mass);
void print(int** mass);

int main() {
	srand(time(NULL));
	int flag_f = 1;
	point min, max;
	min.x = 0; min.y = 0; max.x = 1; max.y = 1;
	int** mass;
	mass = new int* [25];
	for (int i = 0; i < 25; i++) {
		mass[i] = new int[25];
	}
	while (flag_f != 0) {
		cout << "Choose a figure" << endl;
		cout << "Polygon...1" << endl;
		cout << "Circle...2" << endl;
		cout << "Quit...0" << endl;
		cin >> flag_f;
		system("cls");
		if (flag_f == 1) {
			int n;
				cout << "enter peek count : ";
				cin >> n;
				system("cls");
				point* figure = new point[n];
				polygonf(figure, n);
				for (int i = 0; i < 25; i++) {
					for (int j = 0; j < 25; j++) {
						areaf(figure, n, min, max, mass);
						min.x++; max.x++;
					}
					min.y++; max.y++;
					min.x = 0; max.x = 1;
				}
			print(mass);
			min.x = 0; min.y = 0; max.x = 1; max.y = 1;
		}
		if (flag_f == 2) {
			double a, b, r;
			a = 12; b = 12;
				cout << "Enter  radius (r<12)" << endl;
				cin >> r;
			system("cls");
			for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 25; j++) {
					area_circle(a, b, r, min, max, mass);
					min.x++; max.x++;
				}
				min.y++; max.y++;
				min.x = 0; max.x = 1;
			}
			print(mass);
			min.x = 0; min.y = 0; max.x = 1; max.y = 1;
		}
	}
	return 0;
}

void polygonf(point* polygon, int n) {
	for (int i = 0; i < n; i++) {
		cout << "enter vertex coordinates (x,y < 25) " << i + 1 << endl;
		cin >> polygon[i].x;
		cin >> polygon[i].y;
	}
}

bool n_square(int n, point* polygon, double x, double y) {
	bool c = false;
	for (int i = 0, j = n - 1; i < n; j = i++)
	{
		if ((((polygon[i].y <= y) && (y < polygon[j].y)) || ((polygon[j].y <= y) && (y < polygon[i].y))) &&  //
			(((polygon[j].y - polygon[i].y) != 0) && (x > (polygon[j].x - polygon[i].x) * (y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)))
			c = !c;
	}
	return c;
}

double areaf(point* polygon, int n, point min, point max, int **mass) {
	srand(time(NULL));
	int sq1 = 0, sq2 = 0, maxx = max.x, maxy = max.y;
	int minx = min.x, miny = min.y;
	double randx, randy, area = 0;
	for (int i = 0; i < 10000; i++) {
		randx = min.x + 0.01 + rand() % 10 / 10.0;
		randy = min.y + 0.01 + rand() % 10 / 10.0;
		if (n_square(n, polygon, randx, randy) == 1) { sq2++; }
	}
	if (sq2 > 0) { mass[miny][minx] = 1; }
	else { mass[miny][minx] = 0; }
	if (sq2 > 500 && sq2 < 2500) { mass[miny][minx] = 2; }
	if (sq2 > 2500 && sq2 < 4500) { mass[miny][minx] = 4; }
	if (sq2 > 4500 && sq2 < 6500) { mass[miny][minx] = 6; }
	if (sq2 > 6500 && sq2 <= 10000) { mass[miny][minx] = 8; }
	area = (sq2 * 1.0 / 10000) * (width * height);
	return area;
}

bool circle(double a, double b, double r, double x, double y) {
	if ((r * r) > ((x - a) * (x - a) + (y - b) * (y - b))) { return 1; }
	return 0;
}

double area_circle(double a, double b, double r, point min, point max, int **mass) {
	srand(time(NULL));
	int sq1 = 0, sq2 = 0, maxx = max.x, maxy = max.y;
	int minx = min.x, miny = min.y;
	double randx, randy, area = 0;
	for (int i = 0; i < 10000; i++) {
		randx = min.x + 0.01 + rand() % 10 / 10.0;
		randy = min.y + 0.01 + rand() % 10 / 10.0;
		if (circle(a, b, r, randx, randy) == 1) { sq2++; }
	}
	if (sq2 > 0) { mass[miny][minx] = 1; }
	else { mass[miny][minx] = 0; }
	if (sq2 > 500 && sq2 < 2500) { mass[miny][minx] = 2; }
	if (sq2 > 2500 && sq2 < 4500) { mass[miny][minx] = 4; }
	if (sq2 > 4500 && sq2 < 6500) { mass[miny][minx] = 6; }
	if (sq2 > 6500 && sq2 <= 10000) { mass[miny][minx] = 8; }
	area = (sq2 * 1.0 / 10000) * (width * height);
	return area;
}

void print(int **mass) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			if (mass[i][j] == 0) { SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 0)); }
			if (mass[i][j] == 1) { SetConsoleTextAttribute(hConsole, (WORD)((1 << 4) | 0)); }
			if (mass[i][j] == 2) { SetConsoleTextAttribute(hConsole, (WORD)((3 << 4) | 0)); }
			if (mass[i][j] == 4) { SetConsoleTextAttribute(hConsole, (WORD)((2 << 4) | 0)); }
			if (mass[i][j] == 6) { SetConsoleTextAttribute(hConsole, (WORD)((6 << 4) | 0)); }
			if (mass[i][j] == 8) { SetConsoleTextAttribute(hConsole, (WORD)((4 << 4) | 0)); }
			cout << " " << " " << " " << " ";
		}
		cout << endl;
		for (int p = 0; p < 25; p++) {
			if (mass[i][p] == 0) { SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 0)); }
			if (mass[i][p] == 1) { SetConsoleTextAttribute(hConsole, (WORD)((1 << 4) | 0)); }
			if (mass[i][p] == 2) { SetConsoleTextAttribute(hConsole, (WORD)((3 << 4) | 0)); }
			if (mass[i][p] == 4) { SetConsoleTextAttribute(hConsole, (WORD)((2 << 4) | 0)); }
			if (mass[i][p] == 6) { SetConsoleTextAttribute(hConsole, (WORD)((6 << 4) | 0)); }
			if (mass[i][p] == 8) { SetConsoleTextAttribute(hConsole, (WORD)((4 << 4) | 0)); }
			cout << " " << " " << " " << " ";
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
}               
