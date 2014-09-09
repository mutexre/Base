#ifndef header_5895F5690948
#define header_5895F5690948

namespace SG
{
    namespace Topological
    {
        class GatherSegments : public React::Transform<GatherSegments>
        {
            REACT_DEFINE_INPUT(React::ScalarPtr<bool>, enable0, getEneble0, setEnable0, &GatherSegments::invalidate)
            REACT_DEFINE_INPUT(React::ScalarPtr<bool>, enable1, getEneble1, setEnable1, &GatherSegments::invalidate)
            REACT_DEFINE_INPUT(React::ScalarPtr<bool>, enable2, getEneble2, setEnable2, &GatherSegments::invalidate)
            REACT_DEFINE_INPUT(React::ScalarPtr<std::shared_ptr<Segment>>, segment0, getSegment0, setSegment0, &GatherSegments::invalidate)
            REACT_DEFINE_INPUT(React::ScalarPtr<std::shared_ptr<Segment>>, segment1, getSegment1, setSegment1, &GatherSegments::invalidate)
            REACT_DEFINE_INPUT(React::ScalarPtr<std::shared_ptr<Segment>>, segment2, getSegment2, setSegment2, &GatherSegments::invalidate)
            REACT_DEFINE_OUTPUT(React::ScalarPtr<std::shared_ptr<SG::Object>>, object, getObject, setObject, &GatherSegments::evaluate)

        private:
            std::vector<std::shared_ptr<SG::Segment>> segments;

        protected:
            void invalidate() {
                if (object.get())
                    object->invalidate();
            }

            void evaluate() {
                segments.clear();

                if (enable0->value())
                    segments.push_back(segment0->value());

                if (enable1->value())
                    segments.push_back(segment1->value());

                if (enable2->value())
                    segments.push_back(segment2->value());

                object->currentValue()->setSegments(segments);
                commit(object);
            }
        };
    }
}

#endif
