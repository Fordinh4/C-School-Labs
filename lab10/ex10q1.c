#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int *head;    // Start of dynamic storage
    int *start;   // Index 0 of ring buffer
    int *end;     // One after the last element in the ring buffer
    int length;   // Number of elements currently stored in the ring buffer
    int capacity; // Maximum number of elements this ring buffer can hold
} Ring;

Ring *ring_create(void)
{
    // ring -> length = (*ring).length = (*&a).length = ring.length
    // Allocates memory for a new Ring structure and assigns its address to the pointer ring.
    Ring *ring = (Ring *)malloc(sizeof(Ring));

    ring->head = (int *)malloc(sizeof(int) * 2); // Pointer to the actual array

    // Set start and end pointers to the beginning of the allocated array.
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
    int *new_head = (int *)calloc(new_capacity, sizeof(int));

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

void ring_add(Ring *ring, int student_id)
{
    if (ring->length == ring->capacity)
    {
        // Resize the ring if necessary
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

int ring_remove(Ring *ring)
{
    if (ring->length == 0)
    {
        return -1; // or some error code
    }

    int removed_id = *ring->start;
    ring->start++;
    if (ring->start >= ring->head + ring->capacity)
    {
        ring->start = ring->head; // Wrap around
    }
    ring->length--;

    return removed_id;
}

// Removes a student from the end of the ring
int ring_remove_from_end(Ring *ring)
{

    ring->end--; // Move back the end pointer
    if (ring->end < ring->head)
    {
        ring->end = ring->head + ring->capacity - 1; // Wrap around
    }

    int removed_id = *ring->end; // Get the student ID from the end
    ring->length--;

    return removed_id;
}

// Adds a student to the start of the ring
void ring_add_to_start(Ring *ring, int student_id)
{
    if (ring->length == ring->capacity)
    {
        // Resize the ring if necessary
        resizeRing(ring);
    }

    if (ring->start == ring->head)
    {
        ring->start = ring->head + ring->capacity - 1; // Wrap around
    }
    else
    {
        ring->start--; // Move back the start pointer
    }

    *ring->start = student_id; // Add the student ID at the start
    ring->length++;
}

void rebalance_rings(Ring *front, Ring *back) {
    // If back has more students, move from start of back to end of front
    while (front->length < back->length) {
        int student_id = ring_remove(back); // Remove from start of back
        ring_add(front, student_id);        // Add to the end of front
    }

    // If front has more than one extra student, move from end of front to start of back
    while (front->length > back->length + 1) {
        int student_id = ring_remove_from_end(front); // Remove from end of front
        ring_add_to_start(back, student_id);          // Add to the start of back
    }
}


void process_command(Ring *front, Ring *back, char *command)
{
    char type;
    int x, student_id;
    if (sscanf(command, "%c %d %d", &type, &x, &student_id) > 1)
    {
        // It's either an N or a C command

        if (type == 'N')
        {
            // Add non-CMPUT 201 student to the back ring
            if (x > (front->length + back->length))
            {
                ring_add(back, student_id);
            }
        }
        else if (type == 'C')
        {
            int total_length = front->length + back->length;
            int position = (front->length + back->length + 1) / 2;
            if (position < x)
            {
                ring_add(front, student_id); // CMPUT student joins the front ring
            }
            else if (total_length < x)
            {
                ring_add(back, student_id); // CMPUT student joins the back ring
            }
        }
    }
    else if (sscanf(command, "%c", &type) == 1)
    {
        if (type == 'F')
        {
            // Handle autograph (remove from front)
            if (front->length > 0)
            {
                printf("%d\n", ring_remove(front));
            }
            else if (back->length > 0)
            {
                printf("%d\n", ring_remove(back));
            }
            else
            {
                printf("empty\n");
            }
        }
        else if (type == 'L')
        {
            // Handle last person leaving (remove from back)
            if (back->length > 0)
            {
                ring_remove_from_end(back); // Assuming we don't need to print this ID
            }
        }
    }

    // Balancing the rings
    rebalance_rings(front, back);
}

int main()
{
    Ring *front = ring_create();
    Ring *back = ring_create();

    char command[50];

    while (fgets(command, sizeof(command), stdin) != NULL)
    {
        // Directly process the command using the buffer
        process_command(front, back, command);

        // ISSUE WITH CAPACITY AND LENGTH LEAD TO OVERWRITE THE INFO
        // DEBUG PRINT:
        // printf("\nThis is the front rings: ");

        // for (int i = 0; i < front->capacity; i++)
        // {
        //     printf("%d -> ", *((front -> head) + i));
        // }

        // printf("\nFRONT || start -> %d | end -> %d | LENGTH: %d | CAPACITY: %d\n", *(front->start), *(front->end), front->length, front->capacity);

        // printf("\n");

        // printf("This is the back rings: ");
        // for (int i = 0; i < back->capacity; i++)
        // {
        //     printf("%d -> ", *((back -> head) + i));
        // }

        // printf("\nBACK || start -> %d | end -> %d | LENGTH: %d | CAPACITY: %d\n", *(back->start), *(back->end), (back->length), (back->capacity));
        // printf("\n===================================\n");
    }

    // Clean up
    free(front->head);
    free(front);
    free(back->head);
    free(back);
}
