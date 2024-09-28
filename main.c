
#include <stdio.h>
#include <tgmath.h>

#include "spring_finder.h"
int main(void)
{
    vertex_t vertices[21];
    line_t lines[20];
    char* default_msh_file = "mesh.mesh";
    char* mesh_file_name = default_msh_file;

    generate_archimedian_spiral(5,
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

int write_mesh_data(char* mesh_file_name, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines)
{
    const char* msh_file_header = "mesh file ver = 1\n";
    FILE* msh_file_ptr = open_file(mesh_file_name);

    fprintf(msh_file_ptr, msh_file_header);
    fprintf(msh_file_ptr, "Vertex\n");
    for (int i = 0; i < size_vertices; i++)
    {
        write_vertex(msh_file_ptr, i, vertices[i]);
    }

    fprintf(msh_file_ptr, "Line\n");
    for (int i = 0; i < size_lines; i++)
    {
        write_line(msh_file_ptr, i, lines[i]);
    }
    return 0;
}

void generate_archimedian_spiral(int rounds, vertex_t* vertices, int size_vertices, line_t* lines, int size_lines)
{
    float angle_step = rounds * 2 * M_PI / size_vertices;
    for (int t = 0; t < size_vertices; t++)
    {
        float angle = angle_step * (float)t;
        const float a = 1.5f;
        const float b = 1.5f;
        vertices[t].x = (a + b*angle)*cos(angle);
        vertices[t].y = (a + b*angle)*sin(angle);
    }
    for (int i = 0; i < size_lines; i++)
    {
        lines[i].start = i;
        lines[i].end = i+1;
    }
}