#
# load_plugin_demo.py
# Mich, 2015-12-22
# This file is part of MLDB. Copyright 2015 Datacratic. All rights reserved.
#

if False:
    mldb = None

def perform(*args, **kwargs):
    res = mldb.perform(*args, **kwargs)
    assert res['statusCode'] in [200, 201], str(res)
    return res

hello_world_url = '/v1/types/functions/helloWorld'

res = mldb.perform('GET', hello_world_url)
assert res['statusCode'] == 404, str(res)

perform('PUT', '/v1/plugins/sample', [], {
    'type' : 'sharedLibrary',
    'params' : {
        'address' : 'build/x86_64/lib/',
        'library' : 'libmldb_sample_plugin.so',
        'apiVersion' : '1.0.0',
        'allowInsecureLoading' : True
    }
})

# now it exists
mldb.log(perform('GET', hello_world_url))
