#include "tp.h"

#define MAX_LINE_SIZE 10
#define DESTINY_SIZE 6

// Aloca espaço na memória para armazenamento dos estados do autômato.
// automaton_size: Inteiro contendo o tamanho do autômato.
state* init_states(int automaton_size){
    state *states_arr = calloc(sizeof(state), automaton_size);
    for(int i = 0; i < automaton_size; i++){
        states_arr[i].index = i;
        states_arr[i].transitions = init_transition_list();
    }
    return states_arr;
}

// Extrai o index do estado de destino a partir de um vetor de caracteres e retorna como um inteiro.
// line: vetor de char contendo uma linha que representa uma transição no arquivo do autômato.
int get_destiny(char* line){
    char destiny[DESTINY_SIZE];

    for(int i = 0; i < DESTINY_SIZE; i++){
        destiny[i] = line[i+2];
    }

    return atoi(destiny);
}

// Lé um arquivo .txt contendo a representação do autômato a ser utilizado para o reconhecimento das palavras
// automaton_name: vetor de caracteres contendo o nome do arquivo onde se encontra a representaçao do autômato.
state* init_automaton() {
    char line[MAX_LINE_SIZE];
    char symbol;
    int index, automaton_size, destiny;
    
    FILE* arq = fopen("automaton.txt", "r");

    if (arq == NULL){
        printf("Problema ao ler arquivo.\n");
        return NULL;
    }

    fscanf(arq, "%d\n", &automaton_size);
    state* states_arr = init_states(automaton_size);
    fscanf(arq, "%d\n", &index);


    while (!feof(arq)){
        fgets(line, MAX_LINE_SIZE, arq);

        if(strlen(line) == 2){
            fscanf(arq, "%d\n", &index);
            continue;
        }

        symbol = line[0];
        destiny = get_destiny(line);
        
        add_transition(states_arr[index].transitions, symbol, destiny);
    }
    fclose(arq);
    return states_arr;
}

// Adiciona uma nova transição no início da lista de transições de um estado
// list_head: nó cabeça das transições de um estado;
// symbol: char contendo um símbolo que pode ser lido pelo autômato;
// destiny: inteiro contendo o próximo estado quando symbol é lido
void add_transition(transition* list_head, char symbol, int destiny){
    transition *new_transition = (transition*) malloc(sizeof(transition));
    new_transition->symbol = symbol;
    new_transition->destiny = destiny;

    transition *aux_transition = list_head->next;
    list_head->next = new_transition;
    new_transition->next = aux_transition;

}

// Aloca espaço na memória e inicializa uma transição pra ser utilizada como nó cabeça.
transition* init_transition_list(){
    transition* first_transition = (transition*) malloc(sizeof(transition));
    first_transition->next = NULL;
    return first_transition;
}

//  Exibe as opções para o usuário
//  automaton: vetor contento os estados do autômato
void show_menu(state *automaton){
    int option = 0;
    // Exibição do menu em loop.
    do{
        printf("Escolha uma opção:\n"
            "1 - INSERIR PALAVRA INDIVIDUAL\n"
            "2 - CARREGAR PALAVRAS DE UM ARQUIVO\n"
            "0 - SAIR\n");
        scanf("%d", &option);

        if(option == 1){
            read_from_line(automaton);
        }
        else if(option == 0){
            exit(1);
        }
        else{
            read_from_file(automaton);
        }
    } while (1);
    
}

// Lé cada símbolo da palavra e atualiza current_state para seu devido estado.
// automaton: vetor contendo os estados do autômato;
// current_state: estado inicial do autômato que é atualizado a cada símbolo lido;
// word: palavra a ser reconhecida pelo autômato;
// command_line: 1 se o usuário inserir a palavra por terminal ou 0 se for por arquivo.
void execute_automaton(state *automaton, int current_state, char *word, int command_line){
    
    for(int i = 0; i < strlen(word); i++){
        current_state = next_state(automaton[current_state].transitions, word[i]);
        if (current_state == -1){
            printf("\"%s\" \n: Palavra Rejeitada por indefinição\n\n", word);
            return;
        }
        if (command_line){
            printf("Passo %d : '%c' -> %d\n", i, word[i], current_state);
        }
        
    }

    if(is_final(automaton[current_state].transitions)){
        printf("\"%s\" \n: Palavra Aceita\n\n", word);
    }
    else{
        printf("\"%s\" \n: Palavra Rejeitada: Fim da leitura em estado não-final.\n\n", word);
    }
}

// Solicita que o usuário insira uma palavra para verificar se ela é aceita ou não
// automaton: vetor contendo os estados do autômato
void read_from_line(state *automaton){
    char word[1000];
    printf("Digite uma palavra: \n");
    scanf("%s", word);

    printf("\n==== RESULTADO ====\n");
    execute_automaton(automaton, 0, word, 1);
}

// Solicita ao usuário que insira o nome do arquivo .txt contendo as palavras a serem reconhecidas
// e executa o autômato para cada uma delas
// automaton: vetor contendo os estados do autômato.
void read_from_file(state *automaton){
    char file_name[100];
    printf("Informe o nome do arquivo:");
    scanf("%s", file_name);

    FILE* arq2 = fopen(file_name, "r");

    if (arq2 == NULL){
        printf("Problema ao ler arquivo.\n");
        return;
    }

    printf("\n==== RESULTADO ====\n");
    while (!feof(arq2)){
        char line[1000];
        fscanf(arq2, "%s\n", line);

        execute_automaton(automaton, 0, line, 0);
    }
    fclose(arq2);
    
}

// Percorre a lista de transições de um estado procurando por um símbolo retornando o valor destiny da transição ou
// -1 caso não encontre o símbolo;
// transitions: ponteiro para a transição cabeça de um estado;
// symbol: char contendo um símbolo a ser procurado na lista de transição.
int next_state(transition *transitions, char symbol){
        transition *aux_transition = transitions;

        if(aux_transition == NULL){
            printf("indefinição\n");
            return -1;
        }
        aux_transition = aux_transition->next;
        while(aux_transition != NULL){
            if(aux_transition->symbol == symbol){
                return aux_transition->destiny;
            }
            aux_transition = aux_transition->next;
        }
        return -1;
    
}

// Verifica se o estado é final retornando 1, ou -1 caso não seja.
int is_final(transition *transitions){
    transition *aux_transitions = transitions;
    if(aux_transitions == NULL){
        printf("Não é final");
        return 0;
    }
    aux_transitions = aux_transitions->next;
    while(aux_transitions != NULL){
        if(aux_transitions->symbol == '-' && aux_transitions->destiny == -2){
            return 1;
        }
        aux_transitions = aux_transitions->next;
    }
    return 0;
}


