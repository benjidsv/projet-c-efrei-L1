cmake_minimum_required(VERSION 3.24)
project(projetC C)

set(CMAKE_C_STANDARD 23)

add_executable(projetC main.c datastructures/shapes.c datastructures/shapes.h datastructures/linked_list.h shape_manager.c shape_manager.h user_interface.c user_interface.h)
