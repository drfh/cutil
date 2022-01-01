project('cutils', 'c',
	default_options : [
		'warning_level=3',
		'werror=false',
		'debug=false',
		'optimization=2',
		'c_std=c2x', 'build.c_std=c2x',
		'default_library=static'
		],
	license: 'UNLICENSE',
	version: '0.1.0',
)
project_description = 'Basic units, types and process code.'
add_project_arguments('-Wpedantic', language : 'c')
# add_project_arguments('-Wextra', language : 'c')
add_project_arguments('-Wshadow', language : 'c')

project_source_files = files(
	'source/carray.c'
	# ,'source/cbencode.c'
	,'source/cdict.c'
	,'source/cmemory.c'
	,'source/cprint_data.c'
	,'source/cstream.c'
	,'source/mybzero.c'
	,'source/mymemmove.c'
	# ,'source/sdict.c'
	,'source/sstring.c'

	,'source/bencode.c'
	,'source/md5.c'
	,'source/uuid4.c'
)

project_headers = [
	'include/cutil.h'
	,'include/carray.h'
	# ,'include/cbencode.h'
	,'include/cdict.h'
	,'include/clist.h'
	,'include/cmemory.h'
	,'include/cstack.h'
	,'include/macros.h'
	,'include/mybzero.h'
	,'include/mymemmove.h'
	,'include/sdict.h'
	,'include/sstring.h'
	,'include/types.h'

	,'include/bencode.h'
	,'include/md5.h'
	,'include/uuid4.h'
	,'include/ANSI-color-codes.h'
]
headers = files(project_headers)
subdir('include-workaround-meson/cutil')

# global_headers = [
# 	,'globals/global.h'
# 	,'globals/global_defs.h'
# 	,'globals/global_mem.h'
# ]

build_args = [
'-Wpedantic'
]

dependencies=[
	dependency('threads',static:true)
	,dependency('libconfig',static:true)
	# ,dependency('libcjson')
	# ,dependency('glib-2.0')
	# ,dependency('libcrypt')
	# ,dependency('libsodium')
	# ,libsodium_dep
	# ,dependency('libxxhash')
]

# ===================================================================
# ======
# Target
# ======
# project_headers = include_directories('include','globals','source')
# project_headers = include_directories('include','globals','source','source/memory','source/smart','source/xtra')

private_headers = include_directories('globals')
public_headers = include_directories('include')

build_args += [
	'-DPROJECT_NAME=' + meson.project_name(),
	'-DPROJECT_VERSION=' + meson.project_version(),
]
# # Only make public interfaces visible
# if target_machine.system() == 'windows' or target_machine.system() == 'cygwin'
# 	build_args += '-DMYLIB_PUBLIC="__declspec(dllexport)"'
# else
# 	build_args += '-DMYLIB_PUBLIC=__attribute__((visibility("default")))'
# endif

project_target = library(
	meson.project_name(),
	project_source_files,
	install : true,
	c_args : build_args,
	include_directories : [public_headers,private_headers],
	dependencies:dependencies
)
# project_target_static=static_library(
# 	meson.project_name(),
# 	project_source_files,
# 	install : true,
# 	c_args : build_args,
# 	include_directories : [public_headers,private_headers],
# 	dependencies:dependencies
# )

# cutils=library('cutils', project_source_files, include_directories:project_headers, version : '0.1.0', soversion : '0')

# =======
# Project
# =======

# Make this library usable as a Meson subproject.
# project_dep = declare_dependency(
# 	include_directories: [public_headers,'include-workaround-meson'],
# 	link_with : project_target,
# )
project_dep = declare_dependency(
	include_directories: [public_headers,'include-workaround-meson'],
	link_with : project_target,
)
# meson.override_dependency('cutil', project_dep)
# project_dep_static=declare_dependency(
# 	include_directories: [public_headers,'include-workaround-meson'],
# 	link_with : project_target_static,
# )


set_variable(meson.project_name() + '_dep', project_dep)
if meson.version().version_compare('>=0.54.0')
	meson.override_dependency('cutils', project_dep)
	# meson.override_dependency('libcutil_static', project_dep_static)
endif


# Make this library usable from the system's
# package manager.
install_headers(project_headers, subdir:meson.project_name())
# install_man('docs/cutil.1') # -> share/man/man1/foo.1
# install_data('datafile.dat', install_dir : get_option('datadir') / 'progname')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
	name : meson.project_name(),
	filebase : meson.project_name(),
	description : project_description,
	subdirs : meson.project_name(),
	# libraries : project_target,
	# default_library:static
)

# ==========
# Unit Tests
# ==========

if not meson.is_subproject()
	subdir('tests')
	# test('all_tests',
	# 	executable(
	# 		'run_tests',
	# 		files(project_test_files),
	# 		dependencies : [project_dep],
	# 		install : false
	# 	)
	# )
endif
