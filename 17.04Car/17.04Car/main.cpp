#include<iostream>
#include<conio.h>
#include <thread>
#include <Windows.h>
using namespace std;
using namespace std::chrono_literals;

#define Enter 13
#define Escape 27
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
	struct Threads
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
	}threads;


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
		threads.panel_thread = std::thread(&Car::panel, this);

	}
	void get_out()
	{
		system("CLS");
		driver_inside = false;
		if(threads.panel_thread.joinable())threads.panel_thread.join();
		
		cout << "Out of the car " << endl;
	}

	void start()
	{
		if (tank.get_fuei_level())
		{
			engine.start();
			threads.engine_idle_thread = std::thread(&Car::engine_idel, this);
		}
	}

	void stop()
	{
		engine.stop();
		if (threads.engine_idle_thread.joinable())threads.engine_idle_thread.join();

	}

	void control()
	{
		char key;
		do
		{
			key = _getch();
			switch (key)
			{
			case 'F':
			case'f':
				if (driver_inside)
				{
					cout << "Get out of the car\a " << endl;
				}
				else
				{
					double fuel;
					cout << "¬ведите уровень топлива: "; cin >> fuel;
					tank.fill(fuel);
				}
				break;
			case Enter: driver_inside ? get_out() : get_in(); break;
			case'I':
			case'i': engine.started() ? stop() : start(); break;
			case Escape:
				stop();
				get_out();  break;				
			}
		} while (key != 27);
	}

	void engine_idel()
	{
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
			this_thread::sleep_for(1s);

	}


	void panel()const
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Fuel level: \t" << tank.get_fuei_level() << " liters.\t";
			if (tank.get_fuei_level() < 5)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << " LOW FUEL ";
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			cout << endl;
			
			cout << "Engine is " << (engine.started() ? "started" : "stopped") << endl;
			std::this_thread::sleep_for(2s);
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
 