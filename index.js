/*!
 * node-rdpcred
 * Copyright(c) 2018 Ettore Rizza <er@flydesktop.com>
 * MIT Licensed
 */

/**
 * Module dependencies.
 */

var spawn = require('child_process').spawn;
var os = require('os');

var ost = os.type().toLowerCase();
var OSObj = null;
if (ost.indexOf('lin') === 0) {
} else if (ost.indexOf('darwin') === 0) {
} else if (ost.indexOf('win') === 0) {
    OSObj = require('./rdpcred.js');
} else {
}

module.exports = OSObj;
