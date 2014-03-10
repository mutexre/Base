#ifndef header_EB8CC2462BB8
#define header_EB8CC2462BB8

namespace GL
{
    namespace UniformBlock
    {
        class Instance : public Rt::Object
        {
        protected:
            std::shared_ptr<ShaderProgram> program;
            std::shared_ptr<BindingPoint> bindingPoint;
            GLuint index;
            Rt::u1* mappingPtr;

        public:
            Instance();

            Instance(std::shared_ptr<ShaderProgram> program,
                     std::shared_ptr<BindingPoint> bindingPoint);

            virtual ~Instance() {}

            std::shared_ptr<BindingPoint> getBindingPoint() const;
            void setBindingPoint(std::shared_ptr<BindingPoint>);

            void bind() const;

            void prepare(Buffer::Access access);
            void complete();

            template <typename T>
            T getScalar(const std::string& name);

            template <typename T>
            void setScalar(const std::string& name, T);

            template <typename T>
            void setArray(const std::string& name, T* values, Rt::u4 offset, Rt::u4 count, Rt::u4 stride = sizeof(T));

            template <typename T>
            void setMatrix(const std::string& name,
                           T* values,
                           bool srcIsRowMajor,
                           Rt::u4 nRows, Rt::u4 nColumns,
                           Rt::u4 rowStride, Rt::u4 columnStride);
        };
        
        #include <GLCPP/UniformBlock/InstanceDefinition.h>
    }
}

#endif
