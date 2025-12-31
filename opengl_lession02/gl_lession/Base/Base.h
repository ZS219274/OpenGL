#ifndef BASE_H
#define BASE_H 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstring>  // 添加cstring头文件以使用memcpy

typedef unsigned int uint;
typedef unsigned char byte;

struct ffRGBA //描述一个点（像素）颜色的结构体
{
	byte m_b;
	byte m_g;
  byte m_r;
  byte m_a;

  ffRGBA(byte _r = 255, byte _g = 255, byte _b = 255, byte _a = 255)
  {
    m_r = _r;
    m_g = _g;
    m_b = _b;
    m_a = _a;
  }
};

template <typename T>
struct tVec3
{
  T m_x;
  T m_y;
  T m_z;
  
  tVec3(T _x = 0, T _y = 0, T _z = 0)
  {
    m_x = _x;
    m_y = _y;
    m_z = _z;
  }
  
  // 添加向量运算操作
  tVec3 operator+(const tVec3& other) const {
      return tVec3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
  }
  
  tVec3 operator-(const tVec3& other) const {
      return tVec3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
  }
  
  tVec3& operator+=(const tVec3& other) {
      m_x += other.m_x;
      m_y += other.m_y;
      m_z += other.m_z;
      return *this;
  }
  
  T length() const {
      return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
  }
};

template <typename T>
struct tVec2
{
  T m_x;
  T m_y;

  tVec2(T _x = 0, T _y = 0)
  {
    m_x = _x;
    m_y = _y;
  }
  
  // 添加向量运算操作
  tVec2 operator+(const tVec2& other) const {
      return tVec2(m_x + other.m_x, m_y + other.m_y);
  }
  
  tVec2 operator-(const tVec2& other) const {
      return tVec2(m_x - other.m_x, m_y - other.m_y);
  }
  
  tVec2& operator+=(const tVec2& other) {
      m_x += other.m_x;
      m_y += other.m_y;
      return *this;
  }
  
  T length() const {
      return sqrt(m_x * m_x + m_y * m_y);
  }
};

// 添加数学常量
const float PI = 3.14159265359f;

#endif