#ifndef header_FE0FFFF9CF99
#define header_FE0FFFF9CF99

namespace SG
{
    struct StandardTransforms {
        struct Transforms {
            std::shared_ptr<React::Multiply<Math::Matrix<float>>> self;
            std::shared_ptr<React::Multiply<Math::Matrix<float>>> selfMulInversePov;
            std::shared_ptr<React::InverseTranspose<float>> inverseTranspose;
            std::shared_ptr<React::SubMatrix<float>> normal;

            Transforms() {
                self = std::make_shared<React::Multiply<Math::Matrix<float>>>();
                self->setName("self");
                auto output = React::makeMatrix<>(4);
                output->setName("self output");
                self->setOutput(output);

                selfMulInversePov = std::make_shared<React::Multiply<Math::Matrix<float>>>();
                selfMulInversePov->setName("selfMulInversePov");
                output = React::makeMatrix<>(4);
                output->setName("selfMulInversePov output");
                selfMulInversePov->setOutput(output);

                inverseTranspose = std::make_shared<React::InverseTranspose<float>>();
                inverseTranspose->setName("inverse transpose");
                output = React::makeMatrix<>(4);
                output->setName("inverseTranspose output");
                inverseTranspose->setOutput(output);

                normal = std::make_shared<React::SubMatrix<float>>(3);
                normal->setName("normal");
                output = React::makeMatrix<>(4);
                output->setName("normal output");
                normal->setOutput(output);
            }
        }
        transforms;

        struct Matrices {
            React::MatrixPtr<> scale;
            React::MatrixPtr<> rotation;
            React::MatrixPtr<> translate;

            Matrices() {
                scale = React::makeMatrix<>(4);
                scale->setName("scale");

                rotation = React::makeMatrix<>(4);
                rotation->setName("rotation");

                translate = React::makeMatrix<>(4);
                translate->setName("translate");
            }
        }
        matrices;

        StandardTransforms(const React::MatrixPtr<>& transform, const React::MatrixPtr<>& inversePov) {
            transforms.self->addInput(matrices.scale);
            transforms.self->addInput(matrices.rotation);
            transforms.self->addInput(matrices.translate);
            transforms.self->addInput(transform);
            transforms.selfMulInversePov->addInput(transforms.self->getOutput());
            transforms.selfMulInversePov->addInput(inversePov);
            transforms.inverseTranspose->setInput(transforms.selfMulInversePov->getOutput());
            transforms.normal->setInput(transforms.inverseTranspose->getOutput());
        }
    };
}

#endif
