#include <vector>
#include <iostream>
#include <string>
template<typename T>
class Trie;
 
template<typename T>
class Node {
	friend class Trie<T>;
	public:
		Node():isleaf(false){};
		Node(T value):key(value),isleaf(true){};
	private:
		Trie<T> table[256];
		T key;
		bool isleaf;
};
 
template<typename T>
class Trie {
	public:
		Trie():k(0){};
		void add(T);
		Trie<T> * search(T, int &);
		void inorder();
		Node<T> * k;
};
 
template<typename T>
void Trie<T>::add(T value){
	int depth = 0;
	Trie<T> * current = search(value,depth);
	if(current->k==0)
		current->k = new Node<T>(value);
	else{
		Trie<T> * holdon = current;
		T leafkey = holdon->k->key;
		Node<T> * start = new Node<T>();
		Node<T> * loop = start;
		while(depth < value.size() && leafkey[depth] == value[depth]){
			loop->table[value[depth]].k = new Node<T>();
			loop = loop->table[value[depth]].k;
			depth++;	
		}
		loop->table[value[depth]].k = new Node<T>(value);
		loop->table[leafkey[depth]].k = holdon->k;
		holdon->k = start;
	}
}
 
template<typename T>
Trie<T> * Trie<T>::search(T value, int & depth){
	Trie<T> * current = this;
	while(current->k != 0 && !current->k->isleaf){
		current = &current->k->table[value[depth]];
		depth++;
	}
	return current;
}
 
template<typename T>
void Trie<T>::inorder(){
	int count = 0;
	if(k!=0){
		for(unsigned int i = 0; i < 256; i++)
			k->table[i].inorder();
		if(k->isleaf)
			std::cout << k->key << ", ";
	}
}
 
int main(){
	Trie<std::string> start;
	start.add("ABBC");
	start.add("ABBB");
	start.add("AC");
	start.add("15");
	start.inorder();
 
	int depth = 0;
	Trie<std::string> * current = start.search("ABBB",depth);
	std::cout << std::endl << "ABBB found on depth: " << depth;
	return 0;
}