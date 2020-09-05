#!/usr/local/bin/node

const readline = require('readline');
const fs = require('fs');
const path = require('path');
const pinyin = require('tiny-pinyin');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

let title = '';
let locale = 'en-US';
const datetime = new Date().toISOString();
const date = datetime.split('T')[0];

rl.question('What is your blog title?\n', originalTitle => {
  title = originalTitle.toLowerCase();
  rl.question('Is this an English blog (Y/N)?\n', answer => {
    if (answer.indexOf('N') !== -1) locale = 'zh-CN';
    rl.close();
    let filename = '';
    if (locale === 'en-US') {
      filename = `${date}-${title.split(' ').join('-')}.md`;
    } else {
      const letters = title.split('');
      const converted = letters.map(letter =>
        pinyin.convertToPinyin(letter).toLowerCase()
      );
      const mid = [[]];
      for (let i = 0; i < letters.length; ++i) {
        if (letters[i] !== converted[i]) mid.push([]);
        mid[mid.length - 1].push(converted[i]);
        if (letters[i] !== converted[i]) mid.push([]);
      }
      filename = `${date}-${mid
        .map(letters => letters.join(''))
        .filter(str => str.length > 0)
        .join('-')}.md`;
    }
    const content = `---
lang: ${locale}
published: ${datetime}
keywords:
description:
  content: 
---

# ${originalTitle}

<Utterances />
`;
    fs.writeFileSync(
      path.join(process.cwd(), 'docs', '_blogs', filename),
      content
    );
  });
});
