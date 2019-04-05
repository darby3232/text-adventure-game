#include <iostream>
#include <vector>


class Room{

	public:
		Room();
		std::string getRoomDescription(); 
		void init(std::string roomDescription, int northRoomId, int southRoomId, int eastRoomId, int westRoomId); 
		int moveNorth(); 
		int moveSouth(); 
		int moveEast(); 
		int moveWest(); 

	private:
		std::string description; 	
		std::vector<int> itemIds;


		int northRoomId; 
		int southRoomId; 
		int eastRoomId; 
		int westRoomId;

};
