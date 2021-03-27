#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Tipo abstrato transition
typedef struct Transition{
    char symbol;
    int destiny;
    struct Transition* next;
}transition;

// Tipo abstrato state
typedef struct State{
    int index;
    transition *transitions;
} state;

state* init_automaton(char *automaton_name);
state* init_states(int automaton_size);
int get_destiny(char* line);
transition* init_transition_list();
void add_transition(transition* list_head, char symbol, int destiny);
int next_state(transition *transitions, char symbol);
void execute_automaton(state *automaton, int initial_state, char *word, int command_line);
void read_from_line(state *automaton);
void show_menu(state *automaton);
void read_from_file(state *automaton);
int is_final(transition *transitions);