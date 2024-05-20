#include "cdataframe.h"
#include "sort.h"

/**
 * @brief : Create a CDATAFRAME
 * @param1 : Columns types
 * @param2 : Number of column
 * @return : Pointer to created CDATAFRAME
 */
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size)
{
    CDATAFRAME* new_cdataframe = lst_create_list();
    if (new_cdataframe!=NULL)
    {
        if (size>0)
        {
            for (int i = 0; i < size; i++)
            {
                COLUMN* new_column = create_column(cdftype[i], "");
                add_col(new_cdataframe, new_column);
            }
        }
        return new_cdataframe;
    }
    return NULL;
}

/**
 * @brief : Create a empty CDATAFRAME
 * @return : Pointer to created CDATAFRAME
 */
CDATAFRAME *create_empty_cdataframe()
{
    return lst_create_list();
}

/**
 * @brief : Fill the CDATAFRAME with user input
 * @return : Pointer to the full CDATAFRAME
 */
CDATAFRAME* fill_cdataframe()
{
    CDATAFRAME* new_cdataframe = NULL;
    int size=0, type_select=0, col_size=0;
    int cols_size[REALOC_SIZE];
    ENUM_TYPE types[REALOC_SIZE];
    char ***data = (char***)malloc(REALOC_SIZE * sizeof(char**));
    while (size<1 || size>REALOC_SIZE)
    {
        printf("\nEntrez le nombre de colonne (MAX : %d) : ", REALOC_SIZE);
        scanf("%d", &size);
    }
    for (int i = 0; i < REALOC_SIZE; i++)
    {
        data[i] = (char**)malloc(size * sizeof(char*));
        for (int j = 0; j < size; j++)
        {
            data[i][j] = (char*)malloc(STRING_SIZE * sizeof(char));
        }
    }
    for (int i = 0; i < size; i++)
    {
        type_select = 0;
        col_size = 0;
        while (type_select<1 || type_select>6)
        {
            printf("\nChoisissez le type de la colonne %d : \n", i);
            printf(" 1 - Entier non signé\n");
            printf(" 2 - Entier signé\n");
            printf(" 3 - Caractère\n");
            printf(" 4 - Nombre réel sur 32 bits\n");
            printf(" 5 - Nombre réel sur 64 bits\n");
            printf(" 6 - Chaine de caractères\n\t");
            scanf("%d", &size);
        }
        switch (type_select)
        {
        case 1:
            types[i] = UINT;
            break;
            
        case 2:
            types[i] = INT;
            break;
            
        case 3:
            types[i] = CHAR;
            break;
            
        case 4:
            types[i] = FLOAT;
            break;
            
        case 5:
            types[i] = DOUBLE;
            break;
            
        case 6:
            types[i] = STRING;
            break;
        
        default:
            break;
        }
        printf("\nEntrez le nom de la colonne %d : ", i);
        scanf("%s", data[i][0]);
        while (col_size<0 || col_size>REALOC_SIZE-1)
        {
            printf("\nEntrez le nombre de ligne colonne %d : ", i);
            scanf("%d", &col_size);
        }
        cols_size[i] = col_size;
        for (int j = 1; j < cols_size[i]; j++)
        {
            printf("Entrez la data de la ligne %d de la colonne %d : ", j-1, i);
            scanf("%s", data[i][j]);
        }
    }
    new_cdataframe = fill_hard_cdataframe(types, size, data, cols_size);
    for (int i = 0; i < REALOC_SIZE; i++)
    {
        for (int j = 0; j < size; j++)
        {
            free(data[i][j]);
        }
        free(data[i]);
    }
    return new_cdataframe;
}

/**
 * @brief : Hard fill CDATAFRAME
 * @param 1 : Column type
 * @param 2 : Number of column
 * @param 3 : Data
 * @param 4 : Size of each column
 * @return : Pointer to the CDATAFRAME
 */
CDATAFRAME* fill_hard_cdataframe(ENUM_TYPE* types, int size, char*** data, int* cols_size)
{
    CDATAFRAME* new_cdataframe = create_empty_cdataframe();

    for (int i = 0; i < size; i++)
    {
        COLUMN* new_column = create_column(types[i], "");
        for (int j = 0; j < cols_size[0]; j++)
        {
            unsigned int val1;
            int val2;
            float val3;
            double val4;
            switch (new_column->column_type)
            {
            case UINT:
                val1 = (unsigned int) atol(data[j][i]);
                insert_value(new_column, &val1);
                break;
                
            case INT:
                val2 = (int) atoi(data[j][i]);
                insert_value(new_column, &val2);
                break;
                
            case CHAR:
                insert_value(new_column, &data[j][i][0]);
                break;
                
            case FLOAT:
                val3 = (float) atof(data[j][i]);
                insert_value(new_column, &val3);
                break;
                
            case DOUBLE:
                val4 = (double) atof(data[j][i]);
                insert_value(new_column, &val4);
                break;
                
            case STRING:
                insert_value(new_column, data[j][i]);
                break;
            
            default:
                break;
            }
        }
        add_col(new_cdataframe, new_column);
        // print_col(new_column);
    }
    return new_cdataframe;
}

// Printing

/**
 * @brief : Print the entire CDATAFRAME
 * @param1 : The CDATAFRAME
 */
void print_cdataframe(CDATAFRAME* cdataframe)
{
    print_partial_cdataframe(cdataframe, count_row(cdataframe), get_cdataframe_cols_size(cdataframe));
}

/**
 * @brief : Print a part of the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Number of row to print
 * @param3 : Number of column to print
 */
void print_partial_cdataframe(CDATAFRAME* cdataframe, int row, int col)
{
    if (cdataframe!=NULL)
    {
        int row_count = count_row(cdataframe);
        int col_count = get_cdataframe_cols_size(cdataframe);
        printf("\n\n");
        print_cols_names(cdataframe);
        for (int i = 0; i < row_count && i < row; i++)
        {
            for (int j = 0; j < col_count && j < col; j++)
            {
                print_cdataframe_value(cdataframe, i, j);
                printf("\t\t");
            }
            printf("\n");
        }
    }
    printf("\n\n");
}

/**
 * @brief : Print a value from the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Row of value to print
 * @param3 : Column of value to print
 */
void print_cdataframe_value(CDATAFRAME* cdataframe, int row, int col)
{
    if (cdataframe!=NULL && col < get_cdataframe_cols_size(cdataframe))
    {
        lnode* node = get_first_node(cdataframe);
        for (int i = 0; i < col; i++)
        {
            node = get_next_node(cdataframe, node);
        }
        switch (((COLUMN*)node->data)->column_type)
        {
        case UINT:
            printf("%d", *((unsigned int*)((COLUMN*)node->data)->data[row]));
            break;
            
        case INT:
            printf("%d", *((int*)((COLUMN*)node->data)->data[row]));
            break;
            
        case CHAR:
            printf("%c", *((char*)((COLUMN*)node->data)->data[row]));
            break;
            
        case FLOAT:
            printf("%f", *((float*)((COLUMN*)node->data)->data[row]));
            break;
            
        case DOUBLE:
            printf("%f", *((double*)((COLUMN*)node->data)->data[row]));
            break;
            
        case STRING:
            printf("%s", (char*)((COLUMN*)node->data)->data[row]);
            break;
            
        case STRUCTURE:
            printf("%p", ((COLUMN*)node->data)->data[row]);
            break;
        
        default:
            break;
        }
    }
}

/**
 * @brief : Print a value from the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Row of value to print
 * @param3 : Column of value to print
 */
char* get_cdataframe_value(CDATAFRAME* cdataframe, int row, int col)
{
    if (cdataframe!=NULL && col < get_cdataframe_cols_size(cdataframe))
    {
        lnode* node = get_first_node(cdataframe);
        for (int i = 0; i < col; i++)
        {
            node = get_next_node(cdataframe, node);
        }
        char* str = (char*) malloc(STRING_SIZE * sizeof(char));
        convert_value((COLUMN*)node->data, row, str, STRING_SIZE);
        return str;
    }
    return "NULL";
}

// Usual operations

/**
 * @brief : Print a value from the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Number of the column
 * @return : The column type
 */
ENUM_TYPE get_col_type(CDATAFRAME* cdataframe, int col)
{
    if (cdataframe!=NULL)
    {
        lnode* node = get_first_node(cdataframe);
        for (int i = 0; i < col; i++)
        {
            node = get_next_node(cdataframe, node);
        }
        return ((COLUMN*)node->data)->column_type;
    }
    return NULLVAL;
}

/**
 * @brief : Add a row to the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Datas of the row to add
 * @return : 1 if the row has been added, 0 otherwise
 */
int add_row(CDATAFRAME* cdataframe, list* row)
{
    if (cdataframe!=NULL && row!=NULL)
    {
        lnode* node_cdtf = cdataframe->head;
        lnode* node_row = row->head;
        while (node_cdtf!=NULL && node_row!=NULL)
        {
            insert_value((COLUMN*)node_cdtf->data, node_row->data);
            node_cdtf = get_next_node(cdataframe, node_cdtf);
            node_row = get_next_node(row, node_row);
        }
        return 1;
    }
    return 0;
}

/**
 * @brief : Delete a row from the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Index of the row to delete
 * @return : 1 if the row has been deleted, 0 otherwise
 */
int delete_row(CDATAFRAME* cdataframe, int row)
{
    bool result = true;
    lnode* node = get_first_node(cdataframe);
    while (node!=NULL)
    {
        delete_value((COLUMN*)node->data, row);
        node = get_next_node(cdataframe, node);
    }
    
    return result;
}

/**
 * @brief : Add a column to the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The column to add
 */
void add_col(CDATAFRAME* cdataframe, COLUMN* column)
{
    lnode* node = lst_create_lnode(column);
    lst_insert_tail(cdataframe, node);
}

/**
 * @breif: Delete column by name
 * @param1: Pointer to the CDataframe
 * @param2: Column name
 */
void cdataframe_delete_column(CDATAFRAME *cdf, char *col_name)
{
    lnode* col_to_delete = get_first_node(cdf);
    bool delete = false;
    while (col_to_delete->next!=NULL && delete==false)
    {
        if (strcmp(((COLUMN*)col_to_delete->data)->title, col_name)==0)
        {
            delete = true;
            break;
        }
        col_to_delete = get_next_node(cdf, col_to_delete);
    }
    if (delete)
    {
        lst_delete_lnode(cdf, col_to_delete);
    }
}

/**
 * @brief : Rename a column of the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Index of the column to rename
 * @param3 : The new name
 */
void rename_col(CDATAFRAME* cdataframe, int col, char* new_name)
{
    lnode* node = NULL;
    if (col>=0 && col<get_cdataframe_cols_size(cdataframe))
    {
        node = get_first_node(cdataframe);
        for (int i = 0; i < col; i++)
        {
            node = get_next_node(cdataframe, node);
        }
    }
    if (node!=NULL)
    {
        strcpy(((COLUMN*)node->data)->title, new_name);
    }
}

/**
 * @brief : Search a value in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The value to search
 * @return : 1 if the value exist in the CDATAFRAME, 0 otherwise
 */
int find(CDATAFRAME* cdataframe, void* x)
{
    if (cdataframe!=NULL && x!=NULL)
    {
        lnode* node = get_first_node(cdataframe);
        while (node!=NULL)
        {
            if (search_value_in_column((COLUMN*)node->data, x)==1)
            {
                return 1;
            }
            node = get_next_node(cdataframe, node);
        }
    }
    return 0;
}

/**
 * @brief : Get a value from the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Row of the value to get
 * @param3 : Column of the value to get
 * @return : The value
 */
void* get_val_at(CDATAFRAME* cdataframe, int row, int col)
{
    if (cdataframe!=NULL && col<get_cdataframe_cols_size(cdataframe))
    {
        lnode* node = get_first_node(cdataframe);
        for (int i = 0; i < col; i++)
        {
            node = get_next_node(cdataframe, node);
        }
        if (row < ((COLUMN*)node->data)->size)
        {
            return ((COLUMN*)node->data)->data[row];
        }
    }
    return NULL;
}

/**
 * @brief : Replace a value in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The new value
 * @param3 : Row of the value to replace
 * @param4 : Column of the value to replace
 * @return : 1 if the element has been replaced, 0 otherwise
 */
int replace_val_at(CDATAFRAME* cdataframe, void* new_val, int row, int col)
{
    if (cdataframe!=NULL && col<get_cdataframe_cols_size(cdataframe))
    {
        lnode* node = get_first_node(cdataframe);
        for (int i = 0; i < col; i++)
        {
            node = get_next_node(cdataframe, node);
        }
        if (row < ((COLUMN*)node->data)->size)
        {
            ((COLUMN*)node->data)->data[row] = new_val;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief : Print a column name
 * @param1 : The CDATAFRAME
 * @param2 : Index of the column
 */
void print_col_name(CDATAFRAME* cdataframe, int col)
{
    if (cdataframe!=NULL)
    {
        lnode* node = get_first_node(cdataframe);
        for (int i = 0; i < col; i++)
        {
            node = get_next_node(cdataframe, node);
        }
        printf("%s\n", *((COLUMN*)node->data)->title);
    }
}

/**
 * @brief : Print all columns names
 * @param1 : The CDATAFRAME
 */
void print_cols_names(CDATAFRAME* cdataframe)
{
    if (cdataframe!=NULL)
    {
        lnode* node = get_first_node(cdataframe);
        while (node!=NULL)
        {
            printf("%s\t\t", *((COLUMN*)node->data)->title);
            node = get_next_node(cdataframe, node);
        }
    }
    printf("\n");
}

// Analysis and statistics

/**
 * @brief : Count the number of row in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @return : The number of row
 */
int count_row(CDATAFRAME* cdataframe)
{
    int count = 0;
    if (cdataframe!=NULL)
    {
        //lnode* node = get_first_node(cdataframe);
        lnode* node = cdataframe->head;
        while (node!=NULL)
        {
            count = (count < (((COLUMN*)node->data))->size) ? ((COLUMN*)node->data)->size : count;
            //node = get_next_node(cdataframe, node);
            node = node->next;
        }
    }
    return count;
}

/**
* @brief: Number of columns
* @param1: Point to the CDataframe
* @return: Number of columns in the CDataframe
*/
int get_cdataframe_cols_size(CDATAFRAME *cdf)
{
    int count = 0;
    if (cdf!=NULL)
    {
        lnode* node = get_first_node(cdf);
        while (node!=NULL)
        {
            count++;
            node = get_next_node(cdf, node);
        }
    }
    return count;
}

/**
 * @brief : Count the number of items equals to x in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The value x
 * @return : The number of items equals to x in the CDATAFRAME
 */
int count_equals_to(CDATAFRAME* cdataframe, void* x)
{
    int count = 0;
    if (cdataframe!=NULL)
    {
        lnode* node = get_first_node(cdataframe);
        while (node!=NULL)
        {
            count += col_count_equals_to((COLUMN*)node->data, x);
            node = get_next_node(cdataframe, node);
        }
    }
    return count;
}

/**
 * @brief : Count the number of items greater than x in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The value x
 * @return : The number of items greater than x in the CDATAFRAME
 */
int count_greater_than(CDATAFRAME* cdataframe, void* x)
{
    int count = 0;
    if (cdataframe!=NULL)
    {
        lnode* node = get_first_node(cdataframe);
        while (node!=NULL)
        {
            count += col_count_greater_than((COLUMN*)node->data, x);
            node = get_next_node(cdataframe, node);
        }
    }
    return count;
}

/**
 * @brief : Count the number of items less than x in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The value x
 * @return : The number of items less than x in the CDATAFRAME
 */
int count_less_than(CDATAFRAME* cdataframe, void* x)
{
    int count = 0;
    if (cdataframe!=NULL)
    {
        lnode* node = get_first_node(cdataframe);
        while (node!=NULL)
        {
            count += col_count_less_than((COLUMN*)node->data, x);
            node = get_next_node(cdataframe, node);
        }
    }
    return count;
}

/**
 * @brief: Delete a CDataframe
 * param1: Pointer to the CDataframe to delete
 */
void delete_cdataframe(CDATAFRAME **cdf)
{
    lst_create_list(*cdf);
}

/**
 * @brief: Create a CDataframe from csvfile
 * @param1: CSV filename
 * @param2: Array of types
 * @param3: Size of array in param2
 */
CDATAFRAME* load_from_csv(char *file_name, ENUM_TYPE *dftype, int size)
{
    CDATAFRAME* new_cdataframe = lst_create_list();
    FILE* file = NULL;
    file = fopen(file_name, "r");
    if (file!=NULL)
    {
        char ***data = (char***)malloc(REALOC_SIZE * sizeof(char**));
        for (int i = 0; i < REALOC_SIZE; i++)
        {
            data[i] = (char**)malloc(size * sizeof(char*));
            for (int j = 0; j < size; j++)
            {
                data[i][j] = (char*)malloc(STRING_SIZE * sizeof(char));
            }
        }
        
        char line[10 * STRING_SIZE];
        int cols_size[size];
        for (int i = 0; i < size; i++)
        {
            cols_size[i] = 0;
        }
        while (fgets(line, sizeof(line), file)!=NULL)
        {
            char* token = strtok(line, ",");
            for (int i = 0; i < size; i++)
            {
                strcpy(data[cols_size[i]][i], token);
                for (int j = 0; j < sizeof(data[cols_size[i]][i]); j++)
                {
                    if (data[cols_size[i]][i][j]=='\n')
                    {
                        data[cols_size[i]][i][j] = ' ';
                    }
                    
                }
                token = strtok(NULL, ",");
                cols_size[i]++;
            }
        }
        new_cdataframe = fill_hard_cdataframe(dftype, size, data, cols_size);
        fclose(file);
        for (int i = 0; i < REALOC_SIZE; i++)
        {
            for (int j = 0; j < size; j++)
            {
                free(data[i][j]);
            }
            free(data[i]);
        }
        free(data);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier !!");
    }
    return new_cdataframe;
}

/**
 * @brief: Export into a csvfile
 * @param1: Pointer to the CDataframe
 * @param2: csv filename where export file, if the file exists,
 * it will be overwritten
 */
void save_into_csv(CDATAFRAME *cdf, char *file_name)
{
    FILE* file = NULL;
    file = fopen(file_name, "w");
    if (file!=NULL && cdf!=NULL)
    {
        int row = count_row(cdf);
        int col = get_cdataframe_cols_size(cdf);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                fprintf(file, "%s", get_cdataframe_value(cdf, i, j));
                if (j!=col-1)
                {
                    fprintf(file, ",");
                }
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier !!");
    }
}