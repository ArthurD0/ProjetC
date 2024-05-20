#include "cdataframe.h"
#include "sort.h"

int main ()
{
    COLUMN *mycol = create_column(INT, "sorted column");
    int a = 52;
    int b = 44;
    int c = 15;
    int d = 18;
    insert_value(mycol, &a);
    insert_value(mycol, &b);
    insert_value(mycol, &c);
    insert_value(mycol, &d);
    printf("Column content before sorting : \n");
    print_col(mycol);
    sort(mycol,ASC);
    printf("Column content after sorting : \n");
    print_col_by_index(mycol);
    delete_column(&mycol);

    COLUMN *mycol1 = create_column(STRING, "String column");
    insert_value(mycol1, "Lima");
    insert_value(mycol1, "Bravo");
    insert_value(mycol1, "Zulu");
    insert_value(mycol1, "Tango");
    printf("\n\nColumn content before sorting : \n");
    print_col(mycol1);
    sort(mycol1,ASC);
    printf("Column content after sorting : \n");
    print_col_by_index(mycol1);
    delete_column(&mycol1);

    ENUM_TYPE cdftype [] = {INT,STRING,FLOAT};
    CDATAFRAME *cdf = load_from_csv("input.csv", cdftype, 3);
    //cdf = fill_cdataframe();
    printf("\n\nAFFICHAGE DU CDATAFRAME :\n");
    print_cdataframe(cdf);
    save_into_csv(cdf, "output.csv");
    delete_cdataframe(&cdf);
    return 0;
}