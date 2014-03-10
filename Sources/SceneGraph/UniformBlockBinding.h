#ifndef header_9197B23FA748
#define header_9197B23FA748

namespace SG
{
    class UniformBlockBinding
    {
    private:
        Rt::u1* mappingPtr;

    public:
        GLuint point;
        std::shared_ptr<Buffer> buffer;
        Rt::Option<Rt::Range<Rt::u4>> range;

        UniformBlockBinding() : mappingPtr(nullptr) {}

        UniformBlockBinding(const UniformBlockBinding& that) {
            point = that.point;
            buffer = that.buffer;
            range = that.range;
            mappingPtr = that.mappingPtr;
        }

        UniformBlockBinding(UniformBlockBinding&& that) {
            point = that.point;
            buffer = that.buffer;
            range = that.range;
            mappingPtr = that.mappingPtr;
            that.mappingPtr = nullptr;
        }

        //Binding(const Binding&& that) = delete;

        ~UniformBlockBinding() {
            if (mappingPtr) unmap();
        }

        void bind() {
            if (!range.defined) {
                GL::Buffer::bindBufferBase(GL::Buffer::Target::Uniform, point, buffer.get()->get().get());
                GL::Buffer::bind(GL::Buffer::Target::Uniform, buffer.get()->get().get());
            }
            else
                GL::Buffer::bindBufferRange(GL::Buffer::Target::Uniform, point, range.get().a, range.get().length(), buffer.get()->get().get());
        }

        void unbind() {
            GL::Buffer::unbind(GL::Buffer::Target::Uniform);
        }

        Rt::u1* map(GL::Buffer::Access access, bool doBind = true) {
            if (doBind) bind();
            mappingPtr = (Rt::u1*)GL::Buffer::map(GL::Buffer::Target::Uniform, access);
            return mappingPtr;
        }

        void unmap(bool doUnbind = true) {
            GL::Buffer::unmap(GL::Buffer::Target::Uniform);
            mappingPtr = nullptr;
            if (doUnbind) unbind();
        }

        Rt::u1* getMappingPtr() const {
            return mappingPtr;
        }

        bool isMapped() const {
            return mappingPtr != nullptr;
        }
    };
}

#endif
