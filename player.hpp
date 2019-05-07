#include <iostream>
#include <vector>
#include <string>


class Player{

	public:
		Player();
		Player(std::string name);
		void init(std::string playerName, std::vector<int>& inventory);
		void setName(std::string name);
		void addItem(int itemId);
	    bool hurtPlayer();
		bool healPlayer();	
		int useItem(std::string item);
		std::vector<int> getInventory();
		std::string getName(); 
	private:
		std::string playerName;
		std::vector<int> inventory;
		bool isHurt;
};
