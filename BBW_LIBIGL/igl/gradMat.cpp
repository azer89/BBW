// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "gradMat.h"
#include <vector>

template <typename T, typename S>
IGL_INLINE void igl::gradMat(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &V,
  const Eigen::Matrix<S, Eigen::Dynamic, Eigen::Dynamic> &F,
  Eigen::SparseMatrix<T> &G )
{
  Eigen::PlainObjectBase<Eigen::Matrix<T,Eigen::Dynamic,3> > eperp21, eperp13;
  eperp21.resize(F.rows(),3);
  eperp13.resize(F.rows(),3);

  for (int i=0;i<F.rows();++i)
  {
    // renaming indices of vertices of triangles for convenience
    int i1 = F(i,0);
    int i2 = F(i,1);
    int i3 = F(i,2);
    
    // #F x 3 matrices of triangle edge vectors, named after opposite vertices
    Eigen::Matrix<T, 1, 3> v32 = V.row(i3) - V.row(i2);
    Eigen::Matrix<T, 1, 3> v13 = V.row(i1) - V.row(i3);
    Eigen::Matrix<T, 1, 3> v21 = V.row(i2) - V.row(i1);
    
    // area of parallelogram is twice area of triangle
    // area of parallelogram is || v1 x v2 || 
    Eigen::Matrix<T, 1, 3> n  = v32.cross(v13); 
    
    // This does correct l2 norm of rows, so that it contains #F list of twice
    // triangle areas
    double dblA = std::sqrt(n.dot(n));
    
    // now normalize normals to get unit normals
    Eigen::Matrix<T, 1, 3> u = n / dblA;
    
    // rotate each vector 90 degrees around normal
    double norm21 = std::sqrt(v21.dot(v21));
    double norm13 = std::sqrt(v13.dot(v13));
    eperp21.row(i) = u.cross(v21);
    eperp21.row(i) = eperp21.row(i) / std::sqrt(eperp21.row(i).dot(eperp21.row(i)));
    eperp21.row(i) *= norm21 / dblA;
    eperp13.row(i) = u.cross(v13);
    eperp13.row(i) = eperp13.row(i) / std::sqrt(eperp13.row(i).dot(eperp13.row(i)));
    eperp13.row(i) *= norm13 / dblA;
  }

  std::vector<int> rs;
  rs.reserve(F.rows()*4*3);
  std::vector<int> cs;
  cs.reserve(F.rows()*4*3);
  std::vector<double> vs;
  vs.reserve(F.rows()*4*3);

  // row indices
  for(int r=0;r<3;r++)
  {
    for(int j=0;j<4;j++)
    {
      for(int i=r*F.rows();i<(r+1)*F.rows();i++) rs.push_back(i);
    }
  }

  // column indices
  for(int r=0;r<3;r++)
  {
    for(int i=0;i<F.rows();i++) cs.push_back(F(i,1));
    for(int i=0;i<F.rows();i++) cs.push_back(F(i,0));
    for(int i=0;i<F.rows();i++) cs.push_back(F(i,2));
    for(int i=0;i<F.rows();i++) cs.push_back(F(i,0));
  }
  
  // values
  for(int i=0;i<F.rows();i++) vs.push_back(eperp13(i,0));
  for(int i=0;i<F.rows();i++) vs.push_back(-eperp13(i,0));
  for(int i=0;i<F.rows();i++) vs.push_back(eperp21(i,0));
  for(int i=0;i<F.rows();i++) vs.push_back(-eperp21(i,0));
  for(int i=0;i<F.rows();i++) vs.push_back(eperp13(i,1));
  for(int i=0;i<F.rows();i++) vs.push_back(-eperp13(i,1));
  for(int i=0;i<F.rows();i++) vs.push_back(eperp21(i,1));
  for(int i=0;i<F.rows();i++) vs.push_back(-eperp21(i,1));
  for(int i=0;i<F.rows();i++) vs.push_back(eperp13(i,2));
  for(int i=0;i<F.rows();i++) vs.push_back(-eperp13(i,2));
  for(int i=0;i<F.rows();i++) vs.push_back(eperp21(i,2));
  for(int i=0;i<F.rows();i++) vs.push_back(-eperp21(i,2));

  // create sparse gradient operator matrix
  G.resize(3*F.rows(),V.rows()); 
  std::vector<Eigen::Triplet<T> > triplets;
  for (int i=0;i<vs.size();++i)
  {
    triplets.push_back(Eigen::Triplet<T>(rs[i],cs[i],vs[i]));
  }
  G.setFromTriplets(triplets.begin(), triplets.end());
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
#endif
