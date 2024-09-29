#ifndef SPRING_FINDER_H
#define SPRING_FINDER_H
typedef struct vertex
{
    int number;
    double x;
    double y;
} vertex_t;

typedef struct line
{
    int number;
    int start;
    int end;
} line_t;

//main.c

void generate_archimedian_spiral(int rounds, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines);

//mesh_rw.c
int write_mesh_data(char* mesh_file_name, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines);
int read_mesh_data(char* mesh_file_name, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines);
#endif //SPRING_FINDER_H
