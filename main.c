
#include <stdio.h>
#include <tgmath.h>

#include "spring_finder.h"
int main(void)
{
    vertex_t vertices[21];
    line_t lines[20];
    char* default_msh_file = "mesh.mesh";
    char* mesh_file_name = default_msh_file;

    generate_archimedian_spiral(3,
        vertices,
        sizeof(vertices)/sizeof(vertices[1]),
        lines,
        sizeof(lines)/sizeof(lines[1]));

    // write vertices and lines to mesh file, 0 indexed
    write_mesh_data(mesh_file_name,
                    vertices,
                    sizeof(vertices)/sizeof(vertices[1]),
                    lines,
                    sizeof(lines)/sizeof(lines[1]));
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
        vertices[t].x = (a + b*angle)*cos(angle);
        vertices[t].y = (a + b*angle)*sin(angle);
    }
    for (int i = 0; i < size_lines; i++)
    {
        lines[i].start = i;
        lines[i].end = i+1;
    }
}