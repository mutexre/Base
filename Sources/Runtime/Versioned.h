#ifndef header_6276E78C94FF
#define header_6276E78C94FF

namespace Rt
{
    template <typename T>
    class Versioned
    {
    public:
        typedef T V;

    private:
        T version;

    public:
        Versioned() : version(0) {}

        bool match(T version) {
            return this->version == version;
        }

        T getVersion() const {
            return version;
        }

        void setVersion(T version) {
            this->version = version;
        }
        
        void incrementVersion() {
            version++;
        }
    };

    template <typename T>
    class SharedVersioned
    {
    private:
        std::shared_ptr<T> object;
        Rt::Option<typename T::V> storedVersion;

    public:
        SharedVersioned() {}

        SharedVersioned(std::shared_ptr<T> object) {
            this->object = object;
        }

        virtual ~SharedVersioned() {}

        bool isUpToDate() {
            return storedVersion.defined && object->match(storedVersion.get());
        }

        void update() {
            storedVersion.define(object->getVersion());
        }

        std::shared_ptr<T>& operator->() {
            return object;
        }

        std::shared_ptr<T>& get() {
            return object;
        }

        void set(std::shared_ptr<T> object) {
            this->object = object;
        }
    };
}

#endif
