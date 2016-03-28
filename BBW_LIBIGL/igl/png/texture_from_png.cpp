#include "texture_from_png.h"
#ifndef IGL_NO_OPENGL

#include <YImage.hpp>
#include <igl/report_gl_error.h>

IGL_INLINE bool igl::texture_from_png(const std::string png_file, GLuint & id)
{
  YImage yimg;
  if(!yimg.load(png_file.c_str()))
  {
    return false;
  }
  // Why do I need to flip?
  //yimg.flip();
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGB, 
    yimg.width(), yimg.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, yimg.data());
  glBindTexture(GL_TEXTURE_2D, 0);
  return true;
}

#endif

