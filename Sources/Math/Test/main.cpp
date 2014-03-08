#include <Math/Math.h>
/*
void printId(Math::Geometry::Internal::Hypercube::Topology<Rt::u1, Rt::u4>::Id id, Rt::u1 dim) {
    printf("[");
    Rt::printBits(id.mask, dim);
    printf(" ");
    Rt::printBits(id.value, dim);
    printf("]\n");
}

void testInternalHypercubeTopology(Rt::u1 min, Rt::u1 max) {
    for (Rt::u1 dim = min; dim <= max; dim++)
    {
        printf("%u\n", dim);
        for (Rt::u1 i = 0; i <= dim; i++)
        {
            printf("   %u:%u\n", i, Math::Geometry::Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getCount(dim, i));

            auto elements = Math::Geometry::Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getElements(dim, i);
            for (auto& id : elements)
            {
                printf("      ");
                printId(id, dim);

                for (Rt::u1 j = 0; j <= dim; j++)
                {
                    printf("         %u:%u\n", j, Math::Geometry::Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getCount(dim, i, j));

                    auto elements2 = Math::Geometry::Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getElements(dim, id, j);
                    for (auto& id2 : elements2) {
                        printf("            ");
                        printId(id2, dim);
                    }
                }
            }
        }
        printf("\n");
    }
}

void testHypercubeTopology(Rt::u1 min, Rt::u1 max) {
    for (Rt::u1 dim = min; dim <= max; dim++)
    {
//        Math::Geometry::Hypercube::Topology cube(dim);
        Math::Geometry::Hypercube::Model<float> cube(dim);
        printf("%u\n", dim);
        for (Rt::u1 dim0 = 0; dim0 <= dim; dim0++)
        {
            printf("   %u:%u\n", dim0, cube.topology->getCount(dim0));
            for (Rt::u4 id0 = 0; id0 < cube.topology->getCount(dim0); id0++)
            {
                printf("      %u:\n", id0);
                for (Rt::u1 dim1 = 0; dim1 <= dim; dim1++)
                {
                    printf("         %u:%u -> ", dim1, cube.topology->getCount(id0, dim0, dim1));
                    auto elements = cube.topology->getElements(id0, dim0, dim1);
                    for (auto& id1 : elements) printf("%u ", id1);
                    printf("\n");
                }
            }
        }
        printf("\n");
    }
}
*/

void testScalar() {
    Math::Matrix<float> s[] = { Math::makeScalar<float>(39.0f), Math::makeScalar<float>(97.0f) };
    s[0].print(); printf("\n");
    s[1].print(); printf("\n");

    auto r = s[0] * s[1];
    printf("*\n"); r.print(); printf("\n");

    r = s[1];
    r *= s[0];
    printf("*=\n"); r.print(); printf("\n");

    r = s[0] + s[1];
    printf("+\n"); r.print(); printf("\n");

    r = s[1];
    r += s[0];
    printf("+=\n"); r.print(); printf("\n");

    r = s[0] - s[1];
    printf("-\n"); r.print(); printf("\n");

    r = s[0];
    r -= s[1];
    printf("-=\n"); r.print(); printf("\n");

    r = s[0];
    r.transpose();
    printf("transpose\n"); r.print(); printf("\n");

    r = s[0];
    r.inverse();
    printf("inverse\n"); r.print(); printf("\n");
}

void testVector() {
    Math::Matrix<float> v[] = { Math::makeVector<float>(23.0f, 77.0f), Math::makeVector<float>(26.0f, 65.0f) };
    v[0].print(); printf("\n");
    v[1].print(); printf("\n");

    auto r = v[0] * v[1];
    printf("*\n"); r.print(); printf("\n");

    r = v[1];
    r *= v[0];
    printf("*=\n"); r.print(); printf("\n");

    r = v[0] + v[1];
    printf("+\n"); r.print(); printf("\n");

    r = v[1];
    r += v[0];
    printf("+=\n"); r.print(); printf("\n");

    r = v[0] - v[1];
    printf("-\n"); r.print(); printf("\n");

    r = v[0];
    r -= v[1];
    printf("-=\n"); r.print(); printf("\n");

    r = v[0];
    r.transpose();
    printf("transpose\n"); r.print(); printf("\n");

    r = v[0];
    r.inverse();
    printf("inverse\n"); r.print(); printf("\n");
}

void testMatrix2() {
    std::vector<float, Rt::AlignedAllocator<float, 32>> data2[2];
    data2[0].push_back(69.0f);
    data2[0].push_back(70.0f);
    data2[0].push_back(97.0f);
    data2[0].push_back(5.0f);

    data2[1].push_back(33.0f);
    data2[1].push_back(85.0f);
    data2[1].push_back(20.0f);
    data2[1].push_back(93.0f);

    Math::Matrix<float> m2[] = {
        Math::makeMatrix<float>(2, data2[0]),
        Math::makeMatrix<float>(2, data2[1])
    };

    m2[0].print(); printf("\n");
    m2[1].print(); printf("\n");

    auto r = m2[0] * m2[1];
    printf("*\n"); r.print(); printf("\n");

    r = m2[1] * m2[0];
    printf("*\n"); r.print(); printf("\n");

    r = m2[1];
    r *= m2[0];
    printf("*=\n"); r.print(); printf("\n");

    r = m2[0] + m2[1];
    printf("+\n"); r.print(); printf("\n");

    r = m2[0];
    r.transpose();
    printf("transpose\n"); r.print(); printf("\n");

    r = m2[0];
    r.inverse();
    printf("inverse\n"); r.print(); printf("\n");

    r = m2[0];
    r.inverse();
    r *= m2[0];
    //Math::Matrix<float>::inverse(m2[0]).get();
    printf("chech inverse\n"); r.print(); printf("\n");
}

void testMatrix3() {
    std::vector<float, Rt::AlignedAllocator<float, 32>> data3[2];
    data3[0].push_back(34.0f);
    data3[0].push_back(63.0f);
    data3[0].push_back(87.0f);
    data3[0].push_back(69.0f);
    data3[0].push_back(96.0f);
    data3[0].push_back(2.0f);
    data3[0].push_back(91.0f);
    data3[0].push_back(65.0f);
    data3[0].push_back(50.0f);

    data3[1].push_back(42.0f);
    data3[1].push_back(9.0f);
    data3[1].push_back(25.0f);
    data3[1].push_back(76.0f);
    data3[1].push_back(11.0f);
    data3[1].push_back(59.0f);
    data3[1].push_back(66.0f);
    data3[1].push_back(85.0f);
    data3[1].push_back(35.0f);

    Math::Matrix<float> m3[] = {
        Math::makeMatrix<float>(3, data3[0]),
        Math::makeMatrix<float>(3, data3[1])
    };

    m3[0].print(); printf("\n");
    m3[1].print(); printf("\n");

    auto r = m3[0] * m3[1];
    printf("*\n"); r.print(); printf("\n");

    r = m3[1] * m3[0];
    printf("*\n"); r.print(); printf("\n");

    r = m3[1];
    r *= m3[0];
    printf("*=\n"); r.print(); printf("\n");

    r = m3[0] + m3[1];
    printf("+\n"); r.print(); printf("\n");

    r = m3[0];
    r.transpose();
    printf("transpose\n"); r.print(); printf("\n");

    r = m3[0];
    auto det = r.calcDet();
    if (det.defined) printf("det = %f\n", det.get());

    r = m3[0];
    if (r.inverse()) {
        printf("inverse\n"); r.print(); printf("\n");
    }
    else
        printf("non-inversible\n");

    r = m3[0];
    if (r.inverse()) {
        r *= m3[0];
        //Math::Matrix<float>::inverse(m2[0]).get();
        printf("chech inverse\n"); r.print(); printf("\n");
    }
    else
        printf("non-inversible\n");

}

void testMatrix4() {
    std::vector<float, Rt::AlignedAllocator<float, 32>> data4[2];
    data4[0].push_back(1.0f);
    data4[0].push_back(90.0f);
    data4[0].push_back(13.0f);
    data4[0].push_back(75.0f);

    data4[0].push_back(9.0f);
    data4[0].push_back(86.0f);
    data4[0].push_back(38.0f);
    data4[0].push_back(17.0f);

    data4[0].push_back(12.0f);
    data4[0].push_back(99.0f);
    data4[0].push_back(3.0f);
    data4[0].push_back(98.0f);

    data4[0].push_back(67.0f);
    data4[0].push_back(69.0f);
    data4[0].push_back(15.0f);
    data4[0].push_back(37.0f);

    data4[1].push_back(99.0f);
    data4[1].push_back(31.0f);
    data4[1].push_back(68.0f);
    data4[1].push_back(64.0f);

    data4[1].push_back(25.0f);
    data4[1].push_back(97.0f);
    data4[1].push_back(100.0f);
    data4[1].push_back(48.0f);

    data4[1].push_back(71.0f);
    data4[1].push_back(1.0f);
    data4[1].push_back(33.0f);
    data4[1].push_back(45.0f);

    data4[1].push_back(87.0f);
    data4[1].push_back(73.0f);
    data4[1].push_back(13.0f);
    data4[1].push_back(54.0f);

    Math::Matrix<float> m4[] = {
        Math::makeMatrix<float>(4, data4[0]),
        Math::makeMatrix<float>(4, data4[1])
    };

    m4[0].print(); printf("\n");
    m4[1].print(); printf("\n");

    auto r = m4[0] * m4[1];
    printf("*\n"); r.print(); printf("\n");

    r = m4[1] * m4[0];
    printf("*\n"); r.print(); printf("\n");

    r = m4[1];
    r *= m4[0];
    printf("*=\n"); r.print(); printf("\n");

    r = m4[0] + m4[1];
    printf("+\n"); r.print(); printf("\n");

    r = m4[0];
    r.transpose();
    printf("transpose\n"); r.print(); printf("\n");

    r = m4[0];
    auto det = r.calcDet();
    if (det.defined) printf("det = %f\n", det.get());

    r = m4[0];
    if (r.inverse()) {
        printf("inverse\n"); r.print(); printf("\n");
    }
    else
        printf("non-inversible\n");

    r = m4[0];
    if (r.inverse()) {
        r *= m4[0];
        //Math::Matrix<float>::inverse(m2[0]).get();
        printf("chech inverse\n"); r.print(); printf("\n");
    }
    else
        printf("non-inversible\n");

    r = m4[0];
    r.crop(3);
    printf("crop 3\n"); r.print(); printf("\n");

    r = m4[0];
    r.crop(2);
    printf("crop 2\n"); r.print(); printf("\n");

    r = m4[0];
    r.crop(1);
    printf("crop 1\n"); r.print(); printf("\n");

    r = m4[0];
    r.loadIdentity();
    printf("load identity\n"); r.print(); printf("\n");
}

void testMultidimMatrix() {
    testScalar();
    testVector();
    testMatrix2();
    testMatrix3();
    testMatrix4();
}

int main(int argc, const char** argv)
{
#if 0
//    testInternalHypercubeTopology(0, 8);
    testHypercubeTopology(3, 3);

    Math::Geometry::Hypercube::Model<float> cube(4);
    for (auto i = 0; i < cube.topology->getCount(0); i++) {
        for (auto j = 0; j < cube.dim; j++) printf("%3.0f ", cube.vertices[i * cube.dim + j]);
        printf("\n");
    }
#else
    testMultidimMatrix();
#endif

    return 0;
}
