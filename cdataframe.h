#include "list.h"
#include "column.h"

typedef list CDATAFRAME;

// Alimentation

/**
 * @brief : Create a CDATAFRAME
 * @param1 : Columns types
 * @param2 : Number of column
 * @return : Pointer to created CDATAFRAME
 */
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);

/**
 * @brief : Fill the CDATAFRAME
 * @param1 : The CDATAFRAME to fill
 * @return : Pointer to the full CDATAFRAME
 */
CDATAFRAME* fill_cdataframe(CDATAFRAME* cdataframe);

/**
 * @brief : Hard fill CDATAFRAME
 * @param1 : The CDATAFRAME to fill
 * @return : Pointer to the CDATAFRAME
 */
CDATAFRAME* fill_hard_cdataframe(CDATAFRAME* cdataframe);

// Printing

/**
 * @brief : Print the entire CDATAFRAME
 * @param1 : The CDATAFRAME
 */
void print_cdataframe(CDATAFRAME* cdataframe);

/**
 * @brief : Print a part of the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Number of row to print
 * @param3 : Number of column to print
 */
void print_partial_cdataframe(CDATAFRAME* cdataframe, int row, int col);

// Usual operations

/**
 * @brief : Add a row to the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Datas of the row to add
 * @return : 1 if the row has been added, 0 otherwise
 */
int add_row(CDATAFRAME* cdataframe, list* row);

/**
 * @brief : Delete a row from the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Index of the row to delete
 * @return : 1 if the row has been deleted, 0 otherwise
 */
int delete_row(CDATAFRAME* cdataframe, int row);

/**
 * @brief : Add a column to the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The column to add
 */
void add_col(CDATAFRAME* cdataframe, COLUMN* column);

/**
 * @breif: Delete column by name
 * @param1: Pointer to the CDataframe
 * @param2: Column name
 */
void delete_column(CDATAFRAME *cdf, char *col_name);

/**
 * @brief : Rename a column of the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Index of the column to rename
 * @param3 : The new name
 */
void rename_col(CDATAFRAME* cdataframe, int col, char* new_name);

/**
 * @brief : Search a value in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The value to search
 * @return : 1 if the value exist in the CDATAFRAME, 0 otherwise
 */
int find(CDATAFRAME* cdataframe, void* x);

/**
 * @brief : Get a value from the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : Row of the value to get
 * @param3 : Column of the value to get
 * @return : The value
 */
void* get_val_at(CDATAFRAME* cdataframe, int row, int col);

/**
 * @brief : Replace a value in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The new value
 * @param3 : Row of the value to replace
 * @param4 : Column of the value to replace
 * @return : 1 if the element has been replaced, 0 otherwise
 */
int replace_val_at(CDATAFRAME* cdataframe, void* new_val, int row, int col);

/**
 * @brief : Print a column name
 * @param1 : The CDATAFRAME
 * @param2 : Index of the column
 */
void print_col_name(CDATAFRAME* cdataframe, int col);

/**
 * @brief : Print all columns names
 * @param1 : The CDATAFRAME
 */
void print_cols_names(CDATAFRAME* cdataframe);

// Analysis and statistics

/**
 * @brief : Count the number of row in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @return : The number of row
 */
int count_row(CDATAFRAME* cdataframe);

/**
* @brief: Number of columns
* @param1: Point to the CDataframe
* @return: Number of columns in the CDataframe
*/
int get_cdataframe_cols_size(CDATAFRAME *cdf);

/**
 * @brief : Count the number of items equals to x in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The value x
 * @return : The number of items equals to x in the CDATAFRAME
 */
int count_equals_to(CDATAFRAME* cdataframe, void* x);

/**
 * @brief : Count the number of items greater than x in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The value x
 * @return : The number of items greater than x in the CDATAFRAME
 */
int count_greater_than(CDATAFRAME* cdataframe, void* x);

/**
 * @brief : Count the number of items less than x in the CDATAFRAME
 * @param1 : The CDATAFRAME
 * @param2 : The value x
 * @return : The number of items less than x in the CDATAFRAME
 */
int count_less_than(CDATAFRAME* cdataframe, void* x);

/**
 * @brief: Column deletion
 * param1: Pointer to the CDataframe to delete
 */
void delete_cdataframe(CDATAFRAME **cdf);

/**
 * @brief: Create a CDataframe from csvfile
 * @param1: CSV filename
 * @param2: Array of types
 * @param3: Size of array in param2
 */
CDATAFRAME* load_from_csv(char *file_name, ENUM_TYPE *dftype, int size);

/**
 * @brief: Export into a csvfile
 * @param1: Pointer to the CDataframe
 * @param2: csv filename where export file, if the file exists,
 * it will be overwritten
 */
void save_into_csv(CDATAFRAME *cdf, char *file_name);
