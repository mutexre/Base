#ifndef header_FE0FFFF9CF99
#define header_FE0FFFF9CF99

namespace SG
{
    struct StandardTransforms {
        struct Transforms {
            std::shared_ptr<React::Multiply<>> self;
            std::shared_ptr<React::Multiply<>> selfMulInversePov;
            std::shared_ptr<React::InverseTranspose<>> inverseTranspose;
            std::shared_ptr<React::SubMatrix<>> normal;

            Transforms() {
                self = std::make_shared<React::Multiply<>>();
                self->setName("self");
                auto output = React::makeMatrix<>(4);
                output->setName("self output");
                self->addOutput(output);

                selfMulInversePov = std::make_shared<React::Multiply<>>();
                selfMulInversePov->setName("selfMulInversePov");
                output = React::makeMatrix<>(4);
                output->setName("selfMulInversePov output");
                selfMulInversePov->addOutput(output);

                inverseTranspose = std::make_shared<React::InverseTranspose<>>();
                inverseTranspose->setName("inverse transpose");
                output = React::makeMatrix<>(4);
                output->setName("inverseTranspose output");
                inverseTranspose->addOutput(output);

                normal = std::make_shared<React::SubMatrix<>>(3);
                normal->setName("normal");
                output = React::makeMatrix<>(4);
                output->setName("normal output");
                normal->addOutput(output);
            }
        }
        transforms;

        struct Matrices {
            React::ValuePtr<> scale;
            React::ValuePtr<> rotation;
            React::ValuePtr<> translate;

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

        StandardTransforms(const React::ValuePtr<>& transform, const React::ValuePtr<>& inversePov) {
            transforms.self->addInput(matrices.scale);
            transforms.self->addInput(matrices.rotation);
            transforms.self->addInput(matrices.translate);
            transforms.self->addInput(transform);
            transforms.selfMulInversePov->addInput(transforms.self->getOutput());
            transforms.selfMulInversePov->addInput(inversePov);
            transforms.inverseTranspose->addInput(transforms.selfMulInversePov->getOutput());
            transforms.normal->addInput(transforms.inverseTranspose->getOutput());
        }
    };
}

#endif
