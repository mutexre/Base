template <typename T>
int Rt::Branching::Test<T>::testComputePath(T address, std::list<T> branchingFactors, std::list<T> expectedResult)
{
    RtLog("Path of %u in ", address);
    Rt::printList(branchingFactors, "%u", " x ");
//    RtLog("\n");

    Branching::Default<T> b(branchingFactors);
    auto result = true;
    auto path = b.computePath(address);

    if (path.size() != expectedResult.size())
        result = false;
    else {
        auto iter = path.begin();
        auto jter = expectedResult.begin();

        while (iter != path.end()) {
            if (*iter != *jter) {
                result = false;
                break;
            }

            iter++;
            jter++;
        }
    }

    RtLog(" => ");
    printList(path, "%u", ", ");
    RtLog("\n");

#if 0
    if (!result) {
        printList(path, "%u", ", ");
        RtLog(" is not equal to expected ");
        printList(expectedResult, "%u", ", ");
        RtLog("\n");

        return 1;
    }
#endif

    return 0;
}

template <typename T>
int Rt::Branching::Test<T>::test()
{
    T maxSize = 3;
    T maxFactor = 2;
    T numberOfPermutationsOfSmallerSize = 0;

    for (T size = 0; size <= maxSize; size++) {
        T numberOfPermutations = 1;
        for (auto i = 0; i < size; i++)
            numberOfPermutations *= maxFactor;

        for (auto permutationIndex = numberOfPermutationsOfSmallerSize;
             permutationIndex < numberOfPermutations;
             permutationIndex++)
        {
            std::list<T> branchingFactors;

            if (size > 0) {
                auto maxFactorPower = numberOfPermutations / maxFactor;
                auto tmp = permutationIndex;

                do {
                    branchingFactors.push_back(tmp / maxFactorPower + 1);
                    tmp = tmp % maxFactorPower;
                    maxFactorPower /= maxFactor;
                }
                while (tmp > 0);
            }

            T numberOfAddresses = std::accumulate(branchingFactors.begin(), branchingFactors.end(), 1, std::multiplies<T>());
            for (T address = 0; address < numberOfAddresses; address++)
                testComputePath(address, branchingFactors, std::list<T>());
        }

        numberOfPermutationsOfSmallerSize += numberOfPermutations;
    }

    return 0;
}
