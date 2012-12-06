#include <iostream>
#include <string>
#include <map>
#include <ctype.h>
#include <bitset>

//---------------------------------------------
//
//
//	Patricia Trie by cedricve.me
//
//
//---------------------------------------------

/*

	Char to byte convertor

*/
class byte {
public:
	std::string getByte(char);
	int alpha_index(char);
};

std::string byte::getByte(char c) {
	int alpha = alpha_index(tolower(c));
	std::bitset<5> mybits = std::bitset<5>(alpha);
	return mybits.to_string<char,std::char_traits<char>,std::allocator<char> >();
}

int byte::alpha_index(char c) {
	return c - 'a' + 1;
}

/*

	Patricia Trie
	
*/

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
		void inorder(std::map<std::string,std::string> &, int);
		Node<T> * k;
};


template<typename T>
class PatriciaTrieRoot {
	public:
		PatriciaTrieRoot():start(0),extra(0){};
		void add(T);
		PatriciaTrie<T> * search(T);
		PatriciaTrie<T> * search(T, int&);
		void inorder(std::map<std::string,std::string> &);
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

template<typename T>
void PatriciaTrieRoot<T>::inorder(std::map<std::string,std::string> & keys){
	int i = 0;
	start->inorder(keys,i);
}

template<typename T>
void PatriciaTrie<T>::inorder(std::map<std::string,std::string> & keys, int i){
	if(k!=0 && ( i < k->getIndex() ||  k->getIndex() == 0) ){
		k->left.inorder(keys,k->getIndex());
		std::cout << keys[k->getKey()];
		k->right.inorder(keys,k->getIndex());
	}
}

/*


Run

*/
int main(){
	PatriciaTrieRoot<std::string> start;
	std::map<std::string,std::string> keys;
	
	byte b;
	keys[b.getByte('a')] = "a";
	keys[b.getByte('s')] = "s";
	keys[b.getByte('e')] = "e";
	keys[b.getByte('z')] = "z";
	keys[b.getByte('q')] = "q";

	start.add(b.getByte('a'));
	start.add(b.getByte('s'));
	start.add(b.getByte('e'));
	start.add(b.getByte('z'));
	start.add(b.getByte('q'));

	start.inorder(keys);
	
	return 0;
}