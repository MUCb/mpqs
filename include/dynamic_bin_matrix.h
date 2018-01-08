#ifndef BIN_MATRIX
#define BIN_MATRIX

#include "log.h"
#include <vector>
#include <stdint.h>

class bin_matrix_t {
public: 
    int collumn_size;
    int filled;
    bin_matrix_t();
    bin_matrix_t(int size);
    int add_row(std::vector<uint64_t> v1);
    std::vector< std::vector<uint64_t> > matrix;
    std::vector< std::vector<uint64_t> > unit_matrix;
    std::vector<long int> triangular_v;

    int  make_upper_triangular(void);
    int  make_upper_triangular_static(void);
    void count_unit_num( void );
    int max_unit_num(std::vector<uint64_t> selected_row);
    int delete_row(unsigned int iter);
    

    std::vector<int> unit_num;
    int row_size;
    // int unit_matrix_size;
    void init_unit(void);
    void show(void);
    int  make_lower_triangular(void);
    // int m_size(void);
    int resolve_matrix( void);
};

// bin_matrix_t::bin_matrix_t();
// bin_matrix_t::bin_matrix_t(int size);
// // int bin_matrix_t::m_size(void)
// void bin_matrix_t::init_unit(void);
// void bin_matrix_t::show(void);
// void bin_matrix_t::add_row(std::vector<uint64_t> row_v);
// void bin_matrix_t::delete_row(int row_number);
// int  bin_matrix_t::make_upper_triangular(void);
// void bin_matrix_t::count_unit_num( void );
// int bin_matrix_t::max_unit_num(std::vector<uint64_t> selected_row);
// int  bin_matrix_t::make_lower_triangular(void);
// int bin_matrix_t::resolve_matrix();

#endif
