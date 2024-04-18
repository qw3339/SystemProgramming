#include<iostream>
using namespace std;
#define MIN_TANK_VOLUME 20
#define MAX_TANK_VOLUME 20120

class Tank
{
	const int VOLUME;
	double fuei_level;
public:
	const int get_VOLUME()const
	{
		return VOLUME;

	}
	double get_fuei_level()const
	{
		return fuei_level;

	}
	void fill(double amount)
	{
		if (amount < 0);
		if (fuei_level + amount < VOLUME)fuei_level += amount;
		else fuei_level = VOLUME;

	}
	double give_fuel(double amount)
	{
		if (amount < 0)return fuei_level;
		fuei_level -= amount;
		if (fuei_level < 0)fuei_level = 0;
		return fuei_level;

	}
	Tank(int volume):VOLUME(
		volume<MIN_TANK_VOLUME? MIN_TANK_VOLUME: 
		volume>MAX_TANK_VOLUME? MAX_TANK_VOLUME:
		volume)
	{
		//if (volume < MIN_TANK_VOLUME)volume = MIN_TANK_VOLUME;
		//if (volume < MAX_TANK_VOLUME)volume = MAX_TANK_VOLUME;
		/*this->VOLUME = volume;*/
		this->fuei_level = 0;
		cout << "Tank is r " << this << endl;

	}



	void info()const
	{
		cout << "Tank VOLUME: " << VOLUME << " liters.\n";
		cout << "Fuel level: " << fuei_level << " liters.";
	}


};


void main()
{
	setlocale(LC_ALL, " ");
	Tank tank(85);
	int fuel;
	do
	{
		cout << " "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (fuel>0);

	

}
 