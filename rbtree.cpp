#include<queue>
#include<iostream>
#include<stdlib.h>
#define RED 10
#define BLACK 11
using namespace std;
class RBTree{
    typedef struct _node{
        int data;
        _node* parent;
        _node* left;
        _node* right;
        int color;
	}_node;
    _node* NIL;
    _node* ROOT;

    /*Public functions*/

    _node* create_node(int d)
    {
        _node *t = new _node;
        t->color = RED;
        t->data = d;
        t->left = NIL;
        t->right = NIL;
        t->parent = NIL;
        return t;
	}

	void RB_Insert_Fixup(_node* z){
        while(z->parent->color == RED){
            //which child z's parent is, of its grandparent
            if(z->parent == z->parent->parent->left){
                //detemine the color of uncle y;
                _node* y = z->parent->parent->right;
                if(y->color == RED) //uncle y is red
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
				}
                else //uncle y is black
                {
                    if ( z == z->parent->right)
                    {
                        z = z->parent;
                        left_rotate(z);
					}
                    z->parent->color = BLACK;
                    z->parent->parent->color = BLACK;
                    right_rotate(z->parent->parent);
				}
			}
            else
            {
                //detemine the color of uncle y;
                _node* y = z->parent->parent->left;
                if(y->color == RED) //uncle y is red
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
				}
                else //uncle y is black
                {
                    if ( z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
					}
                    z->parent->color = BLACK;
                    z->parent->parent->color = BLACK;
                    left_rotate(z->parent->parent);
				}
			}
		}
        ROOT->color = BLACK;
	}

	void left_rotate(_node* x){
        _node* y = x->right;
        x->right = y->left;
        if(y->left != NIL)
		y->left->parent = x;
        y->parent = x->parent;
        if(x->parent == NIL)
		ROOT = y;
        else if(x == x->parent->left)
		x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
	}

    void right_rotate(_node* y){
        _node* x = y->left;
        y->left = x->right;
        if(x->right != NIL)
		x->right->parent = y;
        x->parent = y->parent;
        if(x->parent == NIL)
		ROOT = x;
        else if(y == y->parent->left)
		y->parent->left = x;
        else y->parent->left = x;
        x->right = y;
        y->parent = x;
	}

    void RB_Transplant(_node* u, _node* v)
    {
        if(u->parent == NIL)
		ROOT = v;
        else if(u == u->parent->left)
		u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
	}

    _node* RB_Tree_Min(_node* x)
    {
        while(x!=NIL)x = x->left;
        return x;
	}

	void RB_Delete_Fixup(_node* x)
    {
        _node* w;
        while(x!=ROOT && x->color == BLACK)
        {
            if(x == x->parent->left)
            {
                w = x->parent->right;
                if(w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
				}
                if(w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
				}
                else
                {
                    if(w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->parent->right;
					}
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->parent);
                    x = ROOT;
				}
			}
            else
            {
                w = x->parent->left;
                if(w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
				}
                if(w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
				}
                else
                {
                    if(w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->parent->left;
					}
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->parent);
                    x = ROOT;
				}
			}
		}
        x->color = BLACK;
	}

	public:
    void initialize(){
        //initialize it with a T.NIL
        NIL = new _node;
        ROOT = new _node;
        NIL->color = BLACK;
        NIL->right = NIL;
        NIL->left = NIL;
        NIL->parent = NULL;
        ROOT = NIL;
	}

    _node* RB_Search(int data, _node* x)
    {
        if(x == NIL || data == x->data) return x;
        if(data < x->data) return RB_Search(data, x->left);
        else return RB_Search(data, x->right);
	}

    void insert_node(int data){
        _node* t = create_node(data);//create_node(data);
        _node* x = ROOT;
        //insert this like a leaf to the tree, like a binary tree
        _node* y = NIL;
        while(x != NIL){
            y = x;
            if(t->data < x->data){
                x = x->left;
			}
            else x = x->right;
		}
        t->parent = y;
        if(y == NIL)
		ROOT = t;
        else if(t->data < y->data)
		y->left = t;
        else y->right = t;
        //inserted like a BST, now perform the RB-Tree insert-fixup
        RB_Insert_Fixup(t);
	}

    void RB_Delete(int data){
        _node* z = RB_Search(data, ROOT);
        _node* x;
        if( z == NIL)
        {
            cout<<"The node cannot be deleted!";
            return;
		}
        _node* y = z;
        int y_original_color = y->color;
        if(z->left == NIL)
        {
            x = z->right;
            RB_Transplant(z,z->right);
		}
        else if(z->right == NIL)
        {
            x = z->left;
            RB_Transplant(z,z->left);
		}
        else
        {
            y = RB_Tree_Min(z->right);
            y_original_color = y->color;
            x = y->right;
            if(y->parent == z)
			x->parent = y;
            else
            {
                RB_Transplant(y,y->right);
                y->right = z->right;
                y->right->parent = y;
			}
            RB_Transplant(y,y->right);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
		}
        if(y_original_color == BLACK)
		RB_Delete_Fixup(x);
	}

    void level_order(){
        queue<_node *> Q;
        queue<int> l;
        l.push(1);
        if(ROOT!=NIL)Q.push(ROOT);
        while(Q.size()){
            _node* u = Q.front();Q.pop();
            int level = l.front();l.pop();
            cout<<u->data<<" ";
            if(u->left!=NIL){Q.push(u->left);l.push(level+1);}
            if(u->right!=NIL){Q.push(u->right);l.push(level+1);}
            if(level != l.front())cout<<"\n";
		}
        cout<<endl;
	}

    void inorder()
    {
        inorder_main(ROOT);
	}

    void inorder_main(_node* x){
        if(x->left!=NIL)inorder_main(x->left);
        cout<<x->data<<" ";
        if(x->right!=NIL)inorder_main(x->right);
	}
};
int main()
{
    RBTree t1;
    int arr[] = {8,13,17,1,6,11,15,22,25,27};
    t1.initialize();
    for(int i = 0;i<10;i++){cout<<arr[i];t1.insert_node(arr[i]);}
    cout<<endl;
    t1.level_order();
    //t1.inorder();
    cout<<endl;
    return 0;
}
