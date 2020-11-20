#include <iostream>
#include <queue>

template <class T>
struct leaf {
    leaf* right;
    leaf* left;
    T value;
    leaf(T g, leaf<T>* b = NULL, leaf<T>* c = NULL) {
        this->value = g;
        this->right = c;
        this->left = b;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class tree {
    leaf<T>* first;
    int length_p(leaf<T>* g) {
        if(g == NULL)
            return 0;
        return 1 + length_p(g->left) + length_p(g->right);
    }
    void copy_left(leaf<T>* q, leaf<T>* g) {
        if(g->left) {
            leaf<T>* l = new leaf<T>;
            leaf<T>* y = g->left;
            l->value = y->value;
            q->left = l;
            copy_left(q->left, g->left);
            copy_right(q->right, g->right);
        }
        else {
            q->left = nullptr;
            return;
        }
    }
    void copy_right(leaf<T>* q, leaf<T>* g) {
        if(g->right) {
            leaf<T>* l = new leaf<T>;
            leaf<T>* y = g->right;
            l->value = y->value;
            q->right = l;
            copy_left(q->left, g->left);
            copy_right(q->right, g->right);
        }
        else {
            q->right = nullptr;
            return;
        }
    }
    
    int leaf_count_private(leaf<T>* q) {
        if(!q)
            return 0;
        
        if(q->left || q->right)
            return leaf_count_private(q->left) + leaf_count_private(q->right);

        return 1;
    }

public:
    tree() {
        first = NULL;
    }
    tree(leaf<T>* g) {
        first = g;
    }
    tree(const tree* a) {
        if(!a.empty()) {
            leaf<T>* q = new leaf<T>;
            leaf<T>* g = a.first;
            q->value = g->value;
            first = q;
            copy_left(first, a.first);
            copy_right(first, a.first);
        }
        else
        {
            first = NULL;
        }
        
    }
    int length() const{
        return length_p(first);
    }

    int leaf_count() {
        return leaf_count_private(first);
    }

    bool empty() const {
        if(first)
            return false;
        return true;
    }
    void createRoot(leaf<T>* g) {
        if(!first) {
            first = g;
        }
        return;
    }
    void insertLeft(T g, leaf<T>* q) {
        if((q->left) == NULL) {
            leaf<T>* n = new leaf<T>(g);
            q->left = n;
        }
        return;
    }
    void insertRight(T g, leaf<T>* q) {
        if((q->right) == NULL) {
            leaf<T>* n = new leaf<T>(g);
            q->right = n;
        }
        return;
    }
    void deleteLeft(leaf<T>* q) {
        if((q->left) != NULL) {
            q->left = nullptr;
        }
    }
    void deleteRight(leaf<T>* q) {
        if(q->right) {
            q->right= nullptr;
        }
    }
    int max_level() {
        if(first == NULL) {
            return 0;
        }
        else {
            std::queue<leaf<T>*> q1, q2;
            q1.push(first);
            int ans = 1;
            while(1) {
                while(!q1.empty()) {
                    leaf<T>* g = q1.front();
                    if(g->left) {
                        q2.push(g->left);
                    }
                    if(g->right) {
                        q2.push(g->right);
                    }
                    q1.pop();
                }
                if(q2.empty())
                    return ans;

                while(!q2.empty()) {
                    q1.push(q2.front());
                    q2.pop();
                }
                ++ans;
            }
        }
    }   
    leaf<T>* getFirst() const{
        return first;
    }

    leaf<T>* find(T g) const {
        if(first->value == g)
            return first;
        std::queue<leaf<T>*> q1, q2;
        q1.push(first);
        while(1) {
            while(!q1.empty()) {
                leaf<T>* u = q1.front();
                if(u->left) {
                    leaf<T>* v = u->left;
                    if(v->value == g)
                        return v;
                    q2.push(u->left);
                }
                if(u->right) {
                    leaf<T>* v = u->right;
                    if(v->value == g)
                        return v;
                    q2.push(u->right);
                }
                q1.pop();
            }
            if(q2.empty())
                return NULL;
            
            while(!q2.empty()) {
                q1.push(q2.front());
                q2.pop();
            }
        }
    }

    void preorder_from(leaf<T>* q) {
        if(q) {
            std::cout<<q->value<<" ";
            preorder_from(q->left);
            preorder_from(q->right);
        }
    }

    void inorder_from(leaf<T>* q) {
        if(q) {
            inorder_from(q->left);
            std::cout<<q->value<<" ";
            inorder_from(q->right);
        }
    }

    void postorder_from(leaf<T>* q) {
        if(q) {
            postorder_from(q->left);
            postorder_from(q->right);
            std::cout<<q->value<<" ";
        }
    }

    void preorder() {
        preorder_from(first);
    }

    void inorder() {
        inorder_from(first);
    }

    void postorder() {
        postorder_from(first);
    }

    void destroyTree() {
        first = NULL;
    }
    ~tree() {
        first = NULL;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

int main() {
    leaf<char>* e = new leaf<char>('e');
    leaf<char>* d = new leaf<char>('d');
    leaf<char>* b = new leaf<char>('b', d, NULL);
    leaf<char>* f = new leaf<char>('f');
    leaf<char>* c = new leaf<char>('c', e, f);
    leaf<char>* root = new leaf<char>('a', b, c);
    tree<char> a;
    a.createRoot(root);
    a.insertLeft('h', e);
    a.insertRight('i', e);
    a.insertRight('g', d);
    cout<<a.leaf_count()<<endl;
    return 0;
}