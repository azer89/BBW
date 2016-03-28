// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "moveFV.h"

template <typename T, typename I>
IGL_INLINE void igl::moveFV(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &V,
            const Eigen::Matrix<I, Eigen::Dynamic, Eigen::Dynamic> &F,
            const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &S,
            Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &SV)
{
  
  SV = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Zero(V.rows(),S.cols());
  Eigen::Matrix<T, Eigen::Dynamic, 1> COUNT = Eigen::Matrix<T, Eigen::Dynamic, 1>::Zero(V.rows());
  for (int i = 0; i <F.rows(); ++i)
  {
    for (int j = 0; j<F.cols(); ++j)
    {
      SV.row(F(i,j)) += S.row(i);
      COUNT[F(i,j)] ++;
    }
  }
  for (int i = 0; i <V.rows(); ++i)
    SV.row(i) /= COUNT[i];
  
};

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
#endif
