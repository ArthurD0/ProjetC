#ifndef SORT_H
#define SORT_H

#include "column.h"

/**
 * @brief: Sort a column according to a given order
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 */
void sort(COLUMN* col, int sort_dir);

/**
 * @brief: Sort a column with the quicksort algorithm according to a given order
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 */
void quick_sort(COLUMN* col, int sort_dir);

/**
 * @brief: Helper for quick_sort(...)
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 * @param3: Start index
 * @param4: End index
 */
void quick_sort_helper(COLUMN* col, int sort_dir, long long int left, long long int right);

/**
 * @brief: Partition function helper for quick_sort(...)
 * @param1: The column containing data array
 * @param2: Start index
 * @param3: End index
 * @return: The new pivot
 */
long long int partition(COLUMN* col, int sort_dir, long long int left, long long int right);

/**
 * @brief: Compare two values
 * @param1: Type of data to compare
 * @param2: a first element to compare
 * @param3: b second element to compare
 * @return: true  : if a is greater than b
 *          false : otherwise
 */
bool a_is_greater_than_b(ENUM_TYPE type, void* a, void* b);

/**
 * @brief: Switch a and b
 * @param1: Index array to switch
 * @param2: a
 * @param3: b
 */
void switch_a_and_b(unsigned long long int* index, int a, int b);

/**
 * @brief: Sort a column with the insertion algorithm according to a given order
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 */
void insertion_sort(COLUMN* col, int sort_dir);

/**
 * @brief: Remove the index of a column
 * @param1: Pointer to the column
 */
void erase_index(COLUMN *col);

/**
 * @brief: Check if an index is correct
 * @param1: Pointer to the column
 * @return: 0: index not existing, -1: the index exists but invalid, 1: the index is correct
 */
int check_index(COLUMN *col);

/**
 * @brief: Update the index
 * @param1: Pointer to the column
 */
void update_index(COLUMN *col);

/**
 * @brief: Check if a value exists in a column
 * @param1: Pointer to the column
 * @param2: Pointer to the value to search for
 * @return: -1: column not sorted, 0: value not found 1: value found
 */
int search_value_in_column(COLUMN *col, void *val);

/**
 * @brief: Compare two values
 * @param1: Type of data to compare
 * @param2: a first element to compare
 * @param3: b second element to compare
 * @return: true  : if a is equal to b
 *          false : otherwise
 */
bool a_is_equal_to_b(ENUM_TYPE type, void* a, void* b);

#endif