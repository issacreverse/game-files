#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <cstdlib>
using namespace std;

static int diceVal;

void Erase();

class Submarine
{
private:
	string shipName;
	int hitPoints;
	string cmd;
	int cmd2;
	
	Submarine* target;

	int ammunitionDamage;
	
	//false: damaged
	bool oxygenSystem;   //1
	bool fuelTank;       //2
	bool wheelHouse;     //3
	bool torpedoGate;    //4
	//empty room         //5
	bool radioSystem;    //6
	bool ammunition;     //7
public:
	bool enhancedEvasionSystem;
	bool evadable;
	Submarine(int hitPoints, string shipName)
	{
		this->hitPoints = hitPoints;
		this->shipName = shipName;
		enhancedEvasionSystem = false;
		evadable = true;
		
		oxygenSystem = true;
		fuelTank = true;
		wheelHouse = true;
		torpedoGate = true;
		radioSystem = true;
		ammunition = true;
		ammunitionDamage = 0;
	}
	void SetTarget(Submarine* sub)
	{
		target = sub;
	}
	void ShootTorpedo()
	{
		int evasionNum = rand()%6+1;
		Erase();
		cout << "\n\nShrooooooom..." << endl << endl;
		Sleep(1500);
		if(!target->evadable)
		{
			TorpedoHit();
			return;
		}
		else if(!target->enhancedEvasionSystem)
		{
			if(evasionNum <= 4)
				TorpedoHit();
			else
			{
				Erase();
				cout << "Torpedo missed" << endl;
				Sleep(1500);
			}
		}
		else
		{
			if(evasionNum <= 2)
			{
				TorpedoHit();
			}
			else
			{
				Erase();
				cout << "Torpedo missed" << endl;
				Sleep(1500);
			}
			target->enhancedEvasionSystem = false;
		}
	}
	void ShootDepthCharge()
	{
		Erase();
		cout << "\n\nBlop..Blop..." << endl << endl;
		Sleep(1500);
		DepthChargeHit();
	}
	void TorpedoHit()
	{
		int damageNum = rand()%7 +1;
		cout << "BOOOM" << endl << "Torpedo Hit!" << endl;
		Sleep(1500);
		target->hitPoints -= 10;
		if(!target->fuelTank)
			target->hitPoints -=10;
		if(target->hitPoints <= 0)
			target->Dead();
		switch(damageNum)
		{
			case 1: 
				cout << target->shipName << "'s Oxygen System is Damaged!" << endl;
				Sleep(1500);
				target->oxygenSystem = false;
				break;
			case 2:
				cout << target->shipName << "'s Fuel Tank is Damaged!" << endl;
				Sleep(1500);
				target->fuelTank = false;
				break;
			case 3:
				cout << target->shipName << "'s WheelHouse is Damaged!" << endl;
				Sleep(1500);
				target->wheelHouse = false;
				target->evadable = false; 
				break;
			case 4: 
				cout << target->shipName << "'s Torpedo Gate is Damaged!" << endl;
				Sleep(1500);
				target->torpedoGate = false;
				break;
			case 5:
				cout << "we hit an empty room" << endl;
				Sleep(1500);
				break;
			case 6:
				cout << target->shipName << "'s Radio System is Damaged!" << endl;
				Sleep(1500);
				target->radioSystem = false;
				break;
			case 7:
				target->AmmunitionHit();
				break;
		}
		cout << endl;
	}		
	void DepthChargeHit()
	{
		int damageNum = rand()%7 +1;
		cout << "BOOOM" << endl << "Depth Charge Hit!" << endl;
		Sleep(1500);
		
		switch(damageNum)
		{
			case 1: 
				cout << target->shipName << "'s Oxygen System is Damaged!" << endl;
				Sleep(1500);
				target->oxygenSystem = false;
				break;
			case 2:
				cout << target->shipName << "'s Fuel Tank is Damaged!" << endl;
				Sleep(1500);
				target->fuelTank = false;
				break;
			case 3:
				cout << target->shipName << "'s WheelHouse is Damaged!" << endl;
				Sleep(1500);
				target->wheelHouse = false;
				target->evadable = false; 
				break;
			case 4: 
				cout << target->shipName << "'s Torpedo Gate is Damaged!" << endl;
				Sleep(1500);
				target->torpedoGate = false;
				break;
			case 5:
				break;
			case 6:
				cout << target->shipName << "'s Radio System is Damaged!" << endl;
				Sleep(1500);
				target->radioSystem = false;
				break;
			case 7:
				target->AmmunitionHit();
				break;
		}
		cout << endl;
	}
	void LowOxygen()
	{
		cout << "\nSeems like the oxygen is leaking out....." << endl << endl;
		hitPoints -= 10;
		Sleep(1500);
		Erase();
		if(hitPoints <= 0)
		{
			Dead();
		}
	}
	void AmmunitionHit()
	{
		cout << shipName << "'s Ammunition Hit!!" << endl;
		Sleep(1500);
		ammunitionDamage++;
		if(ammunitionDamage == 1)
		{
			cout << "Ammunition damaged" << endl;
			Sleep(1500);
		}
		else if(ammunitionDamage == 2)
		{
			cout << "Ammunition can't stand any longer..." << endl;
			Sleep(1500);
		}
		else if(ammunitionDamage == 3)
		{
			cout << "Ammunition Exploded." << endl;
			Sleep(1500);
			Dead();
		}
	}
	string ShowSystemInfo(bool flag)
	{
		if(flag)
			return "normal operation";
		else
			return "damaged";
	}
	bool ShowSystemInfo(int num)
	{
		switch(num)
		{
			case 1:
				return oxygenSystem;
			case 2:
				return fuelTank;
			case 3:
				return wheelHouse;
			case 4: 
				return torpedoGate;
			case 6:
				return radioSystem;
			default:
				return false;
		}
	}
	void ShowSubInfo()
	{
		Erase();
		cout << shipName << "\t\tHitPoints: " << hitPoints << endl << endl;
		
		cout << "///Systems///" << endl;
		cout << "1: Oxygen System\t" << ShowSystemInfo(oxygenSystem) << endl; 
		cout << "2: Fuel Tank\t\t" << ShowSystemInfo(fuelTank) << endl;
		cout << "3: WheelHouse\t\t" << ShowSystemInfo(wheelHouse) << endl;
		cout << "4: Torpedo Gate\t\t" << ShowSystemInfo(torpedoGate) << endl;
		cout << "5: Empty" << endl;
		cout << "6: Radio System\t\t" << ShowSystemInfo(radioSystem) << endl;
		cout << "7: Ammunition\t\t" << ShowSystemInfo(ammunition) << endl << endl;
		
		cout << "Enhanced Evasion System: " << (enhancedEvasionSystem ? "On" : "Off") << endl;
	}
	void Dead()
	{
		Erase();
		cout << "KABOOOOOM!!" << endl << endl;
		cout << "Mission Failed: " << shipName << " got wrecked" << endl;
		exit(1);
	}
	void Act()
	{
		cout << "--------------------------------------------" << endl;
		cout << "Captain Choosing what to do...\n" << endl;
		Sleep(1500);
		
		int actNum = rand()%15+1;
		
		if(actNum >=1 && actNum <=4) // Repair
		{
			cout << "Captain Ordered to Repair Damaged Components..." << endl << endl;
			Sleep(1500);
			if(oxygenSystem && fuelTank && wheelHouse && torpedoGate && radioSystem)
			{
				cout << "All Systems operating normal!" << endl;
				Sleep(1500);
			}
			else
			{
				int repairNum;
				while(true)
				{
					cout << "repair the systems?(y/n): ";
					cin >> cmd;
					if(cmd != "y")
					{
						cout << "\nYou decided not to repair the systems" << endl;
						Sleep(1500);
						return;
					}
					cout << "Enter the System Number you'd like to repair: ";
					cin	>> repairNum;
					if(repairNum < 0 || repairNum > diceVal)
					{
						cout << "No such system";
						Sleep(1500);
						continue;
					}
					else if(repairNum == 5 || repairNum == 7 || ShowSystemInfo(repairNum))
					{
						cout << "Can't repair that system";
						Sleep(1500);
						continue;
					}
					else 
					{
						if(!oxygenSystem)
						{
							LowOxygen();
						}
						switch(repairNum)
						{
							case 1: 
								Erase();
								cout << "repairing Oxygen System..." << endl << endl;
								Sleep(1500);
								cout << "Repair Complete";
								Sleep(1500);
								oxygenSystem = true;
								break;
							case 2:
								Erase();
								cout << "repairing Fuel Tank..." << endl << endl;
								Sleep(1500);
								cout << "Repair Complete";
								Sleep(1500);
								fuelTank = true;
								break;
							case 3: 
								Erase();
								cout << "repairing WheelHouse..." << endl << endl;
								Sleep(1500);
								cout << "Repair Complete";
								Sleep(1500);
								wheelHouse = true;
								evadable = true;
								break;
							case 4:
								Erase();
								cout << "repairing Torpedo Gate..." << endl << endl;
								Sleep(1500);
								cout << "Repair Complete";
								Sleep(1500);
								torpedoGate = true;
								break;
							case 6:
								Erase();
								cout << "repairing Radio System..." << endl << endl;
								Sleep(1500);
								cout << "Repair Complete";
								Sleep(1500);
								radioSystem = true;
								break;
						}
					}
					break;
				}
			}
		}
		else if(actNum >=5 && actNum <=10) // torpedo
		{
			cout << "Captain ordered to launch torpedo!" << endl << endl;
			Sleep(1500);
			
			cout << "launch torpedo?(y/n): ";
			cin >> cmd;
			if(cmd != "y")
			{
				cout << "\nYou decided not to launch torpedo" << endl;
				Sleep(1500);
				return;
			}
			if(torpedoGate)
			{
				if(!oxygenSystem)
				{
					LowOxygen();
				}
				Erase();
				cout << ">>Target Locked<<" << endl;
				Sleep(1500);
				Erase();
				cout << "Torpedo Fired" << endl;
				Sleep(1500);
				Erase();
				ShootTorpedo();
			}
			else
			{
				cout << "Torpedo Gate Damaged... We can't fire" << endl;
				Sleep(1500);
			}
		}
		else if(actNum >=11 && actNum <=13) // depth charge
		{
			cout << "Captain ordered to call for depth charge assistance" << endl << endl;
			Sleep(1500);

			cout << "Send request?(y/n): ";
			cin >> cmd;
			if(cmd != "y")
			{
				cout << "\nYou decided not to send request" << endl;
				Sleep(1500);
				return;
			}
			if(radioSystem)
			{
				if(!oxygenSystem)
				{
					LowOxygen();
				}
				Erase();
				cout << "Sending the request..." << endl;
				Sleep(1500);
				Erase();
				cout << "Request Sent" << endl;
				Sleep(1500);
				Erase();
				cout << "Ally destroyer dropped depth charges" << endl;
				Sleep(1500);
				Erase();
				ShootDepthCharge();
			}
			else
			{
				cout << "Radio System Damaged... We can't send the request" << endl;
				Sleep(1500);
			}
		}
		else if(actNum == 14) // enhanced evasion System
		{
			cout << "Captain ordered to operate enhanced evasion system" << endl << endl;
			Sleep(1500);

			cout << "operate the system?(y/n): ";
			cin >> cmd;
			if(cmd != "y")
			{
				cout << "\nYou decided not to operate the system" << endl;
				Sleep(1500);
				return;
			}
			if(!oxygenSystem)
			{
				LowOxygen();
			}
			Erase();
			cout << "Operating Enhanced Evasion System..." << endl;
			Sleep(1500);
			Erase();
			cout << "System ON" << endl;
			Sleep(1500);
			enhancedEvasionSystem = true;
		}
		else if(actNum == 15) // torpedo twice
		{
			cout << "Captain ordered to launch the ALL the torpedos!!" << endl << endl;
			Sleep(1500);


			if(!torpedoGate)
			{
				cout << "Torpedo Gate Damaged... We can't fire" << endl;
				Sleep(1500);
			}
			else
			{
				cout << "How many torpedo would you launch(0~2): ";
				cin >> cmd2;
				if(cmd2 != 1 && cmd2 != 2)
				{
					cout << "\nYou decided not to launch" << endl;
					Sleep(1500);
					return;
				}
				else if(cmd2 == 2)
				{
					//torpedo 2
					if(!oxygenSystem)
					{
						LowOxygen();
					}
					Erase();
					cout << ">>Target Locked<<" << endl;
					Sleep(1500);
					Erase();
					cout << "Torpedo Fired" << endl;
					Sleep(1500);
					Erase();
					ShootTorpedo();
				}
				//torpedo 1
				if(!oxygenSystem)
				{
					LowOxygen();
				}
				Erase();
				cout << ">>Target Locked<<" << endl;
				Sleep(1500);
				Erase();
				cout << "Torpedo Fired" << endl;
				Sleep(1500);
				Erase();
				ShootTorpedo();
			}
		}
	}
};


void Erase()
{
	system("cls");
}

int main()
{
	string buffer;
	srand(time(0));
	
	//settings

	while(true)
	{
		Erase();
		cout << "Select diceVal(expansion): ";
		cin >> diceVal;
		if(diceVal <6)
			continue;
		break;
	}
	
	
	//shipInfo
	string shipName1, shipName2;
	int hitPoints1, hitPoints2;
	
	Erase();
	cout << "Enter submarine1's Name: ";
	cin >> shipName1;
	cout << "Enter submarine1's hitPoints: ";
	cin >> hitPoints1;	
	
	Submarine sub1(hitPoints1, shipName1);
	
	Erase();
	cout << "Enter submarine2's Name: ";
	cin >> shipName2;
	cout << "Enter submarine2's hitPoints: ";
	cin >> hitPoints2;
	
	Submarine sub2(hitPoints2, shipName2);
	
	Erase();
	cout << "All submarines registered\n\n";
	
	sub1.SetTarget(&sub2);
	sub2.SetTarget(&sub1);

	cout << "Battle Engaged in...\n";
	for(int i=0; i<5; i++)
	{
		cout << 5-i << endl;
		Sleep(1000);
	}
	Erase();
	
	cout << "Player1 Starts First";
	Sleep(1500);
	Erase();
	
	while(true)
	{
		Erase();
		cout << "player1's turn";
		Sleep(1500);
		sub1.ShowSubInfo();
		sub1.Act();
		Sleep(1500);
		sub1.ShowSubInfo();

		cout << "\nEnter any key to switch turn";
		cin >> buffer;
		getline(cin, buffer);
		
		Erase();
		cout << "player2's turn";
		Sleep(1500);
		sub2.ShowSubInfo();
		sub2.Act();
		Sleep(1500);
		sub2.ShowSubInfo();

		cout << "\nEnter any key to switch turn";
		cin >> buffer;
		getline(cin, buffer);
	}
}
