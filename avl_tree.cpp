#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node
{
    int data = 0 ;
    Node* left = nullptr;
    Node* right = nullptr;
};

class TreeVisitor
{
    public:
        virtual void visit(int data) = 0;
};

class OstreamSink : public TreeVisitor
{
    public:
        OstreamSink(ostream& out) : m_out{out}{}
        void visit(int data) override
        {
            m_out << data << " ";
        }
    private:
        ostream& m_out;
};

class AvlTree
{
    public:
        AvlTree(): m_root(nullptr) {}
        void insert(int data)
        {
            if(!m_root){
                m_root = new Node{data};
            }else{
                insertImpl(m_root,nullptr,data);
            }
        }
        bool exist(int data){
            return exist(m_root, data);
        }
        void inOrder(TreeVisitor& tv){
            inOrderImpl(m_root,tv);
        }
        int height()
        {
            return heightImpl(m_root);
        }
    private:
        void insertImpl(Node* cur,Node* parent, int data){
            if (data < cur->data){
                if (!cur->left)cur->left = new Node{data};
                else insertImpl(cur->left,cur,data);
            }else{
                if (!cur->right)cur->right = new Node{data};
                else insertImpl(cur->right, cur, data);
            }
            if (bal(cur) > 1){
                if(bal(cur->right) < 0){
                    rr(cur->right, cur);
                }
                rl(cur, parent);
            }
            else if (bal(cur) < -1){
                if (bal(cur->left) > 0){
                    rl(cur->left,cur);
                }
                rr(cur,parent);
            }
        }

        // 1
        //    3 c->l = nullptr
        // 2 /NP
        void rr(Node* cur, Node* parent){
            Node* newParent = cur->left;
            cur->left = newParent->right;
            newParent->right = cur;
            if (parent){
                if (newParent->data < parent->data){
                    parent->left = newParent;
                }else{
                    parent->right = newParent;
                }
            }else{
                m_root= newParent;
            }
        }

        void rl(Node*cur, Node* parent){
            Node* newParent = cur->right;
            cur->right = newParent->left;
            newParent->left = cur;
            if (parent){
                if (newParent->data < parent->data){
                    parent->left = newParent;
                }else{
                    parent->right = newParent;
                }
            }else{
                m_root = newParent;
            }
        }

        int bal(Node* cur){
            return heightImpl(cur->right) - heightImpl(cur->left);
        }

        void inOrderImpl(Node* cur,TreeVisitor& v){
            if (cur){
                inOrderImpl(cur->left,v);
                v.visit(cur->data);
                inOrderImpl(cur->right,v);
            }
        }

        int heightImpl(Node* cur){
            if (!cur)return 0;
            auto left = heightImpl(cur->left) + 1;
            auto right = heightImpl(cur->right) + 1;
            return max(left,right);
        }

        bool exist(Node* cur, int data){
            if (!cur)return false;
            if (cur->data == data)return true;
            return exist(cur->left, data) || exist(cur->right, data);
        }

        Node* m_root;
};

int main()
{
    AvlTree bst;
    srand(time(0));
    for(int i = 0; i< 100; ++i){
        bst.insert(rand() % 1000);
    }
    // bst.insert(2);
    // bst.insert(1);
    // bst.insert(3);
    // bst.insert(4);
    // bst.insert(5);
    // bst.insert(6);
    OstreamSink sink(cout);
    cout << "Data : ";
    bst.inOrder(sink);
    cout << "\n";
    cout << "Height : " << bst.height() << "\n";

    // bst.insert(5);
    // cout << "Does 5 exist ? " << ((bst.exist(5)) ? "Yes" : "No");
    // cout << "\n";
    return 0;
}
