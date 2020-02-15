#include "shared.hpp"
#include <iostream>

World::World()
{
	engine.seed(1337);
	gravity = 9.81;
	bMass = 50;
	bRadius = 0.1;
}

void World::Fire()
{
	Bullets.push_back(Bullet(mRailgun, engine, bMass, bRadius));
}

void World::Tick(double time)
{	
	for (auto iter = Bullets.begin(); iter != Bullets.end();)
	{
		if (iter->Pos.x >= 256 or iter->Pos.x < -256 or iter->Pos.y >= 256 or iter->Pos.y < -256)
			Bullets.erase(iter);
		else
			iter++;
	}
	for (Bullet& bullet : Bullets)
	{
		Vec2 diff = mWind.Vel - bullet.Vel;
		
		double K1 = 6 * M_PI * mWind.viscosity * bullet.radius;
		double K2 = 0.4 * M_PI * pow(bullet.radius, 2) * mWind.density / 2;

		Vec2 T1 = diff * K1;
		Vec2 T2 = diff() * K2;
		Vec2 vertical(double(0), mWind.density * gravity * 4 / 3 * M_PI * pow(bullet.radius, 3) - bullet.mass * gravity);

		bullet.Vel += (T1 + T2 + vertical) / bullet.mass * time;
		bullet.Pos += bullet.Vel * time;
	}
}