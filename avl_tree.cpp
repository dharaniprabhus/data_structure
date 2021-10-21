#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
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
        virtual void visit(int data, int sp) = 0;
};

class TreeSink  : public TreeVisitor
{
    public:
        void visit(int data, int sp) override
        {
            stringstream ss;
            for(int i = 0; i<sp; ++i){
                ss << " ";
            }
            if (data == INT32_MAX){
                ss << 'x' << "\n";
            }else{
                ss << data << "\n";
            }
            m_print.push_back(ss.str());
            ss.str("");
            ss.clear();
        }
        void show(){
            int mx_len = 0;
            for(auto s : m_print){
                cout << s;
            }
        }
    private:
        vector<string> m_print;
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
        void inOrderRight (TreeVisitor& tv){
            inOrderRightImpl (m_root,tv,1);
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
                v.visit(cur->data,4);
                inOrderImpl(cur->right,v);
            }
        }

        void inOrderRightImpl (Node* cur, TreeVisitor& v, int sp){
            if (cur){
                inOrderRightImpl (cur->right,v, sp + 4);
                v.visit(cur->data, sp);
                inOrderRightImpl (cur->left, v, sp + 4);
            }else{
                v.visit(INT32_MAX,sp);
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
    stringstream ss;
    TreeSink  sink;
    bst.inOrderRight (sink);
    sink.show();
    cout << "\n";
    cout << "Height : " << bst.height() << "\n";

    // bst.insert(5);
    // cout << "Does 5 exist ? " << ((bst.exist(5)) ? "Yes" : "No");
    // cout << "\n";
    return 0;
}
