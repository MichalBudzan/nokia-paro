#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;



class EmptyListError : public std::runtime_error
{
public :
	EmptyListError(std::string msg) :
           runtime_error(msg)
	{}
};



class NotFoundError : public std::runtime_error
{
public :
	NotFoundError(std::string msg) :
           runtime_error(msg)
	{}
};




template <typename Typ>
class Node
{
public:
    Node(const Typ v) :
        next(nullptr),
	prev(nullptr),
        value(v)
    {}


  
    std::shared_ptr<Node<Typ>> next;
    std::shared_ptr<Node<Typ>> prev;
    Typ value;

   
};



template <typename Typ>
class List
{
public:
    List();
    
    void add(shared_ptr<Node<Typ>> node);        // dodaje element na koniec listy
    shared_ptr<Node<Typ>> get(const Typ value);  // zwraca element o wskazanej wartości

private:
    shared_ptr<Node<Typ>> first;
};



template <typename Typ>
List<Typ>::List() :
	first(nullptr)
{}


template <typename Typ>
void List<Typ>::add(shared_ptr<Node<Typ>> node)
{
   if(node->next)
    {
	cerr<< "Nie można dodać ponownie tego samego węzła" << endl;
	return;	
    }
 

    if(!first)
    {
        first = node;
	node->prev=first;
    }
    else
    {
        shared_ptr<Node<Typ>> current = first;
        while(current->next)
        {
		
            current = current->next;
		
        }
       
        current->next = node;
	node->prev=current;      
	
		
    }
}


template <typename Typ>
shared_ptr<Node<Typ>> List<Typ>::get(const Typ value)
{
    if(!first)
    {
        throw EmptyListError("Lista jest pusta !");
    }
    else
    {
        shared_ptr<Node<Typ>> current = first;
        do
        {
            if(current->value == value)
            {
                cout << "Found value " << current->value << endl;
                return current;
            }
            else
            {
                cout << "Going through " << current->value << endl;
	
                     current = current->next;
            }
        } while(current);

	throw NotFoundError("Not found");
        //cout << "Not found: value " << value << endl;
	
        return nullptr;
    }
}

int main()
{
    List<string> lista;


    auto napis1 = make_shared<Node<string>>("napis");
    auto napis2 = make_shared<Node<string>>("napisik");	
    auto napis3 = make_shared<Node<string>>("tekst");	


    lista.add(napis1);
    lista.add(napis2);
    lista.add(napis3);

    
     auto node= lista.get("napisik");
	

 


    return 0;
}
