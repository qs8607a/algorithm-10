#ifndef __2DTree
#define __2DTree
#include <cstdlib>
#include <iostream>
#include <queue>
using std::ostream;

/******************

	2DTree
	by cedricve.me
	
	Class: BinTree with BinNodes
   
***************************************************************************/

template <class TypeKey,class TypeData>
class BinNode;

template <class TypeKey,class TypeData>
class BinTree{
public:
    BinTree<TypeKey,TypeData>():k(0){}
    ~BinTree<TypeKey,TypeData>(){
        delete k;
    }
    
	int depth() const{
        if (k==0)
            return 0;
        else
            return max(k->left.depth(),k->right.depth())+1;
    };

    void write(ostream&) const;
    void write(ostream& os,BinNode<TypeKey,TypeData>* kn) const{
        if (kn!=0)
            os<<"("<<kn->key<<","<<kn->data<<")";
        else
            os<<"(,)";
    }
     BinNode<TypeKey,TypeData>* k;
};



template <class TypeKey,class TypeData>
class BinNode{
    public:
        TypeKey key;
        TypeData data;
		bool isX;
        BinTree<TypeKey,TypeData> left,right;
        BinNode(){}
        BinNode(const TypeKey& _key,const TypeData& _data, const bool _isX):key(_key),data(_data),isX(_isX){}
};

/**********************************************************************

   Class: K2DTree (BinTree => BinSearchTree(smaller,left:bigger,right) => 2KDTree(check on x or y coordinate))
   
***************************************************************************/

template <class TypeKey,class TypeData>
class K2DTree{
public:
     virtual void add(const TypeKey&, const TypeData&);
	 virtual void findNearestPoint(const TypeKey&);
	 virtual void findNearestHelper(const TypeKey&,int&,TypeKey&,BinTree<TypeKey,TypeData>&,int&);
     virtual void searchPosition(const TypeKey&,BinTree<TypeKey,TypeData>*&, bool&);
	 int depth() const{return theTree.depth();};
     friend ostream& operator<<(ostream& os,K2DTree<TypeKey,TypeData>& b){
        b.theTree.write(os);
        return os;
    };
protected:
     BinTree<TypeKey,TypeData> theTree;
};

template <class TypeKey,class TypeData>
void K2DTree<TypeKey,TypeData>::searchPosition(const TypeKey& key,BinTree<TypeKey,TypeData>*& position, bool& isX){
    position=&theTree;
	// Bij root vergelijken we met x
    isX = true;
    while (position->k!=0){
		bool left;
		// als x
		if(isX)
			left = (key.x < position->k->key.x);
		// als y
		else 
			left = (key.y < position->k->key.y);

		if(left)
			// go left
			position = &(position->k->left);
		else 
			// go right
			position = &(position->k->right);

		isX = !isX;
    }
}
        

template <class TypeKey,class TypeData>
void K2DTree<TypeKey,TypeData>::add(const TypeKey& key, const TypeData& data){
    BinTree<TypeKey,TypeData>* position;
	bool isX;
    searchPosition(key,position,isX);
    if (position->k == 0)
        position->k=new BinNode<TypeKey,TypeData>(key,data,isX);
}

template <class TypeKey,class TypeData>
void K2DTree<TypeKey,TypeData>::findNearestPoint(const TypeKey& key){
	int currentBest = 99999999;
	int count = 0;
	TypeKey currentbestpoint;
	findNearestHelper(key,currentBest,currentbestpoint,theTree, count);
	std::cout << "Distance: " << currentBest << " Node: " << key << " TargetNode: " << currentbestpoint << " Searched through " << count << " nodes." << std::endl;
}

template <class TypeKey,class TypeData>
void K2DTree<TypeKey,TypeData>::findNearestHelper(const TypeKey& key,int & currentbest, TypeKey & currentbestpoint, BinTree<TypeKey,TypeData> & position, int & count){
	if(position.k!=0){
		
		// check if on x or y level
		count++;
		bool isX = position.k->isX;
		
		bool left;
		if(isX)
			left = (key.x < position.k->key.x);
		else 
			left = (key.y < position.k->key.y);
		
		// Go left or right	
		if(left)
			findNearestHelper(key,currentbest,currentbestpoint,position.k->left,count);
		else 
			findNearestHelper(key,currentbest,currentbestpoint,position.k->right,count);
		
		// Calculate if better
		int intermezo;
		if(currentbest >= (intermezo=key.quadraticdistance(position.k->key))){
			currentbest = intermezo;
			currentbestpoint.set(position.k->key.x,position.k->key.y);
		}
		
		// When going back from recursion check if
		// there is a better distance in the other tree
		int distance_points;

		// Going to the other tree, from coming
		BinTree<TypeKey,TypeData> * direction;
		if(left)
			direction = &position.k->right;
		else
			direction = &position.k->left;
		
		// Check if on x or y level
		if(isX)
			distance_points = (key.x-position.k->key.x)*(key.x-position.k->key.x);
		else
			distance_points = (key.y-position.k->key.y)*(key.y-position.k->key.y);
		
		// If better start new recursion			
		if(distance_points < currentbest)
			findNearestHelper(key,currentbest,currentbestpoint,*direction,count);
		
	}
}


template <class TypeKey,class TypeData>
void BinTree<TypeKey,TypeData>::write(ostream& os) const{
    if (k!=0){
       std::queue<BinNode<TypeKey,TypeData>*, std::deque<BinNode<TypeKey,TypeData>*> > q;
       q.push(k);
       while(!q.empty()){
           BinNode<TypeKey,TypeData>* nu=q.front();
           write(os,nu);
           os<<" left: ";
           write(os,nu->left.k);
           os<<" right: ";
           write(os,nu->right.k);
           os<<std::endl;
           if (nu->left.k!=0)
               q.push(nu->left.k);
           if (nu->right.k!=0)
               q.push(nu->right.k);
           q.pop();
       }
    }
    else{
        write(os,k);
    }
}

#endif

