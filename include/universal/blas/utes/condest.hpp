/** **********************************************************************
 * Estimated Condition number of matrix 
 *
 * @author:     James Quinlan
 * @date:       2022-12-13
 * @copyright:  Copyright (c) 2022 Stillwater Supercomputing, Inc.
 * @license:    MIT Open Source license 
 * 
 * This file is part of the universal numbers project.
 * ***********************************************************************
 */
#pragma once
#include <universal/blas/matrix.hpp>
#include <universal/blas/vector.hpp>
#include <universal/blas/blas.hpp>
// #include <universal/blas/solvers/plu.hpp>
#include <universal/blas/solvers/lu.hpp>
#include <universal/blas/solvers/backsub.hpp>
#include <universal/blas/solvers/forwsub.hpp>
#include <universal/blas/utes/matnorm.hpp>
#include <tuple>
 
namespace sw { namespace universal { namespace blas {  
template<typename Scalar>
std::tuple<matrix<Scalar>, matrix<Scalar>> plu(const matrix<Scalar>& A){ 

    using Matrix = sw::universal::blas::matrix<Scalar>;
    using namespace std;

    Scalar x;
    size_t n = num_rows(A);
    // Matrix P(n,n);
    Matrix L(n,n);
    Matrix U(n,n);

    // P = 1;
    L = 1;
    U = A;

    // Elimination Process
    for (size_t i = 0; i < n-1; ++i){ // i-th row
        Scalar absmax = abs(U(i,i)); 
        size_t argmax = i;

        // Select k >= i to maximize |U(k,i)| 
        for (size_t k = i + 1; k < n; ++k){ // subsequent row (ele. in column k)
            if (abs(U(k,i)) > absmax){
                absmax = abs(U(k,i));
                argmax = k;
            }
        }
        // Check for necessary swaps
        if (argmax != i){
            // Swap rows loop
            for (size_t j = i; j < n;++j){
                x = U(i,j);
                U(i,j) = U(argmax,j);
                U(argmax,j) = x;
            }
           // for (size_t j = 0; j < n;++j){
           //     x = P(i,j);
           //     P(i,j) = P(argmax,j);
           //     P(argmax,j) = x;
           // }
                // Permuate entries in L to match P
            for (size_t j = 0; j < i; ++j){
                x = L(i,j);
                L(i,j) = L(argmax,j);
                L(argmax,j) = x;
            }
        }
        // Continue with row reduction
        for (size_t k = i + 1; k < n; ++k){  // objective row
        
            // Is there a minpos for Scalar?  including double etc.
            L(k,i) = U(k,i) / U(i,i);
            for (size_t j = i; j < n; ++j){
                U(k,j) = U(k,j) - L(k,i)*U(i,j);
            }
        }
    }
    U = triu(U);
    return std::make_tuple(L,U); 
} // LU
}}} // namespace sw::universal::blas



template<typename Scalar>
Scalar condest(const sw::universal::blas::matrix<Scalar> & A){
/**
 * After changing from [P,L,U] = plu(A) to inplace version of plu,
 * condest has stopped working.  Need to fix, however, as long as
 * showCondest = false; LUIR.cpp will run.   
 */

    Scalar Na  = matnorm(A,1);    // || A ||
    Scalar Ni  = 1;               // || A^{-1} ||
    sw::universal::blas::vector<Scalar> b(num_cols(A),1);
    
    auto [L, U] = plu(A);
    auto z = forwsub(U.transpose(),b);
    auto x = backsub(L.transpose(),z);
    // auto y = solve((L*U), x);  // x = (LU')^(-1)*b
    auto y = backsub(U,forwsub(L,x));
    Ni = norm(y,1)/norm(x,1);
    // Ni = y.infnorm()/x.infnorm();

    return Ni*Na;

} // end function

// Reference 
// Equations (4.3) and (4.4) p. 372 
/**
Cline, A. K., Moler, C. B., Stewart, G. W., & Wilkinson, J. H. (1979). 
An estimate for the condition number of a matrix. SIAM Journal on 
Numerical Analysis, 16(2), 368-375.

@article{cline1979estimate,
  title={An estimate for the condition number of a matrix},
  author={Cline, Alan K and Moler, Cleve B and Stewart, George W and Wilkinson, James H},
  journal={SIAM Journal on Numerical Analysis},
  volume={16},
  number={2},
  pages={368--375},
  year={1979},
  publisher={SIAM}
}
*/