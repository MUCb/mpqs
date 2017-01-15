#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>
#include <unistd.h>

#include "dynamic_bin_matrix.h"

bin_matrix_t::bin_matrix_t(){
    // printf("bin_matrix_t empty\n");
}

bin_matrix_t::bin_matrix_t(int size) : collumn_size(size), filled(0) {
}

// int bin_matrix_t::m_size(void)
// {
//     return rasize;
// }

// void bin_matrix_t::init_unit(void)
// {
//     // don't feel the last row
//     for (int row = 0; row < unit_matrix_size; ++row)
//     {
//         unit_num[row] = 0;
//         for (int col = 0; col < unit_matrix_size; ++col)
//         {
//             if(row == col)
//                 unit_matrix[row][col] = 1;
//             else
//                 unit_matrix[row][col] = 0;

//             DEBUG (4,"%ld\t", unit_matrix[row][col]);
//         }
//         DEBUG (4,"\n");
//     }
// }

int bin_matrix_t::add_row(std::vector<uint64_t> row_v)
{
    if (row_v.size() == collumn_size){

        matrix.push_back(std::vector<uint64_t>() );
        matrix[filled].insert(matrix[filled].end(), row_v.begin(), row_v.end());

        ERROR("%s %d\n", __func__, __LINE__);
        for (int col = 0; col < collumn_size; ++col) {
            matrix[filled][col] %= 2;
        }
        ERROR("%s %d\n", __func__, __LINE__);
        ERROR("filled  %d\n", filled);

        // show();

        unit_matrix.push_back(std::vector<uint64_t>(filled) );
        
        ERROR("%s %d\n", __func__, __LINE__);
        filled++;
        for (int i = 0; i < filled; ++i)
        {
            unit_matrix[i].push_back(0);
        }
        unit_matrix[filled -1][filled -1] = 1;

        return 1;
    }
    else {
        ERROR("Size of vector = %d is different from matrix size = %d", 
            row_v.size(), collumn_size);
        return 0;
    }
}

void bin_matrix_t::show(void){
        // just print exponent mod 2 array
    DEBUG (3,"matrix \n");
    for (int row = 0; row < filled; ++row)
    {
        for (int col = 0; col < collumn_size; ++col)
        {
            DEBUG (3,"%lu\t", matrix[row][col]);
        }
        DEBUG(3, "\n");
    }

    DEBUG (3,"\n");
    DEBUG (3,"unit matrix\n");
    for (int row = 0; row < filled; ++row)
    {
        for (uint64_t col = 0; col <  filled; ++col)
        {
            DEBUG (3,"%"PRIu64"\t", unit_matrix[row][col]);
        }
        DEBUG (3,"\n");
    }
    DEBUG (3,"\n");
}


int bin_matrix_t::delete_row(unsigned int row_number)
{
    if (filled > row_number){
        DEBUG(3, "%s %d row_number: %d filled: %d\n",__func__, __LINE__, row_number, filled);
        for (int row = row_number; row < filled  ; ++row)
        {
            DEBUG(4, "%s %d \n",__func__, __LINE__);
            for (int col = 0; col < unit_matrix_size; ++col)
            {
                DEBUG(4, "%s %d row=|%d| col=|%d|\n",__func__, __LINE__, row, col);
                if (row == (filled - 1))
                    matrix[row][col] = 0;
                else
                    matrix[row][col] = matrix[row+1][col];
            }
            
        }
        DEBUG(4, "%s %d \n",__func__, __LINE__);
        filled--;
        DEBUG(4, "%s %d filled %d\n",__func__, __LINE__, filled);
        return 1;
    } else 
        return 0;
}



int  bin_matrix_t::make_upper_triangular(void)
{
    int current_col = 0;
    int current_row = 0;
    int null_line = -1;
    if (filled == 0 || filled == 1 )
        return null_line;

    for (int i = 0; i < filled ; ++i)
    {

        int row_nonnull;
        // find first non zero value. it will be in row.
        for (row_nonnull = current_row; row_nonnull < filled; ++row_nonnull) 
        {
            if (matrix[row_nonnull][current_col] == 1)
                break;
        }

        DEBUG (3,"row_nonnull=%d current_row=%d filled=%d current_col=%d\n", 
        row_nonnull, current_row, filled, current_col);

        // row should be less then unit_matrix_size , otherwise all value are zero
        if(row_nonnull == filled ){
            WARN (1, "We havn't find values in column %d \n", current_col);
            current_col++;
            continue;
        } else if( row_nonnull > current_row && row_nonnull < filled) {
            DEBUG(3, "i = %d row_nonnull = %d\n", i, row_nonnull);
            matrix[row_nonnull].swap(matrix[current_row]);
            unit_matrix[row_nonnull].swap(unit_matrix[current_row]);
        }

        // remove all value under the first one
        for (int row = current_row + 1; row < filled; ++row) {
            if(matrix[row][current_col] != 0) {
                DEBUG(3, "CHAECK  %d \n", collumn_size);
                // show();
                for (int col = 0; col < collumn_size; ++col) {
                    
                    // DEBUG(3, "matrix r = %d c=%d m=%ld\n", r, c, matrix[row][col]);
                    matrix[row][col] += matrix[current_row][col];
                    matrix[row][col] %= 2;
                    DEBUG(4, "matrix row = %d col=%d m=%ld\n", row, col, matrix[row][col]);

                }
                for (int col = 0; col < filled; ++col) {
                    unit_matrix[row][col] += unit_matrix[current_row][col];
                    unit_matrix[row][col] %= 2; // remove unnecessary moves
                                            // if we use two the same lines they remove each other.
                }
            }
            // show();
            if ( std::find(matrix[row].begin(), matrix[row].end(), 1) == matrix[row].end() ) {
                    DEBUG (1,"nULLL upper j=%d coll=%d\n", row, current_col);
                    // DEBUG (3," smooth_num \n");
                    null_line = row;
                    break;
            }
            // show();
        }

        if (null_line != -1)
            break;

        show();
        current_col++;
        current_row++;
    }
    show();
    return null_line;
}

void bin_matrix_t::count_unit_num( void )
{
    for (int row = 0; row < row_size; ++row)
    {
        unit_num[row] = 0;
        for (int cal = 0; cal < collumn_size; ++cal)
        {
            if (matrix[row][cal] == 1){
                unit_num[row] += 1;
            }
        }
    }
}

int bin_matrix_t::max_unit_num(std::vector<uint64_t> selected_row)
{
    count_unit_num();
    int max_unit = 0;
    int max_iter = 0;
    for (int iter = 0; iter < unit_matrix_size; ++iter)
    {
        DEBUG(3, "%lu\t", selected_row[iter]);
        if (selected_row[iter] == 1){
            if (unit_num[iter] > max_unit){
                max_unit = unit_num[iter];
                max_iter = iter;
            }
        }
    }
    // printf("max %d\n", max_unit);
    DEBUG(3, "\n");
    return max_iter;
}



int  bin_matrix_t::make_lower_triangular(void) 
{
    // printf("tpp1 size %d\n", tpp1.size());
    int null_line = -1;
    for (int i = (unit_matrix_size -1) ; i > 0; --i)
    {
        if (matrix[i][i] != 1) {
            WARN(1, "we have zero value in main diagonal, line: %d\n", i);
            continue;
        }

        for (int row = i-1; row >= 0; --row)
        {
            DEBUG(3, "check row=%d\n", row);
            if(matrix[row][i] != 0)
            {
                DEBUG(2, "change row=%d\n", row);
                for (int col = 0; col < collumn_size; ++col) {
                    matrix[row][col] += matrix[i][col];
                    matrix[row][col] %= 2;

                    unit_matrix[row][col] += unit_matrix[i][col];
                    // unit_matrix[r][c] %= 2;  // ???????
                }
            }

            if ( std::find(matrix[row].begin(), matrix[row].end(), 1) == matrix[row].end() ) {
                    DEBUG (3,"nULLL lower %d\n", row);
                    null_line = row;
            }
        }

        if (null_line != -1)
            break;

    show();

    }
    return null_line;

}


int bin_matrix_t::resolve_matrix()
{
    std::vector<uint64_t> P11;
    uint64_t found = 0;

    show();
    int null_line = make_upper_triangular();
    DEBUG(2, "upper triangular\n");
    // show();


    if (null_line != -1) {
        return null_line;
    }

    // exit(0);

    null_line = make_lower_triangular();
    DEBUG(2, "lower triangular\n");
    show();

    if (null_line != -1) {
        return null_line;
    }

    DEBUG(1, " last \n");
    for (int c = 0; c < unit_matrix_size; ++c) {
        if (matrix[row_size - 1][c]  == 1) {
            for (int r = 0; r < row_size; ++r) {
                matrix[row_size - 1][r] += matrix[c][r];
                matrix[row_size - 1][r] %= 2;

                unit_matrix[row_size - 1][c] += unit_matrix[c][r];
                unit_matrix[row_size - 1][c] %= 2;
            }
        }
    }
    if(matrix[row_size-1][row_size-1] != 0 ) {
        ERROR("no resolv\n");
    } else{
        null_line = row_size -1;
    }
    DEBUG(3, " last \n");
    
    return null_line;

}

