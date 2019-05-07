#include <iostream>
#include <vector>


class Room{

	public:
		Room();
		std::string getRoomDescription(); 
		void init(std::string roomDescription, int hasMonster, std::string monsterDescription, int northRoomId, int southRoomId, int eastRoomId, int westRoomId); 
		void addItem(int itemId);
		std::vector<int> getItemIds();

		bool monsterInRoom();
		void removeMonster();
		std::string getMonsterDescription();


		void unlockNorth();
		void unlockSouth();
		void unlockEast();
		void unlockWest();

		int moveNorth(); 
		int moveSouth(); 
		int moveEast(); 
		int moveWest(); 

	private:
		std::string description; 	
		std::vector<int> itemIds;
		std::string monsterDescription;
		bool hasMonster;

		int northRoomId; 
		int southRoomId; 
		int eastRoomId; 
		int westRoomId;

};
