#include "Base/Base.h"       // 包含基础工具头文件
#include "Shader/Shader.h"   // 包含着色器管理类头文件
#include "ffImage/ffImage.h" // 包含图像处理类头文件
#include "camera/camera.h"
/*
 * 创建一个小太阳，并对方块进行简单着色
 */

// OpenGL对象ID
uint _VAO_cube = 0;      // 顶点数组对象ID
uint _VAO_sun = 0;

unsigned int _texture = 0; // 纹理句柄

// 窗口尺寸
int _width = 800;
int _height = 600;

// 全局对象
Shader _shader_cube;          // 着色器程序对象
Shader _shader_sun;

ffImage *_pImage = NULL; // 图像对象指针
Camera _camera;
glm::mat4 _projMatrix(1.0f); // 投影矩阵

/**
 * 渲染函数
 * 清除屏幕，启用深度测试，更新相机，
 * 设置变换矩阵，并绘制立方体
 */
void rend()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);               // 设置清屏颜色
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色和深度缓冲
  glEnable(GL_DEPTH_TEST);                            // 开启深度测试

  _camera.update();
  _projMatrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);
  glm::mat4 _modelMatrix(1.0f);
  _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
  glBindTexture(GL_TEXTURE_2D, _texture);

  _shader_cube.start(); // 开始使用着色器程序
    _shader_cube.setMatrix("_modelMatrix", _modelMatrix);
    _shader_cube.setMatrix("_viewMatrix", _camera.getMatrix());
    _shader_cube.setMatrix("_projMatrix", _projMatrix);
    glBindVertexArray(_VAO_cube); // 绑定顶点数组对象
    glDrawArrays(GL_TRIANGLES, 0, 36);
  _shader_cube.end(); // 结束使用着色器程序


  _shader_sun.start(); // 开始使用着色器程序
    _shader_sun.setMatrix("_modelMatrix", _modelMatrix);
    _shader_sun.setMatrix("_viewMatrix", _camera.getMatrix());
    _shader_sun.setMatrix("_projMatrix", _projMatrix);

    _modelMatrix  = glm::translate(_modelMatrix, glm::vec3(3.0f, 0.0f, -3.0f));
    _shader_sun.setMatrix("_modelMatrix", _modelMatrix);
    glBindVertexArray (_VAO_sun);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  _shader_sun.end(); // 结束使用着色器程序
}

/**
 * 初始化模型数据
 * 设置立方体的顶点数据（包含位置和纹理坐标），
 * 创建VAO和VBO，并配置顶点属性
 */
uint CreateModel()
{
  uint _VAO = 0;
  uint _VBO = 0;
  // 定义顶点数据：位置(x,y,z)和纹理坐标(u,v)
  float vertices[] = {
      // 前面 (z = -0.5)
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      // 后面 (z = 0.5)
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

      // 左面 (x = -0.5)
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      // 右面 (x = 0.5)
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      // 底面 (y = -0.5)
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      // 顶面 (y = 0.5)
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

  glGenVertexArrays(1, &_VAO); // 生成顶点数组对象
  glBindVertexArray(_VAO);     // 绑定顶点数组对象

  glGenBuffers(1, &_VBO);                                                     // 生成顶点缓冲对象
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);                                        // 绑定缓冲区为顶点缓冲
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将顶点数据传入缓冲区

  // 设置顶点属性指针，指定如何解析顶点数据
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0); // 位置属性(前3个float)
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(sizeof(float) * 3)); // 纹理坐标属性

  glEnableVertexAttribArray(0); // 启用顶点属性0(位置)
  glEnableVertexAttribArray(1); // 启用顶点属性1(纹理坐标)

  glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑顶点缓冲
  glBindVertexArray(0);             // 解绑顶点数组

   return _VAO;
}

/**
 * 初始化纹理
 * 从文件加载图像，生成OpenGL纹理，设置纹理参数，
 * 并上传图像数据到GPU
 */
void initTexture()
{
  _pImage = ffImage::readFromfile("resource/pic.png");

  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // 采样方式(最近)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pImage->getWidth(),
               _pImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _pImage->getData());
}

void initShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
  _shader_cube.initShader(vertexShaderPath, fragmentShaderPath); 
  _shader_sun.initShader("vsunShader.glsl", "fsunShader.glsl");
}


// 窗口大小改变时的回调函数
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  _width = width;
  _height = height;
  glViewport(0, 0, width, height); // 设置视口大小
}

// 处理输入事件
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // 检测是否按下ESC键
  {
    glfwSetWindowShouldClose(window, true); // 设置窗口关闭标志
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // 检测是否按下W键
  {
    _camera.move(CameraMove::FORWARD);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // 检测是否按下S键
  {
    _camera.move(CameraMove::BACKWARD);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // 检测是否按下A键
  {
    _camera.move(CameraMove::LEFT);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // 检测是否按下D键
  {
    _camera.move(CameraMove::RIGHT);
  }
}

/**
 * 鼠标移动回调函数
 * 根据鼠标移动更新相机方向
 */
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
  _camera.OnMouseMove(xpos, ypos);
}

/**
 * 主函数
 * 初始化GLFW，创建窗口，设置OpenGL上下文，
 * 配置回调函数，初始化数据，并运行渲染循环
 */
int main()
{
  glfwInit();                                                    // 初始化GLFW库
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // 设置OpenGL主版本号
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // 设置OpenGL次版本号
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置使用核心(profile)模式

  // 创建GLFW窗口
  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Core", NULL, NULL);
  if (window == NULL) // 检查窗口是否创建成功
  {
    std::cout << "Failed to create GLFW window" << std::endl; // 输出错误信息
    glfwTerminate();                                          // 终止GLFW
    return -1;                                                // 返回错误码
  }
  glfwMakeContextCurrent(window); // 设置当前OpenGL上下文

  // 初始化GLAD，用于加载OpenGL函数指针
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl; // 输出错误信息
    return -1;                                             // 返回错误码
  }

  glViewport(0, 0, _width, _height);                                 // 设置视口尺寸
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 设置窗口大小变化回调函数

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);

  _camera.lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  _camera.setSpeed(0.01f);

  _VAO_cube = CreateModel(); // 初始化模型数据
  _VAO_sun = CreateModel();
  initTexture();
  initShader("vertexShader.glsl", "fragmentShader.glsl");
  // 渲染循环
  while (!glfwWindowShouldClose(window))
  {
    processInput(window); // 处理用户输入
    rend();               // 执行渲染

    glfwSwapBuffers(window); // 交换前后缓冲区
    glfwPollEvents();        // 处理事件队列
  }
  glfwTerminate(); // 终止GLFW
  return 0;        // 程序正常退出
}