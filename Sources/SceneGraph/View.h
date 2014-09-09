#ifndef header_10AA5478F47F
#define header_10AA5478F47F

namespace SG
{
    class View : public std::enable_shared_from_this<View>
    {
    private:
        std::list<ObjectPtr> orderedObjects;
        std::shared_ptr<ObjectsOrder> order;
        std::shared_ptr<Objects> objects;
        std::shared_ptr<Lights> lights;
        GL::Viewport viewport;

        struct Visibility {
            using _Object = std::map<ObjectPtr, React::ScalarPtr<bool>>;
            using _Segment = std::map<std::pair<ObjectPtr, std::shared_ptr<Segment>>, React::ScalarPtr<bool>>;

            _Object object;
            _Segment segment;
        }
        visibility;

        struct {
            using Bindings = std::map<std::string, React::MatrixPtr<>>;
            Bindings global;
            std::map<ObjectPtr, Bindings> perObject;
            std::map<ObjectPtr, std::map<std::shared_ptr<Segment>, Bindings>> perObjectAndSegment;
        }
        bindings;

    private:
        void orderObjects(void*) {
            if (objects.get() && order.get())
                orderedObjects = objects->sort(order);
        }

    public:
        View() {}

        std::shared_ptr<Objects> getObjects() {
            return objects;
        }

        void setObjects(std::shared_ptr<Objects> objects) {
            this->objects = objects;
            orderObjects(nullptr);
            objects->addObserver(Objects::Signal::slot_type(&View::orderObjects, this, _1).track_foreign(shared_from_this()));
        }

        std::shared_ptr<ObjectsOrder> getOrder() {
            return order;
        }

        void setOrder(std::shared_ptr<ObjectsOrder> order) {
            this->order = order;
            orderObjects(nullptr);
            order->addObserver(ObjectsOrder::Signal::slot_type(&View::orderObjects, this, _1).track_foreign(shared_from_this()));
        }

        Visibility::_Object& getObjectsVisibility() {
            return visibility.object;
        }

        void setObjectsVisibility(Visibility::_Object visibility) {
            this->visibility.object = visibility;
        }

        Visibility::_Segment getSegmentVisibility() {
            return visibility.segment;
        }

        void setSegmentVisibility(Visibility::_Segment visibility) {
            this->visibility.segment = visibility;
        }

        GL::Viewport getViewport() const {
            return viewport;
        }

        void setViewport(GL::Viewport viewport) {
            this->viewport = viewport;
//            aspectRatio = float(viewport.h) / float(viewport.w);
            glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
        }

        void bind(const std::string& variable, React::MatrixPtr<> bindingPoint) {
            bindings.global[variable] = bindingPoint;
        }

        void unbind(const std::string& variable) {
            auto iter = bindings.global.find(variable);
            if (iter != bindings.global.end()) bindings.global.erase(iter);
        }

        void bind(const ObjectPtr& object, const std::string& variable, React::MatrixPtr<> bindingPoint) {
            bindings.perObject[object][variable] = bindingPoint;
        }

        void unbind(const ObjectPtr& object, const std::string& variable) {
            auto objectBindingsIter = bindings.perObject.find(object);
            if (objectBindingsIter != bindings.perObject.end()) {
                auto& objectBindings = (*objectBindingsIter).second;
                auto bindingIter = objectBindings.find(variable);
                if (bindingIter != objectBindings.end())
                    objectBindings.erase(bindingIter);
            }
        }

        void bind(const ObjectPtr& object, std::shared_ptr<Segment> segment,
                  const std::string& variable, React::MatrixPtr<> bindingPoint)
        {
            bindings.perObject[object][variable] = bindingPoint;
        }

        void unbind(const ObjectPtr& object, std::shared_ptr<Segment> segment, const std::string& variable)
        {
            auto objectBindingsIter = bindings.perObject.find(object);
            if (objectBindingsIter != bindings.perObject.end()) {
                auto& objectBindings = (*objectBindingsIter).second;
                auto bindingIter = objectBindings.find(variable);
                if (bindingIter != objectBindings.end())
                    objectBindings.erase(bindingIter);
            }
        }

        void setVisibility(const ObjectPtr& object, React::ScalarPtr<bool> value)
        {
            visibility.object[object] = value;
        }

        void setVisibility(const ObjectPtr& object,
                           std::shared_ptr<SG::Segment> segment,
                           React::ScalarPtr<bool> value)
        {
            visibility.segment[std::make_pair(object, segment)] = value;
        }

        void render()
        {
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            for (auto& object : orderedObjects)
            {
                bool objectVisible = true;

                auto iter = visibility.object.find(object);
                if (iter != visibility.object.end())
                    objectVisible = iter->second->get();

                if (objectVisible)
                    for (auto& segment : object->value()->getSegments()) {
                        bool segmentVisible = true;

                        auto iter = visibility.segment.find(std::make_pair(object, segment));
                        if (iter != visibility.segment.end())
                            segmentVisible = iter->second->get();

                        if (segmentVisible) {
                            auto& programValue = segment->getProgram()->value();
                            programValue->bind();

                            for (auto& binding : bindings.global)
                                programValue->setVariable(binding.first, binding.second);

                            for (auto& binding : bindings.perObject[object])
                                programValue->setVariable(binding.first, binding.second);

                            for (auto& binding : bindings.perObjectAndSegment[object][segment])
                                programValue->setVariable(binding.first, binding.second);

                            segment->render();

                            programValue->unbind();
                        }
                    }
            }
        }
    };
}

#endif
