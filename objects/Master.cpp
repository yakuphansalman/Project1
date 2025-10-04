#include "Master.hpp"

namespace Objects {
    void Master::setActive(bool active) {
        m_Active = active;
    }

    const bool Master::isActive() const {
        return m_Active;
    }

    const std::string Master::toString() const {
        return "Master";
    }
}

