
peerchat_src=[
	# 'enviro.c',
	'config_file.c',
	'options.c',
	'globals.c',
	'peerchat.c'
]

# Normal config.h file
cdata = configuration_data()
epoc_date = run_command('date', '+%s', check: true).stdout().strip()
cdata.set('__BUILD_DATE',epoc_date)
cdata.set('__BUILD_NUMBER','000001')
configure_file(input:'config.in',output:'config.h',configuration:cdata)

# peerchat_inc=[
# 	'peerchat.h',
# ]

# sodium_dep=dependency('sodium')
peerchat_dep=[dependencies,project_dep]
peerchat=executable('peerchat',peerchat_src,include_directories:public_headers,dependencies:peerchat_dep)
#
# test_base=executable('test1','test1.c',include_directories:public_headers,link_with:project_target)
# test('test1',test_base)
#
# test_base=executable('test2','test1.c',include_directories:public_headers,link_with:project_target)
# test('test2',test_base)
