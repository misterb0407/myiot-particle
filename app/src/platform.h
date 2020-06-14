#include <functional>
#include "Particle.h"

namespace platform {


struct CloudFunc {
    const char* name;
    std::function<int32_t(String)> fn;
};

// Singleton class acts as platform wrapper
class Platform {
    public:
        // No copy constructor
        Platform(Platform const&) = delete;
        Platform& operator=(Platform const&) = delete;

        static Platform& getInstance();

        static void init();

        static void regCloudFunc(platform::CloudFunc* fns, uint32_t count);

    private:
        explicit Platform() {};
};

} // namespace platform

extern const platform::Platform& API;
