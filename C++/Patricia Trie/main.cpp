#include <iostream>
#include <string>
#include <map>

template<typename T>
class PatriciaTrie;

template<typename T>
class PatriciaTrieRoot;
 
template<typename T>
class Node {
	friend class PatriciaTrie<T>;
	friend class PatriciaTrieRoot<T>;
	public:
		Node(T value,int index):key(value),index(index){};
		PatriciaTrie<T> left;
		PatriciaTrie<T> right;
		T getKey(){return key;};
		int getIndex(){return index;};
	private:
		int index;
		T key;
};
 
template<typename T>
class PatriciaTrie {
	public:
		PatriciaTrie():k(0){};
		Node<T> * k;
};


template<typename T>
class PatriciaTrieRoot {
	public:
		PatriciaTrieRoot():start(0),extra(0){};
		void add(T);
		PatriciaTrie<T> * search(T);
		PatriciaTrie<T> * search(T, int&);
		PatriciaTrie<T> * start;
		Node<T> * extra;
};
 
template<typename T>
void PatriciaTrieRoot<T>::add(T value){
	PatriciaTrie<T> * current = search(value);
	if(current == 0){
		if(extra == 0)
			extra = new Node<T>(value,0);
		else if(start == 0){
			start = new PatriciaTrie<T>();
			int depth = 1;
			while(depth <= value.size() && value[depth-1] == extra->key[depth-1])
				depth++;
			start->k = new Node<T>(value,depth);
			if(value[depth-1] == '0'){
				start->k->left.k = start->k;
				start->k->right.k = extra;
			}
			else{
				start->k->right.k = start->k;
				start->k->left.k = extra;
			}
		}
	}
	else {
		int depth = 1;
		while(depth <= value.size() && value[depth-1] == current->k->key[depth-1])
			depth++;
		PatriciaTrie<T> * next = search(value,depth);
		Node<T> * newnode = new Node<T>(value,depth);
		if(value[depth-1] == '0'){
			newnode->right.k = next->k;
			next->k = newnode;
			newnode->left.k = newnode;
		}
		else{
			newnode->left.k = next->k;
			next->k = newnode;
			newnode->right.k = newnode;
		}	
	}
}
 
template<typename T>
PatriciaTrie<T> * PatriciaTrieRoot<T>::search(T value){
	PatriciaTrie<T> * next = start;
	if(start!=0){
		int prev_depth = 0;
		int next_depth = next->k->index;
		while(prev_depth < next_depth){
			if(value[next_depth-1]=='0')
				next = &next->k->left;
			else
				next = &next->k->right;
			prev_depth = next_depth;
			next_depth = next->k->index;
		}
	}
	return next;
}
 
 
template<typename T>
PatriciaTrie<T> * PatriciaTrieRoot<T>::search(T value, int & depth){
	PatriciaTrie<T> * next = start;
	if(start!=0){
		int prev_depth = 0;
		int next_depth = next->k->index;
		while(prev_depth < next_depth && depth > next_depth){
			if(value[next_depth-1]=='0')
				next = &next->k->left;
			else
				next = &next->k->right;
			prev_depth = next_depth;
			next_depth = next->k->index;
		}
	}
	return next;
}
 
int main(){
	PatriciaTrieRoot<std::string> start;
	std::map<std::string,std::string> keys;
	
	keys["00001"] = "A";
	keys["10011"] = "S";
	keys["00101"] = "E";
	keys["10010"] = "R";
	keys["00011"] = "C";
	keys["01000"] = "H";

	start.add("00001");
	start.add("10011");
	start.add("00101");
	start.add("10010");
	start.add("00011");
	start.add("01000");
	
	// Right @ Root there is R
	std::cout << keys[start.start->k->right.k->getKey()] << std::endl;
	// @ Root there is S
	std::cout << keys[start.start->k->getKey()] << std::endl;
	// Left @ Root there is H
	std::cout << keys[start.start->k->left.k->getKey()] << std::endl;
	// Left @ H there is E
	std::cout << keys[start.start->k->left.k->left.k->getKey()] << std::endl;
	// Left @ E there is C
	std::cout << keys[start.start->k->left.k->left.k->left.k->getKey()] << std::endl;
	// Left @ C there is A
	std::cout << keys[start.start->k->left.k->left.k->left.k->left.k->getKey()] << std::endl;
	return 0;
}