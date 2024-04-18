#include<iostream>
#include<conio.h>
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
		cout << "Tank is ready: " << this << endl;

	}
	~Tank()
	{
		cout << "Tank is over: " << this << endl;
	}



	void info()const
	{
		cout << "Tank VOLUME: " << VOLUME << " liters.\n";
		cout << "Fuel level: " << fuei_level << " liters.\n";
	}


};
#define MIN_ENGINE_CONSUMPTION 3
#define MAX_ENGINE_CONSUMPTION 30
class Engine
{
	double CONSUMPTION;
	double consumption_per_second;
	bool is_started;
public:
	double get_consumption()const
	{
		return CONSUMPTION;

	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	Engine(double consumption)
		: CONSUMPTION
		(
			consumption < MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
			consumption < MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
			consumption
		),
		consumption_per_second(CONSUMPTION * 3e-5),
		is_started(false)
	{
		/*consumption_per_second = CONSUMPTION * 3e-5;*/
		cout << "Engine is ready: " << this << endl;



	}
	~Engine()
	{
		cout << "Engine is over: " << this << endl;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}


	void info()const
	{
		cout << "Consumption: " << CONSUMPTION<< " liters/100km" << endl;
		cout << "Consumption: " << consumption_per_second << " liters/100km" << endl;
		cout << "Engine is : " << (is_started? "started" : "stopped")  << endl;
	
	}



};
class Car
{
	Engine engine;
	Tank tank;
	bool driver_inside;
public:
	Car(int consumption = 10, int volume = 60) :engine(consumption), tank(volume), driver_inside(false)
	{
		cout << "Youn car is ready to go "<< endl;

	}
	~Car() 
	{
		cout << "Youn car is over " << endl;

	}
	
	void get_in()
	{
		driver_inside = true;
		panel();

	}
	void get_out()
	{
		driver_inside = false;
		cout << "Out of the car " << endl;
	}

	void control()
	{
		char key;
		do
		{
			key = _getch();
			switch (key)
			{
			case 13: driver_inside ? get_out() : get_in(); break;
				
			}

		} while (key != 27);


	}


	void panel()const
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Fuel level: \t" << tank.get_fuei_level() << " liters.\n";
			cout << "Engine is " << (engine.started() ? "started" : "stopped") << endl;

		}

	}
	void info()const
	{
		engine.info();
		tank.info();

	}
};


//#define TANK_CHECK
//#define ENGINE

void main()
{
	setlocale(LC_ALL, " ");
#if defined TANK_CHECK
	//если определено танк чекЅ ниже следующей код до дерективы endif будет виден компел€тору.
	Tank tank(85);
	int fuel;
	do
	{
		cout << " "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (fuel > 0);
#endif // TANK_CHECK
#ifdef ENGINE

	Engine engine(10);
	engine.info();
#endif // ENGINE

	Car bmw;
	bmw.info();
	bmw.control();


}
 