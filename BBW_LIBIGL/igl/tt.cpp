// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "tt.h"

#include "is_manifold.h"
#include <algorithm>

template <typename Scalar, typename Index>
IGL_INLINE void igl::tt_preprocess(const Eigen::PlainObjectBase<Scalar>& /*V*/,
                                   const Eigen::PlainObjectBase<Index>& F,
                                   std::vector<std::vector<int> >& TTT)
{
  for(int f=0;f<F.rows();++f)
    for (int i=0;i<F.cols();++i)
    {
      // v1 v2 f ei 
      int v1 = F(f,i);
      int v2 = F(f,(i+1)%F.cols());
      if (v1 > v2) std::swap(v1,v2);
      std::vector<int> r(4);
      r[0] = v1; r[1] = v2;
      r[2] = f;  r[3] = i;
      TTT.push_back(r);
    }
  std::sort(TTT.begin(),TTT.end());
}

// Extract the face adjacencies
template <typename Index>
IGL_INLINE void igl::tt_extractTT(const Eigen::PlainObjectBase<Index>& F,
                                  std::vector<std::vector<int> >& TTT,
                                  Eigen::PlainObjectBase<Index>& TT)
{
  TT = Eigen::PlainObjectBase<Index>::Constant((int)(F.rows()),F.cols(),-1);
  
  for(int i=1;i<(int)TTT.size();++i)
  {
    std::vector<int>& r1 = TTT[i-1];
    std::vector<int>& r2 = TTT[i];
    if ((r1[0] == r2[0]) && (r1[1] == r2[1]))
    {
      TT(r1[2],r1[3]) = r2[2];
      TT(r2[2],r2[3]) = r1[2];
    }
  }
}

// Extract the face adjacencies indices (needed for fast traversal)
template <typename Index>
IGL_INLINE void igl::tt_extractTTi(const Eigen::PlainObjectBase<Index>& F,
                                   std::vector<std::vector<int> >& TTT,
                                   Eigen::PlainObjectBase<Index>& TTi)
{
  TTi = Eigen::PlainObjectBase<Index>::Constant((int)(F.rows()),F.cols(),-1);
  
  for(int i=1;i<(int)TTT.size();++i)
  {
    std::vector<int>& r1 = TTT[i-1];
    std::vector<int>& r2 = TTT[i];
    if ((r1[0] == r2[0]) && (r1[1] == r2[1]))
    {
      TTi(r1[2],r1[3]) = r2[3];
      TTi(r2[2],r2[3]) = r1[3];
    }
  }
}

// Compute triangle-triangle adjacency
template <typename Scalar, typename Index>
IGL_INLINE void igl::tt(const Eigen::PlainObjectBase<Scalar>& V,
                        const Eigen::PlainObjectBase<Index>& F,
                        Eigen::PlainObjectBase<Index>& TT)
{
  //assert(igl::is_manifold(V,F));
  std::vector<std::vector<int> > TTT;
  
  tt_preprocess(V,F,TTT);
  tt_extractTT(F,TTT,TT);
}

// Compute triangle-triangle adjacency with indices
template <typename Scalar, typename Index>
IGL_INLINE void igl::tt(const Eigen::PlainObjectBase<Scalar>& V,
                        const Eigen::PlainObjectBase<Index>& F,
                        Eigen::PlainObjectBase<Index>& TT,
                        Eigen::PlainObjectBase<Index>& TTi)
{
  //assert(igl::is_manifold(V,F));
  std::vector<std::vector<int> > TTT;
  
  tt_preprocess(V,F,TTT);
  tt_extractTT(F,TTT,TT);
  tt_extractTTi(F,TTT,TTi);
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
template void igl::tt<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&);
// generated by autoexplicit.sh
template void igl::tt<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 3, 0, -1, 3> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> >&);
#endif
