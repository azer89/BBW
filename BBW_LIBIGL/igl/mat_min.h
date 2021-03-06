// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_MAT_MIN_H
#define IGL_MAT_MIN_H
#include "igl_inline.h"
#include <Eigen/Dense>

namespace igl
{
  // Ideally this becomes a super overloaded function supporting everything
  // that matlab's min supports

  // Min function for matrices to act like matlab's min function. Specifically
  // like [Y,I] = min(X,[],dim);
  //
  // Templates:
  //   T  should be a eigen matrix primitive type like int or double
  // Inputs:
  //   X  m by n matrix
  //   dim  dimension along which to take min 
  // Outputs:
  //   Y  n-long sparse vector (if dim == 1) 
  //   or
  //   Y  m-long sparse vector (if dim == 2)
  //   I  vector the same size as Y containing the indices along dim of minimum
  //     entries
  //
  // See also: mat_max
  template <typename T>
  IGL_INLINE void mat_min(
    const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> & X,
    const int dim,
    Eigen::Matrix<T,Eigen::Dynamic,1> & Y,
    Eigen::Matrix<int,Eigen::Dynamic,1> & I);
  // Use Y = X.colwise().minCoeff() instead
  //// In-line wrapper
  //template <typename T>
  //IGL_INLINE Eigen::Matrix<T,Eigen::Dynamic,1> mat_min(
  //  const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> & X,
  //  const int dim);
}

#ifdef IGL_HEADER_ONLY
#  include "mat_min.cpp"
#endif

#endif
