cmake_minimum_required(VERSION 3.29)
project(3semestr_2laboratory)

set(CMAKE_CXX_STANDARD 23)

add_executable(3semestr_2laboratory main.cpp
        dynamic_array.h
        file_reader.cpp
        file_reader.h
        graph_builder.cpp
        graph_builder.h
        isorter.h
        main.cpp
        people.h
        names.h
        sequence.h
        sortings.h
        menu.cpp
        menu.h
        file_generator.cpp
        file_generator.h
        file_writer.h
        file_writer.cpp
        comparings.cpp
        comparings.h
        functional_tests.cpp
        functional_tests.h
)
