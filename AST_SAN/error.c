#include "error.h"
#include <stdio.h>
#include <stdlib.h>
void handle_error(ErrorKind s, char *name, int lineno) {
    switch(s) {
        case REDEFINE: 
            printf("redefinition symbol '%s' at line %d\n", name, lineno); 
            exit(-1);
        case REDECLARE: 
            printf("redeclare function '%s' at line %d\n", name, lineno);
            exit(-1);
        case NOT_DEFINE: 
            printf("variable '%s' used before define at line %d\n", name, lineno); 
            exit(-1);
        case PARAMERROR:
            printf("function %s has wrong param number when calling at line %d\n", name, lineno);
            exit(-1);
        default: exit(-1);
    }
}
