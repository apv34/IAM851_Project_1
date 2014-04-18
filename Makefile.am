
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = \
        test_kdv_simple \
        test_kdv_two \
        test_kdv_three \
        test_kdv_scaling \
        test_kdv_comp \
        test_kdv_comp_two \
        test_kdv_comp_three \
        test_kdv_long \
        test_kdv_parallel_scaling

lib_LIBRARIES = libkdv.a
libkdv_a_SOURCES = \
        vector_fun.h \
        vector_fun.c \
        kdv_equation.h \
        kdv_equation.c \
        solver.h \
        solver.c \
        test_kdv_simple.c \
        test_kdv_two.c \
        test_kdv_three.c \
        test_kdv_scaling.c \
        test_kdv_comp.c \
        test_kdv_comp_two.c \
        test_kdv_comp_three.c \
        test_kdv_long.c \
        test_kdv_parallel_scaling.c
		
LDADD = libkdv.a

TESTS = \
        test_kdv_simple \
        test_kdv_two \
        test_kdv_three \
        test_kdv_scaling \
        test_kdv_comp \
        test_kdv_comp_two \
        test_kdv_comp_three \
        test_kdv_long \
        test_kdv_parallel_scaling
