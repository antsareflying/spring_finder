#ifndef SPRING_FINDER_H
#define SPRING_FINDER_H
typedef struct vertex
{
    double x;
    double y;
} vertex_t;

typedef struct line
{
    int start;
    int end;
} line_t;

//main.c

void generate_archimedian_spiral(int rounds, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines);

//mesh_rw.c
FILE* open_file(char* file_name);
int read_file(char *mesh_file_name);
int write_vertex(FILE* mesh_file, int vertex_no, vertex_t vertex);
int write_line(FILE* mesh_file, int line_no, line_t line);
int write_mesh_data(char* mesh_file_name, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines);
#endif //SPRING_FINDER_H
