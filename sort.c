#include "sort.h"

/**
 * @brief: Sort a column according to a given order
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 */
void sort(COLUMN* col, int sort_dir)
{
    if (col!=NULL && col->size>0)
    {
        col->sort_dir = sort_dir;
        if (col->valid_index==0)
        {
            quick_sort(col, col->sort_dir);
        }
        else if (col->valid_index==-1)
        {
            insertion_sort(col, col->sort_dir);
        }
    }
}

/**
 * @brief: Sort a column with the quicksort algorithm according to a given order
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 */
void quick_sort(COLUMN* col, int sort_dir)
{
    quick_sort_helper(col, col->column_type, 0, (col->size)-1);
    if (sort_dir==DESC)
    {
        for (long long int i = 0; i < (col->size)/2; i++)
        {
            switch_a_and_b(col->index, i, (col->size)-1-i);
        }
        
    }
    
}

/**
 * @brief: Helper for quick_sort(...)
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 * @param3: Start index
 * @param4: End index
 */
void quick_sort_helper(COLUMN* col, int sort_dir, long long int left, long long int right)
{
    if (left < right)
    {
        long long int pi = partition(col, sort_dir, left, right);
        quick_sort_helper(col, col->column_type, left, pi-1);
        quick_sort_helper(col, col->column_type, pi+1, right);
    }
}

/**
 * @brief: Partition function helper for quick_sort(...)
 * @param1: The column containing data array
 * @param2: Start index
 * @param3: End index
 * @return: The new pivot
 */
long long int partition(COLUMN* col, int sort_dir, long long int left, long long int right)
{
    long long int pivot = (long long int)right;
    long long int i = 0;
    i = (long long int)left;
    i--;
    for (long long int j = (long long int)left; j <= (long long int)right-1; j++)
    {
        if (!(a_is_greater_than_b(col->column_type, col->data[col->index[j]], col->data[col->index[pivot]])))
        {
            i++;
            switch_a_and_b(col->index, i, j);
        }
    }
    switch_a_and_b(col->index, (long long int)i+1, (long long int)right);
    return (long long int)i+1;
}

/**
 * @brief: Compare two values
 * @param1: Type of data to compare
 * @param2: a first element to compare
 * @param3: b second element to compare
 * @return: true  : if a is greater than b
 *          false : otherwise
 */
bool a_is_greater_than_b(ENUM_TYPE type, void* a, void* b)
{
    bool is_greater_than_x = false;
    switch (type)
    {
    case UINT:
        is_greater_than_x = *((unsigned int*)a) > *((unsigned int*)b);
        break;
        
    case INT:
        is_greater_than_x = *((int*)a) > *((int*)b);
        break;
        
    case CHAR:
        is_greater_than_x = *((char*)a) > *((char*)b);
        break;
        
    case FLOAT:
        is_greater_than_x = *((float*)a) > *((float*)b);
        break;
        
    case DOUBLE:
        is_greater_than_x = *((double*)a) > *((double*)b);
        break;
        
    case STRING:
        is_greater_than_x = (strcmp((char*)a, (char*)b) > 0) ? true : false;
        break;
        
    case STRUCTURE:
        is_greater_than_x = a > b;
        break;
    
    default:
        break;
    }
    return is_greater_than_x;
}

/**
 * @brief: Switch a and b
 * @param1: Index array to switch
 * @param2: a
 * @param3: b
 */
void switch_a_and_b(unsigned long long int* index, int a, int b)
{
    unsigned long long int k = index[a];
    index[a] = index[b];
    index[b] = k;
}

/**
 * @brief: Sort a column with the insertion algorithm according to a given order
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 */
void insertion_sort(COLUMN* col, int sort_dir)
{
    unsigned long long int i=0, j=0;
    for (i = 2; i < col->size; i++)
    {
        unsigned long long int k = i;
        j = i-1;
        while (j>0 && (a_is_greater_than_b(col->column_type, col->data[col->index[j]], col->data[col->index[k]]) && !sort_dir))
        {
            col->index[j+1] = col->index[j];
            j--;
        }
        col->index[j+1] = k;
    }
}

/**
 * @brief: Remove the index of a column
 * @param1: Pointer to the column
 */
void erase_index(COLUMN *col)
{
    if (col==NULL)
    {
        free(col->index);
        col->index = NULL;
        col->valid_index = 0;
    }
}

/**
 * @brief: Check if an index is correct
 * @param1: Pointer to the column
 * @return: 0: index not existing, -1: the index exists but invalid, 1: the index is correct
 */
int check_index(COLUMN *col)
{
    if (col->valid_index==1)
    {
        return 1;
    }
    else if (col->valid_index==-1)
    {
        return -1;
    }
    return 0;
}

/**
 * @brief: Update the index
 * @param1: Pointer to the column
 */
void update_index(COLUMN *col)
{
    sort(col, col->sort_dir);
}

/**
 * @brief: Check if a value exists in a column
 * @param1: Pointer to the column
 * @param2: Pointer to the value to search for
 * @return: -1: column not sorted, 
 *           0: value not found 
 *           1: value found
 */
int search_value_in_column(COLUMN *col, void *val)
{
    long long int start = 0;
    long long int end = col->size-1;

    while (start<=end)
    {
        long long int middle = (start + end)/2;
        if (a_is_equal_to_b(col->column_type, col->data[middle], val))
        {
            return 1;
        }
        else if (a_is_greater_than_b(col->column_type, col->data[middle], val))
        {
            if (col->sort_dir==ASC)
            {
                end = middle-1;
            }
            else
            {
                start = middle+1;
            }
            
        }
        else
        {
            start = middle+1;
            if (col->sort_dir==ASC)
            {
                start = middle+1;
            }
            else
            {
                end = middle-1;
            }
        }
    }
    return -1;
}

/**
 * @brief: Compare two values
 * @param1: Type of data to compare
 * @param2: a first element to compare
 * @param3: b second element to compare
 * @return: true  : if a is equal to b
 *          false : otherwise
 */
bool a_is_equal_to_b(ENUM_TYPE type, void* a, void* b)
{
    bool is_equal_to_b = false;
    switch (type)
    {
    case UINT:
        is_equal_to_b = *((unsigned int*)a) == *((unsigned int*)b);
        break;
        
    case INT:
        is_equal_to_b = *((int*)a) == *((int*)b);
        break;
        
    case CHAR:
        is_equal_to_b = *((char*)a) == *((char*)b);
        break;
        
    case FLOAT:
        is_equal_to_b = *((float*)a) == *((float*)b);
        break;
        
    case DOUBLE:
        is_equal_to_b = *((double*)a) == *((double*)b);
        break;
        
    case STRING:
        is_equal_to_b = (strcmp((char*)a, (char*)b) == 0) ? true : false;
        break;
        
    case STRUCTURE:
        is_equal_to_b = a == b;
        break;
    
    default:
        break;
    }
    return is_equal_to_b;
}