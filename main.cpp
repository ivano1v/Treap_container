#include <iostream>

#include "Tree.h"
#include "Hero.h"

int main(){
	Treap<Hero> tree;
	tree.emplace(200, 5, "Petya");
	tree.emplace(200, 4, "Yan");
	tree.emplace(100, 3, "Kolya");
	tree.emplace(200, 2, "Alex");
	tree.emplace(88, 1, "Vlad");
	std::cout << tree.size() << std::endl;
	for(int i = 0; i < tree.size(); i++)
		std::cout << tree.at(i);
	Hero incognito(100, 3, "Kolya");
	std::cout << tree.search(incognito) << std::endl;
	std::cout << "============================="<< std::endl;
	Treap<Hero>new_teee = tree.new_Treap(3);
	for(int i = 0; i < new_teee.size(); i++)
		std::cout << new_teee.at(i);
	std::cout << new_teee.at(4) << std::endl;
}
