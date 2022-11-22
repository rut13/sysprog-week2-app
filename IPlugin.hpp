#ifndef IPLUGIN_H_
#define IPLUGIN_H_

#include <string>

namespace sp {
    class IPlugin {
        public:
            virtual ~IPlugin() = default;
            virtual void convert(const std::string& path) = 0;
            virtual std::string name() const = 0;
    };
}

#endif // IPLUGIN_H_
