#include <stdio.h>
#include <stdlib.h>

#include "spring_finder.h"

FILE* open_file(char* file_name)
{
    FILE* file = fopen(file_name, "a+");
    if (file == NULL)
    {
        fprintf(stderr,"File unable to be opened/made.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "File opened.\n");
    return file;
}

//read from file
int read_file(char *mesh_file_name)
{
    open_file(mesh_file_name);

    return 0;
}


//write vertex data in this format: vertex number, space, x pos, space, y pos
int write_vertex(FILE* mesh_file, int vertex_no, vertex_t vertex)
{
    char write_buffer[100] = {0};
    snprintf(write_buffer, sizeof(write_buffer),
        "%d %f %f\n", vertex_no, vertex.x, vertex.y);
    fprintf(mesh_file, write_buffer);
    return 0;
}

//write vertex data in this format: line number, space, start vertex, space, end vertex
int write_line(FILE* mesh_file, int line_no, line_t line)
{
    char write_buffer[100] = {0};
    snprintf(write_buffer, sizeof(write_buffer),
        "%d %d %d\n", line_no, line.start, line.end);
    fprintf(mesh_file, write_buffer);
    return 0;
}
