#include "Particle.h"

namespace platform {
// Singleton class acts as platform wrapper
class Platform {
    public:
        // No copy constructor
        Platform(Platform const&) = delete;
        Platform& operator=(Platform const&) = delete;

        Platform& getInstance();

    private:
        explicit Platform() {};
};

} // namespace platform
using platform::Platform;
