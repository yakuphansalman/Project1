#ifndef MASTER_HPP
#define MASTER_HPP
#define PROPERTY(...)
#define REFLECTABLE_CLASS(ClassName) \
    friend class ClassName;

#include <string>
#include <sstream>

class Master {
public:
protected:
    mutable std::ostringstream oss;
    virtual const std::string toString() const;
};




#endif //MASTER_HPP
