#ifndef header_CEC6D9577F6F
#define header_CEC6D9577F6F

namespace GL
{
    class Query : public Object
    {
    private:
        bool enabled;
        GLenum target;

    public:
        Query();
        Query(bool enabled, GLenum target);
        virtual ~Query();

        bool isEnabled() const;
        void setEnabled(bool);

        GLenum getTarget() const;
        void setTarget(GLenum);

        void begin();
        void end();

        void getResult(GLuint&) const;
        void getResult(GLint&) const;
    };
}

#endif
