#ifndef SPRING_FINDER_H
#define SPRING_FINDER_H
typedef struct vertex
{
    float x;
    float y;
} vertex_t;

typedef struct line
{
    int start;
    int end;
} line_t;

//main.c
int write_mesh_data(char* mesh_file_name, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines);
void generate_archimedian_spiral(int rounds, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines);

//mesh_rw.c
FILE* open_file(char* file_name);
int read_file(char *mesh_file_name);
int write_vertex(FILE* mesh_file, int vertex_no, vertex_t vertex);
int write_line(FILE* mesh_file, int line_no, line_t line);
#endif //SPRING_FINDER_H
