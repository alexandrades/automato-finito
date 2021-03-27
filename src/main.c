#include "tp.h"

void main(){

    // Inicializa o autômato e exibe o menu principal
    state *automaton = init_automaton("automaton.txt");
    show_menu(automaton);
}