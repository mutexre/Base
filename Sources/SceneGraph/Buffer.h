#ifndef header_F93169B9D089
#define header_F93169B9D089

namespace SG
{
    class Buffer
    {
    private:
        std::shared_ptr<GL::Buffer> buffer;

    public:
        Buffer() : Buffer(std::make_shared<GL::Buffer>()) {}

        Buffer(std::shared_ptr<GL::Buffer> buffer) {
            this->buffer = buffer;
        }

        std::shared_ptr<GL::Buffer> get() {
            return buffer;
        }

        void set(std::shared_ptr<GL::Buffer> buffer) {
            this->buffer = buffer;
        }
    };
}

#endif
