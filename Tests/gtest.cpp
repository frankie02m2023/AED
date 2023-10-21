//
// Created by lucas on 21/10/2023.
//
#include <gtest/gtest.h>
#include "../Source_files/student.h"
#include "../Source_files/class1.h"
#include "../Source_files/course.h"
#include "../Source_files/interface.h"


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

TEST(Data_readers,read_data_classes){
    cout << "Testing read_data_classes " << endl;
    class1 test1 {"1LEIC01",{"Tuesday",10.5, 1.5 }, {"Monday", 10.5, 1.5} };
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    course c = testi.courses[0];
    class1 cl = c.get_classes()[0];
    EXPECT_EQ(test1.get_class_name(), cl.get_class_name());
    EXPECT_EQ(test1.get_T_class().duration, cl.get_T_class().duration);
    EXPECT_EQ(test1.get_T_class().hour, cl.get_T_class().hour);
    EXPECT_EQ(test1.get_T_class().week_day, cl.get_T_class().week_day);
    EXPECT_EQ(test1.get_TP_class().week_day, cl.get_TP_class().week_day);
    EXPECT_EQ(test1.get_TP_class().hour, cl.get_TP_class().hour);
    EXPECT_EQ(test1.get_TP_class().duration, cl.get_TP_class().duration);
}

TEST(Data_readers, read_data_students_classes){
    cout << "Testing read_data_students_classes" << endl;
    student test1 {"Francisca", "202020897"};
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();
    student s = testi.courses[0].get_classes()[0].get_students().front();
    EXPECT_EQ(s.get_number(), test1.get_number());
    EXPECT_EQ(s.get_name(), test1.get_name());
}