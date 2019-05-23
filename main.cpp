#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

template <class K,class V>
//creez o clasa pentru nod
class Node
{
private:
    V value;
    K key;
    Node *next;
public:
    void SetKey(K x);
    void SetValue(V y);
    void SetNext(Node *x);
    Node *GetNext();
    V GetValue();
    K GetKey();
};
template <class K,class V>
void Node<K,V>::SetKey(K x)
 {
     key=x;
 }
template <class K,class V>
void Node<K,V>::SetValue(V y)
 {
     value=y;
 }
 template <class K,class V>
V Node<K,V>::GetValue()
{
    return value;
}
template <class K,class V>
K Node<K,V>::GetKey()
{
    return key;
}
template <class K,class V>
void Node<K,V>::SetNext(Node *x)
{
    this->next=x;
}
template <class K,class V>
Node<K,V> *Node<K,V>::GetNext()
{
    return this->next;
}


template <class K,class V>

//calsa pentru lista
class List
{
private:
    Node<K,V> *first;
    Node<K,V> *last;
    int Capacity;
    size_t Size;
public:
    List();
    void AddNode(K key,V value);
    void SearchNode(K key,V value);
    void DeleteNode(V value);
    void SlotsAvailable();
   // void PrintList();
    Node<K,V> *GetFirst();
    int GetSize();
    template <class U,class W>
    friend ostream & operator <<(ostream &out,const List<U,W> &H);

};
template <class K,class V>
List<K,V>::List()
{
    Capacity=20;
    Size=0;
}
template <class K,class V>
void List<K,V>::AddNode(K key,V value)
 {
     if(Size==0)
     {
         first=last=new Node<K,V>;
         first->SetKey(key);
         first->SetValue(value);
         first->SetNext(last);
         Size++;
     }
     else
     {
         if(Size+1>Capacity)
         {
             cout<<"Not enought space";
             throw ".";
         }
         Node<K,V> *CurrentNode;
         CurrentNode=last;
         last=new Node<K,V>;
         last->SetKey(key);
         last->SetValue(value);
         CurrentNode->SetNext(last);
         Size++;
     }
 }
 template <class K,class V>
 void List<K,V>::SearchNode(K x,V y)
 {
     Node<K,V> *temp=first;
     int i=0;
     bool gasit=false;
     while(i<Size)
     {
         if((temp->GetValue()==y)&&(temp->GetKey()==x))
            {
                cout<<"\nElementul cautat se afla pe pozitia "<<i<<" in lista ";
                gasit=true;
                break;
            }
         i++;
         temp->SetNext(temp->GetNext());
     }
     if(gasit==false)
     {
         cout<<"Nu am putut gasi elementul\n";
         throw ".";
     }

 }
template <class K,class V>
void List<K,V>::DeleteNode(V value)
{

    Node<K,V> *temp=first;
    if(first->GetValue()==value)
    {

        first=first->GetNext();
        delete []temp;
        Size--;
    }
    else
    {
     Node<K,V> *temp2=first->GetNext();
     int index=0;
    while(index<Size)
    {
        if(temp2->GetValue()==value)
         break;
        else
         {
             temp=temp2;
             if(temp2->GetNext()!=NULL)
             {
                temp2=temp2->GetNext();
             }
         }
      index++;
      if(index>=Size)
      {
          cout<<"Element not found";
          throw ".";
      }
    }
    temp->SetNext(temp2->GetNext());
    Size--;
    delete []temp2;
    }
}
template <class K,class V>
int List<K,V>::GetSize()
{
    return Size;
}
template <class K,class V>
Node<K,V> *List<K,V>::GetFirst()
{
    return first;
}
template <class K,class V>
void List<K,V>::SlotsAvailable()
{
    cout<<"List have "<<Capacity-Size<<" slots\n";
}
/*template <class K,class V>
void List<K,V>::PrintList()
{
    int index=0;
    Node<K,V> *temp=first;
    while(index<Size)
    {
        cout<<"Element: "<<index<<" Key: "<<temp->GetKey()<<" Value: "<<temp->GetValue()<<"\n";
        temp=temp->GetNext();
        index++;
    }

}*/
template <class K,class V>
ostream &operator << (ostream &out,const List<K,V> &H)
{
    int index=0;
    Node<K,V> *temp=H.first;
    while(index<H.Size)
    {
        out<<"Element: "<<index<<" Key: "<<temp->GetKey()<<" Value: "<<temp->GetValue()<<"\n";
        temp=temp->GetNext();
        index++;
    }
    return out;
}


//functie pentru a genera o cheie
template <class K>
struct  HashKey
{
    unsigned  long  operator ()  ( const K &key )
const{
    return  reinterpret_cast<unsigned  long> (key) % 100;
    }
};
template <class K,class V,class F=HashKey<K> >

class HashMap
{
private:
    const size_t TableSize=100;
    List<K,V> *arr;
    F HashKeyFunc;
    vector<int> AllKeys;
public:
    HashMap();
    V operator[](K i);
    vector<V> ElementsForKey(K x);
    void Add(K x, V y);
    void Delete(K x,V y);
    void Search(K x,V y);
    int NrOfKeys();
    template <class U,class L,class W>
    friend ostream& operator <<(ostream &out,const HashMap<U,L,W> &H);


};
template <class K,class V,class F>
HashMap<K,V,F>::HashMap()
{
    arr=new List<K,V>[TableSize];
}
template <class K,class V,class F>
void HashMap<K,V,F>::Add(K x,V y)
{
    arr[HashKeyFunc(x)].AddNode(x,y);
    if(find(AllKeys.begin(),AllKeys.end(),HashKeyFunc(x))==AllKeys.end())
        AllKeys.push_back(HashKeyFunc(x));
}
template <class K,class V,class F>
void HashMap<K,V,F>::Delete(K x,V y)
{
    arr[HashKeyFunc(x)].DeleteNode(y);
}
template <class K,class V,class F>
void HashMap<K,V,F>::Search(K x,V y)
{
   arr[HashKeyFunc(x)].SearchNode(x,y);
   cout<<" si pe pozitia "<<HashKeyFunc(x)<<" in vector\n";
}
template <class K,class V,class F>
int HashMap<K,V,F>::NrOfKeys()
{
    return AllKeys.size();
}
template <class K,class V,class F>
vector<V> HashMap<K,V,F>::ElementsForKey(K x)
{
   vector<V> KeyVector;
   Node<K,V> *f=arr[HashKeyFunc(x)].GetFirst();
   size_t Size=arr[HashKeyFunc(x)].GetSize();
   int i=0;
   while(i<Size)
   {
       KeyVector.push_back(f->GetValue());
       f=f->GetNext();
       i++;
   }
   return KeyVector;
}
template <class K,class V,class F>
V HashMap<K,V,F>:: operator [](K i)
{
    return arr[HashKeyFunc(i)].GetFirst()->GetValue();
}
template <class K,class V,class F>
ostream &operator << (ostream &out,const HashMap<K,V,F> &H)
{
    for(int i=0;i<H.AllKeys.size();i++)
    {
        List<K,V>  o= H.arr[H.AllKeys[i]];
        out<<"Pozitia in vector : "<<H.AllKeys[i]<<"\n";
        out<<o<<" ";
        out<<'\n';
    }
    return out;
}

struct IntKeyHash {
    unsigned long operator()(const int& k) const
    {
        return k % 100;
    }
};
int main()
{
    // Verificare charuri
    HashMap<char*,char*> h;
    h.Add("Anglia","Londra");
    h.Add("Anglia","Manchester");
    h.Add("Anglia","Liverpool");
    h.Add("Spania","Madrid");
    h.Add("Spania","Barcelona");
    h.Add("Romania","Bucuresti");
    h.Add("Romania","Targu-Jiu");
    h.Add("Italia","Roma");
    vector<char*> v;
    v=h.ElementsForKey("Anglia");
    for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << " ";
        }
    cout<<"\n";
    h.Delete("Anglia","Manchester");
    v=h.ElementsForKey("Anglia");
    for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << " ";
        }
    h.Search("Romania","Bucuresti");
    cout<<h["Spania"]<<"\n";
    cout<<"\n";
    cout<<h;
    // Verificare cheie int
    HashMap<int,char*,IntKeyHash> h2;
    h2.Add(10,"a");
    h2.Add(10,"bc");
    h2.Add(14,"tr");
    h2.Add(15,"kg");
    vector<char*> v2;
    v2=h2.ElementsForKey(10);
    for (int i = 0; i < v2.size(); i++)
        {
            cout << v2[i] << " ";
        }
    cout<<"\n";
    h2.Delete(10,"a");
    v2=h2.ElementsForKey(10);
    for (int i = 0; i < v2.size(); i++)
        {
            cout << v2[i] << " ";
        }
   h2.Search(15,"kg");
   cout<<h2[14];
   cout<<"\n";
   cout<<h2<<" ";
    return 0;
}
