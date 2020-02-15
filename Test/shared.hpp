#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <random>

using namespace std;

template<typename T = double>
struct Vec2
{
	T x, y;
	Vec2() : x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2 operator+(Vec2 v)
	{
		return Vec2(x + v.x, y + v.y);
	}
	Vec2 operator-(Vec2 v)
	{
		return Vec2(x - v.x, y - v.y);
	}
	Vec2 operator*(T value)
	{
		return Vec2(x * value, y * value);
	}
	Vec2 operator/(T value)
	{
		return Vec2(x / value, y / value);
	}
	Vec2& operator+=(Vec2 v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2& operator*=(T& value)
	{
		x *= value;
		y *= value;
		return *this;
	}
	void operator()(T len, T angle)
	{
		x = len * cos(angle);
		y = len * sin(angle);
	}
	Vec2 operator()() //v^2
	{
		return Vec2(cos(atan2(y, x)) * (pow(x, 2) + pow(y, 2)), sin(atan2(y, x)) * (pow(x, 2) + pow(y, 2)));
	}
};

struct Wind
{
	double viscosity, density;
	Vec2<double> Vel;
	Wind()
	{
		viscosity = 0.000018;
		density = 1.2;  //kg/m^3 1.2
		Vel.x = -500;
		Vel.y = 100;
	}
};

struct Railgun
{
	double angle, force, length;
	Railgun()
	{
		angle = 0.78;
		force = 10000;
		length = 1;
	}
};

struct Bullet
{
	double mass, radius;
	unsigned int color;
	Vec2<double> Pos, Vel;
	Bullet(Railgun& r, ranlux48& e, double mass, double radius) : mass(mass), radius(radius)
	{
		color = e();
		Pos(r.length, r.angle);
		Vel(sqrt(2 * r.force * r.length / mass), r.angle);
	}
};

struct World
{
	Wind mWind;
	Railgun mRailgun;
	vector<Bullet> Bullets;
	ranlux48 engine;
	double gravity;
	double bMass, bRadius;

	World();
	void Fire();
	void Tick(double time);
};