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
				if(a == temp -> key)
					return get_size(temp -> left) + k;
				else if(a < temp -> key) 
					temp = temp -> left;
				else{
					k += get_size(temp -> left) + 1;
					temp = temp -> right;
				}
			}
			return -1;
		}
		
		T at(int i){
			try{
				if(i > size())throw 1;
				
				int ii = i;
				std::shared_ptr<Node> temp = tree;
				while(true){
					int left_size = get_size(temp) - get_size(temp -> right) - 1;
					if(ii == left_size)
						return temp -> _key;
					if(ii < left_size)
						temp = temp -> left;
					else {
						ii -= left_size + 1;
						temp = temp -> right;
					}
				}
			}
			catch(int thr){
				std::cout << "Error: " << thr;
			}	
		}
		
		Treap<T> new_Treap(int pos){
			Treap<T> new_tree;
			for(int i = 0; i < pos; i++)
				new_tree.insert(add(i));
			return new_tree;
		}
		
		template <typename T1>
		void insert(T1&& new_T){
        	add(tree, new_T);
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
			Node(T& key, int prior = rand()%(1000000 + 1)): _key(key), _size(1), 
			right(nullptr), left(nullptr), _prior(prior){ }
		};
		
		std::shared_ptr <Node> make_node(T& _key) const{
			return std::make_shared<Node>(_key);
		}
		
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
    		
    		if(t1 -> _prior > t2 -> _prior){
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
			std::shared_ptr<Node> t1;
			std::shared_ptr<Node> t2;
			split(t, key, t1, t2);
			std::shared_ptr<Node> temp_node = make_node(key);
			std::shared_ptr<Node> temp = merge(t1, temp_node);
			t = merge(temp, t2);
		}
		
		void print(std::shared_ptr<Node>& t){
			if(t != nullptr){
				print(t -> left);
				std:: cout << t -> key << " ";
				print(t -> right);
			}
		}
};
