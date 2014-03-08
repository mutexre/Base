#include <Runtime/Runtime.h>

rapidxml::xml_node<>* Rt::XML::findNestedElement(rapidxml::xml_node<>* firstChild) {
    rapidxml::xml_node<>* nestedNode = 0;
    bool didFoundElement = false;

    for (auto child = firstChild; child; child = child->next_sibling()) {
        if (child->type() == rapidxml::node_element) {
            if (!didFoundElement) {
                didFoundElement = true;
                nestedNode = child;
            }
            else
                Rt::error(0x82C278BB);
        }
    }

    return nestedNode;
}
