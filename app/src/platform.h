#include "Particle.h"
#include <functional>

namespace platform {

// Singleton class acts as platform wrapper
class Platform {
  public:
    // No copy constructor
    Platform(Platform const &) = delete;
    Platform &operator=(Platform const &) = delete;

    static Platform &getInstance();

    static void init();

  private:
    explicit Platform() = default;
};

} // namespace platform

extern const platform::Platform &API;
