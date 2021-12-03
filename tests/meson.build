# project_test_files = [
# 	'tests/test_base.c'
# 	,'tests/test_mybzero.c'
# 	# ,'tests/test_carray.c'
# ]
test_build_args=[
	'--include-prefix=cutil'
]
test_base=executable('test_base','test_base.c',include_directories:public_headers,link_with:project_target)
test('base',test_base)

test_mybzero=executable('test_mybzero','test_mybzero.c',include_directories:public_headers,dependencies:project_dep,link_with:project_target)
test('mybzero',test_mybzero)

test_sstring=executable('test_sstring','test_sstring.c',include_directories:public_headers,dependencies:project_dep,link_with:project_target)
test('sstring',test_sstring)

test_carray=executable('test_carray','test_carray.c',include_directories:public_headers,dependencies:project_dep,link_with:project_target)
test('carray',test_carray)
#
# test_carray_alt=executable('test_carray_alt','test_carray_alt.c')
# test('carray',test_carray_alt)
#
# test_cdict=executable('test_cdict','test_cdict.c')
# test('cdict',test_cdict)


# executable('test_sdict','test_cdict.c',include_directories:project_headers)
# test('sdict',test_sdict)


# executable('test_stream','test_stream.c',include_directories:project_headers)
# executable('test_bencode','test_bencode.c',include_directories:project_headers)
# executable('test_bencode','test_bencode.c',include_directories:project_headers)
