#ifndef header_9821D3765538
#define header_9821D3765538

#include <memory>
#include <Runtime/Runtime.h>
#include <Math/Math.h>
#include <GLCPP/GL.h>
#include <React/React.h>
#include <Color/Color.h>

namespace SG
{
    class Program;
    class Buffer;
    class Data;
    class DataBinding;
    class BindData;
    class DrawCall;
    class Piece;
    class Material;
    class UniformBlockBinding;
    class Segment;
    class Object;
    template <typename T> class Order;
    template <typename T> class Group;
    class Light;
    class View;

    using ObjectPtr = React::ScalarPtr<std::shared_ptr<Object>>;
    using Objects = Group<ObjectPtr>;
    using Lights = Group<React::ScalarPtr<std::shared_ptr<Light>>>;
    using ObjectsOrder = Order<ObjectPtr>;
}

//#include <SceneGraph/Scene.h>
#include <SceneGraph/Program.h>
#include <SceneGraph/Buffer.h>
#include <SceneGraph/Data.h>
#include <SceneGraph/DataBinding.h>
#include <SceneGraph/BindData.h>
#include <SceneGraph/DrawCall.h>
#include <SceneGraph/Piece.h>
#include <SceneGraph/Material.h>
#include <SceneGraph/UniformBlockBinding.h>
#include <SceneGraph/Segment.h>
#include <SceneGraph/Object.h>
#include <SceneGraph/Order.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/Light.h>
#include <SceneGraph/View.h>
#include <SceneGraph/StandardTransforms.h>
#include <SceneGraph/Implementation.h>
#include <SceneGraph/AttributeArray.h>
#include <SceneGraph/PrimitivesStream.h>
#include <SceneGraph/AttributesMapping.h>
#include <SceneGraph/AttributesExpander.h>
#include <SceneGraph/Topological/Data.h>
#include <SceneGraph/Topological/DefaultPrimitivesExtractor.h>
#include <SceneGraph/Topological/ConvexTriangulation.h>
#include <SceneGraph/Topological/Cpu2GpuProjection.h>
#include <SceneGraph/Topological/Object.h>
#include <SceneGraph/Topological/GatherSegments.h>

#endif
