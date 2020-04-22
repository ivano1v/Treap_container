#pragma once
#include <iostream>
#include <memory>

template <class T>

class Treap{
	public:
		Treap(){
			tree = nullptr;
		}
		
		int size(){
			return get_size(tree);
		}
		
		int search(const T& a){
			int k = 0;
			std::shared_ptr<Node> temp = tree;
			while(temp != nullptr){
				if(a == temp -> _key)
					return get_size(temp -> left) + k;
				else if(a < temp -> _key) 
					temp = temp -> left;
				else{
					k += get_size(temp -> left) + 1;
					temp = temp -> right;
				}
			}
			return -1;
		}
		
		T at(int i){
			if(i > size())
				throw std::out_of_range("Treap: index is out of range");	
			std::shared_ptr<Node> temp = tree;
			return get_k(temp, i);
		}
		
		Treap<T> new_Treap(int pos){
			Treap<T> new_tree;
			for(int i = 0; i < pos; i++)
				new_tree.emplace(at(i));
			return new_tree;
		}
		
		void print(){
			Print(tree);
		}
		
		void insert(T a){
        	add(tree, a);
   		}
   		template <class... Args>
	    void emplace(Args...args){
	        insert(T(args...));
	    }
	    
	private:
		class Node;
		std::shared_ptr<Node>tree;
		class Node{
			public:
			T _key;
			int _size;
			int _prior;   
			std::shared_ptr<Node>left;
			std::shared_ptr<Node>right;
			Node(T& key, int prior = rand()): _key(key), _size(1), 
			right(nullptr), left(nullptr), _prior(prior){ }
		};
		
		int get_size(std::shared_ptr<Node>& node) const{
			if(node == nullptr)return 0;
			return node -> _size;
		}
		
		void update(std::shared_ptr<Node>& node) const{
			if(node == nullptr)return ;
			node -> _size = 1 + get_size(node -> left) + get_size(node -> right); 
		}
		
		std::shared_ptr<Node> merge(std::shared_ptr<Node>& t1, std::shared_ptr<Node>& t2){
			if (t1 == nullptr) { return t2; }
    		if (t2 == nullptr) { return t1; }
    		
    		if(t1 -> _prior < t2 -> _prior){
    			t1 -> right = merge(t1 -> right, t2);
    			update(t1);
    			return t1;
			}
			else{
				t2 -> left =  merge(t1, t2 -> left);
				update(t2);
				return t2;
			}
		}
		
		void split(std::shared_ptr<Node>& t, T& key,
		std::shared_ptr<Node>& t1, std::shared_ptr<Node>& t2){
			if(t == nullptr){
				t1 = t2 = nullptr;
				return;
			}
			if(t -> _key < key){
				
				split(t -> right, key, t -> right, t2);
				t1 = t;
			}
			else{
				split(t -> left, key, t1, t -> left);
				t2 = t;
			}
			update(t);
		}
		
		void add(std::shared_ptr<Node>& t, T& key){
			std::shared_ptr<Node> t1, t2;
			split(t, key, t1, t2);
			std::shared_ptr<Node> new_tree = std::make_shared<Node>(key);
			std::shared_ptr<Node> temp = merge(t1, new_tree);
			t = merge(temp, t2);
		}
		
		void Print(std::shared_ptr<Node>& t){
			if(t != nullptr){
				Print(t -> left);
				std::cout << t -> _key << " ";
				Print(t -> right);
			}
		}
		
		T get_k(std::shared_ptr<Node>& t, int k){
    		if (k < get_size(t -> left)){
        		return get_k(t -> left, k);
   			 }
    		else if (k == get_size(t -> left)){
        		return t -> _key;
    		}
    		else{
       		 return get_k( t-> right, k - get_size(t -> left) - 1);
   			}
		}
};
