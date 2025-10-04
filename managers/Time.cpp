#include "Time.hpp"

#include <GLFW/glfw3.h>

namespace Managers {
    float Time::m_DELTA = 0.0f;
    float Time::m_LAST = 0.0f;
    float Time::m_CURR = 0.0f;

    float Time::DELTATIME() {
        m_CURR = glfwGetTime();
        m_DELTA = m_CURR - m_LAST;
        m_LAST = m_CURR;
        return m_DELTA;
    }
}

