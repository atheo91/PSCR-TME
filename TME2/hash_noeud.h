template<typename K, typename D>
class hash_noeud{

    public:
        hash_noeud(K key, D data){
            this.key = key;
            this.data = data; 
            precedant = NULL;
        }

        D getData(){
            return data;
        }

        K getKey(){
            return key;
        }

        void setData(D data){
            this.data = data;
        }

        hash_noeud * getNext(){
            return suivant;
        }

        void setNext(hash_noeud * next){
            suivant = next;
        }
        
        hash_noeud * getBack(){
            return precedant;
        }

        void setBack(hash_noeud * back){
            precedant = back;
        }

    private:
        hash_noeud * precedant;
        hash_noeud * suivant;
        K key;
        D data;
};