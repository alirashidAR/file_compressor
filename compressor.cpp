#include<fstream>
#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<unordered_map>

using namespace std;



struct Node {
    char ch;                 
    int freq;                   
    Node *left, *right;      

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(char c, int f, Node * left, Node * right) : ch(c), freq(f), left(left), right(right){}
};

struct Compare{
   bool operator()(Node * left, Node* right){
      return left->freq>right->freq;
   }
};


Node * buildHuffmanTree(const unordered_map<char,int> freq){
   priority_queue<Node*, vector<Node*>, Compare> minHeap;
   
   for (const auto& pair : freq) {
        minHeap.push(new Node(pair.first, pair.second));
    }

   while(minHeap.size()>1)
   {
      Node * left = minHeap.top(); minHeap.pop();
      Node * right =  minHeap.top(); minHeap.pop();

      int val =  left->freq+right->freq;

      minHeap.push(new Node('*',val,left,right));
   }

   return minHeap.top();
}

void generateHuffmanCodes(Node * root,const string &str, unordered_map<char, string> & hoffmanCode){
   if(!root){
      return;
   }

   if(!root->left && !root->right){
      hoffmanCode[root->ch] =  str;
   }

   generateHuffmanCodes(root->left,str+"0",hoffmanCode);
   generateHuffmanCodes(root->right,str+"1",hoffmanCode);
}


int main() {
    
   unordered_map<char, int> mp = {{'A', 2}, {'B', 3}, {'C', 450}, {'D', 12}};
   unordered_map<char,string> codes;
   string str = "";

   Node *root = buildHuffmanTree(mp);
   generateHuffmanCodes(root,str,codes);

   for(const auto &pair:codes)
   {
      cout<<pair.first<<":"<<pair.second;
      cout<<endl;
   }

   cout<< root->freq;


    return 0;
}