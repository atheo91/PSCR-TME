#include "hash_noeud.h"

template<typename K, typename D, size_t tableSize>
class hash_map{

    public:
    unsigned long hashKey(K key){
        return stoi(key) % tableSize;
    } 
    
    hash_map(){
        int i = 0;
        while(i< tableSize){
            table[i] = new hash_noeud<K,D>(NULL, NULL);
            i++;
        }
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
    }

    bool get(const K &key, D &data){
        unsigned long hash = hashKey(key);
        hash_noeud<K,D> * noeud = table[hash];
        while(noeud != NULL){
            if(noeud->getKey() == key){
                data = noeud->getData();
                return true;
            }
            noeud = noeud->getNext();
        }
        return false;
    }

    void put(const K &key, const D &data){
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
                newNoeud->setBack(noeud->getBack());
            }
        } else{
            noeud->setData(data);
        }
    }

    private:
        hash_noeud<K, D> * table[tableSize];
};