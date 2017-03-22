#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pqueue.h"
#include "union_find.h"

graph_t kruskal(graph_t graph) {

    elem_t elem = NULL;
    uint l = 0;
    uint r = 0;

    uint vertices_count = graph_vertices_count(graph);
    graph_t gr = graph_empty(vertices_count);
    edge_t *edges = graph_edges(graph);
    union_find_t uf = union_find_create(vertices_count);

    uint edges_count = graph_edges_count(graph);
    pqueue_t pq = pqueue_empty(edges_count);

    for (uint i = 0; i < edges_count; i++) {

        pqueue_enqueue(pq, edges[i]);

    }

    while (!pqueue_is_empty(pq) && union_find_count(uf) > 1) {

        elem = edge_copy(pqueue_fst(pq));

        l = union_find_find(uf, vertex_label(edge_left_vertex(elem)));
        r = union_find_find(uf, vertex_label(edge_right_vertex(elem)));


        if (!union_find_connected(uf, l, r)) {

            elem = edge_set_primary(elem, true);
            union_find_union(uf, l, r);

        }

        gr = graph_add_edge(gr, elem);
        pqueue_dequeue(pq);

    }

    while (!pqueue_is_empty(pq)) {

        elem = edge_copy(pqueue_fst(pq));
        gr = graph_add_edge(gr, elem);
        pqueue_dequeue(pq);

    }

    pq = pqueue_destroy(pq);
    uf = union_find_destroy(uf);

    free(edges);
    edges = NULL;
    elem = NULL;

    return gr;

}

unsigned int mst_total_weight(graph_t mst) {

    uint sum = 0;
    uint count = graph_edges_count(mst);
    edge_t *edges = graph_edges(mst);
    elem_t elem = NULL;

    for (uint i = 0; i < count; i++) {

        elem = edges[i];

        if (edge_is_primary(elem)) {

            sum += edge_weight(elem);

        }

    }

    for (uint i = 0; i < count; i++) {

        edges[i] = edge_destroy(edges[i]);

    }

    free(edges);
    edges = NULL;
    elem = NULL;

    return sum;

}

#ifndef TEST

int main(void) {
    /* read graph from stdin */
    graph_t graph = graph_from_file(stdin);
    assert(graph != NULL);
    /* run kruskal */
    graph_t mst = kruskal(graph);
    /* dump graph */
    graph_dump(mst, stdout);
    /* dump total weight */
    printf("\n# MST : %u\n", mst_total_weight(mst));
    /* destroy both graphs */
    graph = graph_destroy(graph);
    mst = graph_destroy(mst);
}

#endif