#ifndef MASTER_HPP
#define MASTER_HPP
#include <string>
#include <sstream>

namespace Objects {
    class Master {
    public:
        void setActive(bool active);
        const bool isActive() const;
    protected:
        bool m_Active = true;
        mutable std::ostringstream oss;
        virtual const std::string toString() const;
    };
}




#endif //MASTER_HPP
