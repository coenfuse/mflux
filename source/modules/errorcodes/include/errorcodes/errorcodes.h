// preprocessor flags
#pragma once

// standard includes
#include <cstdint>

// forward references
// ..



namespace felidae
{
    enum class ERC : uint16_t
    {
        // General error codes
        SUCCESS = 0,
        FAILURE,
        EXCEPTION,
        MEMORY_ALLOCATION_FAILED

        // Engine level error codes
        // ...

        // Core level error codes
        // ...

        // MQTT level error codes
        // ...

        // Influx level error codes
        // ...

        // MemDB level error codes
        // ...

        // Minix level error codes
        // ...
    };
}