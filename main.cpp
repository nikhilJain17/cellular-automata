/*
* Entry point for the program, runs the simulation
*/

#include <iostream>
#include <vector>
#include <sys/ioctl.h>

#include "termcolor.hpp"
#include "rules.hpp"
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
void update_row(vector<Rule> rules, int curr_gen[], int next_gen[], const int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        int left_index = ((i-1) + SIZE) % SIZE;
        int right_index = ((i+1) + SIZE) % SIZE;
        next_gen[i] = update_cell(rules, curr_gen[left_index], curr_gen[i], curr_gen[right_index]);
    }

}

void print_row(int cells[], const int SIZE)
{        
    for (int j = 0; j < SIZE; j++) 
    {
        if (cells[j])
            cout << termcolor::yellow << "•" << termcolor::reset;
        else
            cout << termcolor::dark << " " << termcolor::reset;
    } 
    cout << endl; 
}

int get_window_size()
{
     struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    int temp = 80;
    if (size.ws_col > 0) 
        temp = size.ws_col;
    
    return temp;
}

int main() 
{
    const int SIZE = get_window_size();

    int curr_gen[SIZE], next_gen[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        curr_gen[i] = 0;
        next_gen[i] = 0;
    }
    curr_gen[(int) (SIZE / 2)] = 1;

    int rule_num = -1;
    while (rule_num < 0 || rule_num > 255) {
        cout << "Which rule? 0-255: ";
        cin >> rule_num;
    }

    while (true)
    {
        usleep(75000);
        print_row(curr_gen, SIZE);
        update_row(generate_rule(rule_num), curr_gen, next_gen, SIZE);
        copy(next_gen, next_gen + SIZE, curr_gen);
        fill(next_gen, next_gen + SIZE, 0);
    }



}