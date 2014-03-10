#ifndef header_6D27231426CA
#define header_6D27231426CA

/*
namespace GL
{
    namespace UniformBlock
    {
        template <typename Description, typename T>
        T getScalar(Rt::u1* ptr, Layout<Description>*, unsigned int var);

        template <typename Description, typename T>
        void setScalar(Rt::u1* ptr, Layout<Description>*, unsigned int var, T value);

        template <typename Description, typename T>
        void setArray(Rt::u1* ptr, Layout<Description>*, unsigned int var, T* values, Rt::u4 offset, Rt::u4 count, Rt::u4 stride);

        template <typename Description, typename T>
        void setMatrix(Rt::u1* ptr, Layout<Description>*,
                       unsigned int var,
                       T* values,
                       bool srcIsRowMajor,
                       Rt::u4 nRows, Rt::u4 nColumns,
                       Rt::u4 rowStride, Rt::u4 columnStride);

        #include <GLCPP/UniformBlock/UniformBlockDefinition.h>
    }
}
*/
#include <GLCPP/UniformBlock/BindingPoint.h>
#include <GLCPP/UniformBlock/Instance.h>

#endif
