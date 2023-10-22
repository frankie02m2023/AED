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

    EXPECT_EQ(testi.get_courses()[1], test1);
    EXPECT_EQ(testi.get_courses()[1].get_classes().size(), test1.get_classes().size());
    EXPECT_EQ(testi.get_courses()[testi.get_courses().size()-1], test2);
    EXPECT_EQ(testi.get_courses()[testi.get_courses().size()-1].get_classes().size(), test2.get_classes().size());
    EXPECT_NE(testi.get_courses()[2], test1);
}

TEST(Data_readers,read_data_classes){
    cout << "Testing read_data_classes " << endl;
    class1 test1 {"1LEIC01",{"Tuesday",10.5, 1.5 }, {"Monday", 10.5, 1.5} };
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    course c = testi.get_courses()[0];
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
    student s = testi.get_courses()[0].get_classes()[0].get_students().front();
    EXPECT_EQ(s.get_number(), test1.get_number());
    EXPECT_EQ(s.get_name(), test1.get_name());
}

TEST(Schedule_readers, get_class_schedule) {
    cout << "Testing get_class_schedule" << endl;
    set<pair<pair<schedule,string>,course>> expected_class_schedule;
    schedule schedule1("Monday",8.5,2);
    string class_type1 = "T";
    course course1("L.EIC002");
    expected_class_schedule.insert(make_pair(make_pair(schedule1,class_type1),course1));
    schedule schedule2("Monday",10.5,2);
    string class_type2 = "TP";
    course course2("L.EIC002");
    expected_class_schedule.insert(make_pair(make_pair(schedule2,class_type2),course2));
    schedule schedule3("Tuesday",9,1.5);
    string class_type3 = "TP";
    course course3("L.EIC001");
    expected_class_schedule.insert(make_pair(make_pair(schedule3,class_type3),course3));
    schedule schedule4("Tuesday",10.5,1.5);
    string class_type4 = "T";
    course course4("L.EIC001");
    expected_class_schedule.insert(make_pair(make_pair(schedule4,class_type4),course4));
    schedule schedule5("Wednesday",9.5,1);
    string class_type5 = "T";
    course course5("L.EIC003");
    expected_class_schedule.insert(make_pair(make_pair(schedule5,class_type5),course5));
    schedule schedule6("Wednesday",10.5,2);
    string class_type6 = "TP";
    course course6("L.EIC005");
    expected_class_schedule.insert(make_pair(make_pair(schedule6,class_type6),course6));
    schedule schedule7("Thursday",8,2);
    string class_type7 = "TP";
    course course7("L.EIC003");
    expected_class_schedule.insert(make_pair(make_pair(schedule7,class_type7),course7));
    schedule schedule8("Thursday",11,2);
    string class_type8 = "T";
    course course8("L.EIC004");
    expected_class_schedule.insert(make_pair(make_pair(schedule8,class_type8),course8));
    schedule schedule9("Friday",10,1);
    string class_type9 = "T";
    course course9("L.EIC003");
    expected_class_schedule.insert(make_pair(make_pair(schedule9,class_type9),course9));
    schedule schedule10("Friday",11,2);
    string class_type10 = "TP";
    course course10("L.EIC004");
    expected_class_schedule.insert(make_pair(make_pair(schedule10,class_type10),course10));
    schedule schedule11("Friday",8,2);
    string class_type11 = "T";
    course course11("L.EIC005");
    expected_class_schedule.insert(make_pair(make_pair(schedule11,class_type11),course11));
    interface testi;
    class1 test_class1("1LEIC05");
    set<pair<pair<schedule,string>,course>> class_schedule;
    class_schedule = testi.get_class_schedule(test_class1);
    EXPECT_EQ(expected_class_schedule.size(), class_schedule.size());
    EXPECT_EQ(expected_class_schedule,class_schedule);

}