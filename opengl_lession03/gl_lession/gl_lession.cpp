#include "Base/Base.h"      // 包含基础工具头文件
#include "Shader/Shader.h"  // 包含着色器管理类头文件
#include "ffImage/ffImage.h" // 包含图像处理类头文件

/*
 *三角形绘制
 */
unsigned int VBO = 0;       // 顶点缓冲对象ID
unsigned int VAO = 0;       // 顶点数组对象ID
unsigned int _texture = 0;  // texture句柄
Shader _shader;             // 着色器程序对象

ffImage* _pImage = NULL; // 图像对象指针

void rend()                 // 渲染函数
{
  glBindTexture(GL_TEXTURE_2D, _texture);
  _shader.start();          // 开始使用着色器程序
    glBindVertexArray(VAO);   // 绑定顶点数组对象
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 使用索引绘制三角形，共绘制6个顶点
  _shader.end();            // 结束使用着色器程序
}

void initModel()            // 初始化模型数据函数
{
  // 定义三角形顶点数据，每行包含位置坐标(x,y,z)和颜色(r,g,b)
  float vertices[] = {
      0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
      -0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  
  };

  unsigned int indices[] = {
      0, 1, 3,
      1, 2, 3
  };

  glGenVertexArrays(1, &VAO);                    // 生成一个顶点数组对象
  glBindVertexArray(VAO);                        // 绑定顶点数组对象

  unsigned int EBO = 0;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glGenBuffers(1, &VBO);                         // 生成一个缓冲区对象
  glBindBuffer(GL_ARRAY_BUFFER, VBO);            // 绑定缓冲区为顶点缓冲
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将顶点数据传入缓冲区

  // 设置顶点属性指针，指定如何解析顶点数据
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);        // 位置属性(前3个float)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3)); // 颜色属性(后3个float)
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));

  glEnableVertexAttribArray(0);                  // 启用顶点属性0(位置)
  glEnableVertexAttribArray(1);                  // 启用顶点属性1(颜色)
  glEnableVertexAttribArray(2);                  // 启用顶点属性1(纹理)

  glBindBuffer(GL_ARRAY_BUFFER, 0);              // 解绑顶点缓冲
  glBindVertexArray(0);                          // 解绑顶点数组
}

void initTexture()
{
  _pImage = ffImage::readFromfile("resource/kroha.png");
  
  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //采样方式(最近)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pImage->getWidth(), 
    _pImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _pImage->getData());
}


// 窗口大小改变时的回调函数
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);              // 设置视口大小
}

// 处理输入事件
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // 检测是否按下ESC键
  {
    glfwSetWindowShouldClose(window, true);       // 设置窗口关闭标志
  }
}

int main()  // 主函数
{
  glfwInit();                                     // 初始化GLFW库
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // 设置OpenGL主版本号
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 设置OpenGL次版本号
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置使用核心(profile)模式

  // 创建GLFW窗口
  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Core", NULL, NULL);
  if (window == NULL)                             // 检查窗口是否创建成功
  {
    std::cout << "Failed to create GLFW window" << std::endl;  // 输出错误信息
    glfwTerminate();                              // 终止GLFW
    return -1;                                    // 返回错误码
  }
  glfwMakeContextCurrent(window);                 // 设置当前OpenGL上下文

  // 初始化GLAD，用于加载OpenGL函数指针
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;  // 输出错误信息
    return -1;                                    // 返回错误码
  }

  glViewport(0, 0, 800, 600);                     // 设置视口尺寸
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 设置窗口大小变化回调函数

  initModel();                                    // 初始化模型数据
  initTexture();
  _shader.initShader("vertexShader.glsl", "fragmentShader.glsl"); // 初始化着色器程序

  // 渲染循环
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);                         // 处理用户输入

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);        // 设置清屏颜色
    glClear(GL_COLOR_BUFFER_BIT);                 // 清除颜色缓冲

    rend();                                       // 执行渲染

    glfwSwapBuffers(window);                      // 交换前后缓冲区
    glfwPollEvents();                             // 处理事件队列
  }
  glfwTerminate();                                // 终止GLFW
  return 0;                                       // 程序正常退出
}