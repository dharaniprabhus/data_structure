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

class BinarySearchTree
{
    public:
        BinarySearchTree(): m_root(nullptr) {}
        void insert(int data)
        {
            if(!m_root){
                m_root = new Node{data};
            }else{
                insertImpl(m_root,data);
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
        void insertImpl(Node* cur, int data){
            if (data < cur->data){
                if (!cur->left)cur->left = new Node{data};
                else insertImpl(cur->left,data);
            }else{
                if (!cur->right)cur->right = new Node{data};
                else insertImpl(cur->right,  data);
            }
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
    BinarySearchTree bst;
    srand(time(0));
    for(int i = 0; i< 10; ++i){
        bst.insert(rand() % 1000);
    }
    OstreamSink sink(cout);
    cout << "Data : ";
    bst.inOrder(sink);
    cout << "\n";
    cout << "Height : " << bst.height() << "\n";

    bst.insert(5);
    cout << "Does 5 exist ? " << ((bst.exist(5)) ? "Yes" : "No");
    cout << "\n";
    return 0;
}
