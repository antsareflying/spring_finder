#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int close_file(FILE* file)
{
    if(fclose(file) == EOF)
    {
        fprintf(stderr,"File not closed.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "File closed.\n");
    return 0;
}

//write vertex data in this format: vertex number, space, x pos, space, y pos
int write_vertex(FILE* mesh_file, vertex_t vertex)
{
    char write_buffer[100] = {0};
    snprintf(write_buffer, sizeof(write_buffer),
        "%d %f %f\n", vertex.number, vertex.x, vertex.y);
    fprintf(mesh_file, write_buffer);
    return 0;
}

//write line data in this format: line number, space, start vertex, space, end vertex
int write_line(FILE* mesh_file, line_t line)
{
    char write_buffer[100] = {0};
    snprintf(write_buffer, sizeof(write_buffer),
        "%d %d %d\n", line.number, line.start, line.end);
    fprintf(mesh_file, write_buffer);
    return 0;
}

int write_mesh_data(char* mesh_file_name, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines)
{
    const char* msh_file_header = "mesh file ver = 1\n";
    FILE* msh_file_ptr = open_file(mesh_file_name);

    fprintf(msh_file_ptr, msh_file_header);
    fprintf(msh_file_ptr, "Vertex %d\n", size_vertices);
    for (int i = 0; i < size_vertices; i++)
    {
        write_vertex(msh_file_ptr, vertices[i]);
    }

    fprintf(msh_file_ptr, "Line %d\n", size_lines);
    for (int i = 0; i < size_lines; i++)
    {
        write_line(msh_file_ptr, lines[i]);
    }

    close_file(msh_file_ptr);
    return 0;
}

int read_mesh_data(char* mesh_file_name, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines)
{
    FILE* mesh_file_ptr = open_file(mesh_file_name);
    char read_buffer[100] = {0};
    //read and get file version number, see if it is 1
    fgets(read_buffer, sizeof(read_buffer), mesh_file_ptr);
    char version_no[] = {read_buffer[16], 0};
    if (strcmp(version_no, "1") != 0)
    {
        fprintf(stderr, "Wrong version number.\n");
        close_file(mesh_file_ptr);
        exit(EXIT_FAILURE);
    }

    //read and get vertex header, number of vertices to follow
    memset(read_buffer, 0, sizeof(read_buffer));
    fgets(read_buffer, sizeof(read_buffer), mesh_file_ptr);
    char* result = strchr(read_buffer, ' ');
    if (result == NULL)
    {
        fprintf(stderr, "Number of vertices not found while reading file.\n");
        close_file(mesh_file_ptr);
        exit(EXIT_FAILURE);
    }
    int num_vertices = strtol(result, NULL, 10);

    //read vertex data into memory
    for (int i = 0; i < num_vertices; i++)
    {
        memset(read_buffer, 0, sizeof(read_buffer));
        fgets(read_buffer, sizeof(read_buffer), mesh_file_ptr);
        char* next_token;
        char* token = strtok_s(read_buffer, " ", &next_token);
        vertices[i].number = strtol(token, NULL, 10);
        vertices[i].x = strtod(strtok_s(NULL, " ", &next_token), NULL);
        vertices[i].y = strtod(strtok_s(NULL, " ", &next_token), NULL);
    }

    //read and get line header, number of lines to follow
    memset(read_buffer, 0, sizeof(read_buffer));
    fgets(read_buffer, sizeof(read_buffer), mesh_file_ptr);
    result = strchr(read_buffer, ' ');
    if (result == NULL)
    {
        fprintf(stderr, "Number of vertices not found while reading file.\n");
        close_file(mesh_file_ptr);
        exit(EXIT_FAILURE);
    }
    int num_lines = strtol(result, NULL, 10);

    //read line data into memory
    for (int i = 0; i < num_lines; i++)
    {
        memset(read_buffer, 0, sizeof(read_buffer));
        fgets(read_buffer, sizeof(read_buffer), mesh_file_ptr);
        char* next_token;
        char* token = strtok_s(read_buffer, " ", &next_token);
        lines[i].number = strtol(token, NULL, 10);
        lines[i].start = strtol(strtok_s(NULL, " ", &next_token), NULL, 10);
        lines[i].end = strtol(strtok_s(NULL, " ", &next_token), NULL, 10);
    }

    close_file(mesh_file_ptr);
    return 0;
}