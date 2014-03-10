#ifndef header_45EC4B83F51B
#define header_45EC4B83F51B

namespace SG
{
    class Scene : public Rt::Object
    {
    public:
        std::map<std::string, std::shared_ptr<Object>> objects;
        std::map<std::string, std::shared_ptr<Model>> models;
        std::map<std::string, std::shared_ptr<Program>> programs;
        std::map<std::string, std::shared_ptr<Material>> materials;
//        std::map<std::string, std::shared_ptr<Matrix>> matrices;
//        std::map<std::string, std::shared_ptr<Transform>> transforms;
        std::map<std::string, std::shared_ptr<ObjectsOrder>> orders;
        struct {
            std::map<std::string, std::shared_ptr<Objects>> objects;
//        std::map<std::string, std::shared_ptr<Lights>> lights;
        }
        groups;
        std::map<std::string, std::shared_ptr<Frame>> frames;

    public:
        void addProgram(const std::string& name, std::shared_ptr<Program> program) {
            programs[name] = program;
        }

        void removeProgram(const std::string& name) {
            programs.erase(name);
        }

        void addModel(const std::string& name, std::shared_ptr<Model> model) {
            models[name] = model;
        }

        void removeModel(const std::string& name) {
            models.erase(name);
        }

        void addMaterial(const std::string& name, std::shared_ptr<Material> material) {
            materials[name] = material;
        }

        void removeMaterial(const std::string& name) {
            materials.erase(name);
        }

        void addObject(const std::string& name, std::shared_ptr<Object> object) {
            objects[name] = object;
        }

        void removeObject(const std::string& name) {
            objects.erase(name);
        }
/*
        void addMatrix(const std::string& name, std::shared_ptr<Matrix> matrix) {
            matrices[name] = matrix;
        }

        void removeMatrix(const std::string& name) {
            matrices.erase(name);
        }
*/
        void addTransform(const std::string& name, std::shared_ptr<Transform> transform) {
            transforms[name] = transform;
        }

        void removeTransform(const std::string& name) {
            transforms.erase(name);
        }

        void addOrder(const std::string& name, std::shared_ptr<ObjectsOrder> order) {
            orders[name] = order;
        }

        void removeOrder(const std::string& name) {
            orders.erase(name);
        }

        void addObjectsGroup(const std::string& name, std::shared_ptr<Objects> group) {
            groups.objects[name] = group;
        }

        void removeGroup(const std::string& name) {
            groups.objects.erase(name);
        }

        void addFrame(const std::string& name, std::shared_ptr<Frame> frame) {
            frames[name] = frame;
        }

        void removeFrame(const std::string& name) {
            frames.erase(name);
        }
    };
}

#endif
