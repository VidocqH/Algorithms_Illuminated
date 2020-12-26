// https://medium.com/@aozturk/simple-hash-map-hash-table-implementation-in-c-931965904250

#define TABLE_SIZE 640000

template<typename K, typename V>
class HashNode{
    private:
        K key;
        V value;
        HashNode* next;
    public:
        HashNode(const K &key, const V &value):key(key), value(value), next(NULL){}
        K getKey() const {return key;}
        V getValue() const {return value;}
        void setValue(V value) {HashNode::value = value;}
        HashNode* getNext() const {return next;}
        HashNode setNext(HashNode* next) {HashNode::next = next;}
};

// hash function, hash modular by K
template<typename K>
struct KeyHash{
    unsigned long operator()(const K& key) const{
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

// TODO: Remove function
template<typename K, typename V, typename F = KeyHash<K>>
class HashMap{
    private:
        HashNode<K, V>** table;
        F hashFunc;
    public:
        HashMap() {table = new HashNode<K, V>*[TABLE_SIZE]();}
        ~HashMap(){
            for (int i=0;i<TABLE_SIZE;i++){
                HashNode<K, V>* n = table[i];
                while (table[i]!=NULL){
                    HashNode* prev = n;
                    n = n->getNext();
                    delete prev;
                }
                table[i]=NULL;
            }
            delete[] table;
        }
        bool get(K &key, V &value){
            unsigned long hashValue = hashFunc(key);
            HashNode<K, V>* n = table[hashValue];
            while (n!=NULL){
                if (n->getKey() == key){
                    value = n->getValue();
                    return true;
                }
                n = n->getNext();
            }
            return false;
        }
        void put(K &key, V &value){
            unsigned long hashValue = hashFunc(key);
            HashNode<K, V>* prev = NULL;
            HashNode<K, V>* n = table[hashValue];
            while (n != NULL && n->getKey() != key){
                prev = n;
                n = n->getNext();
            }
            if (n == NULL){
                n = new HashNode<K, V>(key, value);
                if (prev == NULL) table[hashValue] = n; // the first element of hash table
                else prev->setNext(n);
            }else{
                n->setValue(value); // node exists, just update value
            }
        }
};