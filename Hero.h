#pragma once
#include <iostream>

class Hero{
	public:
		Hero(int hp = 100, int lvl = 1, std::string name= "default Hero"):
		_hp(hp), _lvl(lvl),_name(name){ }
		friend  bool operator <(const Hero& one, const Hero& two){
			return one._lvl < two._lvl;
		}
		friend  bool operator==(const Hero& one, const Hero& two) {
   			return (one._lvl == two._lvl && one._name == two._name && one._hp == two._hp);
		}	
		friend std::ostream& operator<< (std::ostream &out, const Hero& one){
			out << one._name << " " << one._lvl << " " << one._hp << std::endl;
		}
			
	private:
		int _hp;
		int _lvl;
		std::string _name;
};
