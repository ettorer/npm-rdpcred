{
  'targets': [
    {
      'target_name': 'rdpcred',
      'conditions': [ [
		'OS=="win"',
		{
	      'sources': [ 'rdpcred.cc' ],
	      'msvs_settings': {
	        'VCLinkerTool': {
	          'AdditionalDependencies': [
	            'Crypt32.lib'
	          ]
	        }
	      }		
		}
	  ] ]
    }
  ]
}