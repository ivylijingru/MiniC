typedef enum
{
    REDEFINE,
    REDECLARE,
    NOT_DEFINE,
    ARRAY_OUTOFRANGE,
    PARAMERROR
}ErrorKind;

void handle_error(ErrorKind s, char* name, int lineno);

