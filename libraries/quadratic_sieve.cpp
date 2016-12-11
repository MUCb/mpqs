#include <vector>
#include <stdint.h>
#include <stdio.h>

#include "bin_matrix.h"
#include "greatest_common_divisor.h"


int fill_matrix(bin_matrix_t &m1, std::vector<int> &smooth_num, std::vector< std::vector<uint64_t> > &v_exp)
{
    int count = 0;

    // DEBUG(3, "%s %d \n",__func__, __LINE__);
    // DEBUG(3, "%s %d filled \n",__func__, m1.filled);
    // DEBUG(3, "%s %d size \n",__func__, m1.size);
    if ((m1.row_size) == m1.filled)
        return count;

    DEBUG(4, "%s %d \n",__func__, __LINE__);
    for (int i = 0; i < smooth_num.size() && ((m1.row_size) != m1.filled); ++i) {
        // DEBUG(3, "%s %d iteration\n",__func__, i);
        // DEBUG(3, "%s %d filled \n",__func__, m1.filled);
        // DEBUG(3, "%s %d size \n",__func__, m1.size);
        // DEBUG(3, "%s %d smooth_num \n",__func__, smooth_num[i]);
        if (smooth_num[i] != -1) {
            // DEBUG(3, "%s %d added\n",__func__, smooth_num[i]);
            m1.add_row(v_exp[ smooth_num[i]]);
            smooth_num[i] = -1;
            // DEBUG(3, "%s %d =added\n",__func__, smooth_num[i]);
            count++;
        }
    }
    return count;
}


int find_solution (bin_matrix_t m2, 
                    std::vector<int> &smooth_num_back, 
                    std::vector<int> &smooth_num, 
                    std::vector< std::vector<uint64_t> > &v_exp,
                    const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N)
{

    std::vector<int64_t> P11;
    int retval = fill_matrix(m2, smooth_num_back, v_exp);
    m2.show();
    // for (int i = 0; i < smooth_num_back.size() ; ++i) {
    //  DEBUG(3, "%s %d smooth_num \n",__func__, smooth_num_back[i]);
    // }

    bin_matrix_t m1 = m2;
    DEBUG(2, "%d added\n", retval);
    if (retval == 0 )
        return 0;


    int null_line = m1.resolve_matrix();
    // m1.show();
    // return 0;


    if (null_line > -1)
    {
        for (uint64_t i = 0; i <  m1.row_size; ++i)
        {
            DEBUG (2,"%ld\n", m1.unit_matrix[null_line][i]);
            if( m1.unit_matrix[null_line][i] > 0)
            {
                DEBUG (2,"num = %d\t", smooth_num[i]);
                // if (i == 0 )
                // {
                    // DEBUG (1,"Strange\n");
                    // continue;
                // } else
                // {
                    DEBUG (2,"Y  = %ld\n", Y[smooth_num[i]]);
                    P11.push_back(smooth_num[i]);
                // }
            }
        }
        DEBUG (2,"\n");

        int found = 0;
        found = euclid_gcd( X, Y, P11, p, q, N);
        // printf("found %lu\n", found);
        m1.show();
        if (found) {
            return null_line;
        }
        else {

            int max_i = 0;
            max_i = m2.max_unit_num(m1.unit_matrix[null_line]);

            DEBUG (3," iter %d\n",max_i );
            m2.show();
            m2.delete_row(max_i);
            DEBUG (4,"===== %d \n", smooth_num_back[max_i]);
            smooth_num_back.erase(smooth_num_back.begin() + max_i);
            smooth_num.erase(smooth_num.begin() + max_i);
            m2.show();


            // return find_solution(m2, smooth_num_back);
            null_line = find_solution(m2, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N);
            DEBUG(3, "finish %d\n", null_line);
            if (null_line == 0)
                ERROR("failed ");

        }
    }
    else if (null_line < -1)
    {
        int max_i = -(null_line + 10);
        // m2.show();
        m2.delete_row(max_i);
        DEBUG (4,"===== %d \n", smooth_num_back[max_i]);
        smooth_num_back.erase(smooth_num_back.begin() + max_i);
        smooth_num.erase(smooth_num.begin() + max_i);

        null_line = find_solution(m2, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N);
            DEBUG(3, "finish %d\n", null_line);
            if (null_line == 0)
                ERROR("failed ");
    }
    else
    {
            int max_i = 0;
            m2.show();
            m2.delete_row(max_i);
            DEBUG (4,"===== %d \n", smooth_num_back[max_i]);
            smooth_num_back.erase(smooth_num_back.begin() + max_i);
            smooth_num.erase(smooth_num.begin() + max_i);
            m2.show();


            // return find_solution(m2, smooth_num_back);
            null_line = find_solution(m2, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N);
            DEBUG(3, "finish %d\n", null_line);
            if (null_line == 0)
                ERROR("failed ");
    }

    return null_line;
}