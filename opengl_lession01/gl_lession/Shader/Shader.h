#pragma once
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

private:
  unsigned int m_shaderProgram;
};