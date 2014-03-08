template <typename T>
void Rt::printList(std::list<T> l, const char* format, const char* separator) {
    auto iter = l.begin();
    for (T i = 0; i < l.size(); i++) {
        printf(format, *iter);
        if (i != l.size() - 1) printf("%s", separator);
        iter++;
    }
}
