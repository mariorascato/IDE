#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "IDE.h"

struct _progetto{
    char * name_project;
    int n_functions;
    int max_size;
    node_module  modules;
    bool** called_functions;
};
struct _module{
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
    progetto progetto = create_project("Calcolatrice",50);

    printf("%s\n",progetto->name_project);

    add_module_to_project("pippo.h","pippo.c",false,progetto,"pippo");
    add_module_to_project("malloc.h",NULL,true,progetto,"malloc");

    printf("%s\n",progetto->modules->module->name);
    printf("%s\n",progetto->modules->next->module->name);

    add_function_to_module(progetto,"pippo","void stampa(char* str)");
    add_function_to_module(progetto,"pippo","void scrivi(char* str)");
    add_function_to_module(progetto,"malloc","void alloca(void * ptr)");
    add_function_to_module(progetto,"pippo","void sposta(el * element)");
    printf("%d\n",progetto->modules->module->functions->function->id_function);
    printf("%s\n",progetto->modules->next->module->functions->function->signature);
    called_function(progetto,0,2);
    called_function(progetto,0,3);
    called_function(progetto,1,3);
    called_function(progetto,2,0);
    called_function(progetto,1,2);


    printf("%s\n", get_module(progetto)->name);

}
progetto create_project(char * name, int max_size){

    progetto progetto = (struct _progetto *) malloc(sizeof(struct _progetto));
    progetto->max_size = max_size;
    progetto->name_project = strdup(name);
    progetto->n_functions = 0;
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

