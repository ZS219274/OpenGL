#ifndef FFIMAGE_H
#define FFIMAGE_H
#include "Base/Base.h"  // 使用相对项目根目录的路径

#include <vector>

class ffImage
{
private:
  int m_width;
  int m_height;
  int m_picType;
  ffRGBA *m_data;

public:
  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }
  int getPrivate() const { return m_picType; }
  ffRGBA *getData() const { return m_data; }

  ffRGBA getColor(int x, int y) const
  {
    // 修复条件判断中的逻辑运算符使用错误
    if (x < 0 || x > m_width - 1 || y < 0 || y > m_height - 1)
    {
      return ffRGBA(0, 0, 0, 0);
    }
    return m_data[y * m_width + x];
  }

  ffImage(int _width = 0, int _height = 0, int _picType = 0, ffRGBA *_data = nullptr)
  {
    m_width = _width;
    m_height = _height;
    m_picType = _picType;

    int _sumSize = m_width * m_height;
    if (_data && _sumSize)
    {
      m_data = new ffRGBA[_sumSize];
      memcpy(m_data, _data, _sumSize * sizeof(ffRGBA));  // 需要#include <cstring>
    }
    else
    {
      m_data = nullptr;
    }
  }

  // 遵循C++三法则，添加拷贝构造函数和赋值操作符
  ffImage(const ffImage& other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_picType = other.m_picType;
    
    int _sumSize = m_width * m_height;
    if (other.m_data && _sumSize) {
      m_data = new ffRGBA[_sumSize];
      memcpy(m_data, other.m_data, _sumSize * sizeof(ffRGBA));
    } else {
      m_data = nullptr;
    }
  }
  
  ffImage& operator=(const ffImage& other) {
    if (this != &other) {
      // 释放原内存
      if (m_data) {
        delete[] m_data;
      }
      
      m_width = other.m_width;
      m_height = other.m_height;
      m_picType = other.m_picType;
      
      int _sumSize = m_width * m_height;
      if (other.m_data && _sumSize) {
        m_data = new ffRGBA[_sumSize];
        memcpy(m_data, other.m_data, _sumSize * sizeof(ffRGBA));
      } else {
        m_data = nullptr;
      }
    }
    return *this;
  }

  ~ffImage()
  {
    if (m_data)
    {
      delete[] m_data;
      m_data = nullptr;  // 避免悬空指针
    }
  }

public:
  static ffImage *readFromfile(const char *fileName);
};
#endif