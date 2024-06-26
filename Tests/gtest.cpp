//
// Created by lucas on 21/10/2023.
//
#include <gtest/gtest.h>
#include <random>
#include "../Source_files/student.h"
#include "../Source_files/class1.h"
#include "../Source_files/course.h"
#include "../Source_files/interface.h"
#include "../Source_files/schedule.h"
#include "../Source_files/schedule_system.h"
#include "benchmark/benchmark.h"




// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
// Expect two strings not to be equal.
EXPECT_STRNE("hello", "world");
// Expect equality.
EXPECT_EQ(7 * 6, 42);
}

TEST(Data_readers,read_data_classes_per_uc){
    cout << "Testing read_data_classes_per_uc " << endl;

    //initialize the first course to test
    string ucname = "L.EIC002";
    course test1 {ucname};

    //fill the course with classes
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

    //initialize the seconde course for testing
    string ucname2 = "UP001";
    course test2 {ucname2};

    //fill the second course for testing
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

    //initialize test interface
    //only calling the read-data_classes_per_uc function (the function we want to test)
    interface testi;
    testi.read_data_classes_per_uc();

    //assertions
    EXPECT_EQ(testi.get_courses()[1], test1);
    EXPECT_EQ(testi.get_courses()[1].get_classes().size(), test1.get_classes().size());
    EXPECT_EQ(testi.get_courses()[testi.get_courses().size()-1], test2);
    EXPECT_EQ(testi.get_courses()[testi.get_courses().size()-1].get_classes().size(), test2.get_classes().size());
    EXPECT_NE(testi.get_courses()[2], test1);
}

TEST(Data_readers,read_data_classes){
    cout << "Testing read_data_classes " << endl;

    //initialize the expected class for testing
    class1 test1 {"1LEIC01",{"Tuesday",10.5, 1.5 },{},{"Monday", 10.5, 1.5} };

    //initialize the test interface
    //calling only the read_data_classes_per_uc function
    //and the read_data_classes function (the function we want to test)
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();

    //get class for testing
    course c = testi.get_courses()[0];
    class1 cl = c.get_classes()[0];

    //assertions
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

    //Initialize the expected student for testing;
    student test1 {"Francisca", "202020897"};

    //initialize test interface with all the functions
    //including read_data_students_classes
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();

    //initialize test student
    student s = testi.get_courses()[0].get_classes()[0].get_students().front();

    //assertions
    EXPECT_EQ(s.get_number(), test1.get_number());
    EXPECT_EQ(s.get_name(), test1.get_name());
}


TEST(Schedule_readers, get_class_schedule) {
    cout << "Testing get_class_schedule" << endl;
    set<pair<pair<schedule,string>,course>> expected_class_schedule;

    //fill the set with the expected schedules of each class per course
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

    schedule schedule12("Wednesday", 15.5, 1.5);
    string class_type12 = "TP";
    course course12("UP001");
    expected_class_schedule.insert(make_pair(make_pair(schedule12,class_type12),course12));

    //initialize test interface
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();

    //initialize testing class
    class1 test_class1("1LEIC05");

    //call the function we want to test
    set<pair<pair<schedule,string>,course>> class_schedule = testi.get_class_schedule(test_class1);

    //assertions
    EXPECT_EQ(expected_class_schedule.size(), class_schedule.size());
    EXPECT_EQ(expected_class_schedule,class_schedule);

}

TEST(Schedule_readers, get_class_students_for_course){
    cout << "Testing get_class_students_for_course" << endl;

    list<student> expected; //class 1LEIC01 course L.EIC001

    //initialize expected students
    student st1 {"Fracisca", "202020897"};
    student st2 {"Sofia", "202020642"};
    expected.push_back(st1);
    expected.push_back(st2);

    //initialize test interface
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();

    //get course for testing
    course course_test;
    for(course c: testi.get_courses()){
        if(c.get_course_name() == "L.EIC001"){
            course_test = c;
        }
    }

    //get class for testing
    class1 class_test = course_test.get_classes().front();
    for(class1 cl: course_test.get_classes()){
        if(cl.get_class_name() == "1LEIC01"){
                 class_test = cl;
        }
    }

    //call function we want to test
    list<student> student_test = testi.get_class_students_for_course(class_test, course_test);

    //Assertions
    EXPECT_EQ(expected.size(), student_test.size());
    EXPECT_EQ(expected, student_test);
}

TEST(Course_operations, edit_class) {
    cout << "Testing edit_class" << endl;

    //initialize the first expected class
    class1 expected = {"1LEIC01",{"Monday", 10, 2}};

    //initialize the testing course
    course course_test = {"test"};

    //initialize the testing class
    class1 class_test  {"1LEIC01"};

    //class_test modified by the function we want to test
    course_test.add_class(class_test);
    course_test.edit_class(class_test,{"Monday", 10, 2}, "T");
    course_test.get_class(class_test);

    //assertion
    EXPECT_EQ(expected, class_test);

    //more modifications
    course_test.edit_class(class_test,{"Monday", 12, 2}, "TP");
    course_test.edit_class(class_test,{"Tuesday", 10, 2}, "PL");

    //initialize second expected class
    class1 expected2 = {"1LEIC01",{"Monday", 10, 2}, {"Dont aplly",0,0 }, {"Monday", 12, 2}, {"Tuesday", 10, 2}};

    //assertion
    EXPECT_EQ(expected2, class_test);
}

TEST(Course_operations, has_student){
    //initialize the test values
    course test_course {"test"};
    class1 test_class{"test class"};
    student test_student1 {"Lucas", "123456789"};
    student test_student2 {"Francisco", "987654321"};
    test_class.add_students(test_student1);
    test_course.add_class(test_class);

    //call the function we want to tes
    bool test_value = test_course.has_student(test_student1);
    bool test_value2 = test_course.has_student(test_student2);

    //assertions
    EXPECT_EQ(test_value, true);
    EXPECT_EQ(test_value2, false);

}

TEST(Course_operations, get_student_class){
    //initialize the test values
    course test_course {"test"};
    class1 test_class{"test class"};
    class1 test_class2 {"Dummy"};
    student test_student1 {"Lucas", "123456789"};
    student test_student2 {"Francisco", "987654321"};
    test_class.add_students(test_student1);
    test_course.add_class(test_class);

    //call the function we want to test
    class1 test_values_1 = test_course.get_student_class(test_student1);
    class1 test_values_2 = test_course.get_student_class(test_student2);

    //assertions
    EXPECT_EQ(test_values_1, test_class);
    EXPECT_EQ(test_values_2, test_class2);
}

TEST(Schedule_readers,  get_all_students_in_aCourse){
    //initialize test students and course
    student test_1 {"Carolina", "202020302"};
    student test_2 {"Madalena", "202021492"};
    course test_course {"L.EIC001"};

    //initialize the test interface
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();

    //call the class we want to test
    set<student> students_test =  testi.get_all_students_in_aCourse(test_course);

    //get the values for testing
    auto it1 = students_test.find(test_1);
    auto it2 = students_test.find(test_2);

    //assertions
    EXPECT_NE(it1, students_test.end());
    EXPECT_NE(it2, students_test.end());
}

TEST(Schedule_readers, get_all_students_in_aYear){
    student test_1 {"Carolina", "202020302"};
    student test_2 {"Madalena", "202021492"};

    //initialize the test interface
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();

    //call the class we want to test
    set<student> students_test =  testi.get_all_students_in_aYear(1);

    //get the values for testing
    auto it1 = students_test.find(test_1);
    auto it2 = students_test.find(test_2);

    //assertions
    EXPECT_NE(it1, students_test.end());
    EXPECT_NE(it2, students_test.end());

}

TEST(Schedule_readers, number_of_students){
    //initialize the test interface
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();

    //initialize the expected values and auxiliary values
    course test_course {"L.EIC001"};
    class1 test_class{"1LEIC01"};
    int test_year = 1;
    size_t expected_class = 2;
    size_t expected_course = 32;


    //initialize the test values
    size_t n_cl = testi.number_of_students_in_aClass(test_class, test_course);
    size_t n_course = testi.number_of_students_in_anUC(test_course);
    size_t n_year = testi.number_of_students_in_aYear(test_year);

    //assertions
    EXPECT_EQ(expected_class, n_cl);
    EXPECT_EQ(expected_course, n_course);
    EXPECT_NE(n_year, 0);
}

TEST(Schedule_operations,overlapping_schedules){
    schedule schedule1("Monday",10.5,2.0);
    schedule schedule2("Friday",8.0,1.5);
    schedule schedule3("Monday",11.0,2.0);
    schedule schedule4("Monday",11.0,1.0);
    schedule schedule5("Friday",9.5,2.0);
    schedule schedule6("Dont Apply",0,0);
    EXPECT_FALSE(overlapping_schedule(schedule1,schedule2));
    EXPECT_TRUE(overlapping_schedule(schedule1,schedule3));
    EXPECT_TRUE(overlapping_schedule(schedule1,schedule4));
    EXPECT_TRUE(overlapping_schedule(schedule3,schedule4));
    EXPECT_FALSE(overlapping_schedule(schedule2,schedule5));
    EXPECT_FALSE(overlapping_schedule(schedule5,schedule6));
}

TEST(System_changes,check_class_balance){
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();
    course test_course1("L.EIC014");
    for(course c : testi.get_courses()){
        if(c == test_course1){
            test_course1 = c;
        }
    }
    class1 test_class1("2LEIC05");
    test_course1.get_class(test_class1);
    EXPECT_TRUE(test_course1.check_class_balance(test_class1));
}

TEST(System_changes,can_add_to_class){
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();

    course test_course1("L.EIC014");
    for(course c : testi.get_courses()){
        if(c == test_course1){
            test_course1 = c;
            break;
        }
    }
    class1 test_class1("2LEIC05");
    test_course1.get_class(test_class1);
    student test_student1("Gisela","202031607");
    test_course1.get_class(test_class1);
    EXPECT_FALSE(testi.can_add_to_class(test_course1,test_student1,test_class1));

    course test_course2("L.EIC002");
    for(course c : testi.get_courses()){
        if(c == test_course2){
            test_course2 = c;
            break;
        }
    }
    class1 test_class2("1LEIC03");
    test_course2.get_class(test_class2);
    student test_student2("Ludovico","202071557");
    EXPECT_FALSE(testi.can_add_to_class(test_course2,test_student2,test_class2));


    course test_course3("L.EIC002");
    for(course c : testi.get_courses()){
        if(c == test_course3){
            test_course3= c;
            break;
        }
    }
    class1 test_class3("1LEIC12");
    test_course3.get_class(test_class3);
    student test_student3("Manuel Santiago","202066712");
    EXPECT_FALSE(testi.can_add_to_class(test_course3,test_student3,test_class3));

    course test_course4("L.EIC002");
    for(course c : testi.get_courses()){
        if(c == test_course4){
            test_course4 = c;
            break;
        }
    }
    class1 test_class4("1LEIC06");
    test_course4.get_class(test_class4);
    student test_student4("Gisela","202031607");
    EXPECT_TRUE(testi.can_add_to_class(test_course4,test_student4,test_class4));

    course test_course5("L.EIC005");
    for(course c : testi.get_courses()){
        if(c == test_course5){
            test_course5 = c;
            break;
        }
    }
    class1 test_class5("1LEIC01");
    test_course5.get_class(test_class5);
    student test_student5("Manuel Santiago","202066712");
    EXPECT_TRUE(testi.can_add_to_class(test_course5,test_student5,test_class5));
}


TEST(System_changes,enroll_student_in_class){
    interface testi1;
    testi1.read_data_classes_per_uc();
    testi1.read_data_classes();
    testi1.read_data_students_classes();

    course test_course1("L.EIC005");
    class1 test_class1("1LEIC01");
    student test_student1("Manuel Santiago","202066712");
    string error_message = "";
    testi1.enroll_student_in_course(test_student1,test_course1,test_class1,error_message);
    for(course c : testi1.get_courses()){
        if(c == test_course1){
            test_course1 = c;
        }
    }
    test_course1.get_class(test_class1);
    EXPECT_EQ(error_message,"");
    EXPECT_EQ(test_class1.get_students().size(),3);
    EXPECT_TRUE(test_class1.student_in_class(test_student1));


    interface testi2;
    testi2.read_data_classes_per_uc();
    testi2.read_data_classes();
    testi2.read_data_students_classes();

    course test_course2("L.EIC002");
    class1 test_class2("1LEIC03");
    student test_student2("Ludovico","202071557");
    string error_message2 = "";
    testi2.enroll_student_in_course(test_student2,test_course2,test_class2,error_message2);

    for(course c : testi2.get_courses()){
        if(c == test_course2){
            test_course2 = c;
        }
    }

    EXPECT_EQ(error_message2,"Student could not be allocated to their desired class.");
    EXPECT_TRUE(test_course2.has_student(test_student2));

    interface testi3;
    testi3.read_data_classes_per_uc();
    testi3.read_data_classes();
    testi3.read_data_students_classes();

    course test_course3("L.EIC013");
    class1 test_class3("2LEIC01");
    student test_student3("Leonor","202020217");
    string error_message3 = "";
    testi3.enroll_student_in_course(test_student3,test_course3,test_class3,error_message3);

    for(course c : testi3.get_courses()){
        if(c == test_course3){
            test_course3 = c;
        }
    }

    EXPECT_EQ(error_message3,"Enrollment failed because student is already enrolled in the maximum number of courses possible.");
    EXPECT_FALSE(test_course3.has_student(test_student3));

}


TEST(System_changes,remove_student_from_course){
    interface testi1;
    testi1.read_data_classes_per_uc();
    testi1.read_data_classes();
    testi1.read_data_students_classes();

    course test_course1("L.EIC002");
    student test_student1("Ludovico","202071557");
    string error_message1 = "";
    bool test_bool = testi1.remove_student_from_course(test_student1,test_course1,error_message1);

    for(course c : testi1.get_courses()){
        if(c == test_course1){
            test_course1 = c;
        }
    }

    EXPECT_EQ(error_message1,"The student is not enrolled in course L.EIC002");
    EXPECT_FALSE(test_bool);


    interface testi2;
    testi2.read_data_classes_per_uc();
    testi2.read_data_classes();
    testi2.read_data_students_classes();

    course test_course2("L.EIC005");
    student test_student2("Leonor","202020217");
    string error_message2 = "";
    bool test_bool1 = testi2.remove_student_from_course(test_student2,test_course2,error_message2);

    for(course c : testi2.get_courses()){
        if(c == test_course2){
            test_course2 = c;
        }
    }

    EXPECT_TRUE(test_bool1);
    EXPECT_FALSE(test_course2.has_student(test_student2));

    interface testi3;
    testi3.read_data_classes_per_uc();
    testi3.read_data_classes();
    testi3.read_data_students_classes();

    course test_course3("L.EIC003");
    student test_student3("Rute","202028717");
    string error_message3 = "";
    bool test_bool2 = testi3.remove_student_from_course(test_student3,test_course3,error_message3);

    for(course c : testi3.get_courses()){
        if(c == test_course3){
            test_course3 = c;
        }
    }

    EXPECT_TRUE(test_bool2);
    EXPECT_FALSE(test_course3.has_student(test_student3));
}


TEST(System_changes,switch_student_classes){
    interface testi1;
    testi1.read_data_classes_per_uc();
    testi1.read_data_classes();
    testi1.read_data_students_classes();

    course test_course1("L.EIC014");
    class1 test_old_class1("2LEIC04");
    class1 test_new_class1("2LEIC05");
    student test_student1("Marcio","202043592");
    string error_message1 = "";
    bool bool1 = testi1.switch_student_classes(test_student1,test_course1,test_old_class1,test_new_class1,error_message1);

    for(course c : testi1.get_courses()){
        if(c == test_course1){
            test_course1 = c;
        }
    }

    test_course1.get_class(test_old_class1);
    test_course1.get_class(test_new_class1);

    EXPECT_EQ(error_message1,"The student could not be added to their desired class.");
    EXPECT_FALSE(bool1);
    EXPECT_TRUE(test_old_class1.student_in_class(test_student1));
    EXPECT_FALSE(test_new_class1.student_in_class(test_student1));


    interface testi2;
    testi2.read_data_classes_per_uc();
    testi2.read_data_classes();
    testi2.read_data_students_classes();

    course test_course2("L.EIC003");
    class1 test_old_class2("1LEIC04");
    class1 test_new_class2("1LEIC03");
    student test_student2("Rute","202028717");
    string error_message2 = "";
    bool bool2 = testi2.switch_student_classes(test_student2,test_course2,test_old_class2,test_new_class2,error_message2);

    for(course c : testi2.get_courses()){
        if(c == test_course2){
            test_course2 = c;
        }
    }

    test_course2.get_class(test_old_class2);
    test_course2.get_class(test_new_class2);

    EXPECT_TRUE(bool2);
    EXPECT_FALSE(test_old_class2.student_in_class(test_student2));
    EXPECT_TRUE(test_new_class2.student_in_class(test_student2));

    interface testi3;
    testi3.read_data_classes_per_uc();
    testi3.read_data_classes();
    testi3.read_data_students_classes();

    course test_course3("L.EIC001");
    class1 test_old_class3("1LEIC01");
    class1 test_new_class3("1LEIC03");
    student test_student3("Rute","202028717");
    string error_message3 = "";
    bool bool3 = testi3.switch_student_classes(test_student3,test_course3,test_old_class3,test_new_class3,error_message3);

    for(course c : testi3.get_courses()){
        if(c == test_course3){
            test_course3 = c;
        }
    }

    test_course3.get_class(test_old_class3);
    test_course3.get_class(test_new_class3);

    EXPECT_EQ(error_message3,"The student is not enrolled in class 1LEIC01 of course L.EIC001");
    EXPECT_FALSE(bool3);

    interface testi4;
    testi4.read_data_classes_per_uc();
    testi4.read_data_classes();
    testi4.read_data_students_classes();

    course test_course4("L.EIC013");
    class1 test_old_class4("2LEIC09");
    class1 test_new_class4("2LEIC12");
    student test_student4("Manuel Benjamin","202047162");
    string error_message4 = "";
    bool bool4 = testi4.switch_student_classes(test_student4,test_course4,test_old_class4,test_new_class4,error_message4);

    for(course c : testi4.get_courses()){
        if(c == test_course4){
            test_course4 = c;
        }
    }

    test_course4.get_class(test_old_class4);
    test_course4.get_class(test_new_class4);

    EXPECT_EQ(error_message4,"The student could not be added to their desired class.");
    EXPECT_FALSE(bool4);
    EXPECT_TRUE(test_old_class4.student_in_class(test_student4));
    EXPECT_FALSE(test_new_class4.student_in_class(test_student4));

    interface testi5;
    testi5.read_data_classes_per_uc();
    testi5.read_data_classes();
    testi5.read_data_students_classes();

    course test_course5("L.EIC001");
    class1 test_old_class5("1LEIC02");
    class1 test_new_class5("1LEIC06");
    student test_student5("Sara","202022172");
    string error_message5 = "";
    bool bool5 = testi5.switch_student_classes(test_student5,test_course5,test_old_class5,test_new_class5,error_message5);

    for(course c : testi5.get_courses()){
        if(c == test_course5){
            test_course5 = c;
        }
    }

    test_course5.get_class(test_old_class5);
    test_course5.get_class(test_new_class5);

    EXPECT_TRUE(bool5);
    EXPECT_FALSE(test_old_class5.student_in_class(test_student5));
    EXPECT_TRUE(test_new_class5.student_in_class(test_student5));

}

TEST(system_changes,switch_student_courses){
    interface testi1;
    testi1.read_data_classes_per_uc();
    testi1.read_data_classes();
    testi1.read_data_students_classes();

    student test_target_student1("Rute","202028717");
    course test_added_course1("L.EIC014");
    class1 test_added_class1("2LEIC07");
    course test_removed_course1("L.EIC003");
    string error_message1 = "";

    bool bool1 = testi1.switch_student_courses(test_target_student1,test_removed_course1,test_added_course1,test_added_class1,error_message1);

    for(course c : testi1.get_courses()){
        if(c == test_added_course1){
            test_added_course1 = c;
        }
        if(c == test_removed_course1){
            test_removed_course1 = c;
        }
    }
    test_added_course1.get_class(test_added_class1);
    EXPECT_TRUE(bool1);
    EXPECT_EQ(error_message1,"Student could not be allocated to their desired class.");
    EXPECT_TRUE(test_added_course1.has_student(test_target_student1));
    EXPECT_FALSE(test_removed_course1.has_student(test_target_student1));
    EXPECT_FALSE(test_added_class1.student_in_class(test_target_student1));

    interface testi2;
    testi2.read_data_classes_per_uc();
    testi2.read_data_classes();
    testi2.read_data_students_classes();

    student test_target_student2("Rute","202028717");
    course test_added_course2("L.EIC013");
    class1 test_added_class2("2LEIC10");
    course test_removed_course2("L.EIC011");
    string error_message2 = "";

    bool bool2 = testi2.switch_student_courses(test_target_student2,test_removed_course2,test_added_course2,test_added_class2,error_message2);

    for(course c : testi2.get_courses()){
        if(c == test_added_course2){
            test_added_course2 = c;
        }
        if(c == test_removed_course2){
            test_removed_course2 = c;
        }
    }

    test_added_course2.get_class(test_added_class2);

    EXPECT_TRUE(bool2);
    EXPECT_TRUE(test_added_course2.has_student(test_target_student2));
    EXPECT_FALSE(test_removed_course2.has_student(test_target_student2));
    EXPECT_TRUE(test_added_class2.student_in_class(test_target_student2));




}


TEST(data_readers,read_data_students_requests){
    interface testi;
    testi.read_data_classes_per_uc();
    testi.read_data_classes();
    testi.read_data_students_classes();
    testi.read_data_students_requests();

    student target_student("Rute","202028717");
    course added_course("L.EIC012");
    class1 added_class("2LEIC05");
    class1 removed_class("2LEIC11");

    EXPECT_EQ(testi.get_requests().size(),4);
    EXPECT_EQ(testi.get_requests().front().target_student,target_student);
    EXPECT_EQ(testi.get_requests().front().request_type,"switch classes");
    EXPECT_EQ(testi.get_requests().front().added_course,added_course);
    EXPECT_EQ(testi.get_requests().front().added_class,added_class);
    EXPECT_EQ(testi.get_requests().front().removed_class,removed_class);
}

//=============================================================================
// BENCHMARK
//=============================================================================

static void BM_convert_class_to_hour_and_minute_format(benchmark::State& state){
    schedule s;
    class1 cl{"test"};
    auto rng = std::default_random_engine {};
    vector<int> rnd(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        // runtime of this will be ignored
        for (int i=0; i< state.range(0); i++)
            rnd.at(i) = i;
        vector<int> rnd2 = rnd;
        std::shuffle(std::begin(rnd), std::end(rnd), rng);
        for (int i=0; i< state.range(0); i++) {
            s.week_day.append(std::to_string(rnd.at(i)));
        }
        s.duration = state.range(0);
        s.hour = state.range(0);
        //This code gets timed
        state.ResumeTiming();
        cl.convert_class_to_hour_and_minute_format(s);

        }
    state.SetComplexityN(state.range(0));
}

static void BM_read_data_classes_per_uc(benchmark::State& state){
    for (auto _ : state) {
        state.PauseTiming();
        interface testi;
        //This code gets timed
        state.ResumeTiming();
        testi.read_data_classes_per_uc();

    }
    state.SetComplexityN(state.range(0));
}


//=============================================================================
// Register the functions as a benchmark
//=============================================================================



/*
BENCHMARK(BM_convert_class_to_hour_and_minute_format)
        ->Unit(benchmark::kNanosecond)
        ->RangeMultiplier(2)->Range(1<<5, 1<<10)
        ->Complexity();
*/

/*
BENCHMARK(BM_read_data_classes_per_uc)
        ->Unit(benchmark::kNanosecond)
        ->RangeMultiplier(2)->Range(1<<5, 1<<10)
        ->Complexity();
*/
