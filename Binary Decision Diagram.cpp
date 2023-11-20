#include <iostream>
#include <unordered_map>
#include <sstream>

struct Node
{
    char var;
    Node *low;
    Node *high;
    bool isTerminal;
    int v1;
    int v2;

    Node(char v, Node *l, Node *h, bool terminal, int val, int val2)
        : var(v), low(l), high(h), isTerminal(terminal), v1(val), v2(val2) {}
};

class BDD
{
private:
    std::unordered_map<std::string, Node *> table;

public:
    Node *createNode(char var, Node *low, Node *high, bool terminal = false, int val = -1, int val2 = -1)
    {
        Node *newNode = new Node(var, low, high, terminal, val, val2);
        return newNode;
    }

    std::string nodeToString(Node *node)
    {
        std::ostringstream oss;
        oss << reinterpret_cast<std::uintptr_t>(node);
        return oss.str();
    }

    Node *apply(char var, Node *low, Node *high)
    {
        std::string key = nodeToString(low) + nodeToString(high);

        if (table.find(key) != table.end())
        {
            return table[key];
        }

        Node *newNode = createNode(var, low, high);
        table[key] = newNode;

        return newNode;
    }

    void display(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        std::cout << root->var;
        if(root->isTerminal)
        {
            std::cout << "(" << root->v1 << ")"<< "(" << root->v2 << ")";
        }

        std::cout << " ";
        display(root->low);
        display(root->high);
    }
};

int main()
{
    BDD bdd;
    Node *nodeA = bdd.createNode('A', nullptr, nullptr, true, 1, 0);
    Node *nodeB = bdd.createNode('B', nullptr, nullptr, true, 0, 1);
    Node *result = bdd.apply('C', nodeA, nodeB);

    std::cout << "BDD representation: ";
    bdd.display(result);

    return 0;
}
