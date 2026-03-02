#include <iostream>
#include <bits/stdc++.h>
using namespace std;

    struct Node{ 
        //create a node links of size 26 , beacuse the 26 alphabetes 
        Node * links[26] = { nullptr}; //this will store the nodes

        bool flag = false;

        bool containKey(char ch ){
            return links[ch -'a'] != nullptr;
        }

        Node* getNode(char ch){
            return links[ ch - 'a'];
        }

        void put( char ch , Node * node){
            links[ch - 'a'] = node;
        }

        void setEnd(){
            flag = true;    
        }

        bool isEnd(){
            return flag;
        }
    };
class Trie {
    Node* root;
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node * node = root;
        for(char ch : word){
            if(!node->containKey(ch)){ //check that ch is present in the links or not 
                node->put(ch , new Node()); //put the character in the new node which is created 
            }
            node  = node->getNode(ch);//move to that new node 
        }
        //mark the end of the word 
        node->setEnd();
    }
    
    bool search(string word) {
        Node * node =  root;
        for( char ch : word){
            if( !node->containKey(ch)) return false;

            node = node->getNode(ch);
        }
        return node->isEnd(); 
    }
    
    bool startsWith(string prefix) {
        Node * node = root;
        for(char ch : prefix){
            if( !node->containKey(ch)) return false;

            ///move to next key 
            node = node->getNode(ch);
        }
        //prefix found 
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main(){
        Trie* obj = new Trie();
        obj->insert("apple");
        bool param_2 = obj->search("apple");
        bool param_3 = obj->startsWith("app");
    
        cout<<param_2<<" "<<param_3<<endl;
    return 0;
}