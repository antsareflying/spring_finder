
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

#include "spring_finder.h"
int main(void)
{
    int num_vertices = 21;
    int num_lines = 20;
    char* default_msh_file = "mesh.mesh";
    char* mesh_file_name = default_msh_file;

    vertex_t* vertices = calloc(num_vertices, sizeof(vertex_t));
    line_t* lines = calloc(num_lines, sizeof(line_t));


    generate_archimedian_spiral(3,
        vertices,
        num_vertices,
        lines,
        num_lines);

    // write vertices and lines to mesh file, 0 indexed
    write_mesh_data(mesh_file_name,
                    vertices,
                    num_vertices,
                    lines,
                    num_lines);

    read_mesh_data(mesh_file_name,
                    vertices,
                    num_vertices,
                    lines,
                    num_lines);

    free(vertices);
    free(lines);
    return 0;
}


void generate_archimedian_spiral(int rounds, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines)
{
    double angle_step = rounds * 2 * M_PI / size_vertices;
    for (int t = 0; t < size_vertices; t++)
    {
        double angle = angle_step * (float)t;
        const double a = 1.5;
        const double b = 1.5;
        vertices[t].number = t;
        vertices[t].x = (a + b*angle)*cos(angle);
        vertices[t].y = (a + b*angle)*sin(angle);
    }
    for (int i = 0; i < size_lines; i++)
    {
        lines[i].number = i;
        lines[i].start = i;
        lines[i].end = i+1;
    }
}