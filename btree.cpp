#include<bits/stdc++.h>
using namespace std;
class BTree{
    typedef struct node{
        int n;//number of kets that can be stored
        vector<int> keys;
        vector<node* > c;
        bool leaf;
    }node;
    int t; //to specify the lower and upper bound
    node* ROOT;
        void BTree_node_init(node* x)
        {
            for(int i = 0;i<=2*t-1;i++)
            {
                x->keys.push_back(INT_MIN);
                x->c.push_back(NULL);
            }
        }
        void BTree_split(node* x, int i)
        {
            //the arguments imply which child of the x has to be split
            node* z = new node;
            BTree_node_init(z);
            node* y = x->c[i];
            z->leaf = y->leaf;
            z->n = (t-1);
            for(int j = 1; j<=t-1;j++)
            {
                z->keys[j] = y->keys[j+t];
                //copy keys post the median to z
            }
            if(y->leaf == false)
            {
                //copy children post the median
                for(int j = 1;j<=t;j++)
                {
                    z->c[j] = y->c[j+t];
                }
            }
            y->n = t-1;
            for(int j = x->n+1;j>=i+1;--j)
            {
                x->c[j+1] = x->c[j];
                //copy all pointers forward from the position i
                //we will push the z in the space i+1
            }
            x->c[i+1] = z;
            for(int j = x->n;j>=i;--j)
            {
                x->keys[j+1] = x->keys[j];
                //THis loop shifts the keys of the x forward so as to push the median key here
            }
            x->keys[i] = y->keys[t];
            x->n = x->n+1;
        }

        void BTree_insert_nonfull(node* x, int k)
        {
            int i = x->n;
            if(x->leaf == true)
            {
                while(i>=1 && k<x->keys[i])
                {
                    x->keys[i+1] = x->keys[i];
                    --i;
                }
                x->keys[i+1] = k;
                x->n++;
            }
            else
            {
                while(i>=1 && k < x->keys[i])
                {
                    x->keys[i+1] = x->keys[i];
                    --i;
                }
                i = i+1;

                if(x->c[i]->n == 2*t - 1)
                {
                    BTree_split(x,i);
                    if(k>x->keys[i])
                        i++;
                }
                BTree_insert_nonfull(x->c[i],k);
            }
        }
    public:
        BTree(int t)
        {
            node* x = new node;
            x->leaf = true;
            x->n = 0;
            ROOT = x;
            this->t = t;
            BTree_node_init(x);
        }

        void insert(int k)
        {
            node* r = ROOT;
            if(r->n == 2*t - 1)
            {
                node* s = new node;
                BTree_node_init(s);
                ROOT = s;
                s->leaf = false;
                s->n = 0;
                s->c[1] = r;
                BTree_split(s,1);
                BTree_insert_nonfull(s,k);
            }
            BTree_insert_nonfull(r,k);
        }

        void print()
        {
            queue<node* > Q;
            queue<int> L;
            Q.push(ROOT);
            L.push(1);
            while(!Q.empty())
            {
                node* t = Q.front();Q.pop();
                cout<<"[";
                for(int it = 1;it<=t->n;it++)
                {
                    cout<<t->keys[it]<<" ";
                }
                cout<<"] ";
                int level = L.front();L.pop();
                for(int i = 1;i<=t->n+1;i++)
                {
                    if(t->c[i])
                    {
                        Q.push(t->c[i]);
                        L.push(level+1);
                    }
                }
                if(level == L.front())cout<<" ";
                else cout<<endl;
            }
        }
        node* search(node* x, int k)
        {
            int i = 1;
            while(i<=x->n && k>x->keys[i])
                i++;
            if(i<=x->n && k == x->keys[i])
                return x;
            else if(x->leaf == true)
                return NULL;
            else
                return search(x->c[i],k);
        }
        node* parentSearch(node* parent, node* child)
        {
            if(child == ROOT)return NULL;
            for(int i = 1;i<=parent->n;i++)
            {
                if(parent->c[i] == child)
                {
                    return parent;
                }
            }
            for(int i = 1;i<=parent->n+1;i++)
            {
                return parentSearch(parent->c[i],child);
            }
        }
        void deleteValue(int x)
        {
            //search for the node that contains x
            node* q = search(ROOT,x);
            int idx = 1;
            if(q==NULL)return;
            for(int i = 1;i<=q->n;i++){
                if(q->keys[i] == x)
                    idx = i;
            }
            // case 1 : a fully fledged leaf
            if(q->leaf == true && q->n >=t)
            {
                //move back elements
                for(int i = idx;i<=q->n;i++)
                {
                    q->keys[i] = q->keys[i+1];
                }
                q->n = q->n-1;
            }
            else if(q->leaf == true && q->n < t)
            {
                //we have the position as idx
                //we need to play with C[idx] and C[idx+1]
                node* parent = parentSearch(ROOT,q);
                int thisNum = 1;
                for(int i = 1;i<=parent->n;i++)
                {
                    if(parent->c[i] == q)
                        thisNum = i;
                }
                node* sibling = parent->c[thisNum+1];
                if(sibling->n >=t)
                {
                    //move the element from top to down
                    q->keys[idx] = parent->keys[parent->n];
                    parent->keys[parent->n] = sibling->keys[1];
                    for(int i = 1;i<=sibling->n;i++)
                        sibling->keys[i] = sibling->keys[i+1];
                }
            }
        }
};
int main()
{
    BTree T(3);
    T.insert(5);
    T.insert(4);
    T.insert(10);
    T.insert(34);
    T.insert(23);
    T.insert(11);
    T.insert(12);
    T.insert(45);
    T.insert(55);
    T.print();
    T.deleteValue(55);
    T.print();
    T.deleteValue(12);
    T.print();
    return 0;;
}
