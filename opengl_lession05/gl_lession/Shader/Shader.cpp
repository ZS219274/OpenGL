
#include "Shader.h"

void Shader::initShader(const char *_vertexPath, const char *_fragPath)
{
  std::string _vertexCode("");
  std::string _fragCode("");

  std::ifstream _vShaderFile;
  std::ifstream _fShaderFile;

  _vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try
  {
    _vShaderFile.open(_vertexPath);
    _fShaderFile.open(_fragPath);

    std::stringstream _vShaderStream, _fShaderStream;
    _vShaderStream << _vShaderFile.rdbuf();
    _fShaderStream << _fShaderFile.rdbuf();

    _vertexCode = _vShaderStream.str();
    _fragCode = _fShaderStream.str();
  }
  catch (std::ifstream::failure &e)
  {
    std::string errStr = e.what();
    std::cout << errStr << std::endl;
  }

  const char *_vShaderStr = _vertexCode.c_str();
  const char *_fShaderStr = _fragCode.c_str();

  // shader的编译链接
  unsigned int _vertexID = 0, _fragID = 0;
  char _infolog[512]; // 记录错误信息
  int _successFlag = 0;

  // 编译
  _vertexID = glCreateShader(GL_VERTEX_SHADER); // 创建一个shader
  glShaderSource(_vertexID, 1, &_vShaderStr, NULL);
  glCompileShader(_vertexID); // 编译shader

  glGetShaderiv(_vertexID, GL_COMPILE_STATUS, &_successFlag); // 检查是否编译成功
  if (!_successFlag)
  {
    glGetShaderInfoLog(_vertexID, 512, NULL, _infolog);
    std::string errStr(_infolog);
    std::cout << errStr << _infolog << std::endl;
  }

  _fragID = glCreateShader(GL_FRAGMENT_SHADER); // 创建一个shader
  glShaderSource(_fragID, 1, &_fShaderStr, NULL);
  glCompileShader(_fragID); // 编译shader

  glGetShaderiv(_fragID, GL_COMPILE_STATUS, &_successFlag); // 检查是否编译成功
  if (!_successFlag)
  {
    glGetShaderInfoLog(_fragID, 512, NULL, _infolog);
    std::string errStr(_infolog);
    std::cout << errStr << _infolog << std::endl;
  }

  // 链接

  // 创建程序
  m_shaderProgram = glCreateProgram();
  // 附加shader
  glAttachShader(m_shaderProgram, _vertexID);
  glAttachShader(m_shaderProgram, _fragID);

  // 链接程序
  glLinkProgram(m_shaderProgram);

  // 判断是否成功
  glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &_successFlag);
  if (!_successFlag)
  {
    glGetProgramInfoLog(m_shaderProgram, 512, NULL, _infolog);
    std::string errStr(_infolog);
    std::cout << errStr << _infolog << std::endl;
  }

  // 删除shader
  glDeleteShader(_vertexID);
  glDeleteShader(_fragID);
}

void Shader::setMatrix(const std::string &_name, const glm::mat4 &_matrix) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, _name.c_str()), 
    1, GL_FALSE, glm::value_ptr(_matrix));
}
