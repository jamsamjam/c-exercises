#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 128

typedef int Element;

typedef struct {
    size_t capacity;
    size_t size;
    Element *content;
} DynamicArray;

DynamicArray *construct(DynamicArray *arr)
{
    arr->capacity = CHUNK_SIZE;
    arr->size = 0;
    arr->content = calloc(CHUNK_SIZE, sizeof(Element));
    if (arr->content == NULL) return NULL;
    return arr;
}

DynamicArray *resize(DynamicArray *arr)
{
    if (arr == NULL) return NULL;

    size_t old_capacity = arr->capacity;
    arr->capacity += CHUNK_SIZE;
    Element *new_content = realloc(arr->content, arr->capacity * sizeof(Element));

    if (new_content == NULL) {
        arr->capacity -= CHUNK_SIZE;
        return NULL;
    }

    for (size_t i = old_capacity; i < arr->capacity; i++) {
        new_content[i] = 0;
    }

    arr->content = new_content;
    return arr;
}

size_t push(DynamicArray *arr, Element e)
{
    if (arr == NULL) return 0;

    if (arr->size >= arr->capacity) {
        if (resize(arr) == NULL) {
            return 0;
        }
    }

    arr->content[arr->size++] = e;
    return arr->size;
}

void delete(DynamicArray *arr)
{
    if (arr == NULL || arr->content == NULL) return;

    free(arr->content);
    arr->capacity = 0;
    arr->size = 0;
    arr->content = NULL;
}

int main(void)
{
    DynamicArray arr;

    if (construct(&arr) == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Array size: %zu, Capacity: %zu\n", arr.size, arr.capacity);


    push(&arr, 10);
    push(&arr, 20);
    push(&arr, 30);

    printf("arr[0] = %d\n", arr.content[0]);
    printf("arr[1] = %d\n", arr.content[1]);
    printf("arr[2] = %d\n", arr.content[2]);
    printf("Array size: %zu, Capacity: %zu\n", arr.size, arr.capacity);

    delete(&arr);
    printf("Array size: %zu, Capacity: %zu\n", arr.size, arr.capacity);


    return 0;
}