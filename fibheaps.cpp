#include<bits/stdc++.h>
using namespace std;
class fibHeaps{
    typedef struct node{
        int data;
        node* childList;
        node* left;
        node* right;
        node* parent;
        int degree;
        bool mark;
    }node;
    node* MIN;
    node* ROOT;
    int H;
    node* makeNode(int x)
    {
        node* t = new node;
        t->data = x;
        t->left = NULL;
        t->right = NULL;
        t->childList = NULL;
        t->parent = NULL;
        t->degree = 0;
        t->mark = false;
        return t;
    }
    void fibHeaps_insert_deep(node* x)
    {
        if(this->MIN == NULL)
        {
            this->MIN = x;
            this->ROOT = x;
            this->ROOT->left = ROOT;
            this->ROOT->right = ROOT;
        }
        else
        {
            node* LAST = ROOT->left;
            x->right = ROOT;
            ROOT->left = x;
            LAST->right = x;
            x->left = LAST;
            ROOT = x;
            //inserted as a doubly linked list
            //now check if this could be the new min
            if(x->data < this->MIN->data)
            {
                this->MIN = x;
            }
        }
        this->H = this->H+1;
    }
    vector<node*> A;
public:
    fibHeaps()
    {
        this->MIN = NULL;
        this->H = 0;
        this->ROOT = NULL;
        for(int i = 0;i<10;i++)//for 100th degree only shall it work
        {
            A.push_back(NULL);
        }
    }
    void fibHeaps_insert(int data)
    {
        node* x = makeNode(data);
        fibHeaps_insert_deep(x);
    }
    fibHeaps fibHeaps_union(fibHeaps *H2)
    {
        //concatenate H2 to this
        node* lastOfThis = ROOT->left;
        node* lastOfH2 = H2->ROOT->left;
        lastOfThis->right = H2->ROOT;
        H2->ROOT->left = lastOfThis;
        lastOfH2->right = this->ROOT;
        this->ROOT->left = lastOfH2;
        if(H2->MIN->data < this->MIN->data)
            this->MIN = H2->MIN;
        this->H += H2->H;
        delete H2;
    }
    int fibHeaps_extractMin()
    {
        node* z = this->MIN;
        int k = z->data;
        if(z!=NULL)
        {
            node* chit = z->childList;
            if(chit)
            {
                do
                {
                    this->fibHeaps_insert(chit->data);//insert to the root list
                    chit->parent = NULL;
                    chit = chit->right;
                }
                while(chit!=z->childList);
            }
            //remove z from the list

            if(z == ROOT)
            {
                ROOT = z->right;
            }

            node* leftOfz = z->left;
            node* rightOfz = z->right;

            leftOfz->right = rightOfz;
            rightOfz->left = leftOfz;

            print_rootList();

            if(z == z->right)
            {
                this->MIN = NULL;
            }
            else
            {
                this->MIN = z->right;
                consolidate();
            }
            this->H--;

            delete z;
            return k;
        }
        cout<<"This heap is empty!";
        return 0;
    }
    void consolidate()
    {
        node* w = ROOT;
        for(int i = 0;i<10;i++)
            A[i] = NULL;
        do
        {
            node* x = w;
            int d = x->degree;
            while(A[d]!=NULL)
            {
                node* y = A[d];
                if(y->data < x->data)
                {
                    node* temp = x;
                    x = y;
                    y = temp;
                    if(y == ROOT)
                    {
                        ROOT = x;
                    }
                }
                fibHeaps_link(x,y);
                A[d] = NULL;
                d = d+1;
            }
            A[d] = x;
            cout<<"X has "<<A[d]->data<<endl;
            w = w->right;
        }while(w!=ROOT);

        ROOT = NULL;
        this->MIN = NULL;

        for(int i = 0;i<10;i++)
        {
            if(A[i])
            {
                A[i]->degree = i;
                if(this->MIN == NULL)
                {
                    this->fibHeaps_insert_deep(A[i]);
                }
                else
                {
                    this->fibHeaps_insert_deep(A[i]);
                    if(A[i]->data <= this->MIN->data)
                        this->MIN = A[i];
                }
            }
        }

    }
    void printA()
    {
        int k = A.size();
        for(int i = 0;i<k;i++)
        {
            if(A[i])cout<<A[i]->data<<" ";
            else cout<<"- ";
        }
        cout<<endl;
        for(int i = 0;i<k;i++)
        {
            if(A[i])cout<<A[i]->degree<<" ";
            else cout<<"  ";
        }
        cout<<endl;
    }
    void fibHeaps_link(node* parent, node* child)
    {
        node* leftOfChild = child->left;
        node* rightOfChild = child->right;
        leftOfChild->right = rightOfChild;
        rightOfChild->left = leftOfChild;

        child->left = NULL;
        child->right = NULL;

        fibHeaps_attachChild(parent,child);
    }
    void fibHeaps_attachChild(node* parent, node* tobe_child)
    {
        node* tempHEAD = parent->childList;
        node* child = new node;
        child->left = child;
        child->right = child;
        child->data = tobe_child->data;
        if(tempHEAD == NULL)
        {
            tempHEAD = child;
            child->left = child;
            child->right = child;
        }
        else
        {
            node* lastInRow = tempHEAD->left;
            child->left = lastInRow;
            child->right = tempHEAD;
            tempHEAD->left = child;
            lastInRow->right = child;
            tempHEAD = child;
        }
        parent->childList = tempHEAD;
        child->mark = false;
        delete tobe_child;
        parent->degree++;
    }
    void print_rootList()
    {
        node* begin = ROOT;
        do
        {
            cout<<begin->data<<" ";
            /*if(begin->childList)
            {
                node* u = begin->childList;
                do
                {
                    cout<<u->data<<" ";
                    if(u->childList)
                    {
                        cout<<"((This has more children) "<<u->childList->data<<" "<<")";
                    }
                    u = u->right;
                }while(u!=begin->childList);
            }*/
            begin = begin->right;
        }while(begin!=ROOT);
        cout<<endl;
    }
    int printMin()
    {
        return this->MIN->data;
    }
    int printSize()
    {
        return this->H;
    }
    int returnROOT()
    {
        return ROOT->data;
    }
};
int main()
{
    fibHeaps* H1 = new fibHeaps();
    fibHeaps* H2 = new fibHeaps();

    H1->fibHeaps_insert(4);
    H1->fibHeaps_insert(10);
    H1->fibHeaps_insert(15);
    H1->fibHeaps_insert(24);
    H1->fibHeaps_insert(3);
    H1->fibHeaps_insert(-100);

    cout<<"Original list ";
    H1->print_rootList();
    cout<<endl;

    //H1->fibHeaps_union(H2);

    H1->fibHeaps_extractMin();//<<" \n";

    H1->print_rootList();

    return 0;
}
