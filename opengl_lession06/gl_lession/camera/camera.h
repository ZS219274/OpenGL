#ifndef CAMERA_H
#define CAMERA_H

#include "Base/Base.h"

enum class CameraMove
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class Camera
{
public:
  Camera()
  {
    m_cameraPos = glm::vec3(1.0f);
    m_cameraFront = glm::vec3(1.0f);
    m_cameraUp = glm::vec3(1.0f);
    m_speed = 0.01f;
    v_mMatrix = glm::mat4(1.0f);
  }
  ~Camera() {}

  void lookAt(glm::vec3 pos, glm::vec3 front, glm::vec3 up);

  void update();
  glm::mat4 getMatrix()
  {
    return v_mMatrix;
  }

  void move(CameraMove move);
  void setSpeed(float speed)
  {
    m_speed = speed;
  }

private:
  glm::vec3 m_cameraPos;
  glm::vec3 m_cameraFront;
  glm::vec3 m_cameraUp;

  float m_speed;
  glm::mat4 v_mMatrix;
};

#endif