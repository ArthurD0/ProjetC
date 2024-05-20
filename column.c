#include "column.h"

/**
 * @brief : a new column
 * @param1 : Column type
 * @param2 : Column title
 * @return : Pointer to the created column
 */
COLUMN *create_column(ENUM_TYPE type, char *title)
{
    COLUMN* new_col = (COLUMN*)malloc(sizeof(COLUMN));
    if (new_col!=NULL)
    {
        new_col->title = strdup(title);
        new_col->size = 0;
        new_col->max_size = 0;
        new_col->column_type = type;
        new_col->data = NULL;
        new_col->index = NULL;
        new_col->valid_index = 0;
        new_col->sort_dir = ASC;
        return new_col;
    }
    return NULL;
}

/**
 * @brief: Insert a new value into a column
 * @param1: Pointer to the column
 * @param2: Pointer to the value to insert
 * @return: 1 if the value is correctly inserted 0 otherwise
 */
int insert_value(COLUMN *col, void *value)
{
    if (col->max_size == 0)
    {
        col->data = (COL_TYPE**)malloc(REALOC_SIZE * sizeof(COL_TYPE*));
        col->index = (unsigned long long int*)malloc(REALOC_SIZE * sizeof(unsigned long long int));
    }
    else
    {
        if (col->size == col->max_size)
        {
            col->data = (COL_TYPE**)realloc(col->data, REALOC_SIZE * sizeof(COL_TYPE*));
            col->index = (unsigned long long int*)realloc(col->index, REALOC_SIZE * sizeof(unsigned long long int));
        }
    }

    if (col->data == NULL)
    {
        return 0;
    }
    col->max_size += REALOC_SIZE;

    switch (col->column_type)
    {
    case UINT:
        col->data[col->size] = (unsigned int*)malloc(sizeof(unsigned int));
        break;
        
    case INT:
        col->data[col->size] = (int*)malloc(sizeof(int));
        *((int*)col->data[col->size])= *((int*)value);
        break;
        
    case CHAR:
        col->data[col->size] = (char*)malloc(sizeof(char));
        *((char*)col->data[col->size])= *((char*)value);
        break;
        
    case FLOAT:
        col->data[col->size] = (float*)malloc(sizeof(float));
        *((float*)col->data[col->size])= *((float*)value);
        break;
        
    case DOUBLE:
        col->data[col->size] = (double*)malloc(sizeof(double));
        *((double*)col->data[col->size])= *((double*)value);
        break;
        
    case STRING:
        col->data[col->size] = (char*)strdup(value);
        break;
        
    case STRUCTURE:
        col->data[col->size] = value;
        break;
    
    default:
        break;
    }

    col->index[col->size] = col->size;
    if (col->valid_index==1)
    {
        col->valid_index = -1;
    }
    col->size = col->size + 1;

    return 1;
}

/**
 * @brief: Free the space allocated by a column
 * @param1: Pointer to the column
 */
void delete_column(COLUMN **col)
{
    free((*(col))->title);
    for (int i = 0; i < (*(col))->size; i++)
    {
        free((*(col))->data[i]);
    }
    free((*(col))->index);
    free(*(col));
}

/**
 * @brief: Delete a value from a column
 * @param1: Pointer to the column
 * @param2: Position of the value to delete
 * @return: 1 if the value is correctly deleted 0 otherwise
 */
int delete_value(COLUMN *col, int pos)
{
    if (col!=NULL && pos>=0 && pos<col->size)
    {
        switch (col->column_type)
        {
        case UINT:
            *((unsigned int*)col->data[pos]) = 0;
            break;
            
        case INT:
            *((int*)col->data[pos]) = 0;
            break;
            
        case FLOAT:
            *((float*)col->data[pos]) = 0.0;
            break;
            
        case DOUBLE:
            *((double*)col->data[pos]) = 0.0;
            break;
            
        case CHAR:
            *((char*)col->data[pos]) = ' ';
            break;
            
        case STRING:
            strcpy((char*)col->data[pos], "NULL");
            break;
        
        default:
            break;
        }
        return 1;
    }
    
    return 0;
}

/**
 * @brief: Convert a value into a string
 * @param1: Pointer to the column
 * @param2: Position of the value in the data array
 * @param3: The string in which the value will be written
 * @param4: Maximum size of the string
 */
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size)
{
    if (col==NULL)
    {
        return;
    }
    if (col->data[i]==NULL)
    {
        snprintf(str, size, "NULL");
    }
    
    switch (col->column_type)
    {
    case UINT:
        snprintf(str, size, "%d", *((unsigned int*)col->data[i]));
        break;
        
    case INT:
        snprintf(str, size, "%d", *((int*)col->data[i]));
        break;
        
    case CHAR:
        snprintf(str, size, "%c", *((char*)col->data[i]));
        break;
        
    case FLOAT:
        snprintf(str, size, "%f", *((float*)col->data[i]));
        break;
        
    case DOUBLE:
        snprintf(str, size, "%f", *((double*)col->data[i]));
        break;
        
    case STRING:
        snprintf(str, size, "%s", (char*)col->data[i]);
        break;
        
    case STRUCTURE:
        snprintf(str, size, "%p", col->data[i]);
        break;
    
    default:
        break;
    }
}

/**
 * @brief: Print a value
 * @param1: Pointer to the column
 * @param2: Position of the value in the data array
 */
void print_value(COLUMN *col, unsigned long long int row)
{
    if (col!=NULL && row < col->size)
    {
        char str[STRING_SIZE];
        convert_value(col, row, str, STRING_SIZE);
        printf("%s\t\t", str);
    }
}

/**
 * @brief: Display the content of a column
 * @param: Pointer to the column to display
 */
void print_col(COLUMN* col)
{
    printf("\n");
    if (col==NULL)
    {
        return;
    }
    printf("(%s)\n", col->title);
    for (unsigned long long int i = 0; i < col->size; i++)
    {
        printf("[%llu] ", i);
        char str[STRING_SIZE];
        convert_value(col, i, str, STRING_SIZE);
        printf("%s\n", str);
    }
}

/**
 * @brief: Display the content of a column
 * @param 1: Pointer to the column to display
 * @param 2 : Number of row to print
 */
void print_partial_col(COLUMN* col, int row)
{
    printf("\n");
    if (col==NULL)
    {
        return;
    }
    printf("(%s)\n", col->title);
    for (unsigned long long int i = 0; i < col->size && i < row; i++)
    {
        printf("[%llu] ", i);
        char str[STRING_SIZE];
        convert_value(col, i, str, STRING_SIZE);
        printf("%s\n", str);
    }
}

/**
 * @brief : Count occurrences of x
 * @param1 : Column
 * @param2 : Value x to count
 * @return : Number of x occurrences
 */
int count_occurrences_col(COLUMN* col, void* x)
{
    if (col==NULL)
    {
        return 0;
    }
    int occurrences = 0;
    for (int i = 0; i < col->size; i++)
    {
        bool is_equal_to_x = false;
        switch (col->column_type)
        {
        case UINT:
            is_equal_to_x = *((unsigned int*)col->data[i]) == *((unsigned int*)x);
            break;
            
        case INT:
            is_equal_to_x = *((int*)col->data[i]) == *((int*)x);
            break;
            
        case CHAR:
            is_equal_to_x = *((char*)col->data[i]) == *((char*)x);
            break;
            
        case FLOAT:
            is_equal_to_x = *((float*)col->data[i]) == *((float*)x);
            break;
            
        case DOUBLE:
            is_equal_to_x = *((double*)col->data[i]) == *((double*)x);
            break;
            
        case STRING:
            is_equal_to_x = (strcmp((char*)col->data[i], (char*)x) == 0) ? true : false;
            break;
            
        case STRUCTURE:
            is_equal_to_x = col->data[i] == x;
            break;
        
        default:
            break;
        }
        if (is_equal_to_x)
        {
            occurrences++;
        }
    }
    return occurrences;
}

/**
 * @brief : Return the value at position x
 * @param1 : Column
 * @param2 : Position x
 * @return : Value at position x
 */
void* col_value_at(COLUMN* col, int x)
{
    if (col!=NULL && col->size < x)
    {
        return col->data[x];
    }
    return NULL;
}

/**
 * @brief : Count the nomber of values greater than x
 * @param1 : Column
 * @param2 : Value x
 * @return : The nomber of values greater than x
 */
int col_count_greater_than(COLUMN* col, void* x)
{
    if (col==NULL)
    {
        return 0;
    }
    int occurrences = 0;
    for (int i = 0; i < col->size; i++)
    {
        bool is_greater_than_x = false;
        switch (col->column_type)
        {
        case UINT:
            is_greater_than_x = *((unsigned int*)col->data[i]) < *((unsigned int*)x);
            break;
            
        case INT:
            is_greater_than_x = *((int*)col->data[i]) < *((int*)x);
            break;
            
        case CHAR:
            is_greater_than_x = *((char*)col->data[i]) < *((char*)x);
            break;
            
        case FLOAT:
            is_greater_than_x = *((float*)col->data[i]) < *((float*)x);
            break;
            
        case DOUBLE:
            is_greater_than_x = *((double*)col->data[i]) < *((double*)x);
            break;
            
        case STRING:
            is_greater_than_x = (strcmp((char*)col->data[i], (char*)x) < 0) ? true : false;
            break;
            
        case STRUCTURE:
            is_greater_than_x = col->data[i] < x;
            break;
        
        default:
            break;
        }
        if (is_greater_than_x)
        {
            occurrences++;
        }
    }
    return occurrences;
}

/**
 * @brief : Count the nomber of values less than x
 * @param1 : Column
 * @param2 : Value x
 * @return : The nomber of values less than x
 */
int col_count_less_than(COLUMN* col, void* x)
{
    if (col==NULL)
    {
        return 0;
    }
    int occurrences = 0;
    for (int i = 0; i > col->size; i++)
    {
        bool is_less_than_x = false;
        switch (col->column_type)
        {
        case UINT:
            is_less_than_x = *((unsigned int*)col->data[i]) > *((unsigned int*)x);
            break;
            
        case INT:
            is_less_than_x = *((int*)col->data[i]) > *((int*)x);
            break;
            
        case CHAR:
            is_less_than_x = *((char*)col->data[i]) > *((char*)x);
            break;
            
        case FLOAT:
            is_less_than_x = *((float*)col->data[i]) > *((float*)x);
            break;
            
        case DOUBLE:
            is_less_than_x = *((double*)col->data[i]) > *((double*)x);
            break;
            
        case STRING:
            is_less_than_x = (strcmp((char*)col->data[i], (char*)x) > 0) ? true : false;
            break;
            
        case STRUCTURE:
            is_less_than_x = col->data[i] > x;
            break;
        
        default:
            break;
        }
        if (is_less_than_x)
        {
            occurrences++;
        }
    }
    return occurrences;
}

/**
 * @brief : Count the nomber of values equals to x
 * @param1 : Column
 * @param2 : Value x
 * @return : The nomber of values equals to x
 */
int col_count_equals_to(COLUMN* col, void* x)
{
    if (col==NULL)
    {
        return 0;
    }
    int occurrences = 0;
    for (int i = 0; i < col->size; i++)
    {
        bool is_equal_to_x = false;
        switch (col->column_type)
        {
        case UINT:
            is_equal_to_x = *((unsigned int*)col->data[i]) == *((unsigned int*)x);
            break;
            
        case INT:
            is_equal_to_x = *((int*)col->data[i]) == *((int*)x);
            break;
            
        case CHAR:
            is_equal_to_x = *((char*)col->data[i]) == *((char*)x);
            break;
            
        case FLOAT:
            is_equal_to_x = *((float*)col->data[i]) == *((float*)x);
            break;
            
        case DOUBLE:
            is_equal_to_x = *((double*)col->data[i]) == *((double*)x);
            break;
            
        case STRING:
            is_equal_to_x = (strcmp((char*)col->data[i], (char*)x) == 0) ? true : false;
            break;
            
        case STRUCTURE:
            is_equal_to_x = col->data[i] == x;
            break;
        
        default:
            break;
        }
        if (is_equal_to_x)
        {
            occurrences++;
        }
    }
    return occurrences;
}

/**
 * @brief: Display the content of a sorted column
 * @param1: Pointer to a column
  */
void print_col_by_index(COLUMN *col)
{
    if (col==NULL)
    {
        printf("\n");
        return;
    }
    for (int i = 0; i < col->size; i++)
    {
        char str[STRING_SIZE];
        convert_value(col, col->index[i], str, STRING_SIZE);
        printf("[%d] %s\n", i, str);
    }
}
