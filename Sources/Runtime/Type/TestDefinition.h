template <typename T, typename I> int Rt::Type::Test<T, I>::test()
{
#if 1
    auto x = new Atom<u4, u2>(3);
    x->setRounding(Option<u4>(4));
    auto y = new Atom<u4, u2>(4);
    auto s = new Struct<u4, u2>(2, x, y);
    auto w = new Atom<u4, u2>(11);
    auto t = new Atom<u4, u2>(12);
    auto s1 = new Struct<u4, u2>(2, w, t);
    auto s2 = new Struct<u4, u2>(2, s, s1);
    auto a = new Matrix<u4, u2>(s2, 15);
    auto s3 = new Struct<u4, u2>(1, a);
    Matrix<u4, u2> a1(s3, 10);
    printf("--- %u %u %u %u %u %u\n", x->getSize(), x->getRoundedSize(), y->getSize(), y->getRoundedSize(), s->getSize(), s->getRoundedSize());
    printf("--- %u %u %u %u\n", s1->getSize(), s1->getRoundedSize(), s2->getSize(), s2->getRoundedSize());
    printf("--- %u\n", s->getNumberOfOccurences());

    auto text =
        "<struct name=\"data\">\
            <matrix dim=\"100\" name=\"d0\" round=\"33\">\
                <struct name=\"vertex\">\
                    <struct name=\"coord\">\
                        <atom size=\"4\" name=\"x\"/>\
                        <atom size=\"4\" name=\"y\"/>\
                    </struct>\
                    \
                    <struct name=\"color\">\
                        <atom size=\"4\" name=\"r\"/>\
                        <atom size=\"4\" name=\"g\"/>\
                        <atom size=\"4\" name=\"b\"/>\
                        <atom size=\"4\" name=\"a\"/>\
                    </struct>\
                </struct>\
            </matrix>\
            \
            <struct name=\"d1\">\
                <matrix dim=\"200\" name=\"vertices\">\
                    <struct name=\"vertex\">\
                        <struct name=\"coord\">\
                            <atom size=\"4\" name=\"x\"/>\
                            <atom size=\"4\" name=\"y\"/>\
                        </struct>\
                        \
                        <struct name=\"color\">\
                            <atom size=\"4\" name=\"r\"/>\
                            <atom size=\"4\" name=\"g\"/>\
                            <atom size=\"4\" name=\"b\"/>\
                            <atom size=\"4\" name=\"a\"/>\
                        </struct>\
                    </struct>\
                </matrix>\
                \
                <matrix dim=\"300\" name=\"d1\">\
                    <struct name=\"edge\">\
                        <atom size=\"4\" name=\"v0\"/>\
                        <atom size=\"4\" name=\"v1\"/>\
                    </struct>\
                </matrix>\
            </struct>\
            \
            <struct name=\"d2\">\
                <matrix dim=\"260\" name=\"vertices\">\
                    <struct name=\"vertex\">\
                        <struct name=\"coord\">\
                            <atom size=\"4\" name=\"x\"/>\
                            <atom size=\"4\" name=\"y\"/>\
                        </struct>\
                        \
                        <struct name=\"color\">\
                            <atom size=\"4\" name=\"r\"/>\
                            <atom size=\"4\" name=\"g\"/>\
                            <atom size=\"4\" name=\"b\"/>\
                            <atom size=\"4\" name=\"a\"/>\
                        </struct>\
                    </struct>\
                </matrix>\
                \
                <matrix dim=\"370\" name=\"d2\">\
                    <struct name=\"triangle\">\
                        <atom size=\"4\" name=\"v0\"/>\
                        <atom size=\"4\" name=\"v1\"/>\
                        <atom size=\"4\" name=\"v2\"/>\
                    </struct>\
                </matrix>\
            </struct>\
        </struct>";

    auto textLen = strlen(text);
    std::unique_ptr<char> mutableText(new char[textLen + 1]);
	memcpy(mutableText.get(), text, textLen + 1);
    //strlcpy(mutableText.get(), text, textLen + 1);

    auto doc = new rapidxml::xml_document<>();
    doc->parse<0>(mutableText.get());
    XMLLoader<> loader;

//    Rt::Type::Trait type(doc);

    auto type = loader.parse(doc);
    printf("%s\n", type->toString().c_str());

    auto element = type->at("d1")->at("vertices")->at("vertex")->at("color");
    printf("%s\n", element->toString().c_str());

    auto so = element->getStrideAndOffset();
    if (so.defined) printf("stride and offset %u %u\n", so.value.first, so.value.second);

    element = type->at("d0");
    printf("%u\n", element->getRoundedSize());

    element = type->at("d1");
    printf("%u\n", element->getRoundedSize());

    element = type->at("d2");
    printf("%u\n", element->getRoundedSize());

    delete type;
    delete doc;

    auto text2 =
        "<matrix dim=\"100\" name=\"d0\">\
            <struct name=\"vertex\">\
                <struct name=\"coord\">\
                    <atom size=\"4\" name=\"x\"/>\
                    <atom size=\"4\" name=\"y\"/>\
                </struct>\
                \
                <struct name=\"color\">\
                    <atom size=\"4\" name=\"r\"/>\
                    <atom size=\"4\" name=\"g\"/>\
                    <atom size=\"4\" name=\"b\"/>\
                    <atom size=\"4\" name=\"a\"/>\
                </struct>\
            </struct>\
        </matrix>";

    textLen = strlen(text2);
    std::unique_ptr<char> mutableText2(new char[textLen + 1]);
	memcpy(mutableText2.get(), text2, textLen + 1);
    //strlcpy(mutableText2.get(), text2, textLen + 1);

    doc = new rapidxml::xml_document<>();
    doc->parse<0>(mutableText2.get());
    type = loader.parse(doc);

    element = type->at("vertex")->at("coord");
    printf("%s ", element->toString().c_str());

    so = element->getStrideAndOffset();
    if (so.defined) printf("stride and offset %u %u\n", so.value.first, so.value.second);
    else printf("none\n");

    element = type->at("vertex")->at("color");
    printf("%s ", element->toString().c_str());

    so = element->getStrideAndOffset();
    if (so.defined) printf("stride and offset %u %u\n", so.value.first, so.value.second);
    else printf("none\n");

    auto text3 =
        "<struct name=\"data\">\
            <typedef name=\"float\"><atom size=\"4\"/></typedef>\
            <typedef name=\"int\"><atom size=\"4\"/></typedef>\
            \
            <typedef name=\"coord\">\
                <struct>\
                    <float name=\"x\"/>\
                    <float name=\"y\"/>\
                </struct>\
            </typedef>\
            \
            <typedef name=\"color\">\
                <struct>\
                    <float name=\"r\"/>\
                    <float name=\"g\"/>\
                    <float name=\"b\"/>\
                    <float name=\"a\"/>\
                </struct>\
            </typedef>\
            \
            <typedef name=\"vertex\">\
                <struct>\
                    <coord name=\"coord\"/>\
                    <color name=\"color\"/>\
                </struct>\
            </typedef>\
            \
            <typedef name=\"edge\">\
                <struct>\
                    <int name=\"v0\"/>\
                    <int name=\"v1\"/>\
                </struct>\
            </typedef>\
            \
            <typedef name=\"triangle\">\
                <struct>\
                    <int name=\"v0\"/>\
                    <int name=\"v1\"/>\
                    <int name=\"v2\"/>\
                </struct>\
            </typedef>\
            \
            <struct name=\"d0\">\
                <matrix name=\"vertices\">\
                    <vertex name=\"vertex\"/>\
                </matrix>\
            </struct>\
            \
            <struct name=\"d1\">\
                <matrix name=\"vertices\">\
                    <vertex name=\"vertex\"/>\
                </matrix>\
                <matrix name=\"d1\">\
                    <edge name=\"edge\"/>\
                </matrix>\
            </struct>\
            \
            <struct name=\"d2\">\
                <matrix name=\"vertices\">\
                    <vertex name=\"vertex\"/>\
                </matrix>\
                <matrix name=\"d2\">\
                    <triangle name=\"triangle\"/>\
                </matrix>\
            </struct>\
        </struct>";

    textLen = strlen(text3);
    std::unique_ptr<char> mutableText3(new char[textLen + 1]);
	memcpy(mutableText3.get(), text3, textLen + 1);
    //strlcpy(mutableText3.get(), text3, textLen + 1);

    doc = new rapidxml::xml_document<>();
    doc->parse<0>(mutableText3.get());
    type = loader.parse(doc);

    printf("%s\n", type->toString().c_str());
#endif
    return 0;
}
