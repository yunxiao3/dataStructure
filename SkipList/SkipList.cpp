#include <iostream>
#include <vector>
using namespace std;  
 
#define MAXLEVEL 4 //最多2 power n=16个数   
/*skip list node,they are keys and pointers*/
classSKNode{   
public:  
    int key;                  
    SKNode* forward[MAXLEVEL];  
    SKNode(){  
        key=0;        
        for(int i =0;i<MAXLEVEL;i++) {             
            forward[i]= NULL;  
        }    
    }   
    SKNode& operator=(const SKNode* & node){  
key=node->key;  
for(inti=0;i<MAXLEVEL;i++)  
        {  
forward[i] = node->forward[i];  
        }  
return *this;  
    }  
};        
//skip list, it has a header, this header have maxlevel pointers   
classSkipList
{   
public:  
SKNode *hdr;              /* list Header */    
intlistLevel;              /* current level of list */    
int insert(int key);   
SKNode* search(int key);  
intdeleteNode(int key);  
voidprintList();  
SkipList()
    {  
hdr = new SKNode;  
listLevel = 0;  
hdr->key = -INT_MAX;  
SKNode* end = new SKNode;  
SKNode* first = new SKNode;  
first->key=-INT_MAX;  
end->key=INT_MAX;  
for(inti =0;i<MAXLEVEL;i++)  
        {     
hdr->forward[i]=first;  
hdr->forward[i]->forward[i] = end;  
        }  
printList();  
    }  
    ~SkipList()
    {  
deletehdr;  
    }  
};   
intgetInsertLevel()  
{  
intupcount = 0;  
for(inti=0;i<MAXLEVEL;i++)  
    {  
intnum = rand()%10;  
if(num<5)  
        {  
upcount++;  
        }  
    }  
returnupcount;  
}  
SKNode*  SkipList::search(int key)   
{      
SKNode* current = new SKNode;  
current = hdr;  
inti = listLevel-1;  
for(;i>=0;i--)  
    {  
while(current->forward[i]->key != INT_MAX && key>current->forward[i]->key)//key大于下一个数据的值。转到本层下一个元素  
        {  
current = current->forward[i];  
        }
        //否则i--，转到下一层
    }  
current = current->forward[0];  
if(current!= NULL && current->key == key)  
    {  
cout<<"find"<<key<<endl;  
return current;  
    }  
return NULL;  
 
}   
 
intSkipList::insert(int key)  
{  
int level = getInsertLevel();  
SKNode* node = new SKNode;  
node->key=key;  
 
SKNode *s[MAXLEVEL];  
SKNode* current = new SKNode;  
SKNode* last = new SKNode;  
for(inti =0;i<MAXLEVEL;i++)  
    {  
s[i]=hdr->forward[i];//initiation  
    }  
current = last = hdr;  
cout<<"hdr"<<hdr->key<<endl;  
inti = listLevel-1;  
for(;i>=0;i--)  
    {  
while(current->forward[i]->key != INT_MAX && key>current->forward[i]->key)//key大于下一个数据的值。转到本层下一个元素  
        {  
current = current->forward[i];  
        }  
        s[i] = current;//保存每一层位置上的最后指针的前驱  
    }  
last=current->forward[0];  
if(last != NULL && last->key == key)  
    {  
cout<<"inset key:"<<key<<"already existed"<<endl;  
return 0;  
    }  
    if(level>listLevel)//更新层数  
    {  
listLevel = level;  
    }  
 
for(int k = 0; k <listLevel;k++)  
    {  
node->forward[k]=s[k]->forward[k];  
s[k]->forward[k]=node;     
 
    }  
if(level>listLevel)  
    {  
listLevel = level;  
    }  
return 1;  
 
}  
intSkipList::deleteNode(int key)
{
SKNode *s[MAXLEVEL];
SKNode* current = new SKNode;
SKNode* last = new SKNode;
for(inti =0;i<MAXLEVEL;i++)
 {
s[i]=hdr->forward[i];//initiation
 }
current = last = hdr;
for(inti = listLevel-1;i>=0;i--)
 {
while(current->forward[i]->key != INT_MAX && key>current->forward[i]->key)//key大于下一个数据的值。转到本层下一个元素
  {
current = current->forward[i];
  }
  s[i] = current;//保存每一层位置上的最后指针的前驱
 }
last=current->forward[0];
if(last->key != key)
 {
cout<<"delete key:"<<key<<"does not existed"<<endl;
 
return 0;
 }
for(inti = 0; i<listLevel;i++)
 {
s[i]->forward[i]=s[i]->forward[i]->forward[i];
 }
return 1;
}
voidSkipList::printList()
{
    SKNode* current = hdr;
    for(inti = listLevel -1;i>=0;i--)
    {
        current = hdr->forward[i];
        cout<<"level "<<i<<"................................"<<endl;
        while(current->forward[i] != NULL)//key大于下一个数据的值。转到本层下一个元素
        {
            cout<<" "<<current->key;
            current = current->forward[i];
        }
        cout<<" "<<current->key<<endl; 
    }
}   
 
int main() 
{ 
    SkipListsk;
    constint n = 7;
    intnum[n]={30,15,45,37,11,53,17};
    cout<<"test insert............."<<endl;
    for(inti = 0;i<n;i++)
    {
        sk.insert(num[i]);
    }
    sk.printList();
    cout<<"test search............"<<endl;
    sk.search(17);
    cout<<"test delete................."<<endl;
    sk.deleteNode(30);
    sk.printList();
    system("pause");
    return 0;
}  