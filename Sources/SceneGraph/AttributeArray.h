#ifndef header_60289CF2EC98
#define header_60289CF2EC98

namespace SG
{
    struct AttributeArray {
        void* ptr;
        GL::VertexArray::AttribPointer layout;

        AttributeArray() {}

        AttributeArray(void* ptr, GL::VertexArray::AttribPointer layout) {
            this->ptr = ptr;
            this->layout = layout;
        }
    };
}

#endif
