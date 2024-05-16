
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *strdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *dst = (char *)malloc(len);
    if (dst != NULL) {
        strcpy(dst, src);
    }
    return dst;
}

struct List_Repr {
    string *items;
    size_t length;
    size_t capacity;
};

static void resize_list(list l, size_t new_capacity) {
    l->items = (string *)realloc(l->items, new_capacity * sizeof(string));
    l->capacity = new_capacity;
}

list list_create(void) {
    list new_list = (list)malloc(sizeof(struct List_Repr));
    if (new_list != NULL) {
        new_list->length = 0;
        new_list->capacity = 10;
        new_list->items = (string *)malloc(new_list->capacity * sizeof(string));
        if (new_list->items == NULL) {
            free(new_list);
            return NULL;
        }
    }
    return new_list;
}

void list_destroy(list l) {
    if (l != NULL) {
        for (size_t i = 0; i < l->length; i++) {
            free(l->items[i]);
        }
        free(l->items);
        free(l);
    }
}

bool list_is_empty(list l) {
    return (l == NULL || l->length == 0);
}

size_t list_length(list l) {
    if (l == NULL) return 0;
    return l->length;
}

static void check_resize(list l) {
    if (l->length >= l->capacity) {
        resize_list(l, l->capacity * 2);
    }
}

void list_push(list l, string item) {
    if (l == NULL || item == NULL) return;
    check_resize(l);
    l->items[l->length++] = strdup(item);
}

string list_pop(list l) {
    if (l == NULL || l->length == 0) return NULL;
    string item = l->items[--l->length];
    l->items[l->length] = NULL;
    return item;
}

void list_enqueue(list l, string item) {
    if (l == NULL || item == NULL) return;
    check_resize(l);
    l->items[l->length++] = strdup(item);
}

string list_dequeue(list l) {
    if (l == NULL || l->length == 0) return NULL;
    string item = l->items[0];
    for (size_t i = 0; i < l->length - 1; i++) {
        l->items[i] = l->items[i + 1];
    }
    l->items[--l->length] = NULL;
    return item;
}

void list_add(list l, string item) {
    if (l == NULL || item == NULL) return;
    for (size_t i = 0; i < l->length; i++) {
        if (strcmp(l->items[i], item) == 0) return;
    }
    check_resize(l);
    l->items[l->length++] = strdup(item);
}

void list_remove(list l, string item) {
    if (l == NULL || item == NULL || l->length == 0) return;
    for (size_t i = 0; i < l->length; i++) {
        if (strcmp(l->items[i], item) == 0) {
            free(l->items[i]);
            for (size_t j = i; j < l->length - 1; j++) {
                l->items[j] = l->items[j + 1];
            }
            l->items[--l->length] = NULL;
            return;
        }
    }
}

bool list_contains(list l, string item) {
    if (l == NULL || item == NULL) return false;
    for (size_t i = 0; i < l->length; i++) {
        if (strcmp(l->items[i], item) == 0) return true;
    }
    return false;
}

