#include <stdbool.h>

typedef struct _progetto * progetto;
typedef struct _module * module;
typedef struct _function * function;
typedef struct _node_module * node_module;
typedef struct _node_function * node_function;

progetto create_project(char * name, int max_size);
bool add_module_to_project(const char * path_h, char * path_c, bool external,progetto project,char* name);
bool add_function_to_module(progetto project, char * module_name,char * function_signature);
bool called_function(progetto project,int id_chiamante, int id_chiamata);
module get_module(progetto progetto);
char** cyclic_call_internal(progetto progetto);
char* project_structure(progetto progetto);
int** exist_cyclic(progetto progetto, int source_id);
void findAllPathsUtil(progetto progetto, int u, int dst, int visited[], int path[], int pathLen, int ** allPaths, int *pathCount);
module get_function_module(progetto progetto, int id_function);
void print_functions_cycle(progetto my_project , int** paths);
bool vertex_exists(progetto progetto, int vertex_id);
char* path_to_string(progetto progetto,int* path);
bool is_a_cycle_path(progetto progetto, int * path);
void print_string_array(char **array);
bool is_already_printed(int index, const int * indexes, int dim);
void reset(int * array, int dim);
void print_modules(progetto progetto);
void print_modules_and_functions(progetto progetto);
node_function get_function_by_id(progetto progetto,int id);
char * add_string_cycle(progetto progetto,char * str, int id);

