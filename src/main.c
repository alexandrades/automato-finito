#include "tp.h"

void main(){

    state *automaton = init_automaton("automaton.txt");
    show_menu(automaton);
}