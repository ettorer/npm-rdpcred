/*!
 * node-rdpcred
 * Copyright(c) 2018 Ettore Rizza <er@flydesktop.com>
 * MIT Licensed
 */

/**
 * Module dependencies.
 */

var spawn = require('child_process').spawn;
var rdpcred = require('./build/Release/rdpcred.node');

/**
 * RdpCredentialsStore for computers running Node.js
 *
 * @class RdpCredentialsStore
 * @api public
 */

function RdpCredentialsStore() {

}

/**
 * Set/update credentials in the Credential Manager.
 *
 * @param {Object} opts Object containing `account`, `service`, and `password`
 * @param {Function} fn Callback
 * @api public
 */

RdpCredentialsStore.prototype.setCredentials = function(opts, fn) {
  opts = opts || {};
  var err;

  if (!opts.account) {
    err = new Error('An account is required');
    fn(err, null);
    return;
  }

  if (!opts.service) {
    err = new Error('A service is required');
    fn(err, null);
    return;
  }

  if (!opts.password) {
    err = new Error('A password is required');
    fn(err, null);
    return;
  }

  if (rdpcred.add(opts.service, opts.account, opts.password)) {
    fn(null);
  } else {
    err = new Error('Could not save the credentilas on Credential Manager');
    fn(err);
  }
};

/**
* Delete credentials from the Credential Manager.
*
* @param {Object} opts Object containing `account`, `service`, and `password`
* @param {Function} fn Callback
* @api public
*/

RdpCredentialsStore.prototype.deleteCredentials = function(opts, fn)
{

  opts = opts || {};
  var err;

  if (!opts.service) {
    err = new Error('A service is required');
    fn(err);
    return;
  }

  if (rdpcred.del(opts.service)) {
	  fn(null);
  } else {
  	err = new Error('Could not remove the credentilas from Credential Manager');
    fn(err);
  }
  
};

/**
 * Expose new RdpCredentialsStore
 */

module.exports = new RdpCredentialsStore();
