#!/usr/bin/env node

const util = require('util');

const exec = util.promisify(require('child_process').exec);
const options = { maxBuffer: 10000000000 * 1024, cwd: process.cwd() };
const isDarwin = /^darwin/.test(process.platform);
const grep = 'grep -v [^A-Za-z] /usr/share/dict/words';
const shuf = isDarwin ? 'gshuf' : 'shuf';
const tail = `tail ${isDarwin ? "-" : "--lines="}`;
var path = "./"
var total = [10, 20, 50, 100, 1000, 2000, 5000, 10000, 200000, 500000];

async function df() {
  var { stdout } = await exec(`df -k . | sed -n 2p | awk '{print $2, $3}'`);
  const space = stdout.split(' ');
  const size = space[0], used = space[1];
  return used < size;
}

async function generate_dictionary() {
  await exec(`${grep} > dictionary`, options);
  console.log('Dictionary created');
}

async function generate_shuffled() {
  var sequence = [0, 1, 2, 3, 4, 5, 6, 7, 8 , 9, 10];
  for(let i = 0; i < sequence.length; i++) {
    
  }
}