// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_MOSEK_GUARDED_H
#define IGL_MOSEK_GUARDED_H
#include "../igl_inline.h"

#include "mosek.h"
namespace igl
{
  // Little function to wrap around mosek call to handle errors
  // 
  // Inputs:
  //   r  mosek error code returned from mosek call
  // Returns r untouched
  IGL_INLINE MSKrescodee mosek_guarded(const MSKrescodee r);
}

#ifdef IGL_HEADER_ONLY
#  include "mosek_guarded.cpp"
#endif

#endif

