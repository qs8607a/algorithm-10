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
		Trie<T> left;
		Trie<T> right;
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
			if(value[depth] == '0'){
				loop->left.k = new Node<T>();
				loop = loop->left.k;
			}
			else {
				loop->right.k = new Node<T>();
				loop = loop->right.k;
			}
			depth++;	
		}
		if(leafkey[depth] == '0'){
			loop->left.k = holdon->k;
			loop->right.k = new Node<T>(value);
		}
		else {
			loop->right.k = holdon->k;
			loop->left.k = new Node<T>(value);			
		}
		holdon->k = start;
	}
}
 
template<typename T>
Trie<T> * Trie<T>::search(T value, int & depth){
	Trie<T> * current = this;
	while(current->k != 0 && !current->k->isleaf){
		if(value[depth] == '0')
			current = &current->k->left;
		else 
			current = &current->k->right;
		depth++;
	}
	return current;
}
 
template<typename T>
void Trie<T>::inorder(){
	if(k!=0){
		k->left.inorder();
		if(k->isleaf)
			std::cout << k->key << ", ";
		k->right.inorder();
	}
}
 
int main(){
	Trie<std::string> start;
	start.add("1000");
	start.add("011000");
	start.add("111110000");
	start.add("0001");
	start.inorder();
	return 0;
}