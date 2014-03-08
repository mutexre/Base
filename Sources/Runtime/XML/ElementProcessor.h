#ifndef header_43AFDD92BF15
#define header_43AFDD92BF15

#include <rapidxml.hpp>

namespace Rt
{
    namespace XML
    {
        template <typename T>
        class ElementProcessor
        {
        protected:
            std::map<std::string, std::function<void (T*, rapidxml::xml_attribute<>*)>> attrsProcessors;

        protected:
            void matchAttrs(rapidxml::xml_attribute<>* firstAttr, T* type) const {
                for (auto attr = firstAttr; attr; attr = attr->next_attribute()) {
                    bool matchedCommonAttr = false;

                    for (auto& attrProc : attrsProcessors)
                        if (!strncmp(attr->name(), attrProc.first.c_str(), attr->name_size())) {
                            attrProc.second(type, attr);
                            matchedCommonAttr = true;
                            break;
                        }
                }
            }

        public:
            virtual T* process(rapidxml::xml_node<>* node, void* data, std::function<void* (rapidxml::xml_node<>*, void*)> callback) = 0;
        };
    }
}

#endif
