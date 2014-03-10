#include <GLCPP/GL.h>

GL::SamplingState::SamplingState() : mask(0) {}

GL::SamplingState::SamplingState(Wrap s, Wrap t, Wrap r,
                                 Filter::Min min, Filter::Mag mag)
    : mask(0)
{}

bool GL::SamplingState::isParameterSet(Parameter param) const {
    return ((mask & (unsigned int)param) ? true : false);
};

void GL::SamplingState::getWraps(Wrap& s, Wrap& t, Wrap& r) const {
    s = wrap.s;
    t = wrap.t;
    r = wrap.r;
}

void GL::SamplingState::setWraps(Wrap s, Wrap t, Wrap r) {
    wrap.s = s;
    wrap.t = t;
    wrap.r = r;

    mask |= ((unsigned int)Parameter::WrapS |
             (unsigned int)Parameter::WrapT |
             (unsigned int)Parameter::WrapR);
}

GL::SamplingState::Wrap GL::SamplingState::getWrapS() const {
    return wrap.s;
}

void GL::SamplingState::setWrapS(Wrap s) {
    wrap.s = s;
    mask |= (unsigned int)Parameter::WrapS;
}

GL::SamplingState::Wrap GL::SamplingState::getWrapT() const {
    return wrap.t;
}

void GL::SamplingState::setWrapT(Wrap t) {
    wrap.t = t;
    mask |= (unsigned int)Parameter::WrapT;
}

GL::SamplingState::Wrap GL::SamplingState::getWrapR() const {
    return wrap.r;
}

void GL::SamplingState::setWrapR(Wrap r) {
    wrap.r = r;
    mask |= (unsigned int)Parameter::WrapR;
}

void GL::SamplingState::getFilters(Filter::Min& min, Filter::Mag& mag) const {
    min = filter.min;
    mag = filter.mag;
}

void GL::SamplingState::setFilters(Filter::Min min, Filter::Mag mag) {
    filter.min = min;
    filter.mag = mag;

    mask |= ((unsigned int)Parameter::MinFilter |
             (unsigned int)Parameter::MagFilter);
}
