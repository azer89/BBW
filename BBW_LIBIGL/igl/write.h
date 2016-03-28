// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_WRITE_H
#define IGL_WRITE_H
#include "igl_inline.h"

#include <Eigen/Core>
#include <string>

namespace igl 
{
  // write mesh to an ascii file with automatic detection of file format. supported: obj, off)
  // Known Bugs:
  //  Does not correctly find file extensions: myfile.foo.off 
  template <typename DerivedV, typename DerivedF>
  IGL_INLINE bool write(
                        const std::string str,
                        const Eigen::PlainObjectBase<DerivedV>& V,
                        const Eigen::PlainObjectBase<DerivedF>& F);
}

#ifdef IGL_HEADER_ONLY
#  include "write.cpp"
#endif

#endif
