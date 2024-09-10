#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "IDE.h"

struct _progetto{
    char * name_project;
    int n_modules;
    int n_functions;
    int max_size;
    node_module  modules;
    bool** called_functions;
};
struct _module{
    int id_module;
    char * name;
    char * path_h;
    char * path_c;
    bool external;
    node_function  functions;
};
struct _function{
    int id_function;
    char * signature;
};
struct _node_function{
    function function;
    struct _node_function * next;
};
struct _node_module{
    module module;
    struct _node_module * next;
};
int main() {
    int choice;
    char * project_name = (char*) malloc(sizeof(char ) * 20);
    char * signature = (char*) malloc(sizeof(char ) * 40);
    char * nome_modulo = (char*) malloc(sizeof(char ) * 10);
    FILE *file;
    char** cycle_paths;
    int internal_choice;
    int functions_choice;
    int called_function_choice;
    int id_function_calling;
    int id_function_called;
    bool internal;
    char * path_h = (char*) malloc(sizeof(char ) * 40);
    char * path_c = (char*) malloc(sizeof(char ) * 40);
    progetto progetto;

    printf("BENVENUTO NEL SISTEMA SOFTWARE CHE GESTISCE UN PROGETTO.\n");
    printf("\n");
    printf("Inserisci il nome del progetto:\n");
    fgets(project_name, 20, stdin);
    project_name[strcspn(project_name, "\n")] = '\0';

    progetto = create_project(project_name,20);

    do {
        printf("1) Stampa e aggiungi un nuovo modulo al progetto \n");
        printf("2) Registra una chiamata a funzione\n");
        printf("3) Salva l'elenco delle chiamate cicliche\n");
        printf("4) Esci\n");
        printf("Fai la tua scelta:\n");

        scanf("%d", &choice);
        getchar();


        switch (choice) {
            case 1:
                print_modules(progetto);

                printf("Inserisci nuovo modulo:\n - inserisci il nome del modulo:\n");

                fgets(nome_modulo, 10, stdin);
                nome_modulo[strcspn(nome_modulo, "\n")] = '\0';

                printf("Il modulo inserito è interno?\n");



                do {

                    printf("1) SI\n");
                    printf("2) NO,ESTERNO\n");
                    scanf("%d" ,&internal_choice);
                    getchar();

                    switch (internal_choice) {
                        case 1:
                            internal = true;
                            break;
                        case 2:
                            internal = false;
                            break;
                        default:
                            break;
                    }
                } while (internal_choice <= 0 || internal_choice >2);

                if(internal){
                    printf("inserisci il percorso del file .h: \n");
                    fgets(path_h, 40, stdin);
                    path_h[strcspn(path_h, "\n")] = '\0';
                    printf("Inserisci il percorso del file .c: \n");
                    fgets(path_c, 40, stdin);
                    path_c[strcspn(path_c, "\n")] = '\0';
                }
                else {
                    printf("Inserisci il percorso del file .h: \n");
                    fgets(path_h, 40, stdin);
                    path_h[strcspn(path_h, "\n")] = '\0';
                }

                add_module_to_project(path_h,path_c,!internal,progetto,nome_modulo);

                do {

                    printf("1) INSERISCI NUOVA FUNZIONE\n");
                    printf("2) ESCI\n");
                    scanf("%d" ,&functions_choice);
                    getchar();

                    switch (functions_choice) {
                        case 1:
                            printf("inserisci la signature della funzione: \n");
                            fgets(signature, 40, stdin);
                            signature[strcspn(signature, "\n")] = '\0';
                            add_function_to_module(progetto,nome_modulo,signature);

                            break;
                        case 2:
                            break;
                        default:
                            break;
                    }
                } while (functions_choice <= 1 || functions_choice > 2);



                break;
            case 2:


                do {
                printf("1) REGISTRA NUOVA CHIAMATA A FUNZIONE\n");
                printf("2) ESCI\n");
                scanf("%d" ,&called_function_choice);
                getchar();

                switch (called_function_choice) {
                    case 1:
                        id_function_called = 0;
                        id_function_calling = 0;
                        do {
                            print_modules_and_functions(progetto);
                            printf("Inserisci ID della funzione chiamante\n");
                            scanf("%d",&id_function_calling);
                            getchar();
                        }while (id_function_calling < 0 || id_function_calling > progetto->n_functions - 1);

                        do {
                            print_modules_and_functions(progetto);
                            printf("Inserisci ID della funzione chiamata\n");
                            scanf("%d",&id_function_called);
                            getchar();
                        } while (id_function_called < 0 || id_function_called > progetto->n_functions - 1);
                        called_function(progetto,id_function_calling,id_function_called);
                        printf("%d\n",progetto->called_functions[id_function_calling][id_function_called]);

                        break;
                    case 2:
                        break;
                    default:
                        break;
                }
        } while (called_function_choice <= 1 || called_function_choice > 2);


        break;
            case 3:
                cycle_paths = NULL;
                file = NULL;
                FILE *file = fopen("cicli.txt", "w");
                cycle_paths = cyclic_call_internal(progetto);
            int i = 0;
                while (cycle_paths[i]!=NULL) {
                    //printf("%s\n",cycle_paths[i]);
                    fprintf(file, "%s\n", cycle_paths[i]);
                    i++;
                }
                fflush(file);


                break;
            case 4:
                exit(0);
            default:
                break;
        }
    } while (1);
}




progetto create_project(char * name, int max_size){

    progetto progetto = (struct _progetto *) malloc(sizeof(struct _progetto));
    progetto->max_size = max_size;
    progetto->name_project = strdup(name);
    progetto->n_functions = 0;
    progetto->n_modules = 0;
    progetto->modules = NULL;

    progetto->called_functions = (bool**) malloc(sizeof(bool*) * max_size);
    for (int i = 0; i < max_size; i++) {
        progetto->called_functions[i] = (bool*) malloc(sizeof(bool) * max_size);
        for (int j = 0; j < max_size; ++j) {
            progetto->called_functions[i][j] = false;
        }
    }

    return progetto;

}
bool add_module_to_project(const char * path_h, char * path_c, bool external,progetto project,char* name){
    module module = (struct _module*) malloc(sizeof(struct _module));
    if(external){
        if (path_h == NULL) return false;
        module->path_h = strdup(path_h);
    }
    if(!external){
        if(path_h == NULL && path_c == NULL) return false;
        module->path_h = strdup(path_h);
        module->path_c = strdup(path_c);
    }
    module->name = strdup(name);

    module->functions = NULL;
    module->external = external;
    module->id_module = project->n_modules;
    project->n_modules ++;


    node_module current = project->modules;



    if (current == NULL) {
        project->modules = (struct _node_module *) malloc(sizeof(struct _node_module));
        project->modules->module = module;
        project->modules->next = NULL;
    } else {
        // Altrimenti, scorrere la lista fino a trovare il primo nodo disponibile
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = (struct _node_module *) malloc(sizeof(struct _node_module));
        current->next->module = module;
        current->next->next = NULL;
    }

    return true;


}
bool add_function_to_module(progetto project, char * module_name,char * function_signature){
    if(project->n_functions > project->max_size) return false;

    node_module modules = project->modules;

    while(strcmp(modules->module->name,module_name) !=0 && modules != NULL){
        modules = modules->next;
    }
    if(modules == NULL) return false;


    function  function = (struct _function *) malloc (sizeof (struct _function));
    function->signature = strdup(function_signature);
    function->id_function = project->n_functions;
    project->n_functions++;

    node_function current = modules->module->functions;

    if (current == NULL) {
        modules->module->functions = (struct _node_function *) malloc(sizeof(struct _node_function));
        modules->module->functions->function = function;
        modules->module->functions->next = NULL;
    } else {

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = (struct _node_function *) malloc(sizeof(struct _node_function));
        current->next->function = function;
        current->next->next = NULL;
    }

    return true;


}
bool called_function(progetto project,int id_chiamante, int id_chiamata){
    if(id_chiamante < 0 || id_chiamata < 0 || id_chiamante >= project->n_functions || id_chiamata >= project->n_functions) return false;

    project->called_functions[id_chiamante][id_chiamata] = true;
    return true;
}
module get_module(progetto progetto){
    int n_moduli = 0;
    node_module current_module = progetto->modules;

    // Conta il numero di moduli nel progetto
    while (current_module != NULL) {
        n_moduli++;
        current_module = current_module->next;
    }

    // Array per contare il numero di chiamate per ogni modulo
    int *chiamate = (int *) malloc(sizeof(int) * n_moduli);
    for (int i = 0; i < n_moduli; i++) {
        chiamate[i] = 0;
    }

    // Mappatura da ID funzione a modulo
    module *mappa_funzione_modulo = (module *) malloc(sizeof(module) * progetto->max_size);

    current_module = progetto->modules;
    int index_module = 0;

    // Associa ogni funzione al modulo a cui appartiene
    while (current_module != NULL) {
        node_function current_function = current_module->module->functions;
        while (current_function != NULL) {
            mappa_funzione_modulo[current_function->function->id_function] = current_module->module;
            current_function = current_function->next;
        }
        current_module = current_module->next;
        index_module++;
    }

    // Conta le chiamate tra i moduli
    for (int id_chiamante = 0; id_chiamante < progetto->max_size; id_chiamante++) {
        for (int id_chiamata = 0; id_chiamata < progetto->max_size; id_chiamata++) {
            if (progetto->called_functions[id_chiamante][id_chiamata]) {
                module modulo_chiamante = mappa_funzione_modulo[id_chiamante];
                module modulo_chiamato = mappa_funzione_modulo[id_chiamata];

                if (modulo_chiamante != modulo_chiamato) {
                    // Incrementa il contatore per il modulo chiamato
                    node_module temp = progetto->modules;
                    int index_chiamato = 0;
                    while (temp != NULL) {
                        if (temp->module == modulo_chiamato) {
                            chiamate[index_chiamato]++;
                            break;
                        }
                        temp = temp->next;
                        index_chiamato++;
                    }
                }
            }
        }
    }

    // Trova il modulo più importante
    int indice_modulo_importante = 0;
    for (int i = 1; i < n_moduli; i++) {
        if (chiamate[i] > chiamate[indice_modulo_importante]) {
            indice_modulo_importante = i;
        }
    }

    // Restituisci il modulo corrispondente
    current_module = progetto->modules;
    for (int i = 0; i < indice_modulo_importante; i++) {
        current_module = current_module->next;
    }

    free(chiamate);
    free(mappa_funzione_modulo);

    return current_module->module;
}
int get_neighbors(progetto progetto, int vertex_id, int* result, int how_many) {
    if (!vertex_exists(progetto, vertex_id) || how_many <= 0)
        return -1;

    int dim = 0;

    for (int j = 0; j < progetto->n_functions; j++) {
        if (progetto->called_functions[vertex_id][j]) {
            result[dim] = j;
            dim++;

            if (dim == how_many) {
                return dim;
            }
        }
    }

    return dim;
}
bool vertex_exists(progetto progetto, int vertex_id) {
    return (vertex_id >= 0 && vertex_id < progetto->n_functions);
}
void findAllPathsUtil(progetto progetto, int u, int dst, int visited[], int path[], int pathLen, int ** allPaths, int *pathCount) {
    // Marca il nodo corrente come visitato e memorizzalo nel percorso attuale
    // Marca il nodo corrente come visitato e memorizzalo nel percorso attuale
    visited[u] = 1;
    path[pathLen] = u;
    pathLen++;

    // Se il nodo corrente è la destinazione, memorizza il percorso trovato
    if (u == dst) {
        for (int i = 0; i < pathLen; i++) {
            allPaths[*pathCount][i] = path[i];
        }
        // Termina il percorso con -1 per indicare la fine
        allPaths[*pathCount][pathLen] = -1;
        (*pathCount)++;
    } else {
        // Esplora i nodi adiacenti al nodo corrente
        for (int v = 0; v < progetto->n_functions; v++) {
            if (progetto->called_functions[u][v] && !visited[v]) {
                findAllPathsUtil(progetto, v, dst, visited, path, pathLen, allPaths, pathCount);
            }
        }
    }

    // Backtracking
    visited[u] = 0;

}
int** exist_cyclic(progetto progetto, int source_id) {
    if(get_function_module(progetto,source_id)->external) return NULL;


    int* visited = (int*)calloc(progetto->n_functions, sizeof(int));
    int* temp_path = (int*)malloc(progetto->n_functions * sizeof(int));
    int** paths = (int**)malloc(progetto->max_size *progetto->n_functions * sizeof(int*));
    int path_count = 0;

    // Inizializza i percorsi con -1 per indicare la fine
    for (int i = 0; i < progetto->max_size * progetto->n_functions; i++) {
        paths[i] = (int*)malloc((progetto->n_functions + 1) * sizeof(int));
        for (int j = 0; j <= progetto->n_functions; j++) {
            paths[i][j] = -1;
        }
    }

    for (int i = 0; i < progetto->n_functions; i++) {
        // Resetta `visited` a zero per ogni nuovo percorso
        memset(visited, 0, progetto->n_functions * sizeof(int));
        findAllPathsUtil(progetto, source_id, i, visited, temp_path, 0, paths, &path_count);

    }
    //printf("%d\n",path_count);
    int dim = 0;
    int** definitive_path = (int**)malloc(progetto->max_size *progetto->n_functions * sizeof(int*));
    for(int i = 0 ; i < path_count; i++) {
        if (!is_a_cycle_path(progetto,paths[i])){
            paths[i] = NULL;
        } else {
            definitive_path[dim] = (int*) malloc(((progetto->n_functions + 1) * sizeof(int)));
            definitive_path[dim] = paths[i] ;

            dim++;
        }
    }



    for (int k = dim; k < progetto->max_size * progetto->n_functions; k++) {
        definitive_path[k] = NULL;
    }
    free(visited);
    free(temp_path);
    free(paths);


    return definitive_path;



}
module get_function_module(progetto progetto, int id_function){
    node_module modules = progetto->modules;
    while (modules != NULL){
        node_function functions = modules->module->functions;

        while (functions != NULL && functions->function->id_function != id_function){
            functions = functions->next;
        }
        if( functions !=NULL && functions->function->id_function == id_function ) return modules->module;

        modules = modules->next;
    }
    return NULL;
}
void print_functions_cycle(progetto my_project , int** paths){
    if (paths != NULL) {
        // Stampa i percorsi trovati
        printf("Percorsi trovati:\n");
        for (int i = 0; i < my_project->max_size; i++) {
            printf("%d\n",i);
            if (paths[i] == NULL) continue;
            for (int j = 0; j < my_project->n_functions && paths[i][j] != -1; j++) {
                printf("%d ", paths[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Nessun percorso trovato o errore nella ricerca.\n");
    }
}
char** cyclic_call_internal(progetto progetto) {

    int max_size = progetto->max_size * progetto->n_functions;

    char** strings_paths = (char**) malloc(max_size * sizeof(char*));
    if (strings_paths == NULL) {
        perror("Failed to allocate memory for strings_paths");
        exit(EXIT_FAILURE);
    }

    int j = 0;

    for (int i = 0; i < progetto->n_functions; i++) {
        int** int_path = exist_cyclic(progetto, i);
        if (int_path == NULL) continue;

        int k = 0;
        while (int_path[k] != NULL) {
            char* path_str = path_to_string(progetto,int_path[k]);
            if (path_str != NULL) {
                strings_paths[j] = path_str;
                printf("%s\n", strings_paths[j]);
                j++;
            }
            k++;
        }

    }

    for (int v = j; v < max_size; v++) {
        strings_paths[v] = NULL;
    }

    return strings_paths;

}



char* path_to_string(progetto progetto ,int* path) {
    if (path == NULL || path[0] == -1) return NULL;

    // Step 1: Calculate the length needed for the output string
    int len = 0;
    for (int i = 0; path[i] != -1; i++) {
        module mod = get_function_module(progetto, path[i]);
        node_function func_node = mod ? mod->functions : NULL;
        char* signature = NULL;
        while (func_node != NULL && func_node->function->id_function != path[i]) {
            func_node = func_node->next;
        }
        if (func_node != NULL) {
            signature = func_node->function->signature;
        }
        if (mod && signature) {
            len += snprintf(NULL, 0, "%s (%s) -> ", signature, mod->name);
        }
    }
    if (len > 0) {
        len -= 4; // Adjust length for the last " -> "
    }
    char * signature = get_function_by_id(progetto,path[0])->function->signature;
    char * module_name = get_function_module(progetto,path[0])->name;

    size_t len1 = strlen(" -> ");
    size_t len2 = strlen(signature);
    size_t len3 = strlen(" ");
    size_t len4 = strlen("(");
    size_t len5 = strlen(module_name);
    size_t len6 = strlen(")");
    size_t total_len = len1 + len2 + len3 + len4 + len5 + len6 + 1;

    // Step 2: Allocate memory for the output string
    char* str = (char*)malloc(total_len + len + 1); // +1 for the null terminator
    if (str == NULL) {
        perror("Failed to allocate memory for path string");
        exit(EXIT_FAILURE);
    }

    // Step 3: Format the string
    int pos = 0;
    for (int i = 0; path[i] != -1; i++) {
        module mod = get_function_module(progetto, path[i]);
        node_function func_node = mod ? mod->functions : NULL;
        char* signature = NULL;
        while (func_node != NULL && func_node->function->id_function != path[i]) {
            func_node = func_node->next;
        }
        if (func_node != NULL) {
            signature = func_node->function->signature;
        }
        if (mod && signature) {
            pos += sprintf(str + pos, "%s (%s) -> ", signature, mod->name);
        }
    }
    str[pos - 4] = '\0';

    //printf("%s\n",add_string_cycle(progetto,str,path[0]));



    return add_string_cycle(progetto,str,path[0]);
}
bool is_a_cycle_path(progetto progetto, int * path){
    if (path == NULL) return false;

    int i = 0;
    while (i < progetto->n_functions && path[i] != -1) {
        module mod = get_function_module(progetto, path[i]);
        if (mod == NULL || mod->external) {
            // Se mod è NULL, evita di accedere a locazioni di memoria non valide

            return false;
        }
        i++;
    }


    if (path[i] == -1) {
        if (progetto->called_functions[path[i - 1]][path[0]]) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
void print_string_array(char **array) {
    int i = 0;
    if(array[i] == NULL) return;
    while (array[i] != NULL){
        printf("%s\n",array[i]);
        i++;
    }
}
char* project_structure(progetto progetto){

    char * structure = (char*) malloc(sizeof(char) * 1000);
    structure[0] = '\0';
    int * indexes = malloc(sizeof(int) * progetto->n_modules);
    int j;

    node_module modules = progetto->modules;



    while(modules != NULL){
        if(!modules->module->external) {
            strcat(structure, "-  ");
            strcat(structure, modules->module->name);
            strcat(structure, "\n");
            strcat(structure, "  Funzioni:\n");

            node_function functions = modules->module->functions;
            while (functions != NULL) {
                strcat(structure, "   - ");
                strcat(structure, functions->function->signature);
                strcat(structure, "\n");

                functions = functions->next;
            }
            strcat(structure, "  Moduli dipendenti:\n");

            node_function called_function = modules->module->functions;
            int n_functions;
             j = 0;

            while(called_function != NULL) {
                n_functions = progetto->n_functions - 1;
                while (n_functions >= 0) {
                    if (progetto->called_functions[called_function->function->id_function][n_functions] &&
                        get_function_module(progetto, n_functions) != modules->module && !is_already_printed(get_function_module(progetto, n_functions)->id_module,indexes,j)) {

                        strcat(structure, "    -> ");
                        strcat(structure, get_function_module(progetto, n_functions)->name);
                        if (get_function_module(progetto, n_functions)->external) strcat(structure, "  (esterno)");
                        strcat(structure, "\n");

                        indexes[j] = get_function_module(progetto, n_functions)->id_module;
                        j++;
                    }
                    n_functions--;
                }
                called_function = called_function->next;
            }
        }
        reset(indexes,j);
        modules = modules->next;
    }
    return structure;
}
bool is_already_printed(int index, const int * indexes, int dim){
    for(int i = 0 ; i < dim ; i++){
        if(indexes[i] == index) return true;
    }
    return false;
}
void reset(int * array, int dim){
    for(int i = 0 ; i < dim ; i++){
        array[i] = -1;
    }
}
void print_modules(progetto progetto){
    if(progetto->n_modules == 0) return;

    node_module modules = progetto->modules;

    for(int i = 0; i < progetto->n_modules;i++){
        printf("%s\n",modules->module->name);
        modules = modules->next;
    }
}
void print_modules_and_functions(progetto progetto){
    node_module modules = progetto->modules;

    while (modules != NULL) {
        printf("- Module: %s\n", modules->module->name);
        printf("  Functions:\n");

        node_function functions = modules->module->functions;
        while (functions != NULL) {
            printf("    - Function: %s\n", functions->function->signature);
            printf("      ID: %d\n", functions->function->id_function);

            functions = functions->next;
        }

        modules = modules->next;
    }
    }
node_function get_function_by_id(progetto progetto,int id){
    node_module modules = progetto->modules;
    while (modules != NULL){
        node_function nodeFunction = modules->module->functions;
        while (nodeFunction != NULL){
            if(nodeFunction->function->id_function == id) return nodeFunction;
            nodeFunction = nodeFunction->next;
        }
        modules = modules->next;
    }
    return NULL;
}
char * add_string_cycle(progetto progetto,char * str, int id){

    char * signature = get_function_by_id(progetto,id)->function->signature;
    char * module_name = get_function_module(progetto,id)->name;

    size_t len1 = strlen(" -> ");
    size_t len2 = strlen(signature);
    size_t len3 = strlen(" ");
    size_t len4 = strlen("(");
    size_t len5 = strlen(module_name);
    size_t len6 = strlen(")");
    size_t total_len = len1 + len2 + len3 + len4 + len5 + len6 + 1;


    char * temp = (char*) malloc(total_len * sizeof(char) );
    temp[0] = '\0';

    strcat(temp," -> ");
    strcat(temp,signature);
    strcat(temp," ");
    strcat(temp,"(");
    strcat(temp,module_name);
    strcat(temp,")");
    strcat(str,temp);

    return str;
}
