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
int* exist_cyclic(progetto progetto, int source_id);

