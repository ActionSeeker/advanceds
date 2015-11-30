#include<iostream>
using namespace std;
class stack{
    typedef struct node{
    int data;
    node* next;
    }node;
    node* head;
    node* tail;
    node* createNewNode(int d)
    {
        node* temp = new node;
        temp->data = d;
        temp->next = NULL;
        return temp;
    }
public:
    stack()
    {
        head = NULL;
        tail = NULL;
    }
    void push(int x)
    {
        node* temp = createNewNode(x);
        if (head == NULL && tail == NULL)
        {
            head = tail = temp;
        }
        else
        {
            //insert from tail
            tail->next = temp;
            tail = temp;
        }
    }
    node* pop()
    {
        node* last = tail;
        if(tail == NULL)
            cout<<"Undeflow";
        else
        {
            node* it = head;
            while(it->next!= tail)
                it = it->next;
            tail = it;
            tail->next = NULL;
        }
        return last;
    }
    void print()
    {
        node*it = head;
        while(it)
        {
            cout<<it->data<<" ";
            it = it->next;
        }
        cout<<endl;
    }
};
int main()
{
    stack S;
    S.push(10);
    S.push(20);
    S.push(30);
    S.push(40);
    S.print();
    S.pop();
    S.print();
    S.pop();
    S.print();
    return 0;
}
