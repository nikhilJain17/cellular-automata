/*
* Entry point for the program, runs the simulation
*/

#include <iostream>
#include <vector>
#include "termcolor.hpp"
#include "rules.hpp"
#define SIZE 178
#define NUM_ITER 1000
using namespace std;

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

void print_row(int cells[])
{
    for (int j = 0; j < SIZE; j++) 
    {
        usleep(300);
        if (cells[j])
            cout << termcolor::yellow << "•" << termcolor::reset;
        else
            cout << termcolor::dark << " " << termcolor::reset;
    } 
    cout << endl; 
}

int main() 
{
    int curr_gen[SIZE] = {0};
    curr_gen[(int) (SIZE / 2)] = 1;
    int next_gen[SIZE] = {0};

    int rule_num = 0;
    cout << "Which rule? 0-255: ";
    cin >> rule_num;

    for (int i = 0; i < NUM_ITER; i++)
    {
        print_row(curr_gen);
        update_row(generate_rule(rule_num), curr_gen, next_gen);
        copy(next_gen, next_gen + SIZE, curr_gen);
        fill(next_gen, next_gen + SIZE, 0);
    }



}