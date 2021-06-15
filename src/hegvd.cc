// Copyright (c) 2017-2020, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"
#include "NoConstructAllocator.hh"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t hegvd(
    int64_t itype, lapack::Job jobz, lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* B, int64_t ldb,
    float* W )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(itype) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int itype_ = (lapack_int) itype;
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    LAPACK_chegvd(
        &itype_, &jobz_, &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        W,
        (lapack_complex_float*) qry_work, &ineg_one,
        qry_rwork, &ineg_one,
        qry_iwork, &ineg_one, &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);
    lapack_int lrwork_ = real(qry_rwork[0]);
    lapack_int liwork_ = real(qry_iwork[0]);

    // allocate workspace
    lapack::vector< std::complex<float> > work( lwork_ );
    lapack::vector< float > rwork( lrwork_ );
    lapack::vector< lapack_int > iwork( liwork_ );

    LAPACK_chegvd(
        &itype_, &jobz_, &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        W,
        (lapack_complex_float*) &work[0], &lwork_,
        &rwork[0], &lrwork_,
        &iwork[0], &liwork_, &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t hegvd(
    int64_t itype, lapack::Job jobz, lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* B, int64_t ldb,
    double* W )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(itype) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int itype_ = (lapack_int) itype;
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    LAPACK_zhegvd(
        &itype_, &jobz_, &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        W,
        (lapack_complex_double*) qry_work, &ineg_one,
        qry_rwork, &ineg_one,
        qry_iwork, &ineg_one, &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);
    lapack_int lrwork_ = real(qry_rwork[0]);
    lapack_int liwork_ = real(qry_iwork[0]);

    // allocate workspace
    lapack::vector< std::complex<double> > work( lwork_ );
    lapack::vector< double > rwork( lrwork_ );
    lapack::vector< lapack_int > iwork( liwork_ );

    LAPACK_zhegvd(
        &itype_, &jobz_, &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        W,
        (lapack_complex_double*) &work[0], &lwork_,
        &rwork[0], &lrwork_,
        &iwork[0], &liwork_, &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
