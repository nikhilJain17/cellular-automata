#include <vector>
using namespace std;

class Rule 
{
    private:
        int left, middle, right, next;
    public:
        Rule (int left, int middle, int right, int next);
        int getLeft() { return left; }
        int getMiddle() { return middle; }
        int getRight() { return right; }
        int getNext() { return next; }
};

Rule::Rule(int l, int m, int r, int n)
{
    left = l;
    middle = m;
    right = r;
    next = n;
}

int* to_binary(int x)
{
    static int bits[8] = {0};
    int i = 0;
    while (x > 0)
    {
        bits[i] = x % 2;
        i++;
        x = x / 2;
    }
    return bits;
}


// return rule 0 - 255
vector<Rule> generate_rule(int x)
{
    vector<Rule> rules;
    if (x < 0 || x > 255)
    {
        return rules; 
    }

    int *bits = to_binary(x);
    
    Rule r1(1,1,1,bits[7]);
    Rule r2(1,1,0,bits[6]);
    Rule r3(1,0,1,bits[5]);
    Rule r4(1,0,0,bits[4]);
    Rule r5(0,1,1,bits[3]);
    Rule r6(0,1,0,bits[2]);
    Rule r7(0,0,1,bits[1]);
    Rule r8(0,0,0,bits[0]);

    rules.push_back(r1);
    rules.push_back(r2);
    rules.push_back(r3);
    rules.push_back(r4);
    rules.push_back(r5);
    rules.push_back(r6);
    rules.push_back(r7);
    rules.push_back(r8);

    return rules;
}

