[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# PA3

**Makefile Usage:**
```sh
make          # build
make run      # build and run
make clean    # remove build directory  
make test     # builds and runs tests
```

# Data Structure Selection

**HashTable** - Implemented in ```include/map.h``` chosen for constant time product lookups.
**ResizeableArray** - Implemented in ```include/list.h``` chosen for managing any collection of items that doesnt require constant lookup.

# CSV Data Formatting

I've left empty fields as strings with "N/A" as a placeholder, with the exception of the categories field which is left as an empty list.

# Test Cases

## ResizeableArray test cases
- Insert into an empty array
- Resizes the array when capacity is reached
- Find work when element exists
- Find returns the end() iterator when an element does not exist
- Bracket operator works when index is within bounds
- Bracket operator throws when index out of bounds
- Delete work when index is in bound
- Delete throws when index is out of bounds

## HashTable test cases
- Insert into an empty map
- Insert when load factor exceeded rehashes
- Find by key works when the key exists
- Find by key returns a null value when the key does not exists
- Delete does not throw on nonexistant key
- Delete removes the key value pai when it does exist.