template <typename Data>
void Buffer<Data>::copyData(GL::Buffer::Target target, GLintptr offset)
{
    auto ptr = Buffer::map(target, Buffer::Access::Write);
    if (!ptr) Rt::error(0xFA3BDA5A);

    memcpy(((Rt::u1*)ptr) + offset, Data::vertices, sizeof(Data::vertices));
    memcpy(((Rt::u1*)ptr) + offset + sizeof(Data::vertices), Data::edges, sizeof(Data::edges));
    memcpy(((Rt::u1*)ptr) + offset + sizeof(Data::vertices) + sizeof(Data::edges), Data::triangles, sizeof(Data::triangles));

    Buffer::unmap(target);
}

template <typename Data>
Buffer<Data>::Buffer() : GL::Buffer() {
    Buffer::bind(Buffer::Target::CopyWrite, getID());
    Buffer::data(Buffer::Target::CopyWrite,
                 sizeof(Data::vertices) + sizeof(Data::edges) + sizeof(Data::triangles),
                 nullptr, GL_STATIC_DRAW);
    copyData(Buffer::Target::CopyWrite, 0);
}
