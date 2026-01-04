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

void Camera::pitch(float yOffset) 
{
  m_pitch += yOffset * m_sensitivity;
  if (m_pitch > 89.0f)
  {
    m_pitch = 89.0f;
  }
  if (m_pitch < -89.0f)
  {
    m_pitch = -89.0f;
  } 
  m_cameraFront.y = sin(glm::radians(m_pitch));
  m_cameraFront.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
  m_cameraFront.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));

  m_cameraFront = glm::normalize(m_cameraFront);
  update();
}

void Camera::yaw(float xOffset) 
{
  m_yaw += xOffset * m_sensitivity;

  m_cameraFront.y = sin(glm::radians(m_pitch));
  m_cameraFront.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
  m_cameraFront.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));

  m_cameraFront = glm::normalize(m_cameraFront);
  update();
}

void Camera::sensitivity(float sensitivity) 
{
  m_sensitivity = sensitivity;
}

void Camera::OnMouseMove(float xpos, float ypos) 
{
  if (m_firstMove)
  {
    m_xpos = xpos;
    m_ypos = ypos;
    m_firstMove = false;
    return;
  }
  float xOffset = xpos - m_xpos;
  float yOffset = m_ypos - ypos;

  m_xpos = xpos;
  m_ypos = ypos;

  pitch(yOffset);
  yaw(xOffset);
}
