#ifndef header_5AD1DC6BE287
#define header_5AD1DC6BE287

#include <rapidxml.hpp>

namespace Rt
{
    namespace XML
    {
        template <typename T>
        class Parser
        {
        protected:
            std::map<std::string, ElementProcessor<T>*> elementProcessors;

            virtual T* parseRecursively(rapidxml::xml_node<>* node, void* data) {
                switch (node->type()) {
                    case rapidxml::node_document: {
                        auto nestedElement = findNestedElement(node->first_node());
                        if (nestedElement) return parseRecursively(nestedElement, data);
                    }
                    break;

                    case rapidxml::node_element: {
                        auto iter = elementProcessors.find(node->name());
                        if (iter != elementProcessors.end())
                            return (*iter).second->process(node, data, [&](rapidxml::xml_node<>* node, void* data) -> void* { return this->parseRecursively(node, data); });
                    }
                    break;

                    default:
                        printf("unknown %d\n", node->type());
                    break;
                }

                return 0;
            }

        public:
            virtual T* parse(rapidxml::xml_node<>* node) {
                return parseRecursively(node, 0);
            }
        };
    }
}

#endif
