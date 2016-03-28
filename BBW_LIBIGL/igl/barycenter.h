// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_BARYCENTER_H
#define IGL_BARYCENTER_H
#include "igl_inline.h"
#include <Eigen/Dense>
namespace igl
{
  // BARYCENTER
  //
  // B = barycenter(V,F)
  //
  // Compute the barycenter of every triangle
  //
  // Inputs:
  //   V #V x dim matrix of vertex coordinates
  //   F #F x simplex_size  matrix of indices of triangle corners
  // Output:
  //   BC a #F x dim matrix of 3d vertices
  template <
    typename DerivedV,
    typename DerivedF,
    typename DerivedBC>
  IGL_INLINE void barycenter(
      const Eigen::PlainObjectBase<DerivedV> & V,
      const Eigen::PlainObjectBase<DerivedF> & F,
      Eigen::PlainObjectBase<DerivedBC> & BC);
}

#ifdef IGL_HEADER_ONLY
#  include "barycenter.cpp"
#endif

#endif
