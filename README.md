# Linked List

## Content

[About](#about)

[API](#api)

[Examples](#examples)

[Return Values](#return-values)

[Resources](#resources)

## About

Singly-linked list, simply called *linked list*, is a data structure composed of individual elements, each linked by a single pointer. Each element consists of two parts: a data member and a pointer, called the *next* pointer. Using this two-member structure, a linked list is formed by setting the next pointer of each element to point to the element that follows it. The next pointer of the last element is set to *NULL*, , a convenient sentinel marking the end of the list.

## API

### List_init

```C
int List_init(struct List* list, void (*destroy)(void* data), void (*print)(const void* data), int (*match)(const void* data_1, const void* data_2));
```

The `List_init` function initializes a linked list so that it can be used in other operations. List is considered to be initialized if its `print` and `match` fields are not *NULL*.

| Type | Description |
| ---- | ----------- |
| `void (*destroy)(void* data)` | Provides a way to free dynamically allocated data when `List_destroy` is called. If the list contains data dynamically allocated using `malloc`, `destroy` should be set to `free` to free the data as the linked list is destroyed. For structured data containing several dynamically allocated members, destroy should be set to a user-defined function that calls `free` for each dynamically allocated member as well as for the structure itself. For a linked list containing data that should not be freed, destroy should be set to *NULL* |
| `void (*print)(const void* data)` | Provides a default way to display content of the linked list when `List_display` is invoked. [How to write `print` functions](#how-to-write-print-functions)|
| `int (*match)(const void* data_1, const void* data_2)` | Provides a default way to compare values of the linked list when certain functions are called. [How to write `match` functions](#how-to-write-match-functions) |

On success, the function returns `INIT_SUCCESS` evaluated to *0*.

### Lis_init

```C
Lis_init(list) ((list->print != NULL && list->match != NULL))
```

This macros implements a simpler linked list operation - telling us if the list is initialized. A list is considered to be initialized if its `print` and `match` fields are not *NULL*.

### List_insert_first

```C
int List_insert_first(struct List* list, const void* data);
```

The `List_insert_first` function inserts an element with the specified `data` at the beginning of the linked list `list`. The function dynamically allocates memory for a list node and places data into it. When data is *NULL*, the function returns `EXIT_FAILURE` (e.g., a node is not inserted). Preventing a node to have *NULL* is the default behaviour. To allow nodes to contain *NULL*, compile a program with `NULL_ELMS`. Specifying `NULL_ELMS` affects the way some other functions operate.

| Type | Description |
| ---- | ----------- |
| `struct List* list` | The list to insert into |
| `const void* data` | Data to be inserted |

On success, the function returns `EXIT_SUCCESS`.

### List_insert_last

```C
int List_insert_last(struct List* list, const void* data);
```

The `List_insert_last` function inserts an element with the specified `data` at the end of the linked list `list`. The function dynamically allocates memory for a list node and places data into it. When data is *NULL*, the function returns `EXIT_FAILURE` (e.g., a node is not inserted). Preventing a node to have *NULL* is the default behaviour. To allow nodes to contain *NULL*, compile a program with `NULL_ELMS`. Specifying `NULL_ELMS` affects the way some other functions operate.

| Type | Description |
| ---- | ----------- |
| `struct List* list` | The list to insert into |
| `const void* data` | Data to be inserted |

On success, the function returns `EXIT_SUCCESS`.

### List_display

```C
void List_display(const struct List* list, void (*print)(const void* data));
```

The `List_display` function outputs content of the list. The `print` argument is a callback function that is called on every node while traversng the list. If `print` is NULL, the `print` function specified in `List_init` is used.

| Type | Description |
| ---- | ----------- |
| `const struct List* list` | The list to be displayed |
| `void (*print)(const void* data)` | The callback function to handle data in a node |

### List_find

```C
struct Node* List_find(const struct List* list, const void* data, int (*match)(const void* data_1, const void* data_2));
```

The `List_find` function looks for the specified data `data` in the linked list `list`. The `macth` argument is a callback that compares data. While traversing a list, `match` takes node data as its first parameter `data_1` and data to campare it with as `data_2`.

| Type | Description |
| ---- | ----------- |
| `const struct List* list` | The list to search in |
| `const void* data` | Data to be searched |
| `int (*match)(const void* data_1, const void* data_2)` | A callback function that compares values |

If there is a node with the given data, returns a pointer to that node, NULL if there is no such data.

### List_remove_first

```C
void* List_remove_first(struct List* list);
```

The `List_remove_first` funtion removes the first element from the list. It takes the only argument - the list to remove from. It returns a pointer to the data from removed element.

| Type | Description |
| ---- | ----------- |
| `struct List* list` | A list to remove from |

### List_remove_last

```C
void* List_remove_last(struct List* list);
```

The `List_remove_last` funtion removes the last element from the list. It takes the only argument - the list to remove from. It returns a pointer to the data from removed element.

| Type | Description |
| ---- | ----------- |
| `struct List* list` | A list to remove from |

### List_remove_node

```C
void* List_remove_node(struct List* list, struct Node* node);
```

The `List_remove_node` function removes the specified node from the list. It returns a pointer to data from removed node. The function returns *NULL* if the node was not removed. You can specify the `List_find` function for example, or any other function that returns `struct Node*` in place of a `node` argument.

| Type | Description |
| ---- | ----------- |
| `struct List* list` | A list to remove from |
| `struct Node* node`| A node to remove |

### List_insert_before

```C
int List_insert_before(struct List* list, const void* data, const struct Node* node);
```

The `List_insert_before` function inserts a node with specified data in a list before another node. If `node` is *NULL*, the function behaves like the `List_insert_first` one. Returns `EXIT_SICCESS` if a node is inserted, `EXIT_FAILURE` a node is not inserted.

| Type | Description |
| ---- | ----------- |
| `struct List* list` | A list to insert into |
| `const void* data` | Data to insert |
| `const struct Node* node` | A node to insert before (*insert before this node if it's in the list*) |

### List_insert_after

```C
int List_insert_after(struct List* list, const void* data, const struct Node* node);
```

The `List_insert_after` function inserts a node with specified data in a list after another node. If `node` is *NULL*, the function behaves like the `List_insert_last` one. Returns `EXIT_SICCESS` if a node is inserted, `EXIT_FAILURE` a node is not inserted.

| Type | Description |
| ---- | ----------- |
| `struct List* list` | A list to insert into |
| `const void* data` | Data to insert |
| `const struct Node* node` | A node to insert after (*insert after this node if it's in the list*) |

### List_destroy

```C
int List_destroy(struct List* list);
```

The `List_destroy` function destroys a linked list. Primarally this means removing all elements from the list. The function passed to `List_init` is called once for each element as it is removed, provided `destroy` was not set to *NULL*. Returns `EXIT_SUCCESS` if the list.

| Type | Description |
| ---- | ----------- |
| `struct List* list` | A list to destroy |

### List_each

```C
int List_each(const struct List* list, void (*callback)(void* data));
```

The `List_each` operation calls a function `callback` for each element of the list. It is up to the user to convert `void*` to the appropriate data type stored in a list node.

| Type | Description |
| ---- | ----------- |
| `const struct List* list` | A list to modify |
| `void (*callback)(void* data)` | A callback function to be applied |

## Examples

### How to write `print` functions

The `print` argument in the `List_display` function is a callback that handles data in a linked list node.

One must assume that a list is homogeneous (e.g., contains data of the same type). For example, suppose we have a linked list of integers, then we might write the function:

```C
/* ... */

void print_int(const void* data) {
    printf("%d", *((int*) data));
}
```

Keep in mind that **`print` callback takes `const void*` as its argument**.

### How to write `match` functions

A `match` function is a callback that is passed as an argument to another function. In order to write a *match* function, one must assume that a list is *homogeneous* (i.e., contains data of the same type). According to the API, the `match` function should return *0*:

```C
/* just an example of the implementation of the `match` callback function */
int match_int(const void* data_1, const void* data_2) {
    return (*((int*) x) - *((int*) y));
}
```

**Overflow may occur!**.

The match function takes two parameters: `data_1` and `data_2`. The `data_1` parameter takes data of the list node, and `data_2` is data to compare with. Keep in mind that a match function accepts `void*` pointers, and you cast/dereference them to the appropriate type in a `callback` function body.

If a list contains complex data (e.g., structs, for example), the user must decide how to compare them.

## Return Values

Here goes a list of values returned by some functions above.

### `List_init`

| Return value | Description |
| :--- | :---------- |
| 0    | Successful initialization |
| 1    | `print` argument is *NULL* |
| 2    | `match` argument is *NULL* |
| 3    | Both `print` and `match` arguments are *NULL*|

## Resources

[Mastering Algorithms with C](https://www.amazon.com/Mastering-Algorithms-Techniques-Sorting-Encryption/dp/1565924533/ref=sr_1_1?crid=1ZN4ENEQEGO5&keywords=mastering+c+algorithms&qid=1679619546&s=books&sprefix=mastering+c+algoritms%2Cstripbooks-intl-ship%2C221&sr=1-1) by Kyle Loudon.

[Data Structures, Algorithms, and Software Principles in C](https://www.amazon.com/Data-Structures-Algorithms-Software-Principles/dp/0201591189/ref=sr_1_10?crid=14MCGWUKW0F98&keywords=data+structures+and+algorithms+in+C&qid=1679784448&s=books&sprefix=data+structures+and+algorithms+in+c%2Cstripbooks-intl-ship%2C186&sr=1-10) by Thomas Standish.

[Computer Systems: A Programmer's Perspective](https://www.amazon.com/Computer-Systems-Programmers-Randal-Bryant/dp/013034074X/ref=sr_1_3?crid=1NDI8BHE4BPQM&keywords=computer+systems+a+programmer%27s+perspective&qid=1679784732&s=books&sprefix=computer+pers%2Cstripbooks-intl-ship%2C199&sr=1-3) by Randal E. Bryant, David Richard O'Hallaron.

[Linked list](https://en.wikipedia.org/wiki/Linked_list) Wikipedia.
