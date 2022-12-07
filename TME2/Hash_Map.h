#include "hash_noeud.h"

template<typename K, typename D>
class hash_map{

    unsigned long hashKey(K key){
        return key%tableSize;
    } 
    
    hash_map(){
        tableSize = 30;
    }

    hash_map(int size){
        tableSize = size;
    }

    ~hash_map()
    {
        for (size_t i = 0; i < tableSize; ++i) {
            hash_noeud<K, D> *noeud = table[i];

            while (noeud != NULL) {
                hash_noeud<K, D> *prev = noeud;
                noeud = noeud->getNext();
                delete prev;
            }

            table[i] = NULL;
        }
        delete[] table;
    }

    bool get(const K &key, D &data){
        unsigned long hash = hashKey(key);
        hash_noeud<K,D> * noeud = table[hash];
        while(noeud != NULL){
            if(noeud.getKey == key){
                data = noeud.getData;
                return true;
            }
            noeud = noeud.getNext;
        }
        return false;
    }

    void put(const K &key, D &data){
        unsigned long hash = hashKey(key);
        hash_noeud<K,D> * noeud = table[hash];

        while (noeud != NULL && noeud->getKey() != key) {
            noeud = noeud->getNext();
        }

        if(noeud == NULL){
            hash_noeud<K,D> * newNoeud = new hash_noeud<K, D>(key, data);
            if(noeud->getBack() == NULL){
                table[hash] = newNoeud;
            }
            else{
                newNoeud->setBack(noeud.getBack);
            }
        } else{
            noeud->setData(data);
        }
    }

    private:
        int tableSize;
        hash_noeud<K, D> * table[];
        
            
};