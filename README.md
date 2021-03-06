#  Windows Credential Manager module for Node.js 

  This module exports methods to inject/remove credentials to/from the Windows Credential Manager. It is used to perform SSO RDP connection with Node.js or Electron scripts
  
## Requirements

 * Windows XP or higher

## Build

 * download the latest source https://github.com/ettorer/npm-rdpcred/archive/master.zip
 * expand and open a command prompt in the folder containing the source
 * node-gyp config
 * node-gyp build 
    
## Example

```javascript
var rdpcred = require('rdpcred');

rdpcred.setCredentials({ account: 'MYDOMAIN\\user', service: 'TERMSRV/HOST', password: 'mypassword' }, function(err) {
  console.log('Credentials added');
  rdpcred.deleteCredentials({ service: 'TERMSRV/HOST' }, function(err) {
    console.log('Credentials removed');
  });
});
```

## License 

(The MIT License)

Copyright (c) 2018 Ettore Roberto Rizza &lt;er@flydesktop.com&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
