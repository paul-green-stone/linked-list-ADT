# Linked List

## Content

[About](#about)

[API](#api)

[Examples](#examples)

[Resources](#resources)

## About

Singly-linked list, simply called *linked list*, is a data structure composed of individual elements, each linked by a single pointer. Each element consists of two parts: a data member and a pointer, called the *next* pointer. Using this two-member structure, a linked list is formed by setting the next pointer of each element to point to the element that follows it. The next pointer of the last element is set to *NULL*, a convenient sentinel marking the end of the list.

## API

### List_create

```C
List List_create(void (*fptr_destroy)(void*), void (*fptr_print)(const Data));
```

The `List_create` function allocates a new instance of a linked list.

| Type | Description |
| ---- | ----------- |
| `fptr_destroy destroy_func` | Provides a way to free dynamically allocated data when `List_destroy` is called. If the list contains data dynamically allocated using `malloc`, `destroy` should be set to `free` to free the data as the linked list is destroyed. For structured data containing several dynamically allocated members, destroy should be set to a user-defined function that calls `free` for each dynamically allocated member as well as for the structure itself. For a linked list containing data that should not be freed, destroy should be set to *NULL* |
| `fptr_print print_func` | Provides a default way to display content of the linked list when `List_display` is called. [How to write `print` functions](#how-to-write-print-functions)|
| `fptr_match match_func` | Provides a default way to compare data residing in the linked list node. See [how to write `match` functions](#how-to-write-match-functions) for details |

**Return value**: a new instance of a linked list (`List_t`) on success, `NULL` on failure.

### List_insert_first

```C
int List_insert_first(List_t list, const Data data);
```

The `List_insert_first` function inserts an element with the specified `data` at the beginning of the linked list `list`. The function dynamically allocates memory for a list node and places data into it.

| Type | Description |
| ---- | ----------- |
| `List_t list` | The list to insert into |
| `const Data data` | Data to be inserted |

**Return value**: *0* if inserting the data is successful, or *-1* otherwise.

### List_insert_last

```C
int List_insert_last(List_t list, const Data data);
```

The `List_insert_last` function inserts an element with the specified `data` at the end of the linked list `list`. The function dynamically allocates memory for a list node and places data into it.

| Type | Description |
| ---- | ----------- |
| `List_t list` | The list to insert into |
| `const Data data` | Data to be inserted |

**Return value**: *0* if inserting the data is successful, or *-1* otherwise.

### List_print

```C
void List_print(const List_t list, void (*fptr_print)(const Data));
```

The `List_print` function outputs content of the list. The `fptr_print` argument is an alternative way to display the list content. If `fptr_print` is NULL, the `fptr_print` function specified in `List_create` is used.

| Type | Description |
| ---- | ----------- |
| `const List_t list` | The list to be displayed |
| `fptr_print print_func` | The callback function to handle data in a node |

**Return value**: none.

### List_find

```C
Node List_find(const List list, const Data data);
```

The `List_find` function looks for the specified data `data` in the linked list `list`.

| Type | Description |
| ---- | ----------- |
| `const List list` | The list to search in |
| `const Data data` | Data to be searched |

**Return value**: a linked list node (`Node`) on success, `NULL` on failure.

### List_remove_first

```C
Data List_remove_first(List_t list);
```

The `List_remove_first` funtion removes the first element from the list. It takes the only argument - the list to remove from. It returns `Data` from removed element. It's the user responsibility to free returned data if needed.

| Type | Description |
| ---- | ----------- |
| `List_t list` | A list to remove from |

**Return value**: data if deletion is success, `NULL` otherwise.

### List_remove_last

```C
Data List_remove_last(List_t list);
```

The `List_remove_last` function removes the last element from the list. It takes the only argument - the list to remove from. It's the user responsibility to free returned data if needed.

| Type | Description |
| ---- | ----------- |
| `List_t list` | A list to remove from |

**Return value**: data if deletion is success, `NULL` otherwise.

### List_get_size

```C
size_t List_get_size(const List_t list);
```

The `List_get_size` function returns a size of linked list.

| Type | Description |
| ---- | ----------- |
| `const List_t list` | A list we want to know the size of |

**Return value**: the number of elements in the list if it's not `NULL`, *-1* otherwise.

### List_merge

```C
int List_merge(List_t* dest, List_t* src);
```

The `List_merge` function merges two lists into one (`src` into `dest`).

| Type | Description |
| ---- | ----------- |
| `List* dest` | A list to merge into |
| `List* src` | A list to merge |

**Return value**: *0* if the merging is success, *-1* on failure.

### List_remove_node

```C
Data List_remove_node(List_t list, Node node);
```

The `List_remove_node` function removes the specified node from the list. You can specify the `List_find` function for example, or any other function that returns `Node*` in place of a `node` argument.

| Type | Description |
| ---- | ----------- |
| `List_t list` | A list to remove from |
| `Node node`| A node to remove |

On success, the function returns `Data`, or *NULL* on failure. It's the user resposibility to deallocate `Data` if needed.

**Return value**: data if removing the element is successful, `NULL` otherwise.

### List_insert_before

```C
int List_insert_before(List_t list, const Data data, const Node node);
```

The `List_insert_before` function inserts a node with specified data in a list before another node. If `node` is *NULL*, the function behaves like the `List_insert_first` function.

| Type | Description |
| ---- | ----------- |
| `List list` | A list to insert into |
| `const Data data` | Data to insert |
| `const Node node` | A node to insert before (*insert before this node if it's in the list*) |

**Return value**: *0* if insertion is successful, *-1* otherwise.

### List_insert_after

```C
int8_t List_insert_after(List list, const Data data, const Node node);
```

The `List_insert_after` function inserts a node with specified data in a list after another node. If `node` is *NULL*, the function behaves like the `List_insert_last` one.

| Type | Description |
| ---- | ----------- |
| `List list` | A list to insert into |
| `const Data data` | Data to insert |
| `const Node node` | A node to insert after (*insert after this node if it's in the list*) |

**Return value**: *0* if insertion is successful, *-1* otherwise.

### List_destroy

```C
void List_destroy(List* list);
```

The `List_destroy` function destroys a linked list. Primarally this means removing all elements from the list. The function passed to `List_new` is called once for each element as it is removed, provided `fptr_destroy` was not set to *NULL*.

| Type | Description |
| ---- | ----------- |
| `List_t* list` | A pointer to a list to destroy |

**Return value**: none. The list is `NULL` upon completion.

## Examples

### How to write `print` functions

The `print` argument in the `List_print` function is a callback that handles data in a linked list node.

One must assume that a list is homogeneous (e.g., contains data of the same type). For example, suppose we have a linked list of integers, then we might write the function:

```C
/* ... */

void print_int(Data data) {
    printf("%d", *((int*) data));
}
```

Keep in mind that **`print` callback takes `const void*` as its argument**.

### How to write `match` functions

A `match` function is a callback that is passed as an argument to another function. In order to write a *match* function, one must assume that a list is *homogeneous* (i.e., contains data of the same type). According to the API, the `match` function should return *0*:

```C
/* just an example of the implementation of the `match` callback function */
int match_int(Data data_1, Data data_2) {
    return (*((int*) x) - *((int*) y));
}
```

**Overflow may occur!**.

The match function has two parameters: `data_1` and `data_2`. The `data_1` parameter expects data of the list node, and `data_2` is data to compare with. Keep in mind that match functions accepts `const Data`. A user must  cast and dereference them to the appropriate type in a `match` function body.

If a list contains complex data (e.g., structs, for example), the user must decide how to compare them.

## Resources

[Mastering Algorithms with C](https://www.amazon.com/Mastering-Algorithms-Techniques-Sorting-Encryption/dp/1565924533/ref=sr_1_1?crid=1ZN4ENEQEGO5&keywords=mastering+c+algorithms&qid=1679619546&s=books&sprefix=mastering+c+algoritms%2Cstripbooks-intl-ship%2C221&sr=1-1) by Kyle Loudon.

[Data Structures, Algorithms, and Software Principles in C](https://www.amazon.com/Data-Structures-Algorithms-Software-Principles/dp/0201591189/ref=sr_1_10?crid=14MCGWUKW0F98&keywords=data+structures+and+algorithms+in+C&qid=1679784448&s=books&sprefix=data+structures+and+algorithms+in+c%2Cstripbooks-intl-ship%2C186&sr=1-10) by Thomas Standish.

[Computer Systems: A Programmer's Perspective](https://www.amazon.com/Computer-Systems-Programmers-Randal-Bryant/dp/013034074X/ref=sr_1_3?crid=1NDI8BHE4BPQM&keywords=computer+systems+a+programmer%27s+perspective&qid=1679784732&s=books&sprefix=computer+pers%2Cstripbooks-intl-ship%2C199&sr=1-3) by Randal E. Bryant, David Richard O'Hallaron.

[Patterns in C](https://leanpub.com/patternsinc) by Adam Tornhill

[Linked list](https://en.wikipedia.org/wiki/Linked_list) Wikipedia.
