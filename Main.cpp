#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <conio.h>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <vector>
#include <time.h>
#include "Person.h"
#include "DoublyLinkedNode.h"
#include "Effect.h"
#include "Statuses.h"
#include "Battle.h"
#include "Materials.h"
#include "Object.h"
#include "Itr.h"
#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h" -
#include "Enemy.h"
#include "Drake.h"
#include "Location.h"
#include "SinglyLinkedNode.h"
#include "SkillSet.h"
#include "Stack.h"

using namespace std;

//initialising states
bool lastScene = false;
string result = "";
bool hideDialg = false;
bool isFighting = false;
bool gameOn = true;
int key_down;


//Credit: https://www.asciiart.eu/weapons/swords

// Object carried by Drake
void Weapon(Drake& drake) 
{
	// if the object is a key
	if (drake.objectCarrying().getName() == "Metal key" || drake.objectCarrying().getName() == "Iron key" || drake.objectCarrying().getName() == "Steel key" || drake.objectCarrying().getName() == "Marble key") 
	{
		if (drake.objectCarrying().getStatus() == false) 
		{
			cout << "\n" << endl;
			cout << "  ,o.          8 8" << endl;
			cout << " d   bzzzzzzzza8o8b" << endl;
			cout << "  `o'" << endl;
		}
	}

	//if the object is healing potion
	else if (drake.objectCarrying().getName() == "Healing Potion") 
	{
		if (drake.objectCarrying().getStatus() == false) 
		{
			cout << "\nI feel so much better now." << endl;
			drake.setStrength(drake.getStrength() + drake.objectCarrying().getPower());
			drake.objectCarrying().setStatus(true);
		}
		else 
		{
			cout << "\nI don\'t have any more healing potion left." << endl;
		}
	}

	//if the object is a ring
	else if (drake.objectCarrying().getName() == "Ring") 
	{
		if (drake.objectCarrying().getStatus() == false) 
		{
			cout << "\nThe inscription on it says that it belonged to a man named Nathan Drake" << endl;
			drake.setHP(drake.getHP() + drake.objectCarrying().getPower());
			drake.objectCarrying().setStatus(true);
		}
		else 
		{
			cout << "I have the ring with me safely" << endl;
		}
	}
}

// Status of Drake
void Bar(Drake& drake) 
{
	Weapon(drake);
	cout << "PLAYER STATUS: " << endl;
	cout << "HP: " << drake.getHP() << endl;
	cout << "Energy: " << drake.getStrength() << endl;
}

// Status of Witch
void EnemyBar(Enemy& aEnemy) 
{
	cout << "Enemy STATUS: " << endl;
	cout << "HP: " << aEnemy.getHP() << endl;
	cout << "Shield: " << aEnemy.getHeal() << endl;
}

//Invalid Command entered
void InvalidOption() 
{
	cout << "Choose a valid option." << endl;
}

// List of options
void Command() 
{
	cout << "    Mapping     " << endl;
	cout << "(N) Step north" << endl;
	cout << "(S) Step south" << endl;
	cout << "(E) Step east" << endl;
	cout << "(W) Step west" << endl;
	cout << "(C) View Collection" << endl;
}

// Main class
int main() 
{

	

	//Initialising objects
	Object* healingPotion = new Object("Healing potion", "\nWhoa, this is a healing potion! What great luck!", 100);
	Object* metalKey = new Object("Metal key", "\nFound a metal key, maybe this will help get us out of here", 0);
	Object* ironKey = new Object("Iron key", "\nFound an iron key, maybe this will help get us out of here", 0);
	Object* steelKey = new Object("Steel key", "\nFound a steel key, maybe this will help get us out of here", 0);
	Object* marbleKey = new Object("Marble key", "\nFound a marble key, maybe this will help get us out of here", 0);
	Object* ring = new Object("Ring", "\nIt is exquisite. This place is filled with treasures of all kinds!", -20);
	Object* bandage = new Object("Ointment", "\nThis ointment will help with recoveries", 50);

	//initialising skill sets
	SkillSet* kick = new SkillSet("Kick", 37);
	SkillSet* punch = new SkillSet("Punch", 42);
	vector<SkillSet> drakeSkillSet = { *kick, *punch };
	SkillSet* stab = new SkillSet("Stab", 53);
	SkillSet* shoot = new SkillSet("Shoot", 49);
	vector<SkillSet> enemySkillSet = { *stab, *shoot };

	//initialising materails
	Materials* gate = new Materials("Gate", "It's locked. I have to insert a key to open it.");
	Materials* ground = new Materials("Ground", "The whole building is falling down I must hurry");
	Materials* keyStack = new Materials("Stack of keys", "It is a stack of keys. The keys can be removed from it one by one.");
	Materials* door = new Materials("Door", "Let me leave this place for now");
	Materials* potion = new Materials("Potion", "The label on this potion says that it is healing potion");
	Materials* inscription = new Materials("Inscription", "There is an inscription on the wall in Latin, is says... 'No one gets out of here alive' ");
	Materials* oldRing = new Materials("Ring", "This ring must be 2000 years old");
	Materials* ointment = new Materials("Ointment", "Oh look an ointment for cuts and scrapes");
	Materials* insect = new Materials("Insect", "This insect looks so different than anything I have ever seen");

	//initialising areas and locations
	Materials mainArea[4] = 
	{ 
		*door, *gate, *oldRing, *door 
	};

	Location* mainLoc = new Location(mainArea, true);


	Materials ringArea[4] = 
	{ 
		*door, *potion, *insect, *ground 
	};

	Location* ringLoc = new Location(ringArea, false);


	Materials keyArea[4] = 
	{ 
		*door, *ointment, *keyStack, *ground 
	};

	Location* keyLoc = new Location(keyArea, false);


	Materials battleArea[4] = 
	{ 
		*ground, *ground, *ground, *ground 
	};

	Location* battleLoc = new Location(battleArea, false);

	Statuses* injured = new Statuses("Blood Loss", 10);
	Statuses* sound = new Statuses("Screaming Noises", 5);

	//initialising statuses
	SinglyLinkedNode<Statuses> injury(*injured);
	SinglyLinkedNode<Statuses> noises(*sound, &injury);
	SinglyLinkedNode<Statuses>* startSingly = &noises;

	//the game starts from here
gameStart:
	//initialising players
	Drake* drake = new Drake(100, drakeSkillSet, 5, 200);
	Enemy* enemy = new Enemy(100, enemySkillSet, 15, 100);

	//initialising iterators
	Iterator<Object>* itr_Dbly = new DoublyLinkedList<Object>(drake->getFirstObject());
	DoublyLinkedList<Object>* dbly_ptr = dynamic_cast<DoublyLinkedList<Object>*>(itr_Dbly);

	//Fight
	Battle* fight = new Battle(*drake, *enemy);

	//Iterator singly linked list
	Iterator<Statuses>* iteratorSngl = new SinglyLinkedList<Statuses>(*startSingly);

	//Stack
	Stack<Object> Objectstack(4);
	Objectstack.add(*metalKey);
	Objectstack.add(*marbleKey);
	Objectstack.add(*steelKey);
	Objectstack.add(*ironKey);

	//ASCII art is generated from https://patorjk.com/software/taag/#p=display&f=Epic&t=CHARTED
	//title of the game
	cout << "_______           _______  _______ _________ _______  ______ " << endl;
	cout << "(  ____ \ |\      /|(  ___  )(  ____ )\__   __/(  ____ \(  __  \ " << endl;
	cout << "| (    \/ | )   ( || (   ) || (    )|   ) (   | (    \/| (  \  )" << endl;
	cout << "| |      | (___) || (___) || (____)|   | |   | (__   | |   ) |" << endl;
	cout << "| |      |  ___  ||  ___  ||     __)   | |   |  __)  | |   | |" << endl;
	cout << "| |      | (   ) || (   ) || (\ (       | |   | (     | |   ) |" << endl;
	cout << "| (____/\ | )   ( || )   ( || ) \ \__     | |   | (____/\| (__/  )" << endl;
	cout << "(_______/|/     \||/     \||/   \__/      )_(   (_______/(______/ \n" << endl;

	//slogan
	cout << "A Thief's Beginning\n" << endl;

	//game starts
	while (gameOn) {
		cout << "Start Game" << endl;
		cout << "A. Continue" << endl;
		cout << "B. End" << endl;
		key_down = _getch(); //Take user input in the form of ASCII code

		//when a key is pressed
		switch (key_down) 
		{
		case 65: case 97:
			system("cls");
			cout << "CHARTED";
			cout << "\nYou, and Elena stand still in the front of a large door.\nThe aura is mysterious and you look over to Elena who is breathing in this moment to remember it forever. " << endl;
			system("pause");
			//ascii art sourced from: https://www.asciiart.eu/buildings-and-places/castles
			system("cls");
			cout << "                                  |>>>" << endl;
			cout << "                                  |" << endl;
			cout << "                    |>>>      _  _|_  _         |>>>" << endl;
			cout << "                    |        |;| |;| |;|        |" << endl;
			cout << "                _  _|_  _    \\.    .  /    _  _|_  _ " << endl;
			cout << "               |;|_|;|_|;|    \\:. ,  /    |;|_|;|_|;|" << endl;
			cout << "               \\..      /    ||;   . |    \\.    .  /" << endl;
			cout << "                \\.  ,  /     ||:  .  |     \\:  .  /" << endl;
			cout << "                 ||:   |_   _ ||_ . _ | _   _||:   |" << endl;
			cout << "                 ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |" << endl;
			cout << "                 ||:   ||.    .     .      . ||:  .|" << endl;
			cout << "                 ||: . || .     . .   .  ,   ||:   |       \,/" << endl;
			cout << "                 ||:   ||:  ,  _______   .   ||: , |            /`\ " << endl;
			cout << "                 ||:   || .   /+++++++\    . ||:   |" << endl;
			cout << "                 ||:   ||.    |+++++++| .    ||: . |" << endl;
			cout << "              __ ||: . ||: ,  |+++++++|.  . _||_   |" << endl;
			cout << "     ____--`~    '--~~__|.    |+++++__|----~    ~`---,              ___" << endl;
			cout << "-~--~                   ~---__|,--~'                  ~~----_____-~'   `~----~~ " << endl;
			system("pause");

			system("cls");
			cout << "\n*Elena turns over to you* \nElena: Can you believe we made it?\nWe are finally going to find what most people have spent their entire lives looking for! \nSomething hidden away so meticulously by Marco Polo.\nWhat is behind this door will change our lives forever. " << endl;
			cout << "\nShall we? " << endl;
			system("pause");

			//ENTER DIAMOND ART : https://www.asciiart.eu/miscellaneous/diamonds
			system("cls");
			cout << "\n*She opens the door and you both lay your eyes on the Lost City of Gold. \n\"Divine\" you murmur under your breath. \nElena: Don't gasp yet. This City of Gold isnt even why we came all this way. \n*She points at the light shining out of the stack* What lies there is the Cursed Emerald of La LLorona that will bring our every desire to life! \n*She goes and opens the stack.* \nIt's majestic!" << endl;
			cout << "              v " << endl;
			cout << "       \             / " << endl;
			cout << "          _________ " << endl;
			cout << " `       /        \\      ' " << endl;
			cout << "        /  \      /\\ " << endl;
			cout << "       /            \\ " << endl;
			cout << "_     /   _ _ . _ _  \\    _ " << endl;
			cout << "     \\               / " << endl;
			cout << "      \\             / " << endl;
			cout << "       \\  /      \ / " << endl;
			cout << " '      \\_________/      ` " << endl;
			cout << " " << endl;
			cout << " " << endl;
			cout << "       /             \ " << endl;
			cout << "              ^ " << endl;
			system("pause");

			//ENTER WITCH ART : https://asciiart.website/index.php?art=creatures/fairies
			system("cls");
			cout << "*As she holds up the Cursed Emerald of La Llorona, its light dims the shine of the City of Gold, and darkness dawns upon it.\nElena: What just happened? \n*A witch appears with wings of gold, fair skin, and black hair* \nThe Witch: How Dare Ye Cross The Threshold Of Our Holy City! \nNow You Shall Face The Mighty Wrath Leading To Your Ultimate Demise" << endl;
			cout << "       _                           _ " << endl;
			cout << "      / `._        \+O+/        _.' \\ " << endl;
			cout << "     ( @ : `.      //`\\      .' : @ ) " << endl;
			cout << "      \  `.  `.   ((a a))   .'  .'  / " << endl;
			cout << "       \;' `.  `.((( - ))).'  .' `;/ " << endl;
			cout << "        \`.  `.  ((()=()))  .'  .'/ " << endl;
			cout << "         ) :-._`/`(('Y'))`\\'_.-: ( " << endl;
			cout << "         (`..../ /(_ * _)\\ \\....') " << endl;
			cout << "          >---/ /  )   (  \\ \\---< " << endl;
			cout << "         / .'.\ \_/\\_//\_/ /.'. \\ " << endl;
			cout << "         |o _.-\/_) '*' (_\/-._ o| " << endl;
			cout << "         |`'   ;/         \\;   `'| " << endl;
			cout << "         '.o_.-/           \\ - ._o.' " << endl;
			cout << "           '._/             \\_.'" << endl;
			cout << "             /               \\ " << endl;
			cout << "            /                 \\ " << endl;
			cout << "           /                   \\ " << endl;
			cout << "          /                     \\ " << endl;
			cout << "         /                       \\ " << endl;
			cout << "         `----....._____.....----' " << endl;

			cout << "\n*The witch strikes Elena and she faints and falls to the ground.* \n*She is now coming toward you* \nPrepare to attack. " << endl;
			system("pause");

			//the fight scene is now triggered
			isFighting = true;
			hideDialg = false;
			while (isFighting) 
			{
				system("cls");
				cout << "*Elena exclaims* Watch out! She's coming for you!" << endl;
				Bar(*drake);
				system("cls");
				if (result != "" && hideDialg == false) 
				{
					cout << result << endl;
				}
				EnemyBar(*enemy);

				// facade design pattern allows the entire to be carried out through this function
				result = battleLoc->startFight(*fight);

				//result of the game
				if (drake->getHP() <= 30) 
				{
					Bar(*drake);
					cout << "*Drake falls to the ground in his injured state* \nThe witch is about to strike one last time until she exclaims in pain! \nAAAAAAAAAAAAAAAAAAAAAAA \nA dagger went through her abdomen attacked by Elena \nThe Witch: This City will bring you no good fortune. \nThe Witch: You shall meet the same end as me" << endl;
					isFighting = false;
					system("pause");
					system("cls");
				}
				else if (enemy->getHP() <= 30) 
				{
					system("cls");
					cout << "*Drake falls to the ground in his injured state and Elena rushes over to his side to hold him* \nElena: You did it! You killed that witch! \nElena: I\'m so proud of you! \nElena: You are okay, you will be okay. I will stitch you up and you will be good as new.  " << endl;
					Bar(*drake);
					system("pause");
					system("cls");
					isFighting = false;
				}
			}

			//fight scene is over
			//cutscene
			system("cls");
			cout << "Elena: Oh good, you're up. I was so worried! \n*Softly kisses your head.* \nElena: Not much has happened since you fainted except that we're sinking. \nElena: This whole place is falling down and we have to run... \nElena: NOW \n*earthquakes* Elena: We\'re running out of time" << endl;
			system("pause");

			system("cls");
			//cout ASCII GATE ART: https://www.asciiart.eu/buildings-and-places/fences
			cout << "                                 {} {} " << endl;
			cout << "                         !  !  ! II II !  !  ! " << endl;
			cout << "                      !  I__I__I_II II_I__I__I  ! " << endl;
			cout << "                      I_/|__|__|_|| ||_|__|__|\_I " << endl;
			cout << "                   ! /|_/|  |  | || || |  |  |\_|\ !        " << endl;
			cout << "       .--.        I//|  |  |  | || || |  |  |  |\\I        .--. " << endl;
			cout << "      /-   \    ! /|/ |  |  |  | || || |  |  |  | \|\ !    /=   \ " << endl;
			cout << "      \=__ /    I//|  |  |  |  | || || |  |  |  |  |\\I    \-__ / " << endl;
			cout << "       }  {  ! /|/ |  |  |  |  | || || |  |  |  |  | \|\ !  }  { " << endl;
			cout << "      {____} I//|  |  |  |  |  | || || |  |  |  |  |  |\\I {____} " << endl;
			cout << "_!__!__|= |=/|/ |  |  |  |  |  | || || |  |  |  |  |  | \|\=|  |__!__!_ " << endl;
			cout << "_I__I__|  ||/|__|__|__|__|__|__|_|| ||_|__|__|__|__|__|__|\||- |__I__I_ " << endl;
			cout << "-|--|--|- ||-|--|--|--|--|--|--|-|| ||-|--|--|--|--|--|--|-||= |--|--|- " << endl;
			cout << " |  |  |  || |  |  |  |  |  |  | || || |  |  |  |  |  |  | ||  |  |  | " << endl;
			cout << " |  |  |= || |  |  |  |  |  |  | || || |  |  |  |  |  |  | ||= |  |  | " << endl;
			cout << " |  |  |- || |  |  |  |  |  |  | || || |  |  |  |  |  |  | ||= |  |  | " << endl;
			cout << " |  |  |- || |  |  |  |  |  |  | || || |  |  |  |  |  |  | ||- |  |  |  " << endl;
			cout << "_|__|__|  ||_|__|__|__|__|__|__|_|| ||_|__|__|__|__|__|__|_||  |__|__|_ " << endl;
			cout << "-|--|--|= ||-|--|--|--|--|--|--|-|| ||-|--|--|--|--|--|--|-||- |--|--|- " << endl;
			cout << "-|--|--|| |  |  |  |  |  |  | || || |  |  |  |  |  |  | ||= |  |  |  " << endl;
			cout << "~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^~~~~~~~~~~~ " << endl;

			cout << "\n* She helps you get up and runs to the big door * Elena: This is our only exit. \n*She tries to open it* Elena: It is too heavy. Help me open it. \n*The door doesn\'t budge* Elena: Damn it! It\'s locked. \nElena: It\'s too big to climb over and you are injured. We need to find the key. \nElena: It must be here somewhere. \nI will go search in the right corridor and you search in the left corridor. \nElena: Let's hurry.Go, go, GO!" << endl;
			system("pause");
			system("cls");

			//interactive part of the game starts again
			while (true) 
			{
				key_down = _getch();
				while (drake->getStatus() == true && drake->getIfStrength() == true) 
				{
					while (*iteratorSngl != iteratorSngl->end()) 
					{
						Statuses checkEffect = *(*iteratorSngl);
						checkEffect.affectDrake(*drake);
						(*iteratorSngl)++;
					}
					if (*iteratorSngl == iteratorSngl->end()) 
					{
						Statuses checkEffect = *(*iteratorSngl);
						checkEffect.affectDrake(*drake);
						SinglyLinkedList<Statuses>* singly_ptr = dynamic_cast<SinglyLinkedList<Statuses>*>(iteratorSngl);
						singly_ptr->setIterPointer(noises);
					}

					if (drake->getHP() <= 0) 
					{
						drake->setStatus(false);
					}

					if (drake->getStrength() <= 0) 
					{
						drake->setIfStrength(false);
					}

					if (drake->getStatus() == false || drake->getIfStrength() == false) 
					{
						break;
					}

					//the scene where Drake looks for keys in the corridor starts now
				corridorScene:
					Bar(*drake);
					Object* objPtr = &drake->objectCarrying();
					Command();
					key_down = _getch();

					//He is infront of the gate
					if (mainLoc->getAccess() == true) 
					{
						switch (key_down) 
						{
						case 78: case 110:
							// tries to unlock the door by keys from collection
							if (drake->objectCarrying().getName() == "Metal key") 
							{
								cout << mainLoc->getMaterialsDesc(1).c_str() << endl;
								system("pause");
								cout << "The gate opened!" << endl;
								system("pause");
								system("cls");
								mainLoc->setAccess(false);
								cout << "You yell to call for Elena and run out the gate with her \nThe entire city of gold turns to dust infront of your eyes \nYou: We got out just in time huh?\n Elena: Yeah \nYou: Pity we didnt get our treasure \nElena: Yes, a pity. Except... that opal that I didnt leave behind. *You both exclaim in joy* " << endl;
								lastScene = true;
								goto gameStart;
							}
							//the door is still locked
							else 
							{
								cout << "This is not the right key to the gate. I should keep trying. " << endl;
								system("pause");
								system("cls");
							}
							break;
							//door leads to the key room
						case 83: case 115:
							cout << mainLoc->getMaterialsDesc(0).c_str() << endl;
							system("pause");
							system("cls");
							keyLoc->setAccess(true);
							mainLoc->setAccess(false);
							continue;
							//the location of a ring
						case 69: case 101:
							system("cls");
							Bar(*drake);
							dbly_ptr->setDoublyPtr(drake->getFirstObject());
							if (drake->checkObject(*itr_Dbly, *ring)) 
							{
								cout << "I must keep the ring with me. It might be worth something.\n " << endl;

							}
							else 
							{
								cout << "This ring looks magnificient " << endl;
								drake->addObject(*ring);
								system("pause");
								system("cls");
								Bar(*drake);
							}
							//the noise node is triggered
							if (noises.object.getStatus() == false) 
							{

								cout << mainLoc->getMaterialsDesc(2).c_str() << endl;
								Bar(*drake);
								cout << "There are voices screaming in my head. IT'S THE RING I MUST REMOVE IT " << endl;
								noises.object.StatusChange();
								system("pause");
								system("cls");
								continue;
							}
							else 
							{
								cout << "It is best if I take off the ring and keep it safe with myself" << endl;
								noises.object.StatusChange();
								system("pause");
								system("cls");
								continue;
							}
							break;

							//door leads to ring room
						case 87: case 119:
							cout << mainLoc->getMaterialsDesc(3).c_str() << endl;

							system("pause");
							system("cls");

							ringLoc->setAccess(true);
							mainLoc->setAccess(false);
							continue;

							//collection displayed
						case 67: case 99:
							system("cls");
							drake->showCollection(*itr_Dbly);
							continue;

							//invalid command entered by the used
						default:
							system("cls");
							InvalidOption();
							goto corridorScene;
						}
					}

					//enters the ringroom
					if (ringLoc->getAccess() == true) 
					{
						switch (key_down) 
						{
						case 78: case 110:
							//gets bitten by an insect
							if (injury.object.getStatus() == false) 
							{
								cout << ringLoc->getMaterialsDesc(2).c_str() << endl;
								system("pause");
								system("cls");
								Bar(*drake);
								cout << "Ring Loc" << endl;
								//injury node is triggered
								injury.object.StatusChange();
								cout << "It's a deadly insect that bit me and now I am injured due to its bite! " << endl;
							}
							else 
							{
								cout << "Ring Loc" << endl;
								cout << "I need to stay wary of these insects " << endl;
								system("pause");
								system("cls");
								continue;
							}
							break;

							//picks up healing potion
						case 83: case 115: 
						{
							cout << ringLoc->getMaterialsDesc(1).c_str() << endl;
							Bar(*drake);
							dbly_ptr->setDoublyPtr(drake->getFirstObject());
							if (drake->checkObject(*itr_Dbly, *healingPotion)) 
							{
								cout << "I got my healing potion from here " << endl;
							}
							else 
							{
								cout << "A healing Potion! Just what I needed right now! " << endl;
								drake->addObject(*healingPotion);
							}
							system("pause");
							system("cls");
						}
							   continue;
							   //door leads to main location
						case 69: case 101: 
						{
							cout << ringLoc->getMaterialsDesc(0).c_str() << endl;
							ringLoc->setAccess(false);
							mainLoc->setAccess(true);
						}
							   continue;

							   //ground shakes
						case 87: case 119: 
						{
							system("cls");
							Bar(*drake);
							cout << ringLoc->getMaterialsDesc(3).c_str() << endl;
							system("pause");
						}
							   //collection displayed
							   continue;
						case 67: case 99:
							system("cls");
							drake->showCollection(*itr_Dbly);
							break;

							//invalid command entered by user
						default:
							system("cls");
							InvalidOption();
							goto corridorScene;
						}
					}

					// drake goes to the key room
					if (keyLoc->getAccess() == true) 
					{

						switch (key_down) 
						{
						case 78: case 110:
							//finds a stack of keys
							//gets keys one by one
							//the keys are added to the collection
							cout << keyLoc->getMaterialsDesc(2).c_str() << endl;
							Bar(*drake);
							if (Objectstack.ifNull() == false) {
								if (Objectstack.stackReturn() == *metalKey) 
								{
									drake->addObject(*metalKey);
									Objectstack.stackCount();
									objPtr->setStatus(true);
									drake->addObject(*metalKey);
									cout << "I got a metal key!" << endl;

								}
								else if (Objectstack.stackReturn() == *marbleKey)
								{
									cout << keyLoc->getMaterialsDesc(2).c_str() << endl;
									drake->addObject(*marbleKey);
									Objectstack.stackCount();
									objPtr->setStatus(true);
									cout << "I got a marble key!" << endl;

								}
								else if (Objectstack.stackReturn() == *steelKey)
								{
									cout << keyLoc->getMaterialsDesc(2).c_str() << endl;
									drake->addObject(*steelKey);
									Objectstack.stackCount();
									objPtr->setStatus(true);
									cout << "I got a steel key!" << endl;
								}
								else if (Objectstack.stackReturn() == *ironKey)
								{
									cout << keyLoc->getMaterialsDesc(2).c_str() << endl;
									drake->addObject(*ironKey);
									Objectstack.stackCount();
									objPtr->setStatus(true);
									cout << "I got a iron key!" << endl;
								}

							}
							else 
							{
								cout << "I have taken all keys from the stack of keys on the wall.\n\0" << endl;
							}

							system("pause");
							system("cls");
							continue;

						case 83: case 115: 
						{
							//finds bandages
							//added to collection
							system("cls");
							Bar(*drake);
							cout << ringLoc->getMaterialsDesc(1).c_str() << endl;
							dbly_ptr->setDoublyPtr(drake->getFirstObject());
							if (drake->checkObject(*itr_Dbly, *bandage)) 
							{
								if (injury.object.getStatus() == true) 
								{
									injury.object.StatusChange();
								}
								else 
								{
									cout << "I dont need any bandages at the moment\n " << endl;
								}
							}
							else 
							{
								cout << "This is so valuable for stopping injuries and cuts " << endl;
								drake->addObject(*bandage);
								injury.object.StatusChange();
							}
						}
							   continue;

							   //door leads to main location
						case 69: case 101:
							cout << keyLoc->getMaterialsDesc(0).c_str() << endl;
							keyLoc->setAccess(false);
							mainLoc->setAccess(true);
							continue;

							//ground shakes
						case 87: case 119:
							cout << keyLoc->getMaterialsDesc(3).c_str() << endl;
							system("pause");
							system("cls");
							continue;

							//display collection
						case 67: case 99:
							system("cls");
							drake->showCollection(*itr_Dbly);

							break;

							// invalid command entered by user
						default:
							system("cls");
							InvalidOption();
							goto corridorScene;
						}

					}
				}

				//game ends
				//values are reset to default
				if (drake->getIfStrength() == false || drake->getStatus() == false || lastScene == true) 
				{
					system("cls");
					cout << "The game ended" << endl;

					delete drake;
					delete enemy;
					delete itr_Dbly;
					delete fight;

					injury.object.setStatus(false);

					noises.object.setStatus(false);
					injury.object.setStatus(false);

					mainLoc->setAccess(true);
					ringLoc->setAccess(false);
					keyLoc->setAccess(false);
					battleLoc->setAccess(false);
					goto gameStart;

				}
			}
			//last screen
		case 66: case 98: 
		{
			system("cls");
			cout << "The end" << endl;
			gameOn = false;
		}
			break;

			   //invalid command entered by user
		default:
			system("cls");
			InvalidOption();

		}
	}
	return 0;
}
