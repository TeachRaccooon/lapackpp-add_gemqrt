// Copyright (c) 2017-2020, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack/defines.h"

#if ! (defined(LAPACK_HAVE_ROCBLAS) || defined(LAPACK_HAVE_CUBLAS) || defined(LAPACK_HAVE_ONEMKL))

#include "lapack/device.hh"

//==============================================================================
namespace lapack {

//------------------------------------------------------------------------------
// Wrapper around workspace query.
// dA is only for templating scalar_t; it isn't referenced.
template <typename scalar_t>
void getrf_work_size_bytes(
    int64_t m, int64_t n,
    scalar_t* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue )
{
    *dev_work_size  = 0;
    *host_work_size = 0;
}

//------------------------------------------------------------------------------
// Wrapper stub.
// This is async. Once finished, the return info is in dev_info on the device.
template <typename scalar_t>
void getrf(
    int64_t m, int64_t n,
    scalar_t* dA, int64_t ldda, device_pivot_int* dipiv,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue )
{
    throw lapack::Error( "device LAPACK not available", __func__ );
}

//------------------------------------------------------------------------------
// Explicit instantiations.
template
void getrf_work_size_bytes(
    int64_t m, int64_t n,
    float* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue );

template
void getrf_work_size_bytes(
    int64_t m, int64_t n,
    double* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue );

template
void getrf_work_size_bytes(
    int64_t m, int64_t n,
    std::complex<float>* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue );

template
void getrf_work_size_bytes(
    int64_t m, int64_t n,
    std::complex<double>* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue );

//--------------------
template
void getrf(
    int64_t m, int64_t n,
    float* dA, int64_t ldda, device_pivot_int* dipiv,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue );

template
void getrf(
    int64_t m, int64_t n,
    double* dA, int64_t ldda, device_pivot_int* dipiv,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue );

template
void getrf(
    int64_t m, int64_t n,
    std::complex<float>* dA, int64_t ldda, device_pivot_int* dipiv,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue );

template
void getrf(
    int64_t m, int64_t n,
    std::complex<double>* dA, int64_t ldda, device_pivot_int* dipiv,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue );

} // namespace lapack

#endif // ! (LAPACK_HAVE_ROCBLAS || LAPACK_HAVE_CUBLAS || LAPACK_HAVE_ONEMKL)
