
cmake_minimum_required(VERSION 2.8...3.13)
project(fips-duktape)
# include the fips main cmake file
get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

fips_setup()

	# duktape
        fips_begin_lib(duktape)
            fips_dir(duktape/src)
            fips_files(
                duk_config.h
                duktape.h
                duktape.c
            )
        fips_end_lib()
        target_include_directories(duktape PUBLIC duktape/src)


	# the "original?" module approach
		fips_begin_lib(dukmod_duktape)
			fips_deps(duktape)
			fips_dir(duktape/module-duktape)
			fips_files(
				duk_module_duktape.c
				duk_module_duktape.h
			)
		fips_end_lib()
		target_include_directories(dukmod_duktape PUBLIC duktape/module-duktape/)
        # teh test
            fips_begin_app(dukmod_duktape_test cmdline)
                fips_deps(dukmod_duktape)
                fips_dir(duktape/module-duktape)
                fips_files(
                    test.c
                )
            fips_end_app()


	# the "more nodejs?" module approach
		fips_begin_lib(dukmod_nodeish)
			fips_deps(duktape)
			fips_dir(duktape/module-nodeish)
			fips_files(
				duk_module_node.c
				duk_module_node.h
			)
		fips_end_lib()
		target_include_directories(dukmod_nodeish PUBLIC duktape/module-nodeish/)
        # the test
            fips_begin_app(dukmod_nodeish_test cmdline)
                fips_deps(dukmod_nodeish)
                fips_dir(duktape/module-nodeish)
                fips_files(
                    test.c
                )
            fips_end_app()


	# add libs to not-windows
        IF (MSVC)
            # ...
        ELSE()
            target_link_libraries(duktape m)
            target_link_libraries(dukmod_duktape_test m)
            target_link_libraries(dukmod_nodeish_test m)
        ENDIF()
