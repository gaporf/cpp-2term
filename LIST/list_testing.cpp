#include <gtest/gtest.h>
#include "fault_injection.h"
#include "counted.h"

#include "list.h"

//typedef std::vector<counted> container;
//typedef std::vector<int> container_int;

typedef list<counted> container;
typedef list<int> container_int;

TEST(correctness, default_ctor) {
    faulty_run([] {
        counted::no_new_instances_guard g;
        container c;
        EXPECT_TRUE(c.empty());
    });
}

TEST(correctness, push_back_front_simple) {
    faulty_run([] {
        counted::no_new_instances_guard g;
        container c;
        c.push_back(3);
        EXPECT_FALSE(c.empty());
        EXPECT_EQ(3, c.front());
        EXPECT_EQ(3, c.back());
        c.push_back(4);
        EXPECT_EQ(3, c.front());
        EXPECT_EQ(4, c.back());
        c.push_back(5);
        EXPECT_EQ(3, c.front());
        EXPECT_EQ(5, c.back());
        c.push_front(2);
        EXPECT_EQ(2, c.front());
        EXPECT_EQ(5, c.back());
        c.push_front(1);
        EXPECT_EQ(1, c.front());
        EXPECT_EQ(5, c.back());
    });
}

TEST(correctness, push_back_big) {
    faulty_run([] {
        counted::no_new_instances_guard g;
        container c;
        for (size_t i = 0; i != 42; i++) {
            c.push_back(282);
        }
        EXPECT_FALSE(c.empty());
        EXPECT_EQ(282, c.back());
        EXPECT_EQ(282, c.front());
    });
}

TEST(correctness, push_front_big) {
    faulty_run([] {
        counted::no_new_instances_guard g;
        container c;
        for (size_t i = 0; i != 42; i++) {
            c.push_front(228);
        }
        EXPECT_FALSE(c.empty());
        EXPECT_EQ(228, c.back());
        EXPECT_EQ(228, c.front());
    });
}

TEST(correctness, pop_back_front) {
    faulty_run([] {
        counted::no_new_instances_guard g;
        container c;
        for (int i = 0; i != 42; i++) {
            c.push_back(i);
        }
        for (int i = 0; i != 42; i++) {
            EXPECT_EQ(i, c.front());
            c.pop_front();
        }
        EXPECT_TRUE(c.empty());
        for (int i = 0; i != 42; i++) {
            c.push_front(42);
        }
        for (int i = 0; i != 42; i++) {
            EXPECT_EQ(42, c.back());
            c.pop_back();
        }
        for (size_t i = 0; i != 42; i++) {
            c.push_back(i);
            c.push_front(i);
        }
        for (size_t i = 0; i != 84; i++) {
            c.pop_back();
        }
        EXPECT_TRUE(c.empty());
    });
}

TEST(correctness, clear) {
    faulty_run([] {
       counted::no_new_instances_guard g;
       container c;
       for (int i = 0; i != 5; i++) {
           c.push_back(i);
           c.push_front(i);
       }
       c.clear();
       EXPECT_TRUE(c.empty());
    });
}

TEST(correctness, copy) {
    faulty_run([] {
       counted::no_new_instances_guard g;
       container c;
       for (int i = 0; i != 5; i++) {
           c.push_front(i);
       }
       container d = c;
       EXPECT_EQ(4, c.front());
       for (int i = 0; i != 5; i++) {
           d.push_back(i);
       }
       EXPECT_EQ(4, d.back());
       EXPECT_EQ(0, c.back());
    });
}

TEST(correctness, assign) {
    faulty_run([] {
        counted::no_new_instances_guard g;
        container c;
        for (int i = 0; i != 5; i++) {
            c.push_front(282);
        }
        container d;
        for (int i = 0; i != 4; i++) {
            d.push_back(228);
        }
        EXPECT_EQ(228, d.back());
        d = c;
        EXPECT_EQ(282, d.back());
    });
}

TEST(correctness, insert) {
    faulty_run([] {
        counted::no_new_instances_guard g;
        container c;
        c.insert(c.begin(), 5);
        EXPECT_EQ(5, c.front());

    });
}