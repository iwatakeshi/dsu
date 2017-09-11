#!/usr/bin/env node

const util = require('util');

const exec = util.promisify(require('child_process').exec);
const options = { maxBuffer: 10000000000 * 1024, cwd: process.cwd() };
const isDarwin = /^darwin/.test(process.platform);
const grep = 'grep -v [^A-Za-z] /usr/share/dict/words';
const shuf = isDarwin ? 'gshuf' : 'shuf';
const head = `head ${isDarwin ? "-" : "--lines="}`;
const tail = `tail ${isDarwin ? "-" : "--lines="}`;
var path = "./"
var total = [10, 20, 50, 100, 1000, 2000, 5000, 10000, 200000, 500000];

/**
 * Determines whether space is available
 */
async function df() {
  var { stdout } = await exec(`df -k . | sed -n 2p | awk '{print $2, $3}'`);
  const space = stdout.split(' ');
  const size = space[0], used = space[1];
  return used < size;
}

async function wc(file) {
  const { stdout } = await exec(`wc -w ${file}`, options);
  return parseInt(stdout);
}

async function mv(from, to) {
  await exec(`mv ${from} ${to}`, options);
}

async function rm(...file) {
  await exec(`rm -f ${file.join(' ')}`, options);
}

async function echo(message) {
  await exec(`echo ${message}`);
}

async function generate() {
  for(let power = 0; power < 53; power++) {
    let size = Math.pow(2, sequence[power]);
    await exec(`./random.o ${size} 1 0 ${size}> random-${size}`);
    await echo(`info: generated random-${size}.`)
  }
}

(async function() {
  await generate();
})()