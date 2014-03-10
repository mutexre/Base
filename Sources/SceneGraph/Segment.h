#ifndef header_CCCCB23FA748
#define header_CCCCB23FA748

namespace SG
{
    class Segment
    {
    public:
        class Piece
        {
        protected:
            std::shared_ptr<DataBinding> dataBinding;
            std::shared_ptr<DrawCall> drawCall;

        public:
            Piece() {}

            Piece(std::shared_ptr<DataBinding> dataBinding, std::shared_ptr<DrawCall> drawCall) {
                this->dataBinding = dataBinding;
                this->drawCall = drawCall;
            }

            virtual ~Piece() {}

            std::shared_ptr<DataBinding> getDataBinding() const {
                return dataBinding;
            }

            void setDataBinding(std::shared_ptr<DataBinding> dataBinding) {
                this->dataBinding = dataBinding;
            }

            std::shared_ptr<DrawCall> getDrawCall() const {
                return drawCall;
            }

            void setDrawCall(std::shared_ptr<DrawCall> drawCall) {
                this->drawCall = drawCall;
            }

            void render() {
                dataBinding->prepare();
                (*drawCall)();
                dataBinding->complete();
            }
        };

        using Pieces = std::list<Piece>;
        using Bindings = multi_index_container<UniformBlockBinding, indexed_by<ordered_unique<member<UniformBlockBinding, GLuint, &UniformBlockBinding::point>>>>;

    private:
        Pieces pieces;
        std::shared_ptr<Program> program;
        std::shared_ptr<Material> material;
        Bindings bindings;
        struct {
            bool enableDepthTest;
        }
        flags;

    public:
        Segment() {}

        Segment(std::shared_ptr<Program> program,
                std::shared_ptr<Material> material,
                bool enableDepthTest = true)
        {
            this->program = program;
            this->material = material;
            flags.enableDepthTest = enableDepthTest;
        }

        Segment(Pieces pieces,
                std::shared_ptr<Program> program,
                std::shared_ptr<Material> material,
                bool enableDepthTest = true)
            : Segment(program, material, enableDepthTest)
        {
            this->pieces = pieces;
        }

        Segment(Piece piece,
                std::shared_ptr<Program> program,
                std::shared_ptr<Material> material,
                bool enableDepthTest = true)
            : Segment(program, material, enableDepthTest)
        {
            pieces.push_back(piece);
        }

        Segment(std::shared_ptr<DataBinding> dataBinding,
                std::shared_ptr<DrawCall> drawCall,
                std::shared_ptr<Program> program,
                std::shared_ptr<Material> material,
                bool enableDepthTest = true)
            : Segment(program, material, enableDepthTest)
        {
            Piece p(dataBinding, drawCall);
            pieces.push_back(p);
        }

        virtual ~Segment() {}

        Pieces& getPieces() {
            return pieces;
        }

        void setPieces(Pieces pieces) {
            this->pieces = pieces;
        }

        std::shared_ptr<Program> getProgram() const {
            return program;
        }

        void setProgram(std::shared_ptr<Program> program) {
            this->program = program;
        }

        std::shared_ptr<Material> getMaterial() const {
            return material;
        }

        void setMaterial(std::shared_ptr<Material> material) {
            this->material = material;
        }

        void add(GLuint bindingPoint, std::shared_ptr<Buffer> buffer,
                    Rt::Option<Rt::Range<Rt::u4>> range = Rt::Option<Rt::Range<Rt::u4>>())
        {
            UniformBlockBinding binding;
            binding.point = bindingPoint;
            binding.buffer = buffer;
            binding.range = range; //Rt::Option<Rt::Range<Rt::u4>>(0, 100000);//range;
            bindings.insert(binding);
        }

        void remove(Rt::u4 bindingPoint) {
            auto binding = bindings.find(bindingPoint);
            if (binding != bindings.end())
                bindings.erase(binding);
            else
                Rt::error(0xB0EC8E18);
        }

        bool isDepthTestEnabled() const {
            return flags.enableDepthTest;
        }

        void enableDepthTest(bool value) {
            flags.enableDepthTest = value;
        }

// Bind/unbind uniform block buffer
        void bindUniformBlockBuffer(const std::string& name) {
            auto bindingPoint = program->get()->getUniformBlockBinding(name);
            if (bindingPoint.defined) bindUniformBlockBuffer(bindingPoint.get());
            else Rt::error(0x45464323);
        }

        void unbindUniformBlockBuffer(const std::string& name) {
            auto bindingPoint = program->get()->getUniformBlockBinding(name);
            if (bindingPoint.defined) unbindUniformBlockBuffer(bindingPoint.get());
            else Rt::error(0x8600462C);
        }

        void bindUniformBlockBuffer(GLuint bindingPoint) {
            auto binding = bindings.find(bindingPoint);
            if (binding != bindings.end())
                bindings.modify(binding, [](UniformBlockBinding& b) { b.bind(); });
            else
                Rt::error(0xA3068652);
        }

        void unbindUniformBlockBuffer(GLuint bindingPoint) {
            auto binding = bindings.find(bindingPoint);
            if (binding != bindings.end())
                bindings.modify(binding, [](UniformBlockBinding& b) { b.unbind(); });
            else
                Rt::error(0xD5B45BF0);
        }

// Map/unmap uniform block buffer
        Rt::u1* mapUniformBlockBuffer(const std::string& name, GL::Buffer::Access access) {
            auto bindingPoint = program->get()->getUniformBlockBinding(name);
            if (bindingPoint.defined)
                return mapUniformBlockBuffer(bindingPoint.get(), access);
            else
                Rt::error(0x40393DF5);

            return nullptr;
        }

        void unmapUniformBlockBuffer(const std::string& name) {
            auto bindingPoint = program->get()->getUniformBlockBinding(name);
            if (bindingPoint.defined)
                unmapUniformBlockBuffer(bindingPoint.get());
            else
                Rt::error(0x4C06706E);
        }

        Rt::u1* mapUniformBlockBuffer(GLuint bindingPoint, GL::Buffer::Access access) {
            auto binding = bindings.find(bindingPoint);
            if (binding != bindings.end()) {
                bindings.modify(binding, [access](UniformBlockBinding& b) { b.map(access); });
                return binding->getMappingPtr();
            }
            else
                Rt::error(0x428D41F1);

            return nullptr;
        }

        void unmapUniformBlockBuffer(GLuint bindingPoint) {
            auto binding = bindings.find(bindingPoint);
            if (binding != bindings.end())
                bindings.modify(binding, [](UniformBlockBinding& b) { b.unmap(); });
            else
                Rt::error(0xC13A8FDD);
        }

        virtual void renderingSetup()
        {
            for (auto iter = bindings.begin(); iter != bindings.end(); iter++)
                bindings.modify(iter, [](UniformBlockBinding& b) { b.bind(); });

            material->applyTo(program);

            if (flags.enableDepthTest)
                glEnable(GL_DEPTH_TEST);
            else
                glDisable(GL_DEPTH_TEST);
        }

        virtual void renderingCompletion() {
            GL::ShaderProgram::unbind();
        }

        virtual void inheritedRender() {
            for (auto& p : pieces) p.render();
        }

        virtual void render() {
            renderingSetup();
            inheritedRender();
            renderingCompletion();
        }
    };
}

#endif
