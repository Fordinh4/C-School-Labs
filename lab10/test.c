#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int *head;    // Start of dynamic storage
    int *start;   // Index 0 of ring buffer
    int *end;     // One after the last element in the ring buffer
    int length;   // Number of elements currently stored in the ring buffer
    int capacity; // Maximum number of elements this ring buffer can hold
} Ring;

Ring *ring_create(void) {
    Ring *ring = (Ring *)malloc(sizeof(Ring));
    ring->head = (int *)malloc(sizeof(int) * 2);
    ring->start = ring->head;
    ring->end = ring->head;
    ring->length = 0;
    ring->capacity = 2;
    return ring;
}

void resizeRing(Ring *ring)
{
    // Idea:: Make a new larger one (that’s empty), then iterate from the start to the end and “place the old things into the new list”
    int new_capacity = ring->capacity * 2;
    int *new_head = (int *)malloc(sizeof(int) * new_capacity);

    // Copy the elements to the new buffer in a vectorized manner
    for (int i = 0; i < ring->length; i++)
    {
        int circular_idx = (ring->start - ring->head + i) % ring->capacity;
        new_head[i] = ring->head[circular_idx];
    }

    // Free the old buffer and update pointers
    free(ring->head);
    ring->head = new_head;
    ring->start = new_head;
    ring->end = new_head + ring->length;
    ring->capacity = new_capacity;
}


void ring_push_front(Ring *ring, int student_id) {
    if (ring->length == ring->capacity) {
        resizeRing(ring);
    }
    ring->start = (ring->start == ring->head) ? ring->head + ring->capacity - 1 : ring->start - 1;
    *(ring->start) = student_id;
    ring->length++;
}

void ring_push_back(Ring *ring, int student_id) {
    if (ring->length == ring->capacity) {
        resizeRing(ring);
    }
    *ring->end = student_id;
    ring->end++;
    if (ring->end >= ring->head + ring->capacity)
    {
        ring->end = ring->head; // Wrap around
    }
    ring->length++;
}

int ring_pop_front(Ring *ring) {
    if (ring->length == 0) {
        return -1;
    }
    int student_id = *(ring->start);
    ring->start++;
    if (ring->start >= ring->head + ring->capacity)
    {
        ring->start = ring->head; // Wrap around
    }
    ring->length--;
    return student_id;
}
int ring_pop_back(Ring *ring) {
    if (ring->length == 0)
    {
        return -1; // Empty ring buffer
    }

    ring->end--; // Move back the end pointer
    if (ring->end < ring->head)
    {
        ring->end = ring->head + ring->capacity - 1; // Wrap around
    }

    int removed_id = *ring->end; // Get the student ID from the end
    ring->length--;

    return removed_id;
}


void rebalance_rings(Ring *front, Ring *back) {
    while (front->length < back->length) {
        ring_push_front(front, ring_pop_back(back));
    }

    while (front->length > back->length + 1) {
        ring_push_back(back, ring_pop_front(front));
    }
}

void n_queue(Ring *front, Ring *back, int i, int student_id) {
    if (front->length + back->length < i) {
        ring_push_back(back, student_id);
    }
    rebalance_rings(front, back);
}

void c_queue(Ring *front, Ring *back, int i, int student_id) {
    int total_length = front->length + back->length;
    int position = (front->length + back->length + 1) / 2;

    if (position < i) {
        ring_push_back(front, student_id); // CMPUT student joins the front ring
    } else if (total_length < i) {
        ring_push_back(back, student_id); // CMPUT student joins the back ring
    }
}


void l_dequeue(Ring *front, Ring *back) {
    if (back->length > 0) {
        ring_pop_back(back);
    } else if (front->length > 0) {
        ring_pop_back(front);
    }
    rebalance_rings(front, back);
}

void f_dequeue(Ring *front, Ring *back) {
    if (front->length > 0) {
        printf("%d\n", ring_pop_front(front));
    } else if (back->length > 0) {
        printf("%d\n", ring_pop_front(back));
    } else {
        printf("empty\n");
    }
    rebalance_rings(front, back);
}



void process_command(Ring *front, Ring *back, char *command) {
    char type;
    int x, student_id;
    if (sscanf(command, "%c %d %d", &type, &x, &student_id) > 1) {
        if (type == 'N') {
            n_queue(front, back, x, student_id);
        } else if (type == 'C') {
            c_queue(front, back, x, student_id);
        }
    } else if (sscanf(command, "%c", &type) == 1) {
        if (type == 'F') {
            f_dequeue(front, back);
        } else if (type == 'L') {
            l_dequeue(front, back);
        }
    }
}

int main() {
    int x = 007; 
    printf("%3d", &x);

}
