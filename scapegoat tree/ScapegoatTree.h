#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    
    int helperSize(Node<T> *node) const
    {
        if(node == NULL) return 0;
        int leftSize = helperSize(node->left);
        int rightSize = helperSize(node->right);
        return leftSize + rightSize + 1;
    }
    
    int helperHeight(Node<T> *node) const
    {
        if (node == NULL) return 0;
        else {
            int lDepth = helperHeight(node->left);
            int rDepth = helperHeight(node->right);
      
            if (lDepth > rDepth)
                return (lDepth + 1);
            else
                return (rDepth + 1);
        }
        
    }
    
    bool ifExists(Node<T> *node, T value) const{
        if (node == NULL)
            return false;
        else {
            if (node->element == value)
                return true;
            else if (node->element > value)
                return ifExists(node->left,value);
            else if(node->element < value)
                return ifExists(node->right,value);
        }
    }
    
    Node<T>* returnNode(Node<T> *node, T value) const{
        if (node == NULL)
            return NULL;
        else {
            if (node->element == value)
                return node;
            else if (node->element > value)
                return returnNode(node->left,value);
            else if(node->element < value)
                return returnNode(node->right,value);
        }
    }
    
    void helperDel(Node<T> *&node) {
        if(node == NULL) return;
    
        helperDel(node->left);
        helperDel(node->right);
        delete node;
        node=NULL;
    }
    
    
   
     void helperInsert(Node<T> *&root, T element)
    {
        if(root == NULL)
        {
            root = new Node<T>();
            root -> element = element;
        }
        else if(element < root->element)
        {
            helperInsert(root->left,element);
        }
        else
        {
            helperInsert(root->right,element);
        }
       
    }
    
    Node<T>* returnMinNode(Node<T> *node) const
    {
        Node<T>* temp = node;
        while(temp && temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
        
    }
    Node<T>* returnMaxNode(Node<T> *node) const
    {
        Node<T>* temp = node;
        while(temp && temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp;
    }
    
    void helperRemove(Node<T> *& node, T value) {
        if (node == NULL)
            return;
        else if (node->element> value)
            helperRemove(node->left, value);
        else if (node->element < value)
            helperRemove(node->right , value);
        else    
            if (node->left !=NULL && node->right != NULL) {
                node->element = returnMaxNode(node->left)->element;
                helperRemove(node->left, node->element);
            }
            else {
                Node<T> * temp =node;  
                if(node->left !=NULL) 
                    node = node->left;
                else
                    node = node->right;
                
                delete temp;
                temp = NULL;
            }
    }
    
    /*Node<T>* helperRemove(Node<T> *node, T element)
    {
        if(node == NULL) return root;
        else if(node->element > element)
        {
            node->left = helperRemove(node->left,element);
        }
        else if(element > node->element)
        {
            node->right = helperRemove(node->right,element);
        }
        else
        {
            if(node->right == NULL && node ->left == NULL)
            {
                delete node;
                return NULL;
            }
            else if(node->right == NULL)
            {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }
            else if(node->left == NULL)
            {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            }
            else
            {
                Node<T>* temp = returnMaxNode(node->left);
                node->element = temp->element;
                node->left = helperRemove(node->left, temp->element);
            }
        }
        return node;
    }*/
    
      T helperMin(Node<T>* node) {
        if(node == NULL) return -1;
        else if(node->left == NULL) {
            return node->element;
        } 
            return helperMin(node->left);
    }
   
    void helperCopy(Node<T> *& n1, Node<T> *n2){
        if(n2!=NULL){
            n1=new Node<T>();
            n1->element = n2->element;
            helperCopy(n1->left,n2->left);
            helperCopy(n1->right,n2->right);
        }
        else{
		 n1 = NULL;
	  }		
    }
    
    void arrayConstructor(Node<T>* node, T *&arr,int &n){
        if(node != NULL){
            arrayConstructor(node->left,arr,n);
            arr[n] = node->element;
            n++;
            arrayConstructor(node->right,arr,n);
            
        }
    }
    
    void helperBalanced(Node<T>*&root, T*&arr, int start,int end){
    if (start > end) return;
 
    int mid = (start + end)/2;
    root = new Node<T>();
    root ->element = arr[mid];
 
    helperBalanced(root->left,arr, start, mid - 1);
 
    helperBalanced(root->right,arr, mid + 1, end);
 
    }
    
    T helperCeil(Node<T>* node,T num) const
    {
        int ceilVal = -1;
        while(node){
            if(node->element == num){
                ceilVal = node->element;
                return ceilVal;
            }
            else if(node->element>num){
                ceilVal = node->element;
                node = node->left;
            }
            else if(node->element<num){
                node = node -> right;
            }
            
        }
        return ceilVal;
    }
    Node<T>* helperCeilNode(Node<T>* node,T num) const
    {
        Node<T>* temp = node;
        Node<T>* temp2 = NULL;
        while(temp){
            if(temp->element == num){
                return temp;
            }
            else if(temp->element>num){
                temp2 = temp;
                temp = temp->left;
            }
            else if(temp->element<num){
                temp = temp -> right;
                if(temp == NULL && temp2 ==NULL) return NULL;
            }
        }
        return temp2;
    }
    Node<T>* helperFloorNode(Node<T>* node,T num) const
    {
        Node<T>* temp = node;
        Node<T>* temp2 = NULL;
        while(temp){
            if(temp->element == num){
                return temp;
            }
            else if(temp->element<num){
                temp2 = temp;
                temp = temp->right;
            }
            else if(temp->element>num){
                temp = temp -> left;
                if(temp == NULL && temp2 ==NULL) return NULL;
            }
        }
        return temp2;
    }
  
    
    Node<T>* helperNext(Node<T>* node,T num) const{
        
        Node<T>* temp = node;
        Node<T>* temp2 = NULL;
        while(temp){
            if(temp->element == num){
                temp = temp ->right;
            }
            else if(temp->element>num){
                temp2 = temp;
                temp = temp->left;
            }
            else if(temp->element<num){
                temp = temp -> right;
                if(temp == NULL && temp2 ==NULL) return NULL;
            }
        }
        return temp2;
        
    }
    
    Node<T>* helperParent(Node<T>* node,T element){
    if(node == NULL) return NULL;
    Node<T>* temp = NULL;
    
    while(node != NULL){
        if(node->element>element){
            temp = node;
            node = node->left;
        }
        else if(node->element<element){
            temp = node;
            node = node->right;
        }
        else
            break;
        
    }
    return temp;
    }
    
    
    Node<T>* helperScapeGoat(Node<T>* node){
        Node<T>* temp = node;
        while(!(3*helperSize(node)>2*helperSize(helperParent(root,node->element)))){
            node = helperParent(root,node->element);
        }
        temp = helperParent(root,node->element);
        return temp;
    }
    
    Node<T>* helperBalanced2(Node<T>* node){
        int m = helperSize(node);
        int i = 0;
        T *helperArr = new T[m];
        int n = 0;
        arrayConstructor(node,helperArr,n);
        n--; m--;
        helperDel(node);
        helperBalanced(node,helperArr,i,m);
        delete [] helperArr;
        return node;
    }
    void helperConstructor(Node<T> *node){
        Node<T>* parent = helperParent(root,node->element);
        /*if(parent->left == NULL){
             parent->right = helperBalanced2(node);
        }
        else if(parent->right == NULL){
            parent->left = helperBalanced2(node);
        }*/
        if(parent->right == node){
            parent ->right =helperBalanced2(node);
        }
        else if(parent->left == node){
            parent ->left =helperBalanced2(node);
        }
    }


private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    /* TODO */
    root = NULL;
    upperBound = 0; //yeni
    
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    /* TODO */
    if(obj.root == NULL)
    {
        root = NULL;
        upperBound = 0;
    }
    helperCopy(root,obj.root);
    upperBound = obj.upperBound;
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    /* TODO */
    this->removeAllNodes();
    upperBound = 0;
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    /* TODO */
    if(root == NULL) return true;
    return false;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    /* TODO */
    if(root == NULL) return -1;
    else
        return helperHeight(root)-1;
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    /* TODO */
    return helperSize(root);
    
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    /* TODO */
    if(ifExists(root,element)) return false;
    else
    {
        helperInsert(root,element);
        upperBound++;
        
        if(getHeight() > log2(upperBound)/log2(1.5) ){
            Node<T>* scapeGoat = helperScapeGoat(returnNode(root,element));
            helperConstructor(scapeGoat);
        }
        return true;
    }
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    if(ifExists(root,element))
    {
        helperRemove(root,element);
        if(getSize() == 0){
            root = NULL;
            upperBound = 0;
            return true;
        }
        if(upperBound>2*getSize()){
            balance();
            upperBound = getSize();
        }
        else if(getSize() > upperBound){
            balance();
            upperBound = getSize();
        }
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    /* TODO */
    helperDel(root);
    upperBound = 0;
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    // TODO 
    if(ifExists(root,element))
    {
        return returnNode(root,element)->element ;
    }
    else
    {
        throw NoSuchItemException();
    }
    
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        }
        
        else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        }  
        else if (tp == postorder) {
            /* TODO */
            if (isEmpty()) {
                // the tree is empty.
                std::cout << "BST_postorder{}" << std::endl;
                return;
            }
            std::cout << "BST_postorder{" << std::endl;
            print(root, tp);
            std::cout << std::endl << "}" << std::endl;
            
        }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        // TODO 
        if(node == NULL)
        {
            return;
            
        }
        std::cout << "\t" << node -> element;
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        
    } else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;
    
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    else if (tp == postorder) {
        // TODO 
        if(node == NULL)
        {
            return;
        }
        
        print(node->left,postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    /* TODO */
    if(root == rhs.root) return *this;
    else
    {
        helperCopy(root,rhs.root);
        upperBound = rhs.upperBound;
        return *this;
    }
}

template<class T>
void ScapegoatTree<T>::balance() {
    int m = getSize();
    int i = 0;
    T *helperArr = new T[m];
    int n = 0;
    arrayConstructor(root, helperArr,n);
    n--; m--;//yeni ekledim
    int temp = upperBound;
    removeAllNodes();
    upperBound = temp;
    helperBalanced(root,helperArr,i,m);
    
    delete [] helperArr;
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    /* TODO */
    Node<T>*node = root;
  if(helperCeilNode(node,element) == NULL) throw NoSuchItemException();
  else
    return helperCeilNode(node,element)->element;
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    /* TODO */
    Node<T>*node = root;
  if(helperFloorNode(node,element) == NULL) throw NoSuchItemException();
  else
    return helperFloorNode(node,element)->element;
    
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
        Node<T>* node = returnMinNode(root);
        if(node == NULL) throw NoSuchItemException();
        else
            return node->element;
}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    /* TODO */
    Node<T>* node = returnMaxNode(root);
    if(node == NULL)
        throw NoSuchItemException();
    else
        return node ->element;
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    /* TODO */
    Node<T>* node = root;
    if(helperNext(node,element) == NULL) 
        throw NoSuchItemException();

    else
        return helperNext(node,element)->element;
}