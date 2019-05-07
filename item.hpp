#include <iostream>
#include <vector>


class Item{

	public:
		Item();
		int getId();
		std::string getItemName();
		std::string getItemPickupAction();
		std::string getItemDescription(); 
		bool weapon();
		bool healing();
		bool key();
		bool strangeMaterial();
		int getUses();
		void init(int itemId, std::string itemName, std::string itemPickupAction, std::string itemDescription, bool isWeapon, bool isHealing, bool isKey, bool isStrangeMaterial, int uses); 

	private:
		int itemId;
		std::string itemDescription; 
		std::string itemPickupAction;	
		std::string itemName;
		bool isWeapon;
		bool isHealing;
		bool isKey;
		bool isStrangeMaterial;
		bool uses;
};
