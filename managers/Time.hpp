#ifndef TIME_HPP
#define TIME_HPP


namespace Managers {
    class Time {
    private:
        static float m_DELTA,m_LAST,m_CURR;
    public:
        static float DELTATIME();
    };
}




#endif //TIME_HPP
