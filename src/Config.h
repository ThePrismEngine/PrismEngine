#pragma once

namespace prism {

    struct Version
    {
        int MAJOR;
        int MINOR;
        int PATCH;
    };
    
    struct PrismVersion {
        static constexpr int MAJOR = 0;
        static constexpr int MINOR = 1;
        static constexpr int PATCH = 0;
        static constexpr const char* STRING = "0.1.0";
    };

    struct PrismInfo {
        static constexpr const char* NAME = "PrismEngine";
        static constexpr const char* DESCRIPTION = "lightweight Vulkan Engine";
    };
}