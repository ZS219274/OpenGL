#ifndef SHADER_H
#define SHADER_H

#include "../Base/Base.h"


class Shader
{
public:
	Shader()
  {
     m_shaderProgram = 0;
  }
	~Shader(){}

  void initShader(const char* _vertexPath, const char* _fragmentPath);
  void start()
  {
    glUseProgram(m_shaderProgram);
  }
  void end()
  {
    glUseProgram(0);
  }
  
  unsigned int getShaderProgram() const
  {
      return m_shaderProgram;
  }
private:
  unsigned int m_shaderProgram;
};
#endif