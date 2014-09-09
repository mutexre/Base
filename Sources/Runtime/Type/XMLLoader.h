#ifndef header_782D8F3F3DC7
#define header_782D8F3F3DC7

#include <string>
#include <regex>
#include <forward_list>

#ifdef __APPLE__
    #ifdef check
        #undef check
    #endif

    #ifdef nil
        #undef nil
    #endif

    #ifdef Nil
        #undef Nil
    #endif
#endif

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>

namespace Rt
{
    namespace Type
    {
        using std::string;
        using std::map;

        template <typename IntType>
        static IntType strToInt(const char* str) {
            char* endptr;
            auto result = strtoll(str, &endptr, 0);
            if (*endptr != '\0') Rt::error(0xDCADE9C8, "invalid str: %s\n", str);
            return IntType(result);
        }

        template <typename T>
        class ElementProcessor : public XML::ElementProcessor<T>
        {
        public:
            ElementProcessor() {
                this->attrsProcessors[string("name")] = [](T* type, rapidxml::xml_attribute<>* attr) {
                    type->setName(Option<string>(string(attr->value())));
                };

                this->attrsProcessors[string("round")] = [](T* type, rapidxml::xml_attribute<>* attr) {
                    type->setRounding(Option<typename T::SizeType>(strToInt<typename T::SizeType>(attr->value())));
                };
            }
        };

        template <typename T = u4, typename I = u4>
        class AtomProcessor : public ElementProcessor<Atom<T, I>>
        {
        public:
            AtomProcessor() {
                this->attrsProcessors[string("size")] = [](Atom<T, I>* type, rapidxml::xml_attribute<>* attr) {
                    type->setSize(strToInt<typename Atom<T, I>::SizeType>(attr->value()));
                };
            }

            virtual Atom<T, I>* process(rapidxml::xml_node<>* node, void* data, std::function<void* (rapidxml::xml_node<>*, void*)> callback) {
                auto type = new Atom<T, I>(1);
                if (!type) Rt::error(0xBF88790D);

                this->matchAttrs(node->first_attribute(), type);

                return type;
            }
        };

        template <typename T = u4, typename I = u4>
        class StructProcessor : public ElementProcessor<Struct<T, I>>
        {
        public:
            virtual Struct<T, I>* process(rapidxml::xml_node<>* node, void* data, std::function<void* (rapidxml::xml_node<>*, void*)> callback) {
                std::list<Trait<T, I>*> members;

                for (auto child = node->first_node(); child; child = child->next_sibling())
                    if (strcmp(child->name(), "typedef")) {
                        auto t = (Trait<T, I>*)callback(child, data);
                        if (!t) Rt::error(0xBACA1AE1);

                        members.push_back(t);
                    }

                auto type = new Struct<T, I>(members);
                this->matchAttrs(node->first_attribute(), type);

                return type;
            }
        };

        template <typename T = u4, typename I = u4>
        class MatrixProcessor : public ElementProcessor<Matrix<T, I>>
        {
        public:
            MatrixProcessor() {
                this->attrsProcessors[string("dim")] = [](Matrix<T, I>* type, rapidxml::xml_attribute<>* attr) {
                    std::vector<I> dimensions;
                    std::smatch matches;
                    std::regex expr("0x[\\dabcdef]+|0[\\d]+|[123456789]\\d*");
                    std::string str(attr->value());

                    while (std::regex_search(str, matches, expr)) {
                        for (auto match : matches)
                            dimensions.push_back(strToInt<I>(match.str().c_str()));

                        str = matches.suffix().str();
                    }

                    static_cast<Matrix<T, I>*>(type)->setDimensions(dimensions);
                };
            }

            virtual Matrix<T, I>* process(rapidxml::xml_node<>* node, void* data, std::function<void* (rapidxml::xml_node<>*, void*)> callback) {
                    Matrix<T, I>* type = 0;

                    auto nestedElement = XML::findNestedElement(node->first_node());
                    if (nestedElement) {
                        auto nestedType = (Trait<T, I>*)callback(nestedElement, data);
                        if (!nestedType) Rt::error(0xF954CAB7);

                        type = new Matrix<T, I>(nestedType, 0);
                        this->matchAttrs(node->first_attribute(), type);
                    }
                    else
                        Rt::error(0x73119947);

                    return type;
            }
        };

        template <typename T = u4, typename I = u4>
        class TypedefProcessor : public ElementProcessor<Trait<T, I>>
        {
        public:
            virtual Trait<T, I>* process(rapidxml::xml_node<>* node, void* data, std::function<void* (rapidxml::xml_node<>*, void*)> callback) {
                auto typeTemplate = (Trait<T, I>*)data;
                auto type = typeTemplate->copyRecursively();
                if (!type) Rt::error(0xF6F78FCF);

                this->matchAttrs(node->first_attribute(), type);

                return type;
            }
        };

        template <typename T = u4, typename I = u4>
        class XMLLoader : public XML::Parser<Trait<T, I>>
        {
        private:
            struct VertexProperties {
                std::string name;
                rapidxml::xml_node<>* node;
            };

            typedef std::map<std::string, rapidxml::xml_node<>*> Names2Nodes;
            typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperties> Graph;
            typedef std::map<std::string, Trait<T, I>*> Typedefs;
            typedef std::forward_list<Typedefs> TypedefsList;

        private:
            TypedefProcessor<T, I> typedefProcessor;

        private:
            Names2Nodes* findTypedefs(const rapidxml::xml_node<>* node) {
                Names2Nodes* names2nodes = new Names2Nodes;
                if (!names2nodes) Rt::error(0x97EC5DD5);

                for (auto child = node->first_node("typedef"); child; child = child->next_sibling("typedef"))
                    for (auto attr = child->first_attribute("name"); attr; attr = attr->next_attribute("name")) {
                        auto key = std::string(attr->value());
                        if (names2nodes->find(key) == names2nodes->end())
                            names2nodes->insert(std::pair<std::string, rapidxml::xml_node<>*>(key, XML::findNestedElement(child->first_node())));
                        else
                            Rt::error(0x9D47565A);
                    }

                return names2nodes;
            }

            void findTagsRecursively(const rapidxml::xml_node<>* node, std::set<std::string>& tags) {
                if (node->type() == rapidxml::node_element) {
                    tags.insert(std::string(node->name()));
                    for (auto child = node->first_node(); child; child = child->next_sibling())
                        findTagsRecursively(child, tags);
                }
            }

            Graph* constructDependencies(const Names2Nodes* names2nodes) {
                Graph* dependencies = new Graph;
                if (!dependencies) Rt::error(0x31AE2B6E);

                std::map<std::string, typename Graph::vertex_descriptor> tmp;

                for (auto& name2node : *names2nodes) {
                    VertexProperties v;

                    v.name = name2node.first;
                    v.node = name2node.second;

                    tmp[name2node.first] = boost::add_vertex(v, *dependencies);
                }

                for (auto& name2node : *names2nodes) {
                    std::set<std::string> tags;

                    findTagsRecursively(name2node.second, tags);

                    for (auto& tag : tags) {
                        auto tagName2node = names2nodes->find(tag);
                        if (tagName2node != names2nodes->end()) {
                            printf("%s -> %s\n", name2node.first.c_str(), (*tagName2node).first.c_str());
                            boost::add_edge(tmp[name2node.first], tmp[(*tagName2node).first], *dependencies);
                        }
                    }
                }

#if 0
                auto ids = boost::get(&VertexProperties::name, *dependencies);
                auto nodes = boost::get(&VertexProperties::node, *dependencies);

                typename boost::graph_traits<Graph>::edge_iterator ei, edge_end;
                for (boost::tie(ei, edge_end) = boost::d1(*dependencies); ei != edge_end; ++ei)
                    printf("eee\n");

                typename boost::graph_traits<Graph>::vertex_iterator vi, vertex_end;
                for (boost::tie(vi, vertex_end) = boost::vertices(*dependencies); vi != vertex_end; ++vi)
                    printf("vertex %s %s\n", ids[*vi].c_str(), nodes[*vi]->name());
#endif

                return dependencies;
            }

            template <typename OutputIterator>
            struct TopologicalSortVisitor : public boost::dfs_visitor<> {
                OutputIterator iter;

                TopologicalSortVisitor(OutputIterator _iter) : iter(_iter) {}

                template <typename Edge, typename Graph>
                void back_edge(const Edge&, Graph& graph) {
                    Rt::error(0x0D80B470);
#if 0
                    auto file = new std::ofstream("/tmp/graph");
                    if (file)
                    {
                        boost::write_graphviz(*file, graph);
                        delete file;
                    }
#endif
                }

                template <typename Vertex, typename Graph> 
                void finish_vertex(const Vertex& v, Graph& g) {
                    *iter++ = v;
                }
            };

            template <typename OutputIterator>
            void topologicalSort(const Graph* g, OutputIterator result) {
                boost::depth_first_search(*g, boost::bgl_named_params<int, boost::buffer_param_t>(0).visitor(TopologicalSortVisitor<OutputIterator>(result)));
            }

            Typedefs* createTypes(const Graph* dependencies,
                                  const Names2Nodes* names2nodes,
                                  const TypedefsList* inheritedTypedefsList)
            {
                Typedefs* typedefs = new Typedefs;
                if (!typedefs) Rt::error(0xCC983AA7);

                std::deque<typename boost::graph_traits<Graph>::vertex_descriptor> verticesInTopologicalOrder;
                topologicalSort(dependencies, std::back_inserter(verticesInTopologicalOrder));

                auto typedefsList = *inheritedTypedefsList;
                typedefsList.push_front(Typedefs());

                auto nodes = boost::get(&VertexProperties::node, *dependencies);

                for (auto vertexDescriptor : verticesInTopologicalOrder) {
                    auto node = nodes[vertexDescriptor];

                    auto type = parseRecursively(node, (void*)&typedefsList);
                    if (!type) Rt::error(0x28D8091D);

                    for (auto& name2node : *names2nodes) {
                        if (name2node.second == node)
                            typedefsList.front()[name2node.first] = type;
                    }
                }

                *typedefs = typedefsList.front();

                return typedefs;
            }

            Typedefs* getTypedefs(const rapidxml::xml_node<>* node, const TypedefsList* inheritedTypedefsList) {
                std::unique_ptr<Names2Nodes> names2nodes(findTypedefs(node));
                std::unique_ptr<Graph> dependencies(constructDependencies(names2nodes.get()));
                return createTypes(dependencies.get(), names2nodes.get(), inheritedTypedefsList);
            }

            Trait<T, I>* matchTypedefs(rapidxml::xml_node<>* node, const TypedefsList* typedefsList) {
                Trait<T, I>* type = 0;

                for (auto& typedefs : *typedefsList)
                    for (auto& _typedef : typedefs)
                        if (!strcmp(_typedef.first.c_str(), node->name()))
                            type = typedefProcessor.process(node, (void*)_typedef.second, [&](rapidxml::xml_node<>* node, void* data) -> void* { return this->parseRecursively(node, data); });

                return type;
            }

            Trait<T, I>* parseRecursively(rapidxml::xml_node<>* node, void* data) {
                std::unique_ptr<TypedefsList> typedefsList(new TypedefsList);
                if (!typedefsList.get()) Rt::error(0xB475244C);

                auto inheritedTypedefsList = (const std::forward_list<Typedefs>*)data;
                *(typedefsList.get()) = *inheritedTypedefsList;
                typedefsList.get()->push_front(*getTypedefs(node, inheritedTypedefsList));

                auto type = XML::Parser<Trait<T, I>>::parseRecursively(node, typedefsList.get());
                if (type) return type;

                return matchTypedefs(node, typedefsList.get());
            }

        public:
            XMLLoader() {
                this->elementProcessors[string("atom")] = (XML::ElementProcessor<Trait<T, I>>*)(new AtomProcessor<T, I>());
                if (!this->elementProcessors[string("atom")]) Rt::error(0x2C24D393);

                this->elementProcessors[string("struct")] = (XML::ElementProcessor<Trait<T, I>>*)(new StructProcessor<T, I>());
                if (!this->elementProcessors[string("struct")]) Rt::error(0x7FBDF2D0);

                this->elementProcessors[string("matrix")] = (XML::ElementProcessor<Trait<T, I>>*)(new MatrixProcessor<T, I>());
                if (!this->elementProcessors[string("matrix")]) Rt::error(0x20E1947D);
            }

            virtual Trait<T, I>* parse(rapidxml::xml_node<>* node) {
                std::unique_ptr<TypedefsList> typedefsList(new TypedefsList);
                if (!typedefsList.get()) Rt::error(0xB475244C);
                return parseRecursively(node, typedefsList.get());
            }
        };
    }
}

#endif
