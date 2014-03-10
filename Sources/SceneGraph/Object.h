#ifndef header_9197923F0748
#define header_9197923F0748

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

using boost::multi_index_container;
using boost::multi_index::indexed_by;
using boost::multi_index::ordered_unique;
using boost::multi_index::ordered_non_unique;
using boost::multi_index::member;
using boost::multi_index::tag;
using boost::multi_index::const_mem_fun;

#define VECTOR_SEGMENTS 1

namespace SG
{
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
#if !VECTOR_SEGMENTS
        typedef multi_index_container<std::shared_ptr<Segment>,
                                      indexed_by<ordered_unique<const_mem_fun<Segment, std::shared_ptr<Drawable>, &Segment::getDrawable>>,
                                                 ordered_non_unique<const_mem_fun<Segment, std::shared_ptr<Program>, &Segment::getProgram>>,
                                                 ordered_non_unique<const_mem_fun<Segment, std::shared_ptr<Material>, &Segment::getMaterial>>>>
        Segments;
#else
        using Segments = std::vector<std::shared_ptr<SG::Segment>>;
#endif

    protected:
        Segments segments;

    public:
        Segments& getSegments() {
            return segments;
        }

/*
        std::shared_ptr<Program> getProgram() const {
            return program;
        }

        void setProgram(std::shared_ptr<Program> program) {
            this->program = program;
        }

        std::shared_ptr<Model> getModel() const {
            return model;
        }

        void setModel(std::shared_ptr<Model> model) {
            this->model = model;
        }

        std::shared_ptr<Material> getMaterial() const {
            return material;
        }

        void setMaterial(std::shared_ptr<Material> material) {
            this->material = material;
        }
*/
        void add(std::shared_ptr<Segment> segment) {
#if VECTOR_SEGMENTS
            segments.push_back(segment);
#else
            segments.insert(segment);
#endif
        }

// Uniform block variables setters/getters

// Get Scalar
/*
        template <typename T>
        T getScalar(Rt::u1* ptr, const Rt::Option<GL::ShaderProgram::UniformBlock::ActiveUniforms>& activeUniforms, const std::string& uniformName)
        {
            if (!activeUniforms.defined) Rt::error(0xA53923EA);

            auto uniformIndex = activeUniforms.get().right[uniformName];
            auto offset = program->get()->getUniformOffset(uniformIndex);

            return *((T*)(ptr + offset.get()));
        }

        template <typename T>
        T getScalar(Rt::u1* ptr, GLuint uniformBlockIndex, const std::string& uniformName) {
            return getScalar<T>(ptr, program->get()->getUniformBlockActiveUniforms(uniformBlockIndex), uniformName);
        }

        template <typename T>
        T getScalar(Rt::u1* ptr, const std::string& uniformBlockName, const std::string& uniformName) {
            return getScalar<T>(ptr, program->get()->getUniformBlockActiveUniforms(uniformBlockName), uniformName);
        }

// Set Scalar
        template <typename T>
        void setScalar(const Rt::u1* ptr,
                       Rt::Option<GL::ShaderProgram::UniformBlock::ActiveUniforms> activeUniforms,
                       const std::string& uniformName,
                       T value)
        {
            if (activeUniforms.defined) {
                Rt::Option<GLint> index;
                for (auto au : activeUniforms.get().right)
                    if (au.first == uniformName) {
                        index.define(au.second);
                        break;
                    }

                //auto uniformIndex = activeUniforms.get().right.find(uniformName);
                //if (uniformIndex != activeUniforms.get().right.end())
                if (index.defined)
                {
                    //printf("uniform index = %s %s <-> %d\n", uniformName.c_str(), (*uniformIndex).first.c_str(), uniformIndex->second);
                    auto offset = program->get()->getUniformOffset(index.get());
                    if (offset.defined)
                        *((T*)(ptr + offset.get())) = value;
                    else
                        Rt::error(0x8BA6D447);
                }
                else
                    Rt::error(0xAC5512CA);
            }
            else
                Rt::error(0xA8F413CB);
        }

        template <typename T>
        void setScalar(const Rt::u1* ptr, GLuint uniformBlockIndex, const std::string& uniformName, T value) {
            setScalar<T>(ptr, program->get()->getUniformBlockActiveUniforms(uniformBlockIndex), uniformName, value);
        }

        template <typename T>
        void setScalar(const Rt::u1* ptr, const std::string& uniformBlockName, const std::string& uniformName, T value) {
            setScalar<T>(ptr, program->get()->getUniformBlockActiveUniforms(uniformBlockName), uniformName, value);
        }

// Set Array
        template <typename T>
        void setArray(Rt::u1* ptr,
                      const Rt::Option<GL::ShaderProgram::UniformBlock::ActiveUniforms>& activeUniforms,
                      const std::string& uniformName, const T* values,
                      Rt::u4 offset, Rt::u4 count, Rt::u4 stride = sizeof(T))
        {
            if (activeUniforms.defined) {
                Rt::Option<GLint> index;
                for (auto au : activeUniforms.get().right)
                    if (au.first == uniformName) {
                        index.define(au.second);
                        break;
                    }

//                auto uniformIndex = activeUniforms.get().right.find(uniformName);
//                if (uniformIndex != activeUniforms.get().right.end())
                if (index.defined)
                {
//                    printf("uniform index = %s %s <-> %d\n", uniformName.c_str(), (*uniformIndex).first.c_str(), uniformIndex->second);
                    printf("uniform index = %s %d\n", uniformName.c_str(), index.get());
                    auto uniform = program->get()->getUniform(index.get());//uniformIndex->second);
                    if (uniform.defined)
                        Rt::stridedCopy<T>((const Rt::u1*)values, stride,
                                           ptr + uniform.get().offset + offset * uniform.get().arrayStride, uniform.get().arrayStride,
                                           count);
                    else
                        Rt::error(0xC9CDDC7B);
                }
                else
                    Rt::error(0x3195728B);
            }
            else
                Rt::error(0x5329284B);
        }

        template <typename T>
        void setArray(Rt::u1* ptr, GLuint uniformBlockIndex,
                      const std::string& uniformName, const T* values,
                      Rt::u4 offset, Rt::u4 count, Rt::u4 stride = sizeof(T))
        {
            setArray<T>(ptr, program->get()->getUniformBlockActiveUniforms(uniformBlockIndex), uniformName, values, offset, count, stride);
        }

        template <typename T>
        void setArray(Rt::u1* ptr, const std::string& uniformBlockName,
                      const std::string& uniformName, const T* values,
                      Rt::u4 offset, Rt::u4 count, Rt::u4 stride = sizeof(T))
        {
            setArray<T>(ptr, program->get()->getUniformBlockActiveUniforms(uniformBlockName), uniformName, values, offset, count, stride);
        }

// Set Matrix
        template <typename T>
        void setMatrix(const Rt::u1* ptr, const Rt::Option<GL::ShaderProgram::UniformBlock::ActiveUniforms>& activeUniforms,
                       const std::string& uniformName,
                       const T* values,
                       bool srcIsRowMajor,
                       Rt::u4 nRows, Rt::u4 nColumns,
                       Rt::u4 rowStride, Rt::u4 columnStride)
        {
            if (activeUniforms.defined)
            {
                auto uniformIndex = activeUniforms.get().right.find(uniformName);
                auto uniform = program->get()->getUniform((*uniformIndex).second);

                auto offset = uniform.get().offset;
                auto arrayStride = uniform.get().arrayStride;
                auto matrixStride = uniform.get().matrixStride;
                auto dstIsRowMajor = uniform.get().isRowMajor;

                auto dstPtr = ptr + offset;
                
                if (arrayStride == 0) arrayStride = sizeof(T);

                if (srcIsRowMajor) {
                    if (dstIsRowMajor)
                        for (int row = 0; row < nRows; row++)
                            Rt::stridedCopy<T>(((const Rt::u1*)values) + rowStride * row, columnStride,
                                               dstPtr + row * matrixStride, arrayStride,
                                               nColumns);
                    else
                        for (int column = 0; column < nColumns; column++)
                            Rt::stridedCopy<T>(((const Rt::u1*)values) + columnStride * column, rowStride,
                                               dstPtr + column * arrayStride, matrixStride,
                                               nRows);
                }
                else {
                    if (dstIsRowMajor)
                        for (int column = 0; column < nColumns; column++)
                            Rt::stridedCopy<T>(((const Rt::u1*)values) + columnStride * column, rowStride,
                                               dstPtr + column * matrixStride, arrayStride,
                                               nRows);
                    else
                        for (int row = 0; row < nRows; row++)
                            Rt::stridedCopy<T>(((const Rt::u1*)values) + rowStride * row, columnStride,
                                               dstPtr + row * arrayStride, matrixStride,
                                               nColumns);
                }
            }
            Rt::error(0x9C7601C8);
        }

        template <typename T>
        void setMatrix(const Rt::u1* ptr, GLuint uniformBlockIndex,
                       const std::string& uniformName,
                       const T* values,
                       bool srcIsRowMajor,
                       Rt::u4 nRows, Rt::u4 nColumns,
                       Rt::u4 rowStride, Rt::u4 columnStride)
        {
            setMatrix<T>(ptr, program->get()->getUniformBlockActiveUniforms(uniformBlockIndex),
                         uniformName, values,
                         srcIsRowMajor, nRows, nColumns,
                         rowStride, columnStride);
        }

        template <typename T>
        void setMatrix(const Rt::u1* ptr, const std::string& uniformBlockName,
                       const std::string& uniformName,
                       const T* values,
                       bool srcIsRowMajor,
                       Rt::u4 nRows, Rt::u4 nColumns,
                       Rt::u4 rowStride, Rt::u4 columnStride)
        {
            setMatrix<T>(ptr, program->get()->getUniformBlockActiveUniforms(uniformBlockName),
                         uniformName, values,
                         srcIsRowMajor, nRows, nColumns,
                         rowStride, columnStride);
        }
*/
    };
}

#endif
