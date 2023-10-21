//
// Created by lucas on 21/10/2023.
//
#include <gtest/gtest.h>
#include "student.h"
#include "class1.h"
#include "course.h"
#include "interface.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
// Expect two strings not to be equal.
EXPECT_STRNE("hello", "world");
// Expect equality.
EXPECT_EQ(7 * 6, 42);
}

TEST(Data_readers,read_data_classes_per_uc){
    cout << "Testing read_data_classes_per_uc " << endl;
    string ucname = "L.EIC002";
    course test1 {ucname};
    for(int i = 1; i < 10; i++){
        ostringstream aux;
        aux << "1LEIC0" << i;
        string classname = aux.str();
        class1 cl(classname);
        test1.add_class(cl);
    }
    for(int i = 10; i < 16; i++){
        ostringstream aux;
        aux << "1LEIC" << i;
        string classname = aux.str();
        class1 cl(classname);
        test1.add_class(cl);
    }

    string ucname2 = "UP001";
    course test2 {ucname2};
    for(int i = 1; i < 10; i++){
        ostringstream aux;
        aux << "1LEIC0" << i;
        string classname = aux.str();
        class1 cl(classname);
        test2.add_class(cl);
    }
    for(int i = 10; i < 13; i++){
        ostringstream aux;
        aux << "1LEIC" << i;
        string classname = aux.str();
        class1 cl(classname);
        test2.add_class(cl);
    }
    interface testi;
    testi.read_data_classes_per_uc();

    EXPECT_EQ(testi.courses[1], test1);
    EXPECT_EQ(testi.courses[1].get_classes().size(), test1.get_classes().size());
    EXPECT_EQ(testi.courses[testi.courses.size()-1], test2);
    EXPECT_EQ(testi.courses[testi.courses.size()-1].get_classes().size(), test2.get_classes().size());
    EXPECT_NE(testi.courses[2], test1);
}