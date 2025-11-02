#include <cassert>
#include <iostream>
#include <string>
#include "MyVector.hpp"

int main() {
    {
        MyVector<int> v;
        assert(v.empty());
        assert(v.size() == 0);
        std::cout << "test1 ok\n";
    }

    {
        MyVector<int> v(5);
        assert(v.size() == 5);
        for (size_t i = 0; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "test2 ok\n";
    }

    {
        MyVector<int> v(4, 7);
        assert(v.size() == 4);
        for (size_t i = 0; i < v.size(); ++i) {
            assert(v[i] == 7);
        }
        std::cout << "test3 ok\n";
    }

    {
        MyVector<int> v;
        for (int i = 1; i <= 10; ++i) {
            v.push_back(i);
        }
        assert(v.size() == 10);
        assert(v[0] == 1);
        assert(v[9] == 10);
        std::cout << "test4 ok\n";
    }

    {
        MyVector<int> v(3, 5);
        bool threw = false;
        try { (void)v.at(3); }
        catch (const std::out_of_range&) {
            threw = true;
        }
        assert(threw);
        std::cout << "test5 ok\n";
    }

    {
        MyVector<int> v(3, 1);
        v.resize(6, 9);
        assert(v.size() == 6);
        assert(v[0] == 1 && v[2] == 1);
        assert(v[3] == 9 && v[5] == 9);
        v.resize(2);
        assert(v.size() == 2);
        assert(v[0] == 1 && v[1] == 1);
        std::cout << "test6 ok\n";
    }

    {
        MyVector<int> v;
        v.reserve(64);
        assert(v.capacity() >= 64);
        std::cout << "test7 ok\n";
    }

    {
        MyVector<int> a;
        for (int i = 0; i < 5; ++i) {
            a.push_back(i);
        }

        MyVector<int> b(std::move(a));
        assert(b.size() == 5);
        assert(a.size() == 0);

        MyVector<int> c(2, 7);
        c = std::move(b);
        assert(c.size() == 5);
        assert(b.size() == 0);
        std::cout << "test8 ok\n";
    }

    {
        MyVector<std::string> vs;
        vs.emplace_back(3, 'A');
        vs.emplace_back("yo");
        assert(vs.size() == 2);
        assert(vs[0] == "AAA");
        assert(vs[1] == "yo");
        std::cout << "test9 ok\n";
    }

    std::cout << "ALL TESTS PASSED\n";
}
