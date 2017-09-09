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

async function generate_dictionary() {
  await exec(`${grep} > dictionary`, options);
  console.log('Dictionary created');
}

async function generate_shuffled() {
  let sequence = [1, 2, 3, 4, 5, 6, 7, 8 , 9, 10];
  echo('info: generating a list of 100 million words (non-unique)');
  await exec('cat dictionary > temp-words-A')
  for(let i = 0; i < sequence.length; i++) {
    await exec('cat temp-words-A >> temp-words-B', options)
    if (!(await df())) {
      console.log('error: low disk space.');
      if (await wc('temp-words-A') < await wc('temp-words-B')) {
        await mv('temp-words-A', 'words-100M')
        await rm('temp-words-A');
        break;
      }
      await mv('temp-words-B', 'words-100M')
      await rm('temp-words-B');
      break;
    }
    await exec('cat temp-words-B >> temp-words-A'), options;
  }
  await exec(`${head}100000000 temp-words-A > words-100M`, options)

  await rm('temp-words-A', 'temp-words-B');

  sequence.push(11, 12, 13);

  for(let power = 0; power < sequence.length; power++) {
    let size = Math.pow(100000 * 2, sequence[power]);

    await exec(`${head}${size} words-100M | ${shuf} > shuffled-words-${size}`)
    await echo(`info: generated shuffled-words-${size}.`)
  }

}