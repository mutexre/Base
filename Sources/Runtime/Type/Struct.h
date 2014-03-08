#ifndef header_344766C26999
#define header_344766C26999

namespace Rt
{
    namespace Type
    {
        template <typename T = u4, typename I = u4>
        class Struct : public Trait<T, I>
        {
        public:
            struct Member {
                I index;
                T offset;
                Member() {}
                Member(I index, T offset) {
                    this->index = index;
                    this->offset = offset;
                }
            };

        private:
            std::map<Trait<T, I>*, Member> members;

        public:
            Struct() {
                this->kind = Trait<T, I>::Kind::Struct;
            }

            virtual ~Struct() {
                for (auto& t : members) delete t.first;
            }

            Struct(I numberOfMembers, ...) {
                va_list vaList;
                I index = 0;
                T offset = 0;

                va_start(vaList, numberOfMembers);
                for (auto i = 0; i < numberOfMembers; i++) {
                    auto member = static_cast<Trait<T, I>*>(va_arg(vaList, void*));
                    member->setParent(Option<Trait<T, I>*>(this));
                    members.insert(std::pair<Trait<T, I>*, Member>(member, Member(index++, offset)));
                    offset += member->getRoundedSize();
                }
                va_end(vaList);

                this->kind = Trait<T, I>::Kind::Struct;
            }

            Struct(std::list<Trait<T, I>*> members) {
                I index = 0;
                T offset = 0;

                for (auto& m : members) {
                    m->setParent(Option<Trait<T, I>*>(this));
                    this->members.insert(std::pair<Trait<T, I>*, Member>(m, Member(index++, offset)));
                    offset += m->getRoundedSize();
                }

                this->kind = Trait<T, I>::Kind::Struct;
            }

            virtual void traverseTree(std::function<void (Trait<T, I>*)> f) {
                for (auto& m : members) { /*printf("%s.%s\n", this->getName().value.c_str(), m.first->getName().value.c_str());*/ m.first->traverseTree(f); }
                Trait<T, I>::traverseTree(f);
            }

            virtual Trait<T, I>* at(const char* pathComponent) {
                for (auto& m : members) {
                    auto name = m.first->getName();
                    if (name.defined && !strcmp(pathComponent, name.value.c_str()))
                        return m.first;
                }
                return 0;
            }

            virtual T getSize() {
                T size = 0;
                for (auto m : members) size += m.first->getRoundedSize();
                return size;
            }

            std::map<Trait<T, I>*, Member>& getMembers() {
                return members;
            }

            virtual std::string toString() const {
                std::string str;

                auto iter = members.begin();
                while (iter != members.end()) {
                    if (iter == members.begin()) str += std::string("(");

                    str += (*iter).first->toString();
                    iter++;

                    str += std::string(iter != members.end() ? ", " : ")");
                }

                return str;
            }

            virtual Trait<T, I>* copyRecursively() {
                auto retval = new Struct();
                if (!retval) Rt::error(0x3CA38DA8);

                for (auto& m : members) {
                    auto copy = m.first->copyRecursively();
                    if (!copy) Rt::error(0xE6D1793A);
                    retval->members[copy] = m.second;
                }

                this->copyAttributesTo(retval);

                return retval;
            }
        };
    }
}

#endif
