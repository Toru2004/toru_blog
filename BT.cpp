#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node*right,*left;
    int height;
};

void create(Node* &L)
{
    L=NULL;
}

int height(Node* p)
{
    if(p==NULL) return 0;
    return p->height;
}

Node* createNode(int x)
{
    Node*p=new Node;
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    p->height =1;
    return p;
}

void NLR(Node*L)
{
    if(L!=NULL)
    {
        cout << L->data << " ";
        NLR(L->left);
        NLR(L->right);
    }
}

int getBalance(Node* node)
{
    if(node==NULL) return 0;
    return height(node->right) - height(node->left);
}

int max(int x, int y)
{
    return x>y?x:y;
}

Node* leftRotate(Node* &x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->right),height(x->left)) + 1;
    y->height = max(height(y->right),height(y->left)) + 1;\
    return y;
}

Node* rightRotate(Node* x)
{
    Node* y = x->left;
    Node* T2=y->right;

    y->right = x;
    x->left = T2;

    x->height = max(height(x->right),height(x->left)) + 1;
    y->height = max(height(y->right),height(y->left)) + 1;\
    return y;
}

Node* insert(Node* &L, int x)
{
    if(L==NULL) return createNode(x);
    
    if(x<L->data) L->left = insert(L->left,x);
    else if(x>L->data) L->right = insert(L->right,x);
    else return L;

    L->height = max(height(L->right), height(L->left))+1;

    int bal = getBalance(L);
    if(bal<-1 && x<L->left->data)
    {
        return rightRotate(L);
    }
    else if(bal>1 && x>L->right->data)
    {
        return leftRotate(L);
    }
    else if(bal<-1 && x>L->left->data)
    {
        L->left = leftRotate(L->left);
        return rightRotate(L);
    }
    else if(bal>1 && x<L->right->data)
    {
        L->right = rightRotate(L->right);
        return leftRotate(L);
    }
    return L;
}

Node* deleteNode(Node* &L, int x)
{
    if(L==NULL) return L;
    
    if(x<L->data) L->left = deleteNode(L->left,x);
    else if(x>L->data) L->right = deleteNode(L->right,x);
    else
    {
        if(L->right == NULL || L->left == NULL)
        {
            Node*tmp = L->left?L->left:L->right;
            if(tmp==NULL)
            {
                tmp = L;
                L = NULL;
            }
            else
            {
                *L=*tmp;
            }
            delete tmp;
        }
        else
        {
            Node*p=L->right;
            while(p->left!=NULL)
            {
                p = p->left;
            }
            L->data = p->data;
            L->right = deleteNode(L->right,p->data);
        }
    }

    if(L==NULL) return L;

    L->height = max(height(L->right),height(L->left))+1;

    int bal = getBalance(L);

    if(bal<-1 && getBalance(L->left)<=0)
    {
        return rightRotate(L);
    }
    else if(bal<-1 && getBalance(L->left)>0)
    {
        L->left = leftRotate(L->left);
        return rightRotate(L);
    }
    else if(bal>1 && getBalance(L->right)>=0)
    {
        return leftRotate(L);
    }
    else if(bal>1 && getBalance(L->right)<0)
    {
        L->right = rightRotate(L->right);
        return leftRotate(L);
    }
    return L;
}

int main()
{
    Node*L;
    create(L);
    L = insert(L, 9); 
    L = insert(L, 5); 
    L = insert(L, 10); 
    L = insert(L, 0); 
    L = insert(L, 6); 
    L = insert(L, 11); 
    L = insert(L, -1); 
    L = insert(L, 1); 
    L = insert(L, 2); 
    NLR(L);

    cout << endl;
    L = deleteNode(L, 10);
    NLR(L);

    return 0;
}
