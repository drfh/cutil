project('cutils', 'c',
	default_options : [
		'warning_level=3',
		'werror=false',
		# This project defaults to a release build
		'debug=false',
		'optimization=2',
		'c_std=c2x', 'build.c_std=c2x'
		],
	license: 'UNLICENSE',
	version: '0.1.0',
)
project_description = 'Basic units, types and process code.'

project_source_files = files(
	'source/carray.c'
	# ,'source/cbencode.c'
	,'source/cdict.c'
	,'source/cprint_data.c'
	,'source/cstream.c'
	,'source/mybzero.c'
	# ,'source/sdict.c'
	,'source/sstring.c'
)

project_headers = [
	'include/carray.h'
	# ,'include/cbencode.h'
	,'include/cdict.h'
	,'include/clist.h'
	,'include/cmemory.h'
	,'include/cstack.h'
	,'include/macros.h'
	,'include/mybzero.h'
	,'include/sdict.h'
	,'include/sstring.h'
]
headers = files(project_headers)
subdir('include-workaround-meson/cutil')

# global_headers = [
# 	,'globals/global.h'
# 	,'globals/global_defs.h'
# 	,'globals/global_mem.h'
# ]

build_args = [
]

dependencies=[
	dependency('threads')
	,dependency('libconfig')
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

project_target = shared_library(
	meson.project_name(),
	project_source_files,
	# version: meson.version(),
	install : true,
	c_args : build_args,
	# gnu_symbol_visibility : 'hidden',
	include_directories : [public_headers,private_headers],
	dependencies:dependencies
)
# project_target=shared_library('libpeers', project_source_files, include_directories:project_headers, dependencies:dependencies, version:'0.1.0', soversion:'0')
# cutils=library('cutils', project_source_files, include_directories:project_headers, version : '0.1.0', soversion : '0')


# =======
# Project
# =======

# Make this library usable as a Meson subproject.
project_dep = declare_dependency(
	include_directories: [public_headers,'include-workaround-meson'],
	link_with : project_target
)
set_variable(meson.project_name() + '_dep', project_dep)
if meson.version().version_compare('>=0.54.0')
	meson.override_dependency('libcutil', project_dep)
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
	libraries : project_target,
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
