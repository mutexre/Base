#ifndef header_7F4B656C6056
#define header_7F4B656C6056

namespace Rt
{
    class Object
    {
    public:
        static unsigned long long int allocsCount;
        static unsigned long long int deallocsCount;

    protected:
        std::string name;

    public:
        Object();
        virtual ~Object();

        const std::string& getName() const;
        void setName(const std::string& name);
    };
}

#endif
