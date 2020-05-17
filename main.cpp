/*
* Entry point for the program, runs the simulation
*/

#include <iostream>
#include <vector>
#define SIZE 81
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

// try a single rule on a neighborhood
bool rule_applies(Rule rule, int left, int curr, int right) 
{
    bool rule_applies = (rule.getLeft() == left) && (rule.getMiddle() == curr)
                            && (rule.getRight() == right);

    return rule_applies;
}

// keep trying all the rules on the neighborhood until one works, or no more rules left
int update_cell(vector<Rule> rules, int left, int curr, int right)
{
    int next = curr;
    for (vector<Rule>::iterator iter = rules.begin(); iter != rules.end(); iter++)
    {
        Rule curr_rule = *iter;
        if (rule_applies(curr_rule, left, curr, right))
        {
            next = curr_rule.getNext();
            break;
        } 
    }
    return next;
}

// update a row
void update_row(vector<Rule> rules, int curr_gen[], int next_gen[])
{
    for (int i = 0; i < SIZE; i++)
    {
        int left_index = ((i-1) + SIZE) % SIZE;
        int right_index = ((i+1) + SIZE) % SIZE;
        next_gen[i] = update_cell(rules, curr_gen[left_index], curr_gen[i], curr_gen[right_index]);
    }

}

int main() 
{
    vector<Rule> rules;
    int curr_gen[SIZE] = {0};
    int next_gen[SIZE] = {0};

    Rule r1(0,0,0,1);
    Rule r2(0,0,1,1);
    Rule r3(1,0,0,1);
    Rule r4(1,0,1,1);

    Rule ar1(1,1,1,0);
    Rule ar2(1,1,0,0);
    Rule ar3(0,1,1,0);
    Rule ar4(0,1,0,0);

    rules.push_back(r1);
    rules.push_back(r2);
    rules.push_back(r3);
    rules.push_back(r4);
    rules.push_back(ar1);
    rules.push_back(ar2);
    rules.push_back(ar3);
    rules.push_back(ar4);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < SIZE; j++) {cout << curr_gen[j];} cout << endl;
        update_row(rules, curr_gen, next_gen);
        copy(next_gen, next_gen + SIZE, curr_gen);
        fill(next_gen, next_gen + SIZE, 0);
    }



}