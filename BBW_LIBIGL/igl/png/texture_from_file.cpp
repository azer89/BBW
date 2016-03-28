#include "texture_from_file.h"
#ifndef IGL_NO_OPENGL

#include "texture_from_png.h"
#include <igl/report_gl_error.h>
#include <igl/STR.h>
#include <igl/pathinfo.h>
#include <igl/texture_from_tga.h>
#include <YImage.hpp>
#include <string>
#include <algorithm>
#include <iostream>

IGL_INLINE bool igl::texture_from_file(const std::string filename, GLuint & id)
{
  using namespace igl;
  using namespace std;
  // dirname, basename, extension and filename
  string d,b,ext,f;
  pathinfo(filename,d,b,ext,f);
  // Convert extension to lower case
  transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
  if(ext == "tga")
  {
    return texture_from_tga(filename,id);
  }else if(ext == "png")
  {
    return texture_from_png(filename,id);
  }else
  {
#ifdef __APPLE__
    // Convert to a temporary png file
    string tmp = "/var/tmp/.texture_from_file.png";
#define PATH_TO_CONVERT "/opt/local/bin/convert"
    string command = STR(PATH_TO_CONVERT<<" \""<<filename<<"\" \""<<tmp<<"\"");
    try
    {
      if(system(command.c_str())==0)
      {
        return texture_from_file(tmp.c_str(),id);
      }else
      {
        cerr<<"texture_from_file: calling to convert ('"<<command<<"') failed..."<<endl;
        return false;
      }
    }catch(int e)
    {
      cerr<<"^"<<__FUNCTION__<<": Calling to convert crashed..."<<endl;
      return false;
    }
#else
    return false;
#endif
  }
}
#endif


