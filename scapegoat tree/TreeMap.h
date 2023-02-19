#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "ScapegoatTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    bool pop(const K &key);

    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &floorEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();

    void pollLastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.


private: // DO NOT CHANGE THIS PART.
    ScapegoatTree<KeyValuePair<K, V> > stree;
};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    /* TODO */
    stree.removeAllNodes();
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    /* TODO */
    KeyValuePair<K, V> element = KeyValuePair<K,V>(key);
    return (stree.get(element)).getValue();
}

template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) {
    /* TODO */
    
    return stree.remove(KeyValuePair<K, V>(key));
    
}

template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) {
    /* TODO */
    KeyValuePair<K, V> element = KeyValuePair<K, V>(key, value);
    return stree.insert(element);
    
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    /* TODO */
    KeyValuePair<K, V> element = KeyValuePair<K,V>(key);
    return stree.getCeiling(element);
    
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) {
    /* TODO */
    KeyValuePair<K, V> element = KeyValuePair<K,V>(key);
    return stree.getFloor(element);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    /* TODO */
    return stree.getMin();
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    /* TODO */
    return stree.getMax();
}

template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() {
    /* TODO */
    KeyValuePair<K, V> element = stree.getMin();
    stree.remove(element);
}

template<class K, class V>
void TreeMap<K, V>::pollLastEntry() {
    /* TODO */
    KeyValuePair<K, V> element = stree.getMax();
    stree.remove(element);
}

template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const {
std::vector<KeyValuePair<K,V> > temp;
KeyValuePair<K, V> element = KeyValuePair<K,V>(fromKey,(stree.get(fromKey)).getValue());
KeyValuePair<K, V> element2 = KeyValuePair<K,V>(toKey,(stree.get(toKey)).getValue());

temp.push_back(element);
//std::cout<<element2.getKey();

while(element != toKey){
    element = stree.getNext(element.getKey());
    temp.push_back(element);
 
}
if(element != element2)
    temp.push_back(element2);
return temp;
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# ScapegoatTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

#endif //TREEMAP_H
