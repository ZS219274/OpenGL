#include "camera.h"

void Camera::lookAt(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
{
  m_cameraPos = pos;
  m_cameraFront = glm::normalize(front);
  m_cameraUp = up;

  v_mMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void Camera::update()
{
  v_mMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void Camera::move(CameraMove move)
{
  switch (move)
  {
  case CameraMove::FORWARD:
    m_cameraPos += m_cameraFront * m_speed;
    break;
  case CameraMove::BACKWARD:
    m_cameraPos -= m_cameraFront * m_speed;
    break;
  case CameraMove::LEFT:
    m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
    break;
  case CameraMove::RIGHT:
    m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
  }
}
