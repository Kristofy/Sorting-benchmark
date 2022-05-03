#include <chrono>
#include <string>
#include <iostream>


#define Cat2(a, b) a##b
#define Cat(a, b) Cat2(a, b)
#define TimeFuncion() AutoTimer Cat(_timer_name, __COUNTER__) (__func__)
#define TimeScope(name) AutoTimer t(name)
class AutoTimer{
    public:
        AutoTimer(const std::string& name) :start(std::chrono::steady_clock::now()), name(name){}
        ~AutoTimer(){
            if(!ended){
                auto end = std::chrono::steady_clock::now();
                auto dur = end.time_since_epoch() - start.time_since_epoch();
                std::cout << name << ": " << dur.count()/1e6 << "ms" << std::endl;
            }
        }

        void restart() {
            start = std::chrono::steady_clock::now();
            ended = false;
        }

        double end(){
            auto end = std::chrono::steady_clock::now();
            auto dur = end.time_since_epoch() - start.time_since_epoch();
            ended = true;
            return dur.count()/1e6;
        }
    private:
        // std::chrono::milliseconds static_assert
        std::chrono::time_point<std::chrono::steady_clock> start;
        std::string name;
        bool ended = false;
};