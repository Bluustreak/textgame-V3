
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
struct Item
{
	string name;
	string desc;
	string ID;
	unsigned short size; // 1=small, 2=medium, 3=large 4=showoff, 5=what are you doing?
	//unsigned short cx;
	//unsigned short cy;
};
struct Room
{
	string name;
	string desc;
	vector<Item> contents;
	unsigned short cx;
	unsigned short cy;
	void printContents()
	{
		for (int i = 0; i < contents.size(); i++)
		{
			cout << i << ". " << contents.at(i).name << endl;
		}
	}
};
struct Player
{
	string name;
	string desc;
	vector<Item> inventory;
	unsigned short cx;
	unsigned short cy;

	void printInventory()
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			cout << i << ". " << inventory.at(i).name << endl;
		}
	}
};
void initializeRooms(vector<Room>& r_vecRooms)//Rooms and their contents!
{
	Item smorgle;
	smorgle.name = "Smorgle";
	smorgle.desc = "A very good looking Smorgle. You wonder what a Smorgle is, and even how you know it is, indeed, a Smorgle.\n";
	smorgle.size = 1;

	Room tempR;

	tempR.name = "Some room";
	tempR.desc = "A very generic room";
	tempR.cx = 0;
	tempR.cy = 0;
	tempR.contents.push_back(smorgle);
	r_vecRooms.push_back(tempR);
	tempR.contents.clear();

	tempR.name = "eastroom";
	tempR.desc = "Not to be confused with 'restroom'";
	tempR.cx = 1;
	tempR.cy = 0;
	r_vecRooms.push_back(tempR);

	tempR.name = "northroom";
	tempR.desc = "yeah, I dunno what to say about this room";
	tempR.cx = 0;
	tempR.cy = 1;
	r_vecRooms.push_back(tempR);

	tempR.name = "northwestroom";
	tempR.desc = "Now we're talking, a room in two directions at once!";
	tempR.cx = 1;
	tempR.cy = 1;
	r_vecRooms.push_back(tempR);

}
bool roomExistsAt(vector<Room>& r_vecRooms, short unsigned x, short unsigned y)//checks if there is a room at x,y
{
	for (int i = 0; i < r_vecRooms.size(); i++)
	{
		//cout << "loop\n";
		if (r_vecRooms.at(i).cx == x && r_vecRooms.at(i).cy == y) return true;
	}
	return false;
}
int currentRoom(vector<Room>& r_vecRooms, unsigned short& r_playerX, unsigned short& r_playerY)
{
	for (int i = 0; i < r_vecRooms.size(); i++)
	{
		if (r_vecRooms.at(i).cx == r_playerX && r_vecRooms.at(i).cy == r_playerY) return i;
	}
}


int main()
{
	Player player;
	player.name = "Bob";
	player.desc = "Some guy somewhere, ya know?";
	player.cx = 0;
	player.cy = 0;
	unsigned short& r_playerX = player.cx;
	unsigned short& r_playerY = player.cy;											// sets the player's coords to references
	Player& r_player = player;														// makes a reference to player

	vector<Room> vecRooms;
	vector<Room>& r_vecRooms = vecRooms;
	initializeRooms(r_vecRooms);

	vector<Item>& r_playerInv = player.inventory;
	int cr;
	//----------------------------------------------------------------------------- initialization above

	string input;
	do																				// game loop
	{
		cout << "coords: (" << r_playerX << ", " << r_playerY << ")\n";
		getline(cin, input);
		cr = currentRoom(r_vecRooms, r_playerX, r_playerY);							//cr is now the current room

		{
		//-------------------------------------------------------------------- inputs in this scope, to be able to minimize it
			if (input == "w") {
				if (roomExistsAt(r_vecRooms, r_playerX - 1, r_playerY)) {
					r_playerX--;
				}
				else
					cout << "Oof, you can't go there\n";
			}
			else if (input == "e") {
				if (roomExistsAt(r_vecRooms, r_playerX + 1, r_playerY)) {
					r_playerX++;
				}
				else
					cout << "Oof, you can't go there\n";
			}
			else if (input == "s") {
				if (roomExistsAt(r_vecRooms, r_playerX, r_playerY - 1)) {
					r_playerY--;
				}
				else
					cout << "Oof, you can't go there\n";
			}
			else if (input == "n") {
				if (roomExistsAt(r_vecRooms, r_playerX, r_playerY + 1)) {
					r_playerY++;
				}
				else
					cout << "Oof, you can't go there\n";
			}

			if (input == "inv") {
				cout << "Your inventory consists of: \n";
				player.printInventory();
			}
			if (input == "look")
			{
				cout << r_vecRooms.at(cr).name << endl;
				cout << r_vecRooms.at(cr).desc << endl;
				cout << "items in this room are: \n";
				r_vecRooms.at(cr).printContents();
			}
			if (input == "investigate" || input == "i")
			{
				cout << "Items in the room: \n";
				int i = 0;															// the two forloops use the same variable, and just iterates it thorugh the sum of the two loop's iterations
				for (i; i < r_vecRooms.at(cr).contents.size(); i++)
				{
					cout << i << ". " << r_vecRooms.at(cr).contents.at(i).name << endl;
				}
				cout << "Items in your inventory: \n";
				for (i; i < r_playerInv.size(); i++)
				{
					cout << i << ". " << r_playerInv.at(i).name << endl;
				}
				cout << "which do you want to investigate?\n";
				int breakPoint = r_vecRooms.at(cr).contents.size();
				int choise;
				cin >> choise;
				if (choise < breakPoint)
				{
					cout << r_vecRooms.at(cr).contents.at(choise).desc;
				}
				else if (choise >= breakPoint)
					cout << r_playerInv.at(choise - breakPoint).desc;
				else
					break;
			}
			if (input == "take") {
				if (r_vecRooms.at(cr).contents.size() > 0)							// if the rooms is not empty on items
				{
					cout << "which item?\n";
					r_vecRooms.at(cr).printContents();

					int choise;
					cin >> choise;
					auto it = r_vecRooms.at(cr).contents.begin() + choise;			// .erase() below takes an iterator and not an int
					r_playerInv.push_back(r_vecRooms.at(cr).contents.at(choise));	// copies the item from Room to player inv
					r_vecRooms.at(cr).contents.erase(it);							// erases the item from the room
				}
			}
			if (input == "place") {
				if (r_playerInv.size() > 0) {
					cout << "which item?\n";
					player.printInventory();
					int choise;
					cin >> choise;
					auto it = player.inventory.begin() + choise;					// .erase() below takes an iterator and not an int
					r_vecRooms.at(cr).contents.push_back(r_playerInv.at(choise));	// copies item from inv to room
					r_playerInv.erase(it);											// erases the item from inv
				}
				cout << endl;
			}
			//--------------------------------------------------------------------

		}
		cout << flush;
	} while (input != "quit");
}